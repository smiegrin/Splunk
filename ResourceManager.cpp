#include "ResourceManager.h"

sf::Font ResourceManager::PixelFont = sf::Font();

sf::Texture ResourceManager::GroundTiling = sf::Texture();
sf::Texture ResourceManager::WallTiling = sf::Texture();
sf::Texture ResourceManager::SplunkSprites = sf::Texture();

void ResourceManager::initialize() {
//fonts
    PixelFont.loadFromFile("TYPOSTUCK.ttf");

//Textures
    GroundTiling.loadFromFile("Sprites/GroundTiling.png");
    WallTiling.loadFromFile("Sprites/WallTiling.png");
    SplunkSprites.loadFromFile("Sprites/Splunk_Run.png");
}
