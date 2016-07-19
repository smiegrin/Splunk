#include "MainMenu.h"
#include "Button.h"
#include "ResourceManager.h"
#include "GameScreen.h"
#include <math.h>

MainMenu::MainMenu() {
    playButton = Button(325,400,150,50,sf::Color(97,56,11),"Start");
    title = sf::Text();
    title.setString("Splunk");
    title.setCharacterSize(50);
    title.setFont(ResourceManager::PixelFont);
}

int MainMenu::open(sf::RenderWindow* window) {
    int anim = 0;
    sf::RectangleShape fadeOverlay = sf::RectangleShape(sf::Vector2f(800,500));
    fadeOverlay.setFillColor(sf::Color(0,0,0,0));
    window->setView(window->getDefaultView());
    while (window->isOpen()) {
        sf::Event event;
        while(window->pollEvent(event)) {
            if(event.type == sf::Event::Closed) window->close();
            if(event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) window->close();
                if (event.key.code == sf::Keyboard::Return) anim = 121;
            }
            if(event.type == sf::Event::MouseButtonPressed) {
                if(playButton.pointOnBox(event.mouseButton.x, event.mouseButton.y)) anim = 121;
            }
            if(event.type == sf::Event::Resized) window->setView(sf::View(sf::Vector2f(window->getSize().x/2,window->getSize().y/2), sf::Vector2f(window->getSize())));
        }

        if(anim < 120) title.setPosition(5,pow((float)(anim - 120),3)/-1728), anim++;
        if(anim == 120) title.setPosition(5,0);
        if(anim >= 121) fadeOverlay.setFillColor(sf::Color(0,0,0,255*(anim-120)/60)), anim++;
        if(anim == 180) {
            GameScreen().open(window);
            anim = 120;
        }

        window->clear(sf::Color(0,0,0,255));
        window->draw(playButton);
        window->draw(title);
        window->draw(fadeOverlay);
        window->display();
    }
    return 0;
}
