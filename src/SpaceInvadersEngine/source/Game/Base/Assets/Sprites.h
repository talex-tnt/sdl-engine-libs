#pragma once
#include <string>
#include <vector>

namespace game
{
namespace assets
{
struct Sprites
{
	struct Atlases
	{
		static const std::string k_invaders;
		static std::vector<std::string> GetAllAtlases();
	};
	static const std::string k_invader01;
	static const std::string k_invader02;
	static const std::string k_ship;
	static const std::string k_projectile;
	static const std::string k_explosion;
};
}
}