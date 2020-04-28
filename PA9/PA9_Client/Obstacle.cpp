#include "Obstacle.h"



Obstacle::Obstacle(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position):
	animation(texture, imageCount, switchTime)
{
	row = 0;
	body.setSize(sf::Vector2f(40.0f, 70.0f));
	body.setOrigin(body.getSize()/ 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}


Obstacle::~Obstacle()
{

}


void Obstacle::Update(float deltaTime) {
	row = 0;
	animation.Update(row, deltaTime, false);
	body.setTextureRect(animation.uvRect);
}


void Obstacle::Draw(sf::RenderWindow & window)
{
	window.draw(body);
}


