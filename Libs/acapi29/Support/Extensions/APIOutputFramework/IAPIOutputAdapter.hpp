#ifndef __APIOUTPUTADAPTER_HPP__
#define __APIOUTPUTADAPTER_HPP__

#include "GSAPIWrappers.hpp"
#include "Channel.hpp"


namespace GSAPI {

// predeclarations
class IAPIOutputManager;
class IAPIOutputAdapterFactory;
class IAttributeProxy;


/**
 * @interface
 * @stereotype adapter
 */
class IAPIOutputAdapterBase {
protected:
    IAPIOutputManager*				outputManager;
	IAPIOutputAdapterFactory*		outputAdapterFactory;
    const API_DatabaseInfo*			dbInfo;
	IAttributeProxy*				attributeProxy;
	GSAPI::OutputUsedAttributesType attributeOutputType;

public:
    IAPIOutputAdapterBase (IAPIOutputManager* manager, IAPIOutputAdapterFactory* factory) :
		outputManager (manager),
		outputAdapterFactory (factory),
		dbInfo (nullptr),
		attributeProxy (nullptr),
		attributeOutputType (GSAPI::DoNotOutput)
	{
		DBASSERT (outputManager != nullptr);
		DBASSERT (outputAdapterFactory != nullptr);
	}

	IAPIOutputAdapterBase (const IAPIOutputAdapterBase& adapter) :
		outputManager			(adapter.outputManager),
		outputAdapterFactory	(adapter.outputAdapterFactory),
		dbInfo					(adapter.dbInfo),
		attributeProxy			(adapter.attributeProxy),
		attributeOutputType		(adapter.attributeOutputType)
	{}

	virtual ~IAPIOutputAdapterBase ();


    IAPIOutputAdapterBase& operator= (const IAPIOutputAdapterBase& adapter)
	{
		outputManager			= adapter.outputManager;
		outputAdapterFactory	= adapter.outputAdapterFactory;
		dbInfo					= adapter.dbInfo;
		attributeProxy			= adapter.attributeProxy;
		attributeOutputType		= adapter.attributeOutputType;
		return (*this);
	}

	virtual void SetOutputManager			(IAPIOutputManager* manager)													{ if (DBVERIFY (manager != nullptr)) { outputManager = manager; } }
	virtual void SetOutputAdapterFactory	(IAPIOutputAdapterFactory* factory)												{ if (DBVERIFY (factory != nullptr)) { outputAdapterFactory = factory; } }
	virtual void SetDatabaseInfo			(const API_DatabaseInfo* apiDBInfo)												{ if (DBVERIFY (apiDBInfo != nullptr)) { dbInfo = apiDBInfo; } }
	virtual void SetAttributeProxy			(IAttributeProxy* iAttributeProxy = nullptr)										{ attributeProxy = iAttributeProxy; }
	virtual void SetAttributeOutputType		(GSAPI::OutputUsedAttributesType inAttributeOutputType = GSAPI::DoNotOutput)	{ attributeOutputType = inAttributeOutputType; }

	virtual void SetParameters				(const API_DatabaseInfo* apiDBInfo,
											 IAttributeProxy* iAttributeProxy = nullptr,
											 GSAPI::OutputUsedAttributesType inAttributeOutputType = GSAPI::DoNotOutput)
	{
		SetDatabaseInfo (apiDBInfo);
		SetAttributeProxy (iAttributeProxy);
		SetAttributeOutputType (inAttributeOutputType);
	}


	virtual void Output (GS::OChannel& oChannel) = 0;
    virtual void operator>> (GS::OChannel& oChannel) = 0;
};


template <typename APIType>
class IAPIOutputAdapter : public IAPIOutputAdapterBase {
protected:
	const APIType*		   element;
	const API_ElementMemo* memo;

public:
			IAPIOutputAdapter (IAPIOutputManager* manager, IAPIOutputAdapterFactory* factory) : IAPIOutputAdapterBase (manager, factory), element (nullptr), memo (nullptr) {}
			IAPIOutputAdapter (const IAPIOutputAdapter& adapter) : IAPIOutputAdapterBase (adapter), element (adapter.element), memo (adapter.memo) {}
	virtual ~IAPIOutputAdapter () { element = nullptr; memo = nullptr; }

    IAPIOutputAdapter& operator= (const IAPIOutputAdapter& adapter)
	{
		static_cast<IAPIOutputAdapterBase&> (*this) = adapter;
		element = adapter.element;
		memo = adapter.memo;
		return (*this);
	}

	virtual void SetElement     (const APIType* apiType)		  { if (DBVERIFY (apiType != nullptr)) { element = apiType; } }
	virtual void SetElementMemo (const API_ElementMemo* elemMemo) { memo = elemMemo; }

	virtual void SetParameters (const APIType*					apiType,
								const API_DatabaseInfo*			apiDBInfo,
								IAttributeProxy*				iAttributeProxy			= nullptr,
								GSAPI::OutputUsedAttributesType	inAttributeOutputType	= GSAPI::DoNotOutput,
								const API_ElementMemo*			elemMemo				= nullptr)
	{
		SetElement (apiType);
		SetDatabaseInfo (apiDBInfo);
		SetAttributeProxy (iAttributeProxy);
		SetAttributeOutputType (inAttributeOutputType);
		SetElementMemo (elemMemo);
	}
};

}	// namespace GSAPI

#endif //__APIOUTPUTADAPTER_HPP__
