#include "eskimo/Component.h"

namespace eskimo
{
	Component::Component(const eskimo::component_id_t& type) :
		m_type(type),
		m_component(nullptr),
		m_component_type_manager(nullptr)
	{}
	Component::Component(const component_id_t& type, void* component, IComponentTypeManager* component_type_manager) :
		m_type(type),
		m_component(component),
		m_component_type_manager(component_type_manager)
	{}

	const eskimo::component_id_t& Component::type() const
	{
		return m_type;
	}

	const void* const Component::component() const
	{
		return m_component;
	}

	const IComponentTypeManager* Component::manager() const
	{
		return m_component_type_manager;
	}

}
