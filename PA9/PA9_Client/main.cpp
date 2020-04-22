/*
CPTS 122 SPR 2020
PA9

Description:

//Player sprites are from rpgtileset.com/sprite/running-radish-sprite-for-rpg-maker-mv/
*/

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include "Animation.h"
#include "Player.h"
#include "Platform.h"
#include "Obstacle.h"
#include <vector>

static const float VIEW_HEIGHT = 480.0f;
//makes every sprite the same size and posn when window is resized
void ResizeView(sf::RenderWindow &window, sf::View& view) {
	float aspectRatio = float(window.getSize().x) / float(window.getSize().y);

	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}


int main() {

	//renders window and its properties
	sf::RenderWindow window(sf::VideoMode(640,480), "RAD-ish!!", sf::Style::Close| sf::Style::Resize);

	//plays background music
	sf::Music music;
	if (!music.openFromFile("Background.wav")) {
		std::cout<<"ERROR"<<std::endl;
	}
	//music.play();
	//music.setLoop(true);

	//camera follows the player
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(640.0f, 480.0f));
						

	//set player size (a rectangle)		
	//sf::RectangleShape player(sf::Vector2f(65.0f, 80.0f));//vector 2float, or 2i(int), 2u(unsigned int)
	//player.setFillColor(sf::Color::Magenta); //sets color of rectangle
	//player.setOrigin(50.0f, 50.0f); //sets original point of the player rectangle
	//player.setPosition(206.0f, 206.0f);	

	//applies texture to player
	sf::Texture playerTexture; //declares texture from texture class
	playerTexture.loadFromFile("Textures/Radad1.png");	//loads the picture file
	//player.setTexture(&playerTexture);	//applies picture file to the playertexture
	sf::Texture platformTexture;
	platformTexture.loadFromFile("Textures/ground.png");
	
	//obstacle texture
	sf::Texture obstacleTexture;
	//obstacleTexture.loadFromFile("Textures/blades.png");
	obstacleTexture.loadFromFile("Textures/blade1.png");


				//texture, imageCount, switchtime,speed at which sprite "moves", jumpHeight
	Player player(&playerTexture, sf::Vector2u(3,4), 0.2f, 200.0f, 140.0f);
					//texture, imageCount, switchTime, position		
	Obstacle obstacle(&obstacleTexture, sf::Vector2u(4, 1), 0.1f, sf::Vector2f(100.0f, 380.0f));
											//texture , platform size (x,y) , position 
	//Platform ground(&platformTexture, sf::Vector2f(300.0f, 80.0f), sf::Vector2f(1.0f, 458.0f));
	//Platform platform2(nullptr, sf::Vector2f(100.0f, 50.0f), sf::Vector2f(1.0f, 500.0f));

	//declares vector 
	std::vector<Platform> ground;
	std::vector<Obstacle> obst;

	//ground.push_back(Platform(&platformTexture, sf::Vector2f(300.0f, 80.0f), sf::Vector2f(0.0f, 458.0f)));
	//ground.push_back(Platform(&platformTexture, sf::Vector2f(300.0f, 80.0f), sf::Vector2f(300.0f, 458.0f)));
	//ground.push_back(Platform(&platformTexture, sf::Vector2f(300.0f, 80.0f), sf::Vector2f(600.0f, 458.0f)));


	//cheat way of just generating 1000 ground
	float x = 0.0f;
	for (int j = 0; j < 1000; ++j) {
		ground.push_back(Platform(&platformTexture, sf::Vector2f(300.0f, 80.0f), sf::Vector2f(x, 458.0f)));
		x += 300.f;
	}

	//cheat way of generating 900 obstacles
	float y = 500.0f;
	for (int i = 0; i < 900; ++i) {
		obst.push_back(Obstacle(&obstacleTexture, sf::Vector2u(4, 1), 0.1f, sf::Vector2f(y, 380.f)));
		y += 500.0f;
	}


	////selects a sprite from a 3x9 pictures of sprites
	//sf::Vector2u textureSize = playerTexture.getSize();
	//textureSize.x /= 3;	//how many columns of sprites
	//textureSize.y /= 4;		//how may rows of sprites


	//										//array posn of sprite in png file. strts from 0
	//player.setTextureRect(sf::IntRect(textureSize.x * 0, textureSize.y * 2, textureSize.x, textureSize.y));

	float deltaTime=0.0f;
	sf::Clock clock;
	while (window.isOpen()) {
		sf::Event evt;

		deltaTime=clock.restart().asSeconds();

		//to keep score as seconds elapsed
			//float score = 0.0f;
			//score = clock.getElapsedTime().asSeconds();
			//std::cout << score << std::endl;
			//system("cls");


		//locks to 20 fps framerate to prevent errors when resizing window
		if (deltaTime > 1.0f / 20.0f) {
			deltaTime = 1.0f / 20.0f;
		}

		//while window is open, can move the window, and user can close the window
		while (window.pollEvent(evt)) {

			//event to close window
			switch (evt.type) {
			case sf::Event::Closed:
				window.close();
				break;

			//event to get text input from keyboard to console
			case sf::Event::TextEntered:
				if (evt.text.unicode < 128) {
					printf("%c", evt.text.unicode);  //std::cout << evt.text.unicode;

					
				}

			}

		}

		////codeblock to move the player with keyboard
		////checks if specified key is pressed on the Keyboard
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		//	//moves the player on x or y axis
		//	player.move(-0.1f,0.0f);  //this moves the player on the -x-axis, which is left.
		//			// (  x  ,  y ) 	
		//}

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		//	//moves the player on x or y axis
		//	player.move(0.1f, 0.0f);  

		//}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
		//	//moves the player on x or y axis
		//	player.move(0.0f, -0.1f);  

		//}
		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
		//	//moves the player on x or y axis
		//	player.move(0.0f, 0.1f); 

		//}

		////move player with mouse button
		//	// namespace::class::function(namespace::class:function)
		//if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		//	sf::Vector2i mousePos = sf::Mouse::getPosition(window); //gets posn of the top left corner of the window
		//	printf("%d, %d,", sf::Mouse::getPosition());
		//	//player.setPosition((float)mousePos.x/*converts an integer to float*/,static_cast<float>(mousePos.y)/*this is safe casting*/);
		//}


		player.Update(deltaTime);
		obstacle.Update(deltaTime);


		sf::Vector2f direction;
		
		Collider playerCollision = player.GetCollider();
		
		//applies Platform collision logic to each ground
		for (Platform &platform : ground){
			if (platform.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
				player.onCollision(direction);
		//essentially does this
		/*for (int i = 0; i < ground.size(); i++) {
			Platform& platform = platforms[i];
		}
		*/
		}

		//applies Collision logic to each obstacle
		for (Obstacle &o : obst) {
			if (o.GetCollider().CheckCollision(playerCollision, direction, 1.0f))
				player.onCollision(direction);
		}
	
		//ground.GetCollider().CheckCollision(playerCollision, 1.0f);
		//platform2.GetCollider().CheckCollision(playerCollision, 0.7f);

		//sets camera follows player
		view.setCenter(player.GetPosition());

				//gets 3rd row of the sprite image
		//anim.Update(2, deltaTime,false);
		//then sets the texture with corresp. texture
		//player.setTextureRect(anim.uvRect);	

		//clears the buffer when player moves
		window.clear();
		window.setView(view);
		//calls player to draw player on screen
		player.Draw(window);
		//calls obstacle to draw animated obstacle on screen
		//obstacle.Draw(window);

		//draws the ground
		for (Platform &platform : ground) {
			platform.Draw(window);
		}	

		for (Obstacle &o : obst) {
			o.Draw(window);
		}

		//calls windows to display
		window.display(); //double buffer


	}

	return 0;
}

