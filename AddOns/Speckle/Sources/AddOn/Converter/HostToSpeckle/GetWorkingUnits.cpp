#include "HostToSpeckleConverter.h"
#include "ConverterUtils.h"
#include "WorkingUnits.h"

#include "APIEnvir.h"
#include "ACAPinc.h"
#include "CheckError.h"

namespace
{
    std::string LengthTypeToString(API_LengthTypeID lengthType) 
    {
        switch (lengthType) {
        case API_LengthTypeID::Meter: return "Meter";
        case API_LengthTypeID::Decimeter: return "Decimeter";
        case API_LengthTypeID::Centimeter: return "Centimeter";
        case API_LengthTypeID::Millimeter: return "Millimeter";
        case API_LengthTypeID::FootFracInch: return "FootFracInch";
        case API_LengthTypeID::FootDecInch: return "FootDecInch";
        case API_LengthTypeID::DecFoot: return "DecFoot";
        case API_LengthTypeID::FracInch: return "FracInch";
        case API_LengthTypeID::DecInch: return "DecInch";
        case API_LengthTypeID::KiloMeter: return "KiloMeter";
        case API_LengthTypeID::Yard: return "Yard";
        default: return "Unknown";
        }
    }

    std::string AreaTypeToString(API_AreaTypeID areaType) 
    {
        switch (areaType) {
        case API_AreaTypeID::SquareMeter: return "Meter";
        case API_AreaTypeID::SquareKiloMeter: return "KiloMeter";
        case API_AreaTypeID::SquareDeciMeter: return "DeciMeter";
        case API_AreaTypeID::SquareCentimeter: return "Centimeter";
        case API_AreaTypeID::SquareMillimeter: return "Millimeter";
        case API_AreaTypeID::SquareFoot: return "Foot";
        case API_AreaTypeID::SquareInch: return "Inch";
        case API_AreaTypeID::SquareYard: return "Yard";
        default: return "Unknown";
        }
    }

    std::string VolumeTypeToString(API_VolumeTypeID volumeType) 
    {
        switch (volumeType) {
        case API_VolumeTypeID::CubicMeter: return "Meter";
        case API_VolumeTypeID::CubicKiloMeter: return "KiloMeter";
        case API_VolumeTypeID::Liter: return "Liter";
        case API_VolumeTypeID::CubicCentimeter: return "Centimeter";
        case API_VolumeTypeID::CubicMillimeter: return "Millimeter";
        case API_VolumeTypeID::CubicFoot: return "Foot";
        case API_VolumeTypeID::CubicInch: return "Inch";
        case API_VolumeTypeID::CubicYard: return "Yard";
        case API_VolumeTypeID::Gallon: return "Gallon";
        default: return "Unknown";
        }
    }
}

nlohmann::json HostToSpeckleConverter::GetWorkingUnits()
{
	API_WorkingUnitPrefs workingPrefs{};
	CHECK_ERROR(ACAPI_ProjectSetting_GetPreferences(&workingPrefs, APIPrefs_WorkingUnitsID));

    API_CalcUnitPrefs calcPrefs{};
    CHECK_ERROR(ACAPI_ProjectSetting_GetPreferences(&calcPrefs, APIPrefs_CalcUnitsID));

    WorkingUnits units;

	units.workingLengthUnits = LengthTypeToString(workingPrefs.lengthUnit);
	units.workingAreaUnits = AreaTypeToString(workingPrefs.areaUnit);
	units.workingVolumeUnits = VolumeTypeToString(workingPrefs.volumeUnit);

    units.calculatedLengthUnits = LengthTypeToString(calcPrefs.length.unit);
    units.calculatedAreaUnits = AreaTypeToString(calcPrefs.area.unit);
    units.calculatedVolumeUnits = VolumeTypeToString(calcPrefs.volume.unit);

    return units;
}
