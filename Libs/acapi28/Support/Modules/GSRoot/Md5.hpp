// *****************************************************************************
// Description:		MD5 fingerprint code
//
// Namespaces:		MD5
// Contact persons:	HK, FM
//
// [SG compatible]
// *****************************************************************************

#ifndef MD5_H
#define MD5_H

// --------- Includes ----------------------------------------------------------

#include	"GSRootExport.hpp"
#include	"String.hpp"
#include	"ChecksumUpdater.hpp"

// --------- Predeclarations ---------------------------------------------------

namespace GS {
	class Guid;
	class OChannel;
	class IChannel;
}


// --------- Classes -----------------------------------------------------------

namespace MD5 {

	// --- class FingerPrint ---------------------------------------------------
	class GSROOT_DLL_EXPORT FingerPrint final {
	public:
							FingerPrint ();
		explicit			FingerPrint (unsigned char fp[16]);
		explicit			FingerPrint (const GS::String& md5String);

		void				Set (unsigned char fp[16]);
		void				Set (const GS::String& md5String);
		GSErrCode			Write (GS::OChannel& oc) const;
		GSErrCode			Read (GS::IChannel& ic);
		GSErrCode			GetAsString (char* md5String) const;
		GS::String			GetAsGsString () const;
		GS::UInt64			GetUInt64Value () const;
		bool				IsEmpty (void) const;
		ULong				GenerateHashValue (void) const;
		void				Clear (void);

		bool				operator == (const FingerPrint& rhs) const;
		bool				operator != (const FingerPrint& rhs) const;

	public:
		unsigned char		data[16];
	};

	// --- class Generator -----------------------------------------------------
	class GSROOT_DLL_EXPORT Generator : public GS::ChecksumUpdater {
	public:
		Generator ();

		virtual void	Update (const void* data, unsigned int size) override final;
		void			Update (GS::IChannel& ic);
		void			Finish (FingerPrint& result);	// Deprecated.
		FingerPrint		Finish (void);

	private:
		char	mData[128];
	};

}

#endif
