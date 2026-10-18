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

/**
 * @brief Output manager types.
 */
enum OutputManagerType {
    /** SingleOutput */
    SingleOutput = 0,

    /** MultipleOutput */
    MultipleOutput = 1,

    /** GroupedMultipleOutput */
    GroupedMultipleOutput = 2
};

/**
 * @brief Container types.
 */
enum ContainerType {
    /** CreationOrderContainer */
    CreationOrderContainer = 0,

    /** DrawOrderContainer */
    DrawOrderContainer = 1,

    /** IndexedContainer */
    IndexedContainer = 2
};

/**
 * @brief Element save types.
 */
enum ElemSaveType {
    /** SaveElementSettings */
    SaveElementSettings = 0,

    /** SavePrimElements */
    SavePrimElements = 1,

    /** SaveBoth */
    SaveBoth = 2
};

/**
 * @brief Output used attributes types.
 */
enum OutputUsedAttributesType {
    /** Do not output attributes. */
    DoNotOutput = 0,

    /** Output inline attribute by index in Element output. */
    InlineOutput_Index = 1,

    /** Output used attributes by index after each database. */
    AfterEachDatabase_Index = 2,

    /** Output used attributes by index after full element output. */
    AfterOutputElements_Index = 3,

    /** Output inline attribute by name in Element output. */
    InlineOutput_Name = 11,

    /** Output used attributes by name after each database. */
    AfterEachDatabase_Name = 12,

    /** Output used attributes by name after full element output. */
    AfterOutputElements_Name = 13
};


typedef bool AttributeFilter [20];

template <typename ElemType>
struct IteratorElem {
	API_DatabaseInfo databaseInfo;
	ElemType		 elem;
};

}	// namespace GSAPI

#endif	// __GSAPIWRAPPERS_HPP__
