
// *****************************************************************************
//
//                 Base predicates, adapter, negaters, binders
//
// Module:			GSRoot
// Namespace:		GS
// Contact person:	LP
//
// SG compatible
//
// *****************************************************************************


#if !defined PREDICATES_HPP
#define PREDICATES_HPP

#pragma once


namespace GS {

// =========================== Function object base ============================

	// --- Generator

template <class Res>
class Generator {
public:
	typedef Res ResultType;
};

	// --- UnaryFunction ---

template <class Arg, class Res>
class UnaryFunction {
public:
	typedef Arg ArgumentType;
	typedef Res ResultType;
};


	// --- BinaryFunction ---

template <class Arg1, class Arg2, class Res>
class BinaryFunction {
public:
	typedef Arg1 FirstArgumentType;
	typedef Arg2 SecondArgumentType;
	typedef Res  ResultType;
};
// ___________________________ Function object base ____________________________



// ================================= Binders ===================================

// MSDEV 6.0: typename X::Y	val; will not compile with "disable language extension" option set

	// --- Binder

template <class UnOp>
class Binder: public Generator <typename UnOp::ResultType> {
private:
	UnOp	unOp;	// unary operation
	typename UnOp::ArgumentType	arg;	// fixed argument

public:
	typedef typename UnOp::ResultType ResultType;

	Binder (const UnOp& op, const typename UnOp::ArgumentType& val): unOp (op), arg (val) {}

	ResultType	operator () () const { return unOp (arg); }
};

template <class UnOp>
inline Binder<UnOp>	Bind (const UnOp& unOp, const typename UnOp::ArgumentType& arg)
{
	return Binder<UnOp> (unOp, arg);
}

	// --- Binder1st ---

template <class BinOp>
class Binder1st: public UnaryFunction <typename BinOp::SecondArgumentType, typename BinOp::ResultType> {
private:
	BinOp	binOp;	// binary operation
	typename BinOp::FirstArgumentType	arg1;	// first fixed argument

public:
	typedef typename BinOp::SecondArgumentType	ArgumentType;
	typedef typename BinOp::ResultType			ResultType;

	Binder1st (const BinOp& op, const typename BinOp::FirstArgumentType& val): binOp (op), arg1 (val) {}

	ResultType	operator () (const ArgumentType& arg2) const { return binOp (arg1, arg2); }
	ResultType	operator () (ArgumentType& arg2) const { return binOp (arg1, arg2); }
};


template <class BinOp>
inline Binder1st<BinOp>	Bind1st (const BinOp& binOp, const typename BinOp::FirstArgumentType& arg1)
{
	return Binder1st<BinOp> (binOp, arg1);
}


	// --- Binder2nd ---

template <class BinOp>
class Binder2nd: public UnaryFunction <typename BinOp::FirstArgumentType, typename BinOp::ResultType> {
private:
	BinOp	binOp;	// binary operation
	typename BinOp::SecondArgumentType	arg2;	// second fixed argument

public:
	typedef typename BinOp::FirstArgumentType	ArgumentType;
	typedef typename BinOp::ResultType			ResultType;

	Binder2nd (const BinOp& op, const typename BinOp::SecondArgumentType& val): binOp (op), arg2 (val) {}

	ResultType	operator () (const ArgumentType& arg1) const { return binOp (arg1, arg2); }
	ResultType	operator () (ArgumentType& arg1) const { return binOp (arg1, arg2); }
};


template <class BinOp>
inline Binder2nd<BinOp>	Bind2nd (const BinOp& binOp, const typename BinOp::SecondArgumentType& arg2)
{
	return Binder2nd<BinOp> (binOp, arg2);
}
// ________________________________ Binders ____________________________________



// ================================ Adapters ===================================

	// --- MemFunAdapter ---

template <class R, class T>		// R = result, T = class
class MemFunAdapter: public UnaryFunction <T*, R> {
private:
	R (T::*mf) (void);	// pointer to the member function

public:
	explicit MemFunAdapter (R (T::*memFun) (void)): mf (memFun) {}

	R	operator () (T* objPtr) const { return (objPtr->*mf) (); }
};


template <class R, class T>
inline MemFunAdapter<R, T>		MemFun (R (T::*memFun) (void))
{
	return MemFunAdapter<R, T> (memFun);
}


	// --- MemFunAdapterConst ---

template <class R, class T>		// R = result, T = class
class MemFunAdapterConst: public UnaryFunction <const T*, R> {
private:
	R (T::*mf) (void) const;	// pointer to the const member function

public:
	explicit MemFunAdapterConst (R (T::*memFun) (void) const): mf (memFun) {}

	R	operator () (const T* objPtr) const { return (objPtr->*mf) (); }
};


template <class R, class T>
inline MemFunAdapterConst<R, T>	MemFun (R (T::*memFun) (void) const)
{
	return MemFunAdapterConst<R, T> (memFun);
}


	// --- MemFun1Adapter ---

template <class R, class T, class A>	// R = result, T = class, A = argument
class MemFun1Adapter: public BinaryFunction <T*, A, R> {
private:
	R (T::*mf) (A);		// pointer to the member function

public:
	explicit MemFun1Adapter (R (T::*memFun) (A)): mf (memFun) {}

	R	operator () (T* objPtr, A arg) const { return (objPtr->*mf) (arg); }
};


template <class R, class T, class A>
inline MemFun1Adapter<R, T, A>		MemFun (R (T::*memFun) (A))
{
	return MemFun1Adapter<R, T, A> (memFun);
}


	// --- MemFun1AdapterConst ---

template <class R, class T, class A>	// R = result, T = class, A = argument
class MemFun1AdapterConst: public BinaryFunction <const T*, A, R> {
private:
	R (T::*mf) (A) const;	// pointer to the const member function

public:
	explicit MemFun1AdapterConst (R (T::*memFun) (A) const): mf (memFun) {}

	R	operator () (const T* objPtr, A arg) const { return (objPtr->*mf) (arg); }
};


template <class R, class T, class A>
inline MemFun1AdapterConst<R, T, A>	MemFun (R (T::*memFun) (A) const)
{
	return MemFun1AdapterConst<R, T, A> (memFun);
}


	// --- MemFunAdapterRef ---

template <class R, class T>		// R = result, T = class
class MemFunAdapterRef: public UnaryFunction <T, R> {
private:
	R (T::*mf) (void);	// pointer to the member function

public:
	explicit MemFunAdapterRef (R (T::*memFun) (void)): mf (memFun) {}

	R	operator () (T& obj) const { return (obj.*mf) (); }
};


template <class R, class T>
inline MemFunAdapterRef<R, T>	MemFunRef (R (T::*memFun) (void))
{
	return MemFunAdapterRef<R, T> (memFun);
}


	// --- MemFunAdapterRefConst ---

template <class R, class T>		// R = result, T = class
class MemFunAdapterRefConst: public UnaryFunction <const T, R> {
private:
	R (T::*mf) (void) const;	// pointer to the const member function

public:
	explicit MemFunAdapterRefConst (R (T::*memFun) (void) const): mf (memFun) {}

	R	operator () (const T& obj) const { return (obj.*mf) (); }
};


template <class R, class T>
inline MemFunAdapterRefConst<R, T>		MemFunRef (R (T::*memFun) (void) const)
{
	return MemFunAdapterRefConst<R, T> (memFun);
}


	// --- MemFun1AdapterRef ---

template <class R, class T, class A>	// R = result, T = class, A = argument
class MemFun1AdapterRef: public BinaryFunction <T, A, R> {
private:
	R (T::*mf) (A);		// pointer to the member function

public:
	explicit MemFun1AdapterRef (R (T::*memFun) (A)): mf (memFun) {}

	R	operator () (T& obj, A arg) const { return (obj.*mf) (arg); }
};


template <class R, class T, class A>
inline MemFun1AdapterRef<R, T, A>		MemFunRef (R (T::*memFun) (A))
{
	return MemFun1AdapterRef<R, T, A> (memFun);
}


	// --- MemFun1AdapterRefConst ---

template <class R, class T, class A>	// R = result, T = class, A = argument
class MemFun1AdapterRefConst: public BinaryFunction <const T, A, R> {
private:
	R (T::*mf) (A) const;	// pointer to the const member function

public:
	explicit MemFun1AdapterRefConst (R (T::*memFun) (A) const): mf (memFun) {}

	R	operator () (const T& obj, A arg) const { return (obj.*mf) (arg); }
};


template <class R, class T, class A>
inline MemFun1AdapterRefConst<R, T, A>	MemFunRef (R (T::*memFun) (A) const)
{
	return MemFun1AdapterRefConst<R, T, A> (memFun);
}


	// --- UnaryFunctionAdapter ---

template <class A, class R>		// A = argument, R = result
class UnaryFunctionAdapter: public UnaryFunction <A, R> {
private:
	R (*pf) (A);	// pointer to the unary function

public:
	explicit UnaryFunctionAdapter (R (*ptrFun) (A)): pf (ptrFun) {}

	R	operator () (A arg) const { return (*pf) (arg); }
};


template <class A, class R>
inline UnaryFunctionAdapter<A, R>		PtrFun (R (*ptrFun) (A))
{
	return UnaryFunctionAdapter<A, R> (ptrFun);
}


	// --- BinaryFunctionAdapter ---

template <class A1, class A2, class R>		// A1 = first argument, A2 = second argument, R = result
class BinaryFunctionAdapter: public BinaryFunction <A1, A2, R> {
private:
	R (*pf) (A1, A2);	// pointer to the binary function

public:
	explicit BinaryFunctionAdapter (R (*ptrFun) (A1, A2)): pf (ptrFun) {}

	R	operator () (A1 arg1, A2 arg2) const { return (*pf) (arg1, arg2); }
};


template <class A1, class A2, class R>
inline BinaryFunctionAdapter<A1, A2, R>	PtrFun (R (*ptrFun) (A1, A2))
{
	return BinaryFunctionAdapter<A1, A2, R> (ptrFun);
}
// ________________________________ Adapters ___________________________________



// ================================ Negaters ===================================

	// --- UnaryNegate ---

template <class UnOp>
class UnaryNegate: public UnaryFunction <typename UnOp::ArgumentType, bool> {
private:
	UnOp	unOp;	// unary operation to be negated

public:
	typedef typename UnOp::ArgumentType ArgumentType;

	explicit UnaryNegate (const UnOp& op): unOp (op) {}
	bool	operator () (const ArgumentType& arg) const { return !unOp (arg); }
};


template <class UnOp>
inline UnaryNegate<UnOp>	Not1 (const UnOp& unOp)
{
	return UnaryNegate<UnOp> (unOp);
}


	// --- BinaryNegate ---

template <class BinOp>
class BinaryNegate: public BinaryFunction <typename BinOp::FirstArgumentType,
										   typename BinOp::SecondArgumentType,
										   bool>
{
private:
	BinOp	binOp;	// binary operation to be negated

public:
	typedef typename BinOp::FirstArgumentType	FirstArgumentType;
	typedef typename BinOp::SecondArgumentType	SecondArgumentType;

	explicit BinaryNegate (const BinOp& op): binOp (op) {}
	bool	operator () (const FirstArgumentType& arg1, const SecondArgumentType& arg2) const { return !binOp (arg1, arg2); }
};


template <class BinOp>
inline BinaryNegate<BinOp>		Not2 (const BinOp& binOp)
{
	return BinaryNegate<BinOp> (binOp);
}
// ________________________________ Negaters ___________________________________



// =============================== Predicates ==================================

	// --- Equal ---

template <class T>
class Equal: public BinaryFunction <T, T, bool> {
public:
	bool	operator () (const T& val1, const T& val2) const { return (val1 == val2); }
};


	// --- NotEqual ---

template <class T>
class NotEqual: public BinaryFunction <T, T, bool> {
public:
	bool	operator () (const T& val1, const T& val2) const { return (val1 != val2); }
};


	// --- Less ---

template <class T>
class Less: public BinaryFunction <T, T, bool> {
public:
	bool	operator () (const T& val1, const T& val2) const { return (val1 < val2); }
};


	// --- LessOrEqual ---

template <class T>
class LessOrEqual: public BinaryFunction <T, T, bool> {
public:
	bool	operator () (const T& val1, const T& val2) const { return (val1 <= val2); }
};


	// --- Greater ---

template <class T>
class Greater: public BinaryFunction <T, T, bool> {
public:
	bool	operator () (const T& val1, const T& val2) const { return (val1 > val2); }
};


	// --- GreaterOrEqual ---

template <class T>
class GreaterOrEqual: public BinaryFunction <T, T, bool> {
public:
	bool	operator () (const T& val1, const T& val2) const { return (val1 >= val2); }
};


	// --- LogicalNot ---

template <class T>
class LogicalNot: public UnaryFunction <T, bool> {
public:
	bool	operator () (const T& val) const { return (!val); }
};


	// --- LogicalOr ---

template <class T>
class LogicalOr: public BinaryFunction <T, T, bool> {
public:
	bool	operator () (const T& val1, const T& val2) const { return (val1 || val2); }
};


	// --- LogicalAnd ---

template <class T>
class LogicalAnd: public BinaryFunction <T, T, bool> {
public:
	bool	operator () (const T& val1, const T& val2) const { return (val1 && val2); }
};
// ________________________________ Predicates _________________________________


// =================== Common mathematical function objects ====================

	// --- Plus ---

template <class T>
class Plus: public BinaryFunction <T, T, T>
{
public:
	T	operator () (const T& val1, const T& val2) const { return (val1 + val2); }
};


	// --- Minus ---

template <class T>
class Minus: public BinaryFunction <T, T, T>
{
public:
	T	operator () (const T& val1, const T& val2) const { return (val1 - val2); }
};


	// --- Multiply ---

template <class T>
class Multiply: public BinaryFunction <T, T, T>
{
public:
	T	operator () (const T& val1, const T& val2) const { return (val1 * val2); }
};


	// --- Divide ---

template <class T>
class Divide: public BinaryFunction <T, T, T>
{
public:
	T	operator () (const T& val1, const T& val2) const { return (val1 / val2); }
};


	// --- Modulus ---

template <class T>
class Modulus: public BinaryFunction <T, T, T>
{
public:
	T	operator () (const T& val1, const T& val2) const { return (val1 % val2); }
};


	// --- Negate ---

template <class T>
class Negate: public UnaryFunction <T, T>
{
public:
	T	operator () (const T& val) const { return (-val); }
};


	// --- Sum ---

template <class T>
class Sum: public UnaryFunction <T, void>
{
private:
	T	sum;

public:
	Sum (T sumInit = 0): sum (sumInit) {}

	void	operator () (T val) { sum += val; }

			operator T () const { return sum; }
};


	// --- Average ---

template <class T>
class Average: public UnaryFunction <T, void>
{
private:
	T		sum;
	USize	count;

public:
	Average (T sumInit = 0, USize countInit = 0): sum (sumInit), count (countInit) {}

	void	operator () (T val) { sum += val; count++; }

			operator double () const { return (count == 0 ? 0.0 : static_cast<double> (sum) / static_cast<double> (count)); }

	T		GetSum	 (void) const { return sum; }
	USize	GetCount (void) const { return count; }
};
// ____________________ Common mathematical function objects ___________________

}	// namespace GS


#endif
