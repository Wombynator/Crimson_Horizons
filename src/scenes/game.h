#ifndef GAME_H
#define GAME_H

enum class IngameStates
{
    Loading,
    StartingGameplay,
    InGame,
    Paused,
    Options,
    Exiting
};

enum class OpenContainer
{
    None,
    Inventory
};

// Forward declaration of sf::RenderWindow
namespace sf {
    class RenderWindow;
    class Event;
}

// Function declarations
void InitGame();
void CleanupGame();

void HandleGameEvents(sf::RenderWindow& window, sf::Event& event, float deltaTime);
void DrawGame(sf::RenderWindow& window, float deltaTime);

#endif
