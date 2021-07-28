#pragma once
#include <string>
#include <unordered_map>
#include <map>
#include <vector>

namespace graphics
{

class Glyphs
{
public:
	Glyphs() = default;
	~Glyphs() = default;
	struct Rect { std::uint32_t x, y, w, h; };
	using Rects = std::vector<graphics::Glyphs::Rect>;

	bool Load(const std::string& i_configFilePath);
	const Rects& GetGlyphsRectsForText(const std::string& i_text) const;
	std::size_t GetGlyphSize() const;

public:
	Glyphs(const Glyphs&) = delete;
	Glyphs(Glyphs&&) = delete;

	Glyphs& operator=(const Glyphs&) = delete;
	Glyphs& operator=(Glyphs&&) = delete;

private:
	using GlyphsMap = std::map<char, Rect>;
	GlyphsMap m_glyphs;
	using GlyphsCacheMap = std::map<std::string, Rects>;
	mutable GlyphsCacheMap m_cache; // #fixme: use lru cache
	std::uint32_t m_size;
};

}
