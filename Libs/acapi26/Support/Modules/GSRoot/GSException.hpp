// *****************************************************************************
//
//                              Class GSException
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	MB, FGY, MM
//
// SG compatible
//
// *****************************************************************************

#ifndef GSEXCEPTION_HPP
#define GSEXCEPTION_HPP

#pragma once


#include <stdio.h>
#include <exception>
#include <new>

#include "GSRootExport.hpp"
#include "Definitions.hpp"
#include "GSDebug.hpp"

namespace GS { class ClassInfo; }
namespace GS { class OChannel; }
namespace GS { class UniString; }

#include "StackInfo.hpp"

// Undefine Windows Macros, we want to use "GetMessage"

#if defined (WINDOWS)
#if defined (GetMessage)
#undef GetMessage
#endif
#endif


// ============================== Class GSException ==============================
#define GS_EXCEPTIONS_DLL_EXPORTED

namespace GS {

#define GS_EXCEPTIONS_INLINE
#define GS_EXCEPTIONS_GSROOT_DLL_EXPORT GSROOT_DLL_EXPORT

class GSROOT_DLL_EXPORT GSException {
	// DECLARE_DYNAMIC_CLASS
public:
	typedef StackInfoCustomDepth<128> StackInfo;

private:
	static constexpr USize			AlignOfUniString = alignof (void*);
	static constexpr USize			SizeOfUniString  = 2 * sizeof (void*);

	Int32							id;				// this is the equivalent error id (it is the same for the given type of exception)

	GS::UniString&					message;		// additional message for the exception from the thrower (if it isn't nullptr)
	alignas (AlignOfUniString) char	messageStorage[SizeOfUniString];

	const char*						fileName;		// name of file where the exception was thrown from (if it isn't nullptr)
	UInt32							lineNumber;		// line number where the exception was thrown from (if it isn't 0)
	GSException*					cause;			// exception chaining

	GSException::StackInfo			stackInfo;

	void				SetCause (const GSException* cause);
	void				SetCause (const GSException& cause);

public:
		// Constructors

		  explicit GSException (const char*	message = nullptr,
					  const char*			fileName = nullptr,
					  UInt32				lineNumber = 0,
					  const GSException*	cause = nullptr,
					  Int32					id = 0					// should be wired in all of the derived classes
					  );

		  explicit GSException (const char*	message,
					  const char*			fileName,
					  UInt32				lineNumber,
					  const GSException&	cause,
					  Int32					id						// should be wired in all of the derived classes
					  );

		  explicit GSException (const GS::UniString&	message,
					  const char*			fileName = nullptr,
					  UInt32				lineNumber = 0,
					  const GSException*	cause = nullptr,
					  Int32					id = 0					// should be wired in all of the derived classes
					  );

		  explicit GSException (
					  const GS::UniString&	message,
					  const char*			fileName,
					  UInt32				lineNumber,
					  const GSException&	cause,
					  Int32					id					   // should be wired in all of the derived classes
					  );

		  GSException (const GSException& source);

		  virtual ~GSException () throw ();

		// User interface
			void							SetMessage	   (const GS::UniString& message);
			void							SetMessage	   (const char* message);

			virtual const char*				GetName        (void) const;
			virtual Int32					GetID		   (void) const;

			virtual const GS::UniString&	GetMessage	   (void) const;
			virtual const char*				GetFileName	   (void) const;
			virtual UInt32					GetLineNumber  (void) const;

			virtual GSException*			Clone		   (void) const;

			virtual void					Print		   (OChannel& oc) const;
			virtual void					Dump		   (OChannel& oc) const;

			virtual const GSException*		GetCause	   () const;
			virtual GSException*			GetCause	   ();

			virtual const StackInfo&		GetStack	   () const;

			GSException&					operator= (const GSException& source);

};


extern const GSROOT_DLL_EXPORT	GSException NoCauseException;	// Special value used when there's no cause of the exception

typedef GSException Exception; // GS::Exception

// ______________________________ Class GSException ______________________________



// ======================= GSException hierarchy framework =======================

class GS_EXCEPTIONS_GSROOT_DLL_EXPORT RootException : virtual public GSException {
public:
	explicit RootException (const char* msg, const char* fName, UInt32 lNumber, const GSException& cause_) :
		GSException (msg, fName, lNumber, cause_, (Int32)Error)
	{}
	explicit RootException (const char* msg = nullptr, const char* fName = nullptr, UInt32 lNumber = 0) :
		GSException (msg, fName, lNumber, nullptr, (Int32)Error)
	{}
	explicit RootException (const GS::UniString& msg, const char* fName, UInt32 lNumber, const GSException& cause_) :
		GSException (msg, fName, lNumber, cause_, (Int32)Error)
	{}
	explicit RootException (const GS::UniString& msg, const char* fName = nullptr, UInt32 lNumber = 0) :
		GSException (msg, fName, lNumber, nullptr, (Int32)Error)
	{}
	virtual const char* GetName () const override;
	virtual GSException* Clone (void) const override;
};

class GS_EXCEPTIONS_GSROOT_DLL_EXPORT GeneralException : virtual public GSException {
public:
	explicit GeneralException (const char* msg, const char* fName, UInt32 lNumber, const GSException& cause_) :
		GSException (msg, fName, lNumber, cause_, (Int32)Error)
	{}
	explicit GeneralException (const char* msg = nullptr, const char* fName = nullptr, UInt32 lNumber = 0) :
		GSException (msg, fName, lNumber, nullptr, (Int32)Error)
	{}
	explicit GeneralException (const GS::UniString& msg, const char* fName, UInt32 lNumber, const GSException& cause_) :
		GSException (msg, fName, lNumber, cause_, (Int32)Error)
	{}
	explicit GeneralException (const GS::UniString& msg, const char* fName = nullptr, UInt32 lNumber = 0) :
		GSException (msg, fName, lNumber, nullptr, (Int32)Error)
	{}
	virtual const char* GetName () const override;
	virtual GSException* Clone (void) const override;
};

#define	DECLARE_EXCEPTION_CLASS_WITH_CLASS_SPEC(classSpec, className, baseClassName, errId)		\
	class classSpec: virtual public baseClassName {											\
	public:																			\
		explicit className (const char* msg, const char* fName, UInt32 lNumber, const GS::GSException& cause); \
		explicit className (const char* msg = nullptr, const char* fName = nullptr, UInt32 lNumber = 0); \
		explicit className (const GS::UniString& msg, const char* fName, UInt32 lNumber, const GS::GSException& cause); \
		explicit className (const GS::UniString& msg, const char* fName = nullptr, UInt32 lNumber = 0); \
		virtual const char* GetName () const override; \
		virtual GS::GSException* Clone (void) const override; \
	};

#define	DECLARE_EXCEPTION_CLASS(className, baseClassName, errId, exportdef) \
	DECLARE_EXCEPTION_CLASS_WITH_CLASS_SPEC(exportdef className, className, baseClassName, errId)

#define	DECLARE_EXCEPTION_CLASS_NO_EXPORTDEF(className, baseClassName, errId) \
	DECLARE_EXCEPTION_CLASS_WITH_CLASS_SPEC(className, className, baseClassName, errId)

#define	IMPLEMENT_EXCEPTION_CLASS_WITH_NAMESPACE(classNameWithNamespace, className, baseClassName, errId)		\
	classNameWithNamespace::className (const char* msg, const char* fName, UInt32 lNumber, const GS::GSException& cause): \
			GS::GSException (msg, fName, lNumber, cause, errId), baseClassName () {}	\
	classNameWithNamespace::className (const char* msg, const char* fName, UInt32 lNumber): \
			GS::GSException (msg, fName, lNumber, nullptr, errId), baseClassName () {}	\
	classNameWithNamespace::className (const GS::UniString& msg, const char* fName, UInt32 lNumber, const GS::GSException& cause): \
			GS::GSException (msg, fName, lNumber, cause, errId), baseClassName () {}	\
	classNameWithNamespace::className (const GS::UniString& msg, const char* fName, UInt32 lNumber): \
			GS::GSException (msg, fName, lNumber, nullptr, errId), baseClassName () {}	\
	const char* classNameWithNamespace::GetName () const { return #className; } \
	GS::GSException* classNameWithNamespace::Clone (void) const { return new className (*this); }

#define	IMPLEMENT_EXCEPTION_CLASS(className, baseClassName, errId)		\
	IMPLEMENT_EXCEPTION_CLASS_WITH_NAMESPACE (className, className, baseClassName, errId)

#define	DECLARE_EXCEPTION_CLASS2(className, baseClassName1, baseClassName2, errId, exportdef)	\
	class exportdef className: virtual public baseClassName1, virtual public baseClassName2 {					\
	public:																			\
	explicit className (const char* msg, const char* fName, UInt32 lNumber, const GS::GSException& cause); \
	explicit className (const char* msg = nullptr, const char* fName = nullptr, UInt32 lNumber = 0); \
	explicit className (const GS::UniString& msg, const char* fName, UInt32 lNumber, const GS::GSException& cause); \
	explicit className (const GS::UniString& msg, const char* fName = nullptr, UInt32 lNumber = 0); \
		virtual const char* GetName () const override; \
		virtual GS::GSException* Clone (void) const override; \
	};

#define	IMPLEMENT_EXCEPTION_CLASS2(className, baseClassName1, baseClassName2, errId)		\
	className::className (const char* msg, const char* fName, UInt32 lNumber, const GS::GSException& cause): \
			 GS::GSException (msg, fName, lNumber, cause, errId), baseClassName1 (), baseClassName2 () {}	\
	className::className (const char* msg, const char* fName, UInt32 lNumber): \
			 GS::GSException (msg, fName, lNumber, nullptr, errId), baseClassName1 (), baseClassName2 () {}	\
	className::className (const GS::UniString& msg, const char* fName, UInt32 lNumber, const GS::GSException& cause): \
			GS::GSException (msg, fName, lNumber, cause, errId), baseClassName1 (), baseClassName2 ()  {}	\
	className::className (const GS::UniString& msg, const char* fName, UInt32 lNumber): \
			GS::GSException (msg, fName, lNumber, nullptr, errId), baseClassName1 (), baseClassName2 ()  {}	\
	const char* className::GetName () const { return #className; } \
	GS::GSException* className::Clone (void) const { return new className (*this); }


DECLARE_EXCEPTION_CLASS (LogicErrorException,  GeneralException, Error, GSROOT_DLL_EXPORT)
	DECLARE_EXCEPTION_CLASS (PreconditionException, LogicErrorException, ErrParam, GSROOT_DLL_EXPORT)
		DECLARE_EXCEPTION_CLASS (IllegalArgumentException, PreconditionException, ErrParam, GSROOT_DLL_EXPORT)
			DECLARE_EXCEPTION_CLASS (IllegalReferenceException,	IllegalArgumentException, ErrParam, GSROOT_DLL_EXPORT)
			DECLARE_EXCEPTION_CLASS (NullPointerException,		IllegalArgumentException, ErrParam, GSROOT_DLL_EXPORT)
			DECLARE_EXCEPTION_CLASS (NullReferenceException,	IllegalArgumentException, ErrParam, GSROOT_DLL_EXPORT)
			DECLARE_EXCEPTION_CLASS (NullHandleException,		IllegalArgumentException, ErrParam, GSROOT_DLL_EXPORT)
			DECLARE_EXCEPTION_CLASS (EmptyHandleException,		IllegalArgumentException, ErrParam, GSROOT_DLL_EXPORT)
			DECLARE_EXCEPTION_CLASS (IllegalTypeException,		IllegalArgumentException, ErrParam, GSROOT_DLL_EXPORT)
DECLARE_EXCEPTION_CLASS (RunTimeErrorException, GeneralException, Error, GSROOT_DLL_EXPORT)
	DECLARE_EXCEPTION_CLASS  (AccessViolationException,  RunTimeErrorException, Error, GSROOT_DLL_EXPORT)
	DECLARE_EXCEPTION_CLASS  (LimitViolationException,  RunTimeErrorException, Error, GSROOT_DLL_EXPORT)
	DECLARE_EXCEPTION_CLASS  (ConversionErrorException, RunTimeErrorException, Error, GSROOT_DLL_EXPORT)
	DECLARE_EXCEPTION_CLASS  (InternalErrorException,   RunTimeErrorException, Error, GSROOT_DLL_EXPORT)
	DECLARE_EXCEPTION_CLASS  (IllegalStateException,   RunTimeErrorException, Error, GSROOT_DLL_EXPORT)
	DECLARE_EXCEPTION_CLASS  (UnsupportedOperationException,   RunTimeErrorException, Error, GSROOT_DLL_EXPORT)
	DECLARE_EXCEPTION_CLASS2 (OutOfMemoryException,     RunTimeErrorException, std::bad_alloc, ErrMemoryFull, GSROOT_DLL_EXPORT)

// General implementation of the precondition

#define PRECOND_IMP(preCondition, exception)			\
	if (!(preCondition)) {								\
	DBBREAK ();											\
	throw exception (nullptr, __FILE__, __LINE__);			\
	}


	// Preconditions that will be compiled only into the debug and test versions

#define PRECOND(condition)		DBASSERT(condition)
#define ARG_CHECK(condition)	DBASSERT(condition)
#define REF_CHECK(condition)	DBASSERT(condition)
#define NULL_PTR_CHECK(ptr)		DBASSERT(ptr != nullptr)
#define NULL_REF_CHECK(ref)		DBASSERT(&ref != nullptr)
#define TYPE_CHECK(condition)	DBASSERT(condition)


	// Preconditions that will always be compiled (debug, test and release)

#define PRECOND_R(condition)	PRECOND_IMP(condition,    GS::PreconditionException)
#define ARG_CHECK_R(condition)	PRECOND_IMP(condition,    GS::IllegalArgumentException)
#define REF_CHECK_R(condition)	PRECOND_IMP(condition,    GS::IllegalReferenceException)
#define NULL_PTR_CHECK_R(ptr)	PRECOND_IMP(ptr != nullptr,  GS::NullPointerException)
#define NULL_REF_CHECK_R(ref)	PRECOND_IMP(&ref != nullptr, GS::NullReferenceException)
#define TYPE_CHECK_R(condition)	PRECOND_IMP(condition,    GS::IllegalTypeException)

// _______________________ GSException hierarchy framework _______________________

}

#endif
