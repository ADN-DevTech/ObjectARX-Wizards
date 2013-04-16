//- Copyright (c) Autodesk, Inc. All rights reserved.
//- by Fenton Webb - Autodesk Developer Technical Services

//- Script for ObjectARX Custom Object .NET Wrapper

function OnFinish (selProj, selObj) {
	var oCM ;
	try {
		oCM	=selProj.CodeModel ;

		var strClassName =wizard.FindSymbol ("MANAGED_WRAPPER_NAME") ;		
		var L_TransactionName_Text ="Add an ObjectARX .NET Wrapper class " ;
		oCM.StartTransaction (L_TransactionName_Text + strClassName) ;

		//- Add the normal header and cpp files that are needed
		var strHeaderFile =wizard.FindSymbol ("HEADER_FILE") ;
		var strImplFile =wizard.FindSymbol ("IMPL_FILE") ;
		RenderAddTemplate (wizard, "managedWrapper.h", strHeaderFile, selObj, true) ;
		RenderAddTemplate (wizard, "managedWrapper.cpp", strImplFile, selObj, false) ;
		
		oCM.CommitTransaction () ;				
		//oCM.Classes.Find (strClassName).StartPoint.TryToShow (vsPaneShowTop) ;

	} catch ( e ) {
		if ( oCM )
			oCM.AbortTransaction () ;
		if ( e.description.length != 0 )
			SetErrorInfo (e) ;
		return (e.number) ;
	}
}
