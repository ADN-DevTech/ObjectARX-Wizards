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
#include "[!output HEADER_FILE]"

//-----------------------------------------------------------------------------
Adesk::UInt32 [!output CLASS_NAME]::kCurrentVersionNumber =1 ;

[!if ACDBOBJECT_PROTOCOLS]
//-----------------------------------------------------------------------------
ACRX_DXF_DEFINE_MEMBERS (
	[!output CLASS_NAME], [!output BASE_CLASS],
	AcDb::kDHL_CURRENT, AcDb::kMReleaseCurrent, 
	AcDbProxyEntity::kNoOperation, [!output DXFNAME],
[!output APPNAME]
|Product Desc:     A description for your object
|Company:          Your company name
|WEB Address:      Your company WEB site address
)

[!else]
ACRX_CONS_DEFINE_MEMBERS([!output CLASS_NAME], [!output BASE_CLASS], 1)

[!endif]
//-----------------------------------------------------------------------------
[!output CLASS_NAME]::[!output CLASS_NAME] () : [!output BASE_CLASS] () {
}

[!output CLASS_NAME]::~[!output CLASS_NAME] () {
}

[!if ACDBOBJECT_PROTOCOLS]
//-----------------------------------------------------------------------------
//----- AcDbObject protocols
[!if DWG_PROTOCOL]
//- Dwg Filing protocol
Acad::ErrorStatus [!output CLASS_NAME]::dwgOutFields (AcDbDwgFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =[!output BASE_CLASS]::dwgOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 ([!output CLASS_NAME]::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::dwgInFields (AcDbDwgFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =[!output BASE_CLASS]::dwgInFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be read first
	Adesk::UInt32 version =0 ;
	if ( (es =pFiler->readUInt32 (&version)) != Acad::eOk )
		return (es) ;
	if ( version > [!output CLASS_NAME]::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < [!output CLASS_NAME]::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params
	//.....

	return (pFiler->filerStatus ()) ;
}

[!endif]
[!if DXF_PROTOCOL]
//- Dxf Filing protocol
Acad::ErrorStatus [!output CLASS_NAME]::dxfOutFields (AcDbDxfFiler *pFiler) const {
	assertReadEnabled () ;
	//----- Save parent class information first.
	Acad::ErrorStatus es =[!output BASE_CLASS]::dxfOutFields (pFiler) ;
	if ( es != Acad::eOk )
		return (es) ;
	es =pFiler->writeItem (AcDb::kDxfSubclass, _RXST("[!output CLASS_NAME]")) ;
	if ( es != Acad::eOk )
		return (es) ;
	//----- Object version number needs to be saved first
	if ( (es =pFiler->writeUInt32 (kDxfInt32, [!output CLASS_NAME]::kCurrentVersionNumber)) != Acad::eOk )
		return (es) ;
	//----- Output params
	//.....

	return (pFiler->filerStatus ()) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::dxfInFields (AcDbDxfFiler *pFiler) {
	assertWriteEnabled () ;
	//----- Read parent class information first.
	Acad::ErrorStatus es =[!output BASE_CLASS]::dxfInFields (pFiler) ;
	if ( es != Acad::eOk || !pFiler->atSubclassData (_RXST("[!output CLASS_NAME]")) )
		return (pFiler->filerStatus ()) ;
	//----- Object version number needs to be read first
	struct resbuf rb ;
	pFiler->readItem (&rb) ;
	if ( rb.restype != AcDb::kDxfInt32 ) {
		pFiler->pushBackItem () ;
		pFiler->setError (Acad::eInvalidDxfCode, _RXST("\nError: expected group code %d (version #)"), AcDb::kDxfInt32) ;
		return (pFiler->filerStatus ()) ;
	}
	Adesk::UInt32 version =(Adesk::UInt32)rb.resval.rlong ;
	if ( version > [!output CLASS_NAME]::kCurrentVersionNumber )
		return (Acad::eMakeMeProxy) ;
	//- Uncomment the 2 following lines if your current object implementation cannot
	//- support previous version of that object.
	//if ( version < [!output CLASS_NAME]::kCurrentVersionNumber )
	//	return (Acad::eMakeMeProxy) ;
	//----- Read params in non order dependant manner
	while ( es == Acad::eOk && (es =pFiler->readResBuf (&rb)) == Acad::eOk ) {
		switch ( rb.restype ) {
			//----- Read params by looking at their DXF code (example below)
			//case AcDb::kDxfXCoord:
			//	if ( version == 1 )
			//		cen3d =asPnt3d (rb.resval.rpoint) ;
			//	else 
			//		cen2d =asPnt2d (rb.resval.rpoint) ;
			//	break ;
			//.....

			default:
				//----- An unrecognized group. Push it back so that the subclass can read it again.
				pFiler->pushBackItem () ;
				es =Acad::eEndOfFile ;
				break ;
		}
	}
	//----- At this point the es variable must contain eEndOfFile
	//----- - either from readResBuf() or from pushback. If not,
	//----- it indicates that an error happened and we should
	//----- return immediately.
	if ( es != Acad::eEndOfFile )
		return (Acad::eInvalidResBuf) ;

	return (pFiler->filerStatus ()) ;
}

[!endif]
[!if SELF_REACTOR]
//- SubXXX() methods (self notification)
Acad::ErrorStatus [!output CLASS_NAME]::subOpen (AcDb::OpenMode mode) {
	return ([!output BASE_CLASS]::subOpen (mode)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::subErase (Adesk::Boolean erasing) {
	return ([!output BASE_CLASS]::subErase (erasing)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::subCancel () {
	return ([!output BASE_CLASS]::subCancel ()) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::subClose () {
	return ([!output BASE_CLASS]::subClose ()) ;
}

[!endif]
[!if PERSISTENT_REACTOR]
//- Persistent reactor callbacks
void [!output CLASS_NAME]::openedForModify (const AcDbObject *pDbObj) {
	assertReadEnabled () ;
	[!output BASE_CLASS]::openedForModify (pDbObj) ;
}

void [!output CLASS_NAME]::cancelled (const AcDbObject *pDbObj) {
	assertReadEnabled () ;
	[!output BASE_CLASS]::cancelled (pDbObj) ;
}

void [!output CLASS_NAME]::objectClosed (const AcDbObjectId objId) {
	assertReadEnabled () ;
	[!output BASE_CLASS]::objectClosed (objId) ;
}

void [!output CLASS_NAME]::goodbye (const AcDbObject *pDbObj) {
	assertReadEnabled () ;
	[!output BASE_CLASS]::goodbye (pDbObj) ;
}

void [!output CLASS_NAME]::copied (const AcDbObject *pDbObj, const AcDbObject *pNewObj) {
	assertReadEnabled () ;
	[!output BASE_CLASS]::copied (pDbObj, pNewObj) ;
}

void [!output CLASS_NAME]::erased (const AcDbObject *pDbObj, Adesk::Boolean bErasing) {
	assertReadEnabled () ;
	[!output BASE_CLASS]::erased (pDbObj, bErasing) ;
}

void [!output CLASS_NAME]::modified (const AcDbObject *pDbObj) {
	assertReadEnabled () ;
	[!output BASE_CLASS]::modified (pDbObj) ;
}

void [!output CLASS_NAME]::modifiedGraphics (const AcDbEntity *pDbEnt) {
	assertReadEnabled () ;
	[!output BASE_CLASS]::modifiedGraphics (pDbEnt) ;
}

void [!output CLASS_NAME]::modifiedXData (const AcDbObject *pDbObj) {
	assertReadEnabled () ;
	[!output BASE_CLASS]::modifiedXData (pDbObj) ;
}

void [!output CLASS_NAME]::subObjModified (const AcDbObject *pMainbObj, const AcDbObject *pSubObj) {
	assertReadEnabled () ;
	[!output BASE_CLASS]::subObjModified (pMainbObj, pSubObj) ;
}

void [!output CLASS_NAME]::modifyUndone (const AcDbObject *pDbObj) {
	assertReadEnabled () ;
	[!output BASE_CLASS]::modifyUndone (pDbObj) ;
}

void [!output CLASS_NAME]::reappended (const AcDbObject *pDbObj) {
	assertReadEnabled () ;
	[!output BASE_CLASS]::reappended (pDbObj) ;
}

void [!output CLASS_NAME]::unappended (const AcDbObject *pDbObj) {
	assertReadEnabled () ;
	[!output BASE_CLASS]::unappended (pDbObj) ;
}

[!endif]
[!if DEEPCLONE]
//----- deepClone
Acad::ErrorStatus [!output CLASS_NAME]::subDeepClone (AcDbObject *pOwnerObject, AcDbObject *&pClonedObject, AcDbIdMapping &idMap, Adesk::Boolean isPrimary) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::subDeepClone (pOwnerObject, pClonedObject, idMap, isPrimary)) ;
}

[!endif]
[!if WBLOCKCLONE]
//----- wblockClone
Acad::ErrorStatus [!output CLASS_NAME]::subWblockClone (AcRxObject *pOwnerObject, AcDbObject *&pClonedObject, AcDbIdMapping &idMap, Adesk::Boolean isPrimary) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::subWblockClone (pOwnerObject, pClonedObject, idMap, isPrimary)) ;
}

[!endif]
[!if AUTOMATION]
//- Automation support
Acad::ErrorStatus [!output CLASS_NAME]::subGetClassID (CLSID *pClsid) const {
	assertReadEnabled () ;
	//::CLSIDFromProgID (L"[!output SAFE_PROJECT_NAME].EntityComWrapperInt", pClsid) ;
	//return (Acad::eOk) ;
	return ([!output BASE_CLASS]::subGetClassID (pClsid)) ;
}

[!endif]
[!endif]
[!if ACDBENTITY_PROTOCOLS]
//-----------------------------------------------------------------------------
//----- AcDbEntity protocols
Adesk::Boolean [!output CLASS_NAME]::subWorldDraw (AcGiWorldDraw *mode) {
	assertReadEnabled () ;
[!if !IMPL_VIEWPORT]
	return ([!output BASE_CLASS]::subWorldDraw (mode)) ;
}

[!else]
	//------ Returning Adesk::kFalse here will force viewportDraw() call
	return (Adesk::kFalse) ;
}

void [!output CLASS_NAME]::subViewportDraw (AcGiViewportDraw *mode) {
	assertReadEnabled () ;
	[!output BASE_CLASS]::subViewportDraw (mode) ;
}

Adesk::UInt32 [!output CLASS_NAME]::subViewportDrawLogicalFlags (AcGiViewportDraw *vd) {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::subViewportDrawLogicalFlags (vd)) ;
}
[!endif]

Adesk::UInt32 [!output CLASS_NAME]::subSetAttributes (AcGiDrawableTraits *traits) {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::subSetAttributes (traits)) ;
}

[!if OSNAP_PROTOCOL]
	//- Osnap points protocol
Acad::ErrorStatus [!output CLASS_NAME]::subGetOsnapPoints (
	AcDb::OsnapMode osnapMode,
	Adesk::GsMarker gsSelectionMark,
	const AcGePoint3d &pickPoint,
	const AcGePoint3d &lastPoint,
	const AcGeMatrix3d &viewXform,
	AcGePoint3dArray &snapPoints,
	AcDbIntArray &geomIds) const
{
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::subGetOsnapPoints (osnapMode, gsSelectionMark, pickPoint, lastPoint, viewXform, snapPoints, geomIds)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::subGetOsnapPoints (
	AcDb::OsnapMode osnapMode,
	Adesk::GsMarker gsSelectionMark,
	const AcGePoint3d &pickPoint,
	const AcGePoint3d &lastPoint,
	const AcGeMatrix3d &viewXform,
	AcGePoint3dArray &snapPoints,
	AcDbIntArray &geomIds,
	const AcGeMatrix3d &insertionMat) const
{
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::subGetOsnapPoints (osnapMode, gsSelectionMark, pickPoint, lastPoint, viewXform, snapPoints, geomIds, insertionMat)) ;
}

[!endif]
[!if GRIPPOINT_PROTOCOL]
//- Grip points protocol
Acad::ErrorStatus [!output CLASS_NAME]::subGetGripPoints (
	AcGePoint3dArray &gripPoints, AcDbIntArray &osnapModes, AcDbIntArray &geomIds
) const {
	assertReadEnabled () ;
	//----- This method is never called unless you return eNotImplemented 
	//----- from the new getGripPoints() method below (which is the default implementation)

	return ([!output BASE_CLASS]::subGetGripPoints (gripPoints, osnapModes, geomIds)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::subMoveGripPointsAt (const AcDbIntArray &indices, const AcGeVector3d &offset) {
	assertWriteEnabled () ;
	//----- This method is never called unless you return eNotImplemented 
	//----- from the new moveGripPointsAt() method below (which is the default implementation)

	return ([!output BASE_CLASS]::subMoveGripPointsAt (indices, offset)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::subGetGripPoints (
	AcDbGripDataPtrArray &grips, const double curViewUnitSize, const int gripSize, 
	const AcGeVector3d &curViewDir, const int bitflags
) const {
	assertReadEnabled () ;

	//----- If you return eNotImplemented here, that will force AutoCAD to call
	//----- the older getGripPoints() implementation. The call below may return
	//----- eNotImplemented depending of your base class.
	return ([!output BASE_CLASS]::subGetGripPoints (grips, curViewUnitSize, gripSize, curViewDir, bitflags)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::subMoveGripPointsAt (
	const AcDbVoidPtrArray &gripAppData, const AcGeVector3d &offset,
	const int bitflags
) {
	assertWriteEnabled () ;

	//----- If you return eNotImplemented here, that will force AutoCAD to call
	//----- the older getGripPoints() implementation. The call below may return
	//----- eNotImplemented depending of your base class.
	return ([!output BASE_CLASS]::subMoveGripPointsAt (gripAppData, offset, bitflags)) ;
}
[!endif]

[!endif]
[!if ACDBCURVE_PROTOCOLS]
[!if CURVE_PROTOCOL]
//-----------------------------------------------------------------------------
//----- AcDbCurve protocols
//- Curve property tests.
Adesk::Boolean [!output CLASS_NAME]::isClosed () const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::isClosed ()) ;
}

Adesk::Boolean [!output CLASS_NAME]::isPeriodic () const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::isPeriodic ()) ;
}
      
//- Get planar and start/end geometric properties.
Acad::ErrorStatus [!output CLASS_NAME]::getStartParam (double &param) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getStartParam (param)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getEndParam (double &param) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getEndParam (param)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getStartPoint (AcGePoint3d &point) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getStartPoint (point)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getEndPoint (AcGePoint3d &point) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getEndPoint (point)) ;
}

//- Conversions to/from parametric/world/distance.
Acad::ErrorStatus [!output CLASS_NAME]::getPointAtParam (double param, AcGePoint3d &point) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getPointAtParam (param, point)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getParamAtPoint (const AcGePoint3d &point, double &param) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getParamAtPoint (point, param)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getDistAtParam (double param, double &dist) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getDistAtParam (param, dist)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getParamAtDist (double dist, double &param) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getParamAtDist (dist, param)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getDistAtPoint (const AcGePoint3d &point , double &dist) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getDistAtPoint (point, dist)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getPointAtDist (double dist, AcGePoint3d &point) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getPointAtDist (dist, point)) ;
}

//- Derivative information.
Acad::ErrorStatus [!output CLASS_NAME]::getFirstDeriv (double param, AcGeVector3d &firstDeriv) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getFirstDeriv (param, firstDeriv)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getFirstDeriv  (const AcGePoint3d &point, AcGeVector3d &firstDeriv) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getFirstDeriv (point, firstDeriv)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getSecondDeriv (double param, AcGeVector3d &secDeriv) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getSecondDeriv (param, secDeriv)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getSecondDeriv (const AcGePoint3d &point, AcGeVector3d &secDeriv) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getSecondDeriv (point, secDeriv)) ;
}

//- Closest point on curve.
Acad::ErrorStatus [!output CLASS_NAME]::getClosestPointTo (const AcGePoint3d &givenPnt, AcGePoint3d &pointOnCurve, Adesk::Boolean extend /*=Adesk::kFalse*/) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getClosestPointTo (givenPnt, pointOnCurve, extend)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getClosestPointTo (const AcGePoint3d &givenPnt, const AcGeVector3d &direction, AcGePoint3d &pointOnCurve, Adesk::Boolean extend /*=Adesk::kFalse*/) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getClosestPointTo (givenPnt, direction, pointOnCurve, extend)) ;
}

//- Get a projected copy of the curve.
Acad::ErrorStatus [!output CLASS_NAME]::getOrthoProjectedCurve (const AcGePlane &plane, AcDbCurve *&projCrv) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getOrthoProjectedCurve (plane, projCrv)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getProjectedCurve (const AcGePlane &plane, const AcGeVector3d &projDir, AcDbCurve *&projCrv) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getProjectedCurve (plane, projDir, projCrv)) ;
}

//- Get offset, spline and split copies of the curve.
Acad::ErrorStatus [!output CLASS_NAME]::getOffsetCurves (double offsetDist, AcDbVoidPtrArray &offsetCurves) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getOffsetCurves (offsetDist, offsetCurves)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getOffsetCurvesGivenPlaneNormal (const AcGeVector3d &normal, double offsetDist, AcDbVoidPtrArray &offsetCurves) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getOffsetCurvesGivenPlaneNormal (normal, offsetDist, offsetCurves)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getSpline (AcDbSpline *&spline) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getSpline (spline)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getSplitCurves (const AcGeDoubleArray &params, AcDbVoidPtrArray &curveSegments) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getSplitCurves (params, curveSegments)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::getSplitCurves (const AcGePoint3dArray &points, AcDbVoidPtrArray &curveSegments) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getSplitCurves (points, curveSegments)) ;
}

//- Extend the curve.
Acad::ErrorStatus [!output CLASS_NAME]::extend (double newParam) {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::extend (newParam)) ;
}

Acad::ErrorStatus [!output CLASS_NAME]::extend (Adesk::Boolean extendStart, const AcGePoint3d &toPoint) {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::extend (extendStart, toPoint)) ;
}

//- Area calculation.
Acad::ErrorStatus [!output CLASS_NAME]::getArea (double &area) const {
	assertReadEnabled () ;
	return ([!output BASE_CLASS]::getArea (area)) ;
}

[!endif]
[!endif]
