#include "Node.h"
#include "Connector.h"
#include "ArchiCadApiException.h"
#include "SpeckleConversionException.h"
#include "UserCancelledException.h"
#include "GuidGenerator.h"

Node::Node(const nlohmann::json& j, const Node* parent) : parent(parent)
{
	if (j.is_object() && j.contains("speckle_type"))
	{
		isSpeckleType = true;	
		id = j.contains("id") ? j["id"].get<std::string>() : "";
		speckle_type = j["speckle_type"].get<std::string>();

		if (j.contains("applicationId") && j["applicationId"].is_string()) 
		{
			appId = j["applicationId"].get<std::string>();
		}
		else 
		{
			appId = "0";
		}
	}

	data = &j;
}

bool Node::IsObject() const
{
	return data->is_object();
}

bool Node::IsArray() const
{
	return data->is_array();
}

bool Node::IsSpeckleType() const
{
	return isSpeckleType;
}

bool Node::IsMesh() const
{
	return speckle_type == "Objects.Geometry.Mesh";
}

bool Node::IsColorProxy() const
{
	return speckle_type == "Objects.Other.ColorProxy";
}

bool Node::IsMaterialProxy() const
{
	return speckle_type == "Objects.Other.RenderMaterialProxy";
}

bool Node::IsInstanceProxy() const
{
	return speckle_type == "Speckle.Core.Models.Instances.InstanceProxy";
}

bool Node::IsInstanceDefinitionProxy() const
{
	return speckle_type == "Speckle.Core.Models.Instances.InstanceDefinitionProxy";
}

bool Node::IsCollection() const
{
	return speckle_type == "Speckle.Core.Models.Collections.Collection";
}