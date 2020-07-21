#pragma once

#include "Entity.h"
#include "ComponentManager.h"

#include <vector>

namespace eskimo
{

	class EntityManager;

	class IEntityListener
	{

	public:
		virtual void on_entity_created(EntityManager& entities, EntityId Id) = 0;
		virtual void on_entity_destroyed(EntityManager& entities, EntityId Id) = 0;

	};

	class EntityManager
	{
	public:

		ComponentManager& component_manager;

		std::vector<EntityId> entities;

		EntityManager(ComponentManager& components);
		~EntityManager();

		Entity create();
		Entity get(EntityId id);
		bool destroy(EntityId id);

	private:
		size_t m_entity_id;

		std::vector<EntityId> m_free;

		EntityId get_free_id();

		std::vector<IEntityListener*> m_entity_listeners;

	};
}
