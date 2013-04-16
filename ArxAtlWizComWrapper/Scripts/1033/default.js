//- Copyright (c) Autodesk, Inc. All rights reserved.
//- by Cyrille Fauvel - Autodesk Developer Technical Services

function OnFinish (selProj, selObj) {
	var oCM ;
	try {
		oCM	=selProj.CodeModel ;

		var strShortName =wizard.FindSymbol ("SHORT_NAME") ;
		var L_TRANSACTION_Text ="Add an AutoCAD COM wrapper object. " ;
		oCM.StartTransaction (L_TRANSACTION_Text + strShortName) ;

		var bDLL ;
		if ( typeDynamicLibrary == selProj.Object.Configurations (1).ConfigurationType )
			bDLL =true ;
		else
			bDLL =false ;
		wizard.AddSymbol ("DLL_APP", bDLL) ;

		var strProjectName =wizard.FindSymbol ("PROJECT_NAME") ;
		var strProjectPath =wizard.FindSymbol ("PROJECT_PATH") ;
		var strTemplatePath =wizard.FindSymbol ("TEMPLATES_PATH") ;
		var strUpperShortName =strShortName.toUpperCase () ;
		var strInterfaceName =wizard.FindSymbol ("INTERFACE_NAME") ;
		wizard.AddSymbol ("UPPER_SHORT_NAME", strUpperShortName) ;
		var strVIProgID =wizard.FindSymbol ("VERSION_INDEPENDENT_PROGID") ;
		wizard.AddSymbol ("PROGID", strVIProgID.substr (0, 37) + ".1") ;
		var bConnectionPoint =wizard.FindSymbol ("CONNECTION_POINTS") ;
 		var strClassName =wizard.FindSymbol ("CLASS_NAME") ;
		var strHeaderFile =wizard.FindSymbol ("HEADER_FILE") ;
		var strImplFile =wizard.FindSymbol ("IMPL_FILE") ;
		var strCoClass =wizard.FindSymbol ("COCLASS") ;
		var bAttributed =wizard.FindSymbol ("ATTRIBUTED") ;

		var strProjectRC =GetProjectFile (selProj, "RC", true, false) ;

		//----- Create necessary GUIDS
		CreateGUIDs () ;

		if ( !bAttributed ) {
			//----- Get LibName
			wizard.AddSymbol ("LIB_NAME", oCM.IDLLibraries (1).Name) ;
			//----- Get LibID
			var oUuid =oCM.IDLLibraries (1).Attributes.Find ("uuid") ;
			if ( oUuid )
				wizard.AddSymbol ("LIBID_REGISTRY_FORMAT", oUuid.Value) ;
			//----- Get typelib version
			var oVersion =oCM.IDLLibraries (1).Attributes.Find ("version") ;
			if ( oVersion ) {
				var aryMajorMinor =oVersion.Value.split ('.') ;
				for ( var nCntr =0 ; nCntr < aryMajorMinor.length ; nCntr++ ) {
					if ( nCntr == 0 )
						wizard.AddSymbol ("TYPELIB_VERSION_MAJOR", aryMajorMinor [nCntr]) ;
					else
						wizard.AddSymbol ("TYPELIB_VERSION_MINOR", aryMajorMinor [nCntr]) ;
				}
			}
			//----- Get AppID
			var strAppID =wizard.GetAppID () ;
			if ( strAppID.length > 0 ) {
				wizard.AddSymbol ("APPID_EXIST", true) ;
				wizard.AddSymbol ("APPID_REGISTRY_FORMAT", strAppID) ;
			}
			//----- Add RGS file resource
			var strRGSFile =GetUniqueFileName (strProjectPath, strShortName + ".rgs") ;
			var strRGSID ="IDR_" + strUpperShortName ;
			RenderAddTemplate (wizard, "object.rgs", strRGSFile, false, false) ;
			
			var oResHelper =wizard.ResourceHelper ;
			oResHelper.OpenResourceFile (strProjectRC) ;
			var strSymbolValue =oResHelper.AddResource (strRGSID, strProjectPath + strRGSFile, "REGISTRY") ;
			wizard.AddSymbol ("RGS_ID", strSymbolValue.split ("=").shift ()) ;
			oResHelper.CloseResourceFile () ;
			//----- Add connection point support
			if ( bConnectionPoint )
				RenderAddTemplate (wizard, "connpt.h", "_" + strInterfaceName + "Events_CP.h", selObj, false) ;
			//------ Render objco.idl and insert into strProject.idl
			AddCoclassFromFile (oCM, "objco.idl") ;
			//----- Render objint.idl and insert into strProject.idl
			//AddInterfaceFromFile (oCM, "objint.idl") ;
			selProj.Object.Save () ;
			SetMergeProxySymbol (selProj) ;
		}
		//------ Add header
		RenderAddTemplate (wizard, "object.h", strHeaderFile, selObj, true) ;
		//------ Add CPP
		RenderAddTemplate (wizard, "object.cpp", strImplFile, selObj, false) ;
		oCM.CommitTransaction () ;
		oCM.Classes.Find (strClassName).StartPoint.TryToShow (vsPaneShowTop) ;
	} catch ( e ) {
		if ( oCM )
			oCM.AbortTransaction () ;
		if ( e.description.length != 0 )
			SetErrorInfo (e) ;
		return (e.number) ;
	}
}

function CreateGUIDs () {
	try {
		//----- Create CLSID
		var strRawGUID =wizard.CreateGuid () ;
		var strFormattedGUID =wizard.FormatGuid (strRawGUID, 0) ;
		wizard.AddSymbol ("CLSID_REGISTRY_FORMAT", strFormattedGUID) ;
		//----- Create interface GUID
		strRawGUID =wizard.CreateGuid () ;
		strFormattedGUID =wizard.FormatGuid (strRawGUID, 0) ;
		wizard.AddSymbol ("INTERFACE_IID", strFormattedGUID) ;
		//------ Create connection point GUID
		var bConnectionPoint =wizard.FindSymbol ("CONNECTION_POINTS") ;
		if ( bConnectionPoint ) {
			strRawGUID =wizard.CreateGuid () ;
			strFormattedGUID =wizard.FormatGuid (strRawGUID, 0) ;
			wizard.AddSymbol ("CONNECTION_POINT_IID", strFormattedGUID) ;
		}
	} catch ( e ) {
		throw e ;
	}
}
