#include "Player.h"
#include "ResourceManager.h"

Player::Player() {} //unused constructor

Player::Player(Level* newWorld) {
    jumpActivated = false;
    digActivated = false;

    world = newWorld;
    xPos = 0.;
    yPos = 0.;
    xVel = 0.;
    yVel = 0.;
    anim = 0;
    direction = 1;
    levelFlags = new int[20];
    for (int i = 0; i < 20; i++) levelFlags[i] = 0;

    sprite = sf::Sprite(ResourceManager::SplunkSprites);
    sprite.setOrigin(16.,16.);
    sprite.setTextureRect(sf::IntRect(0,0,32,32));

    while (world->colAt(xPos,yPos)) {
        xPos = (float)(rand() % (int)world->getPixelSize().x);
        yPos = (float)(rand() % (int)world->getPixelSize().y);
    }
}


sf::Vector2f Player::getPosition() { return sf::Vector2f(xPos,yPos); }

int Player::getFlag(int levelNum) { return levelFlags[levelNum]; }


void Player::setPosition(float newX, float newY) {
    xPos = newX;
    yPos = newY;
}

void Player::setPosition(sf::Vector2f posV) {
    xPos = posV.x;
    yPos = posV.y;
}

void Player::setWorld(Level* newWorld) {
    world = newWorld;
}

void Player::setFlag(int levelNum, int flag) {
    levelFlags[levelNum] = levelFlags[levelNum] | flag;
}


int Player::logic() {
    //climb
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        if (yVel < 5 && yVel > -5) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) yVel = -1.;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) yVel = 1.;
            else yVel = 0;
        }
        else yVel += .35;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) xVel = -1.;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) xVel = 1.;
        else xVel = 0;
    }

    else if (world->colAt(xPos,yPos + 16)) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !jumpActivated)  {
            yVel = -8;
            jumpActivated = true;
            anim = 0;
            sprite.setTextureRect(sf::IntRect(32,0,32,32));
        }

        //left or right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            xVel = -3.5;
            direction = -1;
            anim = ++anim % 40;
            sprite.setTextureRect(sf::IntRect(anim/10*32,0,32,32));
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            xVel = 3.5;
            direction = 1;
            anim = ++anim % 40;
            sprite.setTextureRect(sf::IntRect(anim/10*32,0,32,32));
        }
        else {
            xVel = 0;
            anim = 0;
            sprite.setTextureRect(sf::IntRect(0,0,32,32));
        }
    }
    else {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && xVel >= 0) xVel = -1., direction = -1;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && xVel <= 0) xVel = 1., direction = 1;
        yVel += .35;
        anim = 0;
        sprite.setTextureRect(sf::IntRect(32,0,32,32));
    }

    //dig check
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X) && !digActivated) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) world->activateAt(xPos-32.,yPos);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) world->activateAt(xPos+32.,yPos);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) world->activateAt(xPos,yPos-32.);
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) world->activateAt(xPos,yPos+32.);
        else world->activateAt(xPos,yPos);
        digActivated = true;
    }

    //reset activated flags
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) jumpActivated = false;
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::X)) digActivated = false;

    //physics
    for (int i = abs(yVel); i > 0; i--) {
        if(!world->colAt(xPos, yPos + abs(yVel)/yVel*16)) yPos += abs(yVel)/yVel;
        else {
            yVel = 0;
            break;
        }
        while (yVel == 0 && world->colAt(xPos,yPos+16)) yPos -= 1.;
    }

    for (int i = abs(xVel); i > 0; i--) {
        if(!world->colAt(xPos + abs(xVel)/xVel*5, yPos)) xPos += abs(xVel)/xVel;
        else break;
    }

    //prepare to draw
    sprite.setScale(direction,1);
    sprite.setPosition(xPos,yPos);

    return 0;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(sprite);
}
