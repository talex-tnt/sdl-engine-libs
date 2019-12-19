#include "BasicTextRenderer.h"

namespace graphics
{

template<
	class TextureAccessPolicy,
	class GlyphsAccessPolicy,
	class TextureRenderPolicy
>
inline bool BasicTextRenderer<
	TextureAccessPolicy, 
	GlyphsAccessPolicy, 
	TextureRenderPolicy
>
::Init(const std::string& i_texturePath, const std::string& i_configFilePath)
{
	if ( TextureAccessPolicy::Load(i_texturePath) )
	{
		return GlyphsAccessPolicy::Load(i_configFilePath);
	}
	return false;
}


template<
	class TextureAccessPolicy,
	class GlyphsAccessPolicy,
	class TextureRenderPolicy
>
inline void BasicTextRenderer<
	TextureAccessPolicy, 
	GlyphsAccessPolicy, 
	TextureRenderPolicy
>
::RenderText(const std::string& i_text, const Pos& i_pos, float i_fontSize) const
{
	using RenderRect = typename TextureRenderPolicy::Rect;
	using GlyphsRects = typename GlyphsAccessPolicy::Rects;
	using TextureSize = typename TextureAccessPolicy::TextureSize;

	TextureSize textureSize = TextureAccessPolicy::GetTextureSize();
	const float sf = i_fontSize / GlyphsAccessPolicy::GetGlyphSize();
	Pos pos = i_pos;

	const GlyphsRects rects = GlyphsAccessPolicy::GetGlyphsRectsForText(i_text);
	for (auto& rect : rects)
	{
		const RenderRect screenRect = TextureRenderPolicy::MakeRect(pos.x, pos.y, rect.w*sf, rect.h*sf);
		RenderRect glyphRect = TextureRenderPolicy::MakeRect(rect.x, rect.y, rect.w, rect.h);
		glyphRect.y = textureSize.y() - glyphRect.y - glyphRect.h; // flip y coord
		TextureRenderPolicy::RenderTexture(TextureAccessPolicy::GetTexture(), screenRect, glyphRect);
		pos.x += screenRect.w;
	}
}


template<
	class TextureAccessPolicy,
	class GlyphsAccessPolicy,
	class TextureRenderPolicy
>
typename graphics::BasicTextRenderer<
	TextureAccessPolicy,
	GlyphsAccessPolicy,
	TextureRenderPolicy
>::Rect
graphics::BasicTextRenderer<
	TextureAccessPolicy,
	GlyphsAccessPolicy,
	TextureRenderPolicy
>::ComputeTextRect(const std::string& i_text, float i_fontSize) const
{
	using RenderRect = typename TextureRenderPolicy::Rect;
	using GlyphsRects = typename GlyphsAccessPolicy::Rects;
	using TextureSize = typename TextureAccessPolicy::TextureSize;

	Rect result{0.f, 0.f, 0.f, 0.f};
	TextureSize textureSize = TextureAccessPolicy::GetTextureSize();
	const float sf = i_fontSize / GlyphsAccessPolicy::GetGlyphSize();
	Pos pos{ 0.f , 0.f };
	const GlyphsRects rects = GlyphsAccessPolicy::GetGlyphsRectsForText(i_text);
	for (auto& rect : rects)
	{
		const RenderRect screenRect = TextureRenderPolicy::MakeRect(pos.x, pos.y, rect.w*sf, rect.h*sf);
		result.h = std::max(result.h, screenRect.h);
		result.w += screenRect.w;
	}
	return result;
}
}
