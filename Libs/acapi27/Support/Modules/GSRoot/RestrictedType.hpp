// *****************************************************************************
// 
// Description and compliance check of types narrowed by additional restrictions
// e.g. excluding some descendants.
// 
// Contact person: FNo, MB
//
// *****************************************************************************

#ifndef RESTRICTEDTYPE_HPP
#define RESTRICTEDTYPE_HPP

#include "Array.hpp"
#include "ClassInfo.hpp"
#include "TypeTraits.hpp"


namespace GS {

namespace RestrictedTypeImpl {
	template <class PossiblyRestrictedTarget>	struct CheckerFor;
	template <class PossiblyRestrictedTarget>	struct Reflector;
}




// ===== RestrictedType description ===============================================================

template <class Base, class... Restrictions>
struct RestrictedType {
	using BaseType = Base;

	static constexpr bool HasRestrictions = (0 < sizeof...(Restrictions));
};


// Forbid descendants down from Subtype.
template <class Subtype>
struct Exclude {};




// ===== Compliance queries =======================================================================

// Every descendant of Root is compatible with the possibly restricted type Target.
template <class Root, class Target>		
constexpr bool IsCompatibleHierarchy		  = RestrictedTypeImpl::CheckerFor<Target>::type::template IsCompatibleHierarchy<Root>;

// At least some descendant of Root (or Root itself) is compatible with the possibly restricted type Target.
template <class Root, class Target>		
constexpr bool IsPartiallyCompatibleHierarchy = !RestrictedTypeImpl::CheckerFor<Target>::type::template IsIncompatibleHierarchy<Root>;




// Dynamic type of obj is compatible with the possibly restricted type Target.
template <class Target, class Object>
bool IsCompatibleType (const Object& obj)
{
	using Chk = typename RestrictedTypeImpl::CheckerFor<Target>::type;
	return Chk::IsCompatibleType (obj);
}

// The described class whith ancestor KnownBase is compatible with the possibly restricted type Target.
// KnownBase is optional, can optimize unnecessary runtime checks.
template <class Target, class KnownBase = void>
bool IsCompatibleClass (const ClassInfo& classInfo)
{
	using Chk = typename RestrictedTypeImpl::CheckerFor<Target>::type;
	return Chk::template IsCompatibleClass<KnownBase> (classInfo);
}


// Actually usable pointer/reference type, be the Target either a simple or a RestrictedType.
template <class Target>
using UnrestrictedBase = typename RestrictedTypeImpl::CheckerFor<Target>::type::TBase;




// ===== Runtime info ~ reflection ================================================================

// Obtain ClassInfos of types within Exclude restrictions if Target is a RestrictedType.
template <class Target>
static Array<const ClassInfo*> GetExcludedClasses ()
{
	using Refl = typename RestrictedTypeImpl::Reflector<Target>;
	return Refl::GetExcludedClasses ();
}





// ===== Internals ================================================================================

namespace RestrictedTypeImpl {

template <class T>
constexpr bool IsGSObject = IsCompatible<T, Object>;


template <class Target>
class FastCastTo {
	template <class Obj>
	static bool IsComp (const Obj&, EnableIf<IsCompatible<Obj, Target>>* = nullptr)
	{
		return true;
	}

	template <class Obj>
	static bool IsComp (const Obj&,
						EnableIf<!AreRelated<Obj, Target>>*				= nullptr,
						EnableIf<IsGSObject<Obj> && IsGSObject<Target>>*	= nullptr)
	{
		// because of known single inheritance
		return false;
	}


	template <class Obj, class Trg = Target>
	static bool IsComp (const Obj& obj,
						EnableIf<!IsCompatible<Obj, Trg> && IsCompatible<Target, Obj>>* = nullptr,
						EnableIf<IsGSObject<Obj> && IsGSObject<Trg>>*					  = nullptr,
						decltype (Trg::GetClassInfoStatic ())							  = nullptr)
	{
		// NOTE: in very special cases obj may not have ClassInfo, currently that simply asserts.
		return obj.GetClassInfo ()->IsCompatibleWith (Target::GetClassInfoStatic ());
	}

	template <class Obj>
	static bool IsComp (const Obj& obj, ...)
	{
		return dynamic_cast<const Target*> (&obj) != nullptr;
	}

public:
	template <class Obj>
	static bool IsCompatibleType (const Obj& obj)
	{
		// nullptr is to avoid overload ambiguity --> allow using (...) as default
		return IsComp<Obj> (obj, nullptr);
	}
};




// ---- Restriction Implementations ---------------------------------------------------------------

// Specialize this template for each kind of Restriction Descriptor.
// 
// Concept of an implemented Restriction requires the following static / runtime checks:
//   + constexpr IsCompatibleHierarchy<T>:		Any descendant of type T is Compatible
//   + constexpr IsIncompatibleHierarchy<T>:	Any descendant of type T is Incompatible
//   ----
//   + IsCompatibleType	 (const T&):			pointed object is Compatible
//   + IsCompatibleClass (const ClassInfo&):	instance of described class is Compatible
//												(usable only amongst GS::Objects)
template <class Desc>
struct RestrictionImpl;


// Exclude - Forbid descendants of a subtype.
template <class Subtype>
struct RestrictionImpl<Exclude<Subtype>> {
	template <class T>
	static constexpr bool IsCompatibleHierarchy   = !GS::AreRelated<T, Subtype>		// Siblings allowed -
												  && IsGSObject<Subtype>			// But for multiple inheritance,
												  && IsGSObject<T>;					// we just cannot know!
	template <class T>
	static constexpr bool IsIncompatibleHierarchy = IsCompatible<T, Subtype>;


	template <class TRef>
	static bool IsCompatibleType (const TRef& obj)
	{
		return !FastCastTo<Subtype>::IsCompatibleType (obj);
	}

	static bool IsCompatibleClass (const ClassInfo& classInfo)
	{
		const ClassInfo* excluded = Subtype::GetClassInfoStatic ();
		return !classInfo.IsCompatibleWith (excluded);
	}
};




// ---- Restriction Enumerators -------------------------------------------------------------------

// Interfaces match the concept of singular Restrictions, except the ClassInfo checking overload
// has an added type parameter allowing us to rule out unnecessary runtime calls:
//   + IsCompatibleClass<KnownBase> (const ClassInfo&):	the described class, descendant of KnownBase,
//														is Compatible with All the restrictions.

// Helper to check conjunction of multiple restrictions.
// Intelligently optimizes runtime calls when static info is enough for decision.
template <class... Restrictions>
struct ForAll;

// Helper to check disjunction of multiple restrictions.
template <class... Restrictions>
struct ForAny;


template <class First, class... Rest>
struct ForAll<First, Rest...> {
	template <class T>	
	static constexpr bool IsCompatibleHierarchy = First::template IsCompatibleHierarchy<T> && ForAll<Rest...>::template IsCompatibleHierarchy<T>;

	template <class T>	
	static constexpr bool IsIncompatibleHierarchy = First::template IsIncompatibleHierarchy<T> && ForAll<Rest...>::template IsIncompatibleHierarchy<T>;


	template <class TRef>
	static bool IsCompatibleType (const TRef& obj)
	{
		const bool firstAccepts = First::template IsCompatibleHierarchy<TRef>
							  || !First::template IsIncompatibleHierarchy<TRef> && First::template IsCompatibleType (obj);

		return firstAccepts && ForAll<Rest...>::IsCompatibleType (obj);
	}

	template <class KnownBase = void>
	static bool IsCompatibleClass (const GS::ClassInfo& classInfo)
	{
		constexpr bool sureFirstAccept = !IsVoid<KnownBase> && First::template IsCompatibleHierarchy<KnownBase>;
		constexpr bool sureFirstReject = !IsVoid<KnownBase> && First::template IsIncompatibleHierarchy<KnownBase>;
		const bool firstAccepts = sureFirstAccept
							  || !sureFirstReject && First::IsCompatibleClass (classInfo);

		return firstAccepts && ForAll<Rest...>::template IsCompatibleClass<KnownBase> (classInfo);
	}
};

template <>
struct ForAll<> {
	template <class T>
	static constexpr bool IsCompatibleHierarchy = true;

	template <class T>
	static constexpr bool IsIncompatibleHierarchy = true;


	template <class TRef>
	static bool IsCompatibleType (const TRef&)				{ return true; }
	template <class KnownBase = void>
	static bool IsCompatibleClass (const GS::ClassInfo&)	{ return true; }
};




template <class First, class... Rest>
struct ForAny<First, Rest...> {
	template <class T>	
	static constexpr bool IsCompatibleHierarchy = First::template IsCompatibleHierarchy<T> || ForAny<Rest...>::template IsCompatibleHierarchy<T>;

	template <class T>	
	static constexpr bool IsIncompatibleHierarchy = First::template IsIncompatibleHierarchy<T> || ForAny<Rest...>::template IsIncompatibleHierarchy<T>;
};

template <>
struct ForAny<> {
	template <class T>
	static constexpr bool IsCompatibleHierarchy = false;

	template <class T>
	static constexpr bool IsIncompatibleHierarchy = false;
};




// ---- Processing - RestrictionsChecker ----------------------------------------------------------

// Requires implementations of Restrictions as parameters!
template <class Base, class... Restrictions>
struct RestrictionsChecker {
	using TBase = Base;

	static_assert (!ForAny<Restrictions...>::template IsCompatibleHierarchy<Base>, "Some of the given restrictions are irrelevant "
																				   "(i.e. always true) descending from this Base class.");

	static_assert (!ForAny<Restrictions...>::template IsIncompatibleHierarchy<Base>, "Some of the given restrictions cannot be satisfied by this Base class.");


	template <class T>
	static constexpr bool IsCompatibleHierarchy	  = IsCompatible<T, Base> && ForAll<Restrictions...>::template IsCompatibleHierarchy<T>;

	template <class T>
	static constexpr bool IsIncompatibleHierarchy = ForAny<Restrictions...>::template IsIncompatibleHierarchy<T>;


	template <class Obj>
	static bool IsCompatibleType (const Obj& obj)
	{
		return FastCastTo<Base>::IsCompatibleType (obj)
			&& ForAll<Restrictions...>::IsCompatibleType (obj);
	}

	template <class KnownBase = void>
	static bool IsCompatibleClass (const ClassInfo& classInfo)
	{
		DBASSERT (IsCompatibleIfKnown<KnownBase> (classInfo, nullptr));

		return classInfo.IsCompatibleWith (Base::GetClassInfoStatic ())
			&& ForAll<Restrictions...>::template IsCompatibleClass<KnownBase> (classInfo);
	}

private:
	template <class Known>
	static bool IsCompatibleIfKnown (const ClassInfo& classInfo, decltype (Known::GetClassInfoStatic ()) = nullptr)
	{
		return classInfo.IsCompatibleWith (Known::GetClassInfoStatic ());
	}
	template <class>
	static bool IsCompatibleIfKnown (const ClassInfo&, ...)
	{
		return true;
	}
};


// Obtain a Checker correctly parametrized with implementations, either from a RestrictedType description or a simple class.
template <class PossiblyRestrictedTarget>	
struct CheckerFor;

template <class SimpleBase>
struct CheckerFor {
	using type = RestrictionsChecker<SimpleBase>;
};

template <class Base, class... Restrictions>
struct CheckerFor<RestrictedType<Base, Restrictions...>> {
	using type = RestrictionsChecker<Base, RestrictionImpl<Restrictions>...>;
};




// ----- Simplified reflection for current usages -------------------------------------------------

template <class Target>
struct Reflector {
	static Array<const ClassInfo*> GetExcludedClasses ()
	{
		return {}; 
	}
};


template <class Base, class... Restrictions>
struct Reflector <RestrictedType<Base, Restrictions...>>
{
	static Array<const ClassInfo*> GetExcludedClasses ()
	{
		Array<const ClassInfo*> excluded;
		std::initializer_list<const ClassInfo*> exRoots { GetExclusionRoot (Restrictions {})... };
		for (const ClassInfo* r : exRoots) {
			if (r != nullptr)
				excluded.Push (r);
		}
		return excluded;
	}

private:
	template <class T>
	static const ClassInfo* GetExclusionRoot (Exclude<T>)
	{
		return T::GetClassInfoStatic (); 
	}

	template <class Anything>
	static const ClassInfo* GetExclusionRoot (Anything)
	{
		return nullptr; 
	}
};


}		// namespace RequiredTypeImp

}		// namespace GS
#endif	// RESTRICTEDTYPE_HPP
