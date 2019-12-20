#include <SDL/Policy/EventDispatch.h>
#include <AppEvents/IEventHandler.h>

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
void EventDispatch::ProcessAndDispatch(app::events::IEventHandler& i_eventHandler)
{
	i_eventHandler.OnEventDispatchStarted();
	SDL_Event e;
	while ( SDL_PollEvent(&e) != 0 )
	{
		OnEvent(i_eventHandler, e);
	}
}

void EventDispatch::OnEvent(app::events::IEventHandler& i_eventHandler, const SDL_Event& e)
{
	switch ( e.type )
	{
	case SDL_QUIT:
	{
		i_eventHandler.OnEvent(app::events::EventType::k_quit);
	} break;
	case SDL_WINDOWEVENT_FOCUS_LOST:
	{
		i_eventHandler.OnEvent(app::events::EventType::k_focus_lost);
	} break;
	case SDL_KEYDOWN:
	case SDL_KEYUP:
	{
		using KeyEvent = app::events::KeyEvent;
		KeyEvent::KeycodeType key = KeyEvent::KeycodeType::k_down; // Fixme: use optional
		switch ( e.key.keysym.sym )
		{
		case SDLK_LEFT:
		{
			key = KeyEvent::KeycodeType::k_left;
		} break;
		case SDLK_RIGHT:
		{
			key = KeyEvent::KeycodeType::k_right;
		} break;
		case SDLK_UP:
		{
			key = KeyEvent::KeycodeType::k_up;
		} break;
		case SDLK_DOWN:
		{
			key = KeyEvent::KeycodeType::k_down;
		} break;
		case SDLK_SPACE:
		{
			key = KeyEvent::KeycodeType::k_space;
		} break;

		case SDLK_ESCAPE:
		{
			key = KeyEvent::KeycodeType::k_esc;
		} break;
		}
		i_eventHandler.OnEvent(KeyEvent(key, 
										e.type == SDL_KEYDOWN ? 
										KeyEvent::EventState::k_down : 
										KeyEvent::EventState::k_up));
	} break;
	}
}
}
}