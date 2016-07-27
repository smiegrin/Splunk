#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Level.h"

class Player : public GameObject {
public:
    static const int VISITED = 1;
    static const int NOTE_READ = 2;

private:
    float xPos;
    float yPos;
    float xVel;
    float yVel;
    int direction;
    int anim;
    int* levelFlags;
    bool jumpActivated;
    bool digActivated;
    Level* world;
    sf::Sprite sprite;

public:
    Player();
    Player(Level*);

    sf::Vector2f getPosition();
    int getFlag(int);

    void setPosition(float,float);
    void setPosition(sf::Vector2f);
    void setWorld(Level*);
    void setFlag(int,int);

    int logic();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // PLAYER_H
