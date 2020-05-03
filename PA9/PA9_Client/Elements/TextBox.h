#pragma once
#include <iostream>
#include <string.h>
#include <sstream>
#include "SFML/Graphics.hpp"
#define SFML_NO_DEPRECATED_WARNINGS	

using namespace std;
#define DELETE_KEY 8
#define ENTER_KEY 30
#define ESCAPE_KEY 27

class TextBox
{
public:
	TextBox();
	TextBox(int size, sf::Color, bool sel);
	~TextBox();

	void setFont(sf::Font& font);
	void setPosition(sf::Vector2f pos);

	void setLimit(bool Tof);
	void setLimit(bool Tof, int lim);
	void setSelecter(bool sel);

	string getText();

	void drawTo(sf::RenderWindow& window);
	void typedOn(sf::Event input);
private:
	sf::Text textbox;
	ostringstream text;

	bool isSelected;
	bool hasLimit;
	int limit;

	void inputLogic(int charTyped);
	void deleteLastChar();
};

