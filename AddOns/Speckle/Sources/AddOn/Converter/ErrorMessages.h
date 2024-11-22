#pragma once

#include <string>

class ErrorMessages final
{		
	public:
		static std::string Get(const int errCode);
};
