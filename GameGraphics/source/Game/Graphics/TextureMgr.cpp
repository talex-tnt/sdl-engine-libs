#include <Game/Graphics/TextureMgr.h>

namespace game
{
namespace graphics
{

TextureMgr::TextureMgr(const sdl::TextureFactory& i_textureFactory)
	: TextureProvider(i_textureFactory)
{ }

const sdl::Texture* TextureMgr::FindTextureById(TextureProvider::TextureId i_textureId) const
{
	auto it = m_textures.find(i_textureId);
	if ( it != m_textures.end() )
	{
		return it->second.get();
	}
	return nullptr;
}

}
}