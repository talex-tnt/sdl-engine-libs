#pragma once
#include <functional>
#include <memory>

struct SDL_Window;

namespace sdl
{
class Window;
namespace policy
{
class Initialization
{
public:
	using WindowT = Window;

	bool Init(const std::string& i_windowTitle, std::int32_t i_width, std::int32_t i_height);
	WindowT* GetWindow();
	const WindowT* GetWindow() const;

protected:
	Initialization();
	~Initialization();

	Initialization(const Initialization&) = delete;
	Initialization(Initialization&&) = delete;

	Initialization& operator=(const Initialization&) = delete;
	Initialization& operator=(Initialization&&) = delete;

protected:
	std::unique_ptr<WindowT> m_window;
};

}
}