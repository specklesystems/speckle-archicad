#ifndef GS_UD_COLORRECORD_HPP
#define GS_UD_COLORRECORD_HPP

#include "Color.hpp"
#include "DGUtility.hpp"
#include "UDDefinitions.hpp"

namespace UD {

class UD_DLL_EXPORT ColorRecord
{
public:
	ColorRecord ();
	explicit ColorRecord (Gfx::Color color);

	ColorRecord (const ColorRecord& source);
	ColorRecord& operator= (const ColorRecord& source);

	ColorRecord (ColorRecord&& source) noexcept;
	ColorRecord& operator= (ColorRecord&& source) noexcept;

	~ColorRecord ();

	void SetColor (const Gfx::Color& color);

	Gfx::Color GetColor () const;
	DG::Icon   GetIcon () const;

private:
	static constexpr int IconSize = 12;

	friend bool operator== (const ColorRecord& self, const ColorRecord& other);

	Gfx::Color mColor;
	HICON	   mIcon = nullptr;
};

} // namespace UD

#endif // GS_UD_COLORRECORD_HPP
