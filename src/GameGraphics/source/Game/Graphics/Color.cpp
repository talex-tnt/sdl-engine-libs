#include <Game/Graphics/Color.h>
#include <Game/Graphics/Renderer2D.h>
#include <SDL/Renderer.h>

namespace game
{
namespace graphics
{
const Color::RGB Color::k_colorWhite(255u, 255u, 255u);
const Color::RGB Color::k_colorRed(255u, 0u, 0u);
const Color::RGB Color::k_colorGreen(0u, 255u, 0u);
const Color::RGB Color::k_colorBlue(0u, 0u, 255u);

template<class ScaledType, class InputType>
ScaledType ScaleValue(InputType value)
{
	const std::size_t maxValue = std::numeric_limits<ScaledType>::max();
	const ScaledType s = static_cast< ScaledType >(std::round(value * maxValue));
	return s;
}

Color::RGBA Color::ToRgba(const RGB& c, float alpha)
{
	using ValueT = RGBA::value_type;
	const ValueT a = ScaleValue<ValueT>(alpha);
	return ToRgba(c, a);
}

Color::RGBA Color::ToRgba(const RGB& c, std::uint8_t alpha)
{
	return RGBA({ c[ 0 ], c[ 1 ], c[ 2 ], alpha });
}


graphics::Color::RGBA Color::GetGray(std::uint8_t value)
{
	return RGBA({value, value, value, 255u });
}

graphics::Color::RGBA Color::GetGray(float value)
{
	return GetGray(ScaleValue<RGBA::value_type>(value));
}

PushedColor::PushedColor(Renderer2D& i_renderer, const Color::RGBA& c)
	: m_renderer(i_renderer), m_prevColor(c)
{ }

PushedColor::~PushedColor()
{
	m_renderer.SetRenderColor(m_prevColor);
}

}
}
