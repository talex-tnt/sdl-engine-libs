#include <Graphics/Glyphs.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <assert.h>

namespace graphics
{

bool Glyphs::Load(const std::string& i_confFilePath)
{
	std::ifstream inFile;
	inFile.ignore('\n');
	inFile.open(i_confFilePath);
	if ( !inFile )
	{
		std::cerr << "Unable to open file: " << i_confFilePath << std::endl;;
		return false;
	}
	std::string skipNewLine;
	char c;
	Rect r;
	while ( inFile >> std::noskipws >> c >> std::skipws >> r.x >> r.y >> r.w >> r.h)
	{
		m_glyphs.emplace(c, r);
		//std::cout << "c: " << c << ", x: " << r.x << ", y: " << r.y << ", w: " << r.w << ", h: " << r.h << std::endl;
		m_size = std::max(m_size, r.h);
		std::getline(inFile, skipNewLine);
	}
	inFile.close();
	return true;
}

const Glyphs::Rects& Glyphs::GetGlyphsRectsForText(const std::string& i_text) const
{
	const std::string& text = i_text;
	//text.erase(std::find(text.begin(), text.end(), '\0'), text.end());

	GlyphsCacheMap::const_iterator it = m_cache.find(text);
	if (it != m_cache.cend())
	{
		return it->second;
	}
	else
	{
		Rects rects;
		rects.reserve(text.length());
		for (char c : text)
		{
			GlyphsMap::const_iterator it = m_glyphs.find(c);
			if ( it != m_glyphs.cend() )
			{
				rects.emplace_back(it->second);
			}
			else
			{
				std::cerr << "Glyph " << c << " not found."  << std::endl;
				assert(false); // #fixme: db assert
			}
		}
		auto res = m_cache.emplace(text, std::move(rects));
		return res.first->second;
	}
}

std::size_t Glyphs::GetGlyphSize() const
{
	return m_size;
}

}