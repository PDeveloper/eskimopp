#include "eskimo/ComponentManager.h"

#include "eskimo/ComponentSet.h"

namespace eskimo
{

	ComponentManager::ComponentManager() :
		m_components(),
		m_component_size(),
		m_connections(),
		m_active_flags(MAX_ENTITIES + 1),
		m_entity_flags(MAX_ENTITIES + 1),
		m_entity_active(MAX_ENTITIES + 1)
	{
	}

	ComponentManager::~ComponentManager()
	{
	}

	void ComponentManager::disconnect(IComponentListener* view, component_id_t id)
	{
		auto iterator = std::find_if(m_connections[id].begin(), m_connections[id].end(),
			[&view](const ComponentListenerSlot& listener) {
				return listener.view == view; }
		);
		if (iterator != m_connections[id].end())
			m_connections[id].erase(iterator);
	}

	void ComponentManager::reset(EntityId id)
	{
		m_entity_flags[id.id] = 0;
		m_active_flags[id.id] = 0;
		m_entity_active[id.id] = true;

		notify(id);
	}

	BitFlag ComponentManager::flags(EntityId id) const
	{
		return m_active_flags.at(id);
	}

	bool ComponentManager::is_active(EntityId id) const
	{
		return m_entity_active.at(id.id);
	}

	void ComponentManager::apply(EntityId id, const ComponentSet& set, bool overwrite)
	{
		const BitFlag& bitflag = flags(id);
		for (const Component& component : set.components())
		{
			if (!overwrite && has_bit(bitflag, component.type()))
				continue;
	
			const IComponentTypeManager& manager = *component.manager();
			manager.set(*this, id, component);
		}
	}
	
	void ComponentManager::move(EntityId id, ComponentSet& set, bool overwrite)
	{
		const BitFlag& bitflag = flags(id);
		for (Component& component : set.components())
		{
			if (!overwrite && has_bit(bitflag, component.type()))
				continue;
	
			const IComponentTypeManager& manager = *component.manager();
			manager.move(*this, id, component);
		}
	}

	void ComponentManager::apply(EntityId from_id, EntityId to_id, bool overwrite, bool null_components)
	{
		BitFlag& from_flags = flags(from_id);
		BitFlag& to_flags = flags(to_id);

		for (component_id_t component_id = 0; component_id < ComponentIds::count(); component_id++)
		{
			if (!null_components && !has_bit(from_flags, component_id) || !overwrite && has_bit(to_flags, component_id))
				continue;

			const IComponentTypeManager& manager = get_manager(component_id);
			manager.copy(*this, from_id, to_id);
		}
	}

	void ComponentManager::move(EntityId from_id, EntityId to_id, bool overwrite, bool null_components)
	{
		BitFlag& from_flags = flags(from_id);
		BitFlag& to_flags = flags(to_id);

		for (component_id_t component_id = 0; component_id < ComponentIds::count(); component_id++)
		{
			if (!null_components && !has_bit(from_flags, component_id) || !overwrite && has_bit(to_flags, component_id))
				continue;

			const IComponentTypeManager& manager = get_manager(component_id);
			manager.move(*this, from_id, to_id);
		}
	}

	void ComponentManager::notify(EntityId id)
	{
		// Notify all component listeners
		for (std::vector<ComponentListenerSlot>& slots : m_connections)
		{
			for (ComponentListenerSlot& slot : slots)
			{
				slot.view->on_component_update(id);
			}
		}
	}

	void ComponentManager::notify(EntityId id, component_id_t type)
	{
		// BitFlag entity_flags(flags(id));
		for (ComponentListenerSlot& slot : m_connections[type])
		{
			// if (!entity_flags.contains(slot.filter)) continue;
			slot.view->on_component_update(id);
		}
	}

	bool ComponentManager::has_bit(const BitFlag& flag, const component_id_t& componentId) const
	{
		return flag.contains(make_bitflag(static_cast<size_t>(componentId)));
	}

	bool ComponentManager::filter_contains(const BitFlag& filter, const EntityId& id) const
	{
		return flags(id).contains(filter);
	}

	const IComponentTypeManager& ComponentManager::get_manager(component_id_t id) const
	{
		return *m_component_managers.at(id);
	}

}
