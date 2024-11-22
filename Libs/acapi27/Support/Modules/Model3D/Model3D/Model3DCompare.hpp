// *********************************************************************************************************************
// Description:		Model comapre
//
// Module:			Modeler
// Namespace:		Modeler
// Contact person:	PP
//
// SG compatible
// *********************************************************************************************************************

#if !defined (MODEL3D_MODEL_COMPARE__HPP)
#define MODEL3D_MODEL_COMPARE__HPP

#pragma once

// from GSRoot
#include "HashSet.hpp"
#include "SharedPtr.hpp"

// from Model3D
#include "Model3D/ElemComparisonFlags.hpp"
#include "Model3D/Model3DExport.h"
#include "Model3D/DataCmpOption.hpp"

// from Geometry
#include "RealNumber.h"

namespace Modeler {
	class Elem;
	typedef GS::ConstSharedPtr<Elem> ConstElemPtr;
	class Model3DViewer;
}


namespace Modeler {

enum	ElemComparisonResult {
	Differ,
	Equal
};


class MODEL3D_DLL_EXPORT ModelCompareResult
{
public:
	ModelCompareResult () = default;
	ModelCompareResult (ModelCompareResult&& mcr) = default;

	const GS::HashSet<GS::Guid>&	GetUniqueElemsInModel1	(void) const			{ return m_uniqueElemsInModel1;		}
	const GS::HashSet<GS::Guid>&	GetUniqueElemsInModel2	(void) const			{ return m_uniqueElemsInModel2;		}
	const GS::HashSet<GS::Guid>&	GetModifiedElems		(void) const			{ return m_modifiedElems;			}

	void							AddUniqueElemsInModel1	(const GS::Guid& guid)	{ m_uniqueElemsInModel1.Add (guid);	}
	void							AddUniqueElemsInModel2	(const GS::Guid& guid)	{ m_uniqueElemsInModel2.Add (guid);	}
	void							AddModifiedElem			(const GS::Guid& guid)	{ m_modifiedElems.Add (guid);		}

private:
	GS::HashSet<GS::Guid>			m_uniqueElemsInModel1;
	GS::HashSet<GS::Guid>			m_uniqueElemsInModel2;
	GS::HashSet<GS::Guid>			m_modifiedElems;
};


ElemComparisonResult	MODEL3D_DLL_EXPORT	CompareElems	(const ConstElemPtr& elem1, const ConstElemPtr& elem2, ElemComparisonFlags flags, DataCmpOption cmpOpt, double eps = MiddleEps6);

ModelCompareResult		MODEL3D_DLL_EXPORT	CompareModels	(const Model3DViewer& model1, const Model3DViewer& model2);


}	// namespace Modeler


#endif // MODEL3D_MODEL_COMPARE__HPP
