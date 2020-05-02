/*******************************************************************************************
* Programmer: Shutian Wang *
* Class: CptS 122, Spring, 2020; Lab Section 14 *
* Programming Assignment: PA9 *
* Date: Apr 27, 2020 *
* Description: PA9 LOGIN FUNCTION*
*******************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "login.h"
#include "../UDP/udp_client_sender.h"
#include "../UDP/udp_client_receiver.h";
#include "../udp/udp_config.h"

using namespace std;

void login_start()
{
	cout << "CHOOSE WHAT TO DO:" << endl;
	cout << "1.LOGIN" << endl;
	cout << "2.SIGN UP FOR NEW ACCOUNT!" << endl;

	char *userInput = new char;
	char username[128];
	char password[128];
	char repassword[128];

	if (strcmp(userInput, "1") == 0)
	{
		cout << "INPUT YOUR USERNAME!" << endl;
		cin >> username;
		cout << "INPUT YOUR PASSWORD!" << endl;
		cin >> password;
		login_sendInfo(username, password);
	}
	else if (strcmp(userInput, "2") == 0)
	{
		cout << "NEW USERS!" << endl;
		cout << "PLEASE INPUT YOUR USERNAME!" << endl;
		cin >> username;
		cout << "PLEASE INPUT YOUR PASSWORD" << endl;
		cin >> password;
		cout << "PLEASE RE-INPUT YOUR PASSWORD" << endl;
		cin >> repassword;

	}
}

//SEND LOGIN INFROMATION
bool login_sendInfo(char username[128], char password[128])
{
	udp_client_sender udp_send;
	udp_client_receiver udp_rec;
	char mess[4096];
	char ip[256] = DEFAULT_SERVER_IP;	//THE SERVER IP
	strcat(mess, "0001-");	//0001--LOGIN

	strcat(mess, username);
	strcat(mess, "-");
	strcat(mess, password);

	udp_send.setIP(ip);
	udp_send.setPort(DEFAULT_SEND_PORT);	//THE SERVER PORT
	udp_send.setMessage(mess);
	udp_send.sendMessage();

	//WAIT FOR RESPONSE
	udp_rec.setPort(DEFAULT_RECE_PORT);	//SET RECEIVE PORT
	udp_rec.startUDPclient();
	while (strcmp(udp_rec.getMessage(),"") == 0)
	{
		if (strcmp(udp_rec.getMessage(), "OK") == 0)
		{
			//login success
			islogin = true;
			//set username
			strcpy(name, username);
			return true;
		}
		if (strcmp(udp_rec.getMessage(), "ERROR") == 0)
		{
			//login error username or password wrong
			islogin = false;
			return false;
		}
	}
	udp_send.freeMessage();
	return false;
}

//SEND SIGNUP INFORMATION
bool signup_sendInfo(char username[128], char password[128])
{
	udp_client_sender udp_send;
	udp_client_receiver udp_rec;
	char mess[4096];
	char ip[256] = DEFAULT_SERVER_IP;	//THE SERVER IP
	strcat(mess, "0002-");	//0002--SIGNUP
	strcat(mess, username);
	strcat(mess, "-");
	strcat(mess, password);

	udp_send.setIP(ip);
	udp_send.setPort(DEFAULT_SEND_PORT);
	udp_send.setMessage(mess);
	udp_send.sendMessage();
	udp_rec.setPort(DEFAULT_RECE_PORT);
	udp_rec.startUDPclient();
	while (strcmp(udp_rec.getMessage(), "") == 0)
	{
		if (strcmp(udp_rec.getMessage(), "OK") == 0)
		{
			//sign up success
			islogin = true;
			return true;
		}
		if (strcmp(udp_rec.getMessage(), "ERROR") == 0)
		{
			//username exist
			islogin = false;
			return false;
		}
	}
	udp_send.freeMessage();
	return false;
}

bool isLogin()
{
	return islogin;
}