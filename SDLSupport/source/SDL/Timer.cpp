#include <SDL/Timer.h>

#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wpragma-pack"
#endif
#	include <SDL.h>
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif
#include <iostream>

namespace sdl
{

Timer::Timer() : m_prevTicks(0)
{ }


void Timer::Reset()
{
	m_prevTicks = SDL_GetPerformanceCounter();
}

Timer::SecT Timer::GetElapsed() const
{
	const Uint64 currentTicks { SDL_GetPerformanceCounter() };
	const Uint64 delta { currentTicks - m_prevTicks };
	static const Uint64 k_ticksPerSeconds { GetTickPerSeconds() };
	return SecT(delta / static_cast< BaseT >( k_ticksPerSeconds ));
}

std::uint64_t Timer::GetTickPerSeconds()
{
	return SDL_GetPerformanceFrequency();
}

}