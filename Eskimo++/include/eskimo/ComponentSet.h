#pragma once

#include <vector>
#include <string>

#include "BitFlag.h"
#include "Component.h"
#include "ComponentTypeManager.h"

namespace eskimo
{

	class ComponentManager;

	ComponentSet get_components(const ComponentManager& components, EntityId id);

	class ComponentSet
	{
	public:
		ComponentSet();

		const BitFlag& flag() const;

		const std::vector<Component>& components() const;
		std::vector<Component>& components();

		template<typename TComponent, typename... Args>
		void set(Args&&... args)
		{
			component_id_t type = ComponentTypeId<ComponentManager>::get<TComponent>();
			TComponent* component = new TComponent(std::forward<Args>(args)...);
			ComponentTypeManager<TComponent>* manager = new ComponentTypeManager<TComponent>();

			m_components.emplace_back(type, component, manager);
			m_flag.set(static_cast<size_t>(type));
		}

		template<typename TComponent>
		TComponent* get()
		{
			component_id_t type = ComponentTypeId<ComponentManager>::get<TComponent>();
			for (Component& component : m_components)
			{
				if (component.type() == type)
					return component.component<TComponent>();
			}

			return nullptr;
		}

		template<typename TComponent>
		const TComponent* get() const
		{
			component_id_t type = ComponentTypeId<ComponentManager>::get<TComponent>();
			for (const Component& component : m_components)
			{
				if (component.type() == type)
					return component.component<TComponent>();
			}

			return nullptr;
		}

		template<typename TComponent>
		bool remove()
		{
			component_id_t type = ComponentTypeId<ComponentManager>::get<TComponent>();
			for (auto iterator = m_components.begin(); iterator != m_components.end(); iterator++)
			{
				Component& component = *iterator;
				if (component.type() == type)
				{
					component_id_t type = component.type();
					BitFlag component_flag = make_bitflag(static_cast<size_t>(type));
					m_flag.remove(component_flag);
					m_components.erase(iterator);

					return true;
				}
			}

			return false;
		}

		template<typename TComponent>
		bool has() const
		{
			component_id_t type = ComponentTypeId<ComponentManager>::get<TComponent>();
			BitFlag component_flag = make_bitflag(static_cast<size_t>(type));
			return m_flag.contains(component_flag);
		}

		void add(const Component& component);

	private:
		BitFlag m_flag;
		std::vector<Component> m_components;
	};

}
