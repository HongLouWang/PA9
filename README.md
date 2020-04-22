PA 9 to do list lets get it

-sign up for Google Forms group
https://docs.google.com/forms/d/e/1FAIpQLSd_mB02M9FP86rbHz5rBZwfO6XsjI8BC3texqiRAXYmLLDDzQ/viewform

-Zoom ID: 751-791-2054

-This is the YouTube Playlist I referenced to learn SFML lol https://www.youtube.com/playlist?list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9

-Ground
	-Generate ground while player moves //i just generated 1000 ground in advance, can last player for ~5 minutes
	-generate as time passes? or generate as last generated tile is near to x = 0

-obstacles
	-create obstacles for the game	//Done, but using vectors, if collision is applied, animation cannot be applied vice versa
	-apply collision logic on the obstacle	//Done
	-apply texture to the obstacle		//Done
	-generate obstacles along with the ground	//Generated 900 of them in advance

-player
	-make player constantly move to the right	//Done, for debug purposes still controlled using keys
	-create function that when user presses spacebar, player jumps //DONE
	-collision logic with the obstacle.	//Done? sort of

-gameplay	
	-Increase speed of the player after a set amount of time. (means increases the diffculty)
	-every second counts as +1 score. (Clock.h)? //sfml has Clock and Time library
	-function for scoring system
	-function to save scoring system and display upon player death
	-function to detect if player collided with obstacle
	-apply texture to background of the game [OPTIONAL]
	-background music for the game //Done