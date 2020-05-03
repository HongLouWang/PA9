#ifndef GAMEPLAY_H
#define GAMEPLAY_H
//Gameplay functions

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>

#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "Platform.h"
#include "Obstacle.h"
#include <vector>
#include <chrono>
#include <thread>

#include "Ranklist/ranklist.h"
#include "Elements/Button.h"
#include "Elements/TextBox.h"
#include "Displayer.h"

#include <cstdlib>
#include <Windows.h>
#include <cstring>
using namespace std;

class Gameplay
{
public:
	Gameplay();
	~Gameplay();


	//function to draw window, call player and obstacle functions
	void playGame(char username[128]);

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
	void restart(char username[128]);

	//returns true if player wants to replay the game
	void Replay();

	int getscore();
	void setscore(int s);

private:
	time_t second_program_start;
	time_t second_now;
	bool isColliding = false;
	bool isPaused = false;	//if game is paused
	int score;
};

#endif