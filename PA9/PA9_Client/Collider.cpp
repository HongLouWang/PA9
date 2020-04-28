#include "Collider.h"

Collider::Collider() :body (body){
}

Collider::Collider(sf::RectangleShape &body) : body(body)
{
}


Collider::~Collider()
{
}

bool Collider::CheckCollision(Collider &other, sf::Vector2f &direction, float push)
{
		//delta = distance of the two origin points of the two entities
	//initializes the posn
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f otherHalfSize = other.GetHalfSize();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f thisHalfSize = GetHalfSize();

	//checks to see if they are colliding
	//calc distance between two entities
	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	//calculates intersect point btwn two entities
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f) {
			//clamps push posn: 0 <= push <= 1	
		push = std::min(std::max(push, 0.0f), 1.0f);
		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f) {

				//push from the left
				Move(intersectX * (1.0f - push), 0.0f);
				other.Move(-intersectX * push, 0.0f);	//repels the objects so collision wont keep happening
				
				//jumping code
				direction.x = 1.0f;
				direction.y = 0.0f;

			}
			else {
				//push from the right
				Move(-intersectX * (1.0f - push), 0.0f);
				other.Move(intersectX * push, 0.0f);

				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else {

			if (deltaY > 0.0f) {
				Move(0.0f, intersectY * (1.0f - push));	
				other.Move(0.0f , -intersectY* push);	//repels the objects so collision wont keep happening
			
				
				direction.x = 0.0f;
				direction.y = 1.0f;
			
			}
			else {
				Move(0.0f,-intersectY * (1.0f - push));
				other.Move(0.0f,intersectY * push);

				direction.x = 0.0f;
				direction.y = -1.0f;

			}


		}

		//yes, they are colliding
		return true;
	}

	//reaches the end when no collision is happening
	return false;
}