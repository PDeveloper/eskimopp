#pragma once

#include <vector>
#include <string>

#include "ComponentTypeId.h"
#include "IComponentTypeManager.h"

namespace eskimo
{

	class ComponentManager;

	class Component
	{
	public:
		Component(const component_id_t& type);

		Component(const component_id_t& type, void* component, IComponentTypeManager* component_type_manager);

		const component_id_t& type() const;
		const void* const component() const;
		const IComponentTypeManager* manager() const;

		template<typename TComponent>
		TComponent* component()
		{
			return static_cast<TComponent*>(m_component);
		}

		template<typename TComponent>
		const TComponent* component() const
		{
			return static_cast<TComponent*>(m_component);
		}

	private:
		component_id_t m_type;
		void* m_component;
		IComponentTypeManager* m_component_type_manager;

	};

}
