#include "TextBox.h"

TextBox::TextBox()
{
	
}

TextBox::TextBox(int size, sf::Color color, bool sel)
{
	textbox.setCharacterSize(size);
	textbox.setFillColor(color);
	isSelected = sel;
	if (sel)
	{
		textbox.setString("_");
	}
	else
	{
		textbox.setString("");
	}
}

TextBox::~TextBox()
{
}

void TextBox::inputLogic(int charTyped)
{
	if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
	{
		text << static_cast<char>(charTyped);
	}
	else if (charTyped == DELETE_KEY)
	{
		if (text.str().length() > 0)
		{
			//Delete last character
			deleteLastChar();
		}
	}
	textbox.setString(text.str() + "_");
}

void TextBox::deleteLastChar()
{
	string t = text.str();
	string newT = "";
	for (int i = 0; i < t.length(); i++)
	{
		newT += t[i];
	}
	text.str("");
	text << newT;
	textbox.setString(text.str());
}

void TextBox::setFont(sf::Font& font)
{
	textbox.setFont(font);
}

void TextBox::setPosition(sf::Vector2f pos)
{
	textbox.setPosition(pos);
}

void TextBox::setLimit(bool Tof)
{
	hasLimit = Tof;
}

void TextBox::setLimit(bool Tof, int lim)
{
	limit = lim;
	hasLimit = Tof;
}

void TextBox::setSelecter(bool sel)
{
	isSelected = sel;
	if (!sel)
	{
		string t = text.str();
		string newT = "";
		for (int i = 0; i < t.length(); i++)
		{
			newT += t[i];
		}
		textbox.setString(newT);
	}
}

string TextBox::getText()
{
	return text.str();
}

void TextBox::drawTo(sf::RenderWindow& window)
{
	window.draw(textbox);
}

void TextBox::typedOn(sf::Event input)
{
	if (isSelected)
	{
		int charTyped = input.text.unicode;
		if (charTyped < 128)
		{
			if (hasLimit)
			{
				if (text.str().length() <= limit)
				{
					inputLogic(charTyped);
				}
				else if (text.str().length() > limit&& charTyped == DELETE_KEY)
				{
					deleteLastChar();
				}
			}
			else
			{
				inputLogic(charTyped);
			}
		}
	}
}