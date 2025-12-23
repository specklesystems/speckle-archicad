#pragma once

#include "Algorithms.hpp"
#include "TypeTraits.hpp"
#include "ValueTypeTraits.hpp"

#include <utility>
#include <type_traits>

namespace GS {

// === PushIterator class ==============================================================================================

template <class ContainerT>
class PushIterator {
protected:
	ContainerT* container;

public:
	explicit PushIterator (ContainerT& container): container (&container) {}

	PushIterator<ContainerT>&	operator=	(const typename ContainerT::ValueType& value)	{ container->Push (value); return *this; }
	PushIterator<ContainerT>&	operator=	(typename ContainerT::ValueType&& value)		{ container->Push (std::move (value)); return *this; }
	PushIterator<ContainerT>&	operator*	()												{ return *this; }
	PushIterator<ContainerT>&	operator++	()												{ return *this; }
	PushIterator<ContainerT>	operator++	(int)											{ return *this; }

	using iterator_category = std::output_iterator_tag;
	using value_type = typename ContainerT::ValueType;
	using difference_type = void;
	using pointer = void;
	using reference = void;
};

template <class ContainerT>
inline PushIterator<ContainerT> Pusher (ContainerT& container)
{
	return PushIterator<ContainerT> (container);
}


// === InsertIterator class ============================================================================================

template <class ContainerT>
class InsertIterator {
protected:
	ContainerT*		container;
	UIndex			index;

public:
	InsertIterator (ContainerT& container, UIndex index): container (&container), index (index) {}

	InsertIterator<ContainerT>&		operator=	(const typename ContainerT::ValueType& value)	{ container->Insert (index, value); ++index; return *this; }
	InsertIterator<ContainerT>&		operator=	(typename ContainerT::ValueType&& value)		{ container->Insert (index, std::move (value)); ++index; return *this; }
	InsertIterator<ContainerT>&		operator*	()												{ return *this; }
	InsertIterator<ContainerT>&		operator++	()												{ return *this; }
	InsertIterator<ContainerT>		operator++	(int)											{ return *this; }

	using iterator_category = std::output_iterator_tag;
	using value_type = typename ContainerT::ValueType;
	using difference_type = void;
	using pointer = void;
	using reference = void;
};

template <class ContainerT>
inline InsertIterator<ContainerT> Inserter (ContainerT& container, UIndex index)
{
	return InsertIterator<ContainerT> (container, index);
}


// === AddIterator class ===============================================================================================

template <class ContainerT>
class AddIterator {
protected:
	ContainerT* container;

public:
	explicit AddIterator (ContainerT& container): container (&container) {}

	AddIterator<ContainerT>&	operator=	(const typename ContainerT::ValueType& value)	{ container->Add (value); return *this; }
	AddIterator<ContainerT>&	operator=	(typename ContainerT::ValueType&& value)		{ container->Add (std::move (value)); return *this; }
	AddIterator<ContainerT>&	operator*	()												{ return *this; }
	AddIterator<ContainerT>&	operator++	()												{ return *this; }
	AddIterator<ContainerT>		operator++	(int)											{ return *this; }

	using iterator_category = std::output_iterator_tag;
	using value_type = typename ContainerT::ValueType;
	using difference_type = void;
	using pointer = void;
	using reference = void;
};

template <class ContainerT>
inline AddIterator<ContainerT> Adder (ContainerT& container)
{
	return AddIterator<ContainerT> (container);
}


// === AppendIterator class ============================================================================================

template <class ContainerT>
class AppendIterator {
protected:
	ContainerT* container;

public:
	explicit AppendIterator (ContainerT& container): container (&container) {}

	AppendIterator<ContainerT>&		operator=	(const typename ContainerT::ValueType& value)	{ container->Append (value); return *this; }
	AppendIterator<ContainerT>&		operator=	(typename ContainerT::ValueType&& value)		{ container->Append (std::move (value)); return *this; }
	AppendIterator<ContainerT>&		operator*	()												{ return *this; }
	AppendIterator<ContainerT>&		operator++	()												{ return *this; }
	AppendIterator<ContainerT>		operator++	(int)											{ return *this; }

	using iterator_category = std::output_iterator_tag;
	using value_type = typename ContainerT::ValueType;
	using difference_type = void;
	using pointer = void;
	using reference = void;
};

template <class ContainerT>
inline AppendIterator<ContainerT> Appender (ContainerT& container)
{
	return AppendIterator<ContainerT> (container);
}

} // namespace GS
