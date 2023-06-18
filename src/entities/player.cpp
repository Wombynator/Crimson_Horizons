#include <SFML/Graphics.hpp>
#include <cstring>
#include "../main.h"
#include "player.h"
#include "../resources/texture.h"
#include "../resources/audio.h"
#include "../scenes/game.h"
#include "../utilities/logger.h"

int playerScale;
float walkSpeed = 50;
float runSpeed = 75;
float speed;
float worldPosX;
float worldPosY;
float speedX;
float speedY;
float screenPosX;
float screenPosY;
sf::Texture texture;
sf::Sprite sprite;


void InitPlayer() {
    // Constructor implementation
    playerScale = 3;
    texture = getTexture("player");
    sprite.setTexture(texture);
    sprite.setScale(playerScale, playerScale);
}

void CleanupPlayer() {
    // Destructor implementation
}

void HandlePlayerEvents(sf::RenderWindow& window, sf::Event& event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        speed = runSpeed * playerScale;}
    else {speed = walkSpeed * playerScale;}

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        speedX = speed / -1.414f;
        speedY = speed / -1.414f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        speedX = speed / -1.414f;
        speedY = speed / 1.414f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        speedX = speed / 1.414f;
        speedY = speed / -1.414f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        speedX = speed / 1.414f;
        speedY = speed / 1.414f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        speedX = speed * -1;
        speedY = 0.f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        speedX = speed;
        speedY = 0.f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        speedX = 0.f;
        speedY = speed * -1;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        speedX = 0.f;
        speedY = speed;
    } else {
        speedX = 0.f;
        speedY = 0.f;}
}

void SetPlayerWorldPosition(float posX, float posY) {
    worldPosX = posX;
    worldPosY = posY;
}

sf::Vector2f GetPlayerWorldPosition(sf::RenderWindow& window) {
    return {worldPosX + window.getSize().x / 2, worldPosY + window.getSize().y / 2};
}

sf::FloatRect GetBounds() {
    return sprite.getGlobalBounds();
}

void DrawPlayer(sf::RenderWindow& window, float posX, float posY, float deltaTime) {
    worldPosY += speedY * deltaTime;
    worldPosX += speedX * deltaTime;

    int sizeX = window.getSize().x;
    int sizeY = window.getSize().y;
    screenPosX = worldPosX + (sizeX / 2 - texture.getSize().x / 2 * playerScale);
    screenPosY = worldPosY + (sizeY / 2 - texture.getSize().y / 2 * playerScale);

    sprite.setPosition(screenPosX - posX, screenPosY + posY);
    window.draw(sprite);
}