#pragma once
#include "Types.h"

#include <functional>
#include <array>

struct SDL_Renderer;
namespace sdl
{
class Window;
class Texture;

class TextureFactory
{
public:
	TextureFactory(SDL_Renderer& i_renderer);
	~TextureFactory();
	
	std::unique_ptr<Texture> CreateTexture(const std::string& i_path) const;
	void RenderTexture(const Texture& i_texture, const Rect& i_rect) const;
	void RenderTexture(const Texture& i_texture, const Rect& i_screenRect, const Rect& i_textureRect) const;
	void RenderTexture(const Texture& i_texture, const Pos& i_pos) const;
	
public:
	TextureFactory(const TextureFactory&) = delete;
	TextureFactory(TextureFactory&&) = delete;

	TextureFactory& operator=(const TextureFactory&) = delete;
	TextureFactory& operator=(TextureFactory&&) = delete;

private:
	//
private:
	SDL_Renderer& m_renderer;
};
}