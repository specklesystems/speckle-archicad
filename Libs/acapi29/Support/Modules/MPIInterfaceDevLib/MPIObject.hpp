// *****************************************************************************
// MPI object base type
// GSUtils, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************

#if !defined (MPIOBJECT_HPP)
#define MPIOBJECT_HPP


// ----------------------- Includes --------------------------------------------

#include "MPIObjectFuncTable.hpp"
#include "GSRoot.hpp"


// ----------------------- Class declaration -----------------------------------
namespace MPI {

template<class FuncTable>
class Object {
protected:
	class Id;

	friend class Id;

	static FuncTable*	funcTable;

	class Id {
	private:
		Int32	value;

		inline ObjectFuncTable*	GetFuncTable (void)
		{
			return reinterpret_cast<ObjectFuncTable*> (Object::funcTable);
		}

	public:
		inline	 Id () :
			value (0)
		{
		}

		inline	 Id (const Id& source) :
			value (source.value)
		{
			if (value != 0 && GetFuncTable () != nullptr && GetFuncTable ()->addReference != nullptr) {
				GetFuncTable ()->addReference (value);
			}
		}

		inline	 Id (Int32 i) :
			value (i)
		{
			if (value != 0 && GetFuncTable () != nullptr && GetFuncTable ()->addReference != nullptr) {
				GetFuncTable ()->addReference (value);
			}
		}

		inline	~Id ()
		{
			if (value != 0 && GetFuncTable () != nullptr && GetFuncTable ()->deleteReference != nullptr) {
				GetFuncTable ()->deleteReference (value);
			}
		}

		inline	Id& operator= (const Id& source)
		{
			if (GetFuncTable () != nullptr) {
				if (source.value != 0 && GetFuncTable ()->addReference != nullptr) {
					GetFuncTable ()->addReference (source.value);
				}
				if (value != 0 && GetFuncTable ()->deleteReference != nullptr) {
					GetFuncTable ()->deleteReference (value);
				}
				value = source.value;
			}
			return *this;
		}

		inline	operator Int32 () const
		{
			return value;
		}
	};

	class Head {
	public:
		Int32	version;
		Id		headId;

		inline	Head (const Head& source) :
			version (source.version),
			headId (source.headId)
		{
		}

		inline	Head (Int32 vers) :
			version (vers),
			headId ()
		{
		}
	};

	static void		OnError (GSErrCode err);
};


// ----------------------- Class implementation --------------------------------

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------


template<class FuncTable>
FuncTable* Object<FuncTable>::funcTable = nullptr;

template<class FuncTable>
void	Object<FuncTable>::OnError (GSErrCode err)
{
	throw GS::GSException (nullptr, __FILE__, __LINE__, nullptr, err);
}

} // namespace MPI

#endif
