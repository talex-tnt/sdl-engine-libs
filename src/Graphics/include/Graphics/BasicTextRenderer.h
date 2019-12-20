#pragma once
#include <string>

namespace graphics
{
template<
	class TextureAccessPolicy,
	class GlyphsAccessPolicy,
	class TextureRenderPolicy
>
class BasicTextRenderer
	: public TextureAccessPolicy
	, public GlyphsAccessPolicy
	, public TextureRenderPolicy
{
public:
	BasicTextRenderer() = default;
	~BasicTextRenderer() = default;
	struct Pos { float x, y; };
	struct Rect { float x, y, w, h; };

	bool Init(const std::string& i_texturePath, const std::string& i_configFilePath);
	void RenderText(const std::string& i_text, const Pos& i_pos, float i_fontSize) const;
	Rect ComputeTextRect(const std::string& i_text, float i_fontSize) const;

public:
	BasicTextRenderer(const BasicTextRenderer&) = delete;
	BasicTextRenderer(BasicTextRenderer&&) = delete;

	BasicTextRenderer& operator=(const BasicTextRenderer&) = delete;
	BasicTextRenderer& operator=(BasicTextRenderer&&) = delete;

private:
};

}
