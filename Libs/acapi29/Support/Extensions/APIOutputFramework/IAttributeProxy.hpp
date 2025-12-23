#ifndef __IATTRIBUTEPROXY_HPP__
#define __IATTRIBUTEPROXY_HPP__

#include "IAPIPseudoContainer.hpp"
#include "AttributeIterator.hpp"
#include "UniString.hpp"

namespace GSAPI {

/**
 * @interface
 */
class IAttributeProxy : public IAPIPseudoContainer<GSAPI::IteratorElem <API_Attribute>, AttributeFilter, AttributeIterator>
{
public:
	virtual		~IAttributeProxy ();

	virtual void						SetUsedAttribute			(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) = 0;
    virtual API_Attribute				GetAttribute				(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const = 0;
	virtual const API_Attribute&		GetProxiedAttribute			(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const = 0;
	virtual API_AttributeDefExt			GetAttributeDefExt			(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const = 0;
	virtual const API_AttributeDefExt&	GetProxiedAttributeDefExt	(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const = 0;
	virtual GS::UniString				GetAttributeName			(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const = 0;
	virtual GS::UniString				GetProxiedAttributeName		(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) const = 0;

	const API_Attribute&		GetUsedAttribute		(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) { SetUsedAttribute (dbInfo, attributeType, index); return GetProxiedAttribute (dbInfo, attributeType, index); }
	const API_AttributeDefExt&	GetUsedAttributeDefExt	(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) { SetUsedAttribute (dbInfo, attributeType, index); return GetProxiedAttributeDefExt (dbInfo, attributeType, index); }
	GS::UniString				GetUsedAttributeName	(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType, API_AttributeIndex index) { SetUsedAttribute (dbInfo, attributeType, index); return GetProxiedAttributeName (dbInfo, attributeType, index); }

	// Additions to IAPIPseudoContainer interface
	virtual PseudoIterator			Begin	(const API_DatabaseUnId& dbUnId) const = 0;
    virtual const PseudoIterator	End		(const API_DatabaseUnId& dbUnId) const = 0;

	virtual PseudoIterator			Begin	(const API_DatabaseInfo& dbInfo) const = 0;
    virtual const PseudoIterator	End		(const API_DatabaseInfo& dbInfo) const = 0;

	virtual PseudoIterator			Begin	(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType) const = 0;
    virtual const PseudoIterator	End		(const API_DatabaseInfo& dbInfo, API_AttrTypeID attributeType) const = 0;
};

}

#endif //__IATTRIBUTEPROXY_HPP__
