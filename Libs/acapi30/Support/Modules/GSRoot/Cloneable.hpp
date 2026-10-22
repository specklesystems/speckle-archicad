
// *****************************************************************************
//
//                                Class Cloneable
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB
//
// SG compatible
//
// *****************************************************************************


#ifndef GS_CLONEABLE_HPP
#define GS_CLONEABLE_HPP

#include "Definitions.hpp"
#include "Owner.hpp"
#include "TypeTraits.hpp"


namespace GS {


template <typename Type>
struct DefaultCloneOperations {
	static Type*	Clone  (const Type& data)	 { return data.Clone (); }
	static void		Delete (Type* data) noexcept { delete data; }
};


template <typename Base, template <typename> class CloneOperations = DefaultCloneOperations>
class Cloneable {
private:
	Base* value = nullptr;

	static_assert (IsDecayed<Base>, "'Base' should be decayed.");

	template <typename, template <typename> class>
	friend class Cloneable;

public:
	Cloneable () = default;
	explicit Cloneable (const Base& value);

	Cloneable (Owner<Base> value);

	template <typename Derived, typename = EnableIf<IsCompatible<Derived, Base>>>
	Cloneable (Owner<Derived> value);

	Cloneable (const Cloneable& source);
	Cloneable (Cloneable&& source) noexcept;

	template <typename Derived, typename = EnableIf<IsCompatible<Derived, Base>>>
	Cloneable (const Cloneable<Derived>& source);

	template <typename Derived, typename = EnableIf<IsCompatible<Derived, Base>>>
	Cloneable (Cloneable<Derived>&& source) noexcept;

   ~Cloneable ();

	Cloneable&	operator= (const Cloneable& source);
	Cloneable&	operator= (Cloneable&& source);

	template <typename Derived, typename = EnableIf<IsCompatible<Derived, Base>>>
	Cloneable&	operator= (const Cloneable<Derived>& source);

	template <typename Derived, typename = EnableIf<IsCompatible<Derived, Base>>>
	Cloneable&	operator= (Cloneable<Derived>&& source);

	Cloneable&	operator= (const Base& source);
	Cloneable&	operator= (Owner<Base> source);

	template <typename Derived, typename = EnableIf<IsCompatible<Derived, Base>>>
	Cloneable&	operator= (Owner<Derived> source);

	void		Clear ();

	Base&		operator*	() gs_lifebound;
	const Base&	operator*	() const gs_lifebound;

	Base*		operator->	() gs_lifebound;
	const Base*	operator->	() const gs_lifebound;

	Base*		Get			() gs_lifebound;
	const Base*	Get			() const gs_lifebound;

	Base*		Release ();

	bool		IsEmpty () const;
	bool		HasValue () const;
};


template <typename Base, template <typename> class CloneOperations>
Cloneable<Base, CloneOperations>::Cloneable (const Base& value) :
	value (CloneOperations<Base>::Clone (value))
{
}


template <typename Base, template <typename> class CloneOperations>
Cloneable<Base, CloneOperations>::Cloneable (Owner<Base> value) :
	value (value.Release ())
{
}


template <typename Base, template <typename> class CloneOperations>
template <typename Derived, typename /* = SFINAE */>
Cloneable<Base, CloneOperations>::Cloneable (Owner<Derived> value) :
	value (value.Release ())
{
	static_assert (HasVirtualDestructor<Base>);
}


template <typename Base, template <typename> class CloneOperations>
Cloneable<Base, CloneOperations>::Cloneable (const Cloneable& source) :
	value (source.value != nullptr ? CloneOperations<Base>::Clone (*source.value) : nullptr)
{
}


template <typename Base, template <typename> class CloneOperations>
Cloneable<Base, CloneOperations>::Cloneable (Cloneable&& source) noexcept :
	value (source.value)
{
	source.value = nullptr;
}


template <typename Base, template <typename> class CloneOperations>
template <typename Derived, typename /* = SFINAE */>
Cloneable<Base, CloneOperations>::Cloneable (const Cloneable<Derived>& source) :
	value (source.value != nullptr ? CloneOperations<Base>::Clone (*source.value) : nullptr)
{
	static_assert (HasVirtualDestructor<Base>);
}


template <typename Base, template <typename> class CloneOperations>
template <typename Derived, typename /* = SFINAE */>
Cloneable<Base, CloneOperations>::Cloneable (Cloneable<Derived>&& source) noexcept :
	value (source.value)
{
	static_assert (HasVirtualDestructor<Base>);

	source.value = nullptr;
}


template <typename Base, template <typename> class CloneOperations>
Cloneable<Base, CloneOperations>::~Cloneable ()
{
	CloneOperations<Base>::Delete (value);
}


template <typename Base, template <typename> class CloneOperations>
Cloneable<Base, CloneOperations>&	Cloneable<Base, CloneOperations>::operator= (const Cloneable& source)
{
	if (&source != this) {
		CloneOperations<Base>::Delete (value);
		value = source.value != nullptr ? CloneOperations<Base>::Clone (*source.value) : nullptr;
	}

	return *this;
}


template <typename Base, template <typename> class CloneOperations>
Cloneable<Base, CloneOperations>&	Cloneable<Base, CloneOperations>::operator= (Cloneable&& source)
{
	CloneOperations<Base>::Delete (value);
	value = source.value;
	source.value = nullptr;

	return *this;
}


template <typename Base, template <typename> class CloneOperations>
template <typename Derived, typename /* = SFINAE */>
Cloneable<Base, CloneOperations>&	Cloneable<Base, CloneOperations>::operator= (const Cloneable<Derived>& source)
{
	static_assert (HasVirtualDestructor<Base>);

	if (&source != this) {
		CloneOperations<Base>::Delete (value);
		value = (source.value != nullptr) ? CloneOperations<Base>::Clone (*source.value) : nullptr;
	}

	return *this;
}


template <typename Base, template <typename> class CloneOperations>
template <typename Derived, typename /* = SFINAE */>
Cloneable<Base, CloneOperations>&	Cloneable<Base, CloneOperations>::operator= (Cloneable<Derived>&& source)
{
	static_assert (HasVirtualDestructor<Base>);

	CloneOperations<Base>::Delete (value);
	value = source.value;
	source.value = nullptr;

	return *this;
}


template <typename Base, template <typename> class CloneOperations>
Cloneable<Base, CloneOperations>&	Cloneable<Base, CloneOperations>::operator= (const Base& source)
{
	CloneOperations<Base>::Delete (value);
	value = CloneOperations<Base>::Clone (source);

	return *this;
}


template <typename Base, template <typename> class CloneOperations>
Cloneable<Base, CloneOperations>&	Cloneable<Base, CloneOperations>::operator= (Owner<Base> source)
{
	CloneOperations<Base>::Delete (value);
	value = source.Release ();

	return *this;
}


template <typename Base, template <typename> class CloneOperations>
template <typename Derived, typename /* = SFINAE */>
Cloneable<Base, CloneOperations>&	Cloneable<Base, CloneOperations>::operator= (Owner<Derived> source)
{
	static_assert (HasVirtualDestructor<Base>);

	CloneOperations<Base>::Delete (value);
	value = source.Release ();

	return *this;
}


template <typename Base, template <typename> class CloneOperations>
void	Cloneable<Base, CloneOperations>::Clear ()
{
	CloneOperations<Base>::Delete (value);
	value = nullptr;
}


template <typename Base, template <typename> class CloneOperations>
Base&	Cloneable<Base, CloneOperations>::operator* ()
{
	PRECOND_DB (value != nullptr);

	return *value;
}


template <typename Base, template <typename> class CloneOperations>
const Base&		Cloneable<Base, CloneOperations>::operator* () const
{
	PRECOND_DB (value != nullptr);

	return *value;
}


template <typename Base, template <typename> class CloneOperations>
Base*	Cloneable<Base, CloneOperations>::operator-> ()
{
	PRECOND_DB (value != nullptr);

	return value;
}


template <typename Base, template <typename> class CloneOperations>
const Base*		Cloneable<Base, CloneOperations>::operator-> () const
{
	PRECOND_DB (value != nullptr);

	return value;
}


template <typename Base, template <typename> class CloneOperations>
Base*	Cloneable<Base, CloneOperations>::Get ()
{
	return value;
}


template <typename Base, template <typename> class CloneOperations>
const Base*		Cloneable<Base, CloneOperations>::Get () const
{
	return value;
}


template <typename Base, template <typename> class CloneOperations>
Base*	Cloneable<Base, CloneOperations>::Release ()
{
	Base* result = value;
	value = nullptr;
	return result;
}


template <typename Base, template <typename> class CloneOperations>
bool	Cloneable<Base, CloneOperations>::IsEmpty () const
{
	return value == nullptr;
}


template <typename Base, template <typename> class CloneOperations>
bool	Cloneable<Base, CloneOperations>::HasValue () const
{
	return value != nullptr;
}


/* ================================================================================================================== */


template<typename T, typename... Args>
Cloneable<T>	NewCloneable (Args&&... args)
{
	return Cloneable<T> { NewOwned<T> (std::forward<Args> (args)...) };
}


}	// namespace GS


#endif
