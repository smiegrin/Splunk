#include "PauseScreen.h"
#include "ResourceManager.h"

PauseScreen::PauseScreen() {
    continueButton = Button(10,400,100,50,sf::Color::Red, "Resume");
    title = sf::Text("PAUSE", ResourceManager::PixelFont, 30);
    title.setPosition(sf::Vector2f(200,20));
    title.setColor(sf::Color::White);
}

void PauseScreen::resize(int width, int height) {
    continueButton.setPosition(20,height-70);
    title.setPosition(width/2 - title.getLocalBounds().width, 20);
}

int PauseScreen::open(sf::RenderWindow* window) {
    resize(window->getSize().x,window->getSize().y);
    window->setView(sf::View(sf::FloatRect(0.,0.,window->getSize().x,window->getSize().y)));
    bool done = false;
    int feedback = 0;
    sf::Event event;

    while(!done) {
        while(window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
                done = true;
            }
            if (event.type == sf::Event::KeyPressed) switch (event.key.code) {
            case sf::Keyboard::Escape:
                done = true;
                break;
            case sf::Keyboard::Q:
                done = true;
                window->close();
                break;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if(continueButton.pointOnBox(event.mouseButton.x, event.mouseButton.y)) done = true;
                //save game button
            }
            if (event.type == sf::Event::Resized) {
                resize(event.size.width, event.size.height);
                window->setView(sf::View(sf::FloatRect(0.,0.,event.size.width,event.size.height)));
            }
        }

        window->clear();
        window->draw(title);
        window->draw(continueButton);
        window->display();
    }

    return feedback;
}
