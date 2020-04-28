#ifndef PLAYER_H
#define PLAYER_H

#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Collider.h"
#include "Animation.h"

class Player 
{
public:
	Player(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight);
	~Player();

	//Updates animation and movement
	void Update(float deltaTime, float speed);	
	//calls window.draw
	void Draw(sf::RenderWindow& window);	
	//if player collides with entity, stops the player. If collide with ground, sets canJump to true
	void onCollision(sf::Vector2f direction);

	


	//getter for player's position on the screen
	sf::Vector2f GetPosition() {
		return body.getPosition();
	}

	Collider GetCollider() {
		return Collider(body);
	}

	void playSound();

private:
	sf::RectangleShape body; //body of the player
	Animation animation;
	unsigned int row;	//specifies which row of the sprite sheet i wanna use
	float speed;
	bool faceRight;	//character facing right or not

	sf::Vector2f velocity;
	bool canJump;	//is player colliding with another unmovable object?
	float jumpHeight;	//height that player can jump
	sf::Music sound;

};

#endif