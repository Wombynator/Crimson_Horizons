#include <SFML/Graphics.hpp>
#include "main.h"

#include "entities/player.h"
#include "entities/mob.h"
#include "entities/item.h"

#include "resources/texture.h"
#include "resources/audio.h"
#include "resources/other.h"

#include "scenes/game.h"
#include "scenes/menu.h"
#include "scenes/quit.h"

#include "utilities/logger.h"
#include "utilities/settings.h"


GameStates currentGameState = GameStates::Initializing;
sf::RenderWindow window;
sf::Event event;
float deltaTime;

void StartMainMenu() {
    currentGameState = GameStates::MainMenu;
    InitGame();}
void StartLoading() { currentGameState = GameStates::Loading; }
void StartGameplay() { currentGameState = GameStates::InGame; }
void QuitGame() { currentGameState = GameStates::Exiting; }

void Init()
{
    window.create(sf::VideoMode(1280, 720), "Marsian Game");
    window.setFramerateLimit(60);
    InitLogger();

    LoadTextures();

    StartMainMenu();
}

void HandleEvents()
{
    // Global Events
    if (event.type == sf::Event::Closed) {
        QuitGame();}
    else if (event.type == sf::Event::Resized) {
        sf::Vector2u size = window.getSize();
        sf::View view(sf::FloatRect(0, 0, size.x, size.y));
        window.setView(view);}

    switch (currentGameState) {
        case GameStates::Initializing:
            // Code for the Initializing state
            break;
        
        case GameStates::MainMenu:
            HandleMainMenuEvents(window, event);
            break;

        case GameStates::Loading:
            // Code for the Loading state
            break;

        case GameStates::InGame:
            HandleGameEvents(window, event, deltaTime);
            break;

        case GameStates::Exiting:
            HandleQuitEvents(window, event);    
            break;
    }
}

int main()
{
    sf::Clock clock;
    deltaTime = clock.restart().asSeconds();
    Init();
    while (window.isOpen())
    {
        window.clear(); // Clear the window
        deltaTime = clock.restart().asSeconds();

        while (window.pollEvent(event)) HandleEvents();

        switch (currentGameState) {
            case GameStates::Initializing:
                // Code for the Initializing state
                break;
            
            case GameStates::MainMenu:
                DrawMainMenu(window);
                break;

            case GameStates::Loading:
                // Code for the Loading state
                break;

            case GameStates::InGame:
                DrawGame(window, deltaTime);
                break;

            case GameStates::Exiting:
                // Code for the Exiting state

                DrawQuitScreen(window);
                
                break;
        }

        window.display();
    }

    return 0;
}