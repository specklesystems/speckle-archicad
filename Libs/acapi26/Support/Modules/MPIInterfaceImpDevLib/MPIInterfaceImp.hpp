// *****************************************************************************
// MPI Add-On interface implementer
// GSUtils, Platform independent
//
// Namespaces:        Contact person:
//                         PCS
//
// SG compatible
// *****************************************************************************

#if !defined (MPIINTERFACEIMP_HPP)
#define MPIINTERFACEIMP_HPP


// ----------------------- includes --------------------------------------------

#include "MPIInterfaceImpBase.hpp"
#include "MPIInterfaceBaseTypes.hpp"
#include "MPIInterfaceManager.hpp"
#include "MPIFuncTableHead.hpp"


// ----------------------- Class declaration -----------------------------------

namespace MPI {

template <Int32 Type, Int32 Version, class FuncTable>
class InterfaceImp : public InterfaceImpBase {
private:
	static bool MPI_ADD_ON_CALL CheckVersionCallBack (Int32 version);

	void	FillFuncTable (void);
	bool	CheckVersion (Int32 version);	// pcs 2002.11.28 TT#21065

protected:
	FuncTable		funcTable;
	FuncTable*		GetFuncTable (void);

public:
	InterfaceImp ();
	InterfaceImp (InterfaceManager* manager);

	virtual void*	GetInterface (Int32 type, Int32 version) override;
};


// ----------------------- Class implementation --------------------------------

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

template <Int32 Type, Int32 Version, class FuncTable>
bool MPI_ADD_ON_CALL InterfaceImp<Type, Version, FuncTable>::CheckVersionCallBack (Int32 version)
{
//	*result = CheckVersion (version);		// pcs 2002.11.28 TT#21065
	return (version == Version);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

template <Int32 Type, Int32 Version, class FuncTable>
void	InterfaceImp<Type, Version, FuncTable>::FillFuncTable (void)
{
	FuncTableHead* funcTableHead = reinterpret_cast<FuncTableHead*> (&funcTable);

	funcTableHead->type		= Type;
	funcTableHead->version	= Version;

	funcTableHead->checkVersion = CheckVersionCallBack;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

template <Int32 Type, Int32 Version, class FuncTable>
bool InterfaceImp<Type, Version, FuncTable>::CheckVersion (Int32 version)
{
//	return (version == Version || (version % 1000 == 0 && version % 1000 <= Version % 1000));		// pcs 2002.11.28 TT#21065
	FuncTableHead* funcTableHead = reinterpret_cast<FuncTableHead*> (&funcTable);
	bool result = funcTableHead->checkVersion (version);
	return result;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

template <Int32 Type, Int32 Version, class FuncTable>
FuncTable*	InterfaceImp<Type, Version, FuncTable>::GetFuncTable (void)
{
	return &funcTable;
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

template <Int32 Type, Int32 Version, class FuncTable>
InterfaceImp<Type, Version, FuncTable>::InterfaceImp ()
{
	FillFuncTable ();
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

template <Int32 Type, Int32 Version, class FuncTable>
InterfaceImp<Type, Version, FuncTable>::InterfaceImp (InterfaceManager* manager)
{
	FillFuncTable ();
	manager->RegisterInterfaceImp (this);
}


// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

template <Int32 Type, Int32 Version, class FuncTable>
inline void*	InterfaceImp<Type, Version, FuncTable>::GetInterface (Int32 type, Int32 version)		//mm-vs2005
{
	void* ret = nullptr;
	if (type == Type && CheckVersion (version)) {
		ret = &funcTable;
	}
	return ret;
}

} // namespace


#endif
