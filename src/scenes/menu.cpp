#include <SFML/Graphics.hpp>
#include "../main.h"
#include "menu.h"
#include "../utilities/logger.h"

void HandleMainMenuEvents(sf::RenderWindow& window, sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        QuitGame();}
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        StartGameplay();}
}

void DrawMainMenu(sf::RenderWindow& window)
{
    // Load font for text rendering
    sf::Font font;
    if (!font.loadFromFile("assets/other/sansation.ttf")) {
        // Error handling if font loading fails
        return;}

    sf::Text menuText("Main Menu", font, 50);
    menuText.setFillColor(sf::Color::Red);
    menuText.setPosition(320.f, 100.f);

    window.draw(menuText); // Draw the quit text
}