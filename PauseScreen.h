#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Screen.h"
#include "Player.h"

class PauseScreen : public Screen {
private:
    Button continueButton;
    Button saveButton;
    sf::Text title;
    sf::Text visitedLabel;
    sf::Text readLabel;
    Player* player;

    void resize(int, int);

public:
    PauseScreen(Player*);
    int open(sf::RenderWindow*);
};

#endif
