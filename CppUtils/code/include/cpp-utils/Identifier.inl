#pragma once
#include <type_traits>

namespace cpp
{
namespace utils
{
template<typename ValueT>
Identifier<ValueT>::Identifier(ValueT&& i_value)
	: m_value(std::move(i_value))
{
	// Nothing to do
}

template<typename ValueT>
Identifier<ValueT>::Identifier(const ValueT& i_value)
	: m_value(i_value)
{
	// Nothing to do
}

template<typename ValueT>
Identifier<ValueT>::Identifier(const Identifier<ValueT>& rhs)
	: m_value(rhs.m_value)
{
	// Nothing to do
}

template<typename ValueT>
Identifier<ValueT>::Identifier(Identifier<ValueT>&& rhs)
	: m_value(std::move(rhs.m_value))
{
	// Nothing to do
}

template<typename ValueT>
inline Identifier<ValueT>& Identifier<ValueT>::operator=(const Identifier<ValueT>& rhs) &
{
	if ( this != &rhs )
	{
		m_value = rhs.m_value;
	}
	return *this;
}

template<typename ValueT>
inline Identifier<ValueT>& Identifier<ValueT>::operator=(Identifier<ValueT>&& rhs) &
{
	if ( this != &rhs )
	{
		m_value = std::move(rhs.m_value);
	}
	return *this;
}

template<typename ValueT>
inline const ValueT& Identifier<ValueT>::GetValue() const&
{
	return m_value;
}

template<typename ValueT>
inline ValueT Identifier<ValueT>::GetValue() const&&
{
	return std::move(m_value);
}

// Comparison Operators follows:

template<typename ValueT>
inline bool operator==(const Identifier<ValueT>& lhs, const Identifier<ValueT>& rhs)
{
	return lhs.GetValue() == rhs.GetValue();
}

template<typename ValueT>
inline bool operator!=(const Identifier<ValueT>& lhs, const Identifier<ValueT>& rhs)
{
	return !( lhs == rhs );
}

template<typename ValueT, typename Derived>
InvalidableIdentifier<ValueT, Derived>::InvalidableIdentifier()
	: Identifier<ValueT>(Derived::GetInvalidValue())
{
	// Nothing to do
}

template<typename ValueT, typename Derived>
InvalidableIdentifier<ValueT, Derived>::InvalidableIdentifier(ValueT&& i_value)
	: Identifier(std::move(i_value))
{
	// Nothing to do
}

template<typename ValueT, typename Derived>
InvalidableIdentifier<ValueT, Derived>::InvalidableIdentifier(const ValueT& i_value)
	: Identifier<ValueT>(i_value)
{
	// Nothing to do
}

template<typename ValueT, typename Derived>
inline bool InvalidableIdentifier<ValueT, Derived>::IsValid() const
{
	return GetValue() != typename Derived::GetInvalidValue();
}

template<typename ValueT>
inline std::ostream& operator<<(std::ostream& o_stream, const Identifier<ValueT>& i_identifier)
{
	o_stream << i_identifier.GetValue();
	return o_stream;
}

template<typename ValueT>
inline std::istream& operator>>(std::istream& i_stream, Identifier<ValueT>& i_identifier)
{
	i_stream >> i_identifier.m_value;
	return i_stream;
}


template<typename ValueT>
inline bool utils::Identifier<ValueT>::LessCmp::operator()(const Identifier<ValueT>& lhs, const Identifier<ValueT>& rhs) const
{
	return lhs.GetValue() < rhs.GetValue();
}


template<typename ValueT>
inline std::size_t utils::Identifier<ValueT>::Hasher::operator()(const Identifier<ValueT>& rhs) const
{
	return std::hash<ValueT>{}( rhs.GetValue() );
}

} //namespace utils 
} //namespace cpp