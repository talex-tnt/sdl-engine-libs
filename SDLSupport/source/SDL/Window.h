#pragma once

#include <functional>
#include <memory>


struct SDL_Window;

namespace sdl
{

class Window
{
public:
	Window(const std::string& title, std::int32_t width, std::int32_t height, std::uint32_t i_flags = 0u);
	~Window();

	Window(const Window&) = delete;
	Window(Window&&) = delete;

	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;

	bool IsInitialized() const noexcept;

	SDL_Window* GetSDLWindow() noexcept;
	const SDL_Window* GetSDLWindow() const noexcept;
	int GetDisplayIndex() const;
private:

	using WindowUniquePtr = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>;
	WindowUniquePtr m_window;
};

}