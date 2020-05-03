#ifndef GAMEPLAY_H
#define GAMEPLAY_H
//Gameplay functions

#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "Platform.h"
#include "Obstacle.h"
#include "Displayer.h"
#include <vector>

class Gameplay
{
public:
	Gameplay();
	~Gameplay();
	

	//function to draw window, call player and obstacle functions. Returns true to run game. False to not run.
	bool playGame();

	//returns true if player hits an obstacle.
	//pauses the game, gives player option to restart
	bool isDead();

	//creates and returns GAMEOVER TEXT
	sf::Text createDeathMessage();

	//sets if player is colliding with the obstacle
	void setIsColliding(bool);

	//returns true if player collides with obstacle
	bool getIsColliding();

	//returns true if game is paused
	bool pauseState();

	//sets pause state, true if paused, false if not
	void setPauseState(bool);

	//restarts the game. calls playGame() until player closes the window
	void restart(); 

	//returns true if player wants to replay the game
	bool Replay();

	//gets score
	int getScore();

	//sets final score
	void setScore(int&);



private:

	bool isColliding;
	bool isPaused;
	char score;

};

#endif