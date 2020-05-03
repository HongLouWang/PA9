#ifndef DISPLAYER_H
#define DISPLAYER_H

#include <SFML\Graphics.hpp>
#include <iostream>

//displays text on the console screen
class Displayer
{
public:
	Displayer();
	~Displayer();

	sf::Text GameOver();

	sf::Text Controls();

	sf::Text Score();


private:

	sf::Font font;


};

#endif 