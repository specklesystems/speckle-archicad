// *********************************************************************************************************************
// Description:		Attribute Data
//
// Module:			GSModeler2D
// Namespace:		Modeler
// Contact person:	AACS
//
// SG compatible
// *********************************************************************************************************************

#if !defined (TEXTUREDATA_HPP)
#define TEXTUREDATA_HPP

#pragma once
#include	"UniString.hpp"
#include	"GSUtilsDefs.h"

namespace Modeler {

	class TextureData 
	{
	public: 
		TextureData ()	
		{
			Initialize(); 
		}

		inline void SetInvalid() 
		{
			Initialize();
		}
			
		void Initialize()
		{
			isValid = false;
			xsiz = 0.0;
			ysiz = 0.0;
			status = 0;
			txtrImageName = "";
			pictIndex  = -1;
			rotAngleDEG = 0.0;
		}

		void Setup (
			double					xsizInit,
			double					ysizInit,
			STATW					statusInit,
			const GS::UniString&	txtrImageNameInit,
			short					pictIndexInit)
		{
			isValid =		true; 
			xsiz =			xsizInit;		
			ysiz =			ysizInit;		
			status =		statusInit;		
			txtrImageName =	txtrImageNameInit;	
			pictIndex =		pictIndexInit;	
		}

		void Setup (
			double					xsizInit,
			double					ysizInit,
			STATW					statusInit,
			const GS::UniString&	txtrImageNameInit,
			short					pictIndexInit, 
			double					rotAngleDEGInit)
		{
			isValid =		true; 
			xsiz =			xsizInit;		
			ysiz =			ysizInit;		
			status =		statusInit;		
			txtrImageName =	txtrImageNameInit;	
			pictIndex =		pictIndexInit;	
			rotAngleDEG =	rotAngleDEGInit; 
		}

		bool IsTextureValid () const 
		{
			return isValid;
		}

		void SetTextureValid ()
		{
			isValid = true;
		}


		//data to be able to create an RTXT: 
		double				xsiz;
		double				ysiz;
		STATW				status;
		GS::UniString		txtrImageName;
		short				pictIndex;

		//data for the corresponding UMAT:
		double				rotAngleDEG; 

	private:
		bool				isValid;
	};

} //Modeler
#endif