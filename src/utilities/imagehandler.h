#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <string>
#include <SFML/Graphics.hpp>  // Include the SFML Graphics header

void generateCheckerboardPattern();

sf::Image getFile(const std::string& imagePath, const std::string& downloadUrl);

#endif