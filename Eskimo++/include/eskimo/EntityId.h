#pragma once

#include <algorithm>

namespace eskimo
{
	struct EntityId
	{

		using id_t = size_t;

		id_t id;
		size_t generation;

		inline bool operator==(const EntityId& other) const
		{
			return other.id == this->id && other.generation == this->generation;
		}

		operator bool() const
		{
			return id >= 0;
		}

		operator size_t() const
		{
			return id;
		}

	};
}

namespace std
{

	template<>
	struct hash<eskimo::EntityId>
	{
		size_t operator()(const eskimo::EntityId& k) const
		{
			return hash<typename eskimo::EntityId::id_t>()(k.id);
		}
	};

}
