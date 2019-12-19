#include <Graphics/SpriteAtlasConfig.h>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <assert.h>

namespace graphics
{

namespace
{
SpriteAtlasConfig::SpriteId ComputeId(const std::string& i_text)
{
	return std::hash<std::string> {}( i_text );
}
}

bool SpriteAtlasConfig::Load(const std::string& i_confFilePath)
{
	std::ifstream inFile;
	inFile.ignore('\n');
	inFile.open(i_confFilePath);
	if ( !inFile )
	{
		std::cerr << "Unable to open file: " << i_confFilePath << std::endl;;
		return false;
	}
	
	std::getline(inFile, m_textureNam);
	
	std::string name;
	Rect r;
	while ( inFile >>  name >> r.x >> r.y >> r.w >> r.h)
	{
		m_sprites.emplace(ComputeId(name), r);
		//std::cout << "c: " << c << ", x: " << r.x << ", y: " << r.y << ", w: " << r.w << ", h: " << r.h << std::endl;
	}
	inFile.close();
	return true;
}

bool SpriteAtlasConfig::FindSpriteRect(const std::string& i_spriteName, SpriteAtlasConfig::Rect& o_rect) const
{
	auto it = m_sprites.find(ComputeId(i_spriteName));
	if ( it != m_sprites.end() )
	{
		o_rect = it->second;
		return true;
	}
	return false;
}


const std::string& SpriteAtlasConfig::GetTextureName() const
{
	return m_textureNam;
}

}