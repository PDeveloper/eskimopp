#pragma once

#include "EntityId.h"

namespace eskimo
{

	class IComponentListener
	{

	public:
		virtual ~IComponentListener() = 0 {}

		virtual void on_component_add(const EntityId& entity) = 0;
		virtual void on_component_update(const EntityId& entity) = 0;
		virtual void on_component_remove(const EntityId& entity) = 0;

	};

}
