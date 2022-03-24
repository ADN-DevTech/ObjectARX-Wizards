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
//----- omfHeaders.h : includes OMF headers files
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
//- This line allows us to get rid of the .def file in ARX projects
#ifndef _WIN64
#pragma comment(linker, "/export:_acrxGetApiVersion,PRIVATE")
#else
#pragma comment(linker, "/export:acrxGetApiVersion,PRIVATE")
#endif

//-----------------------------------------------------------------------------
#include "axdb.h"

#undef T
#define AECDECLEXPORT
#define AECDECLIMPORT

//----- The AEC OMF specific includes:
#include "AecCore.h"
#include "AecModeler.h"
#include "AecResMgr/AecRmCString.h"
#include "AecBase.h"			//----- ... AEC Base
#include "ArchBase.h"			//----- ... AEC Architectural Objects
#include "AecLogicalAppNames.h"
#include "AecSchedule.h"
#include "AecScheduleData.h"
#include "AecStructureBase.h"
#include "Res_AecBase.h"
#include "Res_AecXBase.h"
#include "AecXmlBase.h"
#ifndef DBX
#include "AecUiBase.h"
#include "AecGuiBase.h"
#include "Res_AecGuiBase.h"
#endif

#ifdef _MANAGED
//- AecBaseMgd Public
#using <AecBaseMgd.dll>
#include "AecBaseMgd/namespaces.h"
#include "AecBaseMgd/AecBaseNamespaces.h"
//#include "AecBaseMgd/mgdinterop.h"
#include "AecBaseMgd/AecBaseMgdUtils.h"
#include "AecBaseMgd/AecBaseMgd.inl"
#endif

#pragma comment (lib, "AecModeler60.lib")
#pragma comment (lib, "AecBase.lib")
#pragma comment (lib, "AecBaseEx.lib")
#pragma comment (lib, "AecArchBase.lib")
#pragma comment (lib, "AecUiBase.lib")
#pragma comment (lib, "AecArchDACHBase.lib")
#pragma comment (lib, "AecProjectBase.lib")
#pragma comment (lib, "AecResMgr.lib")
#pragma comment (lib, "AecSchedule.lib")
#pragma comment (lib, "AecScheduleData.lib")
#pragma comment (lib, "AecStructureBase.lib")
#pragma comment (lib, "AecSystemTools.lib")
#pragma comment (lib, "AecXBase.lib")
#pragma comment (lib, "AecXmlBase.lib")
#pragma comment (lib, "AecRcpBase.lib")
#ifndef DBX
#pragma comment (lib, "AecGuiBase.lib")
#pragma comment (lib, "AecResUi.lib")
#endif
