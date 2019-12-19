#pragma once
#include <Math/Vector.h>

namespace sdl
{
class Display;
}

namespace game
{
namespace graphics
{

class Display
{
public:
	Display(const sdl::Display& i_display);
	~Display() = default;

	using Size = Math::Vec2u;
	Size GetSize() const;
	int GetRefreshRate() const;

public:
	Display(const Display&) = delete;
	Display(Display&&) = delete;

	Display& operator=(const Display&) = delete;
	Display& operator=(Display&&) = delete;

private:
	const sdl::Display& m_display;
};

}
}
