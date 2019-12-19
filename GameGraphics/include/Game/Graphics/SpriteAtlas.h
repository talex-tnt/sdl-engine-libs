#pragma once
#include <string>
#include "TextureMgr.h"

namespace graphics
{
class SpriteAtlasConfig;
}

namespace game
{
namespace graphics
{
class TextureMgr;

class SpriteAtlas
{
public:
	struct Sprite
	{
		using Pos = Math::Vec2f;
		using Size = Math::Vec2f;
		struct Rect
		{
			Pos pos; Size size;
		};
		Rect m_rect;
		TextureMgr::TextureId m_textureId;
	};

	Sprite GetSprite(const std::string& i_name) const;

protected:
	bool Load(TextureMgr& i_textureMgr, const std::string& i_configFilePath);
	SpriteAtlas();
	~SpriteAtlas();

	SpriteAtlas(const SpriteAtlas&) = delete;
	SpriteAtlas(SpriteAtlas&&) = delete;

	SpriteAtlas& operator=(const SpriteAtlas&) = delete;
	SpriteAtlas& operator=(SpriteAtlas&&) = delete;

private:
	using Config = ::graphics::SpriteAtlasConfig;
	std::unique_ptr<Config> m_config;
	TextureMgr::TextureId m_textureId;
	TextureMgr::Size m_textureSize;
};

}
}