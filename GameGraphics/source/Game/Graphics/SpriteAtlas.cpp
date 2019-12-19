#include <Game/Graphics/SpriteAtlas.h>
#include <Game/Graphics/TextureMgr.h>
#include <Graphics/SpriteAtlasConfig.h>

#include <assert.h>
namespace
{
std::string GetFolderPath(const std::string& i_path)
{
	size_t found;
	found = i_path.find_last_of("/\\");
	return i_path.substr(0, found);
}
}

namespace game
{
namespace graphics
{

SpriteAtlas::~SpriteAtlas() = default;

bool SpriteAtlas::Load(TextureMgr& i_textureMgr, const std::string& i_configFilePath)
{
	if ( m_config->Load(i_configFilePath) )
	{
		const std::string texturePath = GetFolderPath(i_configFilePath) + "//" + m_config->GetTextureName();
		m_textureId = i_textureMgr.CreateTexture(texturePath);
		return i_textureMgr.GetTextureSize(m_textureId, m_textureSize);
	}
	else
	{
		std::cerr << "SpriteAtlas Config with name: " << i_configFilePath << " was not found" << std::endl;
		assert(false); // #fixme use db assert
		return false;
	}
}

SpriteAtlas::SpriteAtlas()
	: m_config(std::make_unique<Config>())
{
	
}

game::graphics::SpriteAtlas::Sprite SpriteAtlas::GetSprite(const std::string& i_name) const
{
	Config::Rect r;
	if ( m_config->FindSpriteRect(i_name, r) )
	{
		r.y = m_textureSize.y() - r.y - r.h; // flip y coord
		return Sprite {
		Sprite::Rect{Sprite::Pos{
			static_cast< Sprite::Pos::value_type >( r.x ),
			static_cast< Sprite::Pos::value_type >( r.y )
		}, Sprite::Size{
			static_cast< Sprite::Size::value_type >( r.w ),
			static_cast< Sprite::Size::value_type >( r.h )
		}} , m_textureId };
	}
	else
	{
		std::cerr << "Sprite with name: " << i_name <<" was not found" << std::endl;
		assert(false); // #fixme use db assert
		return Sprite{};
	}
}

}
}