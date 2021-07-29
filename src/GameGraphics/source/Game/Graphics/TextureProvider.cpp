#include <Game/Graphics/TextureProvider.h>
#include <SDL/TextureFactory.h>
#include <SDL/Texture.h>
#include <assert.h>
#include <vector>

namespace game
{
namespace graphics
{

TextureProvider::TextureProvider(const TextureFactory& i_textureFactory)
	: m_textureFactory(i_textureFactory)
{ }

TextureProvider::~TextureProvider() = default;


namespace
{
const TextureProvider::Texture* FindTextureById(const TextureProvider::Textures& i_textures, TextureProvider::TextureId i_textureId)
{
	auto it = i_textures.find(i_textureId);
	if ( it != i_textures.end() )
	{
		return it->second.get();
	}
	return nullptr;
}

TextureProvider::TextureId ComputeId(const std::string& i_text)
{
	return std::hash<std::string> {}( i_text );
}

}

void TextureProvider::CreateTextures(const std::vector<std::string>& i_paths)
{
	for (const std::string& path : i_paths)
	{
		CreateTexture(path);
	}
}

TextureProvider::TextureId TextureProvider::CreateTexture(const std::string& i_path)
{
	const TextureId textureId = ComputeId(i_path);
	const sdl::Texture* prevTex = FindTextureById(m_textures, textureId);
	if ( prevTex == nullptr )
	{
		m_textures.emplace(textureId, m_textureFactory.CreateTexture(i_path));
	}
	else
	{
		std::cerr << "Texture at path was already created." << std::endl;
	}
	return textureId;
}

bool TextureProvider::GetTextureId(const std::string& i_path, TextureId& o_textureId) const
{
	o_textureId = ComputeId( i_path );
	const Texture* texture = FindTextureById(m_textures, o_textureId);
	if ( texture == nullptr )
	{
		std::cerr << "Texture " << i_path.c_str() << " was not loaded" << std::endl;
		assert(false); // #fixme db assert here
		return false;
	}
	return true;
}


bool TextureProvider::GetTextureSize(TextureId i_textureId, TextureProvider::Size& o_size) const
{
	const Texture* texture = FindTextureById(m_textures, i_textureId);
	if ( texture )
	{
		auto sz = texture->GetSize();
		o_size[ 0 ] = sz.w;
		o_size[ 1 ] = sz.h;
		return true;
	}
	assert(false); // #fixme db assert here
	return false;
}

}
}