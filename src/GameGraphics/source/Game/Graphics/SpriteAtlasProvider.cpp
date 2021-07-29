#include <Game/Graphics/SpriteAtlasProvider.h>
#include <vector>

namespace game
{
namespace graphics
{

namespace
{
SpriteAtlasProvider::SpriteAtlasId ComputeId(const std::string& i_text)
{
	return std::hash<std::string> {}( i_text );
}
}

SpriteAtlasProvider::SpriteAtlasProvider(TextureMgr& i_textureMgr)
	: m_textureMgr(i_textureMgr)
{

}
SpriteAtlasProvider::~SpriteAtlasProvider() = default;


bool SpriteAtlasProvider::LoadSpriteAtlas(const std::string& i_filepath)
{
	auto res = m_spriteAtlases.emplace(std::piecewise_construct,
			std::forward_as_tuple(ComputeId(i_filepath)),
			std::forward_as_tuple());
	return res.first->second.Load(m_textureMgr, i_filepath);
}


bool SpriteAtlasProvider::LoadSpriteAtlases(const std::vector<std::string>& i_filepaths)
{
	bool result = true;
	for (const std::string& path : i_filepaths)
	{
		if ( LoadSpriteAtlas(path) == false )
		{
			result = false;
		}
	}
	return result;
}

const game::graphics::SpriteAtlas* SpriteAtlasProvider::GetSpriteAtlas(const std::string& i_filepath) const
{
	auto it = m_spriteAtlases.find(ComputeId(i_filepath));
	if ( it != m_spriteAtlases.end() )
	{
		return &it->second;
	}
	return nullptr;
}

}
}