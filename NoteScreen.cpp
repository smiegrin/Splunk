#include "NoteScreen.h"
#include <sstream>

NoteScreen::NoteScreen(int noteID) {
    std::stringstream filename;
    filename << "Notes/" << noteID << ".png";
    bg.loadFromFile(filename.str().c_str());
}

int NoteScreen::open(sf::RenderWindow* window) {
    bool done = false;
    sf::Event event;
    sf::Sprite sprite = sf::Sprite(bg);
    window->setView(sf::View(sf::FloatRect(0,0,500,500)));

    while (!done && window->isOpen()) {
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) window->close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Z) done = true;
        }

        window->clear();
        window->draw(sprite);
        window->display();
    }

    return 0;
}

sf::View NoteScreen::resize(int w, int h) {
    sf::Vector2f sizeV = sf::Vector2f(w,h);
    if (sizeV.x > sizeV.y) sizeV *= 500.f/sizeV.y;
    else sizeV *= 500.f/sizeV.x;
    return sf::View(sizeV, sizeV);
}
