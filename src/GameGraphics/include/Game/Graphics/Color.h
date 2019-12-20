#pragma once
#include <Math/Vector.h>

namespace game
{
namespace graphics
{
class Color
{
public:
	using RGBA = Math::Vector<std::uint8_t, 4u>;
	using RGB = Math::Vector<std::uint8_t, 3u>;

	static const RGB k_colorWhite;
	static const RGB k_colorRed;
	static const RGB k_colorGreen;
	static const RGB k_colorBlue;

	static RGBA ToRgba(const RGB& color, float alpha);
	static RGBA ToRgba(const RGB& color, std::uint8_t alpha);
	static RGBA GetGray(std::uint8_t value);
	static RGBA GetGray(float value);

};
class Renderer2D;
class PushedColor
{
public:
	PushedColor(Renderer2D& i_renderer, const Color::RGBA& prevColor);
	~PushedColor();
private:
	Renderer2D& m_renderer;
	Color::RGBA m_prevColor;
};

}
}
