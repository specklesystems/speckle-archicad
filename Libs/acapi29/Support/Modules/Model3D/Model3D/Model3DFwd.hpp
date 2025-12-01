#if !defined(MODEL3DFWD_HPP)
#define MODEL3DFWD_HPP
#pragma once

#include "SharedPtr.hpp"

namespace Modeler {
	class Model3D;
	typedef GS::SharedPtr<Model3D> Model3DPtr;
	typedef GS::ConstSharedPtr<Model3D> ConstModel3DPtr;
}

#endif // MODEL3DFWD_HPP