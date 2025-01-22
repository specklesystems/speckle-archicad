#include "ElementBody.h"

void to_json(nlohmann::json& j, const ElementBody& body)
{
	j = body.meshes;
}
