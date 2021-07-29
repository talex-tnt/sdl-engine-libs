#pragma once
#include "Math/Vector.h"
#include <cmath>
namespace Math
{

namespace details
{
template <class T>
struct abs {	//operator needed by std::transform
	static_assert(
		std::numeric_limits<T>::is_signed,
		"Math::details::abs<T>: Please provide only integral or floating point types" );
	T operator()(T const& t) { return std::abs(t); }
};
} //namespace details

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline Math::VectorBase<V, T, Dim>::VectorBase() : m_data { 0 }
{
	// Nothing to do
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline Math::VectorBase<V, T, Dim>::VectorBase(value_type v)
{
	std::fill(begin(), end(), v);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline Math::VectorBase<V, T, Dim>::VectorBase(const VectorBaseT& rhs)
{
	std::copy(rhs.m_data, rhs.m_data + Dim, this->m_data);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline Math::VectorBase<V, T, Dim>::VectorBase(const T(&rhs)[ Dim ])
{
	std::copy(rhs, rhs + Dim, this->m_data);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::operator=(const VectorBaseT& rhs)
{
	std::copy(rhs.m_data, rhs.m_data + Dim, this->m_data);
	return static_cast< VectorT& >( *this );
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::operator=(VectorBaseT&& rhs)
{
	std::swap(this->m_data, rhs.m_data);
	return static_cast< VectorT& >( *this );
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline T& Math::VectorBase<V, T, Dim>::operator[](std::size_t idx)
{
	return this->m_data[ idx ];
}
template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline const T& Math::VectorBase<V, T, Dim>::operator[](std::size_t idx) const
{
	return this->m_data[ idx ];
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline const T& Math::VectorBase<V, T, Dim>::x() const
{
	return this->m_data[ 0u ];
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::const_reference Math::VectorBase<V, T, Dim>::back() const
{
	return this->m_data[Dim - 1u];
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::reference Math::VectorBase<V, T, Dim>::back()
{
	return this->m_data[Dim - 1u];
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::iterator Math::VectorBase<V, T, Dim>::begin()
{
	return this->m_data;
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::riterator Math::VectorBase<V, T, Dim>::rbegin()
{
	return riterator(end());
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::const_iterator Math::VectorBase<V, T, Dim>::begin() const
{
	return this->m_data;
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::const_riterator Math::VectorBase<V, T, Dim>::rbegin() const
{
	return const_riterator(end());
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::iterator Math::VectorBase<V, T, Dim>::end()
{
	return this->m_data + Dim;
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::riterator Math::VectorBase<V, T, Dim>::rend()
{
	return riterator(begin());
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::const_iterator Math::VectorBase<V, T, Dim>::end() const
{
	return this->m_data + Dim;
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::const_riterator Math::VectorBase<V, T, Dim>::rend() const
{
	return const_riterator(begin());
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::const_iterator Math::VectorBase<V, T, Dim>::cbegin() const
{
	return begin();
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::const_riterator Math::VectorBase<V, T, Dim>::crbegin() const
{
	return rbegin();
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::const_iterator Math::VectorBase<V, T, Dim>::cend() const
{
	return end();
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::const_riterator Math::VectorBase<V, T, Dim>::crend() const
{
	return rend();
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline T Math::VectorBase<V, T, Dim>::dot(const VectorT& rhs) const
{
	T dot = 0;
	auto this_it = cbegin();
	auto rhs_it = rhs.cbegin();
	for ( ; this_it != cend(); ++this_it, ++rhs_it )
	{
		dot += ( *this_it ) * ( *rhs_it );
	}
	return dot;
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::increment(const VectorBaseT& rhs)
{
	return increment(rhs.m_data);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::increment(const T(&rhs)[ Dim ])
{
	return transform<PlusOp>(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::increment(const T& v)
{
	return transform<PlusOp>(v);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::decrement(const VectorBaseT& rhs)
{
	return decrement(rhs.m_data);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::decrement(const T(&rhs)[ Dim ])
{
	return transform<MinusOp>(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::decrement(const T& v)
{
	return transform<MinusOp>(v);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::multiply(const VectorBaseT& rhs)
{
	return multiply(rhs.m_data);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::multiply(const T(&rhs)[ Dim ])
{
	return transform<MultiplyOp>(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::divide(const VectorBaseT& rhs)
{
	return divide(rhs.m_data);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::divide(const T(&rhs)[ Dim ])
{
	return transform<DivideOp>(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::divide(const T& v)
{
	return transform<DivideOp>(v);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::multiply(const T& v)
{
	return transform<MultiplyOp>(v);
}

//template <template<class, std::size_t> class V, class T, std::size_t Dim>
//inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::negate()
//{
//	std::transform(cbegin(), cend(), begin(), NegateOp());
//	return static_cast< VectorT& >( *this );
//}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline bool Math::VectorBase<V, T, Dim>::less_equal(const VectorBaseT& rhs) const
{
	return apply_operator<std::less_equal<T>>(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline bool Math::VectorBase<V, T, Dim>::less(const VectorBaseT& rhs) const
{
	return apply_operator<std::less<T>>(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline bool Math::VectorBase<V, T, Dim>::equal(const VectorBaseT& rhs) const
{
	bool result = std::equal(cbegin(), cend(), rhs.cbegin());
	return result;
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline bool Math::VectorBase<V, T, Dim>::greater_equal(const VectorBaseT& rhs) const
{
	return apply_operator<std::greater_equal<T>>(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline bool Math::VectorBase<V, T, Dim>::greater(const VectorBaseT& rhs) const
{
	return apply_operator<std::greater<T>>(rhs);
}

// template <template<class, std::size_t> class V, class T, std::size_t Dim>
// inline typename Math::VectorBase<V, T, Dim>::VectorT Math::VectorBase<V, T, Dim>::abs() const
// {
// 	VectorT r;
// 	std::transform(cbegin(), cend(), r.begin(), details::abs<T>());
// 	return r;
// }

template <template<class, std::size_t> class V, class T, std::size_t Dim>
template<class OperatorT>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::transform(const T(&rhs)[ Dim ])
{
	std::transform(this->m_data, this->m_data + Dim, rhs, this->m_data, OperatorT());
	return static_cast< VectorT& >( *this );
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
template<class OperatorT>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::transform(const T& v)
{
	std::transform(begin(), end(), begin(), std::bind(OperatorT(), std::placeholders::_1, v));
	return static_cast< VectorT& >( *this );
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::operator+=(const VectorBaseT& rhs)
{
	return increment(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::operator+=(const T(&rhs)[ Dim ])
{
	return increment(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::operator-=(const VectorBaseT& rhs)
{
	return decrement(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::operator-=(const T(&rhs)[ Dim ])
{
	return decrement(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::operator*=(const VectorBaseT& rhs)
{
	return multiply(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::operator*=(const T(&rhs)[ Dim ])
{
	return multiply(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::operator*=(const T& v)
{
	return multiply(v);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::operator/=(const VectorBaseT& rhs)
{
	return divide(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::operator/=(const T(&rhs)[ Dim ])
{
	return divide(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline typename Math::VectorBase<V, T, Dim>::VectorT& Math::VectorBase<V, T, Dim>::operator/=(const T& v)
{
	return divide(v);
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline bool Math::VectorBase<V, T, Dim>::operator!=(const VectorBaseT& rhs) const
{
	return !( *this == rhs );
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
inline bool Math::VectorBase<V, T, Dim>::operator==(const VectorBaseT& rhs) const
{
	return std::equal(begin(), end(), rhs.begin());
}

//template <template<class, std::size_t> class V, class T, std::size_t Dim>
//inline typename Math::VectorBase<V, T, Dim>::VectorT Math::VectorBase<V, T, Dim>::operator-() const
//{
//	return VectorT(this->m_data).negate();
//}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
template<class NewT>
inline Math::VectorBase<V, T, Dim>::operator V<NewT, Dim>() const
{
	V<NewT, Dim> result;
	for ( std::size_t i = 0u; i < Dim; ++i )
	{
		result[ i ] = static_cast< NewT >( this->m_data[ i ] );
	}
	return result;
}

template <template<class, std::size_t> class V, class T, std::size_t Dim>
template<class OperatorT>
inline bool Math::VectorBase<V, T, Dim>::apply_operator(const VectorBaseT& rhs) const
{
	for ( size_t i = 0u; i < Dim; i++ )
	{
		if ( !OperatorT()( this->m_data[ i ], rhs.data()[ i ] ) )
		{
			return false;
		}
	}
	return true;
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator+ (const  V<T, N>& lhs, const  V<T, N>& rhs)
{
	return V<T, N>(lhs.data()).increment(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator+ (const T(&lhs)[ N ], const  V<T, N>& rhs)
{
	return V<T, N>(lhs).increment(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator+ (const  V<T, N>& rhs, const T& v)
{
	return V<T, N>(rhs.data()).increment(v);
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline  V<T, N> operator-(const V<T, N>& lhs, const V<T, N>& rhs)
{
	return V<T, N>(lhs.data()).decrement(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator-(const T(&lhs)[ N ], const  V<T, N>& rhs)
{
	return V<T, N>(lhs).decrement(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator- (const  V<T, N>& rhs, const T& v)
{
	return V<T, N>(rhs.data()).decrement(v);
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator* (const V<T, N>& lhs, const V<T, N>& rhs)
{
	return V<T, N>(lhs.data()).multiply(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator* (const T(&lhs)[ N ], const V<T, N>& rhs)
{
	return V<T, N>(lhs).multiply(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator* (const V<T, N>& rhs, const T& v)
{
	return V<T, N>(rhs.data()).multiply(v);
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator* (const T& v, const V<T, N>& rhs)
{
	return V<T, N>(rhs.data()).multiply(v);
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator/ (const V<T, N>& lhs, const V<T, N>& rhs)
{
	return V<T, N>(lhs.data()).divide(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator/ (const T(&lhs)[ N ], const V<T, N>& rhs)
{
	return V<T, N>(lhs).divide(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator/ (const V<T, N>& rhs, const T& v)
{
	return V<T, N>(rhs.data()).divide(v);
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline bool operator<= (const V<T, N>& lhs, const V<T, N>& rhs)
{
	return lhs.less_equal(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline bool operator>= (const V<T, N>& lhs, const V<T, N>& rhs)
{
	return lhs.greater_equal(rhs);
}
template <template<class, std::size_t> class V, class T, std::size_t N>
inline bool operator< (const V<T, N>& lhs, const V<T, N>& rhs)
{
	return lhs.less(rhs);
}
template <template<class, std::size_t> class V, class T, std::size_t N>
inline bool operator> (const V<T, N>& lhs, const V<T, N>& rhs)
{
	return lhs.greater(rhs);
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline std::ostream& operator<<(std::ostream& o_stream, const  V<T, N>& i_vec)
{
	using VIt = typename V<T, N>::const_iterator;
	VIt begin = i_vec.cbegin();
	VIt end = i_vec.cend();
	o_stream << "[";
	for ( VIt it = begin; it < end - 1u; ++it )
	{
		o_stream << *it << ", ";
	}
	o_stream << *( end - 1u );
	o_stream << "]";
	return o_stream;
}

template <template<class, std::size_t> class V, class T, std::size_t N>
inline std::istream& operator>>(std::istream& i_stream, V<T, N>& i_vec)
{
	i_stream.ignore(N, '[');
	for ( std::size_t i = 0u; i < N - 1; ++i )
	{
		i_stream >> i_vec[ i ];
		i_stream.ignore(N, ' ');
	}
	i_stream >> i_vec[ N - 1 ];
	i_stream.ignore(N, ']');
	return i_stream;
}

//////////////////////////////////////////////////////////////////////////
template <class T>
inline Math::Vector<T, 2u>::Vector()
{
	this->m_data[ 0u ] = 0;
	this->m_data[ 1u ] = 0;
};

template <class T>
inline Math::Vector<T, 2u>::Vector(T v1, T v2)
{
	this->m_data[ 0u ] = v1;
	this->m_data[ 1u ] = v2;
}
template <class T>
inline double Math::Vector<T, 2u>::length() const
{
	return std::sqrt(this->m_data[ 0u ] * this->m_data[ 0u ]
				   + this->m_data[ 1u ] * this->m_data[ 1u ]);
}

template <class T>
inline T Math::Vector<T, 2u>::dot(const Vector<T, 2u>& rhs) const
{
	return this->m_data[ 0u ] * rhs.m_data[ 0u ]
		 + this->m_data[ 1u ] * rhs.m_data[ 1u ];
}

template <class T>
inline T Math::Vector<T, 2u>::y() const
{
	return this->m_data[ 1u ];
}

//////////////////////////////////////////////////////////////////////////
template <class T>
inline Math::Vector<T, 3u>::Vector()
{
	this->m_data[ 0u ] = 0;
	this->m_data[ 1u ] = 0;
	this->m_data[ 2u ] = 0;
};

template <class T>
inline Math::Vector<T, 3u>::Vector(T v1, T v2, T v3)
{
	this->m_data[ 0u ] = v1;
	this->m_data[ 1u ] = v2;
	this->m_data[ 2u ] = v3;
};

template <class T>
inline T Math::Vector<T, 3u>::y() const
{
	return this->m_data[ 1u ];
}

template <class T>
inline T Math::Vector<T, 3u>::z() const
{
	return this->m_data[ 2u ];
}

template <class T>
inline T Math::Vector<T, 3u>::dot(const Vector<T, 3u>& rhs) const
{
	return this->m_data[ 0u ] * rhs.m_data[ 0u ]
		 + this->m_data[ 1u ] * rhs.m_data[ 1u ]
		 + this->m_data[ 2u ] * rhs.m_data[ 2u ];
}

template <class T>
inline double Math::Vector<T, 3u>::length() const
{
	return std::sqrt(this->m_data[ 0u ] * this->m_data[ 0u ]
					 + this->m_data[ 1u ] * this->m_data[ 1u ]
					 + this->m_data[ 2u ] * this->m_data[ 2u ]);
}

template <class T>
inline Math::Vector<T, 3u> Math::Vector<T, 3u>::cross(const Vector<T, 3u>& rhs) const
{
	return Vector<T, 3>(
		this->m_data[ 1 ] * rhs.m_data[ 2 ] - this->m_data[ 2 ] * rhs.m_data[ 1 ],
		this->m_data[ 0 ] * rhs.m_data[ 2 ] - this->m_data[ 2 ] * rhs.m_data[ 0 ],
		this->m_data[ 0 ] * rhs.m_data[ 1 ] - this->m_data[ 1 ] * rhs.m_data[ 0 ]
		);
}

} // namespace Math
