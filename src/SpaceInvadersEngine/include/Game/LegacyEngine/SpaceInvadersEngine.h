#pragma once
#include <memory>
#include <array>

#include <Game/Graphics/SpriteAtlasProvider.h>

class SDLEngine;
struct SpaceInvadersEngine 
{
	static const int CanvasWidth   = 640;
	static const int CanvasHeight  = 480;
	static const int SpriteSize    = 32;
	static const int FontWidth     = 8;
	static const int FontRowHeight = 18;
	
	struct PlayerInput
	{
		bool fire, left, right;
	};

	enum class Sprite : int
	{
		Player,
		Bomb,
		Rocket,
		Enemy1,
		Enemy2,
	};

	bool Run();
	void RenderSprite(Sprite sprite, int x, int y) const;
	void RenderText(const char* message, int x, int y) const;
	struct Size { std::size_t w, h; };
	PlayerInput GetPlayerInput() const;
	double GetElapsedSeconds() const;
	Size GetTextSize(const char* message) const;

	SpaceInvadersEngine();
	~SpaceInvadersEngine();

private:
	using SpriteT = game::graphics::SpriteAtlas::Sprite;

private:
	std::unique_ptr<SDLEngine> m_engine;
	std::array<SpriteT, 5> m_sprites;
};

