#ifndef MENU_H
#define MENU_H

// Forward declaration of sf::RenderWindow
namespace sf {
    class RenderWindow;
    class Event;
}

// Function declarations
void HandleMainMenuEvents(sf::RenderWindow& window, sf::Event& event);
void DrawMainMenu(sf::RenderWindow& window);

#endif
