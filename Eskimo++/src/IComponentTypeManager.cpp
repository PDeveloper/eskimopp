#include "eskimo/IComponentTypeManager.h"

namespace eskimo
{

	IComponentTypeManager::IComponentTypeManager(component_id_t id) :
		m_id(id)
	{

	}

	component_id_t IComponentTypeManager::id() const
	{
		return m_id;
	}

}
