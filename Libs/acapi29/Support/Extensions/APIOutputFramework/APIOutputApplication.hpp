#ifndef __APIOUTPUTAPPLICATION_HPP__
#define __APIOUTPUTAPPLICATION_HPP__

#include "IAPIOutputManager.hpp"
#include "IAttributeProxy.hpp"
#include "DatabaseGraph.hpp"
#include "Array.hpp"
#include "GSAPIWrappers.hpp"
#include "IAPIOutputAdapter.hpp"

namespace GSAPI {

// predeclarations
template <typename APIType, typename FilterType, class Iterator>
class IAPIPseudoContainer;

class IAPIOutputAdapterFactory;
class IAPIAttributeAdapterFactory;
class IDatabaseSelector;


class APIOutputApplication {
private:
    APIOutputApplication& operator= (const APIOutputApplication& application);  // disabled

	template<typename ElemType, typename FilterType, typename ElemIteratorType>
    void CheckTemplateTypes (GSAPI::IAPIPseudoContainer<ElemType, FilterType, ElemIteratorType>*,
							 GSAPI::IAPIOutputAdapterFactory*,
							 GSAPI::IDatabaseSelector*,
							 GSAPI::IAttributeProxy*,
							 GSAPI::IAPIAttributeAdapterFactory*) {}

	template<typename ElemType, typename FilterType, typename ElemIteratorType>
    void CheckTemplateTypes (GSAPI::IAPIPseudoContainer<ElemType, FilterType, ElemIteratorType>*,
							 GSAPI::IAPIOutputAdapterFactory*,
							 GSAPI::IDatabaseSelector*,
							 GSAPI::IAPIAttributeAdapterFactory*) {}

	template<typename ElemType, typename FilterType, typename ElemIteratorType>
    void CheckTemplateTypes (GSAPI::IAPIPseudoContainer<ElemType, FilterType, ElemIteratorType>*,
							 GSAPI::IAPIOutputAdapterFactory*,
							 GSAPI::IDatabaseSelector*) {}

	template<typename ElemType, typename FilterType, typename ElemIteratorType>
    void CheckTemplateTypes (GSAPI::IAPIPseudoContainer<ElemType, FilterType, ElemIteratorType>*,
							 GSAPI::IAPIOutputAdapterFactory*,
							 GSAPI::IAttributeProxy*,
							 GSAPI::IAPIAttributeAdapterFactory*) {}

	template<typename ElemType, typename FilterType, typename ElemIteratorType>
    void CheckTemplateTypes (GSAPI::IAPIPseudoContainer<ElemType, FilterType, ElemIteratorType>*,
							 GSAPI::IAPIOutputAdapterFactory*) {}

	template<typename ElemType, typename FilterType, typename ElemIteratorType>
    void CheckTemplateTypes (GSAPI::IAPIPseudoContainer<ElemType, FilterType, ElemIteratorType>*,
							 GSAPI::IAPIOutputAdapterFactory*,
							 GSAPI::IAPIAttributeAdapterFactory*) {}

	template <typename ElemContainerType,
			  typename OutputFactoryType>
    GSErrCode OutputElementsImplementation (IAPIOutputManager&                  manager,
											const API_ElemFilter&               elemFilter,
											const GSAPI::IDatabaseSelector&     selector,
											const GSAPI::AttributeFilter&       attributeFilter,
											GSAPI::IAttributeProxy*             attributeProxy,
											GSAPI::IAPIAttributeAdapterFactory* attributeFactory,
											OutputUsedAttributesType            attributeOutputType,
											bool                                dumpDatabaseSettings);

public:
			APIOutputApplication () {}
	virtual ~APIOutputApplication ();

	template <typename ElemContainerType,
			  typename OutputFactoryType,
			  typename ElemSelectorType,
			  typename AttributeProxyType,
			  typename AttributeFactoryType>
    GSErrCode OutputElements (IAPIOutputManager&			manager,
							  const API_ElemFilter&			elemFilter,
							  const GSAPI::AttributeFilter& attributeFilter,
							  OutputUsedAttributesType		attributeOutputType  = DoNotOutput,
							  bool							dumpDatabaseSettings = true);

	template <typename ElemContainerType,
			  typename OutputFactoryType,
			  typename ElemSelectorType,
			  typename AttributeFactoryType>
    GSErrCode OutputElements (IAPIOutputManager&			manager,
							  const API_ElemFilter&			elemFilter,
							  const GSAPI::AttributeFilter& attributeFilter,
							  GSAPI::IAttributeProxy&		attributeProxy,
							  OutputUsedAttributesType		attributeOutputType  = DoNotOutput,
							  bool							dumpDatabaseSettings = true);

	template <typename ElemContainerType,
			  typename OutputFactoryType,
			  typename ElemSelectorType>
    GSErrCode OutputElements (IAPIOutputManager&			manager,
							  const API_ElemFilter&			elemFilter,
							  bool							dumpDatabaseSettings = true);

	template <typename ElemContainerType,
			  typename OutputFactoryType,
			  typename AttributeProxyType,
			  typename AttributeFactoryType>
    GSErrCode OutputElements (IAPIOutputManager&			  manager,
							  const API_ElemFilter&			  elemFilter,
							  const GSAPI::IDatabaseSelector& selector,
							  const GSAPI::AttributeFilter&   attributeFilter,
							  OutputUsedAttributesType		  attributeOutputType  = DoNotOutput,
							  bool							  dumpDatabaseSettings = true);

	template <typename ElemContainerType,
			  typename OutputFactoryType>
    GSErrCode OutputElements (IAPIOutputManager&			  manager,
							  const API_ElemFilter&			  elemFilter,
							  const GSAPI::IDatabaseSelector& selector,
							  bool							  dumpDatabaseSettings = true);

	template <typename ElemContainerType,
			  typename OutputFactoryType,
			  typename AttributeFactoryType>
    GSErrCode OutputElements (IAPIOutputManager&			  manager,
							  const API_ElemFilter&			  elemFilter,
							  const GSAPI::IDatabaseSelector& selector,
							  const GSAPI::AttributeFilter&   attributeFilter,
							  GSAPI::IAttributeProxy&		  attributeProxy,
							  OutputUsedAttributesType		  attributeOutputType  = DoNotOutput,
							  bool							  dumpDatabaseSettings = true);
};

}


template <typename ElemContainerType,
		  typename OutputFactoryType,
		  typename ElemSelectorType,
		  typename AttributeProxyType,
		  typename AttributeFactoryType>
GSErrCode GSAPI::APIOutputApplication::OutputElements (GSAPI::IAPIOutputManager&	   outputManager,
													   const API_ElemFilter&		   elemFilter,
													   const GSAPI::AttributeFilter&   attributeFilter,
													   GSAPI::OutputUsedAttributesType attributeOutputType  /*= DoNotOutput*/,
													   bool							   dumpDatabaseSettings /*= true*/)
{
    CheckTemplateTypes ((ElemContainerType*) nullptr,
						(OutputFactoryType*) nullptr,
						(ElemSelectorType*) nullptr,
						(AttributeProxyType*) nullptr,
						(AttributeFactoryType*) nullptr);

	ElemSelectorType selector;
	AttributeProxyType attributeProxy;
	AttributeFactoryType attributeFactory (attributeProxy);

	return OutputElementsImplementation<ElemContainerType, OutputFactoryType> (outputManager, elemFilter, selector, attributeFilter, &attributeProxy, &attributeFactory, attributeOutputType, dumpDatabaseSettings);
}


template <typename ElemContainerType,
		  typename OutputFactoryType,
		  typename ElemSelectorType,
		  typename AttributeFactoryType>
GSErrCode GSAPI::APIOutputApplication::OutputElements (GSAPI::IAPIOutputManager&	   outputManager,
													   const API_ElemFilter&		   elemFilter,
													   const GSAPI::AttributeFilter&   attributeFilter,
													   GSAPI::IAttributeProxy&		   attributeProxy,
													   GSAPI::OutputUsedAttributesType attributeOutputType  /*= DoNotOutput*/,
													   bool							   dumpDatabaseSettings /*= true*/)
{
    CheckTemplateTypes ((ElemContainerType*) nullptr,
						(OutputFactoryType*) nullptr,
						(ElemSelectorType*) nullptr,
						(AttributeFactoryType*) nullptr);

	ElemSelectorType selector;
	AttributeFactoryType attributeFactory (attributeProxy);

	return OutputElementsImplementation<ElemContainerType, OutputFactoryType> (outputManager, elemFilter, selector, attributeFilter, &attributeProxy, &attributeFactory, attributeOutputType, dumpDatabaseSettings);
}


template <typename ElemContainerType,
		  typename OutputFactoryType,
		  typename ElemSelectorType>
GSErrCode GSAPI::APIOutputApplication::OutputElements (GSAPI::IAPIOutputManager&	   outputManager,
													   const API_ElemFilter&		   elemFilter,
													   bool							   dumpDatabaseSettings /*= true*/)
{
    CheckTemplateTypes ((ElemContainerType*) nullptr,
						(OutputFactoryType*) nullptr,
						(ElemSelectorType*) nullptr);

	ElemSelectorType selector;
	GSAPI::AttributeFilter attributeFilter;
	BNZeroMemory (&attributeFilter, sizeof (attributeFilter));

	return OutputElementsImplementation<ElemContainerType, OutputFactoryType> (outputManager, elemFilter, selector, attributeFilter, nullptr, nullptr, GSAPI::DoNotOutput, dumpDatabaseSettings);
}


template <typename ElemContainerType,
		  typename OutputFactoryType,
		  typename AttributeProxyType,
		  typename AttributeFactoryType>
GSErrCode GSAPI::APIOutputApplication::OutputElements (GSAPI::IAPIOutputManager&	   outputManager,
													   const API_ElemFilter&		   elemFilter,
													   const GSAPI::IDatabaseSelector& selector,
													   const GSAPI::AttributeFilter&   attributeFilter,
													   GSAPI::OutputUsedAttributesType attributeOutputType  /*= DoNotOutput*/,
													   bool							   dumpDatabaseSettings /*= true*/)
{
    CheckTemplateTypes ((ElemContainerType*) nullptr,
						(OutputFactoryType*) nullptr,
						(AttributeProxyType*) nullptr,
						(AttributeFactoryType*) nullptr);

	AttributeProxyType attributeProxy;
	AttributeFactoryType attributeFactory (attributeProxy);

	return OutputElementsImplementation<ElemContainerType, OutputFactoryType> (outputManager, elemFilter, selector, attributeFilter, &attributeProxy, &attributeFactory, attributeOutputType, dumpDatabaseSettings);
}


template <typename ElemContainerType,
		  typename OutputFactoryType>
GSErrCode GSAPI::APIOutputApplication::OutputElements (GSAPI::IAPIOutputManager&	   outputManager,
													   const API_ElemFilter&		   elemFilter,
													   const GSAPI::IDatabaseSelector& selector,
													   bool							   dumpDatabaseSettings /*= true*/)
{
    CheckTemplateTypes ((ElemContainerType*) nullptr,
						(OutputFactoryType*) nullptr);

	GSAPI::AttributeFilter attributeFilter;
	BNZeroMemory (&attributeFilter, sizeof (attributeFilter));

	return OutputElementsImplementation<ElemContainerType, OutputFactoryType> (outputManager, elemFilter, selector, attributeFilter, nullptr, nullptr, GSAPI::DoNotOutput, dumpDatabaseSettings);
}


template <typename ElemContainerType,
		  typename OutputFactoryType,
		  typename AttributeFactoryType>
GSErrCode GSAPI::APIOutputApplication::OutputElements (GSAPI::IAPIOutputManager&	   outputManager,
													   const API_ElemFilter&		   elemFilter,
													   const GSAPI::IDatabaseSelector& selector,
													   const GSAPI::AttributeFilter&   attributeFilter,
													   GSAPI::IAttributeProxy&		   attributeProxy,
													   GSAPI::OutputUsedAttributesType attributeOutputType  /*= DoNotOutput*/,
													   bool							   dumpDatabaseSettings /*= true*/)
{
    CheckTemplateTypes ((ElemContainerType*) nullptr,
						(OutputFactoryType*) nullptr,
						(AttributeFactoryType*) nullptr);

	AttributeFactoryType attributeFactory (attributeProxy);

	return OutputElementsImplementation<ElemContainerType, OutputFactoryType> (outputManager, elemFilter, selector, attributeFilter, &attributeProxy, &attributeFactory, attributeOutputType, dumpDatabaseSettings);
}


template <typename ElemContainerType,
		  typename OutputFactoryType>
GSErrCode GSAPI::APIOutputApplication::OutputElementsImplementation (GSAPI::IAPIOutputManager&           outputManager,
																	 const API_ElemFilter&               elemFilter,
																	 const GSAPI::IDatabaseSelector&     selector,
																	 const GSAPI::AttributeFilter&       attributeFilter,
																	 GSAPI::IAttributeProxy*             attributeProxy,
																	 GSAPI::IAPIAttributeAdapterFactory* attributeFactory,
																	 GSAPI::OutputUsedAttributesType     attributeOutputType,
																	 bool                                dumpDatabaseSettings)
{
	if (DBERROR (((attributeProxy == nullptr) && (attributeFactory != nullptr)) ||
				 ((attributeProxy != nullptr) && (attributeFactory == nullptr))))
	{
		return APIERR_BADPARS;
	}

	bool markerDrawingEnabled = false;
	ACAPI_Drawing_IsMarkerDrawingEnabled (&markerDrawingEnabled);
	ACAPI_Drawing_ChangeMarkerDrawingEnabled (static_cast<Int32> (true));

	API_DatabaseInfo currentDatabase;
	GSErrCode dbError = ACAPI_Database_GetCurrentDatabase (&currentDatabase);
	if (dbError != NoError) {
		return dbError;
	}

	GS::Array<API_DatabaseInfo>           dbList    = DatabaseGraph::Instance ().SelectDatabases (selector);
	GS::Array<API_DatabaseInfo>::Iterator dbListIt  = dbList.Begin ();
	GS::Array<API_DatabaseInfo>::Iterator dbListEnd = dbList.End ();
    OutputFactoryType                     outputAdapterFactory (outputManager);

	if (attributeProxy != nullptr) {
		attributeProxy->SetFilter (attributeFilter);
	}

	for (; dbListIt != dbListEnd; ++dbListIt) {
		API_DatabaseInfo dbInfo = *dbListIt;
		dbError = ACAPI_Database_ChangeCurrentDatabase (&dbInfo);
		if (dbError == NoError) {
			if ((dumpDatabaseSettings) && ((dbInfo.typeID == APIWind_LayoutID) || (dbInfo.typeID == APIWind_MasterLayoutID))) {
				API_LayoutInfo layoutInfo;
				BNZeroMemory (&layoutInfo, sizeof (layoutInfo));

				dbError = ACAPI_Navigator_GetLayoutSets (&layoutInfo, &(dbInfo.databaseUnId));
				if (dbError == NoError) {
					try {
						GS::OChannel& oChannel = outputManager.GetOChannel (layoutInfo, dbInfo);
						GSAPI::IAPIOutputAdapterBase* adapter = outputAdapterFactory.GetTypeAdapter (layoutInfo, dbInfo, attributeProxy, attributeOutputType);
						*adapter >> oChannel;
						if (!outputAdapterFactory.GetManagedAdapters ()) {
							delete adapter;
						}

						if (layoutInfo.customData != nullptr) {
							delete layoutInfo.customData;
						}
					} catch (...) {
						// TODO: Report error
					}
				} else {
					// TODO: report error
				}
			}

			ElemContainerType dbContainer (attributeFactory);
			dbContainer.SetFilter (elemFilter);
			typename ElemContainerType::PseudoIterator elemIt = dbContainer.Begin ();
			const typename ElemContainerType::PseudoIterator elemEnd = dbContainer.End ();

			for (; elemIt != elemEnd; ++elemIt) {
				try {
					GS::OChannel& oChannel = outputManager.GetOChannel (elemIt->elem.element, elemIt->elem.elemType, elemIt->elem.guid, elemIt->databaseInfo);
					GSAPI::IAPIOutputAdapterBase* adapter = outputAdapterFactory.GetTypeAdapter (elemIt->elem.element, elemIt->databaseInfo, elemIt->elem.memo, attributeProxy, attributeOutputType);
					*adapter >> oChannel;
					if (!outputAdapterFactory.GetManagedAdapters ()) {
						delete adapter;
					}
				} catch (...) {
					// TODO: Report error
				}
			}

			if ((attributeProxy != nullptr) && ((attributeOutputType == GSAPI::AfterEachDatabase_Index) || (attributeOutputType == GSAPI::AfterEachDatabase_Name))) {
				GSAPI::IAttributeProxy::PseudoIterator       attributeIt  = attributeProxy->Begin (dbInfo.databaseUnId);
				const GSAPI::IAttributeProxy::PseudoIterator attributeEnd = attributeProxy->End (dbInfo.databaseUnId);

				for (; attributeIt != attributeEnd; ++attributeIt) {
					try {
						GS::OChannel& oChannel = outputManager.GetOChannel (attributeIt->elem, attributeIt->databaseInfo, attributeOutputType);
						GSAPI::IAPIOutputAdapterBase* adapter = outputAdapterFactory.GetTypeAdapter (attributeIt->elem, attributeIt->databaseInfo, attributeProxy, attributeOutputType);
						*adapter >> oChannel;
						if (!outputAdapterFactory.GetManagedAdapters ()) {
							delete adapter;
						}
					} catch (...) {
						// TODO: Report error
					}
				}
			}
		}
	}

	if ((attributeProxy != nullptr) && ((attributeOutputType == GSAPI::AfterOutputElements_Index) || (attributeOutputType == GSAPI::AfterOutputElements_Name))) {
		GSAPI::IAttributeProxy::PseudoIterator       attributeIt  = static_cast<IAPIPseudoContainer<GSAPI::IteratorElem <API_Attribute>, AttributeFilter, AttributeIterator>*> (attributeProxy)->Begin ();
		const GSAPI::IAttributeProxy::PseudoIterator attributeEnd = static_cast<IAPIPseudoContainer<GSAPI::IteratorElem <API_Attribute>, AttributeFilter, AttributeIterator>*> (attributeProxy)->End ();

		for (; attributeIt != attributeEnd; ++attributeIt) {
			try {
				GS::OChannel& oChannel = outputManager.GetOChannel (attributeIt->elem, attributeIt->databaseInfo, attributeOutputType);
				GSAPI::IAPIOutputAdapterBase* adapter = outputAdapterFactory.GetTypeAdapter (attributeIt->elem, attributeIt->databaseInfo, attributeProxy, attributeOutputType);
				*adapter >> oChannel;
				if (!outputAdapterFactory.GetManagedAdapters ()) {
					delete adapter;
				}
			} catch (...) {
				// TODO: Report error
			}
		}
	}

	dbError = ACAPI_Database_ChangeCurrentDatabase (&currentDatabase);
	if (dbError != NoError) {
		return dbError;
	}

	ACAPI_Drawing_ChangeMarkerDrawingEnabled (static_cast<GS::IntPtr> (markerDrawingEnabled));

	return NoError;
}


#endif //__APIOUTPUTAPPLICATION_HPP__
