#pragma once

#include <SDL/Policy/Initialization.h>
#include <SDL/Policy/EventDispatch.h>
#include <SDL/Policy/GraphicsProvider.h>
#include <SDL/Timer.h>
#include <AppEvents/IEventHandler.h>

namespace game
{
	namespace graphics
	{
		class Renderer2D;
		class Display;
		class TextRenderer;
		class SpriteRenderer;
		class TextureMgr;
		class SpriteAtlasMgr;
		class SpriteAtlasProvider;
	}
}

// pretty rough draft..
class SDLEngine 
	: private sdl::policy::Initialization
	, private sdl::policy::EventDispatch
	, private app::events::IEventHandler
	, private sdl::policy::GraphicsProvider
{
public:
	bool Run();
	
	SDLEngine(const std::string& i_windowTitle, std::int32_t i_width, std::int32_t i_height);
	~SDLEngine();

	struct Input
	{
		bool space, left, right, up, down;
	} m_input;

public:
	using RendererT = game::graphics::Renderer2D;
	using TextRendererT = game::graphics::TextRenderer;
	using SpriteRendererT = game::graphics::SpriteRenderer;
	using TextureMgrT = game::graphics::TextureMgr;
	using DisplayT = game::graphics::Display;
	using SpriteAtlasProviderT = game::graphics::SpriteAtlasProvider;
	using SpriteAtlasMgrT = game::graphics::SpriteAtlasMgr;
	using TimerT = sdl::Timer;
	using SecT = sdl::Timer::SecT;

	const RendererT& GetRenderer() const { return *m_renderer; }
	const TextRendererT& GetTextRenderer() const { return *m_textRenderer; }
	const SpriteRendererT& GetSpriteRenderer() const { return *m_spriteRenderer; }
	const SpriteAtlasProviderT& GetAtlasProvider() const;
	const DisplayT& GetDisplay() const { return *m_display; }
	const Input& GetInput() const;
	const SecT GetElapsedSeconds() const { return m_timer.GetElapsed(); }

public:
	void OnEventDispatchStarted() override;
	void OnEvent(app::events::EventType i_eventType) override;
	void OnEvent(const app::events::KeyEvent& i_event) override;

private:
	std::unique_ptr<RendererT> m_renderer;
	std::unique_ptr<TextureMgrT> m_textureMgr;
	std::unique_ptr<SpriteAtlasMgrT> m_spriteAtlasMgr;
	std::unique_ptr<DisplayT> m_display;
	std::unique_ptr<TextRendererT> m_textRenderer;
	std::unique_ptr<SpriteRendererT> m_spriteRenderer;
	sdl::Timer m_timer;

	bool m_isRunning;
};

