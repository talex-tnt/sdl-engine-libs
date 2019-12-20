#pragma once
#include "Types.h"

#include <functional>
#include <array>

struct SDL_Renderer;
namespace sdl
{
class Window;
class Texture;

class Renderer
{
public:
	using Color = sdl::Color;
	using Scale = sdl::Scale;

	Renderer(sdl::Window& i_window);
	~Renderer();
	
	bool Init();

	void BeginRendering();
	void EndRendering();

	void RenderEmptyRect(int xPos, int yPos, int width, int height) const;
	void RenderEmptyRect(const Rect& rect) const;
	void RenderEmptyRects(const Rect* rects, std::size_t count) const;

	void RenderFilledRect(int xPos, int yPos, int width, int height) const;
	void RenderFilledRect(const Rect& rect) const;
	void RenderFilledRects(const Rect* rects, std::size_t count) const;
	
	void RenderPoint(int posX, int posY) const;
	void RenderPoint(const Pos& pos) const;
	
	void RenderLine(int startX, int startY, int endX, int endY) const;
	void RenderLine(const Pos& start, const Pos& end) const;
	void RenderLines(const Pos* lines, std::size_t count) const;

	void SetRenderColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a);
	void SetRenderColor(const Color& i_color);
	Color GetRenderColor() const;

	void SetScale(const Scale& i_scale);
	Scale GetScale() const;

	std::unique_ptr<Texture> CreateTexture(const std::string& i_path) const;
	void RenderTexture(const Texture& i_texture, const Rect& i_rect) const;
	void RenderTexture(const Texture& i_texture, const Rect& i_screenRect, const Rect& i_textureRect) const;
	void RenderTexture(const Texture& i_texture, const Pos& i_pos) const;
	
public:
	Renderer(const Renderer&) = delete;
	Renderer(Renderer&&) = delete;

	Renderer& operator=(const Renderer&) = delete;
	Renderer& operator=(Renderer&&) = delete;

private:

private:
	using RendererUnPtr = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>;
	RendererUnPtr m_renderer;
};
}