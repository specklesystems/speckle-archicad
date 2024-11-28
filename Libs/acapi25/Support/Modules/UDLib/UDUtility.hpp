// *********************************************************************************************************************
// File:			UDUtility.hpp
//
// Description:		Utility classes and functions for UD
//
// Project:			GRAPHISOFT User Dialog Module (UDLib)
//
// Namespace:		UD
//
// Contact person:	VM
// *********************************************************************************************************************

#ifndef UDUTILITY_HPP
#define UDUTILITY_HPP

// --- Includes --------------------------------------------------------------------------------------------------------

#include "DGUtility.hpp"
#include "HashCommon.hpp"
#include "HashTable.hpp"

#if defined (WINDOWS)
#include "DGWImageCache.hpp"
#endif


// --- Class declarations ----------------------------------------------------------------------------------------------

namespace UD {

#if defined (WINDOWS)
class WinImages
{
private:
	struct Key
	{
		GSResModule resModule;
		Int32 imageId;
		Int32 developerId;
		Int32 localId;
		UInt32 dpi;

		Key (GSResModule _resModule, Int32 _imageId, Int32 _developerId, Int32 _localId, UInt32 _dpi):
			resModule (_resModule),
			imageId (_imageId),
			developerId (_developerId),
			localId (_localId),
			dpi (_dpi)
		{
		}

		bool	operator== (const Key& other) const
		{
			return resModule == other.resModule && imageId == other.imageId && developerId == other.developerId && localId == other.localId && dpi == other.dpi;
		}

		ULong	GenerateHashValue () const
		{
			return GS::CalculateHashValue (resModule, imageId, developerId, localId, dpi);
		}
	};

	GS::HashTable<Key, DG::ImageCache::Image> add0nImages;

public:
	WinImages ()
	{
	};

	~WinImages ()
	{
	}

	DG::Icon	GetIcon (const DG::Icon& icon, const DG::Command& cmd, UInt32 dpi)
	{
		DG::Icon ic = icon;

		if (cmd.GetDeveloperId () != 0 && cmd.GetProductId () != 0) {
			Key key (icon.GetResourceModule (), icon.GetResourceId (), cmd.GetDeveloperId (), cmd.GetProductId (), dpi);

			if (add0nImages.ContainsKey (key)) {
				DG::ImageCache::Image& image = add0nImages.Get (key);
				ic = DG::Icon (image.GetIcon (dpi));
			} else {
				DG::ImageCache::Image image (icon.GetResourceModule (), icon.GetResourceId (), 0, 0, cmd.GetDeveloperId (), cmd.GetProductId ());
				ic = DG::Icon (image.GetIcon (dpi));
				add0nImages.Add (key, image);
			}
		}
		return ic;
	}
};
#endif

}	// namespace UD

#endif
