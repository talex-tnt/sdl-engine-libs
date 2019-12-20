#include <Game/Graphics/TextRenderer.h>
#include <Game/Graphics/Renderer2D.h>
#include <Game/Graphics/TextureMgr.h>

#include <assert.h>

namespace
{ 
// #fixme: Renderer2D should accept floating points as well and round by itselft eventually
template<class Rect>
game::graphics::Renderer2D::Rect RoundRect(Rect r)
{
	using Pos = game::graphics::Renderer2D::Pos;
	using Size = game::graphics::Renderer2D::Size;
	return game::graphics::Renderer2D::Rect {
		Pos{ 
		static_cast<Pos::value_type>(std::round(r.x)),  
		static_cast<Pos::value_type >(std::round(r.y))},
		Size{ 
		static_cast<Size::value_type>(std::round(r.w)),  
		static_cast<Size::value_type >(std::round(r.h))} };
}
}

namespace game
{
namespace graphics
{
struct TextRenderer::TextureAccessPolicy
{
	using TextureSize = graphics::Renderer2D::Size;
	bool Load(const std::string& i_texturePath)
	{
		assert(m_textMgr);
		m_texture = m_textMgr->CreateTexture(i_texturePath);
		m_textMgr->GetTextureSize(m_texture, m_textureSize);
		return true;
	}
	graphics::TextureProvider::TextureId GetTexture() const { return m_texture; }
	TextureSize GetTextureSize() const { return m_textureSize; }
	//
	graphics::TextureMgr* m_textMgr;
	graphics::TextureProvider::TextureId m_texture;
	TextureSize m_textureSize;
};

struct TextRenderer::TextureRenderPolicy
{
	struct Rect { using ValueT = float; ValueT x, y, w, h; };
	using Pos = Math::Vec2u;
	using Size = Math::Vec2u;
	void RenderTexture(graphics::TextureProvider::TextureId i_textureId, const Rect& i_screenRect, const Rect& i_textureRect) const
	{
		m_renderer->RenderTexture(i_textureId, RoundRect(i_screenRect), RoundRect(i_textureRect));
	}
	template<class PosT, class SizeT>
	Rect MakeRect(PosT x, PosT y, SizeT w, SizeT h) const
	{
		return Rect { 
			static_cast< Rect::ValueT >( x ), 
			static_cast< Rect::ValueT >( y ), 
			static_cast< Rect::ValueT >( w ), 
			static_cast< Rect::ValueT >( h ) 
		};
	}
	graphics::Renderer2D* m_renderer;
};


TextRenderer::TextRenderer(graphics::Renderer2D& i_renderer, graphics::TextureMgr& i_textureProvider)
	: m_textRenderer(std::make_unique<TextRendererT>())
{
	m_textRenderer->m_textMgr = &i_textureProvider;
	m_textRenderer->m_renderer = &i_renderer;
}

TextRenderer::~TextRenderer() = default;

bool TextRenderer::Init(const Font& i_font)
{
	return m_textRenderer->Init(i_font.texturePath, i_font.configPath);
}

void TextRenderer::RenderText(const std::string& i_text, const Pos& i_pos, float i_fontSize) const
{
	m_textRenderer->RenderText(i_text, TextRendererT::Pos { i_pos.x(), i_pos.y() }, i_fontSize);
}

TextRenderer::Rect TextRenderer::ComputeTextRect(const std::string& i_text, float i_fontSize) const
{
	TextRendererT::Rect r = m_textRenderer->ComputeTextRect(i_text, i_fontSize);
	return Rect{ Pos{r.x, r.y}, Size{r.w, r.h} };
}

}
}

