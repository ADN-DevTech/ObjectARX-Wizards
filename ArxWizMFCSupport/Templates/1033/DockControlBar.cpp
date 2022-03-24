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
IMPLEMENT_DYNAMIC ([!output CLASS_NAME], [!output BASE_CLASS])

BEGIN_MESSAGE_MAP([!output CLASS_NAME], [!output BASE_CLASS])
	ON_WM_CREATE()
[!if CHILD_DIALOG_NEEDED]
	ON_WM_SYSCOMMAND()
	ON_WM_SIZE()
[!endif]
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
//----- [!output CLASS_NAME] *pInstance = new [!output CLASS_NAME];
//----- pInstance->Create (acedGetAcadFrame (), "My title bar") ;
//----- pInstance->EnableDocking (CBRS_ALIGN_ANY) ;
//----- pInstance->RestoreControlBar () ;

//-----------------------------------------------------------------------------
static CLSID cls[!output CLASS_NAME] = {0xeab78c04, 0x2194, 0x47ad, {0xa4, 0xf2, 0xad, 0xca, 0x3e, 0x3b, 0xb6, 0x3c}} ;


//-----------------------------------------------------------------------------
[!if CHILD_DIALOG_NEEDED]
[!output CLASS_NAME]::[!output CLASS_NAME] () : [!output BASE_CLASS]() {
[!else]
[!output CLASS_NAME]::[!output CLASS_NAME] () : [!output BASE_CLASS]() {
[!endif]
}

//-----------------------------------------------------------------------------
[!output CLASS_NAME]::~[!output CLASS_NAME] () {
[!if CHILD_DIALOG_NEEDED]

[!endif]
}

//-----------------------------------------------------------------------------
#ifdef _DEBUG
//- Please uncomment the 2 following lines to avoid linker error when compiling
//- in release mode. But make sure to uncomment these lines only once per project
//- if you derive multiple times from CAdUiDockControlBar/CAcUiDockControlBar
//- classes.

//void CAdUiDockControlBar::AssertValid () const {
//}
#endif

//-----------------------------------------------------------------------------
BOOL [!output CLASS_NAME]::Create (CWnd *pParent, LPCSTR lpszTitle) {
	CString strWndClass ;
	strWndClass =AfxRegisterWndClass (CS_DBLCLKS, LoadCursor (NULL, IDC_ARROW)) ;
	CRect rect (0, 0, 250, 200) ;
	if (![!output BASE_CLASS]::Create (
			strWndClass, lpszTitle, WS_VISIBLE | WS_CHILD | WS_CLIPCHILDREN,
			rect, pParent, 0
		)
	)
		return (FALSE) ;

	SetToolID (&cls[!output CLASS_NAME]) ;

	// TODO: Add your code here
	
	return (TRUE) ;
}

//-----------------------------------------------------------------------------
//----- This member function is called when an application requests the window be 
//----- created by calling the Create or CreateEx member function
int [!output CLASS_NAME]::OnCreate (LPCREATESTRUCT lpCreateStruct) {
	if ( [!output BASE_CLASS]::OnCreate (lpCreateStruct) == -1 )
		return (-1) ;

[!if CHILD_DIALOG_NEEDED]
	//----- Point to our resource
	CAcModuleResourceOverride resourceOverride; 	
	//----- Create it and set the parent as the dockctrl bar
	mChildDlg.Create ([!output IDD_DIALOG], this) ;
	//----- Move the window over so we can see the control lines
	mChildDlg.MoveWindow (0, 0, 100, 100, TRUE) ;
[!endif]
	return (0) ;
}

//-----------------------------------------------------------------------------
void [!output CLASS_NAME]::SizeChanged (CRect *lpRect, BOOL bFloating, int flags) {
[!if CHILD_DIALOG_NEEDED]
	// If valid
	if (::IsWindow (mChildDlg.GetSafeHwnd ())) 
	{
		//----- Always point to our resource to be safe
		CAcModuleResourceOverride resourceOverride ;
		//----- Then update its window size relatively
		mChildDlg.SetWindowPos (this, lpRect->left + 4, lpRect->top + 4, lpRect->Width (), lpRect->Height (), SWP_NOZORDER) ;
	}
[!endif]
}

[!if CHILD_DIALOG_NEEDED]
//-----------------------------------------------------------------------------
//-----  Function called when user selects a command from Control menu or when user 
//----- selects the Maximize or the Minimize button.
void [!output CLASS_NAME]::OnSysCommand (UINT nID, LPARAM lParam) {
	CAcUiDockControlBar::OnSysCommand (nID, lParam) ;
}

//-----------------------------------------------------------------------------
//----- The framework calls this member function after the window's size has changed
void [!output CLASS_NAME]::OnSize (UINT nType, int cx, int cy) {
	CAcUiDockControlBar::OnSize (nType, cx, cy) ;
	// If valid
	if (::IsWindow (mChildDlg.GetSafeHwnd ())) 
	{
		//----- Always point to our resource to be safe
		CAcModuleResourceOverride resourceOverride ;
		//----- then update its window position relatively
		mChildDlg.MoveWindow (0, 0, cx, cy) ;
	}
}
[!endif]
