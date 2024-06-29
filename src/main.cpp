#include <iostream>
#include "player.h"
#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
    Player player;
    std::cout << "player.x = " << player.GetPosition().x << std::endl;
    std::cout << "player.y = " << player.GetPosition().y << std::endl;
    return 0;
}