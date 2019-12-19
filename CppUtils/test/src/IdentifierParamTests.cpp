#include "gtest/gtest.h"
#include "cpp-utils/Identifier.h"

#include <vector>
#include <set>
#include <unordered_set>


DEFINE_IDENTIFIER(StringId, std::string);
DEFINE_IDENTIFIER(IntId, std::int32_t);
DEFINE_IDENTIFIER_WITH_INVALID_VALUE(InvStringId, std::string, "Null");
DEFINE_IDENTIFIER_WITH_INVALID_VALUE(InvIntId, std::int32_t, -1);

namespace
{

template <typename IdType>
struct StringIdentifierFixtureBase
{
	const IdType m_constId = IdType("James");
	const IdType m_constId2 = IdType("John");
	IdType m_id = IdType("Mike");
	IdType m_id2 = IdType("Derek");
	IdType GetId() const { return IdType("Jordan"); }
	std::string ToString(const IdType& i_type) const { return i_type.GetValue(); }
	std::vector<IdType> GetValues() const { return { IdType("A"), IdType("B"), IdType("C") }; }
};

template <typename IdType>
struct IntIdentifierFixtureBase
{
	const IdType m_constId = IdType(0);
	const IdType m_constId2 = IdType(1);
	IdType m_id = IdType(2);
	IdType m_id2 = IdType(3);
	IdType GetId() const { return IdType(4); }
	std::string ToString(const IdType& i_type) const { return std::to_string(i_type.GetValue()); }
	std::vector<IdType> GetValues() const { return { IdType(0), IdType(1), IdType(2) }; }
};

template <typename T>
struct IdentifierFixture : public testing::Test {};

template <>
struct IdentifierFixture<StringId> 
	: public testing::Test
	, public StringIdentifierFixtureBase<StringId> {};

template <>
struct IdentifierFixture<IntId>
	: public testing::Test
	, public IntIdentifierFixtureBase<IntId> {};

template <>
struct IdentifierFixture<InvStringId>
	: public testing::Test
	, public StringIdentifierFixtureBase<InvStringId> {};

template <>
struct IdentifierFixture<InvIntId>
	: public testing::Test
	, public IntIdentifierFixtureBase<InvIntId> {};

using IdTypes = testing::Types<StringId, IntId, InvStringId, InvIntId>;
TYPED_TEST_CASE(IdentifierFixture, IdTypes);

///////////////////////////////////////////////////////////////////////////

template <typename T>
struct InvalidableIdentifierFixture : public testing::Test {};

template <>
struct InvalidableIdentifierFixture<InvStringId>
	: public testing::Test
	, public StringIdentifierFixtureBase<InvStringId> { };

template <>
struct InvalidableIdentifierFixture<InvIntId>
	: public testing::Test
	, public IntIdentifierFixtureBase<InvIntId> { };

using InvIdTypes = testing::Types<InvStringId, InvIntId>;
TYPED_TEST_CASE(InvalidableIdentifierFixture, InvIdTypes);
///////////////////////////////////////////////////////////////////////////


TYPED_TEST(IdentifierFixture, TestCopyCtorLValueArg)
{
	const TypeParam copyId(m_id);
	EXPECT_EQ(copyId, m_id);
}

TYPED_TEST(IdentifierFixture, TestCopyCtorConstLValueArg)
{
	const TypeParam copyId(m_constId);
	EXPECT_EQ(copyId, m_constId);
}

TYPED_TEST(IdentifierFixture, TestCopyCtorRValueArg)
{
	const TypeParam copyId(GetId());
	EXPECT_EQ(copyId, GetId());
}

TYPED_TEST(IdentifierFixture, TestMoveCtorLValue)
{
	TypeParam copyId(m_id);
	const TypeParam movedId(std::move(copyId));
	EXPECT_EQ(movedId, m_id);
}

TYPED_TEST(IdentifierFixture, TestMoveCtorRValue)
{
	const TypeParam movedId(std::move(GetId()));
	EXPECT_EQ(movedId, GetId());
}

TYPED_TEST(IdentifierFixture, TestEquality)
{
	const TypeParam copyId(m_id);
	EXPECT_TRUE(copyId == m_id);
}

TYPED_TEST(IdentifierFixture, TestInequality)
{
	EXPECT_TRUE(m_constId != m_id);
}

TYPED_TEST(IdentifierFixture, TestCopyAssignmentOperator)
{
	TypeParam myId = GetId();
	myId = m_id;
	EXPECT_EQ(myId , m_id);
}

TYPED_TEST(IdentifierFixture, TestMoveAssignmentOperator)
{
	TypeParam myId = GetId();
	const TypeParam copyId(m_id);
	myId = std::move(copyId);
	EXPECT_EQ(myId, copyId);
	EXPECT_NE(myId, GetId());
}

TYPED_TEST(IdentifierFixture, TestGetValue)
{
	const TypeParam myId(GetId());
	EXPECT_EQ(myId.GetValue(), TypeParam(myId).GetValue());
}

TYPED_TEST(InvalidableIdentifierFixture, TestExpectInvalidValue)
{
	const TypeParam myId;
	EXPECT_FALSE(myId.IsValid());
}

TYPED_TEST(InvalidableIdentifierFixture, TestExpectValidValue)
{
	const TypeParam myId = GetId();
	EXPECT_TRUE(myId.IsValid());
}

TYPED_TEST(IdentifierFixture, TestOutputStream)
{
	std::ostringstream os;
	os << m_id;
	EXPECT_EQ(os.str(), ToString(m_id));
}

TYPED_TEST(IdentifierFixture, TestInputStream)
{
	std::istringstream is(ToString(GetId()));
	is >> m_id;
	EXPECT_EQ(GetId(), m_id);
}

TYPED_TEST(IdentifierFixture, TestCmpOperator)
{
	const std::vector<TypeParam> values = GetValues();
	using VecRIt = std::vector<TypeParam>::const_reverse_iterator;
	using VecIt = std::vector<TypeParam>::const_iterator;

	std::set<TypeParam, TypeParam::LessCmp> set;
	for ( VecRIt it = values.crbegin(); it != values.crend(); ++it)
	{
		set.insert(TypeParam(*it));
	}
	using SetIt = std::set<TypeParam>::const_iterator; 
	SetIt setIt = set.cbegin();
	VecIt vecIt = values.cbegin();
	for ( ; setIt != set.cend(); ++setIt, ++vecIt )
	{
		EXPECT_EQ(*setIt, *vecIt);
	}
}

TYPED_TEST(IdentifierFixture, TestUnorderedSetKey)
{
	std::unordered_set<TypeParam, TypeParam::Hasher> set;
	set.emplace(m_id);
	set.emplace(m_constId);
	{
		auto it = set.find(m_id);
		EXPECT_TRUE(it != set.cend());
		EXPECT_EQ(*it, m_id);
	}
	{
		auto it = set.find(m_constId);
		EXPECT_TRUE(it != set.cend());
		EXPECT_EQ(*it, m_constId);
	}
}

}

