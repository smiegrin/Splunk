#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class ResourceManager {
public:
    static sf::Font PixelFont;

    static sf::Texture GroundTiling;
    static sf::Texture WallTiling;

    static void initialize();
};

#endif // RESOURCEMANAGER_H
