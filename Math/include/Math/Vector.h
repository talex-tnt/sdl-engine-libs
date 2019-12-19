#pragma once

#include <iostream>
#include <type_traits>
#include <iosfwd>
#include <functional>
#include <algorithm>

namespace Math
{

template <template<class, std::size_t> class V, class T, std::size_t Dim>
class VectorBase
{
	static_assert( Dim > 1u, "Please provide a dimension greater than 1u" );

public:
	using value_type = T;
	using reference = T &;
	using const_reference = const T&;
	using pointer = T *;
	using const_pointer = const T*;
	using size_type = std::size_t;

	using iterator = T*;
	using const_iterator = const T*;
	using riterator = std::reverse_iterator<iterator>;
	using const_riterator = std::reverse_iterator<const_iterator>;

	using PlusOp = std::plus<T>;
	using MinusOp = std::minus<T>;
	using MultiplyOp = std::multiplies<T>;
	using DivideOp = std::divides<T>;
	//using NegateOp = std::negate<T>;
	using VectorBaseT = VectorBase<V, T, Dim>;
	using VectorT = V<T, Dim>;

protected:
	~VectorBase() = default; // We shouldn't delete this polymorfically

	// we shouldn't create objects directly as well
/*protected*/ public:
 // only subclasses should create VectorBase obj but:
//	https://developercommunity.visualstudio.com/content/problem/265966/protected-inherited-constructor-not-available-for.html
	VectorBase();;
	VectorBase(value_type v);;
	VectorBase(const VectorBaseT& rhs);
	VectorBase(const T(&rhs)[ Dim ]);
	VectorBase(VectorBaseT&& rhs) = default;

public:
	VectorT& operator=(const VectorBaseT& rhs);
	VectorT& operator=(VectorBaseT&& rhs);
	T& operator[](std::size_t idx);
	const T& operator[](std::size_t idx) const;

	T const ( &data() const )[ Dim ] { return m_data; } //returns T(&)[Dim]

	const T& x() const;
	reference back();
	const_reference back() const;
	iterator begin();
	riterator rbegin();
	const_iterator begin() const;
	const_riterator rbegin() const;
	iterator end();
	riterator rend();
	const_iterator end() const;
	const_riterator rend() const;
	const_iterator cbegin() const;
	const_riterator crbegin() const;
	const_iterator cend() const;
	const_riterator crend() const;

	T dot(const VectorT& rhs) const;

	VectorT& increment(const VectorBaseT& rhs);
	VectorT& increment(const T(&rhs)[Dim]);
	VectorT& increment(const T& v);

	VectorT& decrement(const VectorBaseT& rhs);
	VectorT& decrement(const T(&rhs)[ Dim ]);
	VectorT& decrement(const T& v);

	VectorT& multiply(const VectorBaseT& rhs);
	VectorT& multiply(const T(&rhs)[ Dim ]);
	VectorT& multiply(const T& v);

	VectorT& divide(const VectorBaseT& rhs);
	VectorT& divide(const T(&rhs)[ Dim ]);
	VectorT& divide(const T& v);

	//VectorT& negate();

	bool less(const VectorBaseT& rhs) const;
	bool less_equal(const VectorBaseT& rhs) const;
	bool equal(const VectorBaseT& rhs) const;
	bool greater_equal(const VectorBaseT& rhs) const;
	bool greater(const VectorBaseT& rhs) const;

	VectorT abs() const;

	template<class OperatorT>
	VectorT& transform(const T(&rhs)[ Dim ]);

	template<class OperatorT>
	VectorT& transform(const T& v);

	VectorT& operator+=(const VectorBaseT& rhs);
	VectorT& operator+= (const T(&rhs)[ Dim ]);
	VectorT& operator-=(const VectorBaseT& rhs);
	VectorT& operator-= (const T(&rhs)[ Dim ]);
	VectorT& operator*=(const VectorBaseT& rhs);
	VectorT& operator*= (const T(&rhs)[ Dim ]);
	VectorT& operator*= (const T& v);
	VectorT& operator/=(const VectorBaseT& rhs);
	VectorT& operator/= (const T(&rhs)[ Dim ]);
	VectorT& operator/= (const T& v);
	bool operator!=(const VectorBaseT& rhs) const;
	bool operator==(const VectorBaseT& rhs) const;
	//VectorT operator-() const;

	template<class NewT>
	explicit operator V<NewT, Dim>() const;

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend std::ostream& operator<<(std::ostream& o_stream, const VectorT& i_vec);
	
	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend std::istream& operator>>(std::istream& i_stream, VectorT& i_vec);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend VectorT operator+ (const VectorT& lhs, const VectorT& rhs);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend VectorT operator+ (const T (&lhs)[N], const VectorT& rhs);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend VectorT operator+ (const VectorT& rhs, const T& v);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend VectorT operator- (const VectorT& lhs, const VectorT& rhs);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend VectorT operator- (const T(&lhs)[ N ], const VectorT& rhs);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend VectorT operator- (const VectorT& rhs, const T& v);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend VectorT operator* (const VectorT& lhs, const VectorT& rhs);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend VectorT operator* (const T(&lhs)[ N ], const VectorT& rhs);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend VectorT operator* (const VectorT& rhs, const T& v);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend VectorT operator/ (const T& v, const VectorT& rhs);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend VectorT operator/ (const VectorT& lhs, const VectorT& rhs);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend VectorT operator/ (const T(&lhs)[ N ], const VectorT& rhs);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend VectorT operator/ (const VectorT& rhs, const T& v);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend bool operator<= (const VectorT& lhs, const VectorT& rhs);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend bool operator>= (const VectorT& lhs, const VectorT& rhs);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend bool operator< (const VectorT& lhs, const VectorT& rhs);

	template <template<class, std::size_t> class V, class T, std::size_t N>
	friend bool operator> (const VectorT& lhs, const VectorT& rhs);

private:
	template<class OperatorT>
	bool apply_operator(const VectorBaseT& rhs) const;

protected:
	T m_data[ Dim ];
};
//////////////////////////////////////////////////////////////////////////

template <template<class, std::size_t> class V, class T, std::size_t N>
inline std::ostream& operator<<(std::ostream& o_stream, const V<T,N>& i_vec);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline std::istream& operator>>(std::istream& i_stream, V<T, N>& i_vec);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator+ (const V<T, N>& lhs, const V<T, N>& rhs);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator+ (const T(&lhs)[ N ], const V<T, N>& rhs);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator+ (const V<T, N>& rhs, const T& v);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator- (const V<T, N>& lhs, const V<T, N>& rhs);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator- (const T(&lhs)[ N ], const V<T, N>& rhs);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator- (const V<T, N>& rhs, const T& v);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator* (const V<T, N>& lhs, const V<T, N>& rhs);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator* (const T(&lhs)[ N ], const V<T, N>& rhs);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator* (const V<T, N>& rhs, const T& v);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator/ (const T& v, const V<T, N>& rhs);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator/ (const V<T, N>& lhs, const V<T, N>& rhs);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator/ (const T(&lhs)[ N ], const V<T, N>& rhs);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline V<T, N> operator/ (const V<T, N>& rhs, const T& v);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline bool operator<= (const V<T, N>& lhs, const V<T, N>& rhs);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline bool operator>= (const V<T, N>& lhs, const V<T, N>& rhs);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline bool operator< (const V<T, N>& lhs, const V<T, N>& rhs);

template <template<class, std::size_t> class V, class T, std::size_t N>
inline bool operator> (const V<T, N>& lhs, const V<T, N>& rhs);
//////////////////////////////////////////////////////////////////////////

template <class T, std::size_t Dim>
class Vector : public VectorBase<Vector,T, Dim>
{
public:
#if defined(__clang__)
	using VectorBase<Vector, T, Dim>::VectorBase;
#else
	using VectorBase::VectorBase;
#endif
};

//////////////////////////////////////////////////////////////////////////

/*
	Most of the features have already a generic implementation in VectorBase
	but we can implement optimizations here if required.
*/

template <class T>
class Vector<T, 2u> : public VectorBase<Vector, T, 2u>
{
public:
#if defined(__clang__)
	using VectorBase<Vector, T, 2u>::VectorBase;
#else
	using VectorBase::VectorBase;
#endif

	Vector<T, 2u>();
	Vector<T, 2u>(T v1, T v2);
	T y() const;
	T dot(const Vector<T, 2u>& rhs) const;
	double length() const;
};

//////////////////////////////////////////////////////////////////////////

template <class T>
class Vector<T, 3u> : public VectorBase<Vector, T, 3u>
{
public:
#if defined(__clang__)
	using VectorBase<Vector, T, 3u>::VectorBase;
#else
	using VectorBase::VectorBase;
#endif
	Vector<T, 3u>();
	Vector<T, 3u>(T v1, T v2, T v3);
	T y() const;
	T z() const;
	T dot(const Vector<T, 3u>& rhs) const;
	Vector<T, 3u> cross(const Vector<T, 3u>& rhs) const;
	double length() const;
};


// some shorthand type
using Vec4f = Vector<float, 4u>;
using Vec3f = Vector<float, 3u>;
using Vec2f = Vector<float, 2u>;
using Vec2i = Vector<std::int32_t, 2u>;
using Vec2u = Vector<std::uint32_t, 2u>;

//////////////////////////////////////////////////////////////////////////
}
