#pragma once

#if !defined SOURCECACHEDATA_HPP
#define SOURCECACHEDATA_HPP

namespace QG {

	class QG_DLL_EXPORT SourceCacheData {
	private:
		bool	isInCache;
		ULong	hashValue;
	public:
		SourceCacheData ();
		SourceCacheData (ULong hashValue, bool isInCache);
		~SourceCacheData ();
		
		void	SetInCache (bool isInCacheFlag);
		bool	IsInCache () const;
		ULong	GetHashValue () const;
	};

}
#endif
