#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <iostream>


class Animation
{
public:
			//passes in texture's size, amount of images, how long the total animation is
	Animation(sf::Texture *texture, sf::Vector2u imageCount,float switchTime);
	~Animation();

	//what row to access, and deltaTime = time between next frame to current time, faceRight = is character facing right?
	void Update(int row, float deltaTime, bool faceRight);



public:
	sf::IntRect uvRect; //the uvcoords of the sprite

private:
	//creates to store the amount of images nad cycles it to create an animation
	sf::Vector2u imageCount;	//how many images in an animation?
	sf::Vector2u currentImage;	//coords of the current image

	//controls speed of the animation, how fast the images change
	float totalTime;	
	float switchTime; //time taken to switch to the next image

};




#endif

