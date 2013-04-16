//- Copyright (c) Autodesk, Inc. All rights reserved.
//- by Cyrille Fauvel - Autodesk Developer Technical Services

//wizard.OkCancelAlert(FindAutoCADUsingWMI('test')); return;
// http://msdn.microsoft.com/en-us/library/aa291835(v=VS.71).aspx
// http://msdn.microsoft.com/en-us/library/microsoft.visualstudio.vswizard.vcwizctlclass_members.aspx

function OnFinish (selProj, selObj) {
    try {
		var strProjectPath =wizard.FindSymbol ('PROJECT_PATH') ;
		var strProjectName =wizard.FindSymbol ('PROJECT_NAME') ;
		wizard.AddSymbol ("UPPER_CASE_PROJECT_NAME", strProjectName.toUpperCase ()) ;
		
		wizard.AddSymbol ("SAFE_PROJECT_NAME", CreateSafeName (strProjectName)) ;
		wizard.AddSymbol ("UPPER_CASE_SAFE_PROJECT_NAME", CreateSafeName (strProjectName.toUpperCase ())) ;

		selProj =CreateProject (strProjectName, strProjectPath) ;
		AddCommonConfig (selProj, strProjectName, true) ; //- Unicode
		AddSpecificConfigs (selProj, strProjectName, strProjectPath) ;
		SetupFilters (selProj) ;

		//AddFilesToProjectWithInfFile (selProj, strProjectName) ;
		var InfFile =CreateInfFile () ;
		AddFilesToCustomProj (selProj, strProjectName, strProjectPath, InfFile) ;
		//AddFilesToProject (selProj, strProjectName, oCollection, InfFile) ;
		InfFile.Delete () ;
		
		SetCommonPchSettings (selProj) ;
		selProj.Object.Save () ;
		
		var bOmf =wizard.FindSymbol ("OMF_APP") ;
		if ( bOmf )
			MakeOmfResourceProject (selProj, strProjectPath, strProjectName)

	} catch (e) {
		if ( e.description.length != 0 )
			SetErrorInfo (e) ;
		return (e.number) ;
	}
}

//-----------------------------------------------------------------------------
function AddFilesToCustomProj (proj, strProjectName, strProjectPath, InfFile) {
	try {
		var projItems =proj.ProjectItems ;

		var strTemplatePath =wizard.FindSymbol ('TEMPLATES_PATH') ;

		var strTpl ='' ;
		var strName ='' ;

		var strTextStream =InfFile.OpenAsTextStream (1, -2) ;
		while ( !strTextStream.AtEndOfStream ) {
			strTpl =strTextStream.ReadLine () ;
			if ( strTpl != '' ) {
				strName =strTpl ;
				var strTarget =GetTargetName (strName, strProjectName) ;
				var strTemplate =strTemplatePath + '\\' + strTpl ;
				var strFile =strProjectPath + '\\' + strTarget ;

				var bCopyOnly =false ;  //----- "true" will only copy the file from strTemplate to strTarget without rendering/adding to the project
				var strExt =strName.substr (strName.lastIndexOf ('.')) ;
				if ( strExt == '.bmp' || strExt==".ico" || strExt=='.gif' || strExt=='.rtf' || strExt=='.css' )
					bCopyOnly =true ;
				wizard.RenderTemplate (strTemplate, strFile, bCopyOnly) ;
				proj.Object.AddFile (strFile) ;
		}
		}
		strTextStream.Close () ;
	} catch (e) {
		throw e ;
	}
}

//-----------------------------------------------------------------------------
function AddSpecificConfigs (proj, strProjectName, strProjectPath) {
    try {
        var strAcadPath =FindAutoCAD () ;
		//- Win32
        AddConfig (proj, strProjectName, /*Debug*/true, /*Win32*/true, strAcadPath) ;
        AddConfig (proj, strProjectName, /*Release*/false, /*Win32*/true, strAcadPath) ;
	    //- x64
        var plist =proj.ConfigurationManager.SupportedPlatforms.toArray () ;
        for ( var i =0 ; i < plist.length ; i++ ) {
            if ( plist [i] == 'x64' ) {
				proj.ConfigurationManager.AddPlatform ('x64', 'x64', true) ;
				AddConfig (proj, strProjectName, /*Debug*/true, /*x64*/false, strAcadPath) ;
				AddConfig (proj, strProjectName, /*Release*/false, /*x64*/false, strAcadPath) ;
                break ;
            }
        }
   } catch ( e ) {
		throw e ;
   }
}

function AddConfig (proj, strProjectName, bDebug, bWin32, strAcadPath) {
	try {
		var szRds =wizard.FindSymbol ('RDS_SYMB') ;
		var bArxAppType =wizard.FindSymbol ('APP_ARX_TYPE') ;
		var bOmfAppType =wizard.FindSymbol ('OMF_APP') ;
		var bMfcExtDll =wizard.FindSymbol ('MFC_EXT_SHARED') ;
		var bSharedMfc =(wizard.FindSymbol ('MFC_REG_SHARED') || bMfcExtDll) ;
		var bMfcSupport =(wizard.FindSymbol ('MFC_REG_STATIC') || bSharedMfc) ;
		var bUseAtl =wizard.FindSymbol ('ATL_COM_SERVER') ;
		var bComServer =(wizard.FindSymbol ('STD_COM_SERVER') || bUseAtl) ;
		var bDotNetModule =wizard.FindSymbol ('DOTNET_MODULE') ;
		var bImplDebug =wizard.FindSymbol ('IMPL_DEBUG') ;
		var szUprProjectName =CreateSafeName (strProjectName.toUpperCase ()) ;
	
		var cfgName =bDebug ? 'Debug' : 'Release' ;
		cfgName +='|' + (bWin32 ? 'Win32' : 'x64') ;
		var config =proj.Object.Configurations (cfgName) ;
		if ( config == null )
		    return ;
		config.ConfigurationType =typeDynamicLibrary ;
		config.IntermediateDirectory ='$(PlatformName)\\$(ConfigurationName)' ;
		config.OutputDirectory ='$(SolutionDir)$(PlatformName)\\$(ConfigurationName)' ;
		config.CharacterSet =charSetUnicode ;
		config.useOfMfc =bMfcSupport ? useMfcDynamic : useMfcStdWin ;
		config.useOfAtl =bUseAtl ? useATLDynamic : useATLNotSet ;
		
		if ( wizard.DTE.Version == '10.0' ) {
		//	config.PlatformToolset =v90 ;
			proj.Object.TargetFrameworkVersion =eFrameworkVersion35 ;
			config.ManagedExtensions =bDotNetModule ? managedAssembly : managedNotSet ;
			//- telling anything below or equal to 3.5 will force the PlatformToolset to be v90
			//- this is designed in the C:\Program Files (x86)\MSBuild\Microsoft.Cpp\v4.0\Microsoft.Cpp.Defaults.props
		} else {
			config.ManagedExtensions =bDotNetModule ;
		}

		var CLTool =config.Tools ('VCCLCompilerTool') ;
		CLTool.DebugInformationFormat =/*debugOption.*/bDebug ? (bWin32 ? debugEditAndContinue : debugEnabled) : debugDisabled ;
		CLTool.WarningLevel =warningLevel_1 ;
		CLTool.TreatWChar_tAsBuiltInType =true ;
		CLTool.ForceConformanceInForLoopScope =true ;
		CLTool.Optimization =bDebug ? optimizeDisabled : optimizeMaxSpeed ;
		CLTool.MinimalRebuild =bDebug ;
		CLTool.StringPooling =!bDebug ;
		CLTool.BasicRuntimeChecks =bDebug ? runtimeBasicCheckAll : runtimeBasicCheckNone ;
		CLTool.BufferSecurityCheck =true ;
		CLTool.RuntimeLibrary =rtMultiThreadedDLL ;
		CLTool.RuntimeTypeInfo =true ;
		CLTool.UsePrecompiledHeader =/*pchCreateUsingSpecific*//*pchGenerateAuto*/pchUseUsingSpecific ;
		//CLTool.PrecompiledHeaderFile ="StdAfx.h" ;
		//- AD_UNICODE UNICODE _UNICODE are added either by .h or setting unicode at the project level
		//- We do not add _DEBUG anymore to avoid problems on Release AutoCAD platform
		CLTool.PreprocessorDefinitions +=bWin32 ? 'WIN32' : '_WIN64' ;
		CLTool.PreprocessorDefinitions +=';_WINDOWS;' + szUprProjectName + '_MODULE' ;
		CLTool.PreprocessorDefinitions +=bDebug ? ''/*;_DEBUG*/ : ';NDEBUG' ;
		CLTool.PreprocessorDefinitions +=bImplDebug && bDebug ? ';_DEBUG' : '' ;
		CLTool.PreprocessorDefinitions +=bMfcExtDll ? ';_AFXEXT' : '' ;
		CLTool.PreprocessorDefinitions +=bArxAppType ? ';_ACRXAPP' : ';_DBXAPP' ;
		if ( bOmfAppType ) {
			CLTool.PreprocessorDefinitions +=';_OMFAPP;USE_ACAD_MODELER' ;
			CLTool.PreprocessorDefinitions +=bArxAppType ? '' : ';DBX' ;
			CLTool.AdditionalOptions +='-Zm1000' ;
		}
		if (bDotNetModule) {
		    CLTool.CompileAsManaged =/*managedAssembly*/1 ;
			CLTool.BasicRuntimeChecks =/*basicRuntimeCheckOption.*/runtimeBasicCheckNone ;
			CLTool.DebugInformationFormat =/*debugOption.*/bDebug ? debugEnabled : debugDisabled ;
			CLTool.MinimalRebuild =false ;
		}

		var LinkTool =config.Tools ('VCLinkerTool') ;
		LinkTool.LinkIncremental =linkIncrementalYes ;
		if ( bDotNetModule )
		    LinkTool.OutputFile ='$(outdir)/' + szRds + strProjectName + '.dll' ;
		else if ( bArxAppType )
			LinkTool.OutputFile ='$(outdir)/' + szRds + strProjectName + '.arx' ;
		else
			LinkTool.OutputFile ='$(outdir)/' + szRds + strProjectName + '.dbx' ;
		LinkTool.LinkDLL =true ;
		//if ( bOmfAppType )
		//    LinkTool.EntryPointSymbol ='DllMain' ;
		//LinkTool.ModuleDefinitionFile =strProjectName + '.def' ;
		LinkTool.SubSystem =subSystemWindows ;
		LinkTool.GenerateDebugInformation =bDebug ;
		LinkTool.ProgramDatabaseFile =bDebug ? '$(OutDir)/' + strProjectName + '.pdb' : '' ;
		LinkTool.ImportLibrary ='$(OutDir)/' + strProjectName + '.lib' ;
		LinkTool.TargetMachine =/*machineTypeOption.*/bWin32 ? machineX86 : machineAMD64 ;

		if ( bComServer ) {
			var MidlTool =config.Tools ("VCMidlTool") ;
			MidlTool.MkTypLibCompatible =false ;
			MidlTool.TargetEnvironment =/*midlTargetEnvironment.*/bWin32 ? midlTargetWin32 : midlTargetNotSet ;
			MidlTool.PreprocessorDefinitions =bDebug ? ''/*_DEBUG'*/ : 'NDEBUG' ;
			MidlTool.PreprocessorDefinitions +=bImplDebug && bDebug ? '_DEBUG' : '' ;
			MidlTool.HeaderFileName ='$(InputName).h' ;
			MidlTool.InterfaceIdentifierFileName =strProjectName + '_i.c' ;
			MidlTool.ProxyFileName =strProjectName + '_p.c' ;
			MidlTool.GenerateStublessProxies =true ;
			MidlTool.GenerateTypeLibrary  =true ;
			MidlTool.TypeLibraryName ='$(IntDir)/' + szRds + strProjectName + '.tlb' ;
			MidlTool.DLLDataFileName ='' ;
		}

		var ResTool =config.Tools ("VCResourceCompilerTool") ;
		ResTool.AdditionalIncludeDirectories +='$(IntDir)' ;

		var DebugTool =config.DebugSettings ;
		DebugTool.Command =strAcadPath + 'acad.exe' ;
		CLTool.AdditionalUsingDirectories +=strAcadPath ;
	} catch (e) {
		throw e ;
	}
}


//-----------------------------------------------------------------------------
function GetTargetName (strName, strProjectName) {
	try {
		//----- Set the name of the rendered file based on the template filename
		var strTarget =strName ;

		if ( strName.substr (0, 4) == 'Root' )
			strTarget =strProjectName + strName.substr (4, strName.length - 4) ;

		if ( strName.substr (0, 3) == 'Omf' )
			strTarget =strProjectName + strName.substr (3, strName.length - 3) ;

		return (strTarget) ;
	} catch (e) {
		throw e ;
	}
}

//-----------------------------------------------------------------------------
function MakeOmfResourceProject (selProj, strProjectPath, strProjectName) {
	//- So we need a resource only DLL
	RenderAddTemplate (wizard, "OmfEnuRes.h", strProjectPath + "\\Enu\\Resource.h", false, false) ;
	RenderAddTemplate (wizard, "OmfEnuRes.rc", strProjectPath + "\\Enu\\" + strProjectName + "Enu.rc", false, false) ;
	//----- Create CLSID
	var strResGUID =wizard.CreateGuid () ;
	var strFormattedGUID =wizard.FormatGuid (strResGUID, 0) ;
	wizard.AddSymbol ("PROJECT_RES_GUID", strFormattedGUID) ;
	var resDllProj ;
	if ( wizard.dte.Version == "10.0" ) {
		RenderAddTemplate (wizard, "OmfEnuRes.vcxproj", strProjectPath + "\\Enu\\" + strProjectName + "Enu.vcxproj", false, false) ;
		RenderAddTemplate (wizard, "OmfEnuRes.vcxproj.filters", strProjectPath + "\\Enu\\" + strProjectName + "Enu.vcxproj.filters", false, false) ;
		resDllProj =selProj.DTE.Solution.AddFromFile (strProjectPath + "\\Enu\\" + strProjectName + "Enu.vcxproj", false) ;
	} else {
	RenderAddTemplate (wizard, "OmfEnuRes.vcproj", strProjectPath + "\\Enu\\" + strProjectName + "Enu.vcproj", false, false) ;
		resDllProj =selProj.DTE.Solution.AddFromFile (strProjectPath + "\\Enu\\" + strProjectName + "Enu.vcproj", false) ;
	}
	
	var deps =selProj.DTE.Solution.SolutionBuild.BuildDependencies ;
	for ( var i =1 ; i <= deps.Count ; i++ ) {
		var dep =deps.Item (i) ;
		if ( dep.Project.UniqueName == selProj.UniqueName ) {
			dep.AddProject (resDllProj.UniqueName) ;
			break ;
		}
	}
}

//-----------------------------------------------------------------------------
//- See arxCommon.js for details
function FindAutoCAD () {
	var szPath ="c:\\Program Files\\AutoCAD 2011\\" ;
    return (szPath) ;
}
