#pragma once

#include "ComponentTypeId.h"

#include <limits>

namespace eskimo
{

	struct BitFlag
	{

		using flag_t = unsigned long long;

		flag_t flag;

		BitFlag();
		BitFlag(const flag_t& flag);

		bool at(size_t bit) const;

		void set(size_t bit);
		void unset(size_t bit);

		void add(const BitFlag& other);
		void remove(const BitFlag& other);
		bool contains(const BitFlag& other) const;

		operator flag_t() const;

		const static BitFlag ALL;

	};
	
	BitFlag make_bitflag(size_t bit);

}
