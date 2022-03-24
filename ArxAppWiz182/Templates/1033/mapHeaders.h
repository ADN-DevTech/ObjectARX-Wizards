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
//----- mapHeaders.h : includes MAP headers files
//-----------------------------------------------------------------------------
#pragma once

[!if MAP_API_2007 || MAP_API_2008]
#include "AcDbObjectFilter.h"
#include "AcMapAnnotationManager.h"
#include "AcMapClassificationManager.h"
#include "AcMapDeclareMembers.h"
#include "AcMapGeometryPE.h"
#include "AcMapIEColumn.h"
#include "AcMapIEColumnIterator.h"
#include "AcMapIEEnum.h"
#include "AcMapIEExporter.h"
#include "AcMapIEExpressionTargetIterator.h"
#include "AcMapIEFormat.h"
#include "AcMapIEFormatIterator.h"
#include "AcMapIEGlobal.h"
#include "AcMapIEImporter.h"
#include "AcMapIEInputLayer.h"
#include "AcMapIEInputLayerIterator.h"
#include "AcMapIENameValueIterator.h"
#include "AcMapIEReactor.h"
#include "AcMapMbError.h"
#include "AcMapMbMapBook.h"
#include "AcMapMbMapBookManager.h"
#include "AcMapMbMapBookReactor.h"
#include "AcMapMbMapSheetLayoutSettings.h"
#include "AcMapMbMapSheetTemplate.h"
#include "AcMapMbTile.h"
#include "AcMapMbTileGenerator.h"
#include "AcMapMbTileGeneratorSettings.h"
#include "AcMapMbTileGeneratorSettingsArea.h"
#include "AcMapMbTileGeneratorSettingsGrid.h"
#include "AcMapMbTileGeneratorSettingsManual.h"
#include "AcMapMBTileNameGenerator.h"
#include "AcMapMBTileNameGeneratorData.h"
#include "AcMapMBTileNameGeneratorGrid.h"
#include "AcMapMBTileNameGeneratorSequence.h"
#include "AcMapMbTileNameGeneratorSettings.h"
#include "AcMapMbTileNameGeneratorSettingsData.h"
#include "AcMapMbTileNameGeneratorSettingsGrid.h"
#include "AcMapMbTileNameGeneratorSettingsSequence.h"
#include "AcMapMbTileSet.h"
#include "AcMapObjClass.h"
#include "AcMapObjClassDefinition.h"
#include "AcMapObjClassProperty.h"
#include "AcMapObjClassReactor.h"
#include "AcMapObjClassSystem.h"
#include "AcMapOracleConnection.h"
#include "AcMapOracleExport.h"
#include "AcMapOracleIdentification.h"
#include "AcMapOracleImport.h"
#include "AcMapOracleQuery.h"
#include "AcMapOracleReactor.h"
#include "AcMapQueryPE.h"
#include "AcMapTopoFullEdge.h"
#include "AcMapTopoHalfEdge.h"
#include "AcMapTopoIterator.h"
#include "AcMapTopology.h"
#include "AcMapTopologyCommonDef.h"
#include "AcMapTopologyManager.h"
#include "AcMapTopoNode.h"
#include "AcMapTopoObject.h"
#include "AcMapTopoPolygon.h"
#include "AcMapTopoRing.h"
#include "AcMapUtilities.h"
#include "adeads.h"
#include "AdMapOracleConnection.h"
#include "AdMapOracleExport.h"
#include "AdMapOracleIdentification.h"
#include "AdMapOracleImport.h"
#include "AdMapOracleProject.h"
#include "AdMapOracleQuery.h"
#include "AdMapOracleReactor.h"
#include "dbMPolygon.h"
#include "DmAdeQueryElement.h"
#include "DmDefaultStyle.h"
#include "DmDisplayElement.h"
#include "DmDisplayItem.h"
#include "DmDisplayManagement.h"
#include "DmDisplayStyle.h"
#include "DmEntityStyle.h"
#include "DmFeatureElement.h"
#include "DmGroup.h"
#include "DmLayerElement.h"
#include "DmLegend.h"
#include "DmMap.h"
#include "DmMapManager.h"
#include "DmProjectQueryElement.h"
#include "DmRasterElement.h"
#include "DmRasterStyle.h"
#include "DMReactor.h"
#include "DmSEAnnotationStyle.h"
#include "DmSEHatchStyle.h"
#include "DmSETextStyle.h"
#include "DmStyleCategory.h"
#include "DmStyleEntStyle.h"
#include "DmStyleLibrary.h"
#include "DmStyleReference.h"
#include "DmThematicStyle.h"
#include "DmThematicTable.h"
#include "DmTopoElement.h"
#include "DmTopoQueryElement.h"
#include "mapads.h"
#include "MapAlteration.h"
#include "MapArxApi.h"
#include "MapBoundary.h"
#include "MapColl.h"
#include "MapConstants.h"
#include "MapDataSources.h"
#include "MapHostApplicationServices.h"
#include "MapImpProject.h"
#include "MapObjectId.h"
#include "MapODColumn.h"
#include "MapODDefinition.h"
#include "MapODIterator.h"
#include "MapODRecord.h"
#include "MapODTable.h"
#include "MapProj.h"
#include "MapQuery.h"
#include "MapReactors.h"
#include "MapSession.h"
#include "MapStringArray.h"
#include "MapTemplate.h"
#include "MapValue.h"
#include "mapvcorevalue.h"
#include "mapvdb.h"
#include "OracleExports.h"
#include "topoads.h"

#pragma comment (lib, "maparx.lib")
#pragma comment (lib, "AcMapAnnotUi.lib")
#pragma comment (lib, "AcDbMPolygon17.lib")
#pragma comment (lib, "AcMapDisplayManagement.lib")
#pragma comment (lib, "AcMapImpExpUI.lib")
#pragma comment (lib, "AcMapMapBook.lib")
#pragma comment (lib, "AcMapObjClassApi.lib")
#pragma comment (lib, "AcMapOrclApi.lib")
#pragma comment (lib, "AcMapWorkspace.lib")
#pragma comment (lib, "adeadsrx.lib")
#pragma comment (lib, "AdMapOrclApi.lib")
#pragma comment (lib, "mapads.lib")
#pragma comment (lib, "mapvdb.lib")
#pragma comment (lib, "topoadsrx.lib")

[!endif]
