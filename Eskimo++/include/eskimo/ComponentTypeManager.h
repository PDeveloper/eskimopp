#pragma once

#include "EntityId.h"
#include "ComponentTypeId.h"

#include <unordered_map>

#include "IComponentTypeManager.h"
#include "ComponentManager.h"
#include "Component.h"

#include <concepts>

namespace eskimo
{

	template<typename TComponent>
	struct ComponentTypeManager : public IComponentTypeManager
	{

		ComponentTypeManager() :
			IComponentTypeManager(ComponentManager::ComponentIds::get<TComponent>())
		{
		}

		void set(ComponentManager& components, const EntityId& id, const Component& component) const override
		{
			components.set<TComponent>(id, *component.component<TComponent>());
		}

		void move(ComponentManager& components, const EntityId& id, Component& component) const override
		{
			components.set<TComponent>(id, std::move(*component.component<TComponent>()));
		}

		void copy(ComponentManager& components, const EntityId& from, const EntityId& to) const override
		{
			components.set<TComponent>(to, components.get<TComponent>(from));
		}

		void move(ComponentManager& components, const EntityId& from, const EntityId& to) const override
		{
			components.set<TComponent>(to, std::move(components.get<TComponent>(from)));
			components.remove<TComponent>(from);
		}

		Component get(const ComponentManager& components, const EntityId& id) const override
		{
			return Component(m_id, new TComponent(components.get<TComponent>(id)), new ComponentTypeManager<TComponent>());
		}

		Component take(ComponentManager& components, const EntityId& id) const override
		{
			TComponent copy = components.get<TComponent>(id);
			components.remove<TComponent>(id);
			return Component(m_id, new TComponent(copy), new ComponentTypeManager<TComponent>());
		}

	};

}
