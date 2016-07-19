#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include <list>
#include "GameObject.h"

class Screen {
protected:
    std::list<sf::Drawable*> dispList;
    std::list<GameObject*> objList;
public:
    virtual int open(sf::RenderWindow*) = 0;
};

#endif // SCREEN_H
