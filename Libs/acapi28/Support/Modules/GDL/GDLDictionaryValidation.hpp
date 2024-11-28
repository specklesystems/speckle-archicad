#ifndef GDL_GDLDICTIONARYVALIDATION_HPP
#define GDL_GDLDICTIONARYVALIDATION_HPP

#include "GDLExport.h" 
#include "GDLDictionaryPath.hpp"
#include "Owner.hpp"
#include "HashSet.hpp"
#include "UniString.hpp"
#include "HashTable.hpp"
#include "Ref.hpp"
#include "GDLDictionaryValueTypes.hpp"
#include "ReportDisplayTextBuilder.hpp"

namespace GDL
{

class Dictionary;
class IDictionaryValueVisitor;

class IDictionaryScheme;
typedef GS::Ref<IDictionaryScheme,GS::AtomicCounter> IDictionarySchemePtr;
class FieldLevelDictionaryScheme;
typedef GS::Ref<FieldLevelDictionaryScheme,GS::AtomicCounter> FieldLevelDictionarySchemePtr;
class DictionarySchemeAlternatives;
typedef GS::Ref<DictionarySchemeAlternatives,GS::AtomicCounter> DictionarySchemeAlternativesPtr;
class IDictionaryFieldValidator;
typedef GS::Ref<IDictionaryFieldValidator> IDictionaryFieldValidatorPtr;




class GDL_DLL_EXPORT IDictionarySchemeErrorCollector
{
public:
	IDictionarySchemeErrorCollector ();
	virtual ~IDictionarySchemeErrorCollector ();

	IDictionarySchemeErrorCollector (const IDictionarySchemeErrorCollector&) = delete;
	void operator= (const IDictionarySchemeErrorCollector&) = delete;

	virtual void EnterField (const FieldName&) = 0;
	virtual void EnterArrayItem (Int32 index) = 0;
	virtual void ExitArrayItem () = 0;
	virtual void ExitField () = 0;

	virtual void EnterSchemeAlternative (const GS::UniString& description) = 0;
	virtual void ExitSchemeAlternative () = 0;

	virtual void InternalSchemeError () = 0;
	virtual void AddMissingField (const FieldName&) = 0;
	virtual void AddUnknownField (const FieldName&) = 0;
	virtual void AddTypeMismatch () = 0;
	virtual void AddInvalidValue () = 0;
};


class GDL_DLL_EXPORT IDictionaryScheme
{
public:
	IDictionaryScheme ();
	virtual ~IDictionaryScheme ();

	IDictionaryScheme (const IDictionaryScheme&) = delete;
	void operator= (const IDictionaryScheme&) = delete;

	virtual void		DumpTechnicalInfo (ReportDisplayTextBuilder&) const = 0;
	virtual void		Validate (const GDL::Dictionary&, IDictionarySchemeErrorCollector&) const = 0;
	bool				IsValid (const GDL::Dictionary& dict);
	
protected:
	void				VisitDictionaryFields (const Dictionary& dict, IDictionaryValueVisitor& visitor) const;
};




class GDL_DLL_EXPORT IDictionaryFieldValidator
{
public:
	virtual ~IDictionaryFieldValidator ();

	IDictionaryFieldValidator (const IDictionaryFieldValidator&) = delete;
	void operator= (const IDictionaryFieldValidator&) = delete;


	virtual void MatchValue (IDictionarySchemeErrorCollector&, const Int32&) const = 0;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const double&) const = 0;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::UniString&) const = 0;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GDL::Dictionary&) const = 0;

	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<Int32>&) const = 0;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<double>&) const = 0;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<GS::UniString>&) const = 0;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<GDL::Dictionary>&) const = 0;

	virtual void DumpTechnicalInfo (ReportDisplayTextBuilder&) const = 0;

protected:
	IDictionaryFieldValidator ();
};




class GDL_DLL_EXPORT FieldLevelDictionaryScheme : public IDictionaryScheme
{
public:
	FieldLevelDictionaryScheme ();
	virtual ~FieldLevelDictionaryScheme ();

	FieldLevelDictionaryScheme*		MergePartialScheme (const FieldLevelDictionaryScheme& schemeToMerge);
	FieldLevelDictionaryScheme*		Expected (const FieldName&, IDictionaryFieldValidatorPtr);
	FieldLevelDictionaryScheme*		Optional (const FieldName&, IDictionaryFieldValidatorPtr);

	virtual void			DumpTechnicalInfo (ReportDisplayTextBuilder&) const override;
	virtual void			Validate (const GDL::Dictionary&, IDictionarySchemeErrorCollector&) const override;


private:
	struct FieldValidationInfo
	{
		bool							isOptional;
		IDictionaryFieldValidatorPtr	fieldValidator;
	};

	void					AddKnownField (const FieldName&, const FieldValidationInfo& entry);
	
	GS::HashTable<FieldName,FieldValidationInfo> knownFields;
};


class GDL_DLL_EXPORT DictionarySchemeAlternatives : public IDictionaryScheme
{
public:
	DictionarySchemeAlternatives ();
	virtual ~DictionarySchemeAlternatives ();

	DictionarySchemeAlternatives* AddPossibleScheme (const GS::UniString& description, const FieldLevelDictionarySchemePtr& scheme);

	virtual void			DumpTechnicalInfo (ReportDisplayTextBuilder&) const override;
	virtual void			Validate (const GDL::Dictionary&, IDictionarySchemeErrorCollector&) const override;

private:
	struct GDL_DLL_EXPORT AlternativeScheme
	{
		GS::UniString					description;
		FieldLevelDictionarySchemePtr	scheme;
	};
	GS::Array<AlternativeScheme> possibleSchemes;
};


class GDL_DLL_EXPORT AcceptAnythingDictionaryFieldValidator : public IDictionaryFieldValidator
{
public:
	virtual ~AcceptAnythingDictionaryFieldValidator ();

	virtual void MatchValue (IDictionarySchemeErrorCollector&, const Int32&) const override;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const double&) const override;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::UniString&) const override;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GDL::Dictionary&) const override;

	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<Int32>&) const override;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<double>&) const override;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<GS::UniString>&) const override;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<GDL::Dictionary>&) const override;

	virtual void DumpTechnicalInfo (ReportDisplayTextBuilder&) const override;
};


class GDL_DLL_EXPORT RefuseAllNotHandledDictionaryFieldValidator : public IDictionaryFieldValidator
{
public:
	virtual ~RefuseAllNotHandledDictionaryFieldValidator ();

	virtual void MatchValue (IDictionarySchemeErrorCollector&, const Int32&) const override;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const double&) const override;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::UniString&) const override;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GDL::Dictionary&) const override;

	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<Int32>&) const override;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<double>&) const override;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<GS::UniString>&) const override;
	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<GDL::Dictionary>&) const override;
};





class GDL_DLL_EXPORT SingleIntegerDictionaryFieldValidator : public RefuseAllNotHandledDictionaryFieldValidator
{
public:
	virtual ~SingleIntegerDictionaryFieldValidator ();

	virtual void MatchValue (IDictionarySchemeErrorCollector&, const Int32&) const override;
	virtual void DumpTechnicalInfo (ReportDisplayTextBuilder&) const override;
};

class GDL_DLL_EXPORT ArrayIntegerDictionaryFieldValidator :	public RefuseAllNotHandledDictionaryFieldValidator
{
public:
	virtual ~ArrayIntegerDictionaryFieldValidator ();

	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<Int32>&) const override;
	virtual void DumpTechnicalInfo (ReportDisplayTextBuilder&) const override;
};

class GDL_DLL_EXPORT SingleDoubleDictionaryFieldValidator : public RefuseAllNotHandledDictionaryFieldValidator
{
public:
	virtual ~SingleDoubleDictionaryFieldValidator ();

	virtual void MatchValue (IDictionarySchemeErrorCollector&, const double&) const override;
	virtual void DumpTechnicalInfo (ReportDisplayTextBuilder&) const override;
};

class GDL_DLL_EXPORT ArrayDoubleDictionaryFieldValidator :	public RefuseAllNotHandledDictionaryFieldValidator
{
public:
	virtual ~ArrayDoubleDictionaryFieldValidator ();

	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<double>&) const override;
	virtual void DumpTechnicalInfo (ReportDisplayTextBuilder&) const override;
};

class GDL_DLL_EXPORT SingleStringDictionaryFieldValidator : public RefuseAllNotHandledDictionaryFieldValidator
{
public:
	virtual ~SingleStringDictionaryFieldValidator ();

	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::UniString&) const override;
	virtual void DumpTechnicalInfo (ReportDisplayTextBuilder&) const override;
};


class GDL_DLL_EXPORT ArrayStringDictionaryFieldValidator :	public RefuseAllNotHandledDictionaryFieldValidator
{
public:
	virtual ~ArrayStringDictionaryFieldValidator ();

	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<GS::UniString>&) const override;
	virtual void DumpTechnicalInfo (ReportDisplayTextBuilder&) const override;
};


class GDL_DLL_EXPORT SingleEnumDictionaryFieldValidator : public RefuseAllNotHandledDictionaryFieldValidator
{
public:
	SingleEnumDictionaryFieldValidator (std::initializer_list<Int32> values);
	virtual ~SingleEnumDictionaryFieldValidator ();

	virtual void MatchValue (IDictionarySchemeErrorCollector&, const Int32&) const override;
	virtual void DumpTechnicalInfo (ReportDisplayTextBuilder&) const override;

private:
	GS::HashSet<Int32>	acceptedValues;
};


class GDL_DLL_EXPORT SingleDictDictionaryFieldValidator :	public RefuseAllNotHandledDictionaryFieldValidator
{
public:
	SingleDictDictionaryFieldValidator (const IDictionarySchemePtr& scheme);
	virtual ~SingleDictDictionaryFieldValidator ();

	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GDL::Dictionary&) const override;
	virtual void DumpTechnicalInfo (ReportDisplayTextBuilder&) const override;

private:
	IDictionarySchemePtr	scheme;
};


class GDL_DLL_EXPORT ArrayDictDictionaryFieldValidator :	public RefuseAllNotHandledDictionaryFieldValidator
{
public:
	ArrayDictDictionaryFieldValidator (const IDictionarySchemePtr& scheme);
	virtual ~ArrayDictDictionaryFieldValidator ();

	virtual void MatchValue (IDictionarySchemeErrorCollector&, const GS::Array<GDL::Dictionary>&) const override;
	virtual void DumpTechnicalInfo (ReportDisplayTextBuilder&) const override;

private:
	IDictionarySchemePtr	scheme;
};


class GDL_DLL_EXPORT SingleStringEnumDictionaryFieldValidator : public RefuseAllNotHandledDictionaryFieldValidator
{
public:
	SingleStringEnumDictionaryFieldValidator (const GS::HashSet<GS::UniString>& acceptedValues);
	virtual ~SingleStringEnumDictionaryFieldValidator ();

	virtual void MatchValue (IDictionarySchemeErrorCollector& errorCollector, const GS::UniString& value) const override;
	virtual void DumpTechnicalInfo (ReportDisplayTextBuilder& display) const override;
private:
	GS::HashSet<GS::UniString>	acceptedValues;
};


}

#endif
