#include "BaseObjectSerializer.h"
#include "Connector.h"
#include "ArchiCadApiException.h"
#include "Base64GuidGenerator.h"
#include <functional> 
#include "picosha2.h"
#include "md5.h"

std::string BaseObjectSerializer::Serialize(RootObject root)
{
	auto idWithTraversedBase = TraverseBase(root);
	objects[idWithTraversedBase.first] = idWithTraversedBase.second;
	return idWithTraversedBase.first;
}

std::pair<std::string, nlohmann::json> BaseObjectSerializer::TraverseBase(const nlohmann::json& base)
{
	auto lineageId = Base64GuidGenerator::NewGuid();
	lineage.push_back(lineageId);
	bool isDetached = false;

	if (!detachLineage.empty())
	{
		isDetached = detachLineage.top();
		detachLineage.pop();
	}

	auto traversedBase = nlohmann::json::object();
	if (!base.contains("speckle_type") || !base["speckle_type"].is_string())
	{
		throw "arrgh";
	}
	traversedBase["speckle_type"] = base["speckle_type"];
	TraverseBaseProps(base, traversedBase);

	auto closure = nlohmann::json::object();
	auto parent = lineage.back();
	lineage.pop_back();

	auto it = familyTree.find(parent);
	if (it == familyTree.end())
	{
		// Initialize if parent is not found
		familyTree[parent] = nlohmann::json::object();
	}
	else
	{
		// Access the existing parent's items
		for (const auto& [ref, depth] : it->second.items())
		{
			closure[ref] = depth - detachLineage.size();
		}
	}

	auto dumped = traversedBase.dump();

	//std::string id = picosha2::hash256_hex_string(dumped);
	std::string id = MD5::hash(dumped);

	traversedBase["id"] = id;
	if (!closure.empty())
	{
		traversedBase["__closure"] = closure;
	}

	if (isDetached)
	{
		objects[id] = traversedBase;
	}

	return {id, traversedBase};
}

void BaseObjectSerializer::TraverseBaseProps(const nlohmann::json& base, nlohmann::json& traversedBase)
{
	for (const auto& [prop, value] : base.items()) 
	{
		if (value == nullptr || prop == "id")
			continue;

		if (!(value.is_object() || value.is_array()))
		{
			traversedBase[prop] = value;
			continue;
		}

		bool isDetachedProp = (prop[0] == '@');

		// TODO: revisit dynamically detaching

		auto child = TraverseValue(value, isDetachedProp);

		if (value.is_object() && value.contains("speckle_type") && isDetachedProp)
		{
			traversedBase[prop] = DetachHelper(child["id"]);
		}
		else
		{
			traversedBase[prop] = child;
		}
	}
}

nlohmann::json BaseObjectSerializer::TraverseValue(const nlohmann::json& value, bool isDetach)
{
	if (!(value.is_object() || value.is_array()))
		return value;

	if (value.is_array())
	{
		if (!isDetach)
		{
			auto values = nlohmann::json::array();
			for (const auto& val : value)
			{
				values.push_back(TraverseValue(val, false));
			}
			return values;
		}

		auto detachedList = nlohmann::json::array();
		for (const auto& val : value)
		{
			if (val.is_object() && val.contains("speckle_type") && val["speckle_type"].is_string())
			{
				detachLineage.push(isDetach);
				auto idWithTraversedBase = TraverseBase(val);
				detachedList.push_back(DetachHelper(idWithTraversedBase.first));
			}
			else
			{
				detachedList.push_back(TraverseValue(val, isDetach));
			}
		}
		return detachedList;
	}

	// TODO object references need to be handled when we have object tracking and send caching

	if (value.is_object() && !value.contains("speckle_type"))
		return value;

	if (value.is_object() && value.contains("speckle_type"))
	{
		detachLineage.push(isDetach);
		return TraverseBase(value).second;
	}

	// TODO throw later Unsupported type (it should not happen)
	

	return {};
}

nlohmann::json BaseObjectSerializer::DetachHelper(const std::string& referenceId)
{
	for (const auto& parent : lineage)
	{
		if (familyTree.find(parent) == familyTree.end())
		{
			familyTree[parent] = nlohmann::json::object();
		}

		auto& table = familyTree[parent];
		bool isRefExist = table.contains(referenceId);
		if (!isRefExist || (table[referenceId].is_number() && table[referenceId] > detachLineage.size()))
		{
			table[referenceId] = detachLineage.size();
		}
	}

	nlohmann::json reference;
	reference["referencedId"] = referenceId;
	reference["speckle_type"] = "reference";
	return reference;
}

std::vector<nlohmann::json> BaseObjectSerializer::GetObjects()
{
	std::vector<nlohmann::json> objectList;

	for (const auto& o : objects)
		objectList.push_back(o.second);

	return objectList;
}

std::vector<std::string> BaseObjectSerializer::BatchObjects()
{
	int maxSize = 1024 * 1024 * 100;
	std::vector<std::string> batches; 

	int batchSize = 0;
	std::string batch = "[";

	for (const auto& [id, obj] : objects)
	{
		auto objectString = obj.dump();
		auto stringSize = static_cast<int>(objectString.size());
		if ((batchSize + stringSize) < maxSize)
		{
			batch += objectString + ",";
			batchSize += stringSize;
		}
		else
		{
			batch.pop_back();
			batch += "]";
			batches.push_back(batch);
			batchSize = stringSize;
			batch = "[" + objectString;
		}
	}

	batch.pop_back();
	batch += "]";
	batches.push_back(batch);

	return batches;
}
