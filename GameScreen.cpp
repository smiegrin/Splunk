#include "GameScreen.h"
#include "PauseScreen.h"
#include <fstream>

GameScreen::GameScreen() {
    levels = new Level*[20];

    std::ifstream stream;
    stream.open("Level.lvl");
    levels[0] = new Level(stream);
    levels[0]->serialize(std::cout);
    stream.close();

    for (int i = 1; i < 20; i++) levels[i] = new Level();
    currentLevel = 0;
    player = Player(levels[currentLevel]);
    camera = sf::View(sf::FloatRect(0.,0.,500.,500.));
}

int GameScreen::open(sf::RenderWindow* window) {
    sf::Vector2f sizeV = (sf::Vector2f)window->getSize();
    if (sizeV.x > sizeV.y) sizeV *= 500.f/sizeV.y;
    else sizeV *= 500.f/sizeV.x;
    camera = sf::View(player.getPosition(), sizeV);
    window->setView(camera);

    while (window->isOpen()) {
        sf::Event event;
        while(window->pollEvent(event)) {
            if(event.type == sf::Event::Closed) window->close();
            if(event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    PauseScreen().open(window);
                    sf::Vector2f sizeV = (sf::Vector2f)window->getSize();
                    if (sizeV.x > sizeV.y) sizeV *= 500.f/sizeV.y;
                    else sizeV *= 500.f/sizeV.x;
                    camera = sf::View(player.getPosition(), sizeV);
                    window->setView(camera);
                }
                if (event.key.code == sf::Keyboard::Return) {
                    std::ofstream stream;
                    stream.open("Level.lvl");
                    levels[currentLevel]->serialize(stream);
                    stream.close();
                }
            }
            if(event.type == sf::Event::Resized) {
                sf::Vector2f sizeV = (sf::Vector2f)window->getSize();
                if (sizeV.x > sizeV.y) sizeV *= 500.f/sizeV.y;
                else sizeV *= 500.f/sizeV.x;
                camera = sf::View(player.getPosition(), sizeV);
            }
        }

        player.logic();
        switch (levels[currentLevel]->logic()) {
        case Level::ADVANCE_LEVEL:
            if (currentLevel < 19) currentLevel++;
            player.setWorld(levels[currentLevel]);
            player.setPosition(levels[currentLevel]->getUpLoc());
            break;
        case Level::RETURN_LEVEL:
            if (currentLevel > 0) currentLevel--;
            player.setWorld(levels[currentLevel]);
            player.setPosition(levels[currentLevel]->getDownLoc());
            break;
        case Level::OPEN_NOTE:
            std::cout << "HO1!!!\n";
            break;
        }
        camera.setCenter((player.getPosition() - camera.getCenter())/10.f+camera.getCenter());

        window->setView(camera);
        window->clear(sf::Color::Black);
        window->draw(levels[currentLevel]->getBG());
        window->draw(player);
        window->draw(levels[currentLevel]->getFG());
        window->display();
    }
    return 0;
}
