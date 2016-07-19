#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include "ResourceManager.h"

int main()
{
    srand(time(0));

    ResourceManager::initialize();

    sf::RenderWindow window(sf::VideoMode(500, 500), "Splunk");
    window.setFramerateLimit(60);
    MainMenu().open(&window);

    return 0;
}
