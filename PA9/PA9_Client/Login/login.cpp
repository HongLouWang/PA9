#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "login.h"
#include "../UDP/udp_client_sender.h"
#include "../UDP/udp_client_receiver.h";

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

void login_sendInfo(char username[128], char password[128])
{
	udp_client_sender udp_send;
	udp_client_receiver udp_rec;
	char mess[4096];
	char ip[256] = "127.0.0.1";
	strcat(mess, "0001-USERNAME-");	//0001--LOGIN
	strcat(mess, username);
	strcat(mess, "-PASSWORD-");
	strcat(mess, password);
	udp_send.setIP(ip);
	udp_send.setPort(54000);
	udp_send.setMessage(mess);
	udp_send.sendMessage();
	udp_rec.setPort(54001);
	while (strcmp(udp_rec.getMessage(),"") == 0)
	{
		if (strcmp(udp_rec.getMessage(), "OK") == 0)
		{
			//cout << "LOGIN" << endl;
			islogin = true;
		}
	}
	udp_send.freeMessage();
}

void signup_sendInfo(char username[128], char password[128])
{
	udp_client_sender udp_send;
	udp_client_receiver udp_rec;
	char mess[4096];
	char ip[256] = "127.0.0.1";
	strcat(mess, "0002-USERNAME-");	//0002--SIGNUP
	strcat(mess, username);
	strcat(mess, "-PASSWORD-");
	strcat(mess, password);
	udp_send.setIP(ip);
	udp_send.setPort(54000);
	udp_send.setMessage(mess);
	udp_send.sendMessage();
	udp_rec.setPort(54001);
	while (strcmp(udp_rec.getMessage(), "") == 0)
	{
		if (strcmp(udp_rec.getMessage(), "OK") == 0)
		{
			//cout << "SUGNUP" << endl;
			islogin = true;
		}
	}
	udp_send.freeMessage();
}

bool isLogin()
{
	return islogin;
}