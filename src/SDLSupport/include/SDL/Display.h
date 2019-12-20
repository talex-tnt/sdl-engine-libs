#pragma once
#include <memory>

struct SDL_Renderer;

namespace sdl
{
class Display
{
public:
	Display(SDL_Renderer& i_renderer, int i_displayIndex);
	~Display() = default;

	struct Size { using value_t = std::size_t; value_t width, height; };
	Size GetSize() const;

	int GetRefreshRate() const;

public:
	Display(const Display&) = delete;
	Display(Display&&) = delete;

	Display& operator=(const Display&) = delete;
	Display& operator=(Display&&) = delete;

private:
	SDL_Renderer& m_renderer;
	int m_displayIndex;
};
}