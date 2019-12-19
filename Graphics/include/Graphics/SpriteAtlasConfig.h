#pragma once
#include <string>
#include <map>

namespace graphics
{

class SpriteAtlasConfig
{
	public:
	SpriteAtlasConfig() = default;
	~SpriteAtlasConfig() = default;

	struct Rect { std::uint32_t x, y, w, h; };
	bool Load(const std::string& i_configFilePath);
	bool FindSpriteRect(const std::string& i_spriteName, SpriteAtlasConfig::Rect& o_rect) const;
	const std::string& GetTextureName() const;


	SpriteAtlasConfig(const SpriteAtlasConfig&) = delete;
	SpriteAtlasConfig(SpriteAtlasConfig&&) = delete;

	SpriteAtlasConfig& operator=(const SpriteAtlasConfig&) = delete;
	SpriteAtlasConfig& operator=(SpriteAtlasConfig&&) = delete;

public:
	using SpriteId = std::size_t;

private:
	using SpriteMap = std::map<SpriteId, Rect>;
	SpriteMap m_sprites;
	std::string m_textureNam;
};

}
