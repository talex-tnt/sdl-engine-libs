#pragma once
#include "SpriteAtlas.h"

#include <string>
#include <map>

namespace game
{
namespace graphics
{
class TextureMgr;

class SpriteAtlasProvider
{
public:
	using SpriteAtlasId = std::size_t;
	const SpriteAtlas* GetSpriteAtlas(const std::string& i_filepath) const;

protected:
	bool LoadSpriteAtlas(const std::string& i_filepath);
	bool LoadSpriteAtlases(const std::vector<std::string>& i_filepaths);

protected:
	~SpriteAtlasProvider();
	SpriteAtlasProvider( TextureMgr& i_textureMgr);

	SpriteAtlasProvider(const SpriteAtlasProvider&) = delete;
	SpriteAtlasProvider(SpriteAtlasProvider&&) = delete;

	SpriteAtlasProvider& operator=(const SpriteAtlasProvider&) = delete;
	SpriteAtlasProvider& operator=(SpriteAtlasProvider&&) = delete;

	class InternalSpriteAtlas : public game::graphics::SpriteAtlas
	{
	public:
		using game::graphics::SpriteAtlas::Load;

		InternalSpriteAtlas() = default;
		InternalSpriteAtlas(const SpriteAtlas&) = delete;
		InternalSpriteAtlas(InternalSpriteAtlas&&) = delete;

		InternalSpriteAtlas& operator=(const InternalSpriteAtlas&) = delete;
		InternalSpriteAtlas& operator=(InternalSpriteAtlas&&) = delete;
	};

protected:
	TextureMgr& m_textureMgr;
	using SpriteAtlasMap = std::map<SpriteAtlasId, InternalSpriteAtlas>;
	SpriteAtlasMap m_spriteAtlases;
};

}
}