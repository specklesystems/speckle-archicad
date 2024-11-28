// *********************************************************************************************************************
// File:			InfoTag.hpp
//
// Description:
//
// Project:			ARCHICAD
//
// Namespace:
//
// Contact person:	MI, NZ, DG
//
// SG compatible
// *********************************************************************************************************************

#ifndef INFOTAG_HPP
#define INFOTAG_HPP

#pragma once


// --- Includes --------------------------------------------------------------------------------------------------------

#include "DGUtility.hpp"
#include "TransparentWindowLibDefinitions.hpp"
#include "RichText.hpp"
#include "NativeImage.hpp"
#include "TransparentWindow.hpp"


#pragma warning (disable: 4512)


// --- Predeclarations -------------------------------------------------------------------------------------------------

namespace Tracking {
	class InfoTagImpl;
}


namespace Tracking {

// --- Class declarations ----------------------------------------------------------------------------------------------

	class TRANSPARENTWINDOWLIB_DLL_EXPORT InfoTag:	public	TransparentWindow
	{
		friend class InfoTagImpl;
	private:
		TE::RichText	m_InfoString1;
		TE::RichText	m_InfoString2;
		NewDisplay::NativeImage m_image;
		TE::RichText	m_InfoString3;
///////////////////////////////////////////
//		DG::NativeRect	m_Rect;
		DG::NativePoint	m_Position;	// Screen relative position in native units
		short			m_Width;	// Logical units
		short			m_Height;	// Logical units
///////////////////////////////////////////
		DG::Rect		m_InfoRect1;
		DG::Rect		m_InfoRect2;
		DG::Rect		m_ImageRect1;
		DG::Rect		m_InfoRect3;
		Gfx::Color		m_ForegroundColor;
		Gfx::Color		m_BackgroundColor;
		Gfx::Color		m_FrameColor;
		double			m_ActualAlpha;
		double			m_EndAlpha;
		float			m_Opacity;
		GSTicks			m_FadeTick;
		GSTicks			m_BeginFadeTick;
		GSTicks			m_EndFadeTick;
		bool			m_Multiple;

	private:
		void				CallDraw ();
		//static DG::Rect	CalcRect (const DG::Point& point, const NewDisplay::NativeImage& image, TE::IRichText& string1, TE::IRichText& string2, const TE::IRichText& string3,
		//							  DG::Rect* pImageRect1 = nullptr, DG::Rect* pInfoRect1 = nullptr, DG::Rect* pInfoRect2 = nullptr, DG::Rect* pInfoRect3 = nullptr);
		static void			CalcRect (const DG::NativePoint& point, const NewDisplay::NativeImage& image, TE::IRichText& string1, TE::IRichText& string2, const TE::IRichText& string3,
									  short* width, short* height, double scaleFactor,
									  DG::Rect* pImageRect1 = nullptr, DG::Rect* pInfoRect1 = nullptr, DG::Rect* pInfoRect2 = nullptr, DG::Rect* pInfoRect3 = nullptr);

		void				CharColor (const Gfx::Color& color, TE::RichText& string);
		void				RoundRect (NewDisplay::NativeContext& context, float posX, float posY, float right, float bottom, float arcX, float arcY, const Gfx::Color& color);

	public:
		InfoTag				(const DG::NativePoint&			point,
							 const TE::RichText&			string1,
							 const TE::RichText&			string2,
							 const Gfx::Color&				foregroundColor,
							 const Gfx::Color&				backgroundColor,
							 const Gfx::Color&				frameColor,
							 float							opacity,
							 const NewDisplay::NativeImage& image,
							 const TE::IRichText&			string3,
							 bool							multiple);
		virtual				~InfoTag			();

	public:
		DG::NativeRect		GetRect				(void)											const;

		void				SetAlpha			(double alpha);
		double				GetAlpha			(void)											const;
		void				SetForegroundColor	(const Gfx::Color& foregroundColor);
		const Gfx::Color&	GetForegroundColor	(void)											const;
		void				SetBackgroundColor	(const Gfx::Color& backgroundColor);
		const Gfx::Color&	GetBackgroundColor	(void)											const;
		void				SetFrameColor		(const Gfx::Color& frameColor);
		const Gfx::Color&	GetFrameColor		(void)											const;
		void				SetOpacity			(float opacity);
		float				GetOpacity			(void)											const;
		DG::NativePoint		MapPointToScreen	(const DG::Point& pointToMap)					const;

		void				Draw				(void);
		bool				Redraw				(void);
		void				FadeIn				(void);
		void				FadeOut				(void);

		void				SetPosition			(const DG::NativePoint& point);
		void				SetSize				(short width, short height);

		void				MoveInfoTagAnimated	(const DG::NativePoint& moveTo, short milliSec);
		void				PlaceInFrontOf		(const short refDialId);
		void				SetContent			(const DG::NativePoint& point,
												 const NewDisplay::NativeImage& image,
												 const TE::RichText& text1,
												 const TE::RichText& text2,
												 const TE::IRichText& text3);
	};

}	//namespace Tracking

#endif
