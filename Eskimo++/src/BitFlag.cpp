#include "eskimo/BitFlag.h"

namespace eskimo
{

	BitFlag::BitFlag() : flag(0) {}
	BitFlag::BitFlag(const flag_t& flag) : flag(flag) {}

	bool BitFlag::at(size_t bit) const
	{
		return ((static_cast<flag_t>(1) << static_cast<flag_t>(bit)) & flag) > 0;
	}

	void BitFlag::set(size_t bit)
	{
		flag |= (static_cast<flag_t>(1) << static_cast<flag_t>(bit));
	}

	void BitFlag::unset(size_t bit)
	{
		flag &= ~(1 << static_cast<flag_t>(bit));
	}

	void BitFlag::add(const BitFlag& other)
	{
		flag |= other;
	}

	void BitFlag::remove(const BitFlag& other)
	{
		flag &= ~other;
	}

	bool BitFlag::contains(const BitFlag& other) const
	{
		return (flag & other) == other;
	}

	BitFlag::operator flag_t() const { return flag; }

	BitFlag make_bitflag(size_t bit)
	{
		return 1ULL << bit;
	}

	const BitFlag BitFlag::ALL = std::numeric_limits<flag_t>::max();

}