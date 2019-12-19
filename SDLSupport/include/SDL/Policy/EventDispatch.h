#pragma once

union SDL_Event;

namespace app
{
namespace events
{
class IEventHandler;
}
}
namespace sdl
{
namespace policy
{
class EventDispatch
{
public:
	void ProcessAndDispatch(app::events::IEventHandler& i_eventHandler);

protected:
	EventDispatch() = default;
	~EventDispatch() = default;

	EventDispatch(const EventDispatch&) = delete;
	EventDispatch(EventDispatch&&) = delete;

	EventDispatch& operator=(const EventDispatch&) = delete;
	EventDispatch& operator=(EventDispatch&&) = delete;


private:
	void OnEvent(app::events::IEventHandler& i_eventHandler, const SDL_Event& e);

private:
	//
};
}
}