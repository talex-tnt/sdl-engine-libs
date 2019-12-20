#pragma once

#include "Renderer2D.h"

namespace game
{
namespace graphics
{

template<std::size_t N>
inline void gamebase::graphics::Renderer2D::RenderFilledRects(const std::array<Rect, N>& i_rects) const
{
	RenderFilledRects(i_rects.data(), N);
}

template<std::size_t N>
inline void gamebase::graphics::Renderer2D::RenderLines(const std::array<Pos, N>& i_points) const
{
	RenderLines(i_points.data(), N);
}

}
}