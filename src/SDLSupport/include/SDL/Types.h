#pragma once
#include <memory>

namespace sdl
{
struct Pos { int x, y; };
struct Size { int w, h; };
struct Scale { float x, y; };
struct Rect { int x, y, w, h; };
struct Color { std::uint8_t r, g, b, a; };

}