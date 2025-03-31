#pragma once

#include "json.hpp"

class Node
{
private:
	bool isSpeckleType = false;

public:
	const nlohmann::json& data;
	const std::shared_ptr<Node> parent = nullptr;
	std::string id = "";
	std::string appId = "";
	std::string speckle_type = "";

	explicit Node(const nlohmann::json& j, const std::shared_ptr<Node> parent);
	bool IsObject() const;
	bool IsArray() const;
	bool IsSpeckleType() const;
	bool IsMesh() const;
	bool IsColorProxy() const;
	bool IsMaterialProxy() const;
	bool IsInstanceProxy() const;
	bool IsInstanceDefinitionProxy() const;
	bool IsCollection() const;
	bool IsGeometryObject() const;
	bool IsDataObject() const;
};
