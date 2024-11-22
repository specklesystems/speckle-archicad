// *****************************************************************************
// Attribute Index Wrapper
// AttributeManager, platform-independent
//
// Namespaces:        Contact person:
//		ADB					VD
//
// [SG compatible]
// *****************************************************************************

#ifndef ADBATTRIBUTEINDEXWRAPPER_HPP
#define ADBATTRIBUTEINDEXWRAPPER_HPP

#pragma once

#include "CADInfrastructureExport.hpp"
#include "ADBAttributeIndex.hpp"

// from GSRoot
#include "Object.hpp"
#include "HashCommon.hpp"

namespace ADB {

class CADINFRASTRUCTURE_DLL_EXPORT AttributeIndexWrapper : public GS::Object {

private:
	ADB::AttributeIndex attributeIndex;

public:
	explicit AttributeIndexWrapper (const ADB::AttributeIndex& attributeIndex) :
		attributeIndex (attributeIndex)
	{}

	const ADB::AttributeIndex&			GetAttributeIndex () const;

	virtual AttributeIndexWrapper*		Clone () const override;
};
}

#endif
