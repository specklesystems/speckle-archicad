// *****************************************************************************
//
//	      Base declarations and definitions for the ObjectDatabase module
//
// Module:		   ObjectDatabase
// Namespace:	   ODB
// Contact person: MB
//
// *****************************************************************************


#ifndef ODBBASE_HPP
#define ODBBASE_HPP


// --------------------------------- Includes ----------------------------------

#include "ODBDefinitions.hpp"
#include "ODBAssert.hpp"
#include "TypeTraits.hpp"

#include <functional>

// Lint is confused if a structure got new members in some cases (can't handle inconsistent definitions)
#if defined (ACCESS_ODB_MODULE_PRIVATE) || defined (OBJECTDATABASE_DLL_COMPILE)
#define ODB_MODULE_PRIVATE
#endif


// -----------------------------------------------------------------------------

namespace ODB {

const Int32 ModuleId = 258;

const Int32 ErrorStart = GS::ErrorFlagMask | (ModuleId << 16);

	// Error code ranges for ODB system - defined here to make the range allocation easier

const Int32 IdSpaceErrors			   = ErrorStart + 0x0000;
const Int32 GeneralROFErrors		   = ErrorStart + 0x0100;
const Int32 RandomObjectFileErrors	   = ErrorStart + 0x0200;
const Int32 RandomObjectFileErrorCount = 0x1000;
const Int32 FileDatabaseErrors		   = ErrorStart + 0x1200;
const Int32 FileDatabaseErrorCount	   = 0x1000;
const Int32 XXXErrors				   = ErrorStart + 0x2200;		// <-- use for the next class

const GSErrCode UnknownClass		   = ErrorStart + 0xFF00;


	// --------------------

ODB_DLL_EXPORT extern const double FineTicksPerSec;


	// --------------------

template <class Type>
inline const GS::ClassInfo*		TypeOf ()
{
	return Type::GetClassInfoStatic ();
}


template <class Type>
inline bool		IsType (const GS::Guid& id)
{
	return (Type::GetClassInfoStatic ()->GetId () == id);
}


template <class Type>
inline GS::Guid		IdOf ()
{
	return Type::GetClassInfoStatic ()->GetId ();
}


enum CheckLevel {
	ReleaseCheckLevel = 1,
	DebugCheckLevel	  = 2
};

ODB_DLL_EXPORT extern CheckLevel checkLevel;


template <typename Function>
inline void		DebugCheck (const Function& checkFunction)
{
	if (checkLevel >= DebugCheckLevel)
		checkFunction ();
}


template <typename Function>
inline void		ReleaseCheck (const Function& checkFunction)
{
	if (checkLevel >= ReleaseCheckLevel)
		checkFunction ();
}

	
	// --------------------

enum StoppableSelector { Stoppable };

enum InternalCallSelector { InternalCall };

enum MethodSelector { Method };

enum EnumerationOrder {
	Preorder,
	Postorder
};

class OperationFlow {
public:
	class Scope;
	friend class Scope;

private:
	volatile bool isInside;		// volatile allows usage from more threads (prevents isInside to be optimized into a register because waiter thread can wait forever to another thread to exit from the scope)

public:
	OperationFlow (): isInside (false) {}

	operator bool () const { return isInside; }

	void	WaitForEnter () { while (!isInside) ; }
	void	WaitForExit  () { while (isInside) ; }

	class Scope {
	private:
		OperationFlow& operationFlow;

		Scope (const Scope& source);				// disabled
		Scope&	operator= (const Scope& source);	// disabled

	public:
		Scope (OperationFlow& operationFlow): operationFlow (operationFlow) { operationFlow.isInside = true; }
	   ~Scope () { operationFlow.isInside = false; }
	};
};


	// --------------------

template <typename Function>
void	OnFirst (bool& first, const Function& function)
{
	if (first) {
		function ();
		first = false;
	}
}
	// --------------------

enum Direction {
	Above,
	Below
};

	// --------------------

template <UInt64 X>
struct Log2 {
	enum { Value = 1 + Log2<X / 2>::Value };
};

template <>
struct Log2<1> {
	enum { Value = 0 };
};


	// --------------------

ODB_NO_INLINE  void TerminateProgram (const char* message);

ODB_DLL_EXPORT extern std::function<void ()> LogicErrorEncountered;			// error that doesn't occur in a correct program, for example precondition error, invariant error, usage error, internal error
ODB_DLL_EXPORT extern std::function<void ()> AccessViolationEncountered;	// special logic error where access rules are violated, for example modifying a constant object or modifying an object outside the modification scope
ODB_DLL_EXPORT extern std::function<void ()> TypeCompatibilityViolation;	// runtime type check error
ODB_DLL_EXPORT extern std::function<void ()> UnexpectedErrorEncountered;	// run time error that the calling code doesn't expect and handles (it is similar to OutOfMemory)

}	// namespace ODB


#endif
