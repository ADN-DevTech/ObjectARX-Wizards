// (C) Copyright 2002-2007 by Autodesk, Inc. 
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
//----- [!output IMPL_FILE] : Implementation of [!output CLASS_NAME]
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "[!output HEADER_FILE]"

//----- [!output CLASS_NAME]
[!if !ATTRIBUTED]
[!if SUPPORT_ERROR_INFO]
//-----------------------------------------------------------------------------
STDMETHODIMP [!output CLASS_NAME]::InterfaceSupportsErrorInfo (REFIID riid) {
	static const IID * arr [] ={
		&IID_[!output INTERFACE_NAME]
	} ;

	for ( int i =0 ; i < sizeof (arr) / sizeof (arr [0]) ; i++ ) {
		if ( InlineIsEqualGUID (*arr [i], riid) )
			return (S_OK) ;
	}
	return (S_FALSE) ;
}
[!endif]
[!endif]

//-----------------------------------------------------------------------------
//IAcadBaseObjectImpl
HRESULT [!output CLASS_NAME]::CreateNewObject (AcDbObjectId &objId, AcDbObjectId &ownerId, TCHAR *keyName) {
	try {
		HRESULT hr ;
		if ( FAILED(hr =CreateObject (ownerId, keyName)) )
			throw hr ;
		if ( FAILED(hr =AddToDb (objId, ownerId, keyName)) )
			throw hr ;
	} catch( HRESULT hr ) {
		return (hr) ;
	}
	return (S_OK) ;
}

//-----------------------------------------------------------------------------
//IAcadBaseObject2Impl
STDMETHODIMP [!output CLASS_NAME]::ForceDbResident (VARIANT_BOOL *forceDbResident) {
	if ( forceDbResident == NULL )
		return (E_POINTER) ;
	//----- Return ACAX_VARIANT_TRUE if the object must be database resident to be functional
	*forceDbResident =ACAX_VARIANT_FALSE ;
	return (S_OK) ;
}

STDMETHODIMP [!output CLASS_NAME]::CreateObject (AcDbObjectId ownerId /*=AcDbObjectId::kNull*/, TCHAR *keyName /*=NULL*/) {
	try {
		Acad::ErrorStatus es ;
		AcDbObjectPointer<[!output ARX_CLASS_NAME]> obj ;
		if ( (es =obj.create ()) != Acad::eOk )
			throw es ;

[!if ACAD_ENTITY_INTERFACE]
		obj->setDatabaseDefaults (ownerId.database ()) ;

[!endif]
		[!output ARX_CLASS_NAME] *pTmp =NULL ;
		obj.release (pTmp) ;

		SetObject ((AcDbObject *&)pTmp) ;
	} catch ( const Acad::ErrorStatus ) {
		return (Error (L"Failed to create [!output ARX_CLASS_NAME]", IID_[!output INTERFACE_NAME], E_FAIL)) ;
	}
	return (S_OK) ;
}

STDMETHODIMP [!output CLASS_NAME]::AddToDb (AcDbObjectId &objId, AcDbObjectId ownerId /*=AcDbObjectId::kNull*/, TCHAR *keyName /*=NULL*/) {
	try {
		AcAxDocLock docLock (ownerId) ;

		Acad::ErrorStatus es ;
		AcAxObjectRefPtr<[!output ARX_CLASS_NAME]> obj (&m_objRef, AcDb::kForRead) ;

[!if ACAD_ENTITY_INTERFACE]
		//----- Entities can be owned by block table records only
		AcDbBlockTableRecordPointer pBlockTableRecord (ownerId, AcDb::kForWrite, true) ;
		if ( (es =pBlockTableRecord.openStatus ()) != Acad::eOk )
			throw es ;

		if ( (es =pBlockTableRecord->appendAcDbEntity (objId, obj.object ())) != Acad::eOk )
			throw es ;
[!else]
		//----- Non-entities cannot be owned by block table record, but are
		//----- usually owned by dictionaries. If this is not your case, please
		//----- change the code below.
		AcDbDictionaryPointer pDictionary (ownerId, AcDb::kForWrite, true) ;
		if ( (es =pDictionary.openStatus ()) != Acad::eOk )
			throw es ;

		if ( (es =pDictionary->setAt (keyName, obj.object (), objId)) != Acad::eOk )
			throw es ;
[!endif]
	} catch( const Acad::ErrorStatus ) {
		return (Error(L"Failed to add [!output ARX_CLASS_NAME] to database", IID_[!output INTERFACE_NAME], E_FAIL)) ;
	}
	return (SetObjectId (objId)) ;
}

[!if OPM_PROPERTY_EXPANDER]
//IOPMPropertyExpander
STDMETHODIMP [!output CLASS_NAME]::GetElementValue (DISPID dispID, DWORD dwCookie, VARIANT *pVarOut) {
	if ( pVarOut == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there 
	return (E_NOTIMPL) ;
}

STDMETHODIMP [!output CLASS_NAME]::SetElementValue (DISPID dispID, DWORD dwCookie, VARIANT VarIn) {
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there 
	return (E_NOTIMPL) ;
}

STDMETHODIMP [!output CLASS_NAME]::GetElementStrings (DISPID dispID, OPMLPOLESTR __RPC_FAR *pCaStringsOut, OPMDWORD __RPC_FAR *pCaCookiesOut) {
	if ( pCaStringsOut == NULL || pCaCookiesOut == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there 
	return (E_NOTIMPL) ;
}

STDMETHODIMP [!output CLASS_NAME]::GetElementGrouping (DISPID dispID, short *groupingNumber) {
	if ( groupingNumber == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there 
	return (E_NOTIMPL) ;
}

STDMETHODIMP [!output CLASS_NAME]::GetGroupCount (DISPID dispID, long *nGroupCnt) {
	if ( nGroupCnt == NULL )
		return (E_POINTER) ;
	//----- Add your code here.

	//return (S_OK) ; //----- If you do anything in there 
	return (E_NOTIMPL) ;
}

[!endif]

