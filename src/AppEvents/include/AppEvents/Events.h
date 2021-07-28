#pragma once
#include <memory>
#include <string>
#include <iostream>
#include <AppUtils/Enum.h>

namespace app
{
namespace events
{

enum class EventType
{
	k_quit,
	k_focus_lost
};

class KeyEvent
{
public:
	enum class KeycodeType
	{
		k_up, k_down, k_left, k_right, k_esc, k_space
	};
	enum class EventState
	{
		k_up, k_down
	};

	KeyEvent(KeycodeType i_keycode, EventState i_state)
		: m_keycode(i_keycode)
		, m_state(i_state)
	{ }
	KeycodeType GetKeycode() const { return m_keycode; }
	EventState GetState() const { return m_state; }

private:
	KeycodeType m_keycode;
	EventState m_state;
};

inline std::ostream& operator<<(std::ostream& o_stream, const KeyEvent& i_keyDownEvent)
{
	o_stream << std::string("KeyDownEvent: ") << utils::Enum::GetValue(i_keyDownEvent.GetKeycode());
	return o_stream;
}
}
}