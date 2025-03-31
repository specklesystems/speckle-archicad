#pragma once

#include <iomanip>

class ARGBColorConverter
{
public:
	static uint32_t PackARGB(double A, double R, double G, double B);
	static void UnpackARGB(uint32_t argb, double& A, double& R, double& G, double& B);
};
