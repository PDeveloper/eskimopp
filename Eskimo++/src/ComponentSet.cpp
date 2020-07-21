#include "eskimo/ComponentSet.h"

namespace eskimo
{

	ComponentSet get_components(const ComponentManager& components, EntityId id)
	{
		ComponentSet set;
		BitFlag& entity_flags = components.flags(id);
		for (component_id_t component_id = 0; component_id < ComponentTypeId<ComponentManager>::count(); component_id++)
		{
			if (!components.has_bit(entity_flags, component_id))
				continue;

			const IComponentTypeManager& manager = components.get_manager(component_id);
			set.add(manager.get(components, id));
		}
		return set;
	}

	ComponentSet::ComponentSet() :
		m_flag(0),
		m_components()
	{
	}

	const eskimo::BitFlag& ComponentSet::flag() const
	{
		return m_flag;
	}

	const std::vector<Component>& ComponentSet::components() const
	{
		return m_components;
	}

	std::vector<Component>& ComponentSet::components()
	{
		return m_components;
	}

	void ComponentSet::add(const Component& component)
	{
		component_id_t type = component.type();
		m_components.emplace_back(component);
		m_flag.set(static_cast<size_t>(type));
	}

}
