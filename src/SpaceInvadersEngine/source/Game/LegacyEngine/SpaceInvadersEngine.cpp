#include <Game/LegacyEngine/SpaceInvadersEngine.h>
#include "SDLEngine.h"

#include <Game/Graphics/Renderer2D.h>
#include <Game/Graphics/TextureMgr.h>
#include <Game/Graphics/TextRenderer.h>
#include <Game/Graphics/Display.h>
#include <Game/Graphics/SpriteAtlasProvider.h>
#include <Game/Graphics/SpriteRenderer.h>
#include "../Base/Assets/Sprites.h"
#include <AppUtils/Enum.h>

const std::size_t SpaceInvadersEngine::CanvasWidth   = 640;
const std::size_t SpaceInvadersEngine::CanvasHeight  = 480;
const std::size_t SpaceInvadersEngine::SpriteSize    = 32;
const std::size_t SpaceInvadersEngine::FontWidth     = 8;
const std::size_t SpaceInvadersEngine::FontRowHeight = 18;

SpaceInvadersEngine::SpaceInvadersEngine()
	: m_engine(std::make_unique<SDLEngine>("Space Invaders", CanvasWidth, CanvasHeight))
{
	using Sprites = game::assets::Sprites;
	using Enum = app::utils::Enum;
	Enum::SetArrayValue(m_sprites, Sprite::Player, m_engine->GetAtlasProvider().GetSpriteAtlas(Sprites::Atlases::k_invaders)->GetSprite(Sprites::k_ship));
	Enum::SetArrayValue(m_sprites, Sprite::Enemy1, m_engine->GetAtlasProvider().GetSpriteAtlas(Sprites::Atlases::k_invaders)->GetSprite(Sprites::k_invader01));
	Enum::SetArrayValue(m_sprites, Sprite::Enemy2, m_engine->GetAtlasProvider().GetSpriteAtlas(Sprites::Atlases::k_invaders)->GetSprite(Sprites::k_invader02));
	Enum::SetArrayValue(m_sprites, Sprite::Rocket, m_engine->GetAtlasProvider().GetSpriteAtlas(Sprites::Atlases::k_invaders)->GetSprite(Sprites::k_projectile));
	Enum::SetArrayValue(m_sprites, Sprite::Bomb, m_engine->GetAtlasProvider().GetSpriteAtlas(Sprites::Atlases::k_invaders)->GetSprite(Sprites::k_explosion));
}

SpaceInvadersEngine::~SpaceInvadersEngine()
{
}

bool SpaceInvadersEngine::Run()
{
	return m_engine->Run();
}

void SpaceInvadersEngine::RenderSprite(Sprite sprite, int x, int y) const
{
	using Rect = game::graphics::SpriteRenderer::Rect;
	using Enum = app::utils::Enum;
	const SpriteT& spr = Enum::GetArrayValue(m_sprites, sprite);
	SpriteT::Size spriteSize{ static_cast<float>(SpriteSize),  static_cast<float>(SpriteSize)};
	SpriteT::Pos pos{ static_cast<float>(x), static_cast<float>(y) };
	if (spr.m_rect.size.x() < spr.m_rect.size.y())
	{
		const float ratio = spr.m_rect.size.x() / spr.m_rect.size.y();
		spriteSize[0] *= ratio;
		pos[0] += (SpriteSize - spriteSize[0]) * 0.5f;
	}
	else
	{
		const float ratio = spr.m_rect.size.y() / spr.m_rect.size.x();
		spriteSize[1] *= ratio;
		pos[1] += (SpriteSize - spriteSize[1]) * 0.5f;

	}
	const Rect rect{ pos , spriteSize };
	m_engine->GetSpriteRenderer().Render(rect, spr);
}

void SpaceInvadersEngine::RenderText(const char* message, int x, int y) const
{
	using Pos = game::graphics::TextRenderer::Pos;
	Pos pos{ static_cast<float>(x), static_cast<float>(y) };
	m_engine->GetTextRenderer().RenderText(std::string(message), pos, FontRowHeight);
}

double SpaceInvadersEngine::GetElapsedSeconds() const
{
	return m_engine->GetElapsedSeconds().count();
}

SpaceInvadersEngine::Size SpaceInvadersEngine::GetTextSize(const char* message) const
{
	using Rect = game::graphics::TextRenderer::Rect;
	const Rect& rect = m_engine->GetTextRenderer().ComputeTextRect(std::string(message), FontRowHeight);
	return Size{ static_cast<std::size_t>(std::round(rect.size.x())) , static_cast<std::size_t>(std::round(rect.size.y())) };
}

SpaceInvadersEngine::PlayerInput SpaceInvadersEngine::GetPlayerInput() const
{
	PlayerInput input;
	input.left = m_engine->GetInput().left;
	input.right = m_engine->GetInput().right;
	input.fire = m_engine->GetInput().space;
	return input;
}