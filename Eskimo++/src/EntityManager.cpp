#include "eskimo/EntityManager.h"

namespace eskimo
{

	EntityManager::EntityManager(ComponentManager& components) :
		component_manager(components),
		m_entity_id(0),
		m_free(),
		entities()
	{
		entities.reserve(MAX_ENTITIES);
	}


	EntityManager::~EntityManager()
	{
	}

	Entity EntityManager::create()
	{
		EntityId Id = m_free.size() > 0 ? get_free_id() : EntityId({ ++m_entity_id, 0 });
		entities.emplace_back(Id);

		component_manager.reset(Id);

		return Entity(this, entities.back());
	}

	Entity EntityManager::get(EntityId id)
	{
		return Entity(this, id);
	}

	bool EntityManager::destroy(EntityId id)
	{
		auto Iterator = std::find(entities.begin(), entities.end(), id);
		if (Iterator != entities.end())
		{
			m_free.push_back(id);
			entities.erase(Iterator);

			component_manager.reset(id);

			return true;
		}

		return false;
	}

	EntityId EntityManager::get_free_id()
	{
		EntityId Id = m_free.back();
		m_free.pop_back();
		Id.generation++;

		return Id;
	}
}
