#pragma once

#include <vector>
#include <unordered_map>
#include <new>

#include "IComponentListener.h"
#include "ComponentTypeId.h"
#include "BitFlag.h"

#include "IComponentTypeManager.h"

namespace eskimo
{

	static const size_t MAX_COMPONENTS = sizeof(component_id_t) * 8;
	static const size_t MAX_ENTITIES = 1024 * 4;

	class ComponentSet;

	class ComponentManager
	{
		struct ComponentListenerSlot
		{
			BitFlag filter;
			IComponentListener* view;

			ComponentListenerSlot(BitFlag filter = BitFlag::ALL, IComponentListener* view = nullptr) :
				filter(filter),
				view(view)
			{}
		};

	public:
		using ComponentIds = ComponentTypeId<ComponentManager>;

		ComponentManager();
		~ComponentManager();

		template<typename TComponent, typename... Args>
		TComponent& set(EntityId id, Args&&... args)
		{
			container<TComponent>()[id.id] = TComponent(std::forward<Args>(args)...);

			if (is_active(id))
			{
				add_flag<TComponent>(m_active_flags[id.id]);
			}
			add_flag<TComponent>(m_entity_flags[id.id]);

			notify<TComponent>(id);

			return get<TComponent>(id);
		}

		template<typename TComponent>
		TComponent& get(EntityId id)
		{
			return container<TComponent>()[id.id];
		}

		// UNSAFE
		template<typename TComponent>
		const TComponent& get(EntityId id) const
		{
			return container<TComponent>()[id.id];
		}

		template<typename TComponent>
		bool has(EntityId id)
		{
			return has_bit<TComponent>(m_active_flags[id.id]);
		}

		template<typename TComponent>
		void remove(EntityId id)
		{
			remove_flag<TComponent>(m_active_flags[id.id]);
			remove_flag<TComponent>(m_entity_flags[id.id]);
			notify<TComponent>(id);
		}

		template<typename TComponent>
		TComponent* container()
		{
			component_id_t id = ComponentIds::get<TComponent>();
			if (m_components[id] == nullptr)
			{
				m_components[id] = new TComponent[MAX_ENTITIES]();
				m_component_size[id] = sizeof(TComponent);

				m_component_managers.emplace(id, new ComponentTypeManager<TComponent>());
			}

			return static_cast<TComponent*>(m_components[id]);
		}

		// UNSAFE
		template<typename TComponent>
		const TComponent* container() const
		{
			component_id_t id = ComponentIds::get<TComponent>();
			return static_cast<TComponent*>(m_components[id]);
		}

		template<typename TComponent>
		component_id_t type()
		{
			return ComponentIds::get<TComponent>();
		}

		template<typename TComponent>
		BitFlag create_bitflag()
		{
			return make_bitflag(static_cast<size_t>(type<TComponent>()));
		}

		template<typename TComponent>
		void add_flag(BitFlag& flag)
		{
			flag.add(create_bitflag<TComponent>());
		}

		template<typename TComponent>
		void remove_flag(BitFlag& flag)
		{
			flag.remove(create_bitflag<TComponent>());
		}

		template<typename TComponent>
		bool has_bit(const BitFlag& flag)
		{
			BitFlag componentFlag = create_bitflag<TComponent>();
			return flag.contains(componentFlag);
		}

		template<typename TComponent>
		void notify(EntityId id)
		{
			component_id_t type = ComponentIds::get<TComponent>();
			notify(id, type);
		}

		void notify(EntityId id);
		void notify(EntityId id, component_id_t type);

		template<typename TComponent>
		void connect(IComponentListener* view, BitFlag filter = BitFlag::ALL)
		{
			component_id_t Id = type<TComponent>();
			m_connections[Id].emplace_back(ComponentListenerSlot(filter, view));
		}

		template<typename TComponent>
		void disconnect(IComponentListener* view)
		{
			component_id_t id = type<TComponent>();
			disconnect(view, id);
		}

		void disconnect(IComponentListener* view, component_id_t id);

		void reset(EntityId id);
		BitFlag flags(EntityId id) const;
		bool is_active(EntityId id) const;

		void apply(EntityId id, const ComponentSet& set, bool overwrite = true);
		void move(EntityId id, ComponentSet& set, bool overwrite = true);
		void apply(EntityId from_id, EntityId to_id, bool overwrite = true, bool null_components = false);
		void move(EntityId from_id, EntityId to_id, bool overwrite = true, bool null_components = false);

		bool has_bit(const BitFlag& flag, const component_id_t& componentId) const;
		bool filter_contains(const BitFlag& filter, const EntityId& id) const;
		const IComponentTypeManager& get_manager(component_id_t id) const;

	private:
		std::vector<BitFlag> m_active_flags;
		std::vector<BitFlag> m_entity_flags;
		std::vector<bool> m_entity_active;

		void* m_components[MAX_COMPONENTS];
		size_t m_component_size[MAX_COMPONENTS];

		std::vector<ComponentListenerSlot> m_connections[MAX_COMPONENTS];

		std::unordered_map<component_id_t, IComponentTypeManager*> m_component_managers;

	};

}

#include "ComponentTypeManager.h"
