#include <SDL/Display.h>

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


namespace sdl
{

Display::Display(SDL_Renderer& i_renderer, int i_displayIndex) 
	: m_renderer(i_renderer), m_displayIndex(i_displayIndex)
{

}

sdl::Display::Size Display::GetSize() const
{
	int w, h;
	SDL_GetRendererOutputSize(&m_renderer, &w, &h);
	return Size {
		static_cast< Size::value_t >( w ), 
		static_cast< Size::value_t >( h ) 
	};
}

int Display::GetRefreshRate() const
{
	SDL_DisplayMode mode;
	if ( SDL_GetCurrentDisplayMode(m_displayIndex, &mode) != 0 )
	{
		SDL_Log("Could not get display mode for video display #%d: %s", m_displayIndex, SDL_GetError());
		return 0;
	}
	return mode.refresh_rate;
}

}
