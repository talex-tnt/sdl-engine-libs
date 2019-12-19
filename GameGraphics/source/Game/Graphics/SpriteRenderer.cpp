#include <Game/Graphics/SpriteRenderer.h>
#include "Game/Graphics/Renderer2D.h"

namespace // #fixme: Renderer2D should accept floating points as well and round by itselft eventually
{
template<class Rect>
game::graphics::Renderer2D::Rect RoundRect(Rect r)
{
	using Pos = game::graphics::Renderer2D::Pos;
	using Size = game::graphics::Renderer2D::Size;
	return game::graphics::Renderer2D::Rect {
		Pos{
		static_cast< Pos::value_type >( std::round(r.pos.x()) ),
		static_cast< Pos::value_type >( std::round(r.pos.y()) )},
		Size{
		static_cast< Size::value_type >( std::round(r.size.x()) ),
		static_cast< Size::value_type >( std::round(r.size.y()) )} };
}
}

namespace game
{
namespace graphics
{

SpriteRenderer::~SpriteRenderer() = default;


SpriteRenderer::SpriteRenderer(const Renderer2D& i_renderer)
	: m_renderer(i_renderer)
{

}

void SpriteRenderer::Render(const Rect& i_screenRect, const Sprite& i_sprite) const
{
	m_renderer.RenderTexture(i_sprite.m_textureId, RoundRect(i_screenRect), RoundRect(i_sprite.m_rect));
}

}
}