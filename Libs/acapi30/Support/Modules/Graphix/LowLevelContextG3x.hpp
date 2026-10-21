// ******************************************************************************
// File:			LowLevelContextG3x.hpp
//
// Description:		Main interface for low level interface of G3x GPU model
//
// Contact person:	DG
//
// SG compatible
// ******************************************************************************

#ifndef	LOWLEVELCONTEXTG3x_HPP
#define	LOWLEVELCONTEXTG3x_HPP

// --- Includes -----------------------------------------------------------------

#include "LowLevelObjectsG3x.hpp"
#include "LowLevelContext.hpp"


// --- LowLevelContextG3x --------------------------------------------------------

namespace	Graphix	{

class	GRAPHIX_DLL_EXPORT	LowLevelContextG3x:	public LowLevelContext
{
public:
	virtual		~LowLevelContextG3x ();

	virtual		void			SetBlend (const BlendG3x* pDesc) = 0;
	virtual		void			SetRasterizer (const RasterizerG3x* pDesc) = 0;
	virtual		void			SetPixelShaderUniformBuffer (UInt32 slot, const UniformBuffer* uniformBuffer) = 0;
	virtual		void			SetVertexShaderUniformBuffer (UInt32 slot, const UniformBuffer* uniformBuffer) = 0;
	virtual		void			SetGeometryShaderUniformBuffer (UInt32 slot, const UniformBuffer* uniformBuffer) = 0;
	virtual		ViewportG3x		GetViewPortG3x () const = 0;
	virtual		void			SetViewPortG3x (const ViewportG3x* viewPort) = 0;	
};


} // namespace Graphix

#endif	// LOWLEVELCONTEXTG3x_HPP