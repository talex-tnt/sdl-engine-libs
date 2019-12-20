#pragma once
#include <Graphics/BasicTextRenderer-inl.h>
#include <Graphics/Glyphs.h>

#include <Math/Vector.h>
#include "Font.h"

#include <string>


namespace graphics
{
template<
	class TextureAccessPolicy,
	class GlyphsAccessPolicy,
	class TextureRenderPolicy
> 
class BasicTextRenderer;
}

namespace game
{
namespace graphics
{
class Renderer2D;
class TextureMgr;

class TextRenderer
{
public:
	using Pos = Math::Vec2f;
	using Size = Math::Vec2f;
	struct Rect { Pos pos; Size size; };

	TextRenderer(graphics::Renderer2D& i_renderer, graphics::TextureMgr& i_textureProvider);
	~TextRenderer();
	bool Init(const Font& i_font);
	void RenderText(const std::string& i_text, const Pos& i_pos, float i_fontSize) const;
	Rect ComputeTextRect(const std::string& i_text, float i_fontSize) const;

public:
	TextRenderer(const TextRenderer&) = delete;
	TextRenderer(TextRenderer&&) = delete;

	TextRenderer& operator=(const TextRenderer&) = delete;
	TextRenderer& operator=(TextRenderer&&) = delete;

private:
	struct TextureAccessPolicy;
	struct TextureRenderPolicy;
	using TextRendererT = ::graphics::BasicTextRenderer<
		TextureAccessPolicy,
		::graphics::Glyphs,
		TextureRenderPolicy>;
	std::unique_ptr<TextRendererT> m_textRenderer;
};

}
}

