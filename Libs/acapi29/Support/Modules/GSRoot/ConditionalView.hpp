
// *****************************************************************************
//
//                                  Class ConditionalView
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	SzoBe
//
//
//
// *****************************************************************************

// TODO C++20: I (rpoesz) think that this file can be deleted. std::views::filter could be used, but needs investigation.

#if !defined CONDITIONALVIEW_HPP
#define CONDITIONALVIEW_HPP

#pragma once

// --------------------------------- Includes ----------------------------------

#include "Optional.hpp"

// ================================ Class ConditionalView ================================

namespace GS {

namespace ConditionalViewImp {

template <class Type, class Condition>
constexpr bool TestIsFunctor (decltype (bool { std::declval<Condition> () (std::declval<const Type&> ()) })*) { return true; }

template <class...>
constexpr bool TestIsFunctor (...) { return false; }

template <class Type, class Condition>
constexpr bool IsFunctor = TestIsFunctor<Type, Condition> (nullptr);


template <class Type>
constexpr bool TestTransformCondition (decltype (TransformCondition (std::declval<const Type&> ()))*) { return true; }

template <class...>
constexpr bool TestTransformCondition (...) { return false; }

template <class T>
constexpr bool HasTransformCondition = TestTransformCondition<T> (nullptr);


template <bool hasTransformCondition>
struct ConditionalViewCreator;

template <>
struct ConditionalViewCreator<true> {
	template <class Container, class Condition>
	static decltype (auto) Create (Container&& container, Condition&& condition);
};

template <>
struct ConditionalViewCreator<false> {
	template <class Container, class Condition>
	static decltype (auto) Create (Container&& container, Condition&& condition);
};

} // namespace ConditionalViewImp


template <class Container, class Condition>
decltype (auto) CreateConditionalView (Container&& container, Condition&& condition);


template <class Container, class Condition>
class ConditionalView {
public:
	using Type = typename Container::ValueType;

private:
	using ContainerIterator = typename Container::ConstIterator;

	static constexpr bool IsConditionCompatible = ConditionalViewImp::IsFunctor<Type, Condition>;
	static_assert (IsConditionCompatible, "'Condition' must have an operator() (const T&) where 'Container::ValueType' should be convertible to 'T'!");
	static_assert (IsDecayed<Container>, "'Container' must be decayed!");
	static_assert (IsDecayed<Condition>, "'Condition' must be decayed!");

	Optional<Container>			rValueContainerSaver;

	Condition					condition;
	ContainerIterator			beginIt;
	ContainerIterator			endIt;

	ConditionalView (const Container& container, const Condition& condition);
	ConditionalView (const Container& container, Condition&& condition);
	ConditionalView (Container&& container, const Condition& condition);
	ConditionalView (Container&& container, Condition&& condition);

	template <bool hasTransformCondition>
	friend struct ConditionalViewImp::ConditionalViewCreator;

public:
	class Iterator;

	Iterator begin () const;
	Iterator end () const;

	class Iterator {
	private:
		ContainerIterator		iterator;
		const ConditionalView*	view;		// nullptr if it's an "end iterator"

		Iterator (const ConditionalView* view, const ContainerIterator& iterator);

	public:
		static Iterator	CreateBegin	(const ConditionalView* view, const ContainerIterator& begin);
		static Iterator	CreateEnd	(const ContainerIterator& end);

		const Type&		operator*	() const;
		Iterator&		operator++	();
		bool			operator==	(const Iterator& rightOp) const;
		bool			operator!=	(const Iterator& rightOp) const;
	};
};

// ================================  ConditionalViewCreator<false>  =========================================


template <class Container, class Condition>
decltype (auto) ConditionalViewImp::ConditionalViewCreator<false>::Create (Container&& container, Condition&& condition)
{
	return ConditionalView<Decay<Container>, Decay<Condition>> (std::forward<Container> (container), std::forward<Condition> (condition));
}

// ================================  ConditionalViewCreator<true>  ==========================================

template <class Container, class Condition>
decltype (auto) ConditionalViewImp::ConditionalViewCreator<true>::Create (Container&& container, Condition&& condition)
{
	using TransformConditionType = decltype (TransformCondition (std::forward<Condition> (condition)));
	return ConditionalView<Decay<Container>, Decay<TransformConditionType>> (std::forward<Container> (container), TransformCondition (std::forward<Condition> (condition)));
}


// ================================  CreateConditionalView  =======================================

template <class Container, class Condition>
decltype (auto) CreateConditionalView (Container&& container, Condition&& condition)
{
	using namespace ConditionalViewImp;

	constexpr bool HasTransformConditionValue = HasTransformCondition<Decay<Condition>>;

	return ConditionalViewCreator<HasTransformConditionValue>::Create (std::forward<Container> (container), std::forward<Condition> (condition));
}


// ================================  ConditionalView Class  =======================================


template <class Container, class Condition>
ConditionalView<Container, Condition>::ConditionalView (const Container& container, const Condition& condition) :
	condition (condition),
	beginIt (container.Begin ()),
	endIt (container.End ())
{
}


template <class Container, class Condition>
ConditionalView<Container, Condition>::ConditionalView (const Container& container, Condition&& condition) :
	condition (std::move (condition)),
	beginIt (container.Begin ()),
	endIt (container.End ())
{
}


template <class Container, class Condition>
ConditionalView<Container, Condition>::ConditionalView (Container&& container, const Condition& condition) :
	rValueContainerSaver (std::move (container)),
	condition (condition),
	beginIt (rValueContainerSaver->Begin ()),
	endIt (rValueContainerSaver->End ())
{
}


template <class Container, class Condition>
ConditionalView<Container, Condition>::ConditionalView (Container&& container, Condition&& condition) :
	rValueContainerSaver (std::move (container)),
	condition (condition),
	beginIt (rValueContainerSaver->Begin ()),
	endIt (rValueContainerSaver->End ())
{
}


template <class Container, class Condition>
typename ConditionalView<Container, Condition>::Iterator	ConditionalView<Container, Condition>::begin () const
{
	return Iterator::CreateBegin (this, beginIt);
}


template <class Container, class Condition>
typename ConditionalView<Container, Condition>::Iterator	ConditionalView<Container, Condition>::end () const
{
	return Iterator::CreateEnd (endIt);
}

// ================================  ConditionalView::Iterator Class  =============================

template <class Container, class Condition>
typename GS::ConditionalView<Container, Condition>::Iterator	GS::ConditionalView<Container, Condition>::Iterator::CreateBegin (const ConditionalView* view, const ContainerIterator& begin)
{
	Iterator it (view, begin);

	if (begin != view->endIt && !view->condition (*begin))
		++it;

	return it;
}


template <class Container, class Condition>
typename GS::ConditionalView<Container, Condition>::Iterator	GS::ConditionalView<Container, Condition>::Iterator::CreateEnd (const ContainerIterator& end)
{
	return Iterator (nullptr, end);
}


template <class Container, class Condition>
ConditionalView<Container, Condition>::Iterator::Iterator (const ConditionalView* view, const ContainerIterator& iterator) :
	iterator (iterator),
	view (view)
{
}


template <class Container, class Condition>
const typename ConditionalView<Container, Condition>::Type& ConditionalView<Container, Condition>::Iterator::operator* () const
{
	return *iterator;
}


template <class Container, class Condition>
typename ConditionalView<Container, Condition>::Iterator& ConditionalView<Container, Condition>::Iterator::operator++ ()
{
	DBASSERT (view != nullptr);
	DBASSERT (iterator != view->endIt);

	do {
		++iterator;
	} while (iterator != view->endIt && !view->condition (*iterator));

	return *this;
}


template <class Container, class Condition>
bool ConditionalView<Container, Condition>::Iterator::operator== (const Iterator& rightOp) const
{
	return iterator == rightOp.iterator;
}


template <class Container, class Condition>
bool ConditionalView<Container, Condition>::Iterator::operator!= (const Iterator& rightOp) const
{
	return iterator != rightOp.iterator;
}


} // namespace GS

#endif
