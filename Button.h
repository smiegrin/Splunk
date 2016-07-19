#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button : public sf::Drawable {
	int x, y, width, height;
	sf::RectangleShape shape;
	sf::Text label;
public:
	Button();
	Button(int,int,int,int,sf::Color, std::string);

	sf::Shape* getShape();

	bool pointOnBox(int,int);

	//inherited from Drawable
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};



#endif
