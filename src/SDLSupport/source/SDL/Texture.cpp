#include <SDL/Texture.h>

#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wpragma-pack"
#endif
#	include <SDL.h>
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif

#include <assert.h>
#include <iostream>


namespace
{

SDL_Texture* LoadTexture(SDL_Renderer& i_renderer, SDL_Surface& i_surface)
{
	SDL_Texture* newTexture = nullptr;
	newTexture = SDL_CreateTextureFromSurface(&i_renderer, &i_surface);
	if ( !newTexture )
	{
		std::cerr << "Unable to create texture: " << SDL_GetError() << std::endl;;
	}
	return newTexture;
}

}

namespace sdl
{

Texture::Texture(SDL_Renderer& i_renderer, SDL_Surface& i_surface)
	: m_texture(LoadTexture(i_renderer, i_surface),
	[] (SDL_Texture* tex) { SDL_DestroyTexture(tex); })
{
	if ( m_texture )
	{
		SDL_QueryTexture(m_texture.get(), nullptr, nullptr, &m_size.w, &m_size.h);
	}
	assert(m_texture); // #fixme use db assert
}
Texture::~Texture() = default;

void Texture::Render(SDL_Renderer& i_renderer, int x, int y) const
{
	SDL_Rect dst {x, y, m_size.w, m_size.h };
	SDL_RenderCopy(&i_renderer, m_texture.get(), nullptr, &dst);
}

void Texture::Render(SDL_Renderer& i_renderer, int x, int y, int w, int h) const
{
	SDL_Rect dst { x, y, w, h };
	SDL_RenderCopy(&i_renderer, m_texture.get(), nullptr, &dst);
}

void Texture::Render(SDL_Renderer& i_renderer, const Rect& i_screenRect, const Rect& i_textureRect) const
{
	static_assert( sizeof(Rect::x) == sizeof(SDL_Rect::x), "Size Type mismatch" );
	static_assert( sizeof(Rect::y) == sizeof(SDL_Rect::y), "Size Type mismatch" );
	static_assert( sizeof(Rect::w) == sizeof(SDL_Rect::w), "Size Type mismatch" );
	static_assert( sizeof(Rect::h) == sizeof(SDL_Rect::h), "Size Type mismatch" );
	const SDL_Rect& dst = reinterpret_cast< const SDL_Rect& >( i_screenRect );
	const SDL_Rect& src = reinterpret_cast< const SDL_Rect& >( i_textureRect );
	SDL_RenderCopy(&i_renderer, m_texture.get(), &src, &dst);
}

const sdl::Size& Texture::GetSize() const
{
	return m_size;
}

}
