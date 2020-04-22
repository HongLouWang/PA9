#include "Animation.h"

Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime){

	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;
	
	//gets size of the sprite
	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);
}


Animation::~Animation()
{
	//destructor 
}

void Animation::Update(int row, float deltaTime, bool faceRight)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime) {
		totalTime -= switchTime;
		currentImage.x++;	//moves to the next sprite

		//checks if currentImage is over the imageCount, sets it back to the first image as cycle
		if (currentImage.x >= imageCount.x) {
			currentImage.x = 0; 
		}
	}


	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;

	//to make character flip on y-axis if facing left
	if (faceRight) {
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.width = abs(uvRect.width);
	}
	else {
		uvRect.left = (currentImage.x +1)* abs(uvRect.width);
		uvRect.width = -abs(uvRect.width);

	}
}
