#ifndef COLLIDER_H
#define COLLIDER_H
#include <SFML\Graphics.hpp> 
#include <iostream>
#include <cmath>

class Collider
{
public:
	Collider();
	Collider(sf::RectangleShape &body);
	~Collider();


	void Move(float dx, float dy) {
		body.move(dx, dy);
	}

									//how much each objects needs to be pushed out
									//0, player cannot got through the object
									//1, payer can "push" it, 0.5, player pushes it but slowly 
	bool CheckCollision(Collider &other,sf::Vector2f &direction, float push);
	
	sf::Vector2f GetPosition() {
		return body.getPosition();
	}
	sf::Vector2f GetHalfSize() {
		return body.getSize() / 2.0f;
	}

private:
	sf::RectangleShape &body;
};


#endif