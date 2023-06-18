#ifndef QUIT_H
#define QUIT_H

// Forward declaration of sf::RenderWindow
namespace sf {
    class RenderWindow;
    class Event;
}

// Function declaration
void HandleQuitEvents(sf::RenderWindow& window, sf::Event& event);
void DrawQuitScreen(sf::RenderWindow& window);
void CleanUp(sf::RenderWindow& window);

#endif