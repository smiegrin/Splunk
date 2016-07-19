#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Level.h"

class Player : public GameObject {
private:
    float xPos;
    float yPos;
    float xVel;
    float yVel;
    int direction;
    bool jumpActivated;
    bool digActivated;
    Level* world;

public:
    Player();
    Player(Level*);

    sf::Vector2f getPosition();

    void setPosition(float,float);
    void setPosition(sf::Vector2f);
    void setWorld(Level*);

    int logic();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // PLAYER_H
