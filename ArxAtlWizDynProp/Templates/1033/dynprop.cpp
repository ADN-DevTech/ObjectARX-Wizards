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
STDMETHODIMP [!output CLASS_NAME]::InterfaceSupportsErrorInfo(REFIID riid) {
	static const IID* arr [] ={
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

//----- IDynamicProperty
STDMETHODIMP [!output CLASS_NAME]::GetGUID (GUID *pPropGUID) {
	if ( pPropGUID == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the line below)
	memcpy (pPropGUID, &CLSID_[!output COCLASS], sizeof(GUID)) ;

	return (S_OK) ;
}

STDMETHODIMP [!output CLASS_NAME]::GetDisplayName (BSTR *pBstrName) {
	if ( pBstrName == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the line below)
	*pBstrName =::SysAllocString (L"My property ([!output CLASS_NAME])") ;

	return (S_OK) ;
}

STDMETHODIMP [!output CLASS_NAME]::IsPropertyEnabled (IUnknown *pUnk, BOOL *pbEnabled) {
	if ( pUnk == NULL )
		return (E_INVALIDARG) ;
	if ( pbEnabled == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the line below)
	*pbEnabled =TRUE ;

	return (S_OK) ;
}

STDMETHODIMP [!output CLASS_NAME]::IsPropertyReadOnly (BOOL *pbReadOnly) {
	if ( pbReadOnly == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the line below)
	*pbReadOnly =FALSE ;

	return (S_OK) ;
}

STDMETHODIMP [!output CLASS_NAME]::GetDescription (BSTR *pBstrName) {
	if ( pBstrName == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the line below)
	*pBstrName =::SysAllocString (L"Description for My Property ([!output CLASS_NAME])") ;

	return (S_OK) ;
}

STDMETHODIMP [!output CLASS_NAME]::GetCurrentValueName (BSTR *pBstrName) {
	if ( pBstrName == NULL )
		return (E_POINTER) ;
	// TODO: add your code here

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

STDMETHODIMP [!output CLASS_NAME]::GetCurrentValueType (VARTYPE *pVarType) {
	if ( pVarType == NULL )
		return (E_POINTER) ;
[!if OPM_DYNENUM]
	//----- Enumerated property
	*pVarType =VT_USERDEFINED ;
[!else]
	// TODO: add your code here (and comment the line below)
	*pVarType =VT_I4 ; //----- An integer
[!endif]

	return (S_OK) ;
}

STDMETHODIMP [!output CLASS_NAME]::GetCurrentValueData (IUnknown *pUnk, VARIANT *pVarData) {
	if ( pUnk == NULL )
		return (E_INVALIDARG) ;
	if ( pVarData == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the 3 lines below)
	::VariantInit (pVarData) ;
	V_VT(pVarData) =VT_I4 ;
	V_I4(pVarData) =0 ; //---- Always return 0

	return (S_OK) ;
}

STDMETHODIMP [!output CLASS_NAME]::SetCurrentValueData (IUnknown *pUnk, const VARIANT varData) {
	if ( pUnk == NULL )
		return (E_INVALIDARG) ;
	// TODO: add your code here

[!if OPM_DYNENUM]
	//----- In case of an enum property, call the following to update the physical combobox
	m_pNotify->OnChanged (this) ;
[!endif]
	return (S_OK) ;
}

STDMETHODIMP [!output CLASS_NAME]::Connect (IDynamicPropertyNotify2 *pSink) {
	if ( pSink == NULL )
		return (E_POINTER) ;
	m_pNotify =pSink ;
	m_pNotify->AddRef () ;
	return (S_OK) ;
}

STDMETHODIMP [!output CLASS_NAME]::Disconnect () {
	if ( m_pNotify ) {
		m_pNotify->Release () ;
		m_pNotify= NULL ;
	}
	return (S_OK) ;
}

[!if OPM_DYNENUM]
//----- IDynamicEnumProperty
STDMETHODIMP [!output CLASS_NAME]::GetNumPropertyValues (LONG *pNumValues) {
	if ( pNumValues == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the line below)
	*pNumValues =3 ; //----- Have 3 items in the drop down

	return (S_OK) ;
}

STDMETHODIMP [!output CLASS_NAME]::GetPropValueName (LONG index, BSTR *pBstrValueName) {
	if ( pBstrValueName == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the 2 lines below)
	WCHAR buffer [5] ; //----- This should be enough
	*pBstrValueName =::SysAllocString (_itow (index, buffer, 10)) ; //----- Show simply the numbers in the combo

	return (S_OK) ;
}

STDMETHODIMP [!output CLASS_NAME]::GetPropValueData (LONG index, VARIANT* pValue) {
	if ( pValue == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the 3 lines below)
	::VariantInit (pValue) ;
	V_VT(pValue) =VT_I4 ;
	V_I4(pValue) =index ; //----- The index IS the value in this case

	return (S_OK) ;
}
[!endif]

[!if OPM_DYNDLG]
//----- IDynamicDialogProperty
STDMETHODIMP [!output CLASS_NAME]::GetCustomDialogProc (OPMDIALOGPROC *pDialogProc) {
	if ( pDialogProc == NULL )
		return (E_POINTER) ;
	// TODO: add your code here

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}

STDMETHODIMP [!output CLASS_NAME]::GetMacroName (BSTR *pBstrName) {
	if ( pBstrName == NULL )
		return (E_POINTER) ;
	// TODO: add your code here

	//return (S_OK) ; //----- If you do anything in there
	return (E_NOTIMPL) ;
}
[!endif]

[!if OPM_CAT]
//----- ICategorizePropertes
STDMETHODIMP [!output CLASS_NAME]::MapPropertyToCategory (DISPID dispid, PROPCAT *pPropCat) {
	if ( pPropCat == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the line below)
	*pPropCat =0 ;

	return (S_OK) ;
}

STDMETHODIMP [!output CLASS_NAME]::GetCategoryName (PROPCAT propcat, LCID lcid, BSTR *pBstrName) {
	if ( pBstrName == NULL )
		return (E_POINTER) ;
	// TODO: add your code here (and comment the 3 lines below)
	if ( propcat != 0 )
		return (E_INVALIDARG) ;
	*pBstrName =::SysAllocString (L"My Category") ;

	return (S_OK) ;
}
[!endif]
