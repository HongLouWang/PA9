#ifndef PLATFORM_H
#define PLATFORM_H

#include <SFML\Graphics.hpp>
#include "Collider.h"
#pragma once


//another "body" same as player, an entity
class Platform
{
public:
			//textures the platform
	Platform(sf::Texture *texture, sf::Vector2f size, sf::Vector2f position);
	~Platform();

	void Draw(sf::RenderWindow &window);
	Collider GetCollider() {
		return Collider(body);
	}

private:
	sf::RectangleShape body;
};


#endif