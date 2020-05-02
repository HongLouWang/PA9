PA 9 to do list lets get it

-sign up for Google Forms group
https://docs.google.com/forms/d/e/1FAIpQLSd_mB02M9FP86rbHz5rBZwfO6XsjI8BC3texqiRAXYmLLDDzQ/viewform

-Zoom ID: 751-791-2054

-This is the YouTube Playlist I referenced to learn SFML lol https://www.youtube.com/playlist?list=PL21OsoBLPpMOO6zyVlxZ4S4hwkY_SLRW9

-Ground<br />
-Generate ground while player moves //i just generated 1000 ground in advance, can last player for ~1 hour<br />

-obstacles<br />
-create obstacles for the game	//Done, but using vectors, if collision is applied, animation cannot be applied vice versa<br />
-apply collision logic on the obstacle	//Done<br />
-apply texture to the obstacle		//Done<br />
-generate obstacles along with the ground	//Generated 900 of them in advance<br />

-player<br />
-make player constantly move to the right	//Done, for debug purposes still controlled using keys<br />
-create function that when user presses spacebar, player jumps //DONE<br />
-collision logic with the obstacle.	//DONE<br />

-gameplay<br />	
-Increase speed of the player after a set amount of time. //DONE (player speeds up every 7 seconds)<br />
-every second counts as +1 score. (Clock.h)? //sfml has Clock and Time library<br />
-function for scoring system<br />
-function to save scoring system and display upon player death<br />
-function to detect if player collided with obstacle //DONE <br />
-apply texture to background of the game [OPTIONAL]<br />
-background music for the game //Done<br />
<br />
-Create login function<br />

-server side<br />
-Create an UDP connection<br />
-Create login function<br />
-Create a score ranking(maybe use database)<br />

<br />

-UI<br />
	-Display GAME OVER Text when game is stopped and player collides with obstacle<br />
	-implement restart button on screen (or "press enter to restart") to loop playGame()<br />
	-when player hits the obstacle, give players option to restart<br />
	-display text/graphics onto the game window to state "Press Spacebar to Jump" <br /><br />
-REMIND<br />
	-This program may only run on windows<br />
	-Please confirm you have ws2_32.lib on your computer and you are allow to use socket communication<br />
	-Please run the server program first, the default server ip is 127.0.0.1(ipv4), the default server receive port is 54000, the default client receiver port is 540001, you can change that in udp_config.h<br />
	-After you first run the program, there will be an UAC alert pop up, please allow the program to have internet access, that's important! If see something like "Can't start Winsock!" please check if you have ws2_32.lib and the program is allowed to have internet access. If see something like "Can't bind socket!", please check the firewall and check the network listening port if other process is using 54000 and 54001, if so, please kill the process<br />
	-Please make sure Windows Universal CRT SDK is installed when you are compiling the program

