#include <SFML/Graphics.hpp>
#include "../main.h"
#include "quit.h"
#include "../utilities/logger.h"

void HandleQuitEvents(sf::RenderWindow& window, sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        StartMainMenu();}
    else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
        CleanUp(window);}
}

void DrawQuitScreen(sf::RenderWindow& window)
{
    // Load font for text rendering
    sf::Font font;
    if (!font.loadFromFile("assets/other/sansation.ttf"))
    {
        // Error handling if font loading fails
        return;
    }

    sf::Text quitText("Do you want to Quit?", font, 50);
    quitText.setFillColor(sf::Color::Red);
    quitText.setPosition(320.f, 250.f);

    window.draw(quitText); // Draw the quit text
}

void CleanUp(sf::RenderWindow& window)
{
    CleanUpLogger();
    window.close();
}