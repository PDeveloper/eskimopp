#pragma once

namespace eskimo
{
	using component_id_t = unsigned long long;

	template <typename TBase>
	class ComponentTypeId
	{
	public:
		template <typename T>
		static component_id_t get()
		{
			static const component_id_t id = m_next_type_id++;
			return id;
		}

		static component_id_t count()
		{
			return m_next_type_id;
		}
	private:
		static component_id_t m_next_type_id;
	};

	template <typename TBase>
	component_id_t ComponentTypeId<TBase>::m_next_type_id = 0;
}
