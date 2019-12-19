#include <Game/Graphics/Renderer2D.h>
#include "Game/Graphics/TextureMgr.h"

#include <SDL/Renderer.h>
#include <SDL/Texture.h>

#include <assert.h>


namespace game
{
namespace graphics
{

Renderer2D::Renderer2D(Renderer& i_renderer)
	: m_renderer(i_renderer)
{ }

Renderer2D::~Renderer2D() = default;

bool Renderer2D::Init()
{
	return m_renderer.Init();
}

void Renderer2D::BeginRendering()
{
	m_renderer.BeginRendering();
}

void Renderer2D::EndRendering()
{
	m_renderer.EndRendering();
}

void Renderer2D::RenderLine(const Pos& start, const Pos& end) const
{
	m_renderer.RenderLine(start.x(), start.y(), end.x(), end.y());
}

void Renderer2D::RenderLines(const Pos* i_points, std::size_t count) const
{
	static_assert( std::is_same<decltype( sdl::Pos::x ), Pos::value_type>::value
				  && std::is_same<decltype( sdl::Pos::y ), Pos::value_type>::value,
				  "Array Base type mismatch" );
	const sdl::Pos* rPoints = reinterpret_cast< const sdl::Pos* >( i_points );
	m_renderer.RenderLines(rPoints, count);
}

void Renderer2D::RenderFilledRects(const Rect* i_rects, std::size_t count) const
{
	static_assert( std::is_same<decltype( sdl::Rect::x ), Pos::value_type>::value
				  && std::is_same<decltype( sdl::Rect::y ), Pos::value_type>::value
				  && std::is_same<decltype( sdl::Rect::w ), Size::value_type>::value
				  && std::is_same<decltype( sdl::Rect::h ), Size::value_type>::value,
				  "Array Base type mismatch" );
	const sdl::Rect* rRects = reinterpret_cast< const sdl::Rect* >( i_rects );
	m_renderer.RenderFilledRects(rRects, count);
}

void Renderer2D::RenderPoint(const Pos& pos) const
{
	m_renderer.RenderPoint(pos.x(), pos.y());
}

void Renderer2D::SetRenderColor(const Color::RGBA& i_col)
{
	m_renderer.SetRenderColor(i_col[ 0u ], i_col[ 1u ], i_col[ 2u ], i_col[ 3u ]);
}

graphics::PushedColor Renderer2D::PushColor(const Color::RGBA& i_col)
{
	const sdl::Renderer::Color c = m_renderer.GetRenderColor();
	m_renderer.SetRenderColor(sdl::Renderer::Color { i_col[ 0 ], i_col[ 1 ], i_col[ 2 ], i_col[ 3 ] });
	return PushedColor(*this, Color::RGBA({ c.r, c.g, c.b, c.a }));
}


//////////////////////////////////////////////////////////////////////////

namespace
{
const TextureProvider::Texture* FindTextureByIdOrAssert(const TextureMgr& i_textureProvider, TextureProvider::TextureId i_textureId)
{
	if ( const TextureProvider::Texture* texture = i_textureProvider.FindTextureById(i_textureId) )
	{
		return texture;
	}
	else
	{
		// #fixme: db assert
		std::cerr << "Texture " << i_textureId << " Not Found" << std::endl;
		assert(false);
	}
	return nullptr;
}
}

void Renderer2D::SetTextureMgr(const TextureMgr& i_textureProvider)
{
	m_textureProvider = &i_textureProvider;
}

void Renderer2D::RenderTexture(TextureProvider::TextureId i_textureId, const Pos& i_pos) const
{
	if ( const TextureProvider::Texture* texture = FindTextureByIdOrAssert(*m_textureProvider, i_textureId) )
	{
		m_renderer.RenderTexture(*texture, sdl::Pos { i_pos.x(), i_pos.y() });
	}
}

void Renderer2D::RenderTexture(TextureProvider::TextureId i_textureId, const Rect& i_rect) const
{
	if ( const TextureProvider::Texture* texture = FindTextureByIdOrAssert(*m_textureProvider, i_textureId) )
	{
		m_renderer.RenderTexture(*texture, sdl::Rect { i_rect.pos.x(), i_rect.pos.y(), i_rect.size.x(), i_rect.size.y() });
	}
}

void Renderer2D::RenderTexture(TextureProvider::TextureId i_textureId, const Rect& i_screenRect, const Rect& i_textureRect) const
{
	if ( const TextureProvider::Texture* texture = FindTextureByIdOrAssert(*m_textureProvider, i_textureId) )
	{
		m_renderer.RenderTexture(*texture,
								 sdl::Rect { i_screenRect.pos.x(), i_screenRect.pos.y(), i_screenRect.size.x(), i_screenRect.size.y() },
								 sdl::Rect { i_textureRect.pos.x(), i_textureRect.pos.y(), i_textureRect.size.x(), i_textureRect.size.y() }
		);
	}
}

}
}
