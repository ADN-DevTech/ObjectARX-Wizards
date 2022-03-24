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
//----- [!output CHILDHEADER_FILE] : Declaration of the [!output CHILDCLASS_NAME]
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
#include "acui.h"

//-----------------------------------------------------------------------------
class [!output CHILDCLASS_NAME] : public CAcUiDialog {
	DECLARE_DYNAMIC ([!output CHILDCLASS_NAME])

public:
	[!output CHILDCLASS_NAME] (CWnd *pParent =NULL, HINSTANCE hInstance =NULL) ;

	enum { IDD = [!output IDD_DIALOG]};

protected:
	virtual void DoDataExchange (CDataExchange *pDX) ;
	virtual BOOL OnCommand (WPARAM wParam, LPARAM lParam) ;

protected:
	afx_msg LRESULT OnAcadKeepFocus (WPARAM wParam, LPARAM lParam) ;
public:	
	afx_msg void OnSize (UINT nType, int cx, int cy) ;

protected:
	DECLARE_MESSAGE_MAP()
} ;
