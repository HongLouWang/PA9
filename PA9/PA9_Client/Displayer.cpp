#include "Displayer.h"

Displayer::Displayer()
{
	font.loadFromFile("Pixel.ttf");
}

Displayer::~Displayer()
{
}


sf::Text Displayer::GameOver()
{
	font.loadFromFile("Pixel.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("GAME OVER!");
	text.setFillColor(sf::Color::Red);
	text.setCharacterSize(200);
	text.setPosition(sf::Vector2f(100.0f, 200.0f));

	return text;
}

sf::Text Displayer::Controls()
{
	font.loadFromFile("Pixel.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("PRESS SPACEBAR TO JUMP!");
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(40);
	text.setPosition(sf::Vector2f(50.0f, 180.0f));

	return text;
}

sf::Text Displayer::Score()
{
	font.loadFromFile("Pixel.ttf");
	sf::Text text;
	text.setFont(font);
	text.setString("GAME OVER!");
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(200);
	text.setPosition(sf::Vector2f(100.0f, 200.0f));

	return text;
}


