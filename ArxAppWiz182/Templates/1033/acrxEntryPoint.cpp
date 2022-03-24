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
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
[!if OMF_APP && !DOTNET_MODULE]
#include "[!output PROJECT_NAME]App.h"
[!endif]

//-----------------------------------------------------------------------------
#define szRDS _RXST("[!output RDS_SYMB]")
[!if MFC_EXT_SHARED && DOTNET_MODULE]
AC_DECLARE_EXTENSION_MODULE([!output SAFE_PROJECT_NAME]DLL) ;
[!endif]

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
[!if OMF_APP && !DOTNET_MODULE]
extern "C"
AcRx::AppRetCode __declspec(dllexport) acrxEntryPoint (AcRx::AppMsgCode msg, void *pkt) {
	return (C[!output SAFE_PROJECT_NAME]App::getApp ()->entryPoint (msg, pkt)) ;
}

[!else]
[!if APP_ARX_TYPE]
class C[!output SAFE_PROJECT_NAME]App : public AcRxArxApp {
[!else]
class C[!output SAFE_PROJECT_NAME]App : public AcRxDbxApp {
[!endif]

public:
[!if APP_ARX_TYPE]
	C[!output SAFE_PROJECT_NAME]App () : AcRxArxApp () {}
[!else]
	C[!output SAFE_PROJECT_NAME]App () : AcRxDbxApp () {}
[!endif]

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here
[!if MFC_EXT_SHARED && DOTNET_MODULE]
		// Save critical data pointers before running the constructors (see afxdllx.h for details)
		AFX_MODULE_STATE* pModuleState = AfxGetModuleState();
		pModuleState->m_pClassInit = pModuleState->m_classList;
		pModuleState->m_pFactoryInit = pModuleState->m_factoryList;
		pModuleState->m_classList.m_pHead = NULL;
		pModuleState->m_factoryList.m_pHead = NULL;

		[!output SAFE_PROJECT_NAME]DLL.AttachInstance (_hdllInstance) ;
[!if ACAD_EXT && APP_ARX_TYPE]
		InitAcUiDLL () ;
[!endif]
[!endif]

		// You *must* call On_kInitAppMsg here
[!if APP_ARX_TYPE]
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
[!else]
		AcRx::AppRetCode retCode =AcRxDbxApp::On_kInitAppMsg (pkt) ;
[!endif]
		
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
[!if APP_ARX_TYPE]
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;
[!else]
		AcRx::AppRetCode retCode =AcRxDbxApp::On_kUnloadAppMsg (pkt) ;
[!endif]

		// TODO: Unload dependencies here
[!if MFC_EXT_SHARED && DOTNET_MODULE]
		[!output SAFE_PROJECT_NAME]DLL.DetachInstance () ;
[!endif]

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
[!if STD_COM_SERVER || ATL_COM_SERVER]
		//----- Self-register COM server upon loading.
		if ( FAILED(::DllRegisterServer ()) )
			acutPrintf (_RXST("Failed to register COM server.\n")) ;
[!endif]
	}

} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(C[!output SAFE_PROJECT_NAME]App)

[!endif]
