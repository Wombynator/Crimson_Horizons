#ifndef PLAYER_H
#define PLAYER_H

// Forward declaration of sf::RenderWindow
namespace sf {
    class RenderWindow;
    class Event;
}

// Function declarations
void InitPlayer();
void CleanupPlayer();

void HandlePlayerEvents(sf::RenderWindow& window, sf::Event& event);
void SetPlayerWorldPosition(float posX, float posY);
sf::Vector2f GetPlayerWorldPosition(sf::RenderWindow& window);
sf::FloatRect GetBounds();
void DrawPlayer(sf::RenderWindow& window, float posX, float posY, float deltaTime);

#endif