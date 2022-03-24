// (C) Copyright 2002-2022 by Autodesk, Inc. 
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
//----- [!output IMPL_FILE] : Implementation of [!output CLASS_NAME_ROOT]
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "[!output HEADER_FILE]"

//-----------------------------------------------------------------------------
ACRX_CONS_DEFINE_MEMBERS([!output CLASS_NAME_ROOT], [!output BASE_CLASS], 1)

//-----------------------------------------------------------------------------
[!output CLASS_NAME_ROOT]::[!output CLASS_NAME_ROOT] (AcApDocument *pDoc) : [!output BASE_CLASS](), mpDocument(pDoc) {
	if ( pDoc )
		pDoc->inputPointManager ()->registerPointFilter (this) ;
}

//-----------------------------------------------------------------------------
[!output CLASS_NAME_ROOT]::~[!output CLASS_NAME_ROOT] () {
	Detach () ;
}

//-----------------------------------------------------------------------------
void [!output CLASS_NAME_ROOT]::Attach (AcApDocument *pDoc) {
	Detach () ;
	if ( mpDocument == NULL ) {
		if ( (mpDocument =pDoc) != NULL )
			pDoc->inputPointManager ()->registerPointFilter (this) ;
	}
}

void [!output CLASS_NAME_ROOT]::Detach () {
	if ( mpDocument ) {
		mpDocument->inputPointManager ()->revokePointFilter () ;
		mpDocument =NULL ;
	}
}

AcApDocument *[!output CLASS_NAME_ROOT]::Subject () const {
	return (mpDocument) ;
}

bool [!output CLASS_NAME_ROOT]::IsAttached () const {
	return (mpDocument != NULL) ;
}

//-----------------------------------------------------------------------------
Acad::ErrorStatus [!output CLASS_NAME_ROOT]::processInputPoint (
	bool &changedPoint,
	AcGePoint3d &newPoint,
	bool &displayOsnapGlyph,
	bool &changedTooltipStr,
	ACHAR *&newTooltipString,
	bool &retry,
	AcGiViewportDraw *drawContext,
	AcApDocument *document,
	bool pointComputed,
	int history,
	const AcGePoint3d &lastPoint,
	const AcGePoint3d &rawPoint,
	const AcGePoint3d &grippedPoint,
	const AcGePoint3d &cartesianSnappedPoint,
	const AcGePoint3d &osnappedPoint,
	AcDb::OsnapMask osnapMask,
	const AcArray<AcDbCustomOsnapMode *> &customOsnapModes,
	AcDb::OsnapMask osnapOverrides,
	const AcArray<AcDbCustomOsnapMode *> &customOsnapOverrides,
	const AcArray<AcDbObjectId> &pickedEntities,
	const AcArray<AcDbObjectIdArray, AcArrayObjectCopyReallocator<AcDbObjectIdArray> > &nestedPickedEntities,
	const AcArray<Adesk::GsMarker> &gsSelectionMark,
	const AcArray<AcDbObjectId> &keyPointEntities,
	const AcArray<AcDbObjectIdArray, AcArrayObjectCopyReallocator<AcDbObjectIdArray> > &nestedKeyPointEntities,
	const AcArray<Adesk::GsMarker> &keyPointGsSelectionMark,
	const AcArray<AcGeCurve3d *> &alignmentPaths,
	const AcGePoint3d &computedPoint,
	const ACHAR *tooltipString
) {
	changedPoint =false ;

	return (Acad::eOk) ;
}

