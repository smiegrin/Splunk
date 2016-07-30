#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include <iostream>

class Level : public GameObject {
public:
    enum Block { Ground, Air, DownPassage, UpPassage, Note, Smear };
    static const int ADVANCE_LEVEL = 1;
    static const int RETURN_LEVEL = 2;
    static const int OPEN_NOTE = 3;

private:
    void updateFgAt(int,int);
    void updateBgAt(int,int);

    int portalAccessed;
    int noteAccessed;
    sf::Vector2f downLoc;
    sf::Vector2f upLoc;

    sf::RenderTexture bg;
    sf::RenderTexture fg;
    Block* space;
    float gridSize;
    int width;
    int height;
    int noteID;

public:
    Level(int);
    Level(std::istream&);

    sf::Vector2f getPixelSize();
    int logic();
    bool colAt(float,float);
    void activateAt(float,float);
    void serialize(std::ostream&);

    int getNoteID();
    sf::Sprite getFG();
    sf::Sprite getBG();
    sf::Vector2f getDownLoc();
    sf::Vector2f getUpLoc();

    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // LEVEL_H
