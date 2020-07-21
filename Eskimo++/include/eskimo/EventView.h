#pragma once

#include <vector>

#include "EntityId.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "View.h"

namespace eskimo
{

	template<typename... ComponentTypes>
	class EventView : public IComponentListener
	{
	private:
		View<ComponentTypes...> view;

	public:

		EntityManager& entity_manager;
		ComponentManager& component_manager;

		EntityList& entities;
		BitFlag& filter;

		EntityList added;
		EntityList updated;
		EntityList removed;

		EventView(EntityManager& entity_manager) :
			entity_manager(entity_manager),
			component_manager(entity_manager.component_manager),
			view(entity_manager, false),
			entities(view.entities),
			filter(view.filter)
		{
			(component_manager.add_flag<ComponentTypes>(filter), ...);
			(component_manager.connect<ComponentTypes>(this), ...);

			for (const EntityId& entity : entity_manager.entities) on_component_update(entity);
		}

		~EventView() override
		{
			(component_manager.disconnect<ComponentTypes>(this), ...);
		}

		EntityId& at(size_t index)
		{
			return view.at(index);
		}

		Entity get(const EntityId& id)
		{
			return view.get(id);
		}

		GenericView::EntityValidationResult validate(const EntityId& entity)
		{
			GenericView::EntityValidationResult result = view.validate(entity);

			switch (result)
			{
			case GenericView::EntityValidationResult::ADD:
				added.add(entity);
				break;
			case GenericView::EntityValidationResult::UPDATE:
				if (!added.has(entity))
					updated.add(entity);
				else
					result = GenericView::EntityValidationResult::NONE;
				break;
			case GenericView::EntityValidationResult::REMOVE:
				added.remove(entity);
				updated.remove(entity);

				removed.add(entity);
				break;
			default:
				break;
			}

			return result;
		}

		void clear()
		{
			added.clear();
			updated.clear();
			removed.clear();
		}

		void on_component_add(const EntityId& entity) override
		{

		}

		void on_component_update(const EntityId& entity) override
		{
			validate(entity);
		}

		void on_component_remove(const EntityId& entity) override
		{

		}

	};

}
