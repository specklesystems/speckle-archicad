
#include "AttributeIterator.hpp"


bool GSAPI::AttributeIterator::operator== (const GSAPI::AttributeIterator& it) const
{
    if (((&(it.parameters.container)) == (&((*this).parameters.container))) &&
		(it.parameters.currentAttribute.databaseInfo == (*this).parameters.currentAttribute.databaseInfo) &&
		(it.parameters.currentAttribute.elem.header.typeID == (*this).parameters.currentAttribute.elem.header.typeID) &&
		(it.parameters.currentAttribute.elem.header.index == (*this).parameters.currentAttribute.elem.header.index))
    {
        return true;
    } else {
        return false;
    }
}
