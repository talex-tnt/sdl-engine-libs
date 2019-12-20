#include <SDL/TextureFactory.h>
#include <SDL/Texture.h>

#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wpragma-pack"
#endif
#	include <SDL_render.h>
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif

#include <assert.h>
#include <iostream>


namespace sdl
{

TextureFactory::TextureFactory(SDL_Renderer& i_renderer)
	: m_renderer(i_renderer)
{ }

TextureFactory::~TextureFactory() = default;

std::unique_ptr<sdl::Texture> TextureFactory::CreateTexture(const std::string& i_path) const
{
	using SurfacePtr = std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface*)>>;
	SurfacePtr surface(SDL_LoadBMP(i_path.c_str()), [] (SDL_Surface* s) { SDL_FreeSurface(s); });
	return std::make_unique<sdl::Texture>(m_renderer, *surface);
}

void TextureFactory::RenderTexture(const Texture& i_texture, const Pos& i_pos) const
{
	i_texture.Render(m_renderer, i_pos.x, i_pos.y);
}

void TextureFactory::RenderTexture(const Texture& i_texture, const Rect& i_rect) const
{
	i_texture.Render(m_renderer, i_rect.x, i_rect.y, i_rect.w, i_rect.h);
}

void TextureFactory::RenderTexture(const Texture& i_texture, const Rect& i_screenRect, const Rect& i_textureRect) const
{
	i_texture.Render(m_renderer, i_screenRect, i_textureRect);

}

}
