#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

//#include "player.cpp"

// Block structure
struct Block {
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color color;
    bool solid;

    Block(sf::Vector2f xy, sf::Vector2f scale, sf::Color color, bool solid)
        : position(xy), size(scale), color(color), solid(solid) {}
};

// Player structure
struct Player {

    sf::Vector2f position;
    sf::Vector2f size;
    sf::Vector2f velocity;
    sf::Color color;

    Player(sf::Vector2f xy, sf::Vector2f scale, sf::Color color)
        : position(xy), size(scale), velocity(0.f, 0.f), color(color) {}
};

//tells where everything is
static int levelStructure[100][100]  = {0};

static sf::Vector2f spawnPoint(0.f, 0.f);

// Function to generate level blocks
void generateLevel(std::fstream& file, std::vector<Block>& blocks) {
    std::string line;

    if (file.is_open()) {
        int y = 0;
        while (getline(file, line)) {
            for (int x = 0; x < line.length(); x++) {
                
                char c = line[x];
                
                    // Default to solid block
                bool solid = true;

                sf::Color color;

                switch (c) {

                    case '0': //empty space
                        levelStructure[x][y] = 0;
                        solid = false;
                        break;
                    case '1': //generic block
                        levelStructure[x][y] = 1;
                        color = sf::Color::White;
                        break;
                    case '2': //liquid
                        levelStructure[x][y] = 1;
                        color = sf::Color::Blue;
                        solid = false;
                        break;
                    case '3': //hazard-flame
                        levelStructure[x][y] = 1;
                        color = sf::Color::Red;
                        solid = false;
                        break;
                    case '4': //hazard-spike
                        levelStructure[x][y] = 1;
                        color = sf::Color::Green;
                        break;
                    case '5': //hazard-shock
                        levelStructure[x][y] = 1;
                        color = sf::Color::Yellow;
                        break;
                    case '6': //destructible-block
                        levelStructure[x][y] = 1;
                        color = sf::Color::Cyan;
                        break;
                    case '7': //story (trigger story event)
                        levelStructure[x][y] = 1;
                        color = sf::Color::Magenta;
                        break;
                    case '8': //button
                        levelStructure[x][y] = 1;
                        color = sf::Color(128, 128, 128);
                        break;
                    case '9': //moving
                        levelStructure[x][y] = 1;
                        color = sf::Color(255, 165, 0); // Orange
                        break;
                    case 'p': //player starting position

                            // spawnPoint equals xy * player size
                        spawnPoint = sf::Vector2f(x * 50, y * 50);

                        levelStructure[x][y] = 0;

                        solid = false;
                        break;
                    default:
                        continue;
                }

                blocks.emplace_back(sf::Vector2f(x * 50, y * 50), sf::Vector2f(50, 50), color, solid);
            }
            y++;
        }
        file.close();
    } else {
        std::cerr << "ERROR! Unable to open file" << std::endl;
    }
}

// Function to check if the player's position is on a non-solid block
bool isOnNonSolidBlock(const Player& player) {
    // Assuming each block is 50x50 pixels
    int gridX = static_cast<int>(player.position.x) / 50;
    int gridY = static_cast<int>(player.position.y) / 50;

    // Ensure the grid coordinates are within the level structure bounds
    if (gridX >= 0 && gridX < 100 && gridY >= 0 && gridY < 100) {
        return levelStructure[gridX][gridY] == 0;
    }

    // If out of bounds, consider it non-solid
    return true;
}

// Function to check if the player's next position will collide with a solid block
bool willCollideWithSolidBlock(const Player& player, const std::vector<Block>& blocks, sf::Vector2f move) {
    sf::FloatRect playerBounds(player.position + move, player.size);

    for (const auto& block : blocks) {
        if (block.solid) {
            sf::FloatRect blockBounds(block.position, block.size);
            if (playerBounds.intersects(blockBounds)) {
                return true;
            }
        }
    }
    return false;
}

namespace {
    unsigned int WINDOW_WIDTH = sf::VideoMode::getDesktopMode().width;
    unsigned int WINDOW_HEIGHT = sf::VideoMode::getDesktopMode().height;
    const char* WINDOW_TITLE = "Hello there";
    const unsigned short WINDOW_STYLE = sf::Style::Fullscreen;
    //const unsigned short WINDOW_STYLE = sf::Style::Resize;
}



int main(int argc, char** argv) {

    WINDOW_WIDTH = 1800;
    WINDOW_HEIGHT = 900;

        //using window screen for just for beta testing!
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML Game");
    //sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE, WINDOW_STYLE);

    std::vector<Block> blocks;

    // Open the file
    std::fstream file("./levels/level0.txt", std::ios::in);
    generateLevel(file, blocks);

    Player player(sf::Vector2f(spawnPoint), sf::Vector2f(50, 50), sf::Color::Green);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.scancode == sf::Keyboard::Scancode::Escape) {
                        window.close();
                    }
                    break;
                default:
                    break;
            }
        }

// Player movement
        sf::Vector2f move(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) move.y -= 5.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) move.y += 5.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) move.x -= 5.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) move.x += 5.f;

        // Update player position if not colliding with solid blocks
        if (!willCollideWithSolidBlock(player, blocks, move)) {

            //move.y += 2.f;

            player.position += move;

        }


        // Update player position
        player.position += player.velocity;

        window.clear();

        // Draw all blocks
        for (const auto& block : blocks) {
            sf::RectangleShape rectangle(block.size);
            rectangle.setPosition(block.position);
            rectangle.setFillColor(block.color);
            window.draw(rectangle);
        }

        // Draw player
        sf::RectangleShape playerShape(player.size);
        playerShape.setPosition(player.position);
        playerShape.setFillColor(player.color);
        window.draw(playerShape);

        // Update the window
        window.display();

        // Delay to control frame rate
        sf::sleep(sf::milliseconds(16));

    }

    return 0;
}