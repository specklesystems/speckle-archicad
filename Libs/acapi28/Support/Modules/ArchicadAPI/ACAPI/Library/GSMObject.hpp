#ifndef ACAPI_LM_GSMOBJECT_HPP
#define ACAPI_LM_GSMOBJECT_HPP

#include "ACAPI/Object.hpp"
#include "ACAPI/Result.hpp"
#include "ACAPI/ModifyScope.hpp"
#include "ACAPI/ArchicadAPIExport.hpp"

// GX
#include "GXImage.hpp"

#include <vector>


//! @cond Doxygen_Suppress
API_Token ACAPI_GetToken ();
//! @endcond


namespace GS { class UnID; }
namespace GDL { class Parameters; }
class VectorImage;

namespace ACAPI {
namespace Library {

namespace v1 {
class GSMObject;
class LibPart;
}


namespace Impl {
class GSMObjectImpl;
class LibraryManagerImpl;

//! @cond Doxygen_Suppress
ACAPI::Result<ACAPI::Library::v1::GSMObject> LoadGSMObjectFromFile (const API_Token& token, const IO::Location& fileLocation);
//! @endcond

}  // namespace Impl


namespace v1 {


/**
 * @brief Raw GSMObject Section representation.
 * @ingroup LibraryManagement
 * @details Mainly used for store and retreive add-on's custom data in GSM contents.
 */
struct ARCHICADAPI_EXPORT GSMSectionData {
	/**
	 * @brief Version of the data format.
	 * @ingroup LibraryManagement
	 */
	int16_t dataVersion;

	/**
	 * @brief Raw bites of the stored data.
	 * @ingroup LibraryManagement
	 */
	std::vector<std::byte> data;
};


/**
 * @brief GSMObject is the representation of a loaded .gsm file
 * @details A GSMObject can represent a .gsm file which is loaded from the local file system or loaded from a library. Only GSM objects loaded from file can be modified.
 * @ingroup LibraryManagement
 * @since Archicad 28
 */
class ARCHICADAPI_EXPORT GSMObject final : public Object
{
	//! @cond Doxygen_Suppress
	friend class Impl::LibraryManagerImpl;
	friend class Impl::GSMObjectImpl;
	friend ACAPI::Result<GSMObject> Impl::LoadGSMObjectFromFile (const API_Token& token, const IO::Location& fileLocation);

	explicit GSMObject (std::shared_ptr<Impl::GSMObjectImpl> gsmObjectImpl);
	bool							IsValid () const;
	static ACAPI::Result<GSMObject> Load (const API_Token& token, const IO::Location& fileLocation);
	//! @endcond

public:
	class Modifier;

	/**
	 * @brief Control flags for the copy of the GSM objects.
	 * @details GenerateNewUnID: The new object gets different UnID; KeepMainGuid: Creates a new revision.
	 * @ingroup LibraryManagement
	 */
	enum class CopyMethod {
		GenerateNewUnID,
		KeepMainGuid
	};

	/**
	 * @brief Creates a new empty GSM Object.
	 * @ingroup LibraryManagement
	 * @param fileLocation The path of the new GSM file. It should be a non-existing gsm file in an existing folder.
	 * @param ancestorSubType The ancestor subtype of the new object. It should be a valid and loaded subtype object.
	 * 						  The new object will inherit the parameters of the ancestor subtype.
	 * @return The new GSMObject if succesfully created otherwise Error.
	 */
	static ACAPI::Result<GSMObject> CreateNew (const IO::Location& fileLocation, const ACAPI::Library::v1::GSMObject& ancestorSubType);
	
	/**
	 * @brief Creates a new copy from the GSM file to a location.
	 * @ingroup LibraryManagement
	 * @param fileLocation The path of the new GSM file. It should be a non-existing gsm file in an existing folder.
	 * @param method KeepMainGuid: Creates a new revision; GenerateNewUnID: The new object gets different UnID.
	 * @return The new GSMObject if succesfully created otherwise Error.
	 */
	ACAPI::Result<void> CopyTo (const IO::Location& fileLocation, CopyMethod method = CopyMethod::KeepMainGuid);

	/**
	 * @brief Opens a modification scope if the object is editable. See 'IsEditable'
	 * @ingroup LibraryManagement
	 * @param modifierFunc The function which will be called with a 'Modifier' object. Through this object can be the GSMObject modified.
	 * @param password If the GSMObject is password protected, the correct password must be given. Otherwise the modifier function will not be called.
	 * @return Returns Ok, if the modification was succesful otherwise Error.
	 */
	ACAPI::Result<void> Modify (const std::function<GSErrCode (Modifier&)>& modifierFunc, GS::UniString password = GS::EmptyUniString);

	/**
	 * @brief A GSM file is editable if it is loaded from the local file system. GSM files from Loaded Libraries should be copied into a local directory before editing.
	 * @ingroup LibraryManagement
	 * @return Returns true if it is loaded from the file system or created/copied into a writable file.
	 */
	bool IsEditable () const;

	/**
	 * @brief The UnID is a combination of the main guid and the revision guid.
	 * @ingroup LibraryManagement
	 * @return Returns unique ID (main guid + rev. guid) of the gsm object
	 */
	ACAPI::Result<GS::UnID> GetUnID () const;

	/**
	 * @brief The object can be placed in a plan file.
	 * @ingroup LibraryManagement
	 * @return Returns true if the .gsm can be placed as an 'object' in a plan file, false otherwise
	 */
	ACAPI::Result<bool> IsPlaceable () const;

	/**
	 * @brief The object is password protected and encrypted.
	 * @ingroup LibraryManagement
	 * @return Returns true if the .gsm file is password-protected
	 */
	ACAPI::Result<bool> IsPasswordProtected () const;

	/**
	 * @brief The UnID of the object's direct ancestor in the subtype hierarchy.
	 * @ingroup LibraryManagement
	 * @return Returns the UnID of the objects subtype
	 */
	ACAPI::Result<GS::UnID> GetSubTypeUnID () const;

	/**
	 * @brief The object is an 'object subtype'.
	 * @ingroup LibraryManagement
	 * @return Returns true if the gsm object is an 'object subtype', false otherwise
	 */
	ACAPI::Result<bool> IsSubType () const;

	/**
	 * @brief The object is a subtype of the given UnID.
	 * @ingroup LibraryManagement
	 * @param subTypeID The id of the sub type.
	 * @return Returns true if the gsm object falls under the subtype noted by the given UnID, false otherwise
	 */
	ACAPI::Result<bool> IsInSubTypeOf (const GS::UnID& subTypeID) const;

	/**
	 * @brief Checks whether MasterScript has value or is empty
	 * @ingroup LibraryManagement
	 * @return Returns true if the MasterScript section has value, false otherwise
	 */
	bool HasMasterScript () const;
	
	/**
	 * @brief Checks whether 2DScript section has value or is empty
	 * @ingroup LibraryManagement
	 * @return Returns true if the 2DScript section has value, false otherwise
	 */
	bool Has2DScript () const;
	
	/**
	 * @brief Checks whether 3DScript section has value or is empty
	 * @ingroup LibraryManagement
	 * @return Returns true if the 3DScript section has value, false otherwise
	 */
	bool Has3DScript () const;
	
	/**
	 * @brief Checks whether PropertiesScript section has value or is empty
	 * @ingroup LibraryManagement
	 * @return Returns true if the PropertiesScript section has value, false otherwise
	 */
	bool HasPropertiesScript () const;
	
	/**
	 * @brief Checks whether ParameterScript section has value or is empty
	 * @ingroup LibraryManagement
	 * @return Returns true if the ParameterScript section has value, false otherwise
	 */
	bool HasParameterScript () const;
		
	/**
	 * @brief Checks whether InterfaceScript section has value or is empty
	 * @ingroup LibraryManagement
	 * @return Returns true if the InterfaceScript section has value, false otherwise
	 */
	bool HasInterfaceScript () const;
		
	/**
	 * @brief Checks whether ForwardMigrationScript section has value or is empty
	 * @ingroup LibraryManagement
	 * @return Returns true if the ForwardMigrationScript section has value, false otherwise
	 */
	bool HasForwardMigrationScript () const;

	/**
	 * @brief Checks whether BackwardMigrationScript section has value or is empty
	 * @ingroup LibraryManagement
	 * @return Returns true if the BackwardMigrationScript section has value, false otherwise
	 */
	bool HasBackwardMigrationScript () const;
		
	/**
	 * @brief Checks whether 2DVectorImage section has value or is empty
	 * @ingroup LibraryManagement
	 * @return Returns true if the 2DVectorImage section has value, false otherwise
	 */
	bool Has2DVectorImage () const;
		
	/**
	 * @brief Checks whether PreviewPicture section has value or is empty
	 * @ingroup LibraryManagement
	 * @return Returns true if the PreviewPicture section has value, false otherwise
	 */
	bool HasPreviewPicture () const;
		
	/**
	 * @brief Checks whether GDLPictures section has value or is empty
	 * @ingroup LibraryManagement
	 * @return Returns true if the GDLPictures section has value, false otherwise
	 */
	bool HasGDLPictures () const;
		
	/**
	 * @brief Checks whether CustomSection has value or is empty
	 * @ingroup LibraryManagement
	 * @param sectionTypeID A four-byte identifier of the custom section. Like 'sect'.
	 * @param index The index of the custom sections with similar type ID.
	 * @return Returns true if the CustomSection section has value, false otherwise
	 */
	bool HasCustomSection (uint32_t sectionTypeID, uint16_t index) const;
		
	/**
	 * @brief Author of the object.
	 * @ingroup LibraryManagement
	 * @return Returns the Author of the object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GS::UniString> GetAuthor () const;

	/**
	 * @brief License name of the object.
	 * @ingroup LibraryManagement
	 * @return Returns the license of the object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GS::UniString> GetLicense () const;

	/**
	 * @brief License version of the object.
	 * @ingroup LibraryManagement
	 * @return Returns the license version of the object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GS::UniString> GetLicenseVersion () const;

	/**
	 * @brief Description of the object.
	 * @ingroup LibraryManagement
	 * @return Returns the description of the object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GS::UniString> GetDescription () const;

	/**
	 * @brief Keywords of the object. Mostly used for search. Usually it is a comma separated list.
	 * @ingroup LibraryManagement
	 * @return Returns the keywords of the object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GS::UniString> GetKeywords () const;

	/**
	 * @brief Parameter list of the object.
	 * @ingroup LibraryManagement
	 * @return Returns the parameter list of the object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GDL::Parameters> GetParameters () const;

	/**
	 * @brief Parameter descriptions of the object.
	 * @ingroup LibraryManagement
	 * @return Returns the parameter descriptions. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<std::vector<GS::UniString>> GetParameterDescriptions () const;

	/**
	 * @brief Master script of the object.
	 * @ingroup LibraryManagement
	 * @param password Optional parameter. Required if the object is password protected
	 * @return Returns the Master script (1D script) of the gsm object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GS::UniString> GetMasterScript (const GS::UniString& password = GS::EmptyUniString) const;

	/**
	 * @brief 2D script of the object.
	 * @ingroup LibraryManagement
	 * @param password Optional parameter. Required if the object is password protected
	 * @return Returns the 2D script of the gsm object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GS::UniString> Get2DScript (const GS::UniString& password = GS::EmptyUniString) const;

	/**
	 * @brief 3D script of the object.
	 * @ingroup LibraryManagement
	 * @param password Optional parameter. Required if the object is password protected
	 * @return Returns the 3D script of the gsm object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GS::UniString> Get3DScript (const GS::UniString& password = GS::EmptyUniString) const;

	/**
	 * @brief Properties script of the object.
	 * @ingroup LibraryManagement
	 * @param password Optional parameter. Required if the object is password protected
	 * @return Returns the Properties script of the gsm object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GS::UniString> GetPropertiesScript (const GS::UniString& password = GS::EmptyUniString) const;

	/**
	 * @brief Parameter script of the object.
	 * @ingroup LibraryManagement
	 * @param password Optional parameter. Required if the object is password protected
	 * @return Returns the Parameter script of the gsm object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GS::UniString> GetParameterScript (const GS::UniString& password = GS::EmptyUniString) const;

	/**
	 * @brief Interface script of the object.
	 * @ingroup LibraryManagement
	 * @param password Optional parameter. Required if the object is password protected
	 * @return Returns the Interface script of the gsm object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GS::UniString> GetInterfaceScript (const GS::UniString& password = GS::EmptyUniString) const;

	/**
	 * @brief The defined interface is set as default UI.
	 * @ingroup LibraryManagement
	 * @return Returns true if the defined interface is set as default UI. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<bool> IsUIDefault () const;

	/**
	 * @brief The defined interface uses hierarchical pages.
	 * @ingroup LibraryManagement
	 * @return Returns true if the defined interface uses hierarchical pages. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<bool> IsHierarchicalPagesUsed () const;

	/**
	 * @brief Forward Migration script of the object.
	 * @ingroup LibraryManagement
	 * @param password Optional parameter. Required if the object is password protected
	 * @return Returns the Forward Migration script of the gsm object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GS::UniString> GetForwardMigrationScript (const GS::UniString& password = GS::EmptyUniString) const;

	/**
	 * @brief Backward Migration script of the object.
	 * @ingroup LibraryManagement
	 * @param password Optional parameter. Required if the object is password protected
	 * @return Returns the Backward Migration script of the gsm object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GS::UniString> GetBackwardMigrationScript (const GS::UniString& password = GS::EmptyUniString) const;

	/**
	 * @brief 2D Vector Image of the object.
	 * @ingroup LibraryManagement
	 * @return Returns the 2D Vector Image data (2D Symbol) of the gsm object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<VectorImage> Get2DVectorImage () const;

	/**
	 * @brief Preview picture of the object.
	 * @ingroup LibraryManagement
	 * @return Returns the Preview picture of the gsm object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GX::ImageRef> GetPreviewPicture () const;

	/**
	 * @brief Embedded pictures of the object.
	 * @ingroup LibraryManagement
	 * @return Returns the embedded pictures of the gsm object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<std::vector<GX::ImageRef>> GetGDLPictures () const;

	/**
	 * @brief Custom section data of the object.
	 * @ingroup LibraryManagement
	 * @param sectionID The identifier of the custom section.
	 * @param index The index of the section data if there are stored more than one
	 * @return Returns the selected custom section data of the gsm object. If the object's reference is not valid, it will return an error.
	 */
	ACAPI::Result<GSMSectionData> GetCustomSection (uint32_t sectionID, uint16_t index = 0) const;
};


/**
 * @brief The modifier object of the GSMObject.
 * @ingroup LibraryManagement
 */
class ARCHICADAPI_EXPORT GSMObject::Modifier final : public ACAPI::ModifierBase
{
	friend GSMObject;
	GSMObject& parent;
	Modifier (GSMObject& parent);
	virtual ~Modifier ();
	virtual void FinalizeModification () override;

public:

	/**
	 * @brief Sets the placeable flag of the object. If true, the object can be placed in a plan file.
	 * @ingroup LibraryManagement
	 * @param placeable If true, the object will be placeable.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetPlaceable (bool placeable);

	/**
	 * @brief Sets the password of the object. If a password is set, it will encrypt and lock the object.
	 * @ingroup LibraryManagement
	 * @param newPassword The new password. If empty, the password will be deleted.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetPassword (const GS::UniString& newPassword);

	/**
	 * @brief Sets the object as a subtype.
	 * @ingroup LibraryManagement
	 * @param isSubType If true the object will be a subtype.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetIsSubtype (bool isSubType);

	/**
	 * @brief Sets the author of the object.
	 * @ingroup LibraryManagement
	 * @param author The new author value.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetAuthor (const GS::UniString& author);

	/**
	 * @brief Sets the license code of the object.
	 * @ingroup LibraryManagement
	 * @param license The new license code.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetLicense (const GS::UniString& license);

	/**
	 * @brief Sets the license version of the object.
	 * @ingroup LibraryManagement
	 * @param licVer The new license version.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetLicenseVersion (const GS::UniString& licVer);

	/**
	 * @brief Sets the description of the object.
	 * @ingroup LibraryManagement
	 * @param description The new description.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetDescription (const GS::UniString& description);

	/**
	 * @brief Sets the keywords of the object. That is used by several search tools. Usually it is a comma separated list.
	 * @ingroup LibraryManagement
	 * @param keywords The new keywords.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetKeywords (const GS::UniString& keywords);

	/**
	 * @brief Sets the parameters of the object. This function will replace the entire parameter list.
	 * @ingroup LibraryManagement
	 * @param newParamList The new parameter list.
	 * @param descriptions The descriptions of the parameters stored in the newParamList parameter.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetParameters (const GDL::Parameters& newParamList, const std::vector<GS::UniString>& descriptions);

	/**
	 * @brief Merges new parameters to the object. This function will add new parameters and replace the existing ones.
	 * @ingroup LibraryManagement
	 * @param newParamList Parameter list with the new parameters.
	 * @param descriptions The descriptions of the parameters stored in the newParamList parameter.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> MergeParameters (const GDL::Parameters& newParamList, const std::vector<GS::UniString>& descriptions);

	/**
	 * @brief Sets the master script. This function will replace the existing master script. If it is empty, the script will NOT be deleted but set to empty.
	 * @ingroup LibraryManagement
	 * @param script A GDL script which will be set as the master script.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetMasterScript (const GS::UniString& script);

	/**
	 * @brief Sets the 2D script. This function will replace the existing 2D script. If it is empty, the script will NOT be deleted but set
	 * 		  to empty.
	 * @ingroup LibraryManagement
	 * @param script A GDL script which will be set as the 2D script.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> Set2DScript (const GS::UniString& script);

	/**
	 * @brief Sets the 3D script. This function will replace the existing 3D script. If it is empty, the script will NOT be deleted but set
	 * 		  to empty.
	 * @ingroup LibraryManagement
	 * @param script A GDL script which will be set as the 3D script.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> Set3DScript (const GS::UniString& script);

	/**
	 * @brief Sets the properties script. This function will replace the existing properties script. If it is empty, the script will NOT be deleted but set
	 * 		  to empty.
	 * @ingroup LibraryManagement
	 * @param script A GDL script which will be set as the properties script.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetPropertiesScript (const GS::UniString& script);

	/**
	 * @brief Sets the parameter script. This function will replace the existing parameter script. If it is empty, the script will NOT be deleted but set
	 * 		  to empty.
	 * @ingroup LibraryManagement
	 * @param script A GDL script which will be set as the parameter script.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetParameterScript (const GS::UniString& script);

	/**
	 * @brief Sets the interface script. This function will replace the existing interface script. If it is empty, the script will NOT be deleted but set
	 * 		  to empty.
	 * @ingroup LibraryManagement
	 * @param script A GDL script which will be set as the interface script.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetInterfaceScript (const GS::UniString& script);

	/**
	 * @brief Sets the interface as default.
	 * @ingroup LibraryManagement
	 * @param isDefault true if is default
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetUIDefault (bool isDefault);

	/**
	 * @brief Sets the interface uses hierarchical pages.
	 * @ingroup LibraryManagement
	 * @param hierarchicalPagesUsed true if yes
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetHierarchicalPagesUsed (bool hierarchicalPagesUsed);

	/**
	 * @brief Sets the forward migration script. This function will replace the existing forward migration script. If it is empty, the script will NOT be deleted but
	 * 		  set to empty.
	 * @ingroup LibraryManagement
	 * @param script A GDL script which will be set as the forward migration script.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetForwardMigrationScript (const GS::UniString& script);

	/**
	 * @brief Sets the backward migration script. This function will replace the existing backward migration script. If it is empty, the script will NOT be deleted
	 * 		  but set to empty.
	 * @ingroup LibraryManagement
	 * @param script A GDL script which will be set as the backward migration script.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetBackwardMigrationScript (const GS::UniString& script);

	/**
	 * @brief Sets a vector image as 2D symbol. This function will replace the existing 2D symbol. If it is empty, the symbol will NOT be deleted but set to empty.
	 * @ingroup LibraryManagement
	 * @param image A VectorImage object.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> Set2DVectorImage (const VectorImage& image);

	/**
	 * @brief Sets the preview picture.
	 * @ingroup LibraryManagement
	 * @param image A GX::ImageRef image. The most common image formats are supported.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetPreviewPicture (const GX::ImageRef& image);

	/**
	 * @brief Sets the pictures which are referred from th GDL scripts.
	 * @ingroup LibraryManagement
	 * @param images A vector of GX::ImageRef images. The most common image formats are supported.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetGDLPictures (const std::vector<GX::ImageRef>& images);

	/**
	 * @brief Sets a custom section.
	 * @ingroup LibraryManagement
	 * @param sectionTypeID A four-byte identifier of the custom section. Like 'sect'.
	 * @param index The index of the custom sections with similar type ID.
	 * @param data The GSMSectionData which contains the binary serialized data.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> SetCustomSection (uint32_t sectionTypeID, uint16_t index, const GSMSectionData& data);

	/**
	 * @brief Deletes the master script.
	 * @ingroup LibraryManagement
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> DeleteMasterScript ();

	/**
	 * @brief Deletes the 2D script.
	 * @ingroup LibraryManagement
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> Delete2DScript ();

	/**
	 * @brief Deletes the 3D script.
	 * @ingroup LibraryManagement
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> Delete3DScript ();

	/**
	 * @brief Deletes the properties script.
	 * @ingroup LibraryManagement
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> DeletePropertiesScript ();
	
	/**
	 * @brief Deletes the parameter script.
	 * @ingroup LibraryManagement
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> DeleteParameterScript ();

	/**
	 * @brief Deletes the interface script.
	 * @ingroup LibraryManagement
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> DeleteInterfaceScript ();
	
	/**
	 * @brief Deletes the forward migration script.
	 * @ingroup LibraryManagement
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> DeleteForwardMigrationScript ();

	/**
	 * @brief Deletes the backward migration script.
	 * @ingroup LibraryManagement
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> DeleteBackwardMigrationScript ();

	/**
	 * @brief Deletes the 2D Vector image.
	 * @ingroup LibraryManagement
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> Delete2DVectorImage ();

	/**
	 * @brief Deletes the preview picture.
	 * @ingroup LibraryManagement
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> DeletePreviewPicture ();
	
	/**
	 * @brief Deletes GDL pictures.
	 * @ingroup LibraryManagement
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> DeleteGDLPictures ();

	/**
	 * @brief Deletes a custom section.
	 * @ingroup LibraryManagement
	 * @param sectionID A four-byte identifier of the custom section. Like 'sect'.
	 * @param index The index of the custom sections with similar type ID.
	 * @return Returns Ok if succesful, otherwise Error.
	 */
	ACAPI::Result<void> DeleteCustomSection (uint32_t sectionID, uint16_t index = 0);

};

}	 // namespace v1

using namespace v1;

} // namespace Library
}	 // namespace ACAPI

#endif 
