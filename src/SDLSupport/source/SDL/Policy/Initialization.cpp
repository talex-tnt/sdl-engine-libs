#include <SDL/Policy/Initialization.h>
#include "../Window.h"

#if defined(__clang__)
#	pragma clang diagnostic push
#	pragma clang diagnostic ignored "-Wpragma-pack"
#endif
#	include <SDL.h>
#if defined(__clang__)
#	pragma clang diagnostic pop
#endif

#include <iostream>

namespace sdl
{

namespace policy
{
Initialization::Initialization()
{ };

Initialization::~Initialization()
{
	SDL_Quit();
}

bool Initialization::Init(const std::string& i_windowTitle, std::int32_t i_width, std::int32_t i_height)
{
	bool initialized = false;
	if ( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		std::cerr << "SDL_Init Error: " << SDL_GetError();
	}
	else
	{
		m_window = std::make_unique<sdl::Window>(i_windowTitle, i_width, i_height);

		if ( m_window && m_window->IsInitialized() )
		{
			initialized = true;
		}
		else
		{
			std::cerr << SDL_GetError();
		}
	}
	return initialized;
}



sdl::Window* Initialization::GetWindow()
{
	return m_window.get();
}

const sdl::Window* Initialization::GetWindow() const
{
	return m_window.get();
}

}
}