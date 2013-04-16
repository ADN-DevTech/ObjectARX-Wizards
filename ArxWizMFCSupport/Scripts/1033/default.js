//- Copyright (c) Autodesk, Inc. All rights reserved.
//- by Fenton Webb / Cyrille Fauvel - Autodesk Developer Technical Services

function OnFinish(selProj, selObj)
{
	var oCM;
	try
	{
		oCM	= selProj.CodeModel;

		var strClassName = wizard.FindSymbol("CLASS_NAME");

		var L_TransactionName_Text = "Add an ObjectARX MFC class ";
		oCM.StartTransaction(L_TransactionName_Text + strClassName);
		
		var strProjectPath		= wizard.FindSymbol("PROJECT_PATH");
		var strTemplatePath		= wizard.FindSymbol("TEMPLATES_PATH");
		var strIncludeHeader	= wizard.FindSymbol("INCLUDE_HEADER");
		var strHeaderFile		= wizard.FindSymbol("HEADER_FILE");
		var strImplFile			= wizard.FindSymbol("IMPL_FILE");
		var strDialogID			= wizard.FindSymbol("IDD_DIALOG");
		var strTemplateHeader	= wizard.FindSymbol("TEMPLATE_HEADER");
		var strTemplateImpl		= wizard.FindSymbol("TEMPLATE_IMPL");
		var strBaseClass		= wizard.FindSymbol("BASE_CLASS");

		var strProjectCPP		= GetProjectFile(selProj, "CPP", false, true);

		// child dialog stuff
		var strChildDlgNeeded = wizard.FindSymbol("CHILD_DIALOG_NEEDED");
		var strChildHeaderFile = wizard.FindSymbol("CHILDHEADER_FILE");
		var strChildImplFile  = wizard.FindSymbol("CHILDIMPL_FILE");		
		// child resource
		var strChildResourceNeeded = wizard.FindSymbol("CHILD_RESOURCE_NEEDED");

		var strProjectRC = GetProjectFile(selProj, "RC", true);
		var oResHelper = wizard.ResourceHelper;

		if (wizard.FindSymbol("CREATE_DIALOG"))
		{
			var strSymbolValue = "";
			oResHelper.OpenResourceFile(strProjectRC);

//wizard.OkCancelAlert (strDialogID);
//wizard.OkCancelAlert (strTemplatePath);
			
			// check to see if we need to create a child dialog
			if (strChildDlgNeeded == true || strChildResourceNeeded == true)
			{
//wizard.OkCancelAlert (strDialogID);
//wizard.OkCancelAlert (strTemplatePath);
			  // create a child dialog resource
				strSymbolValue = oResHelper.AddResource(strDialogID, strTemplatePath + "\\childDialog.rc", "DIALOG");
			}
			// else create a normal dialog resource
			else
			{
				strSymbolValue = oResHelper.AddResource(strDialogID, strTemplatePath + "\\dialog.rc", "DIALOG");
			}

			oResHelper.CloseResourceFile();			
			wizard.AddSymbol("IDD_DIALOG", strSymbolValue.split("=").shift());

			// check to see if we need to create a child dialog
			if (strChildDlgNeeded == true)
			{
			  // then we need to add the child dialog files
//wizard.OkCancelAlert (strChildHeaderFile);
//wizard.OkCancelAlert (strChildImplFile);
				RenderAddTemplate(wizard, "ChildDialog.h", strChildHeaderFile, selObj, true);
				RenderAddTemplate(wizard, "ChildDialog.cpp", strChildImplFile, selObj, false);
			}
		}

		// add the normal header and cpp files that are needed
//wizard.OkCancelAlert (strHeaderFile);
//wizard.OkCancelAlert (strImplFile);
		RenderAddTemplate(wizard, strTemplateHeader, strHeaderFile, selObj, true);
		RenderAddTemplate(wizard, strTemplateImpl, strImplFile, selObj, false);
		

		oCM.CommitTransaction();
				
//		oCM.Classes.Find(strClassName).StartPoint.TryToShow(vsPaneShowTop);

	}
	catch(e)
	{
		if (oCM)
			oCM.AbortTransaction();

		if (e.description.length != 0)
			SetErrorInfo(e);
		return e.number
	}
}
