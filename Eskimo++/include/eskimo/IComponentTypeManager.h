#pragma once

#include "EntityId.h"
#include "ComponentTypeId.h"
#include <unordered_map>

namespace eskimo
{

	class Component;
	class ComponentManager;

	template<typename TComponent>
	struct ComponentTypeManager;

	struct IComponentTypeManager
	{

		component_id_t m_id;

		IComponentTypeManager(component_id_t id);

		component_id_t id() const;
		virtual void set(ComponentManager& components, const EntityId& id, const Component& component) const = 0;
		virtual void move(ComponentManager& components, const EntityId& id, Component& component) const = 0;
		virtual void copy(ComponentManager& components, const EntityId& from, const EntityId& to) const = 0;
		virtual void move(ComponentManager& components, const EntityId& from, const EntityId& to) const = 0;

		virtual Component get(const ComponentManager& components, const EntityId& id) const = 0;
		virtual Component take(ComponentManager& components, const EntityId& id) const = 0;

	};

}
