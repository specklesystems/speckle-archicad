using System.Text;

namespace Speckle.Archicad.ReceiveService;

public class ArchicadElement
{
  private const string XML_HEADER = @"<?xml version=""1.0"" encoding=""UTF-8""?>
<Symbol IsArchivable=""false"" IsPlaceable=""true"" MainGUID=""CEC5B431-C761-4E74-9B8E-E1A65CE71670"" MigrationValue=""Normal"" Owner=""0"" Signature=""1196644685"" Version=""45"">
<Copyright SectVersion=""1"" SectionFlags=""0"" SubIdent=""0"">
	<Author>Speckle Systems</Author>
	<License>
		<Type>CC BY</Type>
		<Version>4.0</Version>
	</License>
</Copyright>

<Ancestry SectVersion=""1"" SectionFlags=""0"" SubIdent=""0"" Template=""false"">
	<MainGUID>F938E33A-329D-4A36-BE3E-85E126820996</MainGUID>
	<MainGUID>103E8D2C-8230-42E1-9597-46F84CCE28C0</MainGUID>
	<MainGUID>784EAEA1-5041-4AA6-B6F4-EF263A891EE7</MainGUID>
</Ancestry>

<ParamSection SectVersion=""27"" SectionFlags=""0"" SubIdent=""0"">
	<ParamSectHeader>
		<AutoHotspots>false</AutoHotspots>
		<StatBits>
			<STBit_FixSize/>
		</StatBits>
		<WDLeftFrame>0</WDLeftFrame>
		<WDRightFrame>0</WDRightFrame>
		<WDTopFrame>0</WDTopFrame>
		<WDBotFrame>0</WDBotFrame>
		<LayFlags>65535</LayFlags>
		<WDMirrorThickness>0</WDMirrorThickness>
		<WDWallInset>0</WDWallInset>
	</ParamSectHeader>
	<Parameters>
		<Length Name=""A"">
			<Description><![CDATA[""Méret 1""]]></Description>
			<Fix/>
			<Value>1</Value>
		</Length>
		<Length Name=""B"">
			<Description><![CDATA[""Méret 2""]]></Description>
			<Fix/>
			<Value>1</Value>
		</Length>
		<Length Name=""ZZYZX"">
			<Description><![CDATA[""Magasság""]]></Description>
			<Fix/>
			<Value>1</Value>
		</Length>
		<Boolean Name=""showOnlyContourEdgesIn3D"">
			<Description><![CDATA[""Show Only Contour Edges In 3D""]]></Description>
			<Value>1</Value>
		</Boolean>
		<RealNum Name=""map_xform"">
			<Description><![CDATA[""General Transformation""]]></Description>
			<ArrayValues FirstDimension=""4"" SecondDimension=""3"">
				<AVal Column=""1"" Row=""1"">1</AVal>
				<AVal Column=""2"" Row=""1"">0</AVal>
				<AVal Column=""3"" Row=""1"">0</AVal>
				<AVal Column=""1"" Row=""2"">0</AVal>
				<AVal Column=""2"" Row=""2"">1</AVal>
				<AVal Column=""3"" Row=""2"">0</AVal>
				<AVal Column=""1"" Row=""3"">0</AVal>
				<AVal Column=""2"" Row=""3"">0</AVal>
				<AVal Column=""3"" Row=""3"">1</AVal>
				<AVal Column=""1"" Row=""4"">0</AVal>
				<AVal Column=""2"" Row=""4"">0</AVal>
				<AVal Column=""3"" Row=""4"">0</AVal>
			</ArrayValues>
		</RealNum>
		<Boolean Name=""AC_show2DHotspotsIn3D"">
			<Description><![CDATA[""Show 2D Hotspots in 3D""]]></Description>
			<Fix/>
			<Value>0</Value>
		</Boolean>
		<Length Name=""ac_bottomlevel"">
			<Description><![CDATA[""Alsó szint""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Hidden/>
			</Flags>
			<Value>1</Value>
		</Length>
		<Length Name=""ac_toplevel"">
			<Description><![CDATA[""Felső szint""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Hidden/>
			</Flags>
			<Value>0</Value>
		</Length>

		<!-- gs_2D_representation: PARAMETER BLOCK ===== PARAMETER BLOCK ===== PARAMETER BLOCK ===== PARAMETER BLOCK -->

		<Title Name=""gs_2D_representation"">
			<Description><![CDATA[""Alaprajzi megjelenítés""]]></Description>
			<Fix/>
		</Title>
		<PenColor Name=""gs_cont_pen"">
			<Description><![CDATA[""Kontúr tolla""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value>2</Value>
		</PenColor>
		<FillPattern Name=""gs_fill_type"">
			<Description><![CDATA[""Kitöltéstípus""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value>65</Value>
		</FillPattern>
		<PenColor Name=""gs_fill_pen"">
			<Description><![CDATA[""Kitöltés tolla""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value>19</Value>
		</PenColor>
		<PenColor Name=""gs_back_pen"">
			<Description><![CDATA[""Kitöltésháttér tolla""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value>19</Value>
		</PenColor>

		<!-- gs_list: PARAMETER BLOCK ===== PARAMETER BLOCK ===== PARAMETER BLOCK ===== PARAMETER BLOCK -->

		<Title Name=""gs_list"">
			<Description><![CDATA[""Leírás""]]></Description>
			<Fix/>
		</Title>
		<RealNum Name=""gs_list_cost"">
			<Description><![CDATA[""Ár""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value>0</Value>
		</RealNum>
		<String Name=""gs_list_manufacturer"">
			<Description><![CDATA[""Gyártó""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value><![CDATA[""""]]></Value>
		</String>
		<String Name=""gs_list_note"">
			<Description><![CDATA[""Megjegyzés""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value><![CDATA[""""]]></Value>
		</String>
		<String Name=""gs_list_location"">
			<Description><![CDATA[""Hely""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value><![CDATA[""""]]></Value>
		</String>
		<String Name=""gs_list_accessories"">
			<Description><![CDATA[""Kiegészítők""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value><![CDATA[""""]]></Value>
		</String>
		<String Name=""FM_Type"">
			<Description><![CDATA[""Csoport típusa""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value><![CDATA[""Egyéb""]]></Value>
		</String>
		<Integer Name=""iFMType"">
			<Description><![CDATA[""Csoport típusa""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
				<ParFlg_Hidden/>
			</Flags>
			<Value>25</Value>
		</Integer>
		<String Name=""FM_InventoryNumber"">
			<Description><![CDATA[""Leltári szám""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value><![CDATA[""""]]></Value>
		</String>
		<String Name=""FM_SerialNumber"">
			<Description><![CDATA[""Sorozatszám""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value><![CDATA[""""]]></Value>
		</String>
		<String Name=""FM_ProductionYear"">
			<Description><![CDATA[""Gyártás éve""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value><![CDATA[""""]]></Value>
		</String>
		<RealNum Name=""FM_ObjectWeight"">
			<Description><![CDATA[""Súly""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value>0</Value>
		</RealNum>
		<String Name=""FM_ObjectWeightUnit"">
			<Description><![CDATA[""Súly egysége""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value><![CDATA[""kg""]]></Value>
		</String>
		<String Name=""gs_list_custom1"">
			<Description><![CDATA[""Egyedi paraméter 1""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value><![CDATA[""""]]></Value>
		</String>
		<String Name=""gs_list_custom2"">
			<Description><![CDATA[""Egyedi paraméter 2""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value><![CDATA[""""]]></Value>
		</String>
		<String Name=""gs_list_custom3"">
			<Description><![CDATA[""Egyedi paraméter 3""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value><![CDATA[""""]]></Value>
		</String>
		<String Name=""gs_list_custom4"">
			<Description><![CDATA[""Egyedi paraméter 4""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value><![CDATA[""""]]></Value>
		</String>
		<String Name=""gs_list_custom5"">
			<Description><![CDATA[""Egyedi paraméter 5""]]></Description>
			<Fix/>
			<Flags>
				<ParFlg_Child/>
			</Flags>
			<Value><![CDATA[""""]]></Value>
		</String>
	</Parameters>
</ParamSection>

<Comment SectVersion=""20"" SectionFlags=""0"" SubIdent=""0"">
<![CDATA[Speckle]]>
</Comment>

<Keywords SectVersion=""1"" SectionFlags=""0"" SubIdent=""0"">
<![CDATA[Speckle]]>
</Keywords>

<!-- GDL SCRIPT ===== GDL SCRIPT ===== GDL SCRIPT ===== GDL SCRIPT ===== GDL SCRIPT -->

<Script_1D SectVersion=""20"" SectionFlags=""0"" SubIdent=""0"">
<![CDATA[";

  private const string XML_MID = @"
]]>
</Script_1D>

<!-- GDL SCRIPT ===== GDL SCRIPT ===== GDL SCRIPT ===== GDL SCRIPT ===== GDL SCRIPT -->

<Script_3D SectVersion=""20"" SectionFlags=""0"" SubIdent=""0"">
<![CDATA[
!
! 3D Script (Generated by Speckle Connector)
!

defaultResolution = 36
RESOL defaultResolution

hiddenProfileEdge = 0
hiddenBodyEdge = 0
smoothBodyEdge = 0
visibleBodyEdge = 262144

IF (GLOB_CONTEXT % 10 >= 2 AND GLOB_CONTEXT % 10 <= 4) AND showOnlyContourEdgesIn3D <> 0 THEN
	hiddenProfileEdge = 1
	hiddenBodyEdge = 1
	smoothBodyEdge = 2
ENDIF

!

RESOL defaultResolution

XFORM map_xform[1][1], map_xform[2][1], map_xform[3][1], map_xform[4][1],
	map_xform[1][2], map_xform[2][2], map_xform[3][2], map_xform[4][2],
	map_xform[1][3], map_xform[2][3], map_xform[3][3], map_xform[4][3]

";

  private const string XML_FOOTER = @"
DEL TOP
]]>
</Script_3D>

<!-- GDL SCRIPT ===== GDL SCRIPT ===== GDL SCRIPT ===== GDL SCRIPT ===== GDL SCRIPT -->

<Script_2D SectVersion=""20"" SectionFlags=""0"" SubIdent=""0"">
<![CDATA[
!
cutPlaneHeight	= (GLOB_CSTORY_ELEV + GLOB_CUTPLANES_INFO[1]) - GLOB_HSTORY_ELEV
cutHeight = 0.01
iCutPlanes = 1

for i = 1 to iCutPlanes
	put cutPlaneHeight + (i-1) * cutHeight
next i

for i = 0 to iCutPlanes
	put 1+32,		! method
		2,				! parts
		1,				! cutFillIndex
		1,				! cutFillFgPen
		1,				! cutFillBgPen
		0.0,			! cutFillOrigoX
		0.0,			! cutFillOrigoY
		0.0,			! cutFillDirection
		1,				! cutLinePen
		1,				! cutLineType
		1,				! projectedFillIndex
		1,				! projectedFillFgPen
		1,				! projectedFillBgPen
		0.0,			! projectedFillOrigoX
		0.0,			! projectedFillOrigoY
		0.0,			! projectedFillDirection
		1,				! projectedLinePen
		1				  ! projectedLineType
next i

project2{4} 3, 270,
	0,			! useTransparency
	0,			! statusParts
	iCutPlanes,	! numCutplanes
	get (nsp)
]]>
</Script_2D>

</Symbol>";

  public bool Empty => Meshes.Count == 0;
  public List<ArchicadMesh> Meshes { get; }
  public List<ArchicadMaterial> Materials { get; }

  public ArchicadElement()
  {
    Meshes = new List<ArchicadMesh>();
    Materials = new List<ArchicadMaterial>();
  }

  public void AddMesh(ArchicadMesh mesh)
  {
    Meshes.Add(mesh);
  }

  public void AddMaterial(ArchicadMaterial material)
  {
    Materials.Add(material);
  }

  public override string ToString()
  {
    var sb = new StringBuilder();
    sb.Append(XML_HEADER);

    foreach (var material in Materials) 
    { 
      sb.Append(material.ToString());
    }

    sb.Append(XML_MID);

    foreach (var mesh in Meshes)
    {
      sb.AppendLine(mesh.ToString());
    }

    sb.Append(XML_FOOTER);
    return sb.ToString();
  }
}
