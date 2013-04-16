// (C) Copyright 2005-2007 by Autodesk, Inc. 
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

//-----------------------------------------------------------------------------
//- [!output HEADER_FILE]
#pragma once

//-----------------------------------------------------------------------------
using namespace System ;
using namespace Autodesk::AutoCAD::Geometry ;
using namespace Autodesk::AutoCAD::DatabaseServices ;

//-----------------------------------------------------------------------------
//- Wizard Generated Custom Object .NET Wrapper
//- See the mgPoly in the ObjectARX SDK for further information
//-----------------------------------------------------------------------------
namespace [!output COMPANY_NAMESPACE] {
	namespace [!output OBJECT_NAMESPACE] {

		[Autodesk::AutoCAD::Runtime::Wrapper("[!output CUSTOM_OBJECTNAME]")]
		public ref class [!output MANAGED_WRAPPER_NAME] : public Autodesk::AutoCAD::DatabaseServices::[!output MANAGED_DERIVATION] {

		public:
			//- Constructor
			[!output MANAGED_WRAPPER_NAME] () ;

		internal:
			[!output MANAGED_WRAPPER_NAME] (System::IntPtr unmanagedPointer, bool bAutoDelete) ;

			//- Returns the unmanaged ARX Object
			inline [!output CUSTOM_OBJECTNAME] *GetImpObj () {
				return (static_cast<[!output CUSTOM_OBJECTNAME] *>(UnmanagedObject.ToPointer ())) ;
			}

		public:
			//- To define properties which get/set values of your object
			//- the format you must use is
			//-		__property void set_Center(Point2d point);
			//-		__property Point2d get_Center();
		} ;

	}
}