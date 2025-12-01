// =============================================================================
// Description:		  Rendering Settings
// Project:           3D Model Access API Refactoring
// Contact person:    SJ
// =============================================================================
#if !defined (RENDERINGSETTINGS_HPP)
#define RENDERINGSETTINGS_HPP

// ----------------------- Includes --------------------------------------------
#include "ModelRect.hpp"
#include "GSModelerExport.h"
#include "SharedPtr.hpp"

// ----------------------- Predeclaration -----------------------------------
namespace ModelerAPI {
	class RenderingSettingsRelay;
	class ParameterList;
	class Environment;
}

// ----------------------- Class declaration -----------------------------------
namespace ModelerAPI {


class GSMODELER_DLL_EXPORT RenderingSettings {
	friend class RenderingSettingsRelay;

private:
	GS::SharedPtr<ModelerAPI::RenderingSettingsRelay>	relay;	//itt nem const referencia marad! AACS

public:
	RenderingSettings ();
	RenderingSettings (const RenderingSettings& other);
	~RenderingSettings ();

	Rect	GetDrawingRect (void) const;
	Int32	GetExtraSettingsSize (void) const;
	Int32	GetExtraSettings (void* extraSettings, Int32 dataSize) const;
	void	GetProperties (ParameterList* properties) const;
	const Environment&	GetEnvironment (void) const;

	void	SetExtraSettings (const void* extraSettings, Int32 dataSize);
	void	SetProperties (ParameterList* properties);
	void	SetEnvironment (const Environment& location);
};


} // namespace ModelerAPI


#endif
