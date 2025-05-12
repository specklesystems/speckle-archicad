#include "PropertyFilters.h"

const std::unordered_map<PropertyCollectionFilter, std::vector<std::string>> PropertyFilters::propertyFilters = {
    { PropertyCollectionFilter::GeneralRatings, {
        "E480E81E-EDE3-43FC-9C52-B55A4CA1A85C", // Fire Resistance Rating
        "13A61253-66A9-4494-9393-9E8F2E19D55E"  // Combustible
    }},
    { PropertyCollectionFilter::IFC, {
        "3B402C48-23D3-4A04-8BDF-E63E81318DAE", // External IFC ID
        "84A027A9-F2F1-40B4-A900-70A422B10829"  // Archicad IFC ID
    }},
    { PropertyCollectionFilter::Dimensional, {
        // Wall
		"C1C47616-2BDD-49BF-92FB-CAC1206BF171", // Wall Height (Archicad 20)
		"41D36190-E3B6-4504-BF4F-1B7EBD02CBA2", // Wall Width (Archicad 20)
		"57597878-A6E8-4D43-BF52-CB4E157DBFE4", // Average length of the Wall

		// Slab
		"A40FD114-CDA3-4554-8831-29FF73151153", // Surface Area of the Slab Top (Gross)
		"AD5116E3-95D9-42E3-A41A-D7155ADF0C5F", // Slab Perimeter (Archicad 21)
		"A824A045-80D7-4E3D-82A8-C82BD15EF0E5", // Slab Thickness (Archicad 20)

		// Beam
		"DADCDFC6-3AFF-415B-98ED-FDF9EF4B1807", // Beam Height (Archicad 20)
		"D8707463-22C1-412B-8146-AD7DCEF17E49", // Beam Width (Archicad 20)
		"BA0E29BD-A795-4A93-A33F-C2C17B46C33A", // 3D Length
		"CCC9ED1E-32D6-410C-9928-EF4C629AFAFB", // Beam Slant Angle

		// Column
		"2E32E96D-6220-4AE2-86C2-FEDB45450DC2", // Column Core Width
		"C9D4DA15-A7A7-4B5D-8E48-854F3D2A7053", // Column Core Height / Diameter
		"F4FEE28D-16B9-4801-B2F2-672CCCD872B0", // Column Length (Archicad 21)
		"7EDA68CA-D646-4180-B840-4327181C3E62", // Profile Height
		"A69ECF2A-DFEE-4B64-A1CF-C562F57FB503", // Profile Width
		"98E22B3A-C663-4249-8D85-BC5C4F32D487", // Veneer Thickness

		// Roof
		"544ED0A0-0C04-4DCA-9F9A-82871C34C03E", // Surface Area of the Roof Bottom (Conditional)
		"D39090EB-5A07-4E2E-8521-FA60E8907592", // Surface Area of the Roof Top (Conditional)
		"48706EB0-152A-47A0-8963-AD00AA7CC11D", // Thickness
		"C4B62357-1289-4D43-A3F6-AB02B192864C", // Height
		"5BF6931F-82EB-40B8-B184-F51D20EC9D17", // Elevation to Project Zero

		// Stair
		"F914EBCF-B012-4DDC-976A-5BFFB5BD301A", // Default Going Depth
		"CD511852-FB66-426B-AC5B-DDAC12817792", // Default Riser Height
		"1C31D9CE-273B-4868-A891-103DC24FE7C8", // Default Riser Slant Angle
		"55F9F389-C7CF-4661-B603-5B3A0591CB21", // Default Stair Width
		"8EC256D5-C747-4778-A4BF-99047C25F4AF", // Required Headroom Height
		"4FFCB82F-1D60-4262-85B9-EC6FEC785D40", // Number Of Risers (total)
		"1108D4D8-BDFB-491D-B527-C1779EE03209", // Number Of Treads (total)
		"C58C7FC2-CBFC-4998-93D1-0A40A0D0681E"  // Walking Line Length

		// Door/Window
		"FE0E55F4-5D5C-4958-9B9D-34D62515FC68", // Bottom Surface Area (Net)
		"7CAB47B5-D80B-4E2F-AB2B-71CF0BB57856", // Height
		"8B474B84-BBD0-42CE-A257-14AA9B799BB7", // Jamb Width1
		"97D11F04-F9EF-475D-A818-EF9597079C1D", // Jamb Width2
		"8F5B1571-2E0B-4410-9286-351E77FBACA4", // Reveal Depth
		"19A99799-5B44-4A6F-9904-F132D7A3F0AC", // Width

		// Zone
		"9F8B3DFA-39D7-472D-A258-B988427C7EF9", // Calculated Area
		"BEE5C2BD-F962-4B48-A1C9-9ABE7C3ACDEB", // Doors Surface Area
		"14DBCC7C-CE1D-41C7-8640-4E3FAB0A51F8", // Doors Width
		"5CB80ECF-6973-430C-9C7B-7DD0E7378F44", // Room Net Volume (Archicad 20)
		"FAEC8521-13DD-41AB-BD56-A358161DF38B", // Windows Surface Area
		"37E784D9-2D6A-4FDF-90B2-4651F4B27A42", // Windows Width
		"4D6E3F47-B99E-43F8-8594-D6C47194AD11", // Zone Gross Perimeter
		"09CEBC76-3990-494A-9F85-5B5DFD6B16FE", // Zone Height (Archicad 20)
		"CAF8D1EB-0BAD-48DE-AEA4-9932ECA3D913", // Zone Name
		"46ABEB73-F338-4103-AE39-0BFF099D0423", // Zone Net Perimeter
		"77367980-3D5A-452B-9900-D88C53E82176", // Zone Number
    }}
};

std::vector<std::string> PropertyFilters::Get(PropertyCollectionFilter filter)
{
    auto it = propertyFilters.find(filter);
    if (it != propertyFilters.end())
    {
        return it->second;
    }
    return {}; // Return empty vector if filter not found
}
