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
//----- [!output HEADER_FILE] : Declaration of the [!output CLASS_NAME]
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "[!output INCLUDE_HEADER]"
[!if CHILD_DIALOG_NEEDED]
#include "[!output CHILDHEADER_FILE]"
[!endif]

//-----------------------------------------------------------------------------
class [!output CLASS_NAME] : public [!output BASE_CLASS] {
	DECLARE_DYNAMIC ([!output CLASS_NAME])

public:
[!if CHILD_DIALOG_NEEDED]
	//----- Child dialog which will use the resource id supplied
	[!output CLASS_NAME]ChildDlg mChildDlg ;
[!endif]

public:
	[!output CLASS_NAME] (HINSTANCE hInstance =NULL) ;
	virtual ~[!output CLASS_NAME] () ;

	//- Load the data from xml.
	virtual BOOL Load (IUnknown *pUnk) ;
	//- Save the data to xml.
	virtual BOOL Save (IUnknown *pUnk) ;
	//- Called by the palette set when the palette is made active
	virtual void OnSetActive () ;
	//- Called by AutoCAD to steal focus from the palette
	virtual bool CanFrameworkTakeFocus () ;

protected:
	afx_msg int OnCreate (LPCREATESTRUCT lpCreateStruct) ;
[!if CHILD_DIALOG_NEEDED]
	afx_msg void OnSize (UINT nType, int cx, int cy) ;
[!endif]

	DECLARE_MESSAGE_MAP()
} ;
