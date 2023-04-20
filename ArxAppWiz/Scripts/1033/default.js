//- Copyright (c) Autodesk, Inc. All rights reserved.
//- by Cyrille Fauvel - Autodesk Developer Technical Services

//wizard.OkCancelAlert(""); return;
// config.InheritedPropertySheets = 'Fullpath\x.vsprops;';
// http://msdn.microsoft.com/en-us/library/aa291835(v=VS.71).aspx
// http://msdn.microsoft.com/en-us/library/microsoft.visualstudio.vswizard.vcwizctlclass_members.aspx

function OnFinish(selProj, selObj) {
  try {
    var strProjectPath = wizard.FindSymbol("PROJECT_PATH");
    var strProjectName = wizard.FindSymbol("PROJECT_NAME");
    wizard.AddSymbol("UPPER_CASE_PROJECT_NAME", strProjectName.toUpperCase());
    wizard.AddSymbol("SAFE_PROJECT_NAME", CreateSafeName(strProjectName));
    wizard.AddSymbol(
      "UPPER_CASE_SAFE_PROJECT_NAME",
      CreateSafeName(strProjectName.toUpperCase())
    );
    wizard.AddSymbol(
      "RC_FILE_NAME",
      CreateSafeRCFileName(strProjectName) + ".rc"
    );

    var bMfcExtDll = wizard.FindSymbol("MFC_EXT_SHARED");
    var bSharedMfc = wizard.FindSymbol("MFC_REG_SHARED") || bMfcExtDll;
    var bMfcSupport = wizard.FindSymbol("MFC_REG_STATIC") || bSharedMfc;
    if (bMfcSupport) wizard.AddSymbol("ARX_MFC_SUPPORT", "Dynamic");
    else wizard.AddSymbol("ARX_MFC_SUPPORT", "false");
    var bUseAtl = wizard.FindSymbol("ATL_COM_SERVER");
    if (bUseAtl) wizard.AddSymbol("ARX_ATL_SUPPORT", "Dynamic");
    else wizard.AddSymbol("ARX_ATL_SUPPORT", "false");

    var bArxAppType = wizard.FindSymbol("APP_ARX_TYPE");
    var bDbxAppType = wizard.FindSymbol("APP_DBX_TYPE");
    var bDotNetModule = wizard.FindSymbol("DOTNET_MODULE");
    if (bDotNetModule) {
      if (bArxAppType) wizard.AddSymbol("PRJ_TYPE_APP", "arxnet");
      else if (bDbxAppType) wizard.AddSymbol("PRJ_TYPE_APP", "dbxnet");
      else wizard.AddSymbol("PRJ_TYPE_APP", "crxnet");
      wizard.AddSymbol("ARX_CLR_SUPPORT", "true");
    } else {
      if (bArxAppType) wizard.AddSymbol("PRJ_TYPE_APP", "arx");
      else if (bDbxAppType) wizard.AddSymbol("PRJ_TYPE_APP", "dbx");
      else wizard.AddSymbol("PRJ_TYPE_APP", "crx");
      wizard.AddSymbol("ARX_CLR_SUPPORT", "false");
    }
    //TOCHANGE Must change for every release.
    CopyPropsFile("Autodesk.arx-2024.props", strProjectName);
    CopyPropsFile("Autodesk.arx-2024-net.props", strProjectName);
    //TOCHANGE
    CopyPropsFile("crx.props", strProjectName);

    //selProj =CreateProject (strProjectName, strProjectPath) ; //- Use the default Win32 only project template from Visual Studio
    var strProjTemplate = RenderPrjToTemporaryFile();
    selProj = CreateArxProject(strProjectName, strProjectPath, strProjTemplate);
    SetupFilters(selProj);
    AddFilesToNewProjectWithInfFile(selProj, strProjectName);
    selProj.Object.Save();
  } catch (e) {
    if (e.description.length != 0) SetErrorInfo(e);
    return e.number;
  }
}

//-----------------------------------------------------------------------------
function CreateArxProject(strProjectName, strProjectPath, strProjTemplate) {
  try {
    /* var strProjTemplatePath =wizard.FindSymbol ("ABSOLUTE_PATH") ;
    var strProjTemplate =strProjTemplatePath + "\\Templates\\1033\\x64win32.vcxproj" ;
 */
    var Solution = dte.Solution;
    var strSolutionName = "";
    if (wizard.FindSymbol("CLOSE_SOLUTION")) {
      Solution.Close();
      strSolutionName = wizard.FindSymbol("VS_SOLUTION_NAME");
      if (strSolutionName.length) {
        var strSolutionPath = strProjectPath.substr(
          0,
          strProjectPath.length - strProjectName.length
        );
        Solution.Create(strSolutionPath, strSolutionName);
      }
    }

    var strProjectNameWithExt = strProjectName + ".vcxproj";
    var oTarget = wizard.FindSymbol("TARGET");
    var oProj;
    if (wizard.FindSymbol("WIZARD_TYPE") == vsWizardAddSubProject) {
      // vsWizardAddSubProject
      var prjItem = oTarget.AddFromTemplate(
        strProjTemplate,
        strProjectPath + "\\" + strProjectNameWithExt
      );
      oProj = prjItem.SubProject;
    } else {
      oProj = oTarget.AddFromTemplate(
        strProjTemplate,
        strProjectPath,
        strProjectNameWithExt
      );
    }
    return oProj;
  } catch (e) {
    throw e;
  }
}

//-----------------------------------------------------------------------------
function GetTargetName(strName, strProjectName) {
  try {
    //----- Set the name of the rendered file based on the template filename
    var strTarget = strName;
    if (strName.substr(0, 4) == "root")
      strTarget = strProjectName + strName.substr(4, strName.length - 4);
    return strTarget;
  } catch (e) {
    throw e;
  }
}

function SetFileProperties(projfile, strName) { }

//-----------------------------------------------------------------------------
function RenderPrjToTemporaryFile() {
  var strProjTemplatePath = wizard.FindSymbol("ABSOLUTE_PATH");
  var strProjTemplate =
    strProjTemplatePath + "\\Templates\\1033\\x64win32.vcxproj";

  var TemporaryFolder = 2;
  var oFSO = new ActiveXObject("Scripting.FileSystemObject");
  var oFolder = oFSO.GetSpecialFolder(TemporaryFolder);
  var strTempFile =
    oFSO.GetAbsolutePathName(oFolder.Path) +
    "\\" +
    oFSO.GetTempName() +
    ".vcxproj";
  var strTempFileContents = wizard.RenderTemplateToString(strProjTemplate);
  var oStream;
  oStream = oFSO.CreateTextFile(strTempFile, true, false /*ANSI*/);
  oStream.Write(strTempFileContents);
  oStream.Close();
  return strTempFile;
}

//-----------------------------------------------------------------------------
function CopyPropsFile(strName, strProjectName) {
  var strTemplatePath = wizard.FindSymbol("TEMPLATES_PATH");
  var strTarget = GetTargetName(strName, strProjectName);
  var strTemplate = strTemplatePath + "\\" + strName;
  wizard.RenderTemplate(strTemplate, strTarget, true, false);
}
