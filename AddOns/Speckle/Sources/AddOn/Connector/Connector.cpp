#include "Connector.h"

std::unique_ptr<Connector> Connector::instance = nullptr;

Connector& Connector::GetInstance()
{
	if (instance == nullptr)
		instance = std::unique_ptr<Connector>(new Connector());

	return *instance;
}
