#pragma once

#include "EntityId.h"

#include <vector>
#include <unordered_set>

namespace eskimo
{
	struct EntityList
	{
		// std::vector<bool> contains;
		std::vector<EntityId> entities;

		class EntityListIterator
		{
		public:
			// Iterator traits, previously from std::iterator.
			using value_type = EntityId;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type * ;
			using reference = value_type & ;
			using iterator_category = std::bidirectional_iterator_tag;

			// Default constructible.
			//ViewIterator() = default;
			explicit EntityListIterator(EntityList& list, size_t index = 0);

			// Dereferencable.
			reference operator*() const;

			// Pre- and post-incrementable.
			EntityListIterator& operator++();
			EntityListIterator operator++(int);

			// Pre- and post-decrementable.
			EntityListIterator& operator--();
			EntityListIterator operator--(int);

			// Equality / inequality.
			bool operator==(const EntityListIterator& rhs);
			bool operator!=(const EntityListIterator& rhs);

		private:
			size_t m_current{ 0 };
			EntityList& m_list;

		};

		using iterator = std::vector<EntityId>::iterator;
		using const_iterator = std::vector<EntityId>::const_iterator;

		EntityList();

		const EntityId& at(size_t index) const;

		bool has(const EntityId& entity) const;
		bool add(const EntityId& entity);
		bool remove(const EntityId& entity);

		size_t size() const;

		void clear();

		iterator begin();
		iterator end();

		const_iterator cbegin() const;
		const_iterator cend() const;

	private:
		std::unordered_set<EntityId::id_t> m_entity_contains;

	};
}
