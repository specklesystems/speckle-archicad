#ifndef GS_ACAPI_ELEMENT_OPENING_FLOORPLANPARAMETERS_HPP
#define GS_ACAPI_ELEMENT_OPENING_FLOORPLANPARAMETERS_HPP


// GDL
#include "GDLParamInterface.hpp"

// ARCHICADAPI
#include "ACAPI/ArchicadAPIExport.hpp"
#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"

#include <optional>


namespace ACAPI::Element {

/**
 * @brief Floor plan display mode type of openings.
 * @since Archicad 29
 * @ingroup Element
 */
enum class OpeningFloorPlanDisplayMode {
	Symbolic,				/**< Opening displayed as per its vertical position in cut parts of the host element. */
	SymbolicCut,			/**< Opening displayed as cut element in cut parts of the host element. */
	SymbolicOverhead,		/**< Opening displayed as hidden / overhead in cut parts of the host element. */
	Projected				/**< Opening displayed as per its vertical position in all parts of the host element. */
};


/**
 * @brief Representation type of openings divided by air space.
 * @since Archicad 29
 * @ingroup Element
 */
enum class DividedOpeningMode {
	Disconnected,			/**< Divided opening is shown as separate openings - not displayed in air space. */
	Connected				/**< Divided opening is shown as a single opening - displayed in air space. */
};


/**
 * @brief Type of contours on open edges of outlines.
 * @since Archicad 29
 * @ingroup Element
 */
enum class OpeningOpenEdgeStyle {
	Hide,					/**< Hide contours on open edges. */
	ShowUncut,				/**< Show contours on open edges as uncut edges. */
	ShowOverhead			/**< Show contours on open edges as overhead edges. */
};


namespace Impl { class OpeningFloorPlanParametersBase; }

class Opening;
class OpeningDefault;


/**
 * @details It represents the floorplan parameters of an Opening element or an OpeningDefault element.
 * @since Archicad 29
 * @ingroup Element
 */
class ARCHICADAPI_EXPORT OpeningFloorPlanParameters : public ACAPI::Object {
protected:
	friend class Opening;
	friend class OpeningDefault;
	/**
	 * @brief Constructs an OpeningFloorPlanParameters with an OpeningFloorPlanParameters implementation.
	 * @param impl The OpeningFloorPlanParameters implementation.
	 */
	OpeningFloorPlanParameters (std::shared_ptr<Impl::OpeningFloorPlanParametersBase> impl);

public:
	//! @cond Doxygen_Suppress
	OpeningFloorPlanParameters (const OpeningFloorPlanParameters&) = delete;
	OpeningFloorPlanParameters (OpeningFloorPlanParameters&&) = delete;
	~OpeningFloorPlanParameters ();

	OpeningFloorPlanParameters& operator= (const OpeningFloorPlanParameters&) = delete;
	OpeningFloorPlanParameters& operator= (OpeningFloorPlanParameters&&) = delete;
	//! @endcond
	
	/** @return Returns the floorplan display mode of the opening(default).	*/
	OpeningFloorPlanDisplayMode		GetFloorPlanDisplayMode () const;

	/** @return Returns the divided opening mode of the opening(default).	*/
	DividedOpeningMode				GetDividedOpeningMode () const;

	/** @return Returns wether the cut line type of the cut element is used for cut surfaces.	*/
	bool							IsCutSurfacesUseLineOfCutElements () const;

	/** @return Returns the cut line type of the opening(default).	*/
	API_AttributeIndex				GetCutSurfacesLineIndex () const;

	/** @return Returns the cut line pen index of the opening(default).	*/
	short							GetCutSurfacesLinePenIndex () const;

	/** @return Returns the open edge style of the opening(default).	*/
	OpeningOpenEdgeStyle			GetOpenEdgeStyle () const;

	/** @return Returns wether the uncut line type of the cut element is used.	*/
	bool							IsOutlinesUseLineOfCutElements () const;

	/** @return Returns the uncut line type of the opening(default).	*/
	API_AttributeIndex				GetOutlinesUncutLineIndex () const;

	/** @return Returns the uncut line pen index of the opening(default).	*/
	short							GetOutlinesUncutLinePenIndex () const;

	/** @return Returns the overhead line type of the opening(default).	*/
	API_AttributeIndex				GetOutlinesOverheadLineIndex () const;

	/** @return Returns the overhead line pen index of the opening(default).	*/
	short							GetOutlinesOverheadLinePenIndex () const;

	/** @return Returns wether cover fill is used.	*/
	bool							GetUseCoverFills () const;

	/** @return Returns wether the cover fill of the cut element is used.	*/
	bool							IsCoverFillsUseFillsOfCutElements () const;

	/** @return Returns the fill type the cover fill.	*/
	API_AttributeIndex				GetCoverFillsIndex () const;

	/** @return Returns the foreground pen index the cover fill.	*/
	short							GetCoverFillsPenIndex () const;

	/** @return Returns the background pen index the cover fill.	*/
	short							GetCoverFillsBackgroundPenIndex () const;

	/** @return Returns the type of the cover fill.	*/
	API_HatchOrientationTypeID		GetCoverFillOrientation () const;

	/** 
	* @return Returns the transformation of the cover fill.
	* @remark Not applicable to opening default.
	*/
	std::optional<API_CoverFillTransformation>		GetCoverFillTransformation () const;

	/** @return Returns wether to show the reference axis.	*/
	bool							IsShowReferenceAxis () const;

	/** @return Returns the line type of the reference axis.	*/
	API_AttributeIndex				GetReferenceAxisLineTypeIndex () const;

	/** @return Returns the pen index of the reference axis.	*/
	short							GetReferenceAxisPenIndex () const;

	/** @return Returns the overhang of the reference axis.	*/
	double							GetReferenceAxisOverhang () const;

	/** @return Returns wether the opening has a cut symbol.	*/
	bool							HasCutSymbol () const;

	/** @return Returns the main GUID of the cut symbol Library Part or std::nullopt if no cut symbol */
	std::optional<API_Guid>			GetCutSymbolLibpartId () const;

	/** @return Returns the AddPar of the cut symbol Library Part or std::nullopt if no cut symbol */
	std::optional<GDL::Parameters>	GetCutSymbolParameters () const;

	/** @return Returns wether the opening has a uncut symbol.	*/
	bool							HasUnCutSymbol () const;

	/** @return Returns the main GUID of the uncut symbol Library Part or std::nullopt if no uncut symbol */
	std::optional<API_Guid>			GetUnCutSymbolLibpartId () const;

	/** @return Returns the AddPar of the uncut symbol Library Part or std::nullopt if no uncut symbol */
	std::optional<GDL::Parameters>	GetUnCutSymbolParameters () const;
};


/**
 * @details It represents the modifiable floorplan parameters of an Opening element or an OpeningDefault element.
 * @since Archicad 29
 * @ingroup Element
 */
class ARCHICADAPI_EXPORT ModifiableOpeningFloorPlanParameters final : public OpeningFloorPlanParameters
{
protected:
	friend class Opening;
	friend class OpeningDefault;
	/**
	 * @brief Constructs an ModifiableOpeningFloorPlanParameters with an OpeningFloorPlanParameters implementation.
	 * @param impl The OpeningFloorPlanParameters implementation.
	 */
	ModifiableOpeningFloorPlanParameters (std::shared_ptr<Impl::OpeningFloorPlanParametersBase> impl);
public:
	//! @cond Doxygen_Suppress
	ModifiableOpeningFloorPlanParameters (const ModifiableOpeningFloorPlanParameters&) = delete;
	ModifiableOpeningFloorPlanParameters (ModifiableOpeningFloorPlanParameters&&) = delete;
	~ModifiableOpeningFloorPlanParameters ();

	ModifiableOpeningFloorPlanParameters& operator= (const ModifiableOpeningFloorPlanParameters&) = delete;
	ModifiableOpeningFloorPlanParameters& operator= (ModifiableOpeningFloorPlanParameters&&) = delete;
	//! @endcond
	
	/** 
	 * @brief set the floorplan display mode of the opening(default).	
	 * @param value: the new floorplan display mode
	 */
	void							SetFloorPlanDisplayMode (OpeningFloorPlanDisplayMode value);

	/** 
	 * @brief set divided opening mode of the opening(default).	
	 * @param value: the new divided opening mode
	 */
	void							SetDividedOpeningMode (DividedOpeningMode value);

	/** 
	 * @brief the cut line type of the cut element is used for cut surfaces
	 */
	void							UseCutSurfacesLineOfCutElementsOn ();

	/** 
	 * @brief the openings own cut line type is used for cut surfaces
	 */
	void							UseCutSurfacesLineOfCutElementsOff ();

	/** 
	 * @brief set the cut line type
	 * @param value: the new cut line type
	 */
	void							SetCutSurfacesLineIndex (const API_AttributeIndex& value);

	/** 
	 * @brief set the cut line pen index
	 * @param value: the new cut line pen index
	 */
	void							SetCutSurfacesLinePenIndex (short value);

	/** 
	 * @brief set the open edge style
	 * @param value: the new open edge style
	 */
	void							SetOpenEdgeStyle (OpeningOpenEdgeStyle value);

	/** 
	 * @brief the uncut line type of the cut element is used for cut surfaces
	 */
	void							UseOutlinesLineOfCutElementsOn ();

	/** 
	 * @brief the openings own uncut line type is used for cut surfaces
	 */
	void							UseOutlinesLineOfCutElementsOff ();

	/** 
	 * @brief set the uncut line type
	 * @param value: the new uncut line type
	 */
	void							SetOutlinesUncutLineIndex (const API_AttributeIndex& value);

	/** 
	 * @brief set the uncut line pen index
	 * @param value: the new uncut line pen index
	 */
	void							SetOutlinesUncutLinePenIndex (short value);

	/** 
	 * @brief set the overhead line type
	 * @param value: the new overhead line type
	 */
	void							SetOutlinesOverheadLineIndex (const API_AttributeIndex& value);

	/** 
	 * @brief set the overhead line pen index
	 * @param value: the new overhead line pen index
	 */
	void							SetOutlinesOverheadLinePenIndex (short value);

	/** 
	 * @brief turn on cover fill
	 */
	void							UseCoverFillsOn ();

	/** 
	 * @brief turn off cover fill
	 */
	void							UseCoverFillsOff ();

	/** 
	 * @brief use the cover fill of the cut element
	 */
	void							UseCoverFillsOfCutElementsOn ();

	/** 
	 * @brief use the openings own cover fill
	 */
	void							UseCoverFillsOfCutElementsOff ();

	/** 
	 * @brief set the cover fill type
	 * @param value: the new cover fill type
	 */
	void							SetCoverFillsIndex (const API_AttributeIndex& value);

	/** 
	 * @brief set the cover fill foreground pen index
	 * @param value: the new cover fill foreground pen index
	 */
	void							SetCoverFillsPenIndex (short value);

	/** 
	 * @brief set the cover fill background pen index
	 * @param value: the new cover fill background pen index
	 */
	void							SetCoverFillsBackgroundPenIndex (short value);

	/** 
	 * @brief set the cover fill orientation type
	 * @param value: the new cover fill orientation type
	 * @return Returns error if failed, nothing otherwise
	 * @remark API_HatchCentered is not supported for opening(default)s
	 */
	Result<void>					SetCoverFillOrientation (API_HatchOrientationTypeID value);

	/** 
	 * @brief set the cover fill trasformation
	 * @param value: the new cover trasformation
	 * @return Returns error if failed, nothing otherwise
	 * @remark Not supported for opening default
	 */
	Result<void>					SetCoverFillTransformation (const API_CoverFillTransformation& value);

	/** 
	 * @brief turn on reference axis
	 */
	void							ShowReferenceAxisOn ();

	/** 
	 * @brief turn off reference axis
	 */
	void							ShowReferenceAxisOff ();

	/** 
	 * @brief set the reference axis line type
	 * @param value: the new reference axis line type
	 */
	void							SetReferenceAxisLineTypeIndex (const API_AttributeIndex& value);

	/** 
	 * @brief set the reference axis line pen index
	 * @param value: the new reference axis line pen index
	 */
	void							SetReferenceAxisPenIndex (short value);

	/** 
	 * @brief set the reference axis overhang
	 * @param value: the new reference axis overhang
	 */
	void							SetReferenceAxisOverhang (double value);

	/**
	 * @brief Changes the cut symbol of OpeningFloorPlanParameters.
	 * @param libPartId the main guid of the library part, must be valid opening symbol library part
	 * @return Returns error if failed, nothing otherwise
	 */
	Result<void>					SetCutSymbol (const API_Guid& libPartId);

	/**
	 * @brief Changes the gdl parameters of the cut symbol of OpeningFloorPlanParameters.
	 * @param gdlParams gdl parameters to set
	 * @return Returns error if failed, nothing otherwise
	 */
	Result<void>					SetCutSymbolParameters (const GDL::Parameters& gdlParams);
	
	/**
	 * @brief Clears the cut symbol of OpeningFloorPlanParameters.
	 * @return Returns error if failed, nothing otherwise
	 */
	Result<void>					ClearCutSymbol ();

	/**
	 * @brief Changes the uncut symbol of OpeningFloorPlanParameters.
	 * @param libPartId the main guid of the library part, must be valid opening symbol library part
	 * @return Returns error if failed, nothing otherwise
	 */
	Result<void>					SetUnCutSymbol (const API_Guid& libPartId);

	/**
	 * @brief Changes the gdl parameters of the uncut symbol of OpeningFloorPlanParameters.
	 * @param gdlParams gdl parameters to set
	 * @return Returns error if failed, nothing otherwise
	 */
	Result<void>					SetUnCutSymbolParameters (const GDL::Parameters& gdlParams);

	/**
	 * @brief Clears the uncut symbol of OpeningFloorPlanParameters.
	 * @return Returns error if failed, nothing otherwise
	 */
	Result<void>					ClearUnCutSymbol ();
};

} // ACAPI::Element


#endif /*GS_ACAPI_ELEMENT_OPENING_FLOORPLANPARAMETERS_HPP*/