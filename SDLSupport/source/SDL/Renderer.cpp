#include <SDL/Renderer.h>
#include <SDL/Texture.h>
#include "Window.h"

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
static const int k_index = -1;
static const std::size_t k_flags = 
	//SDL_RENDERER_PRESENTVSYNC | // disabled for simplicity 
	SDL_RENDERER_ACCELERATED;

Renderer::Renderer(sdl::Window& i_window)
	: m_renderer(!i_window.GetSDLWindow() ? nullptr :
		SDL_CreateRenderer(i_window.GetSDLWindow(), k_index, k_flags),
		[] (SDL_Renderer* renderer) { SDL_DestroyRenderer(renderer); })
{
	assert(m_renderer);
	Init();
}

Renderer::~Renderer() = default;

bool Renderer::Init()
{
	if ( !m_renderer )
	{
		std::cerr << "Could Not Create the SDL_Renderer" << SDL_GetError() << std::endl;
	}
	SDL_SetRenderDrawColor(m_renderer.get(), 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(m_renderer.get());
	SDL_RenderPresent(m_renderer.get());

	return m_renderer != nullptr;
}

void Renderer::BeginRendering()
{
	SDL_RenderClear(m_renderer.get());
}

void Renderer::EndRendering()
{
	SDL_RenderPresent(m_renderer.get());
}

void Renderer::RenderLine(int startX, int startY, int endX, int endY) const
{
	SDL_RenderDrawLine(m_renderer.get(), startX, startY, endX, endY);
}

void Renderer::RenderLines(const Pos* lines, std::size_t count) const
{
	const SDL_Point * sdlLines = reinterpret_cast< const SDL_Point* >( lines );
	SDL_RenderDrawLines(m_renderer.get(), sdlLines, static_cast<int>(count));
}

void Renderer::RenderLine(const Pos& start, const Pos& end) const
{
	RenderLine(start.x, start.y, end.x, end.y);
}

void Renderer::RenderEmptyRect(int xPos, int yPos, int width, int height) const
{
	const SDL_Rect rect { xPos, yPos, width, height };
	SDL_RenderDrawRect(m_renderer.get(), &rect);
}

void Renderer::RenderEmptyRect(const Rect& rect) const
{
	RenderEmptyRect(rect.x, rect.y, rect.w, rect.h);
}

void Renderer::RenderEmptyRects(const Rect* rects, std::size_t count) const
{
	const SDL_Rect * sdlRects = reinterpret_cast< const SDL_Rect* >( rects );
	SDL_RenderDrawRects(m_renderer.get(), sdlRects, static_cast< int >( count ));
}

void Renderer::RenderFilledRects(const Rect* rects, std::size_t count) const
{
	const SDL_Rect * sdlRects = reinterpret_cast< const SDL_Rect* >( rects );
	SDL_RenderFillRects(m_renderer.get(), sdlRects, static_cast< int >( count ));
}

void Renderer::RenderFilledRect(int xPos, int yPos, int width, int height) const
{
	const SDL_Rect rect { xPos, yPos, width, height };
	SDL_RenderFillRect(m_renderer.get(), &rect);
}

void Renderer::RenderFilledRect(const Rect& rect) const
{
	RenderFilledRect(rect.x, rect.y, rect.w, rect.h);
}

void Renderer::RenderPoint(int posX, int posY) const
{
	SDL_RenderDrawPoint(m_renderer.get(), posX, posY);
}

void Renderer::RenderPoint(const Pos& pos) const
{
	RenderPoint(pos.x, pos.y);
}

void Renderer::SetRenderColor(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a)
{
	SDL_SetRenderDrawColor(m_renderer.get(), r, g, b, a);
}

void Renderer::SetRenderColor(const Color& i_color)
{
	SetRenderColor(i_color.r, i_color.g, i_color.b, i_color.a);
}


Renderer::Color Renderer::GetRenderColor() const
{
	Color c;
	SDL_GetRenderDrawColor(m_renderer.get(), &c.r, &c.g, &c.b, &c.a);
	return c;
}

void Renderer::SetScale(const Scale& i_scale)
{
	SDL_RenderSetScale(m_renderer.get(), i_scale.x, i_scale.y);
}

Renderer::Scale Renderer::GetScale() const
{
	Scale s;
	SDL_RenderGetScale(m_renderer.get(), &s.x, &s.y);
	return s;
} 

std::unique_ptr<sdl::Texture> Renderer::CreateTexture(const std::string& i_path) const
{
	using SurfacePtr = std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface*)>>;
	SurfacePtr surface(SDL_LoadBMP(i_path.c_str()), [] (SDL_Surface* s) { SDL_FreeSurface(s); });
	return std::make_unique<sdl::Texture>(*m_renderer, *surface);
}

void Renderer::RenderTexture(const Texture& i_texture, const Pos& i_pos) const
{
	i_texture.Render(*m_renderer, i_pos.x, i_pos.y);
}

void Renderer::RenderTexture(const Texture& i_texture, const Rect& i_rect) const
{
	i_texture.Render(*m_renderer, i_rect.x, i_rect.y, i_rect.w, i_rect.h);
}

void Renderer::RenderTexture(const Texture& i_texture, const Rect& i_screenRect, const Rect& i_textureRect) const
{
	i_texture.Render(*m_renderer, i_screenRect, i_textureRect);

}

}
