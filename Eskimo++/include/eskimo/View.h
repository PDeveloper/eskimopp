#pragma once

#include <vector>

#include "EntityId.h"
#include "EntityManager.h"

#include "IComponentListener.h"
#include "EntityList.h"

namespace eskimo
{

	// template<typename... ComponentTypes>
	// class types {};

	class GenericView : public IComponentListener
	{
	public:
		enum class EntityValidationResult
		{
			ADD = 0,
			UPDATE,
			REMOVE,
			NONE
		};

		EntityManager& entity_manager;
		ComponentManager& component_manager;

		EntityList entities;

		BitFlag filter;

		/*
		template<typename... ComponentTypes>
		GenericView(EntityManager& entity_manager, types<ComponentTypes...> types)
		{
			const std::size_t n = sizeof...(ComponentTypes);
			m_connected_types.reserve(n);
			(connect<ComponentTypes>(), ...);

			for (const EntityId& entity : entity_manager.entities) validate(entity);
		}
		*/

		GenericView(EntityManager& entity_manager);
		virtual ~GenericView() override;

		EntityId& at(size_t index);
		Entity get(const EntityId& id);

		void on_component_add(const EntityId& entity) override;
		void on_component_update(const EntityId& entity) override;
		void on_component_remove(const EntityId& entity) override;

		EntityValidationResult validate(const EntityId& entity);

	private:
		/*
		std::vector<component_id_t> m_connected_types;
		template<typename TComponent>
		void connect()
		{
			component_manager.add_flag<TComponent>(filter);
			component_manager.connect<TComponent>(this);

			m_connected_types.emplace_back(component_manager.type<TComponent>());
		}
		*/

		bool add_valid_entity(const EntityId& entity);
		bool remove_invalid_entity(const EntityId& entity);

	};

	template<typename... ComponentTypes>
	class View : public GenericView
	{

	public:
		View(EntityManager& entity_manager, bool auto_connect = true) :
			GenericView(entity_manager),
			m_is_connected(false)
		{
			if (auto_connect)
				connect();
		}

		~View() override
		{
			disconnect();
		}

	private:
		bool m_is_connected;

		void connect()
		{
			if (m_is_connected) return;

			(component_manager.add_flag<ComponentTypes>(filter), ...);
			(component_manager.connect<ComponentTypes>(this), ...);

			for (const EntityId& entity : entity_manager.entities) validate(entity);

			m_is_connected = true;
		}

		void disconnect()
		{
			if (!m_is_connected) return;

			(component_manager.disconnect<ComponentTypes>(this), ...);
			m_is_connected = false;
		}

	};

}
