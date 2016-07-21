#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Screen.h"

class PauseScreen : public Screen{
private:
    Button continueButton;
    sf::Text title;

    void resize(int, int);

public:
    PauseScreen();
    int open(sf::RenderWindow*);
};

#endif
