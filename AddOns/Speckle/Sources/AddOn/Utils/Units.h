#pragma once

#include <string>
#include <vector>

class Units {
public:
    static const std::string Millimeters;
    static const std::string Centimeters;
    static const std::string Meters;
    static const std::string Kilometers;
    static const std::string Inches;
    static const std::string Feet;
    static const std::string Yards;
    static const std::string Miles;
    static const std::string None;

    static bool IsUnitSupported(const std::string& unit);
    static double GetConversionFactor(const std::string& incomingUnits, const std::string& hostUnits);

private:
    static const std::vector<std::string> SupportedUnits;
    static std::string GetUnitsFromString(const std::string& unit);
};
