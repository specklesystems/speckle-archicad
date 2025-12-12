#include "PropertyDefinitions.h"

const std::unordered_map<API_ElemTypeID, std::vector<std::string>> PropertyDefinitions::propertyDefinitionIds = {
    { API_WallID, {
        "C1C47616-2BDD-49BF-92FB-CAC1206BF171", // Wall Height
        "41D36190-E3B6-4504-BF4F-1B7EBD02CBA2", // Wall Width
        "57597878-A6E8-4D43-BF52-CB4E157DBFE4", // Average length of the Wall
        // Converted TODO items:
        "BC7F0300-AC0C-468A-BB6C-7042703B1D74", // Surface Area of the Inside Face
        "DF59F2B5-55DB-415F-8BA9-562C255CB255", // Surface Area of the Outside Face
        "7A74F4E9-28F5-4EE0-BE1C-8E8B08F04FBC", // Wall Area
        "058E0BBF-826E-4E94-A40E-23B82CAF55F4", // Surface Area of Empty Openings in the Wall
        "812610C2-A7DF-4AF9-96E1-1CD044D41846", // Surface Area of the Wall Edges (Net)
        "CBC831B5-4B36-4DDE-B368-D42CB7152B10", // Surface Area of the Wall Inside Face (Conditional)
        "42FF9D89-8001-4DA5-9AAD-B11AF369F0C7", // Surface Area of the Wall Inside Face (Gross)
        "76E0997D-F61D-4501-B4E8-BF47BFDA838D", // Surface Area of the Wall Inside Face (Net)
        "06481385-9050-48DC-9F97-AE699F816DDE", // Surface Area of the Wall Outside Face (Conditional)
        "BC5C0BC9-797C-4914-96FE-1CE084BA80F2", // Surface Area of the Wall Outside Face (Gross)
        "9FF86DF1-5498-4925-83BA-1D9B97ABE103", // Surface Area of the Wall Outside Face (Net)
        "DBC01B52-B119-4E4E-91F0-4721EC8B6920", // Thickness of the Wall (Archicad 21)
        "579822E8-8A61-429F-96AA-77E7C19C1D01", // Area of the Doors
        "7366A8DD-768F-43D4-84D9-5FF2951D298B", // Area of the Windows
    }},
    { API_SlabID, {
        "A40FD114-CDA3-4554-8831-29FF73151153", // Surface Area of the Slab Top (Gross)
        "AD5116E3-95D9-42E3-A41A-D7155ADF0C5F", // Slab Perimeter
        "A824A045-80D7-4E3D-82A8-C82BD15EF0E5", // Slab Thickness
        // Converted TODO items:
        "A262A4F6-B149-4B4A-90A8-A17C253B62C7", // Bottom Surface Area (Conditional)
        "BE9B776F-CA40-488A-9CFF-35710DA5F364", // Bottom Surface Area (Gross)
        "FE0E55F4-5D5C-4958-9B9D-34D62515FC68", // Bottom Surface Area (Net)
        "4FE31D03-4314-4135-83A9-02CD357AF471", // Edge Surface Area (Gross)
        "9C9B21CB-1A3B-436A-BFAB-EF5DEFEF9633", // Edge Surface Area (Net)
        "54F2D1F7-CE44-43D4-B3F9-D9F8E2668C3C", // Top Surface Area (Conditional)
        "DDA19EED-E9CE-459E-BB8F-610C824939D7", // Top Surface Area (Gross)
        "32369326-82CF-4518-9ABD-B07ACA593A79" // Top Surface Area (Net)
    }},
    { API_BeamID, {
        "DADCDFC6-3AFF-415B-98ED-FDF9EF4B1807", // Beam Height
        "D8707463-22C1-412B-8146-AD7DCEF17E49", // Beam Width
        "BA0E29BD-A795-4A93-A33F-C2C17B46C33A", // 3D Length
        "CCC9ED1E-32D6-410C-9928-EF4C629AFAFB", // Beam Slant Angle
        // Converted TODO items:
        "8FA80A17-C680-4200-8185-BC64250326D3", // Surface Area of Both Beam Ends
        "998224E3-41FD-454A-A279-1DFA009FDFC3", // Surface Area of the Beam Bottom (Net)
        "F68CABD4-7198-4CCB-9DB9-D32943E74772", // Surface Area of the Beam Left Side (Net)
        "DD953D84-800D-4556-8EBF-6E33384E26B0", // Surface Area of the Beam Right Side (Net)
        "217C81EC-0113-438B-B176-693F58681680", // Surface Area of the Beam Top (Net)
    }},
    { API_ColumnID, {
        "2E32E96D-6220-4AE2-86C2-FEDB45450DC2", // Column Core Width
        "C9D4DA15-A7A7-4B5D-8E48-854F3D2A7053", // Column Core Height / Diameter
        "F4FEE28D-16B9-4801-B2F2-672CCCD872B0", // Column Length
        "7EDA68CA-D646-4180-B840-4327181C3E62", // Profile Height
        "A69ECF2A-DFEE-4B64-A1CF-C562F57FB503", // Profile Width
        "98E22B3A-C663-4249-8D85-BC5C4F32D487", // Veneer Thickness
        // Converted TODO items:
        "2EF10AB6-E374-42F6-BC03-F4696CACFFF7", // Column Core (Gross, no top/bottom)
        "863D9834-62CA-4EAA-9FD0-F854549D6ED6", // Column Core (Net, no top/bottom)
        "1F09B9C5-DCC3-4C8D-ACF3-237C1798315A", // Column Core Bottom (Gross)
        "2C928CA4-9160-4A4E-A82F-F046FA68A364", // Column Core Bottom (Net)
        "3B81F3F1-F297-499C-B508-8D69495D2430", // Column Core Top (Gross)
        "2A56FFC1-56D5-4BD2-96C9-68FBE95CB1A6", // Column Core Top (Net)
        "8A032B82-07D2-4DDD-8ECD-4E2793A8D02A", // Column Veneer (Gross, no top/bottom)
        "D74AE1B2-84BC-43D3-9A67-28D2F5E4D83A", // Column Veneer (Net)
        "E55E9D07-CC06-4413-BB58-9925C3A40FCE", // Column Veneer Bottom (Gross)
        "2DC11270-2540-4481-B91C-A9989AABB974", // Column Veneer Bottom (Net)
        "4EC22668-C024-48FC-9A15-A1AE74342E78", // Column Veneer Top (Gross)
        "89193DEB-15D8-46BC-AA0E-2E427078E247", // Column Veneer Top (Net)
    }},
    { API_RoofID, {
        "544ED0A0-0C04-4DCA-9F9A-82871C34C03E", // Surface Area of the Roof Bottom
        "D39090EB-5A07-4E2E-8521-FA60E8907592", // Surface Area of the Roof Top
        "48706EB0-152A-47A0-8963-AD00AA7CC11D", // Thickness
        "C4B62357-1289-4D43-A3F6-AB02B192864C", // Height
        "5BF6931F-82EB-40B8-B184-F51D20EC9D17", // Elevation to Project Zero
    }},
    { API_StairID, {
        "F914EBCF-B012-4DDC-976A-5BFFB5BD301A", // Default Going Depth
        "CD511852-FB66-426B-AC5B-DDAC12817792", // Default Riser Height
        "1C31D9CE-273B-4868-A891-103DC24FE7C8", // Default Riser Slant Angle
        "55F9F389-C7CF-4661-B603-5B3A0591CB21", // Default Stair Width
        "8EC256D5-C747-4778-A4BF-99047C25F4AF", // Required Headroom Height
        "4FFCB82F-1D60-4262-85B9-EC6FEC785D40", // Number Of Risers (total)
        "1108D4D8-BDFB-491D-B527-C1779EE03209", // Number Of Treads (total)
        "C58C7FC2-CBFC-4998-93D1-0A40A0D0681E", // Walking Line Length
    }},
    { API_DoorID, {
        "FE0E55F4-5D5C-4958-9B9D-34D62515FC68", // Bottom Surface Area (Net)
        "7CAB47B5-D80B-4E2F-AB2B-71CF0BB57856", // Height
        "8B474B84-BBD0-42CE-A257-14AA9B799BB7", // Jamb Width1
        "97D11F04-F9EF-475D-A818-EF9597079C1D", // Jamb Width2
        "8F5B1571-2E0B-4410-9286-351E77FBACA4", // Reveal Depth
        "19A99799-5B44-4A6F-9904-F132D7A3F0AC", // Width
    }},
    { API_WindowID, {
        "FE0E55F4-5D5C-4958-9B9D-34D62515FC68", // Bottom Surface Area (Net)
        "7CAB47B5-D80B-4E2F-AB2B-71CF0BB57856", // Height
        "8B474B84-BBD0-42CE-A257-14AA9B799BB7", // Jamb Width1
        "97D11F04-F9EF-475D-A818-EF9597079C1D", // Jamb Width2
        "8F5B1571-2E0B-4410-9286-351E77FBACA4", // Reveal Depth
        "19A99799-5B44-4A6F-9904-F132D7A3F0AC", // Width
    }},
    { API_ZoneID, {
        "9F8B3DFA-39D7-472D-A258-B988427C7EF9", // Calculated Area
        "BEE5C2BD-F962-4B48-A1C9-9ABE7C3ACDEB", // Doors Surface Area
        "14DBCC7C-CE1D-41C7-8640-4E3FAB0A51F8", // Doors Width
        "5CB80ECF-6973-430C-9C7B-7DD0E7378F44", // Room Net Volume
        "FAEC8521-13DD-41AB-BD56-A358161DF38B", // Windows Surface Area
        "37E784D9-2D6A-4FDF-90B2-4651F4B27A42", // Windows Width
        "4D6E3F47-B99E-43F8-8594-D6C47194AD11", // Zone Gross Perimeter
        "09CEBC76-3990-494A-9F85-5B5DFD6B16FE", // Zone Height
        "CAF8D1EB-0BAD-48DE-AEA4-9932ECA3D913", // Zone Name
        "46ABEB73-F338-4103-AE39-0BFF099D0423", // Zone Net Perimeter
        "77367980-3D5A-452B-9900-D88C53E82176", // Zone Number
    }},
    { API_ObjectID, {
        "7CAB47B5-D80B-4E2F-AB2B-71CF0BB57856", // Height
        "DA895241-B437-4897-864C-F001FD704F64", // Length (A)
        "19A99799-5B44-4A6F-9904-F132D7A3F0AC", // Width
    }}
};


PropertyDefinitions& PropertyDefinitions::Instance()
{
    static PropertyDefinitions instance;
    return instance;
}

std::vector<std::string> PropertyDefinitions::GetDefinitionIds(API_ElemTypeID elemType) const
{
    auto it = propertyDefinitionIds.find(elemType);
    if (it != propertyDefinitionIds.end()) 
    {
        return it->second;
    }
    return {};
}

std::vector<std::string> PropertyDefinitions::GetComponentDefinitionIds() const
{
    return 
    { 
        "0CFCB157-DFD2-4B3B-83AD-6DC285B669D5",     // Component Net Projected Area
        "DF702140-ADE7-4B61-8F2C-06052C438E72"      // Component Gross Projected Area
    };
}

std::vector<API_PropertyDefinition> PropertyDefinitions::GetDefinitions(API_ElemTypeID elemType)
{
    auto cached = cache.find(elemType);
    if (cached != cache.end()) 
    {
        return cached->second;
    }

    std::vector<API_PropertyDefinition> definitions;

    for (const auto& propertyId : GetDefinitionIds(elemType)) 
    {
        API_Guid propertyGuid = APIGuidFromString(propertyId.c_str());
        API_PropertyDefinition propertyDefinition{};
        propertyDefinition.guid = propertyGuid;

        if (ACAPI_Property_GetPropertyDefinition(propertyDefinition) == NoError) 
        {
            definitions.push_back(propertyDefinition);
        }
    }

    cache[elemType] = definitions;

    return definitions;
}

std::vector<API_PropertyDefinition> PropertyDefinitions::GetComponentDefinitions()
{
    std::vector<API_PropertyDefinition> definitions;

    for (const auto& propertyId : GetComponentDefinitionIds())
    {
        API_Guid propertyGuid = APIGuidFromString(propertyId.c_str());
        API_PropertyDefinition propertyDefinition{};
        propertyDefinition.guid = propertyGuid;

        if (ACAPI_Property_GetPropertyDefinition(propertyDefinition) == NoError)
        {
            definitions.push_back(propertyDefinition);
        }
    }

    return definitions;
}
