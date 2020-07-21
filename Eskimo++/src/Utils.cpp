#include "eskimo/Utils.h"

namespace eskimo
{

	namespace utils
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


		void apply(ComponentManager& components, EntityId id, const ComponentSet& set, bool overwrite)
		{
			const BitFlag& bitflag = components.flags(id);
			for (const Component& component : set.components())
			{
				if (!overwrite && components.has_bit(bitflag, component.type()))
					continue;

				const IComponentTypeManager& manager = *component.manager();
				manager.set(components, id, component);
			}
		}

		void move(ComponentManager& components, EntityId id, ComponentSet& set, bool overwrite)
		{
			const BitFlag& bitflag = components.flags(id);
			for (Component& component : set.components())
			{
				if (!overwrite && components.has_bit(bitflag, component.type()))
					continue;

				const IComponentTypeManager& manager = *component.manager();
				manager.move(components, id, component);
			}
		}

		void apply(ComponentManager& components, EntityId from_id, EntityId to_id, bool overwrite, bool null_components)
		{
			BitFlag& from_flags = components.flags(from_id);
			BitFlag& to_flags = components.flags(to_id);

			for (component_id_t component_id = 0; component_id < ComponentTypeId<ComponentManager>::count(); component_id++)
			{
				if (!null_components && !components.has_bit(from_flags, component_id) || !overwrite && components.has_bit(to_flags, component_id))
					continue;

				const IComponentTypeManager& manager = components.get_manager(component_id);
				manager.copy(components, from_id, to_id);
			}
		}

		void move(ComponentManager& components, EntityId from_id, EntityId to_id, bool overwrite, bool null_components)
		{
			BitFlag& from_flags = components.flags(from_id);
			BitFlag& to_flags = components.flags(to_id);

			for (component_id_t component_id = 0; component_id < ComponentTypeId<ComponentManager>::count(); component_id++)
			{
				if (!null_components && !components.has_bit(from_flags, component_id) || !overwrite && components.has_bit(to_flags, component_id))
					continue;

				const IComponentTypeManager& manager = components.get_manager(component_id);
				manager.move(components, from_id, to_id);
			}
		}

	}

}
