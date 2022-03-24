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
//----- [!output IMPL_FILE] : Implementation of [!output CLASS_NAME_ROOT]
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "[!output HEADER_FILE]"

//-----------------------------------------------------------------------------
[!output CLASS_NAME_ROOT]::[!output CLASS_NAME_ROOT] (AcApDocument *pDoc) : [!output BASE_CLASS](), mpDocument(pDoc) {
	if ( pDoc ) {	
		AcApDocument *pCurDoc =NULL ;
		if ( pDoc != curDoc () ) {
			pCurDoc =curDoc () ;
			acDocManager->setCurDocument (pDoc) ;
		}
		acgsGetGsManager ()->getGSClassFactory ()->addReactor (this) ;
		if ( pCurDoc )
			acDocManager->setCurDocument (pCurDoc) ;
	}
}

//-----------------------------------------------------------------------------
[!output CLASS_NAME_ROOT]::~[!output CLASS_NAME_ROOT] () {
	//----- If you created this instance with AcApDocument overload,
	//----- do NEVER call this destructor when the GsManager is already
	//----- unloaded. The GsManager is already unloaded when you
	//----- get the AcRx::kUnloadAppMsg message in the acrxEntryPoint,
	//----- or on the AcApDocManagerReactor::documentToBeDestroyed()
	//----- notification.
	//----- If you have to delete this instance when the document this
	//----- instance belongs to gets destroyed, you should use the
	//----- AcGsReactor::gsToBeUnloaded() notification. There it's safe
	//----- to delete this instance.
	Detach () ;
}

//-----------------------------------------------------------------------------
void [!output CLASS_NAME_ROOT]::Attach (AcApDocument *pDoc) {
	Detach () ;
	if ( mpDocument == NULL ) {
		if ( (mpDocument =pDoc) != NULL ) {	
			AcApDocument *pCurDoc =NULL ;
			if ( pDoc != curDoc () ) {
				pCurDoc =curDoc () ;
				acDocManager->setCurDocument (pDoc) ;
			}
			acgsGetGsManager ()->getGSClassFactory ()->addReactor (this) ;
			if ( pCurDoc )
				acDocManager->setCurDocument (pCurDoc) ;
		}
	}
}

void [!output CLASS_NAME_ROOT]::Detach () {
	if ( mpDocument ) {
		AcApDocument *pCurDoc =NULL ;
		if ( mpDocument != curDoc () ) {
			pCurDoc =curDoc () ;
			acDocManager->setCurDocument (mpDocument) ;
		}
		acgsGetGsManager ()->getGSClassFactory ()->removeReactor (this) ;
		if ( pCurDoc )
			acDocManager->setCurDocument (pCurDoc) ;
		mpDocument =NULL ;
	}
}

AcApDocument *[!output CLASS_NAME_ROOT]::Subject () const {
	return (mpDocument) ;
}

bool [!output CLASS_NAME_ROOT]::IsAttached () const {
	return (mpDocument != NULL) ;
}
