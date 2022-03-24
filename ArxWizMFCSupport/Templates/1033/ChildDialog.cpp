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
//- [!output IMPL_FILE] : Implementation of [!output CHILDCLASS_NAME]
//-----------------------------------------------------------------------------
#include "StdAfx.h"

#include "resource.h"
#include "[!output CHILDHEADER_FILE]"

//-----------------------------------------------------------------------------
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//-----------------------------------------------------------------------------
IMPLEMENT_DYNAMIC ([!output CHILDCLASS_NAME], CAcUiDialog)

BEGIN_MESSAGE_MAP([!output CHILDCLASS_NAME], CAcUiDialog)
	//{{AFX_MSG_MAP([!output CHILDCLASS_NAME])
	ON_MESSAGE(WM_ACAD_KEEPFOCUS, OnAcadKeepFocus)    // Needed for modeless dialog.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
[!output CHILDCLASS_NAME]::[!output CHILDCLASS_NAME] (CWnd *pParent /*=NULL*/, HINSTANCE hInstance /*=NULL*/) : CAcUiDialog ([!output CHILDCLASS_NAME]::IDD, pParent, hInstance) {
	//{{AFX_DATA_INIT([!output CHILDCLASS_NAME])
	//}}AFX_DATA_INIT
}

//-----------------------------------------------------------------------------
void [!output CHILDCLASS_NAME]::DoDataExchange (CDataExchange *pDX) {
	CAcUiDialog::DoDataExchange (pDX) ;
	//{{AFX_DATA_MAP([!output CHILDCLASS_NAME])
	//}}AFX_DATA_MAP
}

//-----------------------------------------------------------------------------
//- Needed for modeless dialogs to keep focus.
//- Return FALSE to not keep the focus, return TRUE to keep the focus
LRESULT [!output CHILDCLASS_NAME]::OnAcadKeepFocus (WPARAM wParam, LPARAM lParam) {
	return (TRUE) ;
}

//-----------------------------------------------------------------------------
//- As this dialog is a child dialog we need to disable ok and cancel
BOOL [!output CHILDCLASS_NAME]::OnCommand (WPARAM wParam, LPARAM lParam) {
	switch ( wParam ) {
		case IDOK:
		case IDCANCEL:
			return (FALSE) ;
	}	
	return (CAcUiDialog::OnCommand (wParam, lParam)) ;
}

//-----------------------------------------------------------------------------
void [!output CHILDCLASS_NAME]::OnSize (UINT nType, int cx, int cy) {
	CAcUiDialog::OnSize (nType, cx, cy) ;
	//- Now update the dialog
	MoveWindow (0, 0, cx, cy) ;
}
