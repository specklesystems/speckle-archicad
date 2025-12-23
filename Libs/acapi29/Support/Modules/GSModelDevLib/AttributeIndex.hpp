// =============================================================================
// Description:		  AttributeIndex    
// Contact person:    AACS
// =============================================================================
#if !defined (ATTRIBUTEINDEX_HPP)
#define ATTRIBUTEINDEX_HPP


// ----------------------- Includes --------------------------------------------
#include "GSModelerExport.h"
#include "SharedPtr.hpp"

// ----------------------- Predeclarations -------------------------------------

namespace ModelerAPI {
	class AttributeIndexRelay;
}


// ----------------------- Class declaration -----------------------------------
namespace ModelerAPI {


	class GSMODELER_DLL_EXPORT AttributeIndex
	{
		friend class AttributeIndexRelay;
	public: 
		enum AttributeIndexType {PenColorIndex, FillColorIndex, MaterialIndex, FillIndex, TextureIndex, UnknownIndex}; 
		enum IndexValueCodes : Int32 {Unset = -2};

	private:
		GS::SharedPtr<ModelerAPI::AttributeIndexRelay>		relay;

	public: 
		AttributeIndex ();
		AttributeIndex (const AttributeIndexType indexTypeInit); 
		AttributeIndex (const AttributeIndexType indexTypeInit, Int32 inModelIndex, Int32 inACIndex = Unset); 

		AttributeIndex (const AttributeIndex& rhs); 
		virtual ~AttributeIndex ();

		Int32						GetIndex () const;
		Int32						GetOriginalModelerIndex () const;
		Int32						GetOriginalIndex () const;

		AttributeIndex&				operator=(const AttributeIndex& rhs);
		bool						operator== (const AttributeIndex& other) const;
		bool						operator!= (const AttributeIndex& other) const	{ return !(*this == other); }
		bool						operator< (const AttributeIndex& other) const;
		
		ULong						GenerateHashValue () const;
		bool						IsValid () const; 
	};

} // namespace ModelerAPI

#endif




