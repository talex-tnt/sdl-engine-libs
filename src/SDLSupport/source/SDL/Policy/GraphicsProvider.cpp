#include <SDL/Policy/GraphicsProvider.h>
#include <SDL/Policy/Initialization.h>

#include <SDL/Renderer.h>
#include <SDL/Display.h>
#include <SDL/TextureFactory.h>

#include "../Window.h"

#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wpragma-pack"
#endif
#	include <SDL_render.h>
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif

#include <iostream>
#include <assert.h>

namespace sdl
{
namespace policy
{

GraphicsProvider::GraphicsProvider() = default;
GraphicsProvider::~GraphicsProvider() = default;

void GraphicsProvider::InitGraphics(Initialization& i_windowProvider)
{
	Initialization::WindowT* window = i_windowProvider.GetWindow();
	if ( window )
	{
		m_renderer = std::make_unique<RendererT>(*window);
		SDL_Window* sdlW = window->GetSDLWindow();
		SDL_Renderer* renderer = SDL_GetRenderer(sdlW);
		assert(renderer);
		if ( renderer )
		{
			m_display = std::make_unique<DisplayT>(*renderer, window->GetDisplayIndex());
			m_textureFactory = std::make_unique<TextureFactoryT>(*renderer);
		}
	}
}

const GraphicsProvider::RendererT* GraphicsProvider::GetRenderer() const
{
	return m_renderer.get();
}

GraphicsProvider::RendererT* GraphicsProvider::GetRenderer()
{
	return m_renderer.get();
}

const sdl::policy::GraphicsProvider::DisplayT* GraphicsProvider::GetDisplay() const
{
	assert(m_display);
	return m_display.get();
}

sdl::policy::GraphicsProvider::TextureFactoryT* GraphicsProvider::GetTextureFactory()
{
	assert(m_textureFactory);
	return m_textureFactory.get();
}

const sdl::policy::GraphicsProvider::TextureFactoryT* GraphicsProvider::GetTextureFactory() const
{
	assert(m_textureFactory);
	return m_textureFactory.get();
}

}
}