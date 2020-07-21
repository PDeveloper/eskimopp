#include "eskimo/Entity.h"

#include "eskimo/EntityManager.h"

namespace eskimo
{
	Entity::Entity(EntityManager* entity_manager, EntityId id) :
		entity_manager(entity_manager),
		component_manager(&entity_manager->component_manager),
		id(id)
	{

	}

	Entity::~Entity()
	{

	}

	void Entity::apply(const ComponentSet& components, bool overwrite)
	{
		component_manager->apply(this->id, components, overwrite);
	}

	void Entity::apply_to(Entity& entity, bool overwrite, bool null_components)
	{
		component_manager->apply(this->id, entity.id, overwrite, null_components);
	}

	void Entity::move_to(Entity& entity, bool overwrite, bool null_components)
	{
		component_manager->move(this->id, entity.id, overwrite, null_components);
	}

	void Entity::destroy()
	{
		entity_manager->destroy(this->id);
	}
}
