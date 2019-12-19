#include <Game/Graphics/Display.h>
#include <SDL/Display.h>

namespace game
{
namespace graphics
{
Display::Display(const sdl::Display& i_display) : m_display(i_display)
{ }

Display::Size Display::GetSize() const
{
	const sdl::Display::Size sz = m_display.GetSize();
	return Display::Size(static_cast< Display::Size::value_type>(sz.width), 
						 static_cast< Display::Size::value_type >(sz.height));
}

int Display::GetRefreshRate() const
{
	return m_display.GetRefreshRate();
}

}
}
