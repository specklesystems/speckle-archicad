#include "Connector.h"
#include "AccountDatabase.h"
#include "ModelCardDatabase.h"
#include "HostToSpeckleConverter.h"
#include "SpeckleToHostConverter.h"
#include "ArchiCadDataStorage.h"

std::unique_ptr<Connector> Connector::instance = nullptr;

Connector& Connector::GetInstance()
{
	if (instance == nullptr)
		instance = std::unique_ptr<Connector>(new Connector());

	return *instance;
}

void Connector::InitConnector()
{
	accountDatabase = std::make_unique<AccountDatabase>();
	auto dataStorage = std::make_unique<ArchiCadDataStorage>();
	modelCardDatabase = std::make_unique<ModelCardDatabase>(std::move(dataStorage));
	hostToSpeckleConverter = std::make_unique<HostToSpeckleConverter>();
	speckleToHostConverter = std::make_unique<SpeckleToHostConverter>();
	hostAppEvents = std::make_unique<HostAppEvents>();
}

IAccountDatabase& Connector::GetAccountDatabase() 
{
    if (!accountDatabase)
        throw std::runtime_error("AccountDatabase not initialized");
    
    return *accountDatabase;
}

IModelCardDatabase& Connector::GetModelCardDatabase() 
{
    if (!modelCardDatabase)
        throw std::runtime_error("ModelCardDatabase not initialized");
    
    return *modelCardDatabase;
}

IHostToSpeckleConverter& Connector::GetHostToSpeckleConverter() 
{
    if (!hostToSpeckleConverter) 
        throw std::runtime_error("HostToSpeckleConverter not initialized");

    return *hostToSpeckleConverter;
}

ISpeckleToHostConverter& Connector::GetSpeckleToHostConverter() 
{
    if (!speckleToHostConverter)
        throw std::runtime_error("SpeckleToHostConverter not initialized");

    return *speckleToHostConverter;
}

HostAppEvents& Connector::GetHostAppEvents() 
{
    if (!hostAppEvents)
        throw std::runtime_error("HostAppEvents not initialized");

    return *hostAppEvents;
}
