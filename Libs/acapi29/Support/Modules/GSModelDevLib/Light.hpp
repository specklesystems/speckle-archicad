// =============================================================================
// Description:		  Light    
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (LIGHT_HPP)
#define LIGHT_HPP

// ----------------------- Includes --------------------------------------------
#include "GSModelerExport.h"
#include "ModelColor.hpp"
#include "Vertex.hpp"
#include "ModelVector.hpp"
#include "SharedPtr.hpp"
#include "CoordinateSystem.hpp"

#define AMBIENT_LIGHT_INDEX	1
#define CAMERA_LIGHT_INDEX	2
#define SUN_LIGHT_INDEX		3

// ----------------------- Predeclarations -------------------------------------
namespace ModelerAPI {
	class ParameterList;
	class ILightRelay;
}

// ----------------------- Class declaration -----------------------------------

namespace ModelerAPI {


class GSMODELER_DLL_EXPORT Light {
	friend class ModelLightRelay;
	friend class SpecialLightRelay;

private:
	GS::ConstSharedPtr<ModelerAPI::ILightRelay>	relay;

public:
	enum Type {
		UndefinedLight	= 0,
		DirectionLight	= 9200,
		SpotLight		= 9300,
		PointLight		= 9400,
		SunLight		= 9500,
		EyeLight		= 9600,
		AmbientLight	= 9700,
		CameraLight		= 9800
	};

	Light ();
	Light (const Light& other);
	~Light ();

	Light&	operator= (const Light& other);

	Type	GetType (void) const;
	bool	CastsShadow (void) const;
	Color	GetColor (void) const;
	Vertex	GetPosition (const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World) const;
	Vector	GetDirection (const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World) const;
	Vector	GetUpVector (const ModelerAPI::CoordinateSystem coordinateSystem = ModelerAPI::CoordinateSystem::World) const;
	double	GetRadius (void) const;
	double	GetAngleFalloff (void) const;
	double	GetFalloffAngle1 (void) const;
	double	GetFalloffAngle2 (void) const;
	double	GetDistanceFalloff (void) const;
	double	GetMinDistance (void) const;
	double	GetMaxDistance (void) const;
	void	GetExtraParameters (ParameterList* parameters) const;
};


} // namespace ModelerAPI


#endif
