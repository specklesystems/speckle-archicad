// *****************************************************************************
//
//                     Classes: Query
//                              QueryExpression
//                              BinaryQueryExpression,
//                              AndQueryExpression
//                              OrQueryExpression,
//                              DiffQueryExpression
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// *****************************************************************************


#ifndef ODBQUERY_HPP
#define ODBQUERY_HPP


// --------------------------------- Includes ----------------------------------

#include "ODBBase.hpp"

namespace GS { class String; }

namespace ODB { class Object; }
namespace ODB { class Index; }
namespace ODB { template <class Type> class Ref; }
namespace ODB { template <class Type> class ConstRef; }
namespace ODB { template <class Type> class RefList; }
namespace ODB { template <class Type> class ConstRefList; }


// ================================ Class Query ================================

namespace ODB {

class ODB_DLL_EXPORT Query : public GS::Object {
	DECLARE_CLASS_INFO

public:
	class Scope;
	class ConstScope;
	struct Subject;
	struct SubjectClass;

protected:
	Query ();

	virtual	void	DeleteChildren ();
	static void		DeleteChildren (Query* query);

	virtual void	ExecuteCustom (Scope* scope, RefList<ODB::Object>* result) const;
	virtual void	ExecuteCustom (ConstScope* scope, ConstRefList<ODB::Object>* result) const;

	virtual UInt32	ExecuteCustom (Scope* scope) const;
	virtual UInt32	ExecuteCustom (ConstScope* scope) const;

public:
	Query (const Query& source);
	Query&	operator= (const Query& source);
   ~Query ();

	virtual	Query*	Clone () const override;
	virtual	Query*	CloneComposite () const;

	static void		DeleteComposite (Query* query);

		// Executing the query

	enum ResultMode { Overwrite, Append };

	void	Execute (Scope*	scope, RefList<ODB::Object>* result, ResultMode resultMode = Overwrite) const;
	void	Execute (ConstScope* scope, ConstRefList<ODB::Object>* result, ResultMode resultMode = Overwrite) const;

	UInt32	Execute (Scope* scope) const;
	UInt32	Execute (ConstScope* scope) const;

		// Query condition

	virtual bool	Matches (const ObjectConstRef& object) const = 0;
	inline  bool	Matches (const ObjectRef& object) const;

	virtual bool	Matches (const Subject& subject) const;

		// Debug and test

	virtual GS::String	ToText () const;

		// Types

	class ODB_DLL_EXPORT ScopeBase {
	public:
		virtual bool			HasIndexSupport		(const Query& query) const = 0;
		virtual const Index*	FindExecutableIndex (const Query& query) const = 0;

		virtual UInt32			GetMatchingObjectCount (const Query& query) const = 0;

        virtual ~ScopeBase ();
	};

	class ODB_DLL_EXPORT Scope : public ScopeBase {
	public:
		virtual void	AppendMatchingObjects (const Query& query, RefList<ODB::Object>* result) = 0;

		virtual UInt32	GetMatchingObjectCount (const Query& query) const override;

        virtual ~Scope ();
	};

	class ODB_DLL_EXPORT ConstScope : public ScopeBase {
	public:
		virtual void	AppendMatchingObjects (const Query& query, ConstRefList<ODB::Object>* result) const = 0;

		virtual UInt32	GetMatchingObjectCount (const Query& query) const override;

        virtual ~ConstScope ();
	};

	struct ODB_DLL_EXPORT SubjectClass {};

	struct ODB_DLL_EXPORT Subject {
		const SubjectClass* subjectClass = nullptr;

		Subject (const SubjectClass* subjectClass) : subjectClass (subjectClass) {}
	};
};

}	// namespace ODB


inline bool		ODB::Query::Matches (const Ref<ODB::Object>& object) const
{
	return Matches (*reinterpret_cast<const ConstRef<ODB::Object>*> (&object));
}


// ============================= Query Definitions =============================

#define NO_EXPORT /*NoExport*/

#define DECLARE_ATTRIBUTE_QUERY_CLASS(Export, Name, AttributeType)		\
	class Export Name##Query: public ODB::Query {						\
	protected:															\
		AttributeType value;	/* attribute value to be queried */		\
																		\
		Name##Query (const AttributeType& value): value (value) {}		\
	public:																\
		virtual ~Name##Query ();										\
		AttributeType	GetValue () const { return value; }			\
	};

#define DECLARE_EXTERNAL_ATTRIBUTE_QUERY_CLASS(Export, Name, AttributeType)		\
	class Export Name##Query: public ODB::Query {						\
	protected:															\
		AttributeType value;	/* attribute value to be queried */		\
																		\
		Name##Query (const AttributeType& value): value (value) {}		\
	public:																\
		virtual ~Name##Query ();										\
		AttributeType	GetValue () const { return value; }			\
	};

#define DECLARE_INTERNAL_ATTRIBUTE_EQUALITY_QUERY_CLASS(Export, Name, ClassType, AttributeType, AttributeQueryMethod)	\
	class Export Name##EqualityQuery: public Name##Query {													\
		DECLARE_CLASS_INFO																					\
	public:																									\
		Name##EqualityQuery (const AttributeType& value): Name##Query (value) {}							\
		virtual ~Name##EqualityQuery ();																\
																											\
		virtual	Name##EqualityQuery*	Clone () const override { return new Name##EqualityQuery (*this); }		\
																											\
		virtual bool	Matches (const ODB::ConstRef<ODB::Object>& object) const override { return (ODB::StaticCast<ClassType> (object)->AttributeQueryMethod () == value); }	\
	};

#define DECLARE_INTERNAL_ATTRIBUTE_NONEQUALITY_QUERY_CLASS(Export, Name, ClassType, AttributeType, AttributeQueryMethod)	\
	class Export Name##NonEqualityQuery: public Name##Query {													\
		DECLARE_CLASS_INFO																						\
	public:																										\
		Name##NonEqualityQuery (const AttributeType& value): Name##Query (value) {}								\
		virtual ~Name##NonEqualityQuery ();																		\
																												\
		virtual	Name##NonEqualityQuery*		Clone () const override { return new Name##NonEqualityQuery (*this); }	\
																												\
		virtual bool	Matches (const ODB::ConstRef<ODB::Object>& object) const override { return (ODB::StaticCast<ClassType> (object)->AttributeQueryMethod () != value); }	\
	};

#define DECLARE_ATTRIBUTE_QUERY_CREATOR_CLASS(Export, Name, AttributeType)	\
	class Export Name##QueryCreator {										\
	public:																	\
		Name##EqualityQuery		operator== (const AttributeType& value) const { return Name##EqualityQuery (value); }		\
		Name##NonEqualityQuery	operator!= (const AttributeType& value) const { return Name##NonEqualityQuery (value); }	\
	};																		\
																			\
	static const Name##QueryCreator	Name;


#define DECLARE_ATTRIBUTE_EQUALITY_QUERY(Export, Name, ClassType, AttributeType, AttributeQueryMethod)					\
	DECLARE_ATTRIBUTE_QUERY_CLASS (Export, Name, AttributeType)															\
	DECLARE_INTERNAL_ATTRIBUTE_EQUALITY_QUERY_CLASS (Export, Name, ClassType, AttributeType, AttributeQueryMethod)		\
	DECLARE_INTERNAL_ATTRIBUTE_NONEQUALITY_QUERY_CLASS (Export, Name, ClassType, AttributeType, AttributeQueryMethod)	\
	DECLARE_ATTRIBUTE_QUERY_CREATOR_CLASS (Export, Name, AttributeType)

#define DEFINE_ATTRIBUTE_EQUALITY_QUERY(Name, ClassType, AttributeType, AttributeQueryMethod)	\
	GS::ClassInfo	ClassType::Name##EqualityQuery::classInfo;									\
	GS::ClassInfo	ClassType::Name##NonEqualityQuery::classInfo;								\
	const ClassType::Name##QueryCreator		ClassType::Name = ClassType::Name##QueryCreator ();	\
	ClassType::Name##Query::~Name##Query () {}													\
	ClassType::Name##EqualityQuery::~Name##EqualityQuery () {}									\
	ClassType::Name##NonEqualityQuery::~Name##NonEqualityQuery () {}



#define DECLARE_EXTERNAL_ATTRIBUTE_EQUALITY_QUERY_CLASS(Export, Name, ClassType, AttributeType, AttributeQueryMethod)	\
	class Export Name##EqualityQuery: public Name##Query {												\
		DECLARE_CLASS_INFO																				\
	public:																								\
		Name##EqualityQuery (const AttributeType& value): Name##Query (value) {}						\
		virtual ~Name##EqualityQuery ();																\
																										\
		virtual	Name##EqualityQuery*	Clone () const override { return new Name##EqualityQuery (*this); }	\
																										\
		virtual bool	Matches (const ODB::ConstRef<ODB::Object>& object) const override { return (ClassType::AttributeQueryMethod (ODB::StaticCast<ClassType> (object)) == value); }	\
	};

#define DECLARE_EXTERNAL_ATTRIBUTE_NONEQUALITY_QUERY_CLASS(Export, Name, ClassType, AttributeType, AttributeQueryMethod)	\
	class Export Name##NonEqualityQuery: public Name##Query {													\
		DECLARE_CLASS_INFO																						\
	public:																										\
		Name##NonEqualityQuery (const AttributeType& value): Name##Query (value) {}								\
		virtual ~Name##NonEqualityQuery ();																		\
																												\
		virtual	Name##NonEqualityQuery*		Clone () const override { return new Name##NonEqualityQuery (*this); }	\
																												\
		virtual bool	Matches (const ODB::ConstRef<ODB::Object>& object) const override { return (ClassType::AttributeQueryMethod (ODB::StaticCast<ClassType> (object)) != value); }	\
	};


#define DECLARE_EXTERNAL_ATTRIBUTE_EQUALITY_QUERY(Export, Name, ClassType, AttributeType, AttributeQueryMethod)			\
	DECLARE_EXTERNAL_ATTRIBUTE_QUERY_CLASS (Export, Name, AttributeType)												\
	DECLARE_EXTERNAL_ATTRIBUTE_EQUALITY_QUERY_CLASS (Export, Name, ClassType, AttributeType, AttributeQueryMethod)		\
	DECLARE_EXTERNAL_ATTRIBUTE_NONEQUALITY_QUERY_CLASS (Export, Name, ClassType, AttributeType, AttributeQueryMethod)	\
	DECLARE_ATTRIBUTE_QUERY_CREATOR_CLASS (Export, Name, AttributeType)

#define DEFINE_EXTERNAL_ATTRIBUTE_EQUALITY_QUERY(Name, ClassType, AttributeType, AttributeQueryMethod)	\
	GS::ClassInfo	ClassType::Name##EqualityQuery::classInfo;											\
	GS::ClassInfo	ClassType::Name##NonEqualityQuery::classInfo;										\
	const ClassType::Name##QueryCreator		ClassType::Name = ClassType::Name##QueryCreator ();			\
	ClassType::Name##Query::~Name##Query () {}															\
	ClassType::Name##EqualityQuery::~Name##EqualityQuery () {}											\
	ClassType::Name##NonEqualityQuery::~Name##NonEqualityQuery () {}


// =========================== Class QueryExpression ===========================

namespace ODB {

class ODB_DLL_EXPORT QueryExpression : public Query {
public:
    virtual ~QueryExpression ();
};

}	// namespace ODB


// ======================== Class NegateQueryExpression ========================

namespace ODB {

class ODB_DLL_EXPORT NegateQueryExpression : public QueryExpression {
private:
	const Query* query;

protected:
	virtual	void	DeleteChildren () override;

public:
	NegateQueryExpression (const Query& query);

	virtual	NegateQueryExpression*	Clone () const override;
	virtual	NegateQueryExpression*	CloneComposite () const override;

	virtual bool	Matches (const ConstRef<ODB::Object>& object) const override;

	virtual bool	Matches (const Subject& subject) const override;

	virtual GS::String	ToText () const override;
};


ODB_DLL_EXPORT NegateQueryExpression	operator! (const Query& query);

}	// namespace ODB


// ======================== Class BinaryQueryExpression ========================

namespace ODB {

class ODB_DLL_EXPORT BinaryQueryExpression : public QueryExpression {
protected:
	const Query* leftOp;	// left operand of the binary expression
	const Query* rightOp;	// right operand of the binary expression

	virtual	void	DeleteChildren () override;

public:
	BinaryQueryExpression (const Query& leftOp, const Query& rightOp);

	virtual UInt32	ExecuteCustom (Scope* scope) const override;
	virtual UInt32	ExecuteCustom (ConstScope* scope) const override;

	using QueryExpression::ExecuteCustom;
};

}	// namespace ODB


// ========================= Class AndQueryExpression ==========================

namespace ODB {

class ODB_DLL_EXPORT AndQueryExpression : public BinaryQueryExpression {
private:
	void	ExecuteWithDoubleExecution (Scope* scope, RefList<ODB::Object>* result) const;
	void	ExecuteWithDoubleExecution (ConstScope* scope, ConstRefList<ODB::Object>* result) const;
	void	ExecuteWithLeftExecution   (Scope* scope, RefList<ODB::Object>* result) const;
	void	ExecuteWithLeftExecution   (ConstScope* scope, ConstRefList<ODB::Object>* result) const;
	void	ExecuteWithRightExecution  (Scope* scope, RefList<ODB::Object>* result) const;
	void	ExecuteWithRightExecution  (ConstScope* scope, ConstRefList<ODB::Object>* result) const;

protected:
	virtual void	ExecuteCustom (Scope* scope, RefList<ODB::Object>* result) const override;
	virtual void	ExecuteCustom (ConstScope* scope, ConstRefList<ODB::Object>* result) const override;

public:
	AndQueryExpression (const Query& leftOp, const Query& rightOp);

	virtual	AndQueryExpression*		Clone () const override;
	virtual	AndQueryExpression*		CloneComposite () const override;

	virtual bool	Matches (const ConstRef<ODB::Object>& object) const override;

	virtual bool	Matches (const Subject& subject) const override;

	virtual GS::String	ToText () const override;
};


ODB_DLL_EXPORT AndQueryExpression	operator&& (const Query& leftOp, const Query& rightOp);

}	// namespace ODB


// ========================== Class OrQueryExpression ==========================

namespace ODB {

class ODB_DLL_EXPORT OrQueryExpression : public BinaryQueryExpression {
private:
	void	ExecuteWithDoubleExecution (Scope* scope, RefList<ODB::Object>* result) const;
	void	ExecuteWithDoubleExecution (ConstScope* scope, ConstRefList<ODB::Object>* result) const;
	void	ExecuteWithSingleExecution (Scope* scope, RefList<ODB::Object>* result) const;
	void	ExecuteWithSingleExecution (ConstScope* scope, ConstRefList<ODB::Object>* result) const;

protected:
	virtual void	ExecuteCustom (Scope* scope, RefList<ODB::Object>* result) const override;
	virtual void	ExecuteCustom (ConstScope* scope, ConstRefList<ODB::Object>* result) const override;

public:
	OrQueryExpression (const Query& leftOp, const Query& rightOp);

	virtual	OrQueryExpression*	Clone () const override;
	virtual	OrQueryExpression*	CloneComposite () const override;

	virtual bool	Matches (const ConstRef<ODB::Object>& object) const override;

	virtual bool	Matches (const Subject& subject) const override;

	virtual GS::String	ToText () const override;
};


ODB_DLL_EXPORT OrQueryExpression	operator|| (const Query& leftOp, const Query& rightOp);

}	// namespace ODB


// ========================= Class DiffQueryExpression =========================

namespace ODB {

class ODB_DLL_EXPORT DiffQueryExpression : public BinaryQueryExpression {
private:
	void	ExecuteWithDoubleExecution (Scope* scope, RefList<ODB::Object>* result) const;
	void	ExecuteWithDoubleExecution (ConstScope* scope, ConstRefList<ODB::Object>* result) const;
	void	ExecuteWithLeftExecution   (Scope* scope, RefList<ODB::Object>* result) const;
	void	ExecuteWithLeftExecution   (ConstScope* scope, ConstRefList<ODB::Object>* result) const;

protected:
	virtual void	ExecuteCustom (Scope* scope, RefList<ODB::Object>* result) const override;
	virtual void	ExecuteCustom (ConstScope* scope, ConstRefList<ODB::Object>* result) const override;

public:
	DiffQueryExpression (const Query& leftOp, const Query& rightOp);

	virtual	DiffQueryExpression*	Clone () const override;
	virtual	DiffQueryExpression*	CloneComposite () const override;

	virtual bool	Matches (const ConstRef<ODB::Object>& object) const override;

	virtual bool	Matches (const Subject& subject) const override;

	virtual GS::String	ToText () const override;
};


ODB_DLL_EXPORT DiffQueryExpression	operator- (const Query& leftOp, const Query& rightOp);

}	// namespace ODB


#endif
