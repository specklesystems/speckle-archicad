// *********************************************************************************************************************
// Description:		Owner of a Counted shared pointer template
//					This is a guard, owns the shared object: only this guard may really deallocate the object and it has to deallocate the object, so it determines the scope of the object.
// Module:			GSRoot
// Namespace:		GS
// Contact person:	AACS
//
// *********************************************************************************************************************

#if !defined(SharedPtrGuard_HPP)
#define SharedPtrGuard_HPP

#pragma once

#include	"SharedPtr.hpp"

namespace GS {
	template<typename TPointee>
	class [[nodiscard]] SharedPtrGuard
	{
	public:
		SharedPtrGuard ();
		explicit SharedPtrGuard (const SharedPtr <TPointee>& src);
		virtual ~SharedPtrGuard ();
		const SharedPtrGuard<TPointee> & operator = (const SharedPtr <TPointee>& src);

		const SharedPtr <TPointee>& GetSharedPtr () const;

	private:
		SharedPtr <TPointee> ptr;
	};


	template<typename TPointee>
	class [[nodiscard]] ConstSharedPtrGuard
	{
	public:
		ConstSharedPtrGuard ();
		explicit ConstSharedPtrGuard (const ConstSharedPtr<TPointee>& source);
		virtual ~ConstSharedPtrGuard ();
		const ConstSharedPtrGuard<TPointee> & operator = (const ConstSharedPtr <TPointee>& src);

		const ConstSharedPtr <TPointee>& GetSharedPtr () const;

	private:
		ConstSharedPtr <TPointee> ptr;
	};







	//implementations: 

	template <typename TPointee>
	inline	SharedPtrGuard<TPointee>::SharedPtrGuard ()
		: ptr (nullptr)
	{
	}

	template <typename TPointee>
	inline	SharedPtrGuard<TPointee>::SharedPtrGuard (const SharedPtr <TPointee>& src)
		: ptr (src)
	{
	}

	template <typename TPointee>
	inline	SharedPtrGuard<TPointee>::~SharedPtrGuard ()
	{
		//ToDo AACS: Here we do an assert for now, later we may have more radical things, e.g. termination...
		DBASSERT (ptr == nullptr || ptr.GetRefCount () == 1);
	}

	template <typename TPointee>
	inline const SharedPtrGuard<TPointee> & SharedPtrGuard<TPointee>::operator = (const SharedPtr <TPointee>& src)
	{
		//ToDo AACS: Here we do an assert for now, later we may have more radical things, e.g. termination...
		DBASSERT (ptr == nullptr);
		ptr = src;
		return *this;
	}

	template <typename TPointee>
	inline	const SharedPtr <TPointee>& SharedPtrGuard<TPointee>::GetSharedPtr () const
	{
		return ptr;
	}





	template <typename TPointee>
	inline	ConstSharedPtrGuard<TPointee>::ConstSharedPtrGuard ()
		: ptr (nullptr)
	{
	}

	template <typename TPointee>
	inline	ConstSharedPtrGuard<TPointee>::ConstSharedPtrGuard (const ConstSharedPtr <TPointee>& src)
		: ptr (src)
	{
	}

	template <typename TPointee>
	inline	ConstSharedPtrGuard<TPointee>::~ConstSharedPtrGuard ()
	{
		//ToDo AACS: Here we do an assert for now, later we may have more radical things, e.g. termination...
		DBASSERT (ptr == nullptr || ptr.GetRefCount () == 1);
	}

	template <typename TPointee>
	inline const ConstSharedPtrGuard<TPointee> & ConstSharedPtrGuard<TPointee>::operator = (const ConstSharedPtr <TPointee>& src)
	{
		//ToDo AACS: Here we do an assert for now, later we may have more radical things, e.g. termination...
		DBASSERT (ptr == nullptr);
		ptr = src;
		return *this;
	}

	template <typename TPointee>
	inline	const ConstSharedPtr <TPointee>& ConstSharedPtrGuard<TPointee>::GetSharedPtr () const
	{
		return ptr;
	}
}		// namespace
#endif
