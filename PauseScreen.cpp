#include "PauseScreen.h"
#include "ResourceManager.h"
#include <sstream>

PauseScreen::PauseScreen(Player* p) {
    continueButton = Button(10,400,100,50,sf::Color(97,56,11), "Resume");
    saveButton = Button(390,400,100,50,sf::Color(97,56,11), "Save");

    title = sf::Text("PAUSE", ResourceManager::PixelFont, 50);
    title.setPosition(sf::Vector2f(200,20));
    title.setColor(sf::Color::White);

    visitedLabel = sf::Text("", ResourceManager::PixelFont, 30);
    visitedLabel.setPosition(sf::Vector2f(20,200));
    visitedLabel.setColor(sf::Color::White);

    readLabel = sf::Text("", ResourceManager::PixelFont, 30);
    readLabel.setPosition(sf::Vector2f(20,300));
    readLabel.setColor(sf::Color::White);

    player = p;
}

void PauseScreen::resize(int width, int height) {
    continueButton.setPosition(20,height-70);
    saveButton.setPosition(width - 120,height-70);
    title.setPosition(width/2 - title.getLocalBounds().width/2, 20);
    visitedLabel.setPosition(20,height/2+100);
    readLabel.setPosition(20,height/2);
}

int PauseScreen::open(sf::RenderWindow* window) {
    resize(window->getSize().x,window->getSize().y);
    window->setView(sf::View(sf::FloatRect(0.,0.,window->getSize().x,window->getSize().y)));
    bool done = false;
    int feedback = 0;
    sf::Event event;

    std::stringstream temp;
    int visit = 0;
    int read = 0;
    for (int i = 0; i < 20; i++) {
        visit += (player->getFlag(i) & Player::VISITED) ? 1 : 0;
        read += (player->getFlag(i) & Player::NOTE_READ) ? 1 : 0;
    }

    temp << "Notes Read: " << read << "/" << visit;
    readLabel.setString(temp.str());
    temp.str("");
    temp << "Visited: " << visit;
    visitedLabel.setString(temp.str());

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
                if(saveButton.pointOnBox(event.mouseButton.x, event.mouseButton.y)) done = true, feedback = 1;
            }
            if (event.type == sf::Event::Resized) {
                resize(event.size.width, event.size.height);
                window->setView(sf::View(sf::FloatRect(0.,0.,event.size.width,event.size.height)));
            }
        }

        window->clear();
        window->draw(title);
        window->draw(readLabel);
        window->draw(visitedLabel);
        window->draw(continueButton);
        window->draw(saveButton);
        window->display();
    }

    return feedback;
}
