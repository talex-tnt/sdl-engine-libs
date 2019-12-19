#include "Sprites.h"

namespace game
{
namespace assets
{
const std::string k_rootFolder("./assets/sprites/");
const std::string Sprites::Atlases::k_invaders(k_rootFolder + "invaders-64.sprites");

std::vector<std::string> Sprites::Atlases::GetAllAtlases()
{
	return { 
		k_invaders 
	};
}

const std::string Sprites::k_invader01("invader01");
const std::string Sprites::k_invader02("invader02");
const std::string Sprites::k_ship("ship");
const std::string Sprites::k_projectile("projectile");
const std::string Sprites::k_explosion("explosion");

}
}
