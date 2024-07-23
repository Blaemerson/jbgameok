#include <iostream>
#include "player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace
{
    unsigned int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width;
    unsigned int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height;
    const char* WINDOW_TITLE = "Hello there";
    const unsigned short WINDOW_STYLE = sf::Style::Fullscreen;
}

int main(int argc, char** argv)
{
    Player player;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, WINDOW_STYLE);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::KeyPressed:
                    if(event.key.scancode == sf::Keyboard::Scancode::Escape)
                    {
                        window.close();
                    }
                    break;

                default:
                    break;
            }
        }
    }

    return 0;
}