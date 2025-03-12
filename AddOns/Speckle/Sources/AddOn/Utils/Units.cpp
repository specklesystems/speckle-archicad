#pragma warning(disable : 4244)

#include "Units.h"
#include <algorithm>
#include <stdexcept>

const std::string Units::Millimeters = "mm";
const std::string Units::Centimeters = "cm";
const std::string Units::Meters = "m";
const std::string Units::Kilometers = "km";
const std::string Units::Inches = "in";
const std::string Units::Feet = "ft";
const std::string Units::Yards = "yd";
const std::string Units::Miles = "mi";
const std::string Units::None = "none";

const std::vector<std::string> Units::SupportedUnits = {
    Units::Millimeters, Units::Centimeters, Units::Meters, Units::Kilometers,
    Units::Inches, Units::Feet, Units::Yards, Units::Miles, Units::None
};

bool Units::IsUnitSupported(const std::string& unit) 
{
    return std::find(SupportedUnits.begin(), SupportedUnits.end(), unit) != SupportedUnits.end();
}

double Units::GetConversionFactor(const std::string& incomingUnits, const std::string& hostUnits) 
{
    const std::string from = GetUnitsFromString(incomingUnits);
    const std::string to = GetUnitsFromString(hostUnits);

    if (from == to) return 1.0;

    if (from == Millimeters) 
    {
        if (to == Centimeters) return 0.1;
        if (to == Meters) return 0.001;
        if (to == Kilometers) return 1e-6;
        if (to == Inches) return 0.0393701;
        if (to == Feet) return 0.00328084;
        if (to == Yards) return 0.00109361;
        if (to == Miles) return 6.21371e-7;
    }
    else if (from == Centimeters) 
    {
        if (to == Millimeters) return 10;
        if (to == Meters) return 0.01;
        if (to == Kilometers) return 1e-5;
        if (to == Inches) return 0.393701;
        if (to == Feet) return 0.0328084;
        if (to == Yards) return 0.0109361;
        if (to == Miles) return 6.21371e-6;
    }
    else if (from == Meters) 
    {
        if (to == Millimeters) return 1000;
        if (to == Centimeters) return 100;
        if (to == Kilometers) return 0.001;
        if (to == Inches) return 39.3701;
        if (to == Feet) return 3.28084;
        if (to == Yards) return 1.09361;
        if (to == Miles) return 0.000621371;
    }
    else if (from == Kilometers) 
    {
        if (to == Millimeters) return 1000000;
        if (to == Centimeters) return 100000;
        if (to == Meters) return 1000;
        if (to == Inches) return 39370.1;
        if (to == Feet) return 3280.84;
        if (to == Yards) return 1093.61;
        if (to == Miles) return 0.621371;
    }
    else if (from == Inches) 
    {
        if (to == Millimeters) return 25.4;
        if (to == Centimeters) return 2.54;
        if (to == Meters) return 0.0254;
        if (to == Kilometers) return 2.54e-5;
        if (to == Feet) return 0.0833333;
        if (to == Yards) return 0.027777694;
        if (to == Miles) return 1.57828e-5;
    }
    else if (from == Feet) 
    {
        if (to == Millimeters) return 304.8;
        if (to == Centimeters) return 30.48;
        if (to == Meters) return 0.3048;
        if (to == Kilometers) return 0.0003048;
        if (to == Inches) return 12;
        if (to == Yards) return 0.333332328;
        if (to == Miles) return 0.000189394;
    }
    else if (from == Yards) 
    {
        if (to == Millimeters) return 914.4;
        if (to == Centimeters) return 91.44;
        if (to == Meters) return 0.9144;
        if (to == Kilometers) return 0.0009144;
        if (to == Inches) return 36;
        if (to == Feet) return 3;
        if (to == Miles) return 1.0 / 1760.0;
    }
    else if (from == Miles) 
    {
        if (to == Millimeters) return 1.609e+6;
        if (to == Centimeters) return 160934;
        if (to == Meters) return 1609.34;
        if (to == Kilometers) return 1.60934;
        if (to == Inches) return 63360;
        if (to == Feet) return 5280;
        if (to == Yards) return 1759.99469184;
    }

    return 1.0; // Default if no conversion is found
}

std::string Units::GetUnitsFromString(const std::string& unit) 
{
    std::string lowerUnit = unit;
    std::transform(lowerUnit.begin(), lowerUnit.end(), lowerUnit.begin(), ::tolower);

    if (lowerUnit == "mm" || lowerUnit == "mil" || lowerUnit == "millimeter" || lowerUnit == "millimeters" || lowerUnit == "millimetres")
        return Millimeters;
    if (lowerUnit == "cm" || lowerUnit == "centimetre" || lowerUnit == "centimeter" || lowerUnit == "centimetres" || lowerUnit == "centimeters")
        return Centimeters;
    if (lowerUnit == "m" || lowerUnit == "meter" || lowerUnit == "metre" || lowerUnit == "meters" || lowerUnit == "metres")
        return Meters;
    if (lowerUnit == "inches" || lowerUnit == "inch" || lowerUnit == "in")
        return Inches;
    if (lowerUnit == "feet" || lowerUnit == "foot" || lowerUnit == "ft")
        return Feet;
    if (lowerUnit == "yard" || lowerUnit == "yards" || lowerUnit == "yd")
        return Yards;
    if (lowerUnit == "miles" || lowerUnit == "mile" || lowerUnit == "mi")
        return Miles;
    if (lowerUnit == "kilometers" || lowerUnit == "kilometer" || lowerUnit == "km")
        return Kilometers;
    if (lowerUnit == "none")
        return None;

    throw std::out_of_range("Unrecognized unit string: " + unit);
}
