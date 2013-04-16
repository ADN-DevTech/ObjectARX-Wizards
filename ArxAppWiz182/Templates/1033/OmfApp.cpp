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
//----- [!output SAFE_PROJECT_NAME]App.cpp : Defines the initialization routines for the DLL.
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "[!output SAFE_PROJECT_NAME]App.h"

//-----------------------------------------------------------------------------
C[!output SAFE_PROJECT_NAME]App *pThisOmfApp =NULL ;
extern AFX_EXTENSION_MODULE [!output RDS_SYMB][!output SAFE_PROJECT_NAME]DLL ;
HINSTANCE _hdllInstance =NULL ;

//-----------------------------------------------------------------------------
[!if APP_ARX_TYPE]
ACRX_NO_CONS_DEFINE_MEMBERS(C[!output SAFE_PROJECT_NAME]App, AecAppArx)
AEC_CLASS_DECORATOR(C[!output SAFE_PROJECT_NAME]App, AecAppArx, [!output RDS_SYMB][!output SAFE_PROJECT_NAME], -1, -1)
[!else]
ACRX_NO_CONS_DEFINE_MEMBERS(C[!output SAFE_PROJECT_NAME]App, AecAppDbx)
AEC_CLASS_DECORATOR(C[!output SAFE_PROJECT_NAME]App, AecAppDbx, [!output RDS_SYMB][!output SAFE_PROJECT_NAME], -1, -1)
[!endif]

//-----------------------------------------------------------------------------
C[!output SAFE_PROJECT_NAME]App::C[!output SAFE_PROJECT_NAME]App ()
[!if APP_ARX_TYPE]
	: AecAppArx (_DNT("[!output RDS_SYMB][!output SAFE_PROJECT_NAME]"), _hdllInstance, [!output RDS_SYMB][!output SAFE_PROJECT_NAME]DLL) {
[!else]
	: AecAppDbx (_DNT("[!output RDS_SYMB][!output SAFE_PROJECT_NAME]"), _hdllInstance, [!output RDS_SYMB][!output SAFE_PROJECT_NAME]DLL) {
[!endif]
}

//-----------------------------------------------------------------------------
AcRx::AppRetCode C[!output SAFE_PROJECT_NAME]App::initApp () {
[!if !NO_COM_SERVER]
	if ( FAILED(DllRegisterServer()) )
		acutPrintf (_DNT("\nFailed to register.")) ;

[!endif]
	acrxRegisterAppMDIAware (acadAppPtr ()) ;
	// TODO: add your initialization functions

[!if APP_ARX_TYPE]
	return (AecAppArx::initApp ()) ;
[!else]
	return (AecAppDbx::initApp ()) ;
[!endif]
}

AcRx::AppRetCode C[!output SAFE_PROJECT_NAME]App::exitApp () {
	// TODO: add your initialization functions

[!if APP_ARX_TYPE]
	return (AecAppArx::exitApp ()) ;
[!else]
	return (AecAppDbx::exitApp ()) ;
[!endif]
}

//-----------------------------------------------------------------------------
void C[!output SAFE_PROJECT_NAME]App::getRequiredModules (AecRmCStringArray &reqApps) {
	reqApps.Add (_DNT("AecBase60")) ;
[!if APP_ARX_TYPE]
	reqApps.Add (_DNT("AecUiBase60")) ;
[!else]
	reqApps.Add (_DNT("AecArchBase60")) ;
[!endif]
}

//-----------------------------------------------------------------------------
Acad::ErrorStatus C[!output SAFE_PROJECT_NAME]App::registerServices () {
	Acad::ErrorStatus es =AecBaseServices::registerService (this) ;
	if ( es != Acad::eOk )
		return (es) ;
[!if APP_ARX_TYPE]
	return (AecUiBaseServices::registerService (this)) ;
[!else]
	return (ArchBaseServices::registerService (this)) ;
[!endif]
}

void C[!output SAFE_PROJECT_NAME]App::unRegisterServices () {
	AecBaseServices::unRegisterService (this) ;
[!if APP_ARX_TYPE]
	AecUiBaseServices::unRegisterService (this) ;
[!else]
	ArchBaseServices::unRegisterService (this) ;
[!endif]
}

//-----------------------------------------------------------------------------
C[!output SAFE_PROJECT_NAME]App *C[!output SAFE_PROJECT_NAME]App::getApp () {
	return (pThisOmfApp) ;
}

//-----------------------------------------------------------------------------
void C[!output SAFE_PROJECT_NAME]App::getRegistryInfo (AecRmCString &regCompanyName, AcadApp::LoadReasons &reasons) {
	regCompanyName =_DNT("Your Company Name") ;
[!if APP_ARX_TYPE]
	reasons =static_cast<AcadApp::LoadReasons> (AcadApp::kOnLoadRequest | AcadApp::kOnCommandInvocation) ;
[!else]
	reasons =static_cast<AcadApp::LoadReasons> (AcadApp::kOnLoadRequest) ;
[!endif]
}

[!if APP_ARX_TYPE]
//-----------------------------------------------------------------------------
void C[!output SAFE_PROJECT_NAME]App::registerCommandObjects () {
	// TODO: add your command objects here
}
[!endif]

//-----------------------------------------------------------------------------
void C[!output SAFE_PROJECT_NAME]App::initRegistryInfo () {
    //----- Add the resource only Dll info
	AecRegistryInfo *reginfo =appRegistryInfo () ;
	if ( reginfo != NULL ) {
		reginfo->getRegistryString (_DNT("Language"), _DNT("CurrentLanguage"), _DNT("English"), TRUE) ;
		CString locale ("Language\\English") ;
		CString dllName =appName () + _DNT("Enu.dll") ;
		reginfo->writeRegistryString (locale, (LPCTSTR)(C[!output SAFE_PROJECT_NAME]App::getApp ()->appName ()), dllName) ;
	}
}
