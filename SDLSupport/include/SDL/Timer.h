#pragma  once
#include <memory>
#include <chrono>

namespace sdl
{
class Timer
{
private:
	using BaseT = float;
public:
	using SecT = std::chrono::duration<BaseT>;
	Timer();
	void Reset();
	SecT GetElapsed() const;
	static std::uint64_t GetTickPerSeconds();

private:
	std::uint64_t m_prevTicks;
};
}