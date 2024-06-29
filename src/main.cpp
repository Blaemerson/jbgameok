#include <iostream>
#include "player.h"

int main(int argc, char** argv)
{
    Player player;
    std::cout << "player.x = " << player.getPosition().x << std::endl;
    std::cout << "player.y = " << player.getPosition().y << std::endl;
    return 0;
}