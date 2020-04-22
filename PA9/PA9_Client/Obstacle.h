#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SFML\Graphics.hpp>
#include "Collider.h"
#include "Animation.h"

class Obstacle
{
public:
	Obstacle(sf::Texture *texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position);
	~Obstacle();

	//Updates animation and movement
	void Update(float deltaTime);

	void Draw(sf::RenderWindow &window);

	Collider GetCollider() {
		return Collider(body);
	}


private:
	sf::RectangleShape body;
	Animation animation;
	unsigned int row;
};

#endif