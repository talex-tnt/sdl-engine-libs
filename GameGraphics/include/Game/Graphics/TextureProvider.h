#pragma once

#include <Math/Vector.h>

#include <memory>
#include <array>
#include <unordered_map>

namespace sdl
{
class TextureFactory;
class Texture;
}

namespace game
{
namespace graphics
{
class TextureProvider
{
public:
	using Pos = Math::Vec2i;
	using Size = Math::Vec2i; 
	struct Rect 
	{ 
		Pos pos; Size size; 
	};
	using TextureId = std::size_t;

	bool GetTextureId(const std::string& i_path, TextureId& o_textureId) const;
	bool GetTextureSize(TextureId i_textureId, Size& o_size) const;

protected:
	TextureId CreateTexture(const std::string& i_path);
	void TextureProvider::CreateTextures(const std::vector<std::string>& i_paths);

public:
	using Texture = sdl::Texture;
	using Textures = std::unordered_map<TextureId, std::unique_ptr<const Texture>>;
	using TextureFactory = sdl::TextureFactory;

protected:
	~TextureProvider();
	TextureProvider(const TextureFactory& i_textureFactory);

	TextureProvider(const TextureProvider&) = delete;
	TextureProvider(TextureProvider&&) = delete;

	TextureProvider& operator=(const TextureProvider&) = delete;
	TextureProvider& operator=(TextureProvider&&) = delete;

protected:
	const TextureFactory& m_textureFactory;
	Textures m_textures;
};

}
}