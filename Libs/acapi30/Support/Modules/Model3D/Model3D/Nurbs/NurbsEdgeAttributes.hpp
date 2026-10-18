#if !defined(NURBSEDGEATTRIBUTES_HPP)
#define NURBSEDGEATTRIBUTES_HPP

#pragma once

#include "Definitions.hpp"

#include "Model3D/Model3DExport.h"
#include "Model3D/EdgeAttributes.hpp"

namespace GS {
	class XMLIChannel;
	class XMLOChannel;
	class IChannel;
	class OChannel;
}


namespace Modeler {

class MODEL3D_DLL_EXPORT NurbsEdgeAttributes {
public:
	typedef short Color;
	
	enum class Visibility : GS::UChar { Visible, Invisible, VisibleIfContour };
	enum class Smoothness : GS::UChar { Sharp, Smooth };
	
	struct MODEL3D_DLL_EXPORT Status {
		Visibility	visibility	: 2;
		Smoothness	smoothness	: 1;

		Status (Visibility visibilityIn = Visibility::Visible, Smoothness smoothnessIn = Smoothness::Sharp)
			: visibility (visibilityIn)
			, smoothness (smoothnessIn)
		{
			// do nothing
		}

		bool operator== (const Status& other) const;

		void Read	(GS::IChannel& ic);			
		void Write	(GS::OChannel& oc) const;	

		void WriteXML	(GS::XMLOChannel& outXML) const;
		void ReadXML	(GS::XMLIChannel& inXML);
	};

private:
	Status	status;
	Color	color;

public:
	NurbsEdgeAttributes ();							//color member variable will be invalid!!!
	NurbsEdgeAttributes (Status statusIn, Color colorIn);
	NurbsEdgeAttributes (GS::XMLIChannel& inXML, const char* tagName) { ReadXML (inXML, tagName); }
	NurbsEdgeAttributes (const Modeler::EdgeAttributes &meshAttributes);

	Status		GetStatus	() const	{ return status;	}
	Color		GetColor	() const	{ return color;		}
	void		SetColor	(Color col)	{ color = col;		}
	void		SetInvisible ()			{ status.visibility = Visibility::Invisible; }

	bool operator== (const NurbsEdgeAttributes& other) const { return status == other.status && color == other.color; }


	void		Read	(GS::IChannel& ic);			
	void		Write	(GS::OChannel& oc) const;	

	void		WriteXML (GS::XMLOChannel& outXML, const char* tagName)	const;
	void		ReadXML (GS::XMLIChannel& inXML, const char* tagName);
};


}		// namespace Modeler

#endif	// NURBSEDGEATTRIBUTES_HPP
