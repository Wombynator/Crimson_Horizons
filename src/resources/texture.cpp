#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "../main.h"
#include "texture.h"
#include "../utilities/logger.h"

std::unordered_map<std::string, sf::Texture> textures;

void loadTexture(const std::string& filename, const std::string& id) {
    sf::Texture texture;
    if (texture.loadFromFile(filename)) {
        textures[id] = texture;
    } else {Log(MessageType::ERROR, "Texture Handler", ("Failed to load image \"" + filename + "\""));}
}

void LoadTextures()
{
    loadTexture("assets/textures/blocks/regolith.png", "regolith");
    loadTexture("assets/textures/blocks/ice.png", "ice");
    loadTexture("assets/textures/player/player.png", "player");
}

sf::Texture& getTexture(const std::string& id) {
    return textures[id];
}