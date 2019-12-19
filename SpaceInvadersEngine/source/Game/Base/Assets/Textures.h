#pragma once
#include <string>
#include <vector>

namespace game
{
namespace assets
{
struct Textures
{
	static std::vector<std::string> GetAllTextures();
	static const std::string k_shipPath;
};
}
}