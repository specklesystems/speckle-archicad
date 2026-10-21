#include "APIFunctionsEnvironment.hpp"

// Framework includes
#include "PrimElementIterator.hpp"
#include "IAPIAttributeAdapterFactory.hpp"
#include "IAPIAttributeAdapter.hpp"
#include "Algorithms.hpp"
#include "RealNumber.h"
#include <math.h>

GSAPI::PrimElementIterator* GSAPI::PrimElementIterator::shapePrimsCallerObject = nullptr;

GSErrCode GSAPI::PrimElementIterator::ShapePrimsCallBack (const API_PrimElement *primElem,
																	   const void *par1,
																	   const void *par2,
																	   const void *par3)
{
	if (shapePrimsCallerObject == nullptr) {
		return APIERR_CANCEL;
	}

	switch (primElem->header.typeID) {
		case API_PrimPointID:
		case API_PrimLineID:
		case API_PrimArcID:
		case API_PrimTextID:
		case API_PrimPLineID:
		case API_PrimTriID:
		case API_PrimPolyID:
		case API_PrimPictID:	{
									GSAPI::PrimElement primElement;
									BNZeroMemory (&primElement, sizeof (primElement));
									primElement.primElem = *primElem;
									if (par1 != nullptr) {
										if (primElem->header.typeID == API_PrimPictID) {
											GSSize par1Size = BMGetHandleSize (reinterpret_cast <GSConstHandle> (par1));
											primElement.shapeProcParam1 = BMAllocatePtr (par1Size, ALLOCATE_CLEAR, 0);
											BNCopyMemory (primElement.shapeProcParam1, *(reinterpret_cast <const GSPtr*> (par1)), par1Size);
										} else {
											// This cast is sooo ugly! Why can't BMGetPtrSize use a const pointer?
											GSSize par1Size = BMGetPtrSize (reinterpret_cast <GSPtr> (const_cast<void*> (par1)));
											primElement.shapeProcParam1 = BMAllocatePtr (par1Size, ALLOCATE_CLEAR, 0);
											BNCopyMemory (primElement.shapeProcParam1, par1, par1Size);
										}
									}
									if (par2 != nullptr) {
										// This cast is sooo ugly! Why can't BMGetPtrSize use a const pointer?
										GSSize par2Size = BMGetPtrSize (reinterpret_cast <GSPtr> (const_cast<void*> (par2)));
										primElement.shapeProcParam2 = BMAllocatePtr (par2Size, ALLOCATE_CLEAR, 0);
										BNCopyMemory (primElement.shapeProcParam2, par2, par2Size);
									}
									if (par3 != nullptr) {
										// This cast is sooo ugly! Why can't BMGetPtrSize use a const pointer?
										GSSize par3Size = BMGetPtrSize (reinterpret_cast <GSPtr> (const_cast<void*> (par3)));
										primElement.shapeProcParam3 = BMAllocatePtr (par3Size, ALLOCATE_CLEAR, 0);
										BNCopyMemory (primElement.shapeProcParam3, par3, par3Size);
									}
									shapePrimsCallerObject->primElements.Push (primElement);

									if (shapePrimsCallerObject->parameters.attributeFactory != nullptr) {
										GSAPI::IAPIAttributeAdapterBase* adapter = shapePrimsCallerObject->parameters.attributeFactory->GetTypeAdapter (primElement,
																																						shapePrimsCallerObject->parameters.currentElement.databaseInfo,
																																						shapePrimsCallerObject->parameters.currentElement.elem.memo);
										adapter->CacheAttributes ();
										if (!(shapePrimsCallerObject->parameters.attributeFactory->GetManagedAdapters ())) {
											delete (adapter);
										}
									}
								}
								break;

		default:				break;	// we don't care about control codes
	}

	return NoError;
}

bool GSAPI::PrimElementIterator::PrimElementLessThanOperator::operator() (const GSAPI::PrimElement& primElem1, const GSAPI::PrimElement& primElem2) const
{
	if (primElem1.primElem.header.typeID < primElem2.primElem.header.typeID) {
		return true;
	} else if (primElem1.primElem.header.typeID > primElem2.primElem.header.typeID) {
		return false;
	}

	switch (primElem1.primElem.header.typeID) {
		case API_PrimPointID:	if (fabs (primElem1.primElem.point.loc.x - primElem2.primElem.point.loc.x) > EPS) {
									return (primElem1.primElem.point.loc.x < primElem2.primElem.point.loc.x);
								} else {
									return (primElem1.primElem.point.loc.y < primElem2.primElem.point.loc.y);
								}

		case API_PrimLineID:	if (fabs (primElem1.primElem.line.c1.x - primElem2.primElem.line.c1.x) > EPS) {
									return (primElem1.primElem.line.c1.x < primElem2.primElem.line.c1.x);
								} else if (fabs (primElem1.primElem.line.c1.y - primElem2.primElem.line.c1.y) > EPS) {
									return (primElem1.primElem.line.c1.y < primElem2.primElem.line.c1.y);
								// else primElem1.primElem.line.c1 == primElem2.primElem.line.c1
								} else if (fabs (primElem1.primElem.line.c2.x - primElem2.primElem.line.c2.x) > EPS) {
									return (primElem1.primElem.line.c2.x < primElem2.primElem.line.c2.x);
								} else {
									return (primElem1.primElem.line.c2.y < primElem2.primElem.line.c2.y);
								}

		case API_PrimArcID:		if (fabs (primElem1.primElem.arc.orig.x - primElem2.primElem.arc.orig.x) > EPS) {
									return (primElem1.primElem.arc.orig.x < primElem2.primElem.arc.orig.x);
								} else if (fabs (primElem1.primElem.arc.orig.y - primElem2.primElem.arc.orig.y) > EPS) {
									return (primElem1.primElem.arc.orig.y < primElem2.primElem.arc.orig.y);
								// else primElem1.primElem.arc.orig == primElem2.primElem.arc.orig
								} else if (fabs (primElem1.primElem.arc.r - primElem2.primElem.arc.r) > EPS) {
									return (primElem1.primElem.arc.r < primElem2.primElem.arc.r);
								// else primElem1.primElem.arc.r == primElem2.primElem.arc.r
								} else if (fabs (primElem1.primElem.arc.begAng - primElem2.primElem.arc.begAng) > EPS) {
									return (primElem1.primElem.arc.begAng < primElem2.primElem.arc.begAng);
								// else primElem1.primElem.arc.begAng == primElem2.primElem.arc.begAng
								} else if (fabs (primElem1.primElem.arc.endAng - primElem2.primElem.arc.endAng) > EPS) {
									return (primElem1.primElem.arc.endAng < primElem2.primElem.arc.endAng);
								// else primElem1.primElem.arc.endAng == primElem2.primElem.arc.endAng
								} else if (fabs (primElem1.primElem.arc.ratio - primElem2.primElem.arc.ratio) > EPS) {
									return (primElem1.primElem.arc.ratio < primElem2.primElem.arc.ratio);
								// else primElem1.primElem.arc.ratio == primElem2.primElem.arc.ratio
								} else {
									return (primElem1.primElem.arc.angle < primElem2.primElem.arc.angle);
								}

		case API_PrimTextID:	if (fabs (primElem1.primElem.text.loc.x - primElem2.primElem.text.loc.x) > EPS) {
									return (primElem1.primElem.text.loc.x < primElem2.primElem.text.loc.x);
								} else if (fabs (primElem1.primElem.text.loc.y - primElem2.primElem.text.loc.y) > EPS) {
									return (primElem1.primElem.text.loc.y < primElem2.primElem.text.loc.y);
								// else primElem1.primElem.text.loc == primElem2.primElem.text.loc
								} else if (fabs (primElem1.primElem.text.angle - primElem2.primElem.text.angle) > EPS) {
									return (primElem1.primElem.text.angle < primElem2.primElem.text.angle);
								// else primElem1.primElem.text.angle == primElem2.primElem.text.angle
								} else if (fabs (primElem1.primElem.text.heightMM - primElem2.primElem.text.heightMM) > EPS) {
									return (primElem1.primElem.text.heightMM < primElem2.primElem.text.heightMM);
								// else primElem1.primElem.text.heightMM == primElem2.primElem.text.heightMM
								} else {
									return (primElem1.primElem.text.widthMM < primElem2.primElem.text.widthMM);
								}

		case API_PrimPLineID:	if (primElem1.primElem.pline.nCoords < primElem2.primElem.pline.nCoords) {
									return true;
								} else if (primElem1.primElem.pline.nCoords > primElem2.primElem.pline.nCoords) {
									return false;
								} else if (primElem1.primElem.pline.nArcs < primElem2.primElem.pline.nArcs) {
									return true;
								} else if (primElem1.primElem.pline.nArcs > primElem2.primElem.pline.nArcs) {
									return false;
								} else {
									API_Coord* primElem1Coords = reinterpret_cast<API_Coord*> (primElem1.shapeProcParam1);
									API_Coord* primElem2Coords = reinterpret_cast<API_Coord*> (primElem2.shapeProcParam1);
									API_PolyArc* primElem1PolyArcs = reinterpret_cast<API_PolyArc*> (primElem1.shapeProcParam3);
									API_PolyArc* primElem2PolyArcs = reinterpret_cast<API_PolyArc*> (primElem2.shapeProcParam3);

									if ((primElem1Coords != nullptr) && (primElem2Coords == nullptr)) {
										return true;
									} else if (primElem1Coords == nullptr) {
										return false;
									} else if ((primElem1.primElem.pline.nArcs > 0) &&
											   (primElem1PolyArcs != nullptr) &&
											   (primElem2PolyArcs == nullptr))
									{
										return true;
									} else if ((primElem1.primElem.pline.nArcs > 0) &&
											   (primElem1PolyArcs == nullptr))
									{
										return false;
									}

									for (Int32 i = 0; i < primElem1.primElem.pline.nCoords; i++) {
										if (fabs (primElem1Coords[i].x - primElem2Coords[i].x) > EPS) {
											return (primElem1Coords[i].x < primElem2Coords[i].x);
										} else if (fabs (primElem1Coords[i].y - primElem2Coords[i].y) > EPS) {
											return (primElem1Coords[i].y < primElem2Coords[i].y);
										}
									}

									for (Int32 i = 0; i < primElem1.primElem.pline.nArcs; i++) {
										if (primElem1PolyArcs[i].begIndex < primElem2PolyArcs[i].begIndex) {
											return true;
										} else if (primElem1PolyArcs[i].begIndex > primElem2PolyArcs[i].begIndex) {
											return false;
										} else if (primElem1PolyArcs[i].endIndex < primElem2PolyArcs[i].endIndex) {
											return true;
										} else if (primElem1PolyArcs[i].endIndex > primElem2PolyArcs[i].endIndex) {
											return false;
										} else if (fabs (primElem1PolyArcs[i].arcAngle - primElem2PolyArcs[i].arcAngle) > EPS) {
											return (primElem1PolyArcs[i].arcAngle < primElem2PolyArcs[i].arcAngle);
										}
									}

									// the two polylines are equal -> let the last coordinate's y value decide
									return (primElem1Coords[primElem1.primElem.pline.nCoords - 1].y < primElem2Coords[primElem1.primElem.pline.nCoords - 1].y);
								}

		case API_PrimTriID:		if (fabs (primElem1.primElem.tri.c[0].x - primElem2.primElem.tri.c[0].x) > EPS) {
									return (primElem1.primElem.tri.c[0].x < primElem2.primElem.tri.c[0].x);
								} else if (fabs (primElem1.primElem.tri.c[0].y - primElem2.primElem.tri.c[0].y) > EPS) {
									return (primElem1.primElem.tri.c[0].y < primElem2.primElem.tri.c[0].y);
								// else primElem1.primElem.tri.c[0] == primElem2.primElem.tri.c[0]
								} else if (fabs (primElem1.primElem.tri.c[1].x - primElem2.primElem.tri.c[1].x) > EPS) {
									return (primElem1.primElem.tri.c[1].x < primElem2.primElem.tri.c[1].x);
								} else if (fabs (primElem1.primElem.tri.c[1].y - primElem2.primElem.tri.c[1].y) > EPS) {
									return (primElem1.primElem.tri.c[1].y < primElem2.primElem.tri.c[1].y);
								// else primElem1.primElem.tri.c[1] == primElem2.primElem.tri.c[1]
								} else if (fabs (primElem1.primElem.tri.c[2].x - primElem2.primElem.tri.c[2].x) > EPS) {
									return (primElem1.primElem.tri.c[2].x < primElem2.primElem.tri.c[2].x);
								} else {
									return (primElem1.primElem.tri.c[2].y < primElem2.primElem.tri.c[2].y);
								}

		case API_PrimPolyID:	if (primElem1.primElem.poly.nCoords < primElem2.primElem.poly.nCoords) {
									return true;
								} else if (primElem1.primElem.poly.nCoords > primElem2.primElem.poly.nCoords) {
									return false;
								} else if (primElem1.primElem.poly.nSubPolys < primElem2.primElem.poly.nSubPolys) {
									return true;
								} else if (primElem1.primElem.poly.nSubPolys > primElem2.primElem.poly.nSubPolys) {
									return false;
								} else if (primElem1.primElem.poly.nArcs < primElem2.primElem.poly.nArcs) {
									return true;
								} else if (primElem1.primElem.poly.nArcs > primElem2.primElem.poly.nArcs) {
									return false;
								} else {
									API_Coord*   primElem1Coords   = reinterpret_cast<API_Coord*> (primElem1.shapeProcParam1);
									API_Coord*   primElem2Coords   = reinterpret_cast<API_Coord*> (primElem2.shapeProcParam1);
									Int32*        primElem1SubPolys = reinterpret_cast<Int32*> (primElem1.shapeProcParam2);
									Int32*        primElem2SubPolys = reinterpret_cast<Int32*> (primElem2.shapeProcParam2);
									API_PolyArc* primElem1PolyArcs = reinterpret_cast<API_PolyArc*> (primElem1.shapeProcParam3);
									API_PolyArc* primElem2PolyArcs = reinterpret_cast<API_PolyArc*> (primElem2.shapeProcParam3);

									if ((primElem1Coords != nullptr) && (primElem2Coords == nullptr)) {
										return true;
									} else if (primElem1Coords == nullptr) {
										return false;
									} else if ((primElem1.primElem.poly.nSubPolys > 0) &&
											   (primElem1SubPolys != nullptr) &&
											   (primElem2SubPolys == nullptr))
									{
										return true;
									} else if ((primElem1.primElem.poly.nSubPolys > 0) &&
											   (primElem1SubPolys == nullptr))
									{
										return false;
									} else if ((primElem1.primElem.poly.nArcs > 0) &&
											   (primElem1PolyArcs != nullptr) &&
											   (primElem2PolyArcs == nullptr))
									{
										return true;
									} else if ((primElem1.primElem.poly.nArcs > 0) &&
											   (primElem1PolyArcs == nullptr))
									{
										return false;
									}

									for (Int32 i = 0; i < primElem1.primElem.poly.nCoords; i++) {
										if (fabs (primElem1Coords[i].x - primElem2Coords[i].x) > EPS) {
											return (primElem1Coords[i].x < primElem2Coords[i].x);
										} else if (fabs (primElem1Coords[i].y - primElem2Coords[i].y) > EPS) {
											return (primElem1Coords[i].y < primElem2Coords[i].y);
										}
									}

									for (Int32 i = 0; i < primElem1.primElem.poly.nSubPolys; i++) {
										if (primElem1SubPolys[i] < primElem2SubPolys[i]) {
											return true;
										} else if (primElem1SubPolys[i] > primElem2SubPolys[i]) {
											return false;
										}
									}

									for (Int32 i = 0; i < primElem1.primElem.poly.nArcs; i++) {
										if (primElem1PolyArcs[i].begIndex < primElem2PolyArcs[i].begIndex) {
											return true;
										} else if (primElem1PolyArcs[i].begIndex > primElem2PolyArcs[i].begIndex) {
											return false;
										} else if (primElem1PolyArcs[i].endIndex < primElem2PolyArcs[i].endIndex) {
											return true;
										} else if (primElem1PolyArcs[i].endIndex > primElem2PolyArcs[i].endIndex) {
											return false;
										} else if (fabs (primElem1PolyArcs[i].arcAngle - primElem2PolyArcs[i].arcAngle) > EPS) {
											return (primElem1PolyArcs[i].arcAngle < primElem2PolyArcs[i].arcAngle);
										}
									}

									// the two polygons are equal -> let the last coordinate's y value decide
									return (primElem1Coords[primElem1.primElem.poly.nCoords - 1].y < primElem2Coords[primElem1.primElem.poly.nCoords - 1].y);
								}

		case API_PrimPictID:	if (fabs (primElem1.primElem.pict.destBox.xMin - primElem2.primElem.pict.destBox.xMin) > EPS) {
									return (primElem1.primElem.pict.destBox.xMin < primElem2.primElem.pict.destBox.xMin);
								} else if (fabs (primElem1.primElem.pict.destBox.yMin - primElem2.primElem.pict.destBox.yMin) > EPS) {
									return (primElem1.primElem.pict.destBox.yMin < primElem2.primElem.pict.destBox.yMin);
								} else if (fabs (primElem1.primElem.pict.destBox.xMax - primElem2.primElem.pict.destBox.xMax) > EPS) {
									return (primElem1.primElem.pict.destBox.xMax < primElem2.primElem.pict.destBox.xMax);
								} else if (fabs (primElem1.primElem.pict.destBox.yMax - primElem2.primElem.pict.destBox.yMax) > EPS) {
									return (primElem1.primElem.pict.destBox.yMax < primElem2.primElem.pict.destBox.yMax);
								// else primElem1.primElem.pict.destBox == primElem2.primElem.pict.destBox
								} else {
									return (primElem1.primElem.pict.rotAngle < primElem2.primElem.pict.rotAngle);
								}

		default:				return false; 	// no control codes should reach here anyway
	}
}

GSAPI::PrimElementIterator::PrimElementIterator (const GSAPI::PrimElementIterator::Parameters& params) :
	parameters (params),
	primIndex (0)
{
	if (parameters.currentElement.elem.element.header.type == API_DrawingID) {
		parameters.currentElement.databaseInfo.typeID = APIWind_DrawingID;
		parameters.currentElement.databaseInfo.linkedElement = parameters.currentElement.elem.element.header.guid;
	}
	// if not end elem but has no primitives
	if ((parameters.currentElement.elem.elemType.typeID >= API_FirstElemType) &&
		(parameters.currentElement.elem.elemType.typeID <= API_LastElemType))
	{
		if (BuildPrimElementList () == 0) {
			++(*this);
		}
	} else {
		BNZeroMemory (&currentElement.elem.element, sizeof (currentElement.elem.element));
		currentElement.elem.memo = nullptr;
	}

	currentElement.elem.elemType = parameters.currentElement.elem.element.header.type;
	currentElement.elem.guid = parameters.currentElement.elem.element.header.guid;
	currentElement.databaseInfo = parameters.currentElement.databaseInfo;
}

GSAPI::PrimElementIterator::~PrimElementIterator ()
{
	if (parameters.currentElement.elem.memo != nullptr) {
		ACAPI_DisposeElemMemoHdls (parameters.currentElement.elem.memo);
		delete (parameters.currentElement.elem.memo);
		parameters.currentElement.elem.memo = nullptr;
	}
	DeletePrimElements ();
}

void GSAPI::PrimElementIterator::DeletePrimElements ()
{
	USize primElementCount = primElements.GetSize ();
	for (USize i = 0; i < primElementCount; i++) {
		if (primElements[i].shapeProcParam1 != nullptr) {
			BMKillPtr (&(primElements[i].shapeProcParam1));
		}
		if (primElements[i].shapeProcParam2 != nullptr) {
			BMKillPtr (&(primElements[i].shapeProcParam2));
		}
		if (primElements[i].shapeProcParam3 != nullptr) {
			BMKillPtr (&(primElements[i].shapeProcParam3));
		}
	}
	primElements.Clear ();
	primIndex = 0;
}

USize GSAPI::PrimElementIterator::BuildPrimElementList ()
{
	DeletePrimElements ();
	shapePrimsCallerObject = this;
	GSErrCode shapeErr = ACAPI_DrawingPrimitive_ShapePrims (parameters.currentElement.elem.element.header, ShapePrimsCallBack);
	if ((shapeErr != NoError) && (shapeErr != APIERR_REFUSEDPAR)) {
		// TODO: throw exception
	}
	shapePrimsCallerObject = nullptr;

    USize primElemCount = primElements.GetSize ();
	if (primElemCount > 0) {
		GS::StableSort (primElements.BeginFast (), primElements.EndFast (), GSAPI::PrimElementIterator::PrimElementLessThanOperator ());
		currentElement.elem.element = primElements[0];
	} else {
		BNZeroMemory (&currentElement.elem.element, sizeof (currentElement.elem.element));
		currentElement.elem.memo = nullptr;
	}

	return primElemCount;
}

GSAPI::PrimElementIterator& GSAPI::PrimElementIterator::operator++ ()
{
	if ((primElements.GetSize () > 0) && (primIndex < primElements.GetSize () - 1)) {
		currentElement.elem.element = primElements[primIndex + 1];
		primIndex++;
	} else {
		bool wasDrawing     = (parameters.currentElement.elem.element.header.type == API_DrawingID);
		bool noPrimElements = true;

		parameters.container.GetNext (parameters.currentElement);
		currentElement.elem.elemType = parameters.currentElement.elem.element.header.type;
		currentElement.elem.guid     = parameters.currentElement.elem.element.header.guid;

		bool isEndElem = ((parameters.currentElement.elem.elemType.typeID < API_FirstElemType) || (parameters.currentElement.elem.elemType.typeID > API_LastElemType));

		// while not end elem but has no primitives
		while (!isEndElem && noPrimElements) {
			if (parameters.currentElement.elem.element.header.type == API_DrawingID) {
				if (parameters.attributeFactory != nullptr) {
					if (wasDrawing) {
						API_DatabaseInfo parentDBInfo;
						BNZeroMemory (&parentDBInfo, sizeof (parentDBInfo));

						ACAPI_Database_GetCurrentDatabase (&parentDBInfo);
						GSAPI::IAPIAttributeAdapterBase* adapter = parameters.attributeFactory->GetTypeAdapter (parameters.currentElement.elem.element, parentDBInfo, parameters.currentElement.elem.memo);
						adapter->CacheAttributes ();
						if (!(parameters.attributeFactory->GetManagedAdapters ())) {
							delete (adapter);
						}
					} else {
						GSAPI::IAPIAttributeAdapterBase* adapter = parameters.attributeFactory->GetTypeAdapter (parameters.currentElement.elem.element, parameters.currentElement.databaseInfo, parameters.currentElement.elem.memo);
						adapter->CacheAttributes ();
						if (!(parameters.attributeFactory->GetManagedAdapters ())) {
							delete (adapter);
						}
						wasDrawing = true;
					}
				}
				parameters.currentElement.databaseInfo.typeID = APIWind_DrawingID;
				parameters.currentElement.databaseInfo.linkedElement = parameters.currentElement.elem.element.header.guid;
				currentElement.databaseInfo = parameters.currentElement.databaseInfo;
			} else if (wasDrawing) {
				API_DatabaseInfo currentDBInfo;
				BNZeroMemory (&currentDBInfo, sizeof (currentDBInfo));

				ACAPI_Database_GetCurrentDatabase (&currentDBInfo);
				parameters.currentElement.databaseInfo.typeID = currentDBInfo.typeID;
				parameters.currentElement.databaseInfo.index  = currentDBInfo.index;
				parameters.currentElement.databaseInfo.linkedElement = currentDBInfo.linkedElement;
				currentElement.databaseInfo = parameters.currentElement.databaseInfo;

				if (parameters.attributeFactory != nullptr) {
					GSAPI::IAPIAttributeAdapterBase* adapter = parameters.attributeFactory->GetTypeAdapter (parameters.currentElement.elem.element, parameters.currentElement.databaseInfo, parameters.currentElement.elem.memo);
					adapter->CacheAttributes ();
					if (!(parameters.attributeFactory->GetManagedAdapters ())) {
						delete (adapter);
					}
				}
				wasDrawing = false;
			} else {
				if (parameters.attributeFactory != nullptr) {
					GSAPI::IAPIAttributeAdapterBase* adapter = parameters.attributeFactory->GetTypeAdapter (parameters.currentElement.elem.element, parameters.currentElement.databaseInfo, parameters.currentElement.elem.memo);
					adapter->CacheAttributes ();
					if (!(parameters.attributeFactory->GetManagedAdapters ())) {
						delete (adapter);
					}
				}
			}

			if (BuildPrimElementList () != 0) {
				noPrimElements = false;
			} else {
				parameters.container.GetNext (parameters.currentElement);
				currentElement.elem.elemType = parameters.currentElement.elem.element.header.type;
				currentElement.elem.guid     = parameters.currentElement.elem.element.header.guid;
			}

			isEndElem = ((parameters.currentElement.elem.elemType.typeID < API_FirstElemType) || (parameters.currentElement.elem.elemType.typeID > API_LastElemType));
		}

		if (isEndElem && (parameters.currentElement.databaseInfo.typeID == APIWind_DrawingID)) {
			API_DatabaseInfo currentDBInfo;
			BNZeroMemory (&currentDBInfo, sizeof (currentDBInfo));

			ACAPI_Database_GetCurrentDatabase (&currentDBInfo);
			parameters.currentElement.databaseInfo.typeID = currentDBInfo.typeID;
			parameters.currentElement.databaseInfo.index  = currentDBInfo.index;
			parameters.currentElement.databaseInfo.linkedElement = currentDBInfo.linkedElement;
			currentElement.databaseInfo = parameters.currentElement.databaseInfo;
		}

		if (isEndElem) {
			DeletePrimElements ();
			BNZeroMemory (&currentElement.elem.element, sizeof (currentElement.elem.element));
			currentElement.elem.memo = nullptr;
		}
	}

	return *this;
}

GSAPI::PrimElementIterator GSAPI::PrimElementIterator::operator++ (int)
{
	PrimElementIterator temp = *this;
	++(*this);
	return temp;
}

bool GSAPI::PrimElementIterator::operator== (const GSAPI::PrimElementIterator& it) const
{
    if (((&(it.parameters.container)) == (&(parameters.container))) &&
        (it.parameters.currentElement.elem.elemType == parameters.currentElement.elem.elemType) &&
        (it.parameters.currentElement.elem.guid == parameters.currentElement.elem.guid) &&
		(it.primIndex == primIndex) &&
		(it.currentElement.databaseInfo == currentElement.databaseInfo) &&
		(it.currentElement.elem.element.primElem.header.typeID == currentElement.elem.element.primElem.header.typeID) &&
		(it.primElements.GetSize () == primElements.GetSize ()))
    {
        return true;
    } else {
        return false;
    }
}

bool GSAPI::PrimElementIterator::operator!= (const GSAPI::PrimElementIterator& it) const
{
	return (!((*this)==it));
}

const GSAPI::IteratorElem <GSAPI::Element<GSAPI::PrimElement> >* GSAPI::PrimElementIterator::operator-> ()
{
	return &currentElement;
}

const GSAPI::IteratorElem <GSAPI::Element<GSAPI::PrimElement> >& GSAPI::PrimElementIterator::operator* ()
{
	return currentElement;
}
