#pragma once

#include "EntityId.h"
#include "ComponentManager.h"

namespace eskimo
{
	class EntityManager;

	class Entity
	{

	public:

		EntityManager* entity_manager;
		ComponentManager* component_manager;

		EntityId id;

		Entity(EntityManager* entity_manager, EntityId id);
		~Entity();

		inline bool operator==(const Entity& other) const
		{
			return other.id == this->id;
		}

		operator bool() const
		{
			return this->id.id;
		}

		template<typename TComponent, typename... Args>
		TComponent& set(Args&&... args)
		{
			return component_manager->set<TComponent>(this->id, std::forward<Args>(args)...);
		}

		template<typename TComponent>
		TComponent& get()
		{
			return component_manager->get<TComponent>(this->id);
		}

		template<typename TComponent>
		bool has()
		{
			return component_manager->has<TComponent>(this->id);
		}

		template<typename TComponent>
		void remove()
		{
			component_manager->remove<TComponent>(this->id);
		}

		void apply(const ComponentSet& components, bool overwrite = true);
		void apply_to(Entity& entity, bool overwrite = true, bool null_components = false);
		void move_to(Entity& entity, bool overwrite = true, bool null_components = false);

		void destroy();

	};
}
