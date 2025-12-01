#ifndef DIMPROJECTIONTYPE_HPP
#define DIMPROJECTIONTYPE_HPP

namespace PVI {
	enum class DimProjectionType : int
	{
		ProjectToAngleDir = 1,
		ProjectToNominalDir = 2,
		Undefined = -1
	};
}

#endif

