#include "Math/Vector-inl.h"
#include <iosfwd>

namespace Math
{
using vectype = std::uint32_t;
constexpr static std::size_t Dim = 3u;
using VecT = Vector<vectype, Dim>;

template class VectorBase<Vector, vectype, Dim>;
template class Vector<vectype, Dim>;
template VecT operator+(const VecT&, const VecT&);
template VecT operator+(const vectype(&)[ Dim ], const VecT&);
template VecT operator-(const vectype(&)[ Dim ], const VecT&);
template VecT operator*(const vectype(&)[ Dim ], const VecT&);
template VecT operator/(const vectype(&)[ Dim ], const VecT&);
template VecT operator*(const VecT&, const vectype&);
template VecT operator/(const VecT&, const vectype&);
template VecT operator+(const VecT&, const vectype&);
template VecT operator-(const VecT&, const vectype&);

template std::ostream& operator<<(std::ostream& o_stream, const VecT& i_vec);

namespace details
{
template <>
struct abs<vectype> {	
	vectype operator()(vectype const& t) { return t; }
};
} 

}

