#ifndef GDL_DICT_FIELDS_HPP
#define	GDL_DICT_FIELDS_HPP

#pragma once

#include "GDLExport.h"
#include "GDLDictionary.hpp"

namespace GDLDictFields {

static const GDL::FieldName userData ("userData");

}

namespace GDLCoord2DFields {

static const GDL::FieldName x ("x");
static const GDL::DictionaryPath xPath (x);

static const GDL::FieldName y ("y");
static const GDL::DictionaryPath yPath (y);

}

namespace GDLPolyDictFields {

static const GDL::FieldName contour ("contour");
static const GDL::DictionaryPath contourPath (contour);

static const GDL::FieldName isClosed ("isClosed");
static const GDL::DictionaryPath isClosedPath (isClosed);

static const GDL::FieldName edges ("edges");
static const GDL::DictionaryPath edgesPath (edges);

static const GDL::FieldName type ("type");
static const GDL::DictionaryPath typePath (type);

static const GDL::FieldName begPoint ("begPoint");
static const GDL::DictionaryPath begPointPath (begPoint);

static const GDL::FieldName arcAngle ("arcAngle");
static const GDL::DictionaryPath arcAnglePath (arcAngle);

static const GDL::FieldName holes ("holes");
static const GDL::DictionaryPath holesPath (holes);

static const GDL::FieldName useEdgeInfo ("useEdgeInfo");
static const GDL::DictionaryPath useEdgeInfoPath (useEdgeInfo);

static const GDL::FieldName defaultInhEdgeInfo ("defaultInhEdgeInfo");
static const GDL::DictionaryPath defaultInhEdgeInfoPath (defaultInhEdgeInfo);

static const GDL::FieldName edgeInfo ("edgeInfo");
static const GDL::DictionaryPath edgeInfoPath (edgeInfo);

}

namespace GDLDictFields {

static const GDL::FieldName toHomeStory ("toHomeStory");
static const GDL::DictionaryPath toHomeStoryPath (toHomeStory);

static const GDL::FieldName toProjectZero ("toProjectZero");
static const GDL::DictionaryPath toProjectZeroPath (toProjectZero);

static const GDL::FieldName toWallBottom ("toWallBottom");
static const GDL::DictionaryPath toWallBottomPath (toWallBottom);

static const GDL::FieldName toWallTop ("toWallTop");
static const GDL::DictionaryPath toWallTopPath (toWallTop);

static const GDL::FieldName breakMarks ("breakMarks");
static const GDL::DictionaryPath breakMarksPath (breakMarks);

static const GDL::FieldName isVisible ("isVisible");
static const GDL::DictionaryPath isVisiblePath (isVisible);

}

namespace GDLBoundingBoxFields
{

static const GDL::FieldName xmin ("xmin");
static const GDL::DictionaryPath xminPath (xmin);

static const GDL::FieldName ymin ("ymin");
static const GDL::DictionaryPath yminPath (ymin);

static const GDL::FieldName xmax ("xmax");
static const GDL::DictionaryPath xmaxPath (xmax);

static const GDL::FieldName ymax ("ymax");
static const GDL::DictionaryPath ymaxPath (ymax);

}


namespace GDLSegmentedAssemblyDictFields {

static const GDL::FieldName	segmentList ("segments");
static const GDL::DictionaryPath segmentListPath (segmentList);

static const GDL::FieldName segment_Curvature ("curvature");
static const GDL::DictionaryPath segment_CurvaturePath (segment_Curvature);

static const GDL::FieldName segment_Tapered ("tapered");
static const GDL::DictionaryPath segment_TaperedPath (segment_Tapered);

static const GDL::FieldName segment_CrossSection ("crossSection");
static const GDL::DictionaryPath segment_CrossSectionPath (segment_CrossSection);

static const GDL::FieldName segment_CrossSectionType ("type");
static const GDL::DictionaryPath segment_CrossSectionTypePath ({segment_CrossSection, segment_CrossSectionType});

static const GDL::FieldName segment_CrossSectionStartWidth ("startWidth");
static const GDL::DictionaryPath segment_CrossSectionStartWidthPath ({segment_CrossSection, segment_CrossSectionStartWidth});

static const GDL::FieldName segment_CrossSectionEndWidth ("endWidth");
static const GDL::DictionaryPath segment_CrossSectionEndWidthPath ({segment_CrossSection, segment_CrossSectionEndWidth});

static const GDL::FieldName segment_CrossSectionStartHeight ("startHeight");
static const GDL::DictionaryPath segment_CrossSectionStartHeightPath ({segment_CrossSection, segment_CrossSectionStartHeight});

static const GDL::FieldName segment_CrossSectionEndHeight ("endHeight");
static const GDL::DictionaryPath segment_CrossSectionEndHeightPath ({segment_CrossSection, segment_CrossSectionEndHeight});

static const GDL::FieldName segment_RefLineLength ("refLineLength");
static const GDL::DictionaryPath segment_RefLineLengthPath (segment_RefLineLength);
}

namespace GDLGeometryDictFields {

static const GDL::FieldName referenceLine2D ("referenceLine2D");
static const GDL::DictionaryPath referenceLine2DPath (referenceLine2D);

static const GDL::FieldName polygon2D ("polygon2D");
static const GDL::DictionaryPath polygon2DPath (polygon2D);

static const GDL::FieldName boundingBox2D ("boundingBox2D");
static const GDL::DictionaryPath boundingBox2DPath (boundingBox2D);

static const GDL::FieldName polyLine2D ("polyLine2D");
static const GDL::DictionaryPath polyLine2DPath (polyLine2D);

}

namespace GDLSymbPosFromSurveyPointFields
{

static const GDL::FieldName x ("x");
static const GDL::DictionaryPath xPath (x);

static const GDL::FieldName y ("y");
static const GDL::DictionaryPath yPath (y);

static const GDL::FieldName z ("z");
static const GDL::DictionaryPath zPath (z);

}

namespace GDLPropertyDictFields {

static const GDL::FieldName componentCollectMode ("collectMode");

static const GDL::FieldName	componentId ("componentId");
static const GDL::FieldName componentIdList ("componentIds");
static const GDL::FieldName componentId_uniqueId ("id");

static const GDL::FieldName	propertyIdList ("propertyIds");
static const GDL::FieldName	propertyId_uniqueId ("id");

static const GDL::FieldName	propertyValueList ("propertyValues");
static const GDL::FieldName propertyValue_Status ("value_status");
static const GDL::FieldName propertyValue_Type ("type");
static const GDL::FieldName propertyValue_ArrValue ("value");

static const GDL::FieldName propertyType ("propertyType");
static const GDL::FieldName treeDepth ("treeDepth");
static const GDL::FieldName propertyTree ("propertyTree");

}


namespace GDLMEPDictFields {

static const GDL::FieldName symbolFill ("symbolFill");
static const GDL::FieldName centerLine ("centerLine");
static const GDL::FieldName symbolFillType ("type");
static const GDL::FieldName symbolFillPen ("pen");
static const GDL::FieldName symbolFillBGPen ("bgPen");
static const GDL::FieldName centerLineLineType ("linetype");
static const GDL::FieldName centerLinePen ("pen");
static const GDL::FieldName centerLineBShow ("bShow");
static const GDL::FieldName insulation ("insulation");
static const GDL::FieldName insulationSurface ("surface");
static const GDL::FieldName surface ("surface");
static const GDL::FieldName penContour ("penContour");

static const GDL::FieldName floorPlanAndSection ("floorPlanAndSection");
static const GDL::FieldName cutPlanePosition ("cutPlanePosition");
static const GDL::FieldName floorPlanDisplay ("floorPlanDisplay");
static const GDL::FieldName showProjection ("showProjection");

static const GDL::FieldName overheadLine ("overheadLine");
static const GDL::FieldName lineType ("lineType");
static const GDL::FieldName pen ("pen");

static const GDL::FieldName x ("x");
static const GDL::FieldName y ("y");
static const GDL::FieldName z ("z");

static const GDL::FieldName controlPoints ("controlPoints");
static const GDL::FieldName flexSegmentCoords ("flexSegmentCoords");
static const GDL::FieldName normals ("normals");
static const GDL::FieldName tangents ("tangents");

static const GDL::FieldName resolution ("resolution");
}

#endif	//GDL_DICT_FIELDS_HPP