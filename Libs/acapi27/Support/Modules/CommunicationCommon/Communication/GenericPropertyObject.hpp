
// *****************************************************************************
//
// Declaration and implementation of GenericPropertyObject class
//
// Module:			CommunicationCommon
// Namespace:		Communication
// Contact person:	SN
//
// *****************************************************************************

#ifndef COMMUNICATION_GENERICPROPERTYOBJECT_HPP
#define COMMUNICATION_GENERICPROPERTYOBJECT_HPP

#pragma once


// --- Includes ----------------------------------------------------------------

#include "Communication/PropertyObject.hpp"



// --- GenericPropertyObject class ---------------------------------------------

namespace Communication {

template<class ValueT>
class GenericPropertyObject : public PropertyObject {

// Data members:
private:
	ValueT						m_value;

// Construction / destruction:
public:
			 GenericPropertyObject ();
	explicit GenericPropertyObject (const ValueT& value);
	explicit GenericPropertyObject (ValueT&& value);

// Operator overloading:
public:
	bool						operator == (const GenericPropertyObject& rhs) const;
	bool						operator != (const GenericPropertyObject& rhs) const;

// PropertyObject overrides:
public:
	virtual bool				Equals (const PropertyObject& rhs) const override;
	
	virtual PropertyObject*		Clone () const override;

// Operations:
public:
	void						SetValue (const ValueT& value);
	void						SetValue (ValueT&& value);

	const ValueT&				GetValue () const;
	ValueT&						GetValue ();

};

////////////////////////////////////////////////////////////////////////////////
// GenericPropertyObject implementation

////////////////////////////////////////////////////////////////////////////////
// Construction / destruction
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Default constructor
// -----------------------------------------------------------------------------

template<class ValueT>
inline GenericPropertyObject<ValueT>::GenericPropertyObject () :
	m_value ()
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<class ValueT>
inline GenericPropertyObject<ValueT>::GenericPropertyObject (const ValueT& value) :
	m_value (value)
{
	// Empty constructor body
}

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

template<class ValueT>
inline GenericPropertyObject<ValueT>::GenericPropertyObject (ValueT&& value) :
	m_value (std::move (value))
{
	// Empty constructor body
}

////////////////////////////////////////////////////////////////////////////////
// Operator overloading
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// operator ==
// -----------------------------------------------------------------------------

template<class ValueT>
inline bool		GenericPropertyObject<ValueT>::operator == (const GenericPropertyObject& rhs) const
{
	if (this != &rhs) {
		return (m_value == rhs.m_value);
	}

	return true;
}

// -----------------------------------------------------------------------------
// operator !=
// -----------------------------------------------------------------------------

template<class ValueT>
inline bool		GenericPropertyObject<ValueT>::operator != (const GenericPropertyObject& rhs) const
{
	return !operator == (rhs);
}

////////////////////////////////////////////////////////////////////////////////
// PropertyObject overrides
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// Equals
// -----------------------------------------------------------------------------

template<class ValueT>
bool	GenericPropertyObject<ValueT>::Equals (const PropertyObject& rhs) const
{
	const GenericPropertyObject<ValueT>* genericPropertyObject = dynamic_cast<const GenericPropertyObject<ValueT>*> (&rhs);
	if (genericPropertyObject != nullptr) {
		return operator == (*genericPropertyObject);
	}

	return false;
}
	
// -----------------------------------------------------------------------------
// Clone
// -----------------------------------------------------------------------------

template<class ValueT>
PropertyObject*		GenericPropertyObject<ValueT>::Clone () const
{
	return new GenericPropertyObject<ValueT> (*this);
}

////////////////////////////////////////////////////////////////////////////////
// Operations
////////////////////////////////////////////////////////////////////////////////

// -----------------------------------------------------------------------------
// SetValue
// -----------------------------------------------------------------------------

template<class ValueT>
inline void		GenericPropertyObject<ValueT>::SetValue (const ValueT& value)
{
	m_value = value;
}

// -----------------------------------------------------------------------------
// SetValue
// -----------------------------------------------------------------------------

template<class ValueT>
inline void		GenericPropertyObject<ValueT>::SetValue (ValueT&& value)
{
	m_value = std::move (value);
}

// -----------------------------------------------------------------------------
// GetValue
// -----------------------------------------------------------------------------

template<class ValueT>
inline const ValueT&	GenericPropertyObject<ValueT>::GetValue () const
{
	return m_value;
}

// -----------------------------------------------------------------------------
// GetValue
// -----------------------------------------------------------------------------

template<class ValueT>
inline ValueT&	GenericPropertyObject<ValueT>::GetValue ()
{
	return m_value;
}

}

#endif // COMMUNICATION_GENERICPROPERTYOBJECT_HPP