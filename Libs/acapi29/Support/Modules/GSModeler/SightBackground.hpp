#ifndef _SIGHT_BACKGROUND__HPP_
#define _SIGHT_BACKGROUND__HPP_

#pragma once

// GSModeler
#include "GSModelerExport.h"
#include "Model3D/RTXT.hpp"

struct RENDSETS;

namespace IO {
	class MD5Channel;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Modeler {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class GSMODELER_DLL_EXPORT SightBackground
{
	class SightBackgroundImpl;

public:
	SightBackground ();
	~SightBackground ();

	SightBackground& operator= (const SightBackground& other);

public:
	void Update (const RENDSETS& rendSets, UInt32 hSize, UInt32 vSize);
	void Update (const RENDSETS& rendSets);

	RTXT GetBackgroundTexture ();

	static void WriteFingerPrint (IO::MD5Channel& md5Channel, const RENDSETS& rendSets);

private:
	SightBackgroundImpl* impl;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace Modeler {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // _SIGHT_BACKGROUND__HPP_
