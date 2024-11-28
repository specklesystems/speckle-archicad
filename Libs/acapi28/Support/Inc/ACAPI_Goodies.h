#ifndef ACAPI_GOODIES_H
#define	ACAPI_GOODIES_H

// STL
#include <unordered_set>
#include <unordered_map>

// GSRoot
#include "GSRoot.hpp"
#include "Array.hpp"
#include "PagedArray.hpp"
#include "UniString.hpp"
#include "Owner.hpp"
#include "SharedPtr.hpp"

// own
#include "APICalls.h"
#include "APIdefs.h"
#include "APIdefs_SurfaceType.h"
#include "APIdefs_Goodies.h"



/**
 * @brief Determines whether the string is a GDL keyword or reserved symbol
 * @ingroup LibraryManagement
 * @param str [in] a string to check as a GDL keyword or reserved symbol
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - str is nullptr
 * 			- APIERR_GENERAL - the string is a valid GDL keyword or reserved symbol
 * @remarks This function is used to check whether the given string is a reserved GDL keyword or symbol; or fulfills or not certain requirements to become one.
 * 			By general the function returns NoError if the passed string can be used in a GDL script as an own identifier. For example if your creates a LibraryPart with scripts installed, and some part of the script is generated on the fly, it is a good idea to check the components for usability.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryManagement_UsableGDLString-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_UsableGDLString (const char* str);


/**
 * @brief Calculates the sun position in a given place.
 * @ingroup GeoLocation
 * @since Archicad 26
 * @param placeInfo [in/out] Parameters of the sun place.
 * 					|API_PlaceInfo||
 * 					|--- |--- |
 * 					|longitude|required, longitude|
 * 					|latitude|required, latitude|
 * 					|sumTime|required, daylight saving on/off|
 * 					|year|required, year|
 * 					|month|required, month|
 * 					|day|required, day|
 * 					|hour|required, hour|
 * 					|minute|required, minute|
 * 					|second|required, second|
 * 					|time zone|required, time zone in minutes|
 * 					|north|required, north direction|
 * 					|sunAngXY|out, the sun angle|
 * 					|sunAngZ|out, the sun angle|
 *
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - no open project
 * 			- APIERR_BADPARS - placeInfo is `nullptr` or contains invalid data
 * @remarks This function is used get the sun angles to in a custom place. The sun angles are calculated in a
 * 			given place and on a certain day and time. The calculated angles are returned in the `sunAngXY` and `sunAngZ`
 * 			fields of the structure. Refer to the @ref ACAPI_GeoLocation_GetPlaceSets function to get the actual location
 * 			and date parameters.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_GeoLocation_CalcSunOnPlace-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_GeoLocation_CalcSunOnPlace (API_PlaceInfo* placeInfo);


/**
 * @brief Searches an element by a coordinate.
 * @ingroup Element
 * @param elemSearchPars [in] Parameters of searching
 * @param foundElement [out] guid of the found element
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - searchPars is nullptr or guid is nullptr, or no element is found matching the given parameters.
 * 			- APIERR_REFUSEDPAR - The element to be searched is not a polygonal element.
 * @remarks This function is used to search a polygonal element by a coordinate.
 * 			Refer to the @ref API_ElemSearchPars for the parametrization and more details.
 * 			In the GUID was moved from the third parameter to the second.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_SearchElementByCoord-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_SearchElementByCoord (const API_ElemSearchPars* elemSearchPars, API_Guid* foundElement);


/**
 * @brief Converts a picture into another image format.
 * @ingroup Conversion
 * @param oldPict [in] Parameters of the source picture. The old format and data must be passed in the storageFormat and pictHdl fields, respectively.
 * @param newPict [in/out] Parameters of the destination picture. The new format of the picture must be passed in the storageFormat field. The pictHdl field will be returned according to the specified format.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - parameters are nullptr or storage formats are invalid
 * 			- APIERR_MEMFULL - Not enough memory to create the new pictHdl
 * @remarks This function is used to convert a picture from one standard image format to an other. Any picture format can be passed in both the input and output parameters.
 * 			See also @ref ACAPI_Conversion_ConvertMimePicture if you want to specify the image format using MIME types.
 */
__APIEXPORT GSErrCode ACAPI_Conversion_ConvertPicture (API_PictureHandle* oldPict, API_PictureHandle* newPict);


/**
 * @brief Converts a picture into another image format using MIME types.
 * @ingroup Conversion
 * @param mimePicture [in/out] Parameters of the source and the destination picture.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The input parameters are not given correctly (see @ref API_MimePicture)
 * 			- APIERR_MEMFULL - Not enough memory to create the new pictHdl
 * @remarks This function is used to convert a picture from one standard image format to an other. The image formats are specified with MIME (Multi-purpose Internet Mail Extensions) types.
 * 			MIME types of the most commonly used image formats:
 * 			|Image type|MIME type|
 * 			|--- |--- |
 * 			|Windows Bitmap|image/x-bmp|
 * 			|GIF|image/gif|
 * 			|TIFF|image/tiff|
 * 			|JPEG|image/jpeg|
 * 			|Pict|image/pict|
 * 			|SGI|image/x-sgi|
 * 			|Photoshop Image|image/x-photoshop|
 * 			|PNG|image/png|
 * 			|MacPaint Image|image/x-macpaint|
 * 			|Truevision TGA|image/x-targa|
 * 			|QuickTime Image|image/x-quicktime|
 *
 * 			You can pass a special output type "vnd/DIB" to create a device independent bitmap on Windows.
 * 			Conversion from one pixel depth to another is not supported at the moment.
 * 			You can use the @ref ACAPI_Conversion_ConvertPicture goody function for converting images with @ref API_PictureFormat identifiers rather than MIME types.
 * 			Remember to dispose the returned outputHdl when it is not needed any more.
 * 			See more options at the description of the @ref API_MimePicture structure.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Conversion_ConvertMimePicture-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Conversion_ConvertMimePicture (API_MimePicture* mimePicture);


/**
 * @brief Opens a Library Part parameter list to edit.
 * @ingroup LibraryPart
 * @param paramOwner [in] Reference to the owner of the parameter handle which should be edited
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - paramOwner is nullptr or invalid parameters are passed
 * 			- APIERR_GENERAL - the library part do not has parameters
 * @remarks This function is used to prepare a parameter list to edit.
 * 			Generally to change a parameter of a parameter list is a very complex task. It is because the @ref API_AddParType structure is quite complex, especially in case of array parameters, however this problem can be handled. Another issue is the parameter script. This script sets up rules and links which must be followed to provide a consistent parameter set, while editing it. There is no possibility to handle this issue in an addon.
 * 			The only way to ensure full parameter consistency while changing a value of a Library Part parameter is to use the functions provided for this operation. If you manipulate the @ref API_AddParType handle directly, the parameter list may become invalid.
 * 			The function set is:
 * 			- @ref ACAPI_LibraryPart_OpenParameters
 * 			- @ref ACAPI_LibraryPart_ChangeAParameter
 * 			- @ref ACAPI_LibraryPart_GetActParameters
 * 			- @ref ACAPI_LibraryPart_GetParamValues
 * 			- @ref ACAPI_LibraryPart_CloseParameters
 * 			Once you want to change a parameter you should open the parameter list with the @ref ACAPI_LibraryPart_OpenParameters function. You can specify here various targets to work on:
 * 			- the parameters of a placed element (Library Part instance)
 * 			- the default parameters of an element (default tool settings)
 * 			- the default parameters of a Library Part itself
 * 			Refer to the @ref API_ParamOwnerType structure how to specify the required target of operation.
 * 			After you opened the the parameter list to edit you can use the @ref ACAPI_LibraryPart_ChangeAParameter function to change a value of a parameter. The reference to a variable can be either the name of the variable or its index.
 * 			You can get the current (modified) parameter list in API form (API_AddParType handle) any time by calling the @ref ACAPI_LibraryPart_GetActParameters function.
 * 			You can check the possible values of a parameter (as defined in the Parameter Script of the Library Part) in API form (API_GetParamValuesType handle) any time by calling the @ref ACAPI_LibraryPart_GetParamValues function.
 * 			When you have finished working on a parameter list you should call the @ref ACAPI_LibraryPart_CloseParameters function to free any associated resources allocated by the server application.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_OpenParameters-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_OpenParameters (API_ParamOwnerType* paramOwner);


/**
 * @brief Returns the possible values defined for a Library Part parameter.
 * @ingroup LibraryPart
 * @param getValues [out] the value list for the given parameter
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - theParams is nullptr
 * 			- APIERR_BADNAME - The parameter specified by its name was not found in the open library part
 * 			- APIERR_BADINDEX - The parameter specified by its index was not found in the open library part
 * 			- APIERR_NOTINIT - No open parameter list
 * @remarks This function is used to get the possible values for a given parameter. Refer to the @ref API_GetParamValuesType structure to get further details.
 * 			Do not forget to dispose the strValues and the realValues handles when they are not needed any more.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_GetParamValues-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetParamValues (API_GetParamValuesType* getValues);


/**
 * @brief Changes a value in an opened Library Part parameter list.
 * @ingroup LibraryPart
 * @param changeParamType [in] The Library Part parameter (variable) to change the value of it.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - chgParam is nullptr or the variable reference is invalid
 * 			- APIERR_NOTINIT - there is no parameter list opened
 * @remarks This function is used to change a Library Part parameter. Refer to the @ref API_ChangeParamType structure to get details on the parametrization possibilities.
 * 			Use this function after a parameter list has been opened by the @ref ACAPI_LibraryPart_OpenParameters function. Refer to that function to get more details on this topics.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_ChangeAParameter-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_ChangeAParameter (API_ChangeParamType* changeParamType);


/**
 * @brief Returns the actual (edited) values of a Library Part parameter list opened to edit.
 * @ingroup LibraryPart
 * @param theParams [out] the modified parameter list
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - theParams is nullptr
 * 			- APIERR_NOTINIT - there is no parameter list opened
 * @remarks This function is used to get the actual parameters modified by the @ref ACAPI_LibraryPart_ChangeAParameter function. Refer to the @ref API_GetParamsType structure to get further details.
 * 			Do not forget to dispose the params handle when it is not needed any more. Refer to the @ref ACAPI_DisposeAddParHdl to do that.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_GetActParameters-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetActParameters (API_GetParamsType* theParams);


/**
 * @brief Closes the Library Part parameter list opened for editing.
 * @ingroup LibraryPart
 * @return
 * 			- NoError - The function always returns NoError.
 * @remarks This function is used to close the parameter list of a Library Part opened for editing. Refer to the @ref ACAPI_LibraryPart_OpenParameters function to get more details on this topics.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_LibraryPart_CloseParameters-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_CloseParameters ();


/**
 * @brief Inserts a node into a polygon.
 * @ingroup Polygon
 * @param elementMemo [in/out] The polygon data.
 * @param nodeIndex [in] node index (subindex of the element) to insert a new node after
 * @param coord [in] The coordinate of the new node.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr or invalid nodeIndex passed or memo is not initialized
 * 			- APIERR_MEMFULL - low memory condition
 * 			- APIERR_IRREGULARPOLY - Input polygon or polyline is irregular.
 * @remarks This function is used to insert a new node into a polygon passed in an @ref API_ElementMemo structure.
 * 			This function inserts the given coordinate into the right place.
 * 			Refer to the @ref API_Polygon structure to have more details on the polygon data structure. The coords, pends, parcs and vertexIDs handles in the @ref API_ElementMemo structure must be initialized.
 * 			Note that other memo handles are not touched. In the case the polygon belongs to a roof with side angles initialized, it must be aligned manually.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Polygon_InsertPolyNode-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Polygon_InsertPolyNode (API_ElementMemo* elementMemo, Int32* nodeIndex, API_Coord* coord);


/**
 * @brief Deletes a node from a polygon.
 * @ingroup Polygon
 * @param memo [in/out] The polygon data.
 * @param inIndex [in] node index (subindex of the element) to delete
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr or invalid nodeIndex passed or memo is not initialized
 * 			- APIERR_MEMFULL - low memory condition
 * 			- APIERR_IRREGULARPOLY - Input polygon or polyline is irregular.
 * @remarks This function is used to delete a node from a polygon passed in an @ref API_ElementMemo structure.
 * 			Refer to the @ref API_Polygon structure to have more details on the polygon data structure. The coords, pends, parcs and vertexIDs handles in the @ref API_ElementMemo structure must be initialized.
 * 			Note that other memo handles are not touched. In the case the polygon belongs to a roof with side angles initialized, it must be aligned manually.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Polygon_DeletePolyNode-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Polygon_DeletePolyNode (API_ElementMemo* memo, Int32* inIndex);


/**
 * @brief Inserts a whole subpolygon (hole) into a polygon.
 * @ingroup Polygon
 * @param memo [in/out] The polygon data.
 * @param insMemo [in] Data of the new subpolygon.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr or memo or insMemo is not initialized
 * 			- APIERR_MEMFULL - low memory condition
 * 			- APIERR_IRREGULARPOLY - Input polygon is irregular.
 * @remarks This function is used to insert a new subpolygon (hole) into a polygon passed in an @ref API_ElementMemo structure. The shape of the new hole should be passed in the insMemo parameter.
 * 			Refer to the @ref API_Polygon structure to have more details on the polygon data structure. The coords, pends, parcs and vertexIDs handles in the @ref API_ElementMemo structure must be initialized in the case of the memo parameter. The vertexID and pends handles are ignored in the insMemo parameter.
 * 			The function places the new hole to the and of the contour list.
 * 			Note that other memo handles are not touched. In the case the polygon belongs to a roof with side angles initialized, it must be aligned manually.
 */
__APIEXPORT GSErrCode ACAPI_Polygon_InsertSubPoly (API_ElementMemo* memo, API_ElementMemo* insMemo);


/**
 * @brief Deletes a whole subpolygon (hole) from a polygon.
 * @ingroup Polygon
 * @param elementMemo [in/out] The polygon data.
 * @param subPolyIndex [in] subpolygon index to delete
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr or invalid subPolyIndex passed
 * 			- APIERR_MEMFULL - low memory condition
 * 			- APIERR_IRREGULARPOLY - Input polygon is irregular.
 * @remarks This function is used to delete a whole subpolygon (hole) from a polygon passed in an @ref API_ElementMemo structure.
 * 			Refer to the @ref API_Polygon structure to have more details on the polygon data structure. The coords, pends, parcs and vertexIDs handles in the @ref API_ElementMemo structure must be initialized.
 * 			Note that other memo handles are not touched. In the case the polygon belongs to a roof with side angles initialized, it must be aligned manually.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Polygon_DeleteSubPoly-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Polygon_DeleteSubPoly (API_ElementMemo* elementMemo, Int32* subPolyIndex);


/**
 * @brief Regularizes a polygon and returns the regularized polygons.
 * @ingroup Polygon
 * @param polygon [in] The polygon to regularize.
 * @param nResult [out] The number of resulting regularized polygons.
 * @param regularizedPolygons [out] The result of regularization.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr or polygon or regularizedPolygons is not initialized
 * 			- APIERR_MEMFULL - low memory condition
 * @remarks This function is used to regularize a polygon. The result may be 0, 1 or more regularized polygons.
 * 			Refer to the @ref API_RegularizedPoly structure to have more details on the polygon data structure.
 */
__APIEXPORT GSErrCode ACAPI_Polygon_RegularizePolygon (const API_RegularizedPoly* polygon, Int32* nResult, API_RegularizedPoly*** regularizedPolygons);


/**
 * @brief Regularizes a polyline and returns the regularized polyline.
 * @ingroup Polygon
 * @param polyline [in] The polyline to regularize.
 * @param regularizedPolyline [out] The result of regularization.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr or polyline or regularizedPolyline is not initialized
 * 			- APIERR_MEMFULL - low memory condition
 * @remarks This function is used to regularize a polyline. A polyline is considered irregular when two or more consecutive vertices in the coord array are the same.
 * 			The result may be an empty polyline.
 * 			Refer to the @ref API_RegularizedPoly structure to have more details on the polyline data structure.
 */
__APIEXPORT GSErrCode ACAPI_Polygon_RegularizePolyline (const API_RegularizedPoly* polyline, API_RegularizedPoly* regularizedPolyline);


/**
 * @brief Deallocates handles in an @ref API_RegularizedPoly struct.
 * @ingroup Polygon
 * @param regularizedPoly [in] The polygon or polyline data to dipose.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr or memo or insMemo is not initialized
 * 			- APIERR_MEMFULL - low memory condition
 */
__APIEXPORT GSErrCode ACAPI_Polygon_DisposeRegularizedPoly (API_RegularizedPoly* regularizedPoly);


/**
 * @brief Decomposes a polygon into triangles.
 * @ingroup Polygon
 * @param memo [in] Parameters of an polygon. The coordinates of the polygon and the subpolygon endpoints must be coords handle and pends handle in the memo.
 * @param coords [out] Coordinates of the triangles
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr
 * 			- APIERR_REFUSEDPAR - Arc in the polygon
 * 			- APIERR_MEMFULL - Not enough memory to complete the operation
 * 			- APIERR_IRREGULARPOLY - Input polygon is irregular.
 * @remarks This function is used to decompose a polygon into triangles. The coords handle will be allocated by the server application and filled with coordinates. The number of generated triangles should be determined based on the returned handle size.
 * 			The function accept only polygons which has no arc segments.
 * 			Do not forget to dispose the coords handle if it is not needed any more.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Polygon_TriangulatePoly-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Polygon_TriangulatePoly (API_ElementMemo* memo, API_Coord *** coords);


/**
 * @brief Returns the coordinate of a neig.
 * @ingroup Element
 * @param neig [in] neig data
 * @param coord3D [out] coordinate assigned to the passed neig
 * @param coord3DDocument [out] coordinate over a 3D Document window
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr
 * 			- APIERR_BADID - Invalid neigID has been passed
 * @remarks This function is used to convert neig to coordinate.
 * 			Refer to the @ref API_NeigID structure to get information how neigs are assigned to the element geometry.
 */
__APIEXPORT GSErrCode ACAPI_Element_NeigToCoord (API_Neig* neig, API_Coord3D* coord3D, API_Coord3D* coord3DDocument = nullptr);


/**
 * @brief Returns the maximal distance of a spline segment and a set of coordinates.
 * @ingroup ProjectSetting
 * @param splinePars [in] the coordinates and the parameters of the spline to test.
 * @param distance [out] the maximal distance of the coordinates from the requested segment of the spline.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr, or the passed handles have wrong sizes.
 * @remarks This function is used to determine the maximal distance of a segment of a bezier curve and a set of coordinates.
 * 			Refer to the @ref API_TestSplineFit structure for the parametrization.
 */
__APIEXPORT GSErrCode ACAPI_ProjectSetting_GetSplineMaxDist (API_TestSplineFit* splinePars, double* distance);


/**
 * @brief Converts a picture into another image format.
 * @ingroup Polygon
 * @param elem [in] Parameter elem for element type identification. Give elem.header.guid or elem.header.typeId. For roofs specify elem.roof.roofClass also.
 * @param polygonId [in] Parameter polygonId.
 * @param surfaceType [out] Parameter surfaceType.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - parameters are nullptr or invalid
 * 			- APIERR_BADID - elemGuid does not refer to a valid element in the database.
 * @remarks This function is used to convert a polygonId returned by ModelerAPI::Polygon::GetPolygonId to a @ref API_SurfaceTypeID.
 */
__APIEXPORT GSErrCode ACAPI_Polygon_PolygonId2SurfaceType (const API_Element* elem = nullptr, const Int32* polygonId = nullptr, API_SurfaceTypeID* surfaceType = nullptr);


/**
 * @brief Initializes a parameter list to pass to an other add-on.
 * @ingroup AddOnAddOnCommunication
 * @param params [out] The address of a handle to be initialized
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - params is nullptr
 * 			- APIERR_MEMFULL - low memory condition
 * @remarks This function is used to initialize a parameter list handle used in inter-addon communications. For the utilization details of @ref ACAPI_AddOnAddOnCommunication_InitMDCLParameterList refer to the Parameter Passing section of the Communication Manager.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnAddOnCommunication_InitMDCLParameterList-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnAddOnCommunication_InitMDCLParameterList (GSHandle* params);


/**
 * @brief Retrieves the number of the parameters on the parameter list.
 * @ingroup AddOnAddOnCommunication
 * @param params [in] The handle of the parameter list
 * @param nPars [out] Number of the parameters on the list
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - params is nullptr
 * @remarks This function is used to retrieve the number of the parameters on the parameter list handle used in inter-addon communications. For the utilization details of @ref ACAPI_AddOnAddOnCommunication_GetMDCLParameterNum refer to the Parameter Passing section of the Communication Manager.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnAddOnCommunication_GetMDCLParameterNum-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnAddOnCommunication_GetMDCLParameterNum (GSHandle params, Int32* nPars);


/**
 * @brief Appends a parameter to the parameter list.
 * @ingroup AddOnAddOnCommunication
 * @param params [in/out] Handle of the parameter list
 * @param mDCLParameter [in] Pointer to the parameter to be appended
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - params, par or par->name is nullptr,
 * @remarks This function is used to append a parameter to the parameter list used in inter-addon communications. For the utilization details of @ref ACAPI_AddOnAddOnCommunication_AddMDCLParameter refer to the Parameter Passing section of the Communication Manager.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnAddOnCommunication_AddMDCLParameter-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnAddOnCommunication_AddMDCLParameter (GSHandle params, API_MDCLParameter* mDCLParameter);


/**
 * @brief Retrieves a parameter from the parameter list.
 * @ingroup AddOnAddOnCommunication
 * @param params [in] The handle of the parameter list
 * @param mDCLParameter [out] Pointer to the requested parameter
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - params or par is nullptr
 * 			- APIERR_BADNAME - The passed parameter name is not found on the parameter list
 * 			- APIERR_BADINDEX - The passed parameter index is out of range (checked only if
 */
__APIEXPORT GSErrCode ACAPI_AddOnAddOnCommunication_GetMDCLParameter (GSHandle params, API_MDCLParameter* mDCLParameter);


/**
 * @brief Modifies a parameter on the parameter list.
 * @ingroup AddOnAddOnCommunication
 * @param params [in/out] Handle of the parameter list
 * @param mDCLParameter [in] Pointer to the modified parameter
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - params or par is nullptr,
 * @remarks This function is used to modify a parameter on the parameter list handle used in inter-addon communications. For the utilization details of @ref ACAPI_AddOnAddOnCommunication_ChangeMDCLParameter refer to the Parameter Passing section of the Communication Manager.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnAddOnCommunication_ChangeMDCLParameter-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnAddOnCommunication_ChangeMDCLParameter (GSHandle params, API_MDCLParameter* mDCLParameter);


/**
 * @brief Frees the parameter list handle.
 * @ingroup AddOnAddOnCommunication
 * @param params [in] Handle of the parameter list
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - params is nullptr
 * @remarks This function is used to dispose a parameter list handle used in inter-addon communications. For the utilization details of @ref ACAPI_AddOnAddOnCommunication_FreeMDCLParameterList refer to the Parameter Passing section of the Communication Manager.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AddOnAddOnCommunication_FreeMDCLParameterList-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AddOnAddOnCommunication_FreeMDCLParameterList (GSHandle* params);


/**
 * @brief Returns the length of a line of text in mms.
 * @ingroup Element
 * @param textLinePars [in] parameters of the text to be measured
 * @param length [out] the length of the text
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - one or both of the parameters are nullptr
 * @remarks The `index` field of textLinePars determines the behavior of the function.
 * 			|index|Behavior|
 * 			|--- |--- |
 * 			|-1|No line terminator; this is the last line of the text.|
 * 			|0|Line terminators are in the text; measure the whole string in textLinePars->lineStr.|
 * 			|> 0|Length of the line with the specified index.|
 *
 * 			The `textLinePars->drvScaleCorr` field determines whether any drawing scale correction is applied.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetTextLineLength (API_TextLinePars* textLinePars, double* length);


/**
 * @brief Returns the ratio of the font capital size and typography size.
 * @ingroup Element
 * @param api_fontID [in] Font attribute index.
 * @param textSizeFactor [out] The ratio of the font capital size and typography size.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Any of the parameters are nullptr.
 * @remarks Archicad uses the capital font size. This function is used to determine the ratio of the font capital size and typographical size.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetTextSizeFactor (short* api_fontID, double* textSizeFactor);


/**
 * @brief Returns the texture coordinates of the given surface point.
 * @ingroup  ModelAccess
 * @param texCoordPars [in] identifies the surface point
 * @param uvCoord [out] the local (u, v) coordinate system of the texture
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - one or both of the parameters are nullptr
 * 			- APIERR_GENERAL - Couldn't get the texture coordinates
 */
__APIEXPORT GSErrCode ACAPI_ModelAccess_GetTextureCoord (API_TexCoordPars* texCoordPars, API_UVCoord* uvCoord);


/**
 * @brief Retrieves the GUID of a built-in library part.
 * @ingroup LibraryPart
 * @param templateFileResID [in] the library part template 'FILE' resource ID
 * @param lpfUnId [out] the required unique ID in string format
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - lpfUnId is nullptr or templateFileResID contains invalid data.
 * @remarks This function is used to get the GUID of a library part compiled into the add-on's module as 'FILE' resource. For more information about built-in library parts see @ref ACAPI_AddOnIntegration_RegisterBuiltInLibrary.
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetBuiltInLibpartUnId (short templateFileResID, char* lpfUnId);


/**
 * @brief Retrieves the name of a Libpart, even if the library is unloaded.
 * @ingroup LibraryPart
 * @param guid [in] the guid of the Object, Lamp, Window or Door element.
 * @param name [out] the name of the Libpart
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - guid is nullptr
 * @remarks This function is used to get the name of a library part even if the library is unloaded For more information about library parts see @ref API_LibPart.
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetUnloadedLibpartName (const API_Guid* guid, GS::UniString* name);


/**
 * @brief Checks whether a library part unique ID refers to a subtype of another.
 * @ingroup LibraryPart
 * @param successorUnIDStr [in] the unique ID of the subtype.
 * @param predecessorUnIDStr [in] the unique ID of the expected ancestor.
 * @return
 * 			- NoError - The function has completed with success and the ancestry holds.
 * 			- APIERR_NOTSUBTYPEOF - The function has completed with success but the first one is not a subtype of the second.
 * 			- APIERR_BADPARS - any of the parameters are nullptr.
 * @remarks This function is used to verify that a library part identified by its unique ID is a subtype of the other one.
 * 			No existence check is performed for the predecessor.
 * 			It checks for real ancestry so returns APIERR_NOTSUBTYPEOF for equal unique IDs as well.
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_CheckLibPartSubtypeOf (const char* successorUnIDStr, const char* predecessorUnIDStr);


/**
 * @brief Checks whether a library part unique ID refers to a subtype of another.
 * @ingroup LibraryPart
 * @param successorUnIDStr [in] the unique ID of the subtype.
 * @param predecessorUnIDStr [in] the unique ID of the expected ancestor.
 * @return
 * 			- NoError - The function has completed with success and the ancestry holds.
 * 			- APIERR_NOTSUBTYPEOF - The function has completed with success but the first one is not a subtype of the second.
 * 			- APIERR_BADPARS - any of the parameters are nullptr.
 * @remarks This function is used to verify that a library part identified by its unique ID is a subtype of the other one identified only by the main part of its unique ID.
 * 			No existence check is performed for the predecessor.
 * 			It checks for real ancestry so returns APIERR_NOTSUBTYPEOF for equal unique IDs as well.
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_CheckLibPartSubtypeOfbyMain (const char* successorUnIDStr, const char* predecessorUnIDStr);


/**
 * @brief Compares two library part unique IDs.
 * @ingroup LibraryPart
 * @param unIDStr1 [in] the first library part unique ID.
 * @param unIDStr2 [out] the second library part unuique ID.
 * @return
 * 			- NoError - The function has completed with success and the two unique IDs are equal.
 * 			- APIERR_NOTEQUALREVISION - The function has completed with success and the main GUID parts of the unique IDs are equal but the revision IDs differ.
 * 			- APIERR_NOTEQUALMAIN - The function has completed with success but even the main GUID parts of the unique IDs differ.
 * 			- APIERR_BADPARS - any of the parameters are nullptr.
 * @remarks This function is used to compare two library part unique IDs. Returns NoError if the IDs refer to the same library part with the same revision ID. APIERR_NOTEQUALREVISION is returned when the IDs still refer to the same library part with different revision IDs (different editions of the same library part). If the unique IDs refer to different library parts, APIERR_NOTEQUALMAIN is returned.
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_CompareLibPartUnIds (const char* unIDStr1, const char* unIDStr2);


/**
 * @brief Returns the unique ID of the creator tool of the specified object.
 * @ingroup Element
 * @param elemHead [in] the header or the element (only the guid field is required).
 * @param unIDStr [out] the unique ID of the creator tool subtype.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr, or the passed handles have wrong sizes.
 * 			- APIERR_BADID - Not a Window, Door, Light or Symbol header was passed, or no element with the specified guid was found.
 * @remarks This function is used to get the creator tool of an element. Only elements of type window, door, symbol or light are accepted. The returned string is the unique ID of the template object of the creator tool.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetElemCreatorToolUnId (API_Elem_Head* elemHead, char* unIDStr);


/**
 * @brief Returns the library part unique identifier of the GDL based element (object/lamp/window/door).
 * @ingroup LibraryPart
 * @param elemHead [in] Head of the element. It is identified by the guid field.
 * @param lpfUnId [out] The required unique ID in string format.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - One or both of the parameters is nullptr.
 * 			- APIERR_DELETED - The element is deleted.
 * 			- APIERR_BADID - The element is not GDL based.
 * @remarks This function is used to get the library part unique ID in string format of the given element. The element is window, door, object or lamp.
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetElemLibPartUnId (API_Elem_Head* elemHead, char* lpfUnId);


/**
 * @brief Returns the library part's creator element type and variation ID.
 * @ingroup LibraryPart
 * @param libPart [in] Identifies the library part. A basic @ref ACAPI_LibraryPart_Search is performed to extract the internal library part identifier.
 * @param toolboxItem [out] The requested creator element type and variation ID.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Any of the parameters is nullptr.
 * @remarks This function returns the element type and variation ID, retrieving it from the internal library part registry. This information is necessary when you want to place an object having a special variation ID.
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetLibPartToolVariation (API_LibPart* libPart, API_ToolBoxItem* toolboxItem);


/**
 * @brief Sets the unique ID of the empty hole.
 * @ingroup Element
 * @param signature [in] A four-character identifier of this library part subtype.
 * @param emptyHoleUnIdStr [in] The unique ID string of this library part subtype.
 * @param emptyOpeningSubtypeUnIDStr ...
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOTSUPPORTED - The root type is not window or door.
 * @remarks This function is used to set the unique ID of the empty hole. It works only on window or door subtype.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_SetEmptyHoleUnId-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_SetEmptyHoleUnId (GSType* signature, const char* emptyHoleUnIdStr, const char* emptyOpeningSubtypeUnIDStr);


/**
 * @brief Change the content of a text or a textual label element.
 * @ingroup Element
 * @param contentPars [in/out] Parameters of the element and contents.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The input parameters are not given correctly.
 * 			- APIERR_REFUSEDPAR - The passed element is not a text or a textual label.
 * 			- APIERR_PAROVERLAP - The range overlaps two or more paragraphs.
 * 			- APIERR_PAROVERFLOW - The beginning position (from) run over the content length.
 * 			- APIERR_MEMFULL - Not enough memory.
 * @remarks This function is used to modify the content of a multistyle text or textual label. The styles of the runs won't be lost. The new content piece will pick up the style (font, size, faceBits...) of the character on the from position in the original content. The content member of @ref API_ContentPars should not contain line end characters and ranges may not overlap paragraphs. The another way to change the content is using @ref ACAPI_Element_Change function. With it you can set the style of the text also by passing textContent and paragraphs handles in @ref API_ElementMemo structure. Don't forget to free the allocated memory blocks.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_ChangeContent-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_ChangeContent (API_ContentPars* contentPars);


/**
 * @brief Returns the mode flag currently set for autotext replacing in retrieved texts.
 * @ingroup AutoText
 * @param showAutoText [out] The current value of the autotext flag.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed showAutoText parameter is nullptr.
 * @remarks This function is used to get the current mode which determines whether @ref ACAPI_Element_GetMemo function retrieves the original content of the text and textual label element [false] (the database representation), or the interpreted one [true] (what you see on the user interface).
 * 			Use the @ref ACAPI_AutoText_ChangeAutoTextFlag function to change this flag.
 */
__APIEXPORT GSErrCode ACAPI_AutoText_GetAutoTextFlag (bool* showAutoText);


/**
 * @brief Switches autotexts to be replaced with their current values or kept as autotext keys in retrieved texts.
 * @ingroup AutoText
 * @param showAutoText [in] The value of the autotext flag to be set.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed showAutoText parameter is nullptr.
 * @remarks This function is used to set the flag which determines whether @ref ACAPI_Element_GetMemo function retrieves the original content of the text or textual label element [false] (the database representation), or the interpreted one [true] (what you see on the user interface).
 * 			You can retrieve this flag with the @ref ACAPI_AutoText_GetAutoTextFlag function.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AutoText_ChangeAutoTextFlag-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AutoText_ChangeAutoTextFlag (bool* showAutoText);


/**
 * @brief Retrieves all autotext keys and their values.
 * @ingroup AutoText
 * @param keys [out] Pointer to an array of C strings to be filled with the available autotext keys
 * @param values [out] Pointer to an array of C strings to be filled with the corresponding interpreted values (optional, can be nullptr)
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed keys parameter is nullptr.
 * @remarks This function and @ref ACAPI_AutoText_GetAutoTexts can only resolve non-context dependent autotexts like "PROJECTNAME", "PROJECTNUMBER", "COMPANY", "SHORTDATE". For context dependent autotexts please use @ref ACAPI_AutoText_GetPropertyAutoTextKeyTable with @ref ACAPI_AutoText_InterpretAutoText
 * 			The function allocates memory for the string arrays and for each strings dynamically. Do not forget to dispose the retrieved pointers when you do not need them any more.
 * 			For the same purpose you can also use the @ref ACAPI_AutoText_GetAutoTexts function. You can modify the value of an autotext with @ref ACAPI_AutoText_SetAnAutoText.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AutoText_GetAutoTextKeys-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AutoText_GetAutoTextKeys (char*** keys, char*** values);


/**
 * @brief Retrieves the context dependent autotexts keys.
 * @ingroup AutoText
 * @param guid [in] A pointer to a @ref API_Guid that represents an object like a wall or slab. It can be APINULLGuid, but then only the general autotexts can be received like "Area", "Element ID" (which are common in all element types), and not the element specific ones like "Thickness of the wall".
 * @param keyGuidTable [out] Pointer to a hash table where the resulting autotext names and keys will be stored for a given guid.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed parameters are invalid.
 * @remarks This function will fill the passed hast table with the autotexts' name and key for any given an element like a wall. The names are the same as they can be seen in Archicad while inserting an autotext into a text field, for example "Area".
 * 			The function allows for an APINULLGuid input. But keep in mind that in this case only the general autotexts will be returned.
 * 			The resulting autotext keys can be used to create autotexts or to access the value of certain parameters associated with an object using the function @ref ACAPI_AutoText_InterpretAutoText. These property keys usually look like PROPERTY-69A58F6F-DD3B-478D-B5EF-09A16BD0C548.
 * 			To create an embeddable autotext from its key surround the key with inequality signs: <PROPERTY-69A58F6F-DD3B-478D-B5EF-09A16BD0C548>, then insert this text into the chosen text field.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AutoText_GetPropertyAutoTextKeyTable-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AutoText_GetPropertyAutoTextKeyTable (API_Guid* guid, GS::HashTable<GS::UniString, GS::UniString>* keyGuidTable);


/**
 * @brief Retrieves the context dependent autotext's value.
 * @ingroup AutoText
 * @param autotext [in] A pointer to a GS::UniString containing the key for the context dependent autotexts key, without the '<' and '>' signs. For example the "<The autotext key>" should look like "The autotext key".
 * @param guid [in] Pointer to a @ref API_Guid element for context dependency resolution. This can be the guid of any object which can contain an autotext. For example a label's guid is sufficient to resolve the autotext's value present on that label.
 * @param value [out] A GS::UniString pointer that is either empty or contains the autotext's value.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Either the autotext or the value was nullptr.
 * 			- APIERR_GENERAL - The passed autotext could not be resolved or it is has invalid formatting.
 * @remarks Use this function to find the value of context dependent autotext keys. In this context, context dependency means that the value of a given autotext is determined by the object that it is bound to. For example a label with an autotext < Element Id > will show the object's Element Id that the label is bound to. These autotexts have a format similar to: <PROPERTY-69A58F6F-DD3B-478D-B5EF-09A16BD0C548>
 * 			Remember to dispose of the '<' and '>' signs before passing the function an autotext key. So the previous example should look similar to PROPERTY-69A58F6F-DD3B-478D-B5EF-09A16BD0C548.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AutoText_InterpretAutoText-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AutoText_InterpretAutoText (const GS::UniString* autotext, const API_Guid* guid, GS::UniString* value);


/**
 * @brief Retrieves the key, description and value of the currently available autotexts.
 * @ingroup AutoText
 * @param autotexts [out] Array of UniString triplets containing description, key and value of an autotext
 * @param autotextType [in] Filter for collecting only the given type of autotexts
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed autotexts parameter is nullptr.
 * @remarks This function and @ref ACAPI_AutoText_GetAutoTextKeys can only resolve non-context dependent autotexts like "PROJECTNAME", "PROJECTNUMBER", "COMPANY", "SHORTDATE". For context dependent autotexts please use @ref ACAPI_AutoText_GetPropertyAutoTextKeyTable with @ref ACAPI_AutoText_InterpretAutoText
 * 			Use this function to get the key, the description (as it is referenced in the user interface of Archicad), and the current value of the autotexts. The autotext data is retrieved in an array of array of UniStrings, so you do not need to free the allocated memory, as it is disposed automatically in the destructor.
 * 			The UniString triplets contain the autotext data in the following order: description text, database key, value.
 * 			You can control the range of the autotexts to be retrieved with the @ref API_AutotextType parameter.
 * 			You can modify the value of an autotext with @ref ACAPI_AutoText_SetAnAutoText.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AutoText_GetAutoTexts-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AutoText_GetAutoTexts (GS::Array<GS::ArrayFB<GS::UniString, 3>>* autotexts, API_AutotextType autotextType);


/**
 * @brief Sets the value of an autotext.
 * @ingroup AutoText
 * @param autotextDbKey [in] The database key of autotext to be changed
 * @param autotextValue [in] The new autotext value for the specified key (optional, can be nullptr)
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The passed autotextDbKey parameter is nullptr.
 * 			- APIERR_BADVALUE - The passed autotext value is not valid.
 * @remarks Use this function to set the value of an existing autotext defined by the given autotext key. You can set the autotext value empty by passing nullptr in the autotextValue parameter.
 * 			You can get the list of currently available autotexts with the @ref ACAPI_AutoText_GetAutoTexts and @ref ACAPI_AutoText_GetAutoTextKeys functions.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AutoText_SetAnAutoText-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AutoText_SetAnAutoText (const GS::UniString* autotextDbKey = nullptr, const GS::UniString* autotextValue = nullptr);


/**
 * @brief Returns the top level group of a nested group element.
 * @ingroup Grouping
 * @param groupGuid [in] The guid of a group element.
 * @param mainGroupGuid [out] The guid of the root group in the group hierarchy which contains the tested group.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The groupGuid or the mainGroupGuid parameter is nullptr
 * 			- APIERR_BADID - The passed groupGuid does not refer to an existing group element
 * @remarks This function is used to obtain the top level group of a nested group element. If the passed group is not part of another group, the function returns the passed group guid as main group guid.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Grouping_GetMainGroupGuid-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Grouping_GetMainGroupGuid (const API_Guid* groupGuid, API_Guid* mainGroupGuid);


/**
 * @brief Retrieves the guid of the hotlink element which contains the given element.
 * @ingroup Hotlink
 * @param elemGuid [in] The guid of the element.
 * @param hotlinkElemGuid [out] The guid of the hotlink which contains the given element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The elemGuid or the hotlinkElemGuid parameter is nullptr
 * 			- APIERR_BADID - The passed elemGuid is invalid.
 * @remarks This function is used to obtain the hotlink element which contains the given element. If the passed element is not hotlinked element, hotlinkElemGuid will be set to APINULLGuid.
 */
__APIEXPORT GSErrCode ACAPI_Hotlink_GetContainingHotlinkGuid (const API_Guid* elemGuid, API_Guid* hotlinkElemGuid);


/**
 * @brief Run GDL parameter script.
 * @ingroup LibraryManagement
 * @param elemHead [in] Head of the element. It is identified by the guid field.
 * @param mask Element mask; can be @c APIElemMask_FromFloorplan (= use the element from the floor plan).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - The element doesn't exist.
 * @remarks You are eble to run the GDL parameter script of an object, lamp, window or door element via this function.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_RunGDLParScript (const API_Elem_Head* elemHead, UInt32 mask = 0);


/**
 * @brief Creates a new entry in the Project Info.
 * @ingroup AutoText
 * @param guid [in] The guid of the autotext (stored in the database).
 * @param uiKey [in] The string appear in the GUI (Project Info, Insert Autotext dialog).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The guid or the uiKey parameter is nullptr or uiKey already exists.
 * @remarks This function is used to create a new entry in the Project Info. It will apear in the Insert Autotext dialog also.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AutoText_CreateAnAutoText-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AutoText_CreateAnAutoText (const API_Guid* guid, const char* uiKey);


/**
 * @brief Deletes a custom entry from the Project Info.
 * @ingroup AutoText
 * @param dbKey [in] The identifier of the autotext (stored in the database).
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The dbKey parameter is nullptr or uiKey already exists.
 * 			- APIERR_BADID - The given autotext doesn't exist.
 * @remarks This function is used to delete a custom entry from the Project Info.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_AutoText_DeleteAnAutoText-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_AutoText_DeleteAnAutoText (const char* dbKey);


/**
 * @brief Retrieves the the base height of a curtain wall or its subelem.
 * @ingroup CurtainWall
 * @param guid [in] Curtain Wall or its subelem reference.
 * @param bottom [out] Bottom of the element. This value is relative to the element's home story.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - guid or bottom parameter is nullptr.
 * 			- APIERR_BADID - guid is invalid.
 * @remarks This function is used to obtain the bottom of the curtain wall or its subelem (panel, fram, junction or accessory). As against the function name the bottom is relative to the element's home story.
 */
__APIEXPORT GSErrCode ACAPI_CurtainWall_GetCWAbsoluteBottom (const API_Guid* guid, double* bottom);


/**
 * @brief Retrieves the height of a curtain wall element.
 * @ingroup CurtainWall
 * @param guid [in] Curtain Wall reference.
 * @param height [out] Height of the curtain wall.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - guid or height parameter is nullptr or the guid is invalid.
 * @remarks This function is used to obtain the height - maximal difference of z coords - of the curtain wall.
 */
__APIEXPORT GSErrCode ACAPI_CurtainWall_GetCWHeight (const API_Guid* guid, double* height);


/**
 * @brief Returns the calculated additional parameters of a curtain wall subelem.
 * @ingroup CurtainWall
 * @param guid [in] Curtain Wall subelem reference.
 * @param params [out] Additional parameters of library part-based curtain wall subelem.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - guid or params parameter is nullptr or the guid is invalid.
 * 			- APIERR_BADID - The given element os not library part-based.
 * @remarks This function is used to obtain the additional parameters of a library part-based curtain wall subelem (panel, frame, junction, accessory). Don't forget to call @ref ACAPI_DisposeElemMemoHdls to dispose the params handle when you're done.
 * 			This function is a non-undoable data structure modifier function. See more details on this topic at Command Overview.
 */
__APIEXPORT GSErrCode ACAPI_CurtainWall_GetCWSubElemParams (const API_Guid* guid, API_AddParType*** params);


/**
 * @brief Returns the polygon data of a Skylight hole contour.
 * @ingroup Element
 * @param skylightGuid [in] Identifier of the Skylight element.
 * @param holePoly [out] Polygon data of the hole contour.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_NOPLAN - There is no active plan database.
 * 			- APIERR_BADPARS - skylightGuid or holePoly is nullptr.
 * 			- APIERR_BADINDEX - skylightGuid does not refer to a valid element in the database.
 * 			- APIERR_REFUSEDPAR - The element specified with skylightGuid is not Skylight type.
 * @remarks This function is used to get the contour polygon of a Skylight hole in absolute coordinates, projected to the horizontal plane. (Note that currently this is not the actual hole contour but the four corner points of the Skylight element).
 * 			No need to dispose the allocated data of the Geometry::Polygon2D nor the Geometry::MultiPolygon2D.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetSkylightHolePolygon-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetSkylightHolePolygon (const API_Guid* skylightGuid, Geometry::Polygon2D* holePoly);


/**
 * @brief Enables renovation graphical overrides during @ref ACAPI_DrawingPrimitive_ShapePrims.
 * @ingroup GraphicalOverride
 * @param oldOverrideVal [out] Returns the current override state.
 * @param newOverrideVal [in] The new override state.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function determines the behavior of the @ref ACAPI_DrawingPrimitive_ShapePrims function. If the renovation override is set then all primitive elements will be exported using the overriden attributes (as set in the graphical override attributes for the appropriate renovation filter).
 * @ref ACAPI_GraphicalOverride_EnableRenovationOverride is only effective if @ref ACAPI_GraphicalOverride_EnableVisualOverride is enabled.
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_EnableRenovationOverride (bool* oldOverrideVal, const bool* newOverrideVal);


/**
 * @brief Enables graphical overrides during @ref ACAPI_DrawingPrimitive_ShapePrims.
 * @ingroup GraphicalOverride
 * @param oldOverrideVal [out] Returns the current override state.
 * @param newOverrideVal [in] The new override state.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function determines the behavior of the @ref ACAPI_DrawingPrimitive_ShapePrims function. If the override state is set then all primitive elements will be exported using the overriden attributes.
 * 			When @ref ACAPI_GraphicalOverride_EnableVisualOverride is enabled, the renovation overrides can still be enabled or disabled with @ref ACAPI_GraphicalOverride_EnableRenovationOverride.
 */
__APIEXPORT GSErrCode ACAPI_GraphicalOverride_EnableVisualOverride (bool* oldOverrideVal, const bool* newOverrideVal);


/**
 * @brief Returns the name of the renovation status.
 * @ingroup Renovation
 * @param renovationStatusType [in] The renovation status you are interested in.
 * @param statusName [out] The localized name of the renovation status.
 * @return
 * 			- NoError - The function has completed with success.
 */
__APIEXPORT GSErrCode ACAPI_Renovation_GetRenovationStatusName (API_RenovationStatusType renovationStatusType, GS::UniString* statusName);


/**
 * @brief Returns the name of the renovation filter.
 * @ingroup Renovation
 * @param renovationFilterGuid [in] The GUID of the renovation filter.
 * @param renovationFilterName [out] The localized name of the renovation filter.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks The user may create any number of renovation filters; use this function to retrieve their names.
 * 			The list of the renovation filters can be retrieved with the @ref ACAPI_Renovation_GetRenovationFilters function.
 */
__APIEXPORT GSErrCode ACAPI_Renovation_GetRenovationFilterName (const API_Guid* renovationFilterGuid, GS::UniString* renovationFilterName);


/**
 * @brief Sets the layout context of current database for drawing.
 * @ingroup Navigator
 * @param databaseUnId [in] The database identifier of the layout context.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - databaseUnId is nullptr or a non existing database identifier.
 * @remarks This function is used to set the layout context of the current database, when current database is a master layout.
 * 			Use this function after changed to a master layout of the given layout with @ref ACAPI_Database_ChangeCurrentDatabase. When this function successfully completed, the datas (autotexts, etc.) on master layout will be shown in the context of the given layout.
 */
__APIEXPORT GSErrCode ACAPI_Navigator_SetMasterLayoutOnLayout (const API_DatabaseUnId* databaseUnId = nullptr);


/**
 * @brief Returns user building material connection priority for a interface priority.
 * @ingroup Element
 * @param uiPriority [in] The priority as it appers on the user interface.
 * @param elemPriority [out] The building material's connection priority.
 * @return
 * 			- NoError - The function has completed with success.
 */
__APIEXPORT GSErrCode ACAPI_Element_UI2ElemPriority (GS::Int32* uiPriority, GS::Int32* elemPriority);


/**
 * @brief Returns user interface priority for a building material connection priority.
 * @ingroup Element
 * @param elemPriority [in] The building material's connection priority.
 * @param uiPriority [out] The priority as it appers on the user interface.
 * @return
 * 			- NoError - The function has completed with success.
 */
__APIEXPORT GSErrCode ACAPI_Element_Elem2UIPriority (GS::Int32* elemPriority, GS::Int32* uiPriority);


/**
 * @brief Converts the reveal depth offset from wall side to core skin for wall openings.
 * @ingroup Element
 * @param wallOpeningGuid [in] Unique ID of the WallOpening element.
 * @param sideOffset [in] Reveal depth offset from wall side.
 * @param coreOffset [out] Reveal depth offset from core skin.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - wallOpeningGuid or sideOffset or coreOffset is nullptr.
 * 			- APIERR_BADID - wallOpeningGuid does not refer to a valid element in the database.
 * 			- APIERR_REFUSEDPAR - The element specified with wallOpeningGuid is not WallOpening type, or owner wall of opening is not exist.
 * @remarks This function can be used for wall openings in composite walls (side offset and core offset is equal in walls with basic structure).
 */
__APIEXPORT GSErrCode ACAPI_Element_CalcSideOffsetToCoreOffset (const API_Guid* wallOpeningGuid, const double* sideOffset, double* coreOffset);


/**
 * @brief Converts the reveal depth offset from core skin to wall side for wall openings.
 * @ingroup Element
 * @param wallOpeningGuid [in] Unique ID of the WallOpening element.
 * @param coreOffset [in] Reveal depth offset from core skin.
 * @param sideOffset [out] Reveal depth offset from wall side.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - wallOpeningGuid or coreOffset or sideOffset is nullptr.
 * 			- APIERR_BADID - wallOpeningGuid does not refer to a valid element in the database.
 * 			- APIERR_REFUSEDPAR - The element specified with wallOpeningGuid is not WallOpening type, or owner wall of opening is not exist.
 * @remarks This function can be used for wall openings in composite walls (side offset and core offset is equal in walls with basic structure).
 */
__APIEXPORT GSErrCode ACAPI_Element_CalcCoreOffsetToSideOffset (const API_Guid* wallOpeningGuid, const double* coreOffset, double* sideOffset);


/**
 * @brief Returns if elem has visible skin depending on Partial Structure Display.
 * @ingroup Element
 * @param elemGuid [in] Unique ID of the element.
 * @param structure [in] The partial structure display.
 * @param result [out] Returns if elem has visible skin.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - elemGuid does not refer to a valid element in the database.
 * 			- APIERR_BADPARS - elemGuid or structure or result is nullptr.
 * @remarks This function tells if the element has any visible skin when the given partial structure display is in effect.
 */
__APIEXPORT GSErrCode ACAPI_Element_ElemHasVisibleSkin (const API_Guid* elemGuid, const API_StructureDisplay* structure, bool* result);


/**
 * @brief Returns the position and the normal vector of the given opening.
 * @ingroup Element
 * @param elemGuid [in] The opening element's GUID.
 * @param openingTranMat [out] The global &rarr; local transformation matrix of the opening.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The openingTranMat parameter is nullptr.
 * 			- APIERR_DELETED - The elemGuid doesn't point to a valid element.
 * 			- APIERR_BADID - The elemGuid doesn't point to a valid opening.
 * 			- APIERR_GENERAL - The transformation matrix cannot be calculated.
 * @remarks The transformation matrix may result in a left-handed coordinate system if the opening is mirrored.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetOpeningTransformation (const API_Guid* elemGuid, API_Tranmat* openingTranMat);


/**
 * @brief Converts an @ref API_Neig structure to an @ref API_Guid.
 * @ingroup Selection
 * @param apiNeig [in] The Neig describing a point of the Element.
 * @param apiGuid [out] The GUID of the Subelement at that point.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - apiGuid or apiNeig is nullptr.
 */
__APIEXPORT GSErrCode ACAPI_Selection_GetSelectedElement (const API_Neig* apiNeig, API_Guid* apiGuid);


/**
 * @brief Converts an @ref API_Guid structure to an @ref API_Neig.
 * @ingroup Selection
 * @param apiGuid [in] The GUID of the Subelement at that point.
 * @param apiNeig [out] The Neig describing a point of the Element.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - apiGuid or apiNeig is nullptr.
 */
__APIEXPORT GSErrCode ACAPI_Selection_SetSelectedElementNeig (const API_Guid* apiGuid, API_Neig* apiNeig);


/**
 * @brief Creates a valid stair baseline from invalid data.
 * @ingroup HierarchicalEditing
 * @param apiStair [in/out] The stair element to be checked.
 * @param apiMemo [in/out] The memo of the stair element to be checked.
 * @param solution [out] The result of the operation:
 * 				   |Result|Meaning|
 * 				   |--- |--- |
 * 				   |APISS_Correct|The baseline was already correct, no operation was needed.|
 * 				   |APISS_Solved|The baseline was successfully solved.|
 * 				   |APISS_NotSolved|The baseline could not be solved.|
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - baseline or solution is nullptr.
 */
__APIEXPORT GSErrCode ACAPI_HierarchicalEditing_SolveStair (API_StairType* apiStair, API_ElementMemo* apiMemo, API_StairSolutionID* solution);


/**
 * @brief Checks if the given property expression is a syntactically valid one.
 * @ingroup Property
 * @param expressionString [in] The expression whose validity is to be decided.
 * @return
 * 			- NoError - The given expression string is a syntactically valid one.
 * 			- APIERR_BADEXPRESSION - The given expression string is syntactically incorrect.
 * 			- APIERR_BADPARS - Some of the parameters are nullptr.
 * @remarks This function is used to determine whether a property expression string is syntactically correct.
 * 			It tries to parse the expression, and APIERR_BADEXPRESSION is returned when it fails because of some syntax error.
 */
__APIEXPORT GSErrCode ACAPI_Property_CheckPropertyExpressionString (GS::UniString* expressionString);


/**
 * @brief Returns the string that can be used in expressions to refer to a specific property.
 * @ingroup Property
 * @param propertyDefinition [in] The property definition to be refenced by the returned string.
 * @param propertyReferenceString [out] String for storing the returned property reference string.
 * @return
 * 			- NoError - The operation was successful.
 * 			- APIERR_BADPARS - Some of the parameters are nullptr.
 */
__APIEXPORT GSErrCode ACAPI_Property_GetPropertyExprReferenceString (API_PropertyDefinition* propertyDefinition, GS::UniString* propertyReferenceString);


/**
 * @brief Returns the owner of the child elem in hierarchical elem.
 * @ingroup HierarchicalEditing
 * @param elemApiGuid [in] The guid of the element.
 * @param hierarchicalOwnerType [in]
 * 								|API_HierarchicalOwnerType|Meaning|
 * 								|--- |--- |
 * 								|API_RootHierarchicalOwner|Owner means the root of the hierarchical tree, so the function will return the main element of the hierarchical element.|
 * 								|API_ParentHierarchicalOwner|Owner means parent relationship in the hierarchical tree, so it's possible that the returned owner element is also a child.|
 *
 * @param hierarchicalElemType [out]
 * 							   |API_HierarchicalElemType|Meaning|
 * 							   |--- |--- |
 * 							   |API_MainElemInMultipleElem|The element is the main element of the hierarchical element, such as Curtain Wall, Stair, Railing|
 * 							   |API_ChildElemInMultipleElem|The element is a child element in the hierarchical element, such as Curtain Wall Frame, Tread, ...|
 * 							   |API_SingleElem|This element isn't part of a hierarchical element, such as Wall, Slab, ...|
 * 							   |API_UnknownElemType|Occurs in case of error.|
 *
 * @param ownerElemApiGuid [out] The input element or the owner element of the hierarchical element if the input element is a child element of a hierarchical element.
 * @return
 * 			- NoError - The operation was successful.
 * 			- APIERR_BADPARS - Some of the parameters are nullptr.
 */
__APIEXPORT GSErrCode ACAPI_HierarchicalEditing_GetHierarchicalElementOwner (const API_Guid* elemApiGuid, const API_HierarchicalOwnerType* hierarchicalOwnerType, API_HierarchicalElemType* hierarchicalElemType, API_Guid* ownerElemApiGuid);


/**
 * @brief Returns the image of the given room.
 * @ingroup Element
 * @param roomImage [in/out] The @ref API_RoomImage object containing the parameters for the image and the output generated image.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - The roomImage parameter or the contained (roomImage->nativeImagePtr) is nullptr.
 * 			- APIERR_BADID - The given GUID (roomImage->roomGuid) is invalid.
 * @remarks For example code please see the Goodie_Functions example Add-On.
 */
__APIEXPORT GSErrCode ACAPI_Element_GetRoomImage (API_RoomImage* roomImage);


/**
 * @brief Interprets a 3D GDL script with the same settings as GDL Editor.
 * @ingroup LibraryManagement
 * @since Archicad 25
 * @param script [in] The 3D GDL Script.
 * @param addPars [in] Parameters for script running. Can be NULL, in this case the script will run with empty parameter list.
 * @param modelerAPIModel [out] The generated 3D model as ModelerAPI::Model. Use either this or the modelerModel, but only one at the same time.
 * @param modelerModel [out] The generated 3D model as Modeler::ConstModel3DPtr. Use either this or the modelerAPIModel, but only one at the same time.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Incorrect parameters were specified.
 * 			- APIERR_GENERAL - Failed to interpret the script.
 */
__APIEXPORT GSErrCode ACAPI_LibraryManagement_InterpretGDLScript3D (const GS::UniString* script, API_AddParType** addPars, void* modelerAPIModel = nullptr, void* modelerModel = nullptr);


/**
 * @brief Returns the HTTP port number, on which Archicad is expecting requests.
 * @ingroup Command
 * @param portNumber [out] HTTP port number.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - the portNumber parameter is nullptr.
 * 			- APIERR_GENERAL - there is an internal error and the HTTP server could not be started.
 * @remarks This function is used to get the HTTP port on which the Add-On commands, registered via @c ACAPI_AddOnAddOnCommunication_InstallAddOnCommandHandler, can be accessed.
 */
__APIEXPORT GSErrCode ACAPI_Command_GetHttpConnectionPort (UShort* portNumber);


/**
 * @brief Activates the session report window.
 * @ingroup Dialog
 * @since Archicad 26
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function is used to open the session report window after important informations were written in it.
 * 			See also @c ACAPI_WriteReport.
 */
__APIEXPORT GSErrCode ACAPI_Dialog_ActivateSessionReport ();


/**
 * @brief Returns the parent ID of the marker, in the parentUnID member of the libPart structure.
 * @ingroup LibraryPart
 * @since Archicad 26
 * @param elemType [in] The element type.
 * @param libPart [in] The library part.
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - Incorrect elemType or libPart was specified.
 */
__APIEXPORT GSErrCode ACAPI_LibraryPart_GetMarkerParent (const API_ElemType &elemType,
																  API_LibPart		 &libPart);


/**
 * @brief Returns the localized name of the built-in element types.
 * @ingroup Element
 * @since Archicad 26
 * @param elemType [in] The element type
 * @param elemName [out] The name of the element type in the language of the Archicad version currently
 * 				   running
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADID - Invalid element type value.
 * @remarks This function retrieves the name of the specified element type in the language the currently
 * 			running program is localized for.
 * @par Example
 * 		@snippet API_Examples.cpp ACAPI_Element_GetElemTypeName-Example-Snippet
 */
__APIEXPORT GSErrCode ACAPI_Element_GetElemTypeName (const API_ElemType &elemType,
																  GS::UniString		 &elemName);


/**
 * @brief Returns the element type assigned to a neig.
 * @ingroup Element
 * @since Archicad 26
 * @param neigID [in] neig identifier
 * @param elemType [out] element type identifier
 * @return
 * 			- NoError - The function has completed with success.
 * 			- APIERR_BADPARS - any of the parameters are nullptr
 * 			- APIERR_BADID - Invalid neigID has been passed
 * @remarks This function is used to convert a neig identifier to element type.
 * 			Refer to the @ref API_NeigID structure to get information how neigs are assigned to elements.
 */
__APIEXPORT GSErrCode ACAPI_Element_NeigIDToElemType (API_NeigID neigID, API_ElemType &elemType);


/**
 * @brief Returns a neig for the given element type.
 * @ingroup Element
 * @since Archicad 26
 * @param elemType The element type.
 * @param neigID One neig ID for that element type.
 * @return
 * 			- NoError - The function has completed with success.
 * @remarks This function return a neig ID (a special point) for the given element type. This is useful in
 * 			some situations, for example element selection, where you have to pass the array of neig IDs of the elements
 * 			you want to select, but it is not important, which point of the element is given. Note that the element
 * 			type? neig ID mapping is not a one-to-one, but a one-to-many mapping.
 */
__APIEXPORT GSErrCode ACAPI_Element_ElemTypeToNeigID (const API_ElemType &elemType,
																   API_NeigID		  &neigID);

#endif // ACAPI_GOODIES_H
