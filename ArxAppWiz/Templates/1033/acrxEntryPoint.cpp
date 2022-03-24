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

//-----------------------------------------------------------------------------
#define szRDS _RXST("[!output RDS_SYMB]")
[!if STD_COM_SERVER]
STDAPI DllRegisterServer (void) ;
[!endif]
[!if MFC_EXT_SHARED && DOTNET_MODULE]
AC_DECLARE_EXTENSION_MODULE([!output SAFE_PROJECT_NAME]DLL) ;
[!endif]

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
[!if APP_ARX_TYPE || APP_CRX_TYPE]
class C[!output SAFE_PROJECT_NAME]App : public AcRxArxApp {
[!else]
class C[!output SAFE_PROJECT_NAME]App : public AcRxDbxApp {
[!endif]

public:
[!if APP_ARX_TYPE || APP_CRX_TYPE]
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
[!if APP_ARX_TYPE || APP_CRX_TYPE]
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
[!if APP_ARX_TYPE || APP_CRX_TYPE]
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
	
[!if APP_ARX_TYPE || APP_CRX_TYPE]
	// The ACED_ARXCOMMAND_ENTRY_AUTO macro can be applied to any static member 
	// function of the C[!output SAFE_PROJECT_NAME]App class.
	// The function should take no arguments and return nothing.
	//
	// NOTE: ACED_ARXCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid and
	// have arguments to define context and command mechanism.
	
	// ACED_ARXCOMMAND_ENTRY_AUTO(classname, group, globCmd, locCmd, cmdFlags, UIContext)
	// ACED_ARXCOMMAND_ENTRYBYID_AUTO(classname, group, globCmd, locCmdId, cmdFlags, UIContext)
	// only differs that it creates a localized name using a string in the resource file
	//   locCmdId - resource ID for localized command

	// Modal Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(C[!output SAFE_PROJECT_NAME]App, [!output RDS_SYMB]MyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL)
	static void [!output RDS_SYMB]MyGroupMyCommand () {
		// Put your command code here

	}

[!if !APP_CRX_TYPE]
	// Modal Command with pickfirst selection
	// ACED_ARXCOMMAND_ENTRY_AUTO(C[!output SAFE_PROJECT_NAME]App, [!output RDS_SYMB]MyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET)
	static void [!output RDS_SYMB]MyGroupMyPickFirst () {
		ads_name result ;
		int iRet =acedSSGet (ACRX_T("_I"), NULL, NULL, NULL, result) ;
		if ( iRet == RTNORM )
		{
			// There are selected entities
			// Put your command using pickfirst set code here
		}
		else
		{
			// There are no selected entities
			// Put your command code here
		}
	}

[!endif]
	// Application Session Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(C[!output SAFE_PROJECT_NAME]App, [!output RDS_SYMB]MyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION)
	static void [!output RDS_SYMB]MyGroupMySessionCmd () {
		// Put your command code here
	}

	// The ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO macros can be applied to any static member 
	// function of the C[!output SAFE_PROJECT_NAME]App class.
	// The function may or may not take arguments and have to return RTNORM, RTERROR, RTCAN, RTFAIL, RTREJ to AutoCAD, but use
	// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal to return
	// a value to the Lisp interpreter.
	//
	// NOTE: ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid.
	
	//- ACED_ADSFUNCTION_ENTRY_AUTO(classname, name, regFunc) - this example
	//- ACED_ADSSYMBOL_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file
	//- ACED_ADSCOMMAND_ENTRY_AUTO(classname, name, regFunc) - a Lisp command (prefix C:)
	//- ACED_ADSCOMMAND_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file

	// Lisp Function is similar to ARX Command but it creates a lisp 
	// callable function. Many return types are supported not just string
	// or integer.
	// ACED_ADSFUNCTION_ENTRY_AUTO(C[!output SAFE_PROJECT_NAME]App, MyLispFunction, false)
	static int ads_MyLispFunction () {
		//struct resbuf *args =acedGetArgs () ;
		
		// Put your command code here

		//acutRelRb (args) ;
		
		// Return a value to the AutoCAD Lisp Interpreter
		// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal

		return (RTNORM) ;
	}
	
[!endif]
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(C[!output SAFE_PROJECT_NAME]App)

[!if APP_ARX_TYPE || APP_CRX_TYPE]
ACED_ARXCOMMAND_ENTRY_AUTO(C[!output SAFE_PROJECT_NAME]App, [!output RDS_SYMB]MyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL, NULL)
[!if !APP_CRX_TYPE]
ACED_ARXCOMMAND_ENTRY_AUTO(C[!output SAFE_PROJECT_NAME]App, [!output RDS_SYMB]MyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
[!endif]
ACED_ARXCOMMAND_ENTRY_AUTO(C[!output SAFE_PROJECT_NAME]App, [!output RDS_SYMB]MyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION, NULL)
ACED_ADSSYMBOL_ENTRY_AUTO(C[!output SAFE_PROJECT_NAME]App, MyLispFunction, false)

[!endif]
