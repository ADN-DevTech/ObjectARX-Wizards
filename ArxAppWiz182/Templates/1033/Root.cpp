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
//- [!output SAFE_PROJECT_NAME].cpp : Initialization functions
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
[!if ATL_COM_SERVER]
#include <initguid.h>
#include "[!output PROJECT_NAME].h"
[!endif]
[!if MFC_EXT_SHARED]
[!if !DOTNET_MODULE]
#include <afxdllx.h>
[!endif]
[!endif]
[!if ATL_COM_SERVER]
#include "[!output PROJECT_NAME]_i.c"
[!if ACAD_ATL_EXT]
[!if APP_ARX_TYPE]
#include "acadi_i.c"
[!else]
#include "axdb_i.c"
[!endif]
[!endif]
[!endif]

[!if ATL_COM_SERVER]

//-----------------------------------------------------------------------------
class C[!output SAFE_PROJECT_NAME]Module : public CAtlDllModuleT<C[!output SAFE_PROJECT_NAME]Module> {

public :
	DECLARE_LIBID(LIBID_[!output RDS_SYMB][!output SAFE_PROJECT_NAME]Lib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_[!output UPPER_CASE_SAFE_PROJECT_NAME], "{[!output APPID_REGISTRY_FORMAT]}")
} ;

C[!output SAFE_PROJECT_NAME]Module _AtlModule ;

[!endif]
[!if MFC_EXT_SHARED]
//-----------------------------------------------------------------------------
//- Define the sole extension module object.
[!if !OMF_APP || DOTNET_MODULE]
AC_IMPLEMENT_EXTENSION_MODULE([!output SAFE_PROJECT_NAME]DLL)
//- Please do not remove the 3 following lines. These are here to make .NET MFC Wizards
//- running properly. The object will not compile but is require by .NET to recognize
//- this project as being an MFC project
#ifdef NEVER
AFX_EXTENSION_MODULE [!output SAFE_PROJECT_NAME]ExtDLL ={ NULL, NULL } ;
#endif

//- Now you can use the CAcModuleResourceOverride class in
//- your application to switch to the correct resource instance.
//- Please see the ObjectARX Documentation for more details
[!else]
AFX_EXTENSION_MODULE [!output RDS_SYMB][!output SAFE_PROJECT_NAME]DLL ={ NULL, NULL } ;
#include "[!output PROJECT_NAME]App.h"
extern C[!output SAFE_PROJECT_NAME]App *pThisOmfApp ;
[!endif]

[!endif]
//-----------------------------------------------------------------------------
//- DLL Entry Point
[!if DOTNET_MODULE]
#pragma managed(push, off)
[!endif]
extern "C"
BOOL WINAPI DllMain (HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
	//- Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved) ;

	if ( dwReason == DLL_PROCESS_ATTACH ) {
        _hdllInstance =hInstance ;
[!if MFC_EXT_SHARED]
[!if !OMF_APP]
[!if !DOTNET_MODULE]
		[!output SAFE_PROJECT_NAME]DLL.AttachInstance (hInstance) ;
[!endif]
[!else]
[!if !DOTNET_MODULE]
		//- Extension DLL one time initialization
		if ( !AfxInitExtensionModule ([!output RDS_SYMB][!output SAFE_PROJECT_NAME]DLL, hInstance) )
			return (0) ;
		//- Insert this DLL into the resource chain
		//- NOTE: If this Extension DLL is being implicitly linked to by
		//- an MFC Regular DLL (such as an ActiveX Control)
		//- instead of an MFC application, then you will want to
		//- remove this line from DllMain and put it in a separate
		//- function exported from this Extension DLL. The Regular DLL
		//- that uses this Extension DLL should then explicitly call that
		//- function to initialize this Extension DLL. Otherwise,
		//- the CDynLinkLibrary object will not be attached to the
		//- Regular DLL's resource chain, and serious problems will result.
		new CDynLinkLibrary ([!output RDS_SYMB][!output SAFE_PROJECT_NAME]DLL) ;
		pThisOmfApp =new C[!output SAFE_PROJECT_NAME]App ;
[!else]
[!endif]
[!endif]
[!if MFC_EXT_SHARED && ACAD_EXT]
[!if APP_ARX_TYPE]
[!if !DOTNET_MODULE]
		InitAcUiDLL () ;
[!endif]
[!endif]
[!endif]
[!endif]
	} else if ( dwReason == DLL_PROCESS_DETACH ) {
[!if MFC_EXT_SHARED]
[!if !OMF_APP]
[!if !DOTNET_MODULE]
		[!output SAFE_PROJECT_NAME]DLL.DetachInstance () ;
[!endif]
[!else]
[!if !DOTNET_MODULE]
		delete pThisOmfApp ;
		//- Terminate the library before destructors are called
		AfxTermExtensionModule ([!output RDS_SYMB][!output SAFE_PROJECT_NAME]DLL) ;
[!else]
[!endif]
[!endif]
[!endif]
	}
[!if ATL_COM_SERVER]
	return (_AtlModule.DllMain (dwReason, lpReserved)) ; 
[!else]
	return (TRUE) ;
[!endif]
}
[!if DOTNET_MODULE]
#pragma managed(pop)
[!endif]

[!if !NO_COM_SERVER]
//-----------------------------------------------------------------------------
//- Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow (void) {
[!if ATL_COM_SERVER]
	HRESULT hr =(_AtlModule.GetLockCount () == 0 ? S_OK : S_FALSE) ;
	return (hr) ;
[!else]
	// TODO: Implement this function and return the appropriate value to COM

	return (S_OK) ;
[!endif]
}

//-----------------------------------------------------------------------------
//- Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID *ppv) {
[!if ATL_COM_SERVER]
	return (_AtlModule.GetClassObject (rclsid, riid, ppv)) ;
[!else]
	// TODO: Return your class factory here
	return (S_OK) ;
[!endif]
}

//-----------------------------------------------------------------------------
//- DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer (void) {
[!if ATL_COM_SERVER]
	//- Registers object, typelib and all interfaces in typelib
	return (_AtlModule.RegisterServer (TRUE)) ;
[!else]
	// TODO: Register your server here
	return (S_OK) ;
[!endif]
}

//-----------------------------------------------------------------------------
//- DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer (void) {
[!if ATL_COM_SERVER]
	return (_AtlModule.UnregisterServer (TRUE)) ;
[!else]
	// TODO: Unregister your server here
	return (S_OK) ;
[!endif]
}

//-----------------------------------------------------------------------------
#ifndef _WIN64
#pragma comment(linker, "/EXPORT:DllCanUnloadNow=_DllCanUnloadNow@0,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject=_DllGetClassObject@12,PRIVATE")
#pragma comment(linker, "/EXPORT:DllRegisterServer=_DllRegisterServer@0,PRIVATE")
#pragma comment(linker, "/EXPORT:DllUnregisterServer=_DllUnregisterServer@0,PRIVATE")
#else
#pragma comment(linker, "/EXPORT:DllCanUnloadNow=DllCanUnloadNow,PRIVATE")
#pragma comment(linker, "/EXPORT:DllGetClassObject=DllGetClassObject,PRIVATE")
#pragma comment(linker, "/EXPORT:DllRegisterServer=DllRegisterServer,PRIVATE")
#pragma comment(linker, "/EXPORT:DllUnregisterServer=DllUnregisterServer,PRIVATE")
#endif

[!endif]
