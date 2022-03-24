// (C) Copyright 2005-2022 by Autodesk, Inc. 
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
#include "StdAfx.h"
#include "[!output HEADER_FILE]"

//-----------------------------------------------------------------------------
//- Template class that wraps GCHandle from mscorlib.dll
#include <gcroot.h>

//-----------------------------------------------------------------------------
//- autodesk interop header, to aid converting between unmanaged ObjectARX and managed ObjectARX.NET
#include "mgdinterop.h"

//-----------------------------------------------------------------------------
[!output COMPANY_NAMESPACE]::[!output OBJECT_NAMESPACE]::[!output MANAGED_WRAPPER_NAME]::[!output MANAGED_WRAPPER_NAME] () 
	: Autodesk::AutoCAD::DatabaseServices::[!output MANAGED_DERIVATION] ((System::IntPtr)new [!output CUSTOM_OBJECTNAME] (), true)
{
}

//-----------------------------------------------------------------------------
[!output COMPANY_NAMESPACE]::[!output OBJECT_NAMESPACE]::[!output MANAGED_WRAPPER_NAME]::[!output MANAGED_WRAPPER_NAME] (System::IntPtr unmanagedPointer, bool bAutoDelete)
	: Autodesk::AutoCAD::DatabaseServices::[!output MANAGED_DERIVATION] (unmanagedPointer, bAutoDelete)
{
}
