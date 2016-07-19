#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Screen.h"

class MainMenu : public Screen{
private:
    Button playButton;
    sf::Text title;
public:
    MainMenu();
    int open(sf::RenderWindow*);
};

#endif
