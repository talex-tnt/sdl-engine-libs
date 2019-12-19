#include "Window.h"

#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wpragma-pack"
#endif
#include <SDL.h>
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif

#include <iostream>

namespace sdl
{

Window::Window(const std::string& title, std::int32_t width, std::int32_t height, std::uint32_t i_flags)
	: m_window(
		SDL_CreateWindow(
			title.c_str(),
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			width,
			height,
			i_flags
		),
		[] (SDL_Window* win) { SDL_DestroyWindow(win); })
{
	if ( !m_window )
	{
		std::cerr << SDL_GetError();
	}
}

bool Window::IsInitialized() const noexcept
{
	return m_window != nullptr;
}

SDL_Window* Window::GetSDLWindow() noexcept
{
	return m_window.get();
}

const SDL_Window* Window::GetSDLWindow() const noexcept
{
	return m_window.get();
}

int Window::GetDisplayIndex() const
{
	return SDL_GetWindowDisplayIndex(m_window.get());
}

Window::~Window() = default;

}
