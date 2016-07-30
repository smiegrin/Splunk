#ifndef NOTESCREEN_H
#define NOTESCREEN_H

# include <SFML/Graphics.hpp>
# include "Screen.h"

class NoteScreen : public Screen {
public:
    NoteScreen(int);

    int open(sf::RenderWindow*);

private:
    sf::Texture bg;
    //sf::Texture effect;

    sf::View resize(int, int);

};

#endif
