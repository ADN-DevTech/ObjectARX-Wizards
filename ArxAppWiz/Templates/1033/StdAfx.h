// (C) Copyright 2002-2012 by Autodesk, Inc. 
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
//- StdAfx.h : include file for standard system include files,
//-      or project specific include files that are used frequently,
//-      but are changed infrequently
//-----------------------------------------------------------------------------
#pragma once
#define [!output UPPER_CASE_PROJECT_NAME]_MODULE

[!if IMPL_DEBUG]
//-----------------------------------------------------------------------------
//- 'DEBUG workaround' below prevents the MFC or ATL #include-s from pulling 
//- in "Afx.h" that would force the debug CRT through #pragma-s.
#if defined(_DEBUG) && !defined(AC_FULL_DEBUG)
#define _DEBUG_WAS_DEFINED
#undef _DEBUG
#pragma message ("     Compiling MFC / STL / ATL header files in release mode.")
#endif

[!endif]
#pragma pack (push, 8)
#pragma warning(disable: 4786 4996)
//#pragma warning(disable: 4098)

[!if STD_COM_SERVER || ATL_COM_SERVER || MFC_EXT_SHARED]
//-----------------------------------------------------------------------------
#define STRICT

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN			//- Exclude rarely-used stuff from Windows headers
#endif

//- Modify the following defines if you have to target a platform prior to the ones specified below.
//- Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER							//- Allow use of features specific to Windows 95 and Windows NT 4 or later.
#define WINVER 0x0500			//- Change this to the appropriate value to target Windows 98 and Windows 2000 or later.
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#endif

[!if ATL_COM_SERVER]
//-----------------------------------------------------------------------------
#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	//- Some CString constructors will be explicit
//- Turns off ATL's hiding of some common and often safely ignored warning messages
#define _ATL_ALL_WARNINGS

[!endif]

[!if STD_COM_SERVER && !MFC_EXT_SHARED]
//-----------------------------------------------------------------------------
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <ole2.h>

[!endif]
[!else]
//-----------------------------------------------------------------------------
#include <windows.h>

[!endif]
//- ObjectARX and OMF headers needs this
#include <map>

[!if MFC_EXT_SHARED]
//-----------------------------------------------------------------------------
#include <afxwin.h>				//- MFC core and standard components
#include <afxext.h>				//- MFC extensions
#include <afxcmn.h>				//- MFC support for Windows Common Controls

[!endif]
[!if ATL_COM_SERVER || DBX_COM_IMPORT || ACAD_COM_IMPORT]
//-----------------------------------------------------------------------------
#include <AtlBase.h>
[!if ATL_COM_SERVER]
#include <AtlCom.h>
using namespace ATL ;

[!endif]
[!endif]
[!if DOTNET_MODULE]
//-----------------------------------------------------------------------------
#using <mscorlib.dll>
#using <System.dll>

#using <acdbmgd.dll>
[!if APP_ARX_TYPE || APP_CRX_TYPE]
#using <acmgd.dll>
[!endif]
[!if APP_ARX_TYPE]
#using <AcCui.dll>
[!endif]
[!if DOTNET_ACA]
#using <AecBaseMgd.dll>
#using <AecArchMgd.dll>
#using <AecPropDataMgd.dll>
#using <AecStructureMgd.dll>
#using <AecProjectBaseMgd.dll>
#using <AecRcpMgd.dll>
#using <AecBaseUtilsMgd.dll>
#using <AecUiBaseMgd.dll>
[!endif]
[!if DOTNET_MEP]
#using <AecbBldSrvMgd.dll>
#using <AecbElecBaseMgd.dll>
#using <AecbHvacBaseMgd.dll>
#using <AecbPartBaseMgd.dll>
#using <AecbPipeBaseMgd.dll>
#using <AecbPlumbingBaseMgd.dll>
[!endif]

#include <vcclr.h>

[!endif]
//-----------------------------------------------------------------------------
//- Include ObjectDBX/ObjectARX headers
//- Uncomment one of the following lines to bring a given library in your project.
//#define _BREP_SUPPORT_					//- Support for the BRep API
//#define _HLR_SUPPORT_						//- Support for the Hidden Line Removal API
//#define _AMODELER_SUPPORT_				//- Support for the AModeler API
[!if APP_ARX_TYPE || APP_CRX_TYPE]
//#define _ASE_SUPPORT_							//- Support for the ASI/ASE API
//#define _RENDER_SUPPORT_					//- Support for the AutoCAD Render API
[!if !APP_CRX_TYPE]
//#define _ARX_CUSTOM_DRAG_N_DROP_	//- Support for the ObjectARX Drag'n Drop API
[!endif]
//#define _INC_LEAGACY_HEADERS_			//- Include legacy headers in this project
#include "arxHeaders.h"

[!else]
#include "dbxHeaders.h"
[!if MFC_EXT_SHARED]
#include "AcExtensionModule.h" 					//- Needed for AutoCAD MFC extension even if not present in the RealDWG SDK
[!endif]

[!endif]
[!if APP_ARX_TYPE || APP_CRX_TYPE]

//-----------------------------------------------------------------------------
#include "DocData.h" //- Your document specific data class holder

//- Declare it as an extern here so that it becomes available in all modules
extern AcApDataManager<CDocData> DocVars ;

[!endif]
[!if !ATL_COM_SERVER]
[!if DBX_COM_IMPORT]
//-----------------------------------------------------------------------------
#import "axdb19enu.tlb" raw_interfaces_only no_namespace

[!endif]
[!if ACAD_COM_IMPORT]
//-----------------------------------------------------------------------------
#import "acax19enu.tlb" raw_interfaces_only no_namespace

[!endif]
[!endif]
#pragma pack (pop)

[!if IMPL_DEBUG]
//-----------------------------------------------------------------------------
#ifdef _DEBUG_WAS_DEFINED
#define _DEBUG
#undef _DEBUG_WAS_DEFINED
#endif
[!endif]
