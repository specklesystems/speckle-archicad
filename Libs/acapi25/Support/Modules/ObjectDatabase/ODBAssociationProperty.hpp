
// *****************************************************************************
//
//                          Struct AssociationProperty
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// SG compatible
//
// *****************************************************************************


#if !defined ODBASSOCIATIONPROPERTY_HPP
#define ODBASSOCIATIONPROPERTY_HPP


// --------------------------------- Includes ----------------------------------

#include "ODBBase.hpp"
#include "StaticInstantiable.hpp"

#include "ODBId.hpp"

#include "FixArray.hpp"

#include <functional>


// ======================== Struct AssociationProperty =========================

namespace ODB {

enum Side {
	Left,
	Right
};

enum ObjectSide {
	LeftObject,
	RightObject,
	LinkObject
};

	// Multiplicity of the association

enum Multiplicity {
	Multiplicity11,
	Multiplicity1N,
	MultiplicityNN
};

	// Minimum multiplicity of the association

class MinLeftMultiplicity {
private:
	ULong minLeftMultiplicity;

public:
	inline explicit MinLeftMultiplicity (ULong minLeftMultiplicity): minLeftMultiplicity (minLeftMultiplicity) {}

	inline	operator ULong () const { return minLeftMultiplicity; }
};

class MinRightMultiplicity {
private:
	ULong minRightMultiplicity;

public:
	inline explicit MinRightMultiplicity (ULong minRightMultiplicity): minRightMultiplicity (minRightMultiplicity) {}

	inline	operator ULong () const { return minRightMultiplicity; }
};

	// Ownership relation

enum Ownership {
	NoOwnership,
	LeftOwnership
};

	// Copy propagation along the association

enum CopyPropagation {
	NoCopyPropagation,
	LeftCopyPropagation,
	RightCopyPropagation,
	LeftSetCopyPropagation,
	RightSetCopyPropagation
};

	// Delete propagation along the association

enum DeletePropagation {
	NoDeletePropagation,
	LeftDeletePropagation,
	RightDeletePropagation,
	LeftRightDeletePropagation
};

	// Constraining of the association

enum Constraining {
	Unconstrained,
	Constrained
};

	// Ordering of the association

enum Ordering {
	Unordered,
	ManuallyOrdered,
	RuleOrdered
};

	// Computational dependency

enum Dependency {
	NoDependency,
	LeftDependsOnRight,
	RightDependsOnLeft
};

	// Event sending

enum EventSending {
	DisableAssociationEvents,
	EnableAssociationEvents
};

	// Persistency

enum Persistency {
	PersistentInDatabase,
	Persistent,
	Transient		// transient links are always internal (can't be external) so they never imply loading
};

	// Persistent navigation

enum PersistentNavigation {
	LeftRightPersistentNavigable,
	LeftPersistentNavigable,
	RightPersistentNavigable
};

	// Owner user propagation

enum OwnerUserPropagation {
	NoOwnerUserPropagation,
	LeftOwnerUserPropagation,
	RightOwnerUserPropagation
};

	// Left role

class LeftRole {
private:
	GS::String name;

public:
	LeftRole () = default;
	explicit LeftRole (const char* name) : name (name) {}

	bool				IsEmpty () const					{ return !HasName (); }

	void				SetName (const GS::String& newName)	{ name = newName; }
	const GS::String&	GetName () const					{ return name; }
	bool				HasName () const					{ return !name.IsEmpty (); }
};

	// Right role

class RightRole {
private:
	GS::String name;

public:
	RightRole () = default;
	explicit RightRole (const char* name) : name (name) {}

	bool				IsEmpty () const					{ return !HasName (); }

	void				SetName (const GS::String& newName)	{ name = newName; }
	const GS::String&	GetName () const					{ return name; }
	bool				HasName () const					{ return !name.IsEmpty (); }
};

	// Association index

class RightIndexBase {
private:
	const GS::ClassInfo* indexType;

public:
	explicit RightIndexBase (const GS::ClassInfo* indexType): indexType (indexType) {}

	operator const GS::ClassInfo* () const { return indexType; }
};


template <class Type>
class RightIndex: public RightIndexBase {
public:
	RightIndex (): RightIndexBase (Type::GetClassInfoStatic ()) {}
};


class LeftIndexBase {
private:
	const GS::ClassInfo* indexType;

public:
	explicit LeftIndexBase (const GS::ClassInfo* indexType): indexType (indexType) {}

	operator const GS::ClassInfo* () const { return indexType; }
};


template <class Type>
class LeftIndex: public LeftIndexBase {
public:
	LeftIndex (): LeftIndexBase (Type::GetClassInfoStatic ()) {}
};


	// Custom association property

class CustomAssociationPropertyValue;

class ODB_DLL_EXPORT CustomAssociationProperty : public GS::CustomProperty {
public:
private:
	class ValueNames;

	Id				id;				// identifier of the custom property

	CustomAssociationProperty (const CustomAssociationProperty& source);				// disabled
	CustomAssociationProperty&	operator= (const CustomAssociationProperty& source);	// disabled

	static void		CreateCustomAssociationProperties ();

public:
	CustomAssociationProperty (const Id& id, const char* name, UInt32 defaultValue);
	CustomAssociationProperty (const Id& id, const char* name, int defaultValue);		// because of literals
	CustomAssociationProperty (const Id& id, const char* name, const void* defaultValue);
   ~CustomAssociationProperty ();

	Id				GetId	() const;

	CustomAssociationPropertyValue	operator() (UInt32 value) const;
	CustomAssociationPropertyValue	operator() (const void* value) const;

	static void		EnumerateInstances (const std::function<void (const CustomAssociationProperty&)>& processor);
};


class ODB_DLL_EXPORT CustomAssociationPropertyValue : public GS::CustomPropertyValue {
public:
	using CustomPropertyValue::CustomPropertyValue;

	const CustomAssociationProperty&	GetCustomProperty () const;
};

class ODB_DLL_EXPORT CustomAssociationPropertyValueStatic : public CustomAssociationPropertyValue, public GS::StaticInstantiable {
public:
	CustomAssociationPropertyValueStatic ();
	explicit CustomAssociationPropertyValueStatic (const CustomAssociationProperty& customProperty);
	CustomAssociationPropertyValueStatic (const CustomAssociationProperty& customProperty, UInt32 value, const char* valueName = nullptr);
	CustomAssociationPropertyValueStatic (const CustomAssociationProperty& customProperty, int value, const char* valueName = nullptr);	// because of literals
	CustomAssociationPropertyValueStatic (const CustomAssociationProperty& customProperty, void* value, const char* valueName = nullptr);
	CustomAssociationPropertyValueStatic (const CustomAssociationProperty& customProperty, const CustomAssociationProperty::Value& value, const char* valueName = nullptr);
};


	// Modification

ODB_DLL_EXPORT extern const CustomAssociationProperty Modification;

ODB_DLL_EXPORT extern const CustomAssociationPropertyValue Modifiable;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue ModifiableByLeft;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue ModifiableByRight;

	// Context dependent identification impact

ODB_DLL_EXPORT extern const CustomAssociationProperty IdentificationImpact;

ODB_DLL_EXPORT extern const CustomAssociationPropertyValue NoIdentificationImpact;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue ImpliesContextDependentIdentificationForLeft;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue ImpliesContextDependentIdentificationForRight;

enum IdentificationImpactValue { NoIdentificationImpactValue, ImpliesContextDependentIdentificationForLeftValue, ImpliesContextDependentIdentificationForRightValue };

	// Identification context

ODB_DLL_EXPORT extern const CustomAssociationProperty IdentificationContext;

ODB_DLL_EXPORT extern const CustomAssociationPropertyValue NotIdentificationContext;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue IdentificationContextForLeft;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue IdentificationContextForRight;

enum IdentificationContextValue { NotIdentificationContextValue, IdentificationContextForLeftValue, IdentificationContextForRightValue };

	// Association derivation

ODB_DLL_EXPORT extern const CustomAssociationProperty AssociationDerivation;

ODB_DLL_EXPORT extern const CustomAssociationPropertyValue CoreAssociation;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue DerivedAssociation;

enum AssociationDerivationValue { CoreAssociationValue, DerivedAssociationValue };

	// Link derivation propagation

ODB_DLL_EXPORT extern const CustomAssociationProperty LinkDerivationPropagation;

ODB_DLL_EXPORT extern const CustomAssociationPropertyValue NoLinkDerivationPropagation;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue LinkDerivationIsPropagatedFromLeftObject;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue LinkDerivationIsPropagatedFromRightObject;

enum LinkDerivationPropagationValue { NoLinkDerivationPropagationValue, LinkDerivationIsPropagatedFromLeftObjectValue, LinkDerivationIsPropagatedFromRightObjectValue };

	// Link modification without modification scope

ODB_DLL_EXPORT extern const CustomAssociationProperty LinkModificationWithoutModificationScope;

ODB_DLL_EXPORT extern const CustomAssociationPropertyValue LinksAreNotModifiableWithoutModificationScope;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue LinksAreModifiableWithoutModificationScope;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue LinksAreReorderableWithoutModificationScope;

enum LinkModificationWithoutModificationScopeValue { LinksAreNotModifiableWithoutModificationScopeValue, LinksAreModifiableWithoutModificationScopeValue, LinksAreReorderableWithoutModificationScopeValue };

	// Link modification without modification scope propagation

ODB_DLL_EXPORT extern const CustomAssociationProperty LinkModificationWithoutModificationScopePropagation;

ODB_DLL_EXPORT extern const CustomAssociationPropertyValue NoLinkModificationWithoutModificationScopePropagation;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue LinkModificationWithoutModificationScopeIsPropagatedFromLeftObject;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue LinkModificationWithoutModificationScopeIsPropagatedFromRightObject;

enum LinkModificationWithoutModificationScopePropagationValue { NoLinkModificationWithoutModificationScopePropagationValue, LinkModificationWithoutModificationScopeIsPropagatedFromLeftObjectValue, LinkModificationWithoutModificationScopeIsPropagatedFromRightObjectValue };


	// Distributed object creation

ODB_DLL_EXPORT extern const CustomAssociationProperty DistributedObjectCreation;

ODB_DLL_EXPORT extern const CustomAssociationPropertyValue NoDistributedObjectCreation;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue ImpliesDistributedObjectCreationForLeft;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue ImpliesDistributedObjectCreationForRight;


	// Release operation usage

ODB_DLL_EXPORT extern const CustomAssociationProperty ReleaseOperationUsage;

ODB_DLL_EXPORT extern const CustomAssociationPropertyValue ReleaseOperationIsNotUsed;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue ReleaseOperationIsUsed;


// IsAssociationCurrent

ODB_DLL_EXPORT extern const CustomAssociationProperty IsAssociationCurrent;

ODB_DLL_EXPORT extern const CustomAssociationPropertyValue CurrentAssociation;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValue OldAssociation;


	// Association Visibility

ODB_DLL_EXPORT extern const CustomAssociationProperty AssociationVisibility;

ODB_DLL_EXPORT extern const CustomAssociationPropertyValue		 AssociationIsVisible;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValueStatic AssociationIsNotVisibleForLeft;
ODB_DLL_EXPORT extern const CustomAssociationPropertyValueStatic AssociationIsNotVisibleForRight;



	// Describes the possible association properties

struct ODB_DLL_EXPORT AssociationProperty {
	ULong					minLeftMultiplicity		= 0;
	ULong					minRightMultiplicity	= 0;
	Ownership				ownership				= NoOwnership;
	CopyPropagation			copyPropagation			= NoCopyPropagation;
	DeletePropagation		deletePropagation		= NoDeletePropagation;
	Constraining			constraining			= Unconstrained;
	Ordering				ordering				= Unordered;
	Dependency				dependency				= NoDependency;
	EventSending			eventSending			= DisableAssociationEvents;
	Persistency				persistency				= PersistentInDatabase;
	PersistentNavigation	persistentNavigation	= RightPersistentNavigable;
	OwnerUserPropagation	ownerUserPropagation	= NoOwnerUserPropagation;
	LeftRole				leftRole;
	RightRole				rightRole;

	enum { MaxCustomAssociationPropertyValueCount = 16 };
	GS::FixArray<const CustomAssociationPropertyValue*, MaxCustomAssociationPropertyValueCount> customAssociationPropertyValues;
	ULong	customAssociationPropertyValueCount = 0;

	enum { MaxCustomAssociationPropertyValueStaticCount = 16 };
	GS::FixArray<const CustomAssociationPropertyValueStatic*, MaxCustomAssociationPropertyValueStaticCount> customAssociationPropertyValueStatics;
	ULong	customAssociationPropertyValueStaticCount = 0;

	enum { MaxRightIndexCount = 8 };
	GS::FixArray<const GS::ClassInfo*, MaxRightIndexCount> rightIndices;
	ULong	rightIndexCount = 0;

	enum { MaxLeftIndexCount = 8 };
	GS::FixArray<const GS::ClassInfo*, MaxLeftIndexCount> leftIndices;
	ULong	leftIndexCount = 0;

	static const ULong				   DefaultMinLeftMultiplicity	= 0;
	static const ULong				   DefaultMinRightMultiplicity	= 0;
	static const Ownership             DefaultOwnership				= NoOwnership;
	static const CopyPropagation       DefaultCopyPropagation		= NoCopyPropagation;
	static const DeletePropagation     DefaultDeletePropagation		= NoDeletePropagation;
	static const Constraining          DefaultConstraining			= Unconstrained;
	static const Ordering              DefaultOrdering				= Unordered;
	static const Dependency            DefaultDependency			= NoDependency;
	static const EventSending          DefaultEventSending			= DisableAssociationEvents;
	static const Persistency           DefaultPersistency			= PersistentInDatabase;
	static const PersistentNavigation  DefaultPersistentNavigation	= RightPersistentNavigable;
	static const OwnerUserPropagation  DefaultOwnerUserPropagation  = NoOwnerUserPropagation;

	AssociationProperty ();
	AssociationProperty (MinLeftMultiplicity minLeftMultiplicity);
	AssociationProperty (MinRightMultiplicity minRightMultiplicity);
	AssociationProperty (Ownership ownership);
	AssociationProperty (CopyPropagation copyPropagation);
	AssociationProperty (DeletePropagation deletePropagation);
	AssociationProperty (Constraining constraining);
	AssociationProperty (Ordering ordering);
	AssociationProperty (Dependency dependency);
	AssociationProperty (EventSending eventSending);
	AssociationProperty (Persistency persistency);
	AssociationProperty (PersistentNavigation persistentNavigation);
	AssociationProperty (OwnerUserPropagation ownerUserPropagation);
	AssociationProperty (const CustomAssociationPropertyValue& customAssociationPropertyValue);
	AssociationProperty (const CustomAssociationPropertyValueStatic& customAssociationPropertyValueStatic);
	AssociationProperty (const RightIndexBase& index);
	AssociationProperty (const LeftIndexBase& index);
	AssociationProperty (const LeftRole& leftRole);
	AssociationProperty (const RightRole& rightRole);

	ODB_DLL_EXPORT friend AssociationProperty	operator+ (const AssociationProperty& leftOp, const AssociationProperty& rightOp);
};

ODB_DLL_EXPORT AssociationProperty	operator+ (const AssociationProperty& leftOp, const AssociationProperty& rightOp);

}	// namespace ODB


#endif
