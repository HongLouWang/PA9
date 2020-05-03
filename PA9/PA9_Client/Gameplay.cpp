#include "Gameplay.h"



Gameplay::Gameplay()
{
}


Gameplay::~Gameplay()
{
}

void Gameplay::playGame()
{

	//renders window and its properties
	sf::RenderWindow window(sf::VideoMode(640, 480), "RAD-ish!!", sf::Style::Close | sf::Style::Resize);

	//plays background music
	sf::Music music;
	if (!music.openFromFile("Background.wav")) {
		std::cout << "ERROR" << std::endl;
	}
	music.play();
	music.setLoop(true);

	//camera follows the player
	sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(640.0f, 480.0f));

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
	Player player(&playerTexture, sf::Vector2u(3, 4), 0.2f, 200.0f, 140.0f);
	//texture, imageCount, switchTime, position		
	Obstacle obstacle(&obstacleTexture, sf::Vector2u(4, 1), 0.1f, sf::Vector2f(100.0f, 380.0f));

	//declares vectors for ground and obstacle objects 
	std::vector<Platform> ground;
	std::vector<Obstacle> obst;

	//wil change these cheat ways to increment by time if there's stil time left to finish the assignment, though generating 1000 ground is enough for more than an hour of gameplay.
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
	
	float speed = 200.0f;
	float deltaTime = 0.0f;
	sf::Clock clock;	//clock starts running as soon as it is created
	sf::Clock timer;	//timer for time elapsed in game. cannot use clock as it will be restarted to keep track of deltaTime
	sf::Clock points;
	

	while (window.isOpen()) {
		sf::Event evt;

		setscore(points.restart().asSeconds());
		deltaTime = clock.restart().asSeconds();

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

		

		//timekeeping, uses sf::Clock timer as the timer. Gets elapsed time
		sf::Time elapsed = timer.getElapsedTime();


		//timer restarts every 7 seconds, speed increases by 30.0f every 7 seconds
		if (timer.getElapsedTime().asSeconds() >= 7.0000) {
			elapsed += timer.restart();
			speed += 30.0f;	
		}
		//print out time as testing
		std::cout << elapsed.asSeconds() << std::endl;

		sf::Vector2f direction;

		Collider playerCollision = player.GetCollider();

		//applies Platform collision logic to each ground	
		for (Platform &platform : ground) {																						//essentially does this
				if (platform.GetCollider().CheckCollision(playerCollision, direction, 1.0f))									//for (int i = 0; i < ground.size(); i++) {
				player.onCollision(direction);																					//	Platform& platform = platforms[i];
		}																														//	}	


		  /////////////////////////////////////////////////////////////////
		 //////IMPORTANT OBSTACLE COLLISION LOGIC//////////////////////////
		////when player hits an obstacle//////////////////////////////////
	   ////applies Collision logic to each obstacle//////////////////////
	  ////once player collides with obstacle, isDead() becomes true. ///
	 //////////////////////////////////////////////////////////////////
		for (Obstacle &o : obst) {
			// updates score before possible collision
			setscore(points.getElapsedTime().asSeconds());
			if (o.GetCollider().CheckCollision(playerCollision, direction, 1.0f)) {	
				player.onCollision(direction);
				setIsColliding(true);
				isDead();
			}
			else {
				setIsColliding(false);
			}
		}

		// updates score before pause
		setscore(points.getElapsedTime().asSeconds());
		//passes deltaTime and player speed to update Player. 
		//if pauseState() == true, pauses the game, stops updates of player and obstacles
		if (!pauseState()) {
			player.Update(deltaTime, speed);
			obstacle.Update(deltaTime);
		}
		else if (pauseState()) {
			player.Update(deltaTime, 0.0f);
		}

		// resets points for score after pause
		points.restart(); 

		//sets camera follows player
		view.setCenter(player.GetPosition());

		//clears the buffer when player moves
		window.clear();
		window.setView(view);
		//calls player to draw player on screen
		player.Draw(window);

		//draws the ground
		for (Platform &platform : ground) {
			platform.Draw(window);
		}

		for (Obstacle &o : obst) {
			o.Draw(window);
		}

		//calls windows to display
		window.display(); //double buffer	

		// sets total score
		setscore(getscore() + points.getElapsedTime().asSeconds());
	
	}
	window.close();
}


bool Gameplay::isDead()
{
	if (getIsColliding()) {
		std::cout << "ouch" << std::endl;	//this is just to test if collision is registering between player and obstacle
		std::cout << getscore() << std::endl; // to test the score is accurate
		setPauseState(true);
		createDeathMessage();

	return true;
	}
	else {
		return false;
	}

}

sf::Text Gameplay::createDeathMessage() {
	 //does not work for some reason
	sf::Font font;
	font.loadFromFile("Pixel.ttf");
	sf::Text text("GAME OVER!", font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(200);
	text.setPosition(sf::Vector2f(50.0f, 300.0f));

	return text;

}


void Gameplay::setIsColliding(bool status)
{
	isColliding = status;
}


bool Gameplay::getIsColliding()
{
	return isColliding;
}

bool Gameplay::pauseState()
{
	return isPaused;
}

void Gameplay::setPauseState(bool state)
{
	isPaused = state;
}

void Gameplay::restart()
{
	playGame();
	return;
}

int Gameplay::getscore()
{
	return score;
}

void Gameplay::setscore(int s)
{
	score = s;
}