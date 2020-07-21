#pragma once

#include "ComponentManager.h"
#include "ComponentSet.h"

namespace eskimo
{

	namespace utils
	{

		ComponentSet get_components(const ComponentManager& components, EntityId id);

		void apply(ComponentManager& components, EntityId id, const ComponentSet& set, bool overwrite = true);
		void move(ComponentManager& components, EntityId id, ComponentSet& set, bool overwrite = true);
		void apply(ComponentManager& components, EntityId from_id, EntityId to_id, bool overwrite = true, bool null_components = false);
		void move(ComponentManager& components, EntityId from_id, EntityId to_id, bool overwrite = true, bool null_components = false);

	}

}
