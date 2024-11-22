// *********************************************************************************************************************
// Description:		xxxxxx
//
// Module:			MMM
// Namespace:		TPL
// Contact person:	XX
//
// SG compatible
// *********************************************************************************************************************

#if !defined (MODELIOLOOKUP_HPP)
#define MODELIOLOOKUP_HPP

#pragma once

// --- Includes	--------------------------------------------------------------------------------------------------------

// from GSRoot
#include	"Definitions.hpp"
#include	"HashSet.hpp"
#include	"SharedPtr.hpp"
#include	"HashTable.hpp"
#include	"Array.hpp"
#include	"BaseElem.hpp"
#include	"Elem.hpp"
#include	"Nurbs/NurbsBody.hpp"
#include	"MeshBody.hpp"


// --- Predeclarations	------------------------------------------------------------------------------------------------

namespace Modeler {
class MeshBody;
class NurbsBody;
class BaseElem;
class Elem;

	// --- Constant definitions	--------------------------------------------------------------------------------------------

	// --- Type definitions	------------------------------------------------------------------------------------------------

typedef GS::ConstSharedPtr<MeshBody>	ConstMeshBodyPtr;
typedef GS::ConstSharedPtr<NurbsBody>	ConstNurbsBodyPtr;
typedef GS::ConstSharedPtr<BaseElem>	ConstBaseElemPtr;
typedef GS::ConstSharedPtr<Elem>		ConstElemPtr;

struct ModelOLookup {	
	GS::HashTable<const MeshBody*, UInt32> meshBody;
	GS::HashTable<const NurbsBody*, UInt32> nurbsBody;
	GS::HashTable<const BaseElem*, UInt32> baseElem;
	GS::HashTable<const Elem*, UInt32> elem;
	GS::HashTable<Int32, Int32> iumat;
	GS::HashTable<GSAttributeIndex, GSAttributeIndex> iufil;
	GS::HashTable<Int32, Int32> irtxt;
};

struct ModelILookup {	
	// these have to be shared ptrs, because recently read objects might be deleted during the same read process because of BaseElem::Share
	GS::Array<ConstMeshBodyPtr> meshBody;
	GS::Array<ConstNurbsBodyPtr> nurbsBody;
	GS::Array<ConstBaseElemPtr> baseElem;
	GS::Array<ConstElemPtr> elem;
	GS::HashTable<Int32, Int32> iumat;
	GS::HashTable<GSAttributeIndex, GSAttributeIndex> iufil;
	GS::HashTable<Int32, Int32> irtxt;
};

	// --- Variable declarations -------------------------------------------------------------------------------------------

	// --- Function declarations -------------------------------------------------------------------------------------------


}	// namespace Modeler

#endif // MODELIOLOOKUP_HPP