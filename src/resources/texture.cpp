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
    loadTexture("assets/images/preset.png", "preset");
    loadTexture("assets/images/sand.png", "sand");
    loadTexture("assets/images/player.png", "player");
}

sf::Texture& getTexture(const std::string& id) {
    return textures[id];
}