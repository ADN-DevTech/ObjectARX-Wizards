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

//-----------------------------------------------------------------------------
class [!output CLASS_NAME] : public [!output BASE_CLASS] {
	DECLARE_DYNAMIC ([!output CLASS_NAME])

public:
	[!output CLASS_NAME] (
			BOOL bOpenFileDialog,			// true=open, false=save
			LPCTSTR lpszDefExt =NULL,		// default filename extension
			LPCTSTR lpszFileName =NULL,		// initial filename, NULL means no default file name
			DWORD dwFlags =OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,	// see OPENFILENAME struct
			LPCTSTR lpszFilter =NULL,		// string filter *.cpp;*.h;etc
[!if CLASS_NAME != CAdUiFileDialog]
			CWnd *pParentWnd =NULL			// dialogs parent or owner window				
[!else]
			CWnd *pParentWnd =NULL,			// dialogs parent or owner window				
			HINSTANCE hDialogResource =NULL	// Resource ID for template; null means use the default
[!endif]
	) ;

protected:
	virtual void DoDataExchange (CDataExchange *pDX) ;
	afx_msg LRESULT OnAcadKeepFocus (WPARAM, LPARAM) ;

	DECLARE_MESSAGE_MAP()
} ;
