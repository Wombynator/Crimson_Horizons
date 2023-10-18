#include <SFML/Graphics.hpp>
#include "../main.h"
#include "game.h"
#include "../entities/player.h"
#include "../resources/texture.h"
#include "../resources/audio.h"
#include "../utilities/logger.h"
#include <cstdlib>


int gameScale = 4;
float cameraPosX = 100.f;
float cameraPosY = 100.f;
int textureValue = 0;
int amount[10] = {0}; // An array to store counts for each textureValue


// Function to generate a random value between min and max (inclusive)
int getRandomValue(int min, int max) {
    
	srand((unsigned) time(NULL));
	int random = min + (rand() % (max - min + 1));
    
    return random;
}

void InitGame() {
    // Constructor implementation
    InitPlayer();
    SetPlayerWorldPosition(0,0);
    textureValue = getRandomValue(0,9);

    amount[textureValue] += 1;
    
    for (int i = 0; i < 10; i++) {
        Log(MessageType::TRACE, "Game", (std::to_string(i) + ": " + std::to_string(amount[i])));
    }
}

void CleanupGame() {
    CleanupPlayer();
}

void HandleGameEvents(sf::RenderWindow& window, sf::Event& event, float deltaTime)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        StartMainMenu();
        CleanupGame();
    } else {
        HandlePlayerEvents(window, event);
    }
}

void DrawGame(sf::RenderWindow& window, float deltaTime)
{
    // Load font for text rendering
    sf::Font font;
    if (!font.loadFromFile("assets/other/sansation.ttf")) {
        // Error handling if font loading fails
        return;}

    sf::Text gameText("Game", font, 50);
    gameText.setFillColor(sf::Color::Red);
    gameText.setPosition(320.f, 100.f);

    int sizeX = window.getSize().x;
    int sizeY = window.getSize().y;
    float playerPosX = GetPlayerWorldPosition(window).x;
    float playerPosY = GetPlayerWorldPosition(window).y;

    float playerDistanceX = sizeX/2 - playerPosX + cameraPosX;
    float playerDistanceY = sizeY/2 - playerPosY - cameraPosY;

    // Log(MessageType::TRACE, "Game", ("DistanceX: " + std::to_string(playerDistanceX) + " DistanceY: " + std::to_string(playerDistanceY)));

    if (playerDistanceX < 2.f && playerDistanceX > -2.f) {
        cameraPosX -= playerDistanceX;
    } else {cameraPosX -= playerDistanceX / 20;}

    if (playerDistanceY < 2.f && playerDistanceY > -2.f) {
        cameraPosY += playerDistanceY;
    } else {cameraPosY += playerDistanceY / 20;}
    

    sf::Texture texture = getTexture("regolith");
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sf::IntRect textureRect(textureValue * texture.getSize().x / 10, 0, texture.getSize().x / 10, texture.getSize().y);
    sprite.setTextureRect(textureRect);

    int screenPosX = (sizeX / 2 - texture.getSize().x / 2 * gameScale) - (float)(cameraPosX);
    int screenPosY = (sizeY / 2 - texture.getSize().y / 2 * gameScale) + (float)(cameraPosY);

    sprite.setPosition(screenPosX, screenPosY);
    sprite.setScale(gameScale, gameScale);

    window.draw(sprite);
    DrawPlayer(window, cameraPosX, cameraPosY, deltaTime);
    window.draw(gameText); // Draw the quit text
}