// =============================================================================
// Description:		  Transformation
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (TRANSFORMATION_HPP)
#define TRANSFORMATION_HPP

// ----------------------- Includes          -----------------------------------
#include "GSModelerExport.h"
#include "TRANMAT.h"

// ----------------------- Class declaration -----------------------------------
namespace ModelerAPI {

class GSMODELER_DLL_EXPORT Transformation {
public:
	short	status;
	double	matrix[3][4];
	inline Transformation ();
	inline void SetToIdentity ();
	inline void FromTRANMAT (const TRANMAT* tran);
	inline void ToTRANMAT (TRANMAT* tran) const;
};


Transformation::Transformation ()
{
	SetToIdentity ();
}


void Transformation::SetToIdentity ()
{
	status = TR_IDENT;
	for (short i = 0; i < 3; i++) {
		for (short j = 0; j < 4; j++) {
			if (i == j) {
				matrix[i][j] = 1.0;
			} else {
				matrix[i][j] = 0.0;
			}
		}
	}
}


void Transformation::FromTRANMAT (const TRANMAT* tran)
{
	status = tran->status;
	for (short i = 0; i < 3; i++) {
		for (short j = 0; j < 4; j++) {
			matrix[i][j] = tran->GetMatrix ().Get (i, j);

		}
	}
}


void Transformation::ToTRANMAT (TRANMAT* tran) const
{
	if (tran == nullptr)
		throw GS::IllegalArgumentException ();

	tran->status = status;
	for (short i = 0; i < 3; i++) {
		for (short j = 0; j < 4; j++) {
			tran->tmx.Set (i, j, matrix[i][j]);

		}
	}
}


} // namespace ModelerAPI


#endif
