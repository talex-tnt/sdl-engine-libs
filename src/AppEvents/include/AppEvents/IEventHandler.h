#pragma once
#include "Events.h"

namespace app
{
namespace events
{
class IEventHandler
{
public:
	virtual ~IEventHandler() = default;
	virtual void OnEventDispatchStarted() = 0;
	virtual void OnEvent(events::EventType i_eventType) = 0;
	virtual void OnEvent(const events::KeyEvent& i_event) = 0;
};
}
}