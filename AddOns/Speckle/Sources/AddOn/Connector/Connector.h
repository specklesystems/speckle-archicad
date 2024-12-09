#pragma once

#define CONNECTOR Connector::GetInstance()

#include "IAccountDatabase.h"
#include "IModelCardDatabase.h"
#include "IHostToSpeckleConverter.h"
#include "ISpeckleToHostConverter.h"
#include "HostAppEvents.h"
#include "IDataStorage.h"

#include <memory>

class Connector
{
private:
	Connector() {};
	static std::unique_ptr<Connector> instance;

	std::unique_ptr<IAccountDatabase> accountDatabase;
	std::unique_ptr<IModelCardDatabase> modelCardDatabase;
	std::unique_ptr<IHostToSpeckleConverter> hostToSpeckleConverter;
	std::unique_ptr<ISpeckleToHostConverter> speckleToHostConverter;
	std::unique_ptr<HostAppEvents> hostAppEvents;

public:
	Connector(Connector& other) = delete;
	void operator=(const Connector&) = delete;
	static Connector& GetInstance();
	void InitConnector();

	IAccountDatabase& GetAccountDatabase();
	IModelCardDatabase& GetModelCardDatabase();
	IHostToSpeckleConverter& GetHostToSpeckleConverter();
	ISpeckleToHostConverter& GetSpeckleToHostConverter();
	HostAppEvents& GetHostAppEvents();
};
