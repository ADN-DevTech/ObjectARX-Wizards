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
//----- [!output SAFE_PROJECT_NAME]App.h : OMF application object header
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
[!if APP_ARX_TYPE]
class C[!output SAFE_PROJECT_NAME]App : public AecAppArx {
[!else]
class C[!output SAFE_PROJECT_NAME]App : public AecAppDbx {
[!endif]
	
public:
	//----- ObjectARX run time tree functions
	ACRX_DECLARE_MEMBERS(C[!output SAFE_PROJECT_NAME]App);
public:
	C[!output SAFE_PROJECT_NAME]App () ;
	//----- Called by the OMF when the application loads.
	virtual AcRx::AppRetCode initApp () ;
	//----- Called by the OMF when the application unloads.
	virtual AcRx::AppRetCode exitApp () ;
	//----- Called by the OMF when the application loads to determine the dependencies
	virtual void getRequiredModules (AecRmCStringArray &reqApps) ;
	//----- Called by the OMF when the application loads  to register the application
	virtual void getRegistryInfo (AecRmCString &regCompanyName, AcadApp::LoadReasons &reasons) ;
	//----- Returns the only instance of this class
	static C[!output SAFE_PROJECT_NAME]App *getApp () ;
    
protected:
[!if APP_ARX_TYPE]
	//----- Called by the OMF when the application loads to register the commands the application defines
	virtual void registerCommandObjects () ;
[!endif]
	//----- Called by the OMF when the application loads to register ARX services
	virtual Acad::ErrorStatus registerServices () ;
	//----- Called by the OMF when the application unloads to unregister ARX services
	virtual void unRegisterServices () ;
	//----- Must use resource-DLL now
	virtual void initRegistryInfo () ;
} ;

extern C[!output SAFE_PROJECT_NAME]App *pThisOmfApp ;
