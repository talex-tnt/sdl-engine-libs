#pragma once
#include "TextureProvider.h"

namespace game
{
namespace graphics
{

class TextureMgr : public TextureProvider
{
public:
	TextureMgr(const TextureProvider::TextureFactory& i_textureFactory);
	const TextureProvider::Texture* FindTextureById(TextureProvider::TextureId i_textureId) const;
	using TextureProvider::CreateTexture;
	using TextureProvider::CreateTextures;
};

}
}