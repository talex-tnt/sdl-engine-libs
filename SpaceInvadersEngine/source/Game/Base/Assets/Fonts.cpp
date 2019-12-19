#include "Fonts.h"

namespace game
{
namespace assets
{

const std::string k_rootFolder("./assets/");
const game::graphics::Font Fonts::k_unifont { k_rootFolder + "unifont-64.bmp", k_rootFolder + "unifont-64.font" };

}
}