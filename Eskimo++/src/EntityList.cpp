#include "eskimo/EntityList.h"

namespace eskimo
{

	EntityList::EntityListIterator::EntityListIterator(EntityList& list, size_t index) :
		m_list(list),
		m_current(list.entities.size() - 1 - index)
	{

	}

	// Dereferencable.
	EntityList::EntityListIterator::reference EntityList::EntityListIterator::operator*() const
	{
		return m_list.entities[m_current];
	}

	// Pre- and post-incrementable.
	EntityList::EntityListIterator& EntityList::EntityListIterator::operator++()
	{
		--m_current;
		return *this;
	}
	EntityList::EntityListIterator EntityList::EntityListIterator::operator++(int)
	{
		EntityListIterator tmp = *this;
		--m_current;
		return tmp;
	}

	// Pre- and post-decrementable.
	EntityList::EntityListIterator& EntityList::EntityListIterator::operator--()
	{
		++m_current;
		return *this;
	}
	EntityList::EntityListIterator EntityList::EntityListIterator::operator--(int)
	{
		EntityListIterator tmp = *this;
		++m_current;
		return tmp;
	}

	// Equality / inequality.
	bool EntityList::EntityListIterator::operator==(const EntityListIterator& rhs)
	{
		return m_current == rhs.m_current;
	}
	bool EntityList::EntityListIterator::operator!=(const EntityListIterator& rhs)
	{
		return !(*this == rhs);
	}

	EntityList::EntityList() // :
		// contains(MAX_ENTITIES)
	{
	}

	const EntityId& EntityList::at(size_t index) const
	{
		return entities[index];
	}

	bool EntityList::has(const EntityId& entity) const
	{
		// return m_entity_contains.find(entity.id) != m_entity_contains.cend();
		return std::find(entities.begin(), entities.end(), entity) != entities.end(); // contains[entity.id]; // 
	}

	bool EntityList::add(const EntityId& entity)
	{
		if (!has(entity)) // !contains[entity.id]) // 
		{
			// contains[entity.id] = true;
			entities.emplace_back(entity);
			// m_entity_contains.emplace(entity.id);

			return true;
		}

		return false;
	}

	bool EntityList::remove(const EntityId& entity)
	{
		auto iterator = std::find(entities.begin(), entities.end(), entity);
		if (iterator != entities.end()) // contains[entity.id]) // 
		{
			// contains[entity.id] = false;
			entities.erase(iterator);
			// m_entity_contains.erase(m_entity_contains.find(entity.id));

			return true;
		}

		return false;
	}

	size_t EntityList::size() const
	{
		return entities.size();
	}

	void EntityList::clear()
	{
		//contains.clear();
		//contains.resize(MAX_ENTITIES);
		//std::fill(contains.begin(), contains.end(), false);

		entities.clear();
		// m_entity_contains.clear();
	}

	EntityList::iterator EntityList::begin()
	{
		return entities.begin();
	}

	EntityList::iterator EntityList::end()
	{
		return entities.end();
	}

	EntityList::const_iterator EntityList::cbegin() const
	{
		return entities.cbegin();
	}
	
	EntityList::const_iterator EntityList::cend() const
	{
		return entities.cend();
	}

}
