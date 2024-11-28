#ifndef __GSAPIWRAPPERS_HPP__
#define __GSAPIWRAPPERS_HPP__

#include "APIdefs_Database.h"
#include "APIdefs_Attributes.h"
#include "APIdefs_Properties.h"

namespace GSAPI {

template <typename ElemType>
struct Element {
	API_ElemType     elemType;
	API_Guid         guid;
	ElemType         element;
	API_ElementMemo* memo;
};

struct PrimElement {
	API_PrimElement primElem;
	GSPtr           shapeProcParam1;
	GSPtr           shapeProcParam2;
	GSPtr           shapeProcParam3;
};

enum OutputManagerType {
    SingleOutput   = 0,
    MultipleOutput = 1,
	GroupedMultipleOutput = 2

};

enum ContainerType {
    CreationOrderContainer = 0,
    DrawOrderContainer     = 1,
    IndexedContainer       = 2
};

enum ElemSaveType {
	SaveElementSettings = 0,
	SavePrimElements    = 1,
	SaveBoth            = 2
};

enum OutputUsedAttributesType {
	DoNotOutput               = 0,	///< Do not output attributes.
	InlineOutput_Index        = 1,	///< Output inline attribute by index in Element output.
	AfterEachDatabase_Index   = 2,	///< Output used attributes by index after each database.
	AfterOutputElements_Index = 3,	///< Output used attributes by index after full element output.
	InlineOutput_Name         = 11,	///< Output inline attribute by name in Element output.
	AfterEachDatabase_Name    = 12,	///< Output used attributes by name after each database.
	AfterOutputElements_Name  = 13	///< Output used attributes by name after full element output.
};

typedef bool AttributeFilter [20];

template <typename ElemType>
struct IteratorElem {
	API_DatabaseInfo databaseInfo;
	ElemType		 elem;
};

}	// namespace GSAPI

#endif	// __GSAPIWRAPPERS_HPP__
