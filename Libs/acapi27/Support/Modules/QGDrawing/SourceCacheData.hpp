#pragma once

#if !defined SOURCECACHEDATA_HPP
#define SOURCECACHEDATA_HPP

namespace QG {

	class QG_DLL_EXPORT SourceCacheData {
	private:
		bool			isInCache;
		GS::UniString	hashKey;
	public:
		SourceCacheData ();
		SourceCacheData (GS::UniString hashKey, bool isInCache);
		~SourceCacheData ();
		
		void			SetInCache (bool isInCacheFlag);
		bool			IsInCache () const;
		GS::UniString	GetHashKey () const;
	};

}
#endif
