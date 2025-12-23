#ifndef GX_COLORDEPTH_HPP
#define GX_COLORDEPTH_HPP
#pragma once

namespace GX {
enum ColorDepth : short {
	ColorDepth_Gray = 32,
	ColorDepth_BlackWhite = 1,
#ifdef macintosh
	ColorDepth_4_Colors = 2,
#endif
	ColorDepth_16_Colors = 4,
	ColorDepth_256_Colors = 8,
#ifdef WINDOWS
	ColorDepth_64K_Colors = 16,
	ColorDepth_24bit_TrueColor = 24,
	ColorDepth_32bit_TrueColor = 32,
#endif
#ifdef macintosh
	ColorDepth_Thousand_Colors = 16,
	ColorDepth_Million_Colors = 24,
	ColorDepth_Million_ColorsPlus = 32,
	ColorDepth_4_Grays = ColorDepth_4_Colors | ColorDepth_Gray,
#endif
	ColorDepth_16_Grays = ColorDepth_16_Colors | ColorDepth_Gray,
	ColorDepth_256_Grays = ColorDepth_256_Colors | ColorDepth_Gray
};
}

#endif