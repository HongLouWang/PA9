/*
CPTS 122 SPR 2020
PA9

Description:

//Player sprites are from rpgtileset.com/sprite/running-radish-sprite-for-rpg-maker-mv/
*/

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <vector>
#include "Animation.h"
#include "Player.h"
#include "Platform.h"
#include "Obstacle.h"
#include "Gameplay.h"


static const float VIEW_HEIGHT = 480.0f;
//makes every sprite the same size and posn when window is resized
void ResizeView(sf::RenderWindow &window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);

	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}


int main() {
	Gameplay gameplay;
	bool run = false;

	//starts the game once, then loops as long as playGame returns true.
	do {

		run = gameplay.playGame();

	}while(run);


	return 0;
}

