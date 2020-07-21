#include "eskimo/View.h"

namespace eskimo
{

	GenericView::GenericView(EntityManager& entity_manager) :
		entity_manager(entity_manager),
		component_manager(entity_manager.component_manager),
		filter(0)
	{
	}

	GenericView::~GenericView()
	{
		/*
		for (component_id_t id : m_connected_types)
			component_manager.disconnect(this, id);

		m_connected_types.clear();
		*/
	}

	EntityId& GenericView::at(size_t index)
	{
		return entities.entities[index];
	}

	Entity GenericView::get(const EntityId& id)
	{
		return entity_manager.get(id);
	}

	void GenericView::on_component_add(const EntityId& entity)
	{
		// validate(entity);
	}

	void GenericView::on_component_update(const EntityId& entity)
	{
		validate(entity);
	}

	void GenericView::on_component_remove(const EntityId& entity)
	{
		// validate(entity);
	}

	GenericView::EntityValidationResult GenericView::validate(const EntityId& entity)
	{
		bool is_valid = component_manager.filter_contains(filter, entity);

		if (is_valid)
			if (add_valid_entity(entity))
				return EntityValidationResult::ADD;
			else
				return EntityValidationResult::UPDATE;
		else
			if (remove_invalid_entity(entity))
				return EntityValidationResult::REMOVE;

		return EntityValidationResult::NONE;
	}

	bool GenericView::add_valid_entity(const EntityId& entity)
	{
		return entities.add(entity);
	}

	bool GenericView::remove_invalid_entity(const EntityId& entity)
	{
		return entities.remove(entity);
	}

}