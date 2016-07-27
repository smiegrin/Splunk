#include "GameScreen.h"
#include "PauseScreen.h"
#include <fstream>
#include <sstream>

sf::View GameScreen::resize(int w, int h) {
    sf::Vector2f sizeV = sf::Vector2f(w,h);
    if (sizeV.x > sizeV.y) sizeV *= 500.f/sizeV.y;
    else sizeV *= 500.f/sizeV.x;
    return sf::View(player.getPosition(), sizeV);
}

GameScreen::GameScreen(bool load) {
    levels = new Level*[20];

    if(load) {
        std::stringstream filename;
        std::ifstream stream;
        for (int i = 0; i < 20; i++) {
            filename.str("");
            filename << "SaveData/Level" << i << ".lvl";
            stream.open(filename.str().c_str());
            levels[i] = new Level(stream);
            stream.close();
        }

        int flag = 0;
        currentLevel = 0;
        player = Player(levels[currentLevel]);
        stream.open("SaveData/Flags.dat");
        for (int i = 0; i < 20; i++) {
            stream >> flag;
            player.setFlag(i, flag);
        }
    }
    else {
        for (int i = 0; i < 20; i++) levels[i] = new Level();
        currentLevel = 0;
        player = Player(levels[currentLevel]);
        camera = sf::View(sf::FloatRect(0.,0.,500.,500.));
    }
}

int GameScreen::open(sf::RenderWindow* window) {
    camera = resize(window->getSize().x,window->getSize().y);
    window->setView(camera);

    while (window->isOpen()) {
        sf::Event event;
        while(window->pollEvent(event)) {
            if(event.type == sf::Event::Closed) window->close();
            if(event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    if (PauseScreen(&player).open(window)) { //save sequence
                        std::cout << "Saving Game\n";
                        std::stringstream filename;
                        std::ofstream stream;
                        for (int i = 0; i < 20; i++) {
                            filename.str("");
                            filename << "SaveData/Level" << i << ".lvl";
                            stream.open(filename.str().c_str());
                            levels[i]->serialize(stream);
                            stream.close();
                        }
                        stream.open("SaveData/Flags.dat");
                        for (int i = 0; i < 20; i++) stream << player.getFlag(i) << " ";
                        stream.close();
                    }
                    camera = resize(window->getSize().x,window->getSize().y);
                    window->setView(camera);
                }
                if (event.key.code == sf::Keyboard::Return) {
                    std::ofstream stream;
                    stream.open("Level.lvl");
                    levels[currentLevel]->serialize(stream);
                    stream.close();
                }
            }
            if (event.type == sf::Event::Resized) camera = resize(window->getSize().x, window->getSize().y);
        }

        player.logic();
        switch (levels[currentLevel]->logic()) {
        case Level::ADVANCE_LEVEL:
            if (currentLevel < 19) currentLevel++;
            player.setWorld(levels[currentLevel]);
            player.setPosition(levels[currentLevel]->getUpLoc());
            player.setFlag(currentLevel, Player::VISITED);
            break;
        case Level::RETURN_LEVEL:
            if (currentLevel > 0) currentLevel--;
            player.setWorld(levels[currentLevel]);
            player.setPosition(levels[currentLevel]->getDownLoc());
            player.setFlag(currentLevel, Player::VISITED);
            break;
        case Level::OPEN_NOTE:
            std::cout << "HO1!!!\n";
            player.setFlag(currentLevel, Player::NOTE_READ);
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
