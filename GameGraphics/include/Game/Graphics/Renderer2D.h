#pragma once
#include "TextureProvider.h"
#include "Color.h"

#include <Math/Vector.h>

#include <memory>
#include <array>
#include <unordered_map>

namespace sdl
{
class Renderer;
}

namespace game
{
namespace graphics
{
class TextureMgr;
class Renderer2D
{
public:
	using Pos = Math::Vec2i;
	using Size = Math::Vec2i; 
	struct Rect 
	{ 
		Pos pos; Size size; 
	};

	bool Init();

	void BeginRendering();
	void EndRendering();
	
	void RenderLine(const Pos& start, const Pos& end) const;
	void RenderPoint(const Pos& pos) const;
	template<std::size_t N>
	void RenderLines(const std::array<Pos, N>& i_points) const;

	template<std::size_t N>
	void RenderFilledRects(const std::array<Rect, N>& i_rects) const;

	void SetRenderColor(const Color::RGBA& i_col);
	PushedColor PushColor(const Color::RGBA& i_col);

	void SetTextureMgr(const TextureMgr& i_textureProvider);
	void RenderTexture(TextureProvider::TextureId i_textureId, const Pos& i_pos) const;
	void RenderTexture(TextureProvider::TextureId i_textureId, const Rect& i_rect) const;
	void RenderTexture(TextureProvider::TextureId i_textureId, const Rect& i_screenRect, const Rect& i_textureRect) const;

public:
	using Renderer = sdl::Renderer;
public:
	Renderer2D(Renderer& i_renderer);
	~Renderer2D();

	Renderer2D(const Renderer2D&) = delete;
	Renderer2D(Renderer2D&&) = delete;

	Renderer2D& operator=(const Renderer2D&) = delete;
	Renderer2D& operator=(Renderer2D&&) = delete;

private:
	void RenderLines(const Pos* i_points, std::size_t count) const;
	void RenderFilledRects(const Rect* i_rects, std::size_t count) const;

private:
	Renderer& m_renderer;
	const TextureMgr* m_textureProvider;
};

}
}