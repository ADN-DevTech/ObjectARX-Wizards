// (C) Copyright 1990-2002 by Autodesk, Inc. 
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
[!output CLASS_NAME_ROOT]::[!output CLASS_NAME_ROOT] (AcRxClass *pCls) : [!output BASE_CLASS] () {
	mpCls =NULL ;
	if ( pCls != NULL ) {
		mpCls =pCls ;
		ACRX_PROTOCOL_REACTOR_LIST_AT(mpCls, [!output CLASS_NAME_ROOT]::desc ())->addReactor (this) ;
	}
}

//-----------------------------------------------------------------------------
[!output CLASS_NAME_ROOT]::~[!output CLASS_NAME_ROOT] () {
	if ( mpCls != NULL ) {
		ACRX_PROTOCOL_REACTOR_LIST_AT(mpCls, [!output CLASS_NAME_ROOT]::desc ())->removeReactor (this) ;
	}

}

//-----------------------------------------------------------------------------
Acad::ErrorStatus [!output CLASS_NAME_ROOT]::getInsertionPoints (
	const AcDbBlockTableRecord *pBlock,
	AcGePoint3dArray &insPts,
	AcGeVector3dArray &alignmentDirections
) {
	return (Acad::eOk) ;
}

