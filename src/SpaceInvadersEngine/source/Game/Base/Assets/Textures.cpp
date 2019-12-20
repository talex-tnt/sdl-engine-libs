#include "Textures.h"

namespace game
{
namespace assets
{
const std::string k_rootFolder("./assets/");
const std::string Textures::k_shipPath(k_rootFolder + "Ship.bmp");

std::vector<std::string> Textures::GetAllTextures()
{
	return { 
		//k_shipPath 
	};
}

}
}
