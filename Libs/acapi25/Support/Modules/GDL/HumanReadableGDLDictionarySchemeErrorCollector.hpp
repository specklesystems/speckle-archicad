#ifndef _GDL_HUMANREADABLEGDLDICTIONARYSCHEMEERRORCOLLECTOR_HPP_
#define _GDL_HUMANREADABLEGDLDICTIONARYSCHEMEERRORCOLLECTOR_HPP_

#include "GDLDictionaryValidation.hpp"

namespace GDL
{

class GDL_DLL_EXPORT HumanReadableDictionarySchemeErrorCollector : public IDictionarySchemeErrorCollector
{
public:
	HumanReadableDictionarySchemeErrorCollector ();
	virtual ~HumanReadableDictionarySchemeErrorCollector ();

	virtual void EnterField (const FieldName&) override;
	virtual void EnterArrayItem (Int32 index) override;
	virtual void ExitArrayItem () override;
	virtual void ExitField () override;

	virtual void EnterSchemeAlternative (const GS::UniString& description) override;
	virtual void ExitSchemeAlternative () override;

	virtual void InternalSchemeError () override;
	virtual void AddMissingField (const FieldName&) override;
	virtual void AddUnknownField (const FieldName&) override;
	virtual void AddTypeMismatch () override;
	virtual void AddInvalidValue () override;

	bool			HasErrorMessage () const;
	GS::UniString	GetErrorMessage () const; 

protected:
	struct ValidationPathItem
	{
		GS::Optional<DictionaryPath::Item>	pathItem;
		GS::Optional<GS::UniString>			schemeDescription;

		ValidationPathItem ();
		ValidationPathItem (const GDL::FieldName&	fieldName);
	};

	virtual GS::UniString ComposeInternalSchemeErrorMessagePart (const GS::Array<ValidationPathItem>& path) const = 0;
	virtual GS::UniString ComposeMissingFieldMessagePart (const GS::Array<ValidationPathItem>& path, const GDL::FieldName& fieldName) const = 0;
	virtual GS::UniString ComposeUnknownFieldMessagePart (const GS::Array<ValidationPathItem>& path, const GDL::FieldName& fieldName) const = 0;
	virtual GS::UniString ComposeTypeMismatchMessagePart (const GS::Array<ValidationPathItem>& path) const = 0;
	virtual GS::UniString ComposeInvalidValueMessagePart (const GS::Array<ValidationPathItem>& path) const = 0;
	virtual GS::UniString ComposeMessageFromParts (const GS::Array<GS::UniString>& messageParts) const = 0;

private:
	void						AddErrorMessagePartIfFirstInAlternative (const GS::UniString& errorMessagePart);

	GS::Array<ValidationPathItem>			currentPath;
	GS::Array<bool>							alternativeHasError;
	GS::Array<GS::UniString>				messageParts;
};

}

#endif