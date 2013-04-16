//- Copyright (c) Autodesk, Inc. All rights reserved.
//- by Cyrille Fauvel - Autodesk Developer Technical Services

function OnFinish (selProj, selObj) {
	var oCM ;
	try {
		oCM	=selProj.CodeModel ;

		var strClassName =wizard.FindSymbol ("CLASS_NAME") ;		
		var L_TransactionName_Text ="Add an ObjectARX Jig Class " ;
		oCM.StartTransaction (L_TransactionName_Text + strClassName) ;

		var strProjectName =wizard.FindSymbol ("PROJECT_NAME") ;
		wizard.AddSymbol ("SAFE_PROJECT_NAME", CreateSafeName (strProjectName)) ;
		var szUprProjectName =CreateSafeName (strProjectName.toUpperCase ()) ;
		wizard.AddSymbol ("UPPER_CASE_SAFE_PROJECT_NAME", szUprProjectName) ;

		var nbSt =wizard.FindSymbol ("NUMBER_OF_INPUTS") ;
		var nb =parseInt (nbSt) ;
		if ( nb < 1 ) nb =1 ; //- Make sure we have at least one entry
		if ( nb > 20 ) nb =20 ; //- Let's keep something reasonnable
		
		var inputPrompts ='"\\nPick point"' ;
		var kwords ='""' ;
		var userInputControls ='/*AcEdJig::UserInputControls::*/(AcEdJig::UserInputControls)0' ;
		var cursorTypes ='/*AcEdJig::CursorType::*/(AcEdJig::CursorType)0' ;
		var samplerSwitch ='case 1:\n\t\t\t// TODO : get an input here\n\t\t\t//status =GetStartPoint () ;\n\t\t\tbreak ;\n' ;
		var updateSwitch ='case 1:\n\t\t\t// TODO : update your entity for this input\n\t\t\t//mpEntity->setCenter (mInputPoints [mCurrentInputLevel]) ;\n\t\t\tbreak ;\n' ;

		for ( var j =1 ; j < nb ; j++ ) {
			inputPrompts +=',\n\t\t"\\nPick point"' ;
			kwords +=',\n\t\t""' ;
			userInputControls +=',\n\t\t/*AcEdJig::UserInputControls::*/(AcEdJig::UserInputControls)0' ;
			cursorTypes +=',\n\t\t/*AcEdJig::CursorType::*/(AcEdJig::CursorType)0' ;
			samplerSwitch +='\t\tcase ' + (j + 1) + ':\n\t\t\t// TODO : get an input here\n\t\t\t//status =GetStartPoint () ;\n\t\t\tbreak ;\n' ;
			updateSwitch +='\t\tcase ' + (j + 1) + ':\n\t\t\t// TODO : update your entity for this input\n\t\t\t//mpEntity->setCenter (mInputPoints [mCurrentInputLevel]) ;\n\t\t\tbreak ;\n' ;
		}

		wizard.AddSymbol ("INPUT_PROMPTS", inputPrompts) ;
		wizard.AddSymbol ("INPUT_KEYWORDS", kwords) ;
		wizard.AddSymbol ("INPUT_USERCTRLS", userInputControls) ;
		wizard.AddSymbol ("INPUT_CURSORTYPES", cursorTypes) ;
		wizard.AddSymbol ("SAMPLER_SWITCH", samplerSwitch) ;
		wizard.AddSymbol ("UPDATE_SWITCH", updateSwitch) ;

		//- Add the normal header and cpp files that are needed
		var strHeaderFile =wizard.FindSymbol ("HEADER_FILE") ;
		var strImplFile =wizard.FindSymbol ("IMPL_FILE") ;
		RenderAddTemplate (wizard, "Jig.h", strHeaderFile, selObj, true) ;
		RenderAddTemplate (wizard, "Jig.cpp", strImplFile, selObj, false) ;
		
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
