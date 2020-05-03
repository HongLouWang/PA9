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

void login::login_start()
{
	cout << "CHOOSE WHAT TO DO:" << endl;
	cout << "1.LOGIN" << endl;
	cout << "2.SIGN UP FOR NEW ACCOUNT!" << endl;
	char *userInput = new char;
	cin >> userInput;

	char username[128];
	char password[128];
	char repassword[128];

	if (strcmp(userInput, "1") == 0)
	{
		ZeroMemory(name, 128);
		log_in();
	}
	else if (strcmp(userInput, "2") == 0)
	{
		ZeroMemory(name, 128);
		signup();
	}
}

void login::log_in()
{
	char username[128];
	char password[128];
	char repassword[128];
	do
	{	
		label:
		ZeroMemory(username, 128);
		ZeroMemory(password, 128);
		ZeroMemory(repassword, 128);
		if (!correctInfo)
		{
			correctInfo = true;
			cout << "USERNAME OR PASSWORD ILLEGAL" << endl;
		}
		cout << "INPUT YOUR USERNAME!" << endl;
		cin >> username;
		cout << "INPUT YOUR PASSWORD!" << endl;
			cin >> password;
		if (login_sendInfo(username, password) == true)
		{
			islogin = true;
		}
		else
		{
			correctInfo = false;
			goto label;
		}
	} while (!usernameCheck(username));
}
void login::signup()
{
	char username[128];
	char password[128];
	char repassword[128];
	do
	{
	label:
		ZeroMemory(username, 128);
		ZeroMemory(password, 128);
		ZeroMemory(repassword, 128);
		if (!correctInfo)
		{
			correctInfo = true;
			cout << "USERNAME OR PASSWORD illegal" << endl;
		}
		cout << "NEW USERS!" << endl;
		cout << "PLEASE INPUT YOUR USERNAME!" << endl;
		cin >> username;
		cout << "PLEASE INPUT YOUR PASSWORD" << endl;
		cin >> password;
		cout << "PLEASE RE-INPUT YOUR PASSWORD" << endl;
		cin >> repassword;

		if (!usernameCheck(username))
		{
			correctInfo = false;
			goto label;
		}

		if (!passwordCheck(password, repassword))
		{
			correctInfo = false;
			goto label;
		}

		if (signup_sendInfo(username, password) == true)
		{
			islogin = true;
		}
		else
		{
			goto label;
		}
	} while (!usernameCheck(username));
	
}

bool login::usernameCheck(char username[128])
{
	//no puncuation in username, only accept char lower than 128
	for (int i = 0; i < sizeof(username); i++)
	{
		if (username[i] > 128)
		{
			//username illegal
			return false;
		}
	}
	//username legal
	return true;
}
bool login::passwordCheck(char password[128], char repassword[128])
{
	//no puncuation in password, only accept char lower than 128
	for (int i = 0; i < sizeof(password); i++)
	{
		if (password[i] > 128)
		{
			//password illegal
			return false;
		}
	}

	if (strcmp(password, repassword) == 0)
	{
		//password legal
		return true;
	}
	//password illegal
	return false;
}

//SEND LOGIN INFROMATION
bool login::login_sendInfo(char username[128], char password[128])
{
	udp_client_sender udp_send;
	udp_client_receiver udp_rec;
	char mess[4096];
	ZeroMemory(mess, 4096);
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
	while (strcmp(udp_rec.getMessage(),"") != 0)
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
bool login::signup_sendInfo(char username[128], char password[128])
{
	udp_client_sender udp_send;
	udp_client_receiver udp_rec;
	char mess[4096];
	ZeroMemory(mess, 4096);
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
	while (strcmp(udp_rec.getMessage(), "") != 0)
	{
		if (strcmp(udp_rec.getMessage(), "OK") == 0)
		{
			//sign up success
			islogin = true;
			//set up username
			strcpy(name, username);
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

bool login::isLogin()
{
	return islogin;
}