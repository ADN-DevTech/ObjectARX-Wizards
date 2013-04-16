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
//----- [!output IMPL_FILE] : Implementation of [!output CLASS_NAME_ROOT]
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "[!output HEADER_FILE]"

//-----------------------------------------------------------------------------
[!output CLASS_NAME_ROOT]::[!output CLASS_NAME_ROOT] (const bool autoInitAndRelease) : [!output BASE_CLASS](), mbAutoInitAndRelease(autoInitAndRelease) {
	if ( autoInitAndRelease ) {
		if ( acProfileManagerPtr () )
			acProfileManagerPtr ()->addReactor (this) ;
		else
			mbAutoInitAndRelease =false ;
	}
}

//-----------------------------------------------------------------------------
[!output CLASS_NAME_ROOT]::~[!output CLASS_NAME_ROOT] () {
	Detach () ;
}

//-----------------------------------------------------------------------------
void [!output CLASS_NAME_ROOT]::Attach () {
	Detach () ;
	if ( !mbAutoInitAndRelease ) {
		if ( acProfileManagerPtr () ) {
			acProfileManagerPtr ()->addReactor (this) ;
			mbAutoInitAndRelease =true ;
		}
	}
}

void [!output CLASS_NAME_ROOT]::Detach () {
	if ( mbAutoInitAndRelease ) {
		if ( acProfileManagerPtr () ) {
			acProfileManagerPtr ()->removeReactor (this) ;
			mbAutoInitAndRelease =false ;
		}
	}
}

AcApProfileManager *[!output CLASS_NAME_ROOT]::Subject () const {
	return (acProfileManagerPtr ()) ;
}

bool [!output CLASS_NAME_ROOT]::IsAttached () const {
	return (mbAutoInitAndRelease) ;
}
