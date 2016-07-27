#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "Level.h"
#include "Player.h"

class GameScreen : public Screen {
private:
    sf::View resize(int,int);

    sf::View camera;
    int currentLevel;
    Level** levels;
    Player player;
public:
    GameScreen(bool);
    int open(sf::RenderWindow*);
};

#endif
