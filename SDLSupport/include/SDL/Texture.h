#pragma once
#include "Types.h"

#include <memory>
#include <functional>

struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Surface;

namespace sdl
{
class Renderer;
class Texture
{
public:
	Texture(SDL_Renderer& i_renderer, SDL_Surface& i_surface);
	~Texture();

	void Render(SDL_Renderer& i_renderer, int x, int y) const;
	void Render(SDL_Renderer& i_renderer, int x, int y, int w, int h) const;
	void Render(SDL_Renderer& i_renderer, const Rect& i_screenRect, const Rect& i_textureRect) const;

	const Size& GetSize() const;
public:
	Texture(const Texture&) = delete;
	Texture(Texture&&) = delete;

	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&&) = delete;

private:
	using TextureUnPtr = std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture*)>>;
	TextureUnPtr m_texture;
	Size m_size;
};
}