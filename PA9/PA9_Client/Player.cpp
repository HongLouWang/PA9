#include "Player.h"


			//gets texture, number of images, time taken for next image,	speed= x axis direction
Player::Player(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight):
animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true; //starts with facing right
	this->jumpHeight = jumpHeight;

	//sets player size (body)
	//from main.cpp, changed player to body
	body.setSize(sf::Vector2f(65.0f, 80.0f));	//size of the player
	body.setPosition(2.0f, 456.0f);			//starting posn of player
	body.setTexture(texture);	//applies picture file to the playertexture
	body.setOrigin(body.getSize() / 2.0f);

}


Player::~Player()
{
}

void Player::Update(float deltaTime, float speed)
{
	this->speed = speed;
			//velocity.x *= 0.5f;	smaller number, shorter time to stop jumping
	 //initializes velocity to be 0 at begining of every frame.
	velocity.x = speed;	//0.0f to use keyboard controls //change to speed to switch to constantly moving

	///////////////////////////////////////////////////////////
	////Left the Keyboard presses in for tsting purposes. /////
	////Delete these when finalizing project///////////////////
	///////////////////////////////////////////////////////////
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		velocity.x -= speed;	//goes -x axis

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		velocity.x += speed;	//goes +x axis



	//jumping mechanic
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump) {

		//plays Jump sound when spacebar is pressed
		playSound();

		//initializes cannot jump
		canJump = false;

		//velocity = square root of (2.0f * gravity * jumpHeight)
		//y axis in SFML is flipped
		velocity.y = -sqrt(2.0f * 981.0f * jumpHeight);		//velocity to jump up
	}


	//to fall down again
	velocity.y += 981.0f * deltaTime;




	//if no key is pressed, idle animation plays
	if (velocity.x == 0.0f) {
		row = 0;
	}
	else {
		row = 2;

		//if player is moving on a -x axis, they are facing left, and sprite is flipped on its axis to face left
		if (velocity.x > 0.0f)
		faceRight = true;
			else 
				faceRight = false;

	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}


void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body); //draws the player body on the window
}

void Player::onCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f) {
		//collision on the left
		velocity.x = 0.0f;	//stops the player

	}
	else if (direction.x > 0.0f) {
		//collision on the right
		velocity.x = 0.0f;	//stops the player
	}

	if (direction.y < 0.0f) {
		//Collision on the bottom
		velocity.y = 0.0f;
		canJump = true;	//because player is now touching the ground, player can jump again
	}
	else if (direction.y > 0.0f) {
		//collision on top
		velocity.y = 0.0f;
	}
}

void Player::playSound() {
	sound.openFromFile("Jump.wav");
	sound.setVolume(60);
	sound.play();
}
