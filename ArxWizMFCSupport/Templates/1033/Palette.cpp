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
//----- [!output IMPL_FILE] : Implementation of [!output CLASS_NAME]
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"
#include "[!output HEADER_FILE]"

//-----------------------------------------------------------------------------
//- Import the MSXML functionality
#import "msxml.dll" named_guids
//using namespace MSXML ;

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC ([!output CLASS_NAME], [!output BASE_CLASS])

BEGIN_MESSAGE_MAP([!output CLASS_NAME], [!output BASE_CLASS])
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_SIZING()
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
[!output CLASS_NAME]::[!output CLASS_NAME] (HINSTANCE hInstance) : [!output BASE_CLASS] (), mChildDlg(NULL, hInstance) {
}

//-----------------------------------------------------------------------------
[!output CLASS_NAME]::~[!output CLASS_NAME] () {
}

//-----------------------------------------------------------------------------
//- Load the input data from xml.
BOOL [!output CLASS_NAME]::Load (IUnknown *pUnk) {	
	//- Call base class first 
	[!output BASE_CLASS]::Load (pUnk) ;
	//- Initialise for XML
	CComQIPtr<MSXML::IXMLDOMNode> pNode(pUnk) ;
	MSXML::IXMLDOMNodePtr pChild, pChild1 ;

	// TODO: read in data from palette XML

	return (TRUE) ;
}

//-----------------------------------------------------------------------------
//- Save the input data to xml.
BOOL [!output CLASS_NAME]::Save (IUnknown *pUnk) {
	//- Call base class first 
	[!output BASE_CLASS]::Save (pUnk) ;
	//- initialise for XML
	CComQIPtr<MSXML::IXMLDOMNode> pNode(pUnk) ;
	MSXML::IXMLDOMNodePtr pChild, pChild1 ;

	// TODO: save data to palette XML

	return (TRUE) ;
}

//-----------------------------------------------------------------------------
//- Used to add a dialog resource
int [!output CLASS_NAME]::OnCreate (LPCREATESTRUCT lpCreateStruct) {
	if ( [!output BASE_CLASS]::OnCreate (lpCreateStruct) == -1 )
		return (-1) ;
	//- Create it and set the parent as the dockctrl bar
	mChildDlg.Create ([!output IDD_DIALOG], this) ;

	CRect rect ;
	GetWindowRect (&rect) ;
	//- Move the window over so we can see the control lines
	mChildDlg.MoveWindow (0, 0, rect.Width (), rect.Height (), TRUE) ;
	return (0) ;
}

//-----------------------------------------------------------------------------
//- Called by the palette set when the palette is made active
void [!output CLASS_NAME]::OnSetActive () {
	return ([!output BASE_CLASS]::OnSetActive ()) ;
}

//-----------------------------------------------------------------------------
//- Called by AutoCAD to steal focus from the palette
bool [!output CLASS_NAME]::CanFrameworkTakeFocus () {
	//- Not simply calling IsFloating() (a BOOL) avoids warning C4800
	return (GetPaletteSet ()->IsFloating () == TRUE ? true : false) ;
}

//-----------------------------------------------------------------------------
void [!output CLASS_NAME]::OnSize (UINT nType, int cx, int cy) {
	[!output BASE_CLASS]::OnSize (nType, cx, cy) ;
	//- If valid
	if ( ::IsWindow (mChildDlg.GetSafeHwnd ()) ) {
		//- Forward the call
		mChildDlg.OnSize (nType, cx, cy) ;
	}
}

