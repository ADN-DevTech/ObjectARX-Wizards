// (C) Copyright 2005-2022 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "[!output HEADER_FILE]"

//-----------------------------------------------------------------------------
[!output CLASS_NAME]::[!output CLASS_NAME] () : AcEdJig (),
	mCurrentInputLevel(0), mpEntity(NULL)
{
}

[!output CLASS_NAME]::~[!output CLASS_NAME] () {
}

//-----------------------------------------------------------------------------
AcEdJig::DragStatus [!output CLASS_NAME]::startJig ([!output ARX_OBJECTNAME] *pEntity) {
	//- Store the new entity pointer
	mpEntity =pEntity ;
	//- Setup each input prompt
	AcString inputPrompts [[!output NUMBER_OF_INPUTS]] ={
		[!output INPUT_PROMPTS]
	} ;
	//- Setup kwords for each input
	AcString kwords [[!output NUMBER_OF_INPUTS]] ={
		[!output INPUT_KEYWORDS]
	} ;

	bool appendOk =true ;
	AcEdJig::DragStatus status =AcEdJig::kNull ;
	//- Loop the number of inputs
	for ( mCurrentInputLevel =0 ; mCurrentInputLevel < [!output NUMBER_OF_INPUTS] ; mCurrentInputLevel++ ) {
		//- Add a new input point to the list of input points
		mInputPoints.append (AcGePoint3d ()) ;
		//- Set the input prompt
		setDispPrompt (inputPrompts [mCurrentInputLevel]) ;
		//- Setup the keywords required
		setKeywordList (kwords [mCurrentInputLevel]) ;

		bool quit =false ;
		//- Lets now do the input
		status =drag () ;
		if ( status != kNormal ) {
			//- If it's a keyword
			switch ( status ) {
				case kCancel: 
				case kNull:
					quit =true ;
					break ;

				case kKW1:
				case kKW2:
				case kKW3:
				case kKW4:
				case kKW5:
				case kKW6:
				case kKW7:
				case kKW8:
				case kKW9:
					//- Do something

					break ;
		  }
		} else {
			appendOk =true ;
		}

		//- If to finish
		if ( quit )
			break ;
	}

	//- If the input went well
	if ( appendOk )
		//- Append to the database
		append () ;
	else
		//- Clean up
		delete mpEntity  ;

	return (status) ;
}

//-----------------------------------------------------------------------------
//- Input sampler
AcEdJig::DragStatus [!output CLASS_NAME]::sampler () {
	//- Setup the user input controls for each input
	AcEdJig::UserInputControls userInputControls [[!output NUMBER_OF_INPUTS]] ={
		[!output INPUT_USERCTRLS]
	} ;
	//- Setup the cursor type for each input
	AcEdJig::CursorType cursorType [[!output NUMBER_OF_INPUTS]] ={
		[!output INPUT_CURSORTYPES]
	} ;
	//- Setup the user input controls for each sample
	setUserInputControls (userInputControls [mCurrentInputLevel]) ;
	setSpecialCursorType (cursorType [mCurrentInputLevel]) ;

	AcEdJig::DragStatus status =AcEdJig::kCancel ;
	//- Check the current input number to see which input to do
	switch ( mCurrentInputLevel+1 ) {
		[!output SAMPLER_SWITCH]
		default:
			break ;
	}
	return (status) ;
}

//-----------------------------------------------------------------------------
//- Jigged entity update
Adesk::Boolean [!output CLASS_NAME]::update () {
	//- Check the current input number to see which update to do
	switch ( mCurrentInputLevel+1 ) {
		[!output UPDATE_SWITCH]
		default:
			break ;
	}

	return (updateDimData ()) ;
}

//-----------------------------------------------------------------------------
//- Jigged entity pointer return
AcDbEntity *[!output CLASS_NAME]::entity () const {
	return ((AcDbEntity *)mpEntity) ;
}

//-----------------------------------------------------------------------------
//- Dynamic dimension data setup
AcDbDimDataPtrArray *[!output CLASS_NAME]::dimData (const double dimScale) {

	/* SAMPLE CODE:
	AcDbAlignedDimension *dim =new AcDbAlignedDimension () ;
	dim->setDatabaseDefaults () ;
	dim->setNormal (AcGeVector3d::kZAxis) ;
	dim->setElevation (0.0) ;
	dim->setHorizontalRotation (0.0) ;
	dim->setXLine1Point (m_originPoint) ;
	dim->setXLine2Point (m_lastPoint) ;
	//- Get the dimPoint, first the midpoint
	AcGePoint3d dimPoint =m_originPoint + ((m_lastPoint - m_originPoint) / 2.0) ;
	//- Then the offset
	dim->setDimLinePoint (dimPoint) ;
	dim->setDimtad (1) ;

	AcDbDimData *dimData = new AcDbDimData (dim) ;
	//AppData *appData =new AppData (1, dimScale) ;
	//dimData.setAppData (appData) ;
	dimData->setDimFocal (true) ;
	dimData->setDimHideIfValueIsZero (true) ;

	//- Check to see if it is required
	if ( getDynDimensionRequired (m_inputNumber) )
		dimData->setDimInvisible (false) ;
	else
		dimData->setDimInvisible (true) ;

	//- Make sure it is editable TODO: 
	dimData->setDimEditable (true) ;
	mDimData.append (dimData) ;

	return (&mDimData) ;
	*/
	return (NULL) ;
}

//-----------------------------------------------------------------------------
//- Dynamic dimension data update
Acad::ErrorStatus [!output CLASS_NAME]::setDimValue (const AcDbDimData *pDimData, const double dimValue) {
	Acad::ErrorStatus es =Acad::eOk ;

	/* SAMPLE CODE:
	//- Convert the const pointer to non const
	AcDbDimData *dimDataNC =const_cast<AcDbDimData *>(pDimData) ;
	int inputNumber =-1 ;
	//- Find the dim data being passed so we can determine the input number
	if ( mDimData.find (dimDataNC, inputNumber) ) {
		//- Now get the dimension
		AcDbDimension *pDim =(AcDbDimension *)dimDataNC->dimension () ;
		//- Check it's the type of dimension we want
		AcDbAlignedDimension *pAlnDim =AcDbAlignedDimension::cast (pDim) ;
		//- If ok
		if ( pAlnDim ) {
			//- Extract the dimensions as they are now
			AcGePoint3d dimStart =pAlnDim->xLine1Point () ;
			AcGePoint3d dimEnd =pAlnDim->xLine2Point () ;
			//- Lets get the new point entered by the user 
			AcGePoint3d dimEndNew =dimStart + (dimEnd - dimStart).normalize () * dimValue ;
			//- Finally set the end dim point
			pAlnDim->setXLine2Point (dimEndNew) ;
			//- Now update the jig data to reflect the dynamic dimension input
			mInputPoints [mCurrentInputLevel] =dimEndNew ;
		}
	}*/
	return (es) ;
}

//-----------------------------------------------------------------------------
//- Various helper functions
//- Dynamic dimdata update function
Adesk::Boolean [!output CLASS_NAME]::updateDimData () {
	//- Check the dim data store for validity
	if ( mDimData.length () <= 0 )
		return (true) ;

	/* SAMPLE CODE :
	//- Extract the individual dimData
	AcDbDimData *dimData =mDimData [m_inputNumber] ;
	//- Now get the dimension
	AcDbDimension *pDim =(AcDbDimension *)dimData->dimension () ;
	//- Check it's the type of dimension we want
	AcDbAlignedDimension *pAlnDim =AcDbAlignedDimension::cast (pDim) ;
	//- If ok
	if ( pAlnDim ) {
		//- Check to see if it is required
		if ( getDynDimensionRequired (m_inputNumber) )
			dimData->setDimInvisible (false) ;
		else
			dimData->setDimInvisible (true) ;
		pAlnDim->setXLine1Point (m_originPoint) ;
		pAlnDim->setXLine2Point (m_lastPoint) ;
		//- Get the dimPoint, first the midpoint
		AcGePoint3d dimPoint =m_originPoint + ((m_lastPoint - m_originPoint) / 2.0) ;
		//- Then the offset
		pAlnDim->setDimLinePoint (dimPoint) ;
	} */
	return (true) ;
}

//-----------------------------------------------------------------------------
//- Std input to get a point with no rubber band
AcEdJig::DragStatus [!output CLASS_NAME]::GetStartPoint () {
	AcGePoint3d newPnt ;
	//- Get the point 
	AcEdJig::DragStatus status =acquirePoint (newPnt) ;
	//- If valid input
	if ( status == AcEdJig::kNormal ) {
		//- If there is no difference
		if ( newPnt.isEqualTo (mInputPoints [mCurrentInputLevel]) )
			return (AcEdJig::kNoChange) ;
		//- Otherwise update the point
		mInputPoints [mCurrentInputLevel] =newPnt ;
	}
	return (status) ;
}

//-----------------------------------------------------------------------------
//- Std input to get a point with rubber band from point
AcEdJig::DragStatus [!output CLASS_NAME]::GetNextPoint () {
	AcGePoint3d oldPnt =mInputPoints [mCurrentInputLevel] ;
	AcGePoint3d newPnt ;
	//- Get the point 
	AcEdJig::DragStatus status =acquirePoint (newPnt, oldPnt) ;
	//- If valid input
	if ( status == AcEdJig::kNormal ) {
		//- If there is no difference
		if ( newPnt.isEqualTo (mInputPoints [mCurrentInputLevel]) )
			return (AcEdJig::kNoChange) ;
		//- Otherwise update the point
		mInputPoints [mCurrentInputLevel] =newPnt ;
	}
	return (status) ;
}
