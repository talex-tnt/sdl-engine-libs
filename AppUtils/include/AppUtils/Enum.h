#pragma once
#include <type_traits>
#include <array>
#include <assert.h>

namespace app
{
namespace utils
{

class Enum
{
private:
	template<class ValueT, std::size_t N>
	static constexpr bool BoundaryCheck(const std::array<ValueT, N>& i_array, std::size_t i) noexcept
	{
		assert(i >= 0 && i < i_array.size()); // # fixme: use db_assert
		return ( i >= 0 && i < i_array.size() );
	}

public:
	template<class E>
	static constexpr typename std::underlying_type<E>::type GetValue(E e) noexcept
	{
		return static_cast< typename std::underlying_type<E>::type >( e );
	}

	template<class E, class ValueT, std::size_t N>
	static constexpr ValueT GetArrayValue(const std::array<ValueT, N>& i_array, E i_e) noexcept
	{
		const typename std::underlying_type<E>::type i = GetValue(i_e);
		if ( BoundaryCheck(i_array, i) )
		{
			return i_array[ i ];
		}
		return ValueT{};
	}

	template<class E, class ValueT, std::size_t N>
	static constexpr ValueT SetArrayValue(std::array<ValueT, N>& i_array, E i_e, ValueT i_v) noexcept
	{
		const typename std::underlying_type<E>::type i = GetValue(i_e);
		if ( BoundaryCheck(i_array, i) )
		{
			return i_array[ i ] = i_v;
		}
		return ValueT{};
	}
};

}
}