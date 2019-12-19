#include "gtest/gtest.h"
#include "cpp-utils/Identifier.h"
#include "cpp-utils/Signal.h"

namespace
{
using namespace cpp;

void Square(int& value) { value *= value; }
void Sum(int a, int b, int& result) { result = a + b; }

template<typename T>
class Delegate
{
public:
	Delegate(T i_value) : m_value(i_value) { }
	const T& GetValue() const& noexcept { return m_value; }
	void SetValue(const T& i_value) noexcept { m_value = i_value; }
private:
	T m_value;
};

class Emitter
{
public:
	void Emit(int v) 
	{
		Sig::Emitter(sig_emit).Emit(v);
	}
protected:
	class SigKey;
public:
	using Sig = utils::KeySignal<SigKey, int>;
	Sig sig_emit;
};

TEST(SignalTest, SignalConnectedWithLambda)
{
	using Sig = utils::Signal<int>;
	const int original = 0;
	int value = original;
	Sig sig;
	Sig::Connection c = sig.Connect([ &value ] (int delta) { value += delta; });

	const int delta = 100;
	sig.Emit(delta);

	EXPECT_EQ(value, original + delta);
}

TEST(SignalTest, SignalDisconnectedWithLambda)
{
	using Sig = utils::Signal<int>;
	const int original = 0;
	int value = original;
	Sig sig;
	{
		Sig::Connection c = sig.Connect([ &value ] (int delta) { value += delta; });
	}
	const int delta = 100;
	sig.Emit(delta);

	EXPECT_EQ(value, original);
}


TEST(SignalTest, SignalConnectedWithFunc)
{
	using Sig = utils::Signal<int&>;

	const int original = 10;
	int value = original;
	
	int expected = original;
	Square(expected);
	
	Sig sig;
	Sig::Connection c = sig.Connect(Square);

	sig.Emit(value);

	EXPECT_EQ(value, expected);
}

TEST(SignalTest, SignalConnectedWithMethod)
{
	using T = int;
	const T original = 0;
	const T expected = 100;
	using Sig = utils::Signal<const T&>;
	Delegate<T> del(original);

	Sig sig;
	Sig::Connection c = sig.Connect(&Delegate<T>::SetValue, &del, std::placeholders::_1);

	sig.Emit(expected);

	EXPECT_EQ(del.GetValue(), expected);
}


TEST(SignalTest, SignalDisconnectedWithMethod)
{
	using T = int;
	const T original = 0;
	const T expected = 100;
	using Sig = utils::Signal<const T&>;
	Delegate<T> del(original);

	Sig sig;
	{
		Sig::Connection c = sig.Connect(&Delegate<T>::SetValue, &del, std::placeholders::_1);
	}

	sig.Emit(expected);

	EXPECT_EQ(del.GetValue(), original);
}


TEST(SignalTest, SignalConnectedWithFuncSum2)
{
	using Sig = utils::Signal<int, int, int&>;

	const int original1 = 7;
	const int original2 = 3;
	int result = 0;

	int expected = 0;
	Sum(original1, original2, expected);

	Sig sig;
	Sig::Connection c = sig.Connect(Sum);

	sig.Emit(original1, original2, result);

	EXPECT_EQ(result, expected);
}


TEST(SignalTest, SignalConnectedWithFuncSum2Placeholders)
{
	using Sig = utils::Signal<int&>;

	const int original1 = 17;
	const int original2 = 13;
	int result = 0;

	int expected = 0;
	Sum(original1, original2, expected);

	Sig sig;

	Sig::Connection c = sig.Connect(&Sum, original1, original2, std::placeholders::_1);

	sig.Emit(result);

	EXPECT_EQ(result, expected);
}

TEST(SignalTest, SignalCheckSlotCount)
{
	using Sig = utils::Signal<int>;
	Sig sig;
	{
		Sig::Connection c1 = sig.Connect([] (int delta) { std::cout << "Slot Test" << std::endl; });
		{
			Sig::Connection c2 = sig.Connect([] (int delta) { std::cout << "Slot Test" << std::endl; });
			EXPECT_EQ(sig.GetSlotCount(), 2);
		}
		EXPECT_EQ(sig.GetSlotCount(), 1);
	}
	EXPECT_EQ(sig.GetSlotCount(), 0);
}


TEST(SignalTest, SignalBlockedWithLambda)
{
	using Sig = utils::Signal<int>;
	const int original = 0;
	int value = original;
	const int delta = 100;

	Sig sig;
	
	Sig::Connection c = sig.Connect([ &value ] (int delta) { value += delta; });
	c.SetBlocked(true);


	sig.Emit(delta);
	EXPECT_EQ(value, original);

	c.SetBlocked(false);
	sig.Emit(delta);
	EXPECT_EQ(value, original + delta);
}

TEST(SignalTest, SignalExplicitDiscWithLambda)
{
	using Sig = utils::Signal<int>;
	const int original = 0;
	int value = original;
	const int delta = 100;

	Sig sig;

	Sig::Connection c = sig.Connect([ &value ] (int delta) { value += delta; });
	c.Disconnect();


	sig.Emit(delta);
	EXPECT_EQ(value, original);
}

TEST(SignalTest, SignalCheckIsConnected)
{
	using Sig = utils::Signal<int>;

	Sig sig;
	Sig::Connection c = sig.Connect([ ] (int delta) { });
	EXPECT_TRUE(c.IsConnected());
	c.Disconnect();
	EXPECT_FALSE(c.IsConnected());
}


TEST(SignalTest, EmptyConnectionCheck)
{
	using Sig = utils::Signal<int>;
	Sig::Connection c;
	EXPECT_FALSE(c.IsConnected());
	c.Disconnect();
	EXPECT_FALSE(c.IsConnected());
}

TEST(SignalTest, AssignConnectionCheck)
{
	using Sig = utils::Signal<int>;
	Sig::Connection c;
	EXPECT_FALSE(c.IsConnected());
	Sig sig;
	c = sig.Connect([] (int delta) { });
	EXPECT_TRUE(c.IsConnected());
	c.Disconnect();
	EXPECT_FALSE(c.IsConnected());
}

TEST(SignalTest, DisconnetionWithSignalDestructionCheck)
{
	using Sig = utils::Signal<int>;
	Sig::Connection c;
	{
		Sig sig;
		c = sig.Connect([] (int delta) { });
		EXPECT_EQ(sig.GetSlotCount(), 1u);
		EXPECT_TRUE(c.IsConnected());
	}
	EXPECT_FALSE(c.IsConnected());
}


TEST(SignalTest, SignalCheckMultipleConnections)
{
	using Sig = utils::Signal<>;
	Sig sig;
	{
		Sig::Connection c1 = sig.Connect([] () { std::cout << "Slot Test" << std::endl; });
		EXPECT_TRUE(c1.IsConnected());
		{
			Sig::Connection c2 = sig.Connect([] () { std::cout << "Slot Test2" << std::endl; });
			EXPECT_TRUE(c2.IsConnected());
			{
				Sig::Connection c3 = sig.Connect([] () { std::cout << "Slot Test3" << std::endl; });
				EXPECT_TRUE(c3.IsConnected());
			}
			EXPECT_TRUE(c2.IsConnected());
		}
		EXPECT_TRUE(c1.IsConnected());
	}
}

TEST(PrvSignalTest, SignalConnectedWithLambda)
{
	class KeyT;
	using Sig = utils::KeySignal<KeyT, int>;
	const int original = 0;
	int value = original;
	Sig sig;
	Sig::Connection c = sig.Connect([ &value ] (int delta) { value += delta; });

	const int delta = 100;
	Sig::Emitter(sig).Emit(delta);

	EXPECT_EQ(value, original + delta);
}

TEST(PrvSignalTest, EmitterWithLambda)
{
	Emitter emitter;
	const int original = 0;
	int value = original;
	Emitter::Sig::Connection c = emitter.sig_emit.Connect([ &value ] (int delta) { value += delta; });
	//emitter.sig_emit.Emit(100); // not allowed
	const int delta = 100;
	emitter.Emit(delta);

	EXPECT_EQ(value, original + delta);
}
} //namespace

