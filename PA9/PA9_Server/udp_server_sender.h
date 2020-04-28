/*******************************************************************************************
* Programmer: Shutian Wang *
* Class: CptS 122, Spring, 2020; Lab Section 14 *
* Programming Assignment: PA9 *
* Date: Apr 27, 2020 *
* Description: PA9 SERVER SIDE UDP SENDER HEADER*
*******************************************************************************************/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

class udp_server_sender
{
public:
	udp_server_sender()
	{
		port = 0;
		ZeroMemory(ip, 256);
		ZeroMemory(message, 4096);
	}

	~udp_server_sender(){}

	void sendMessage();

	void setMessage(char mess[4096]);
	void setIP(char addr[256]);
	void setPort(int p);

	string getMessage();
	string getIP();
	int getPort();
private:
	
	char message[4096];
	char ip[256];
	int port;
	
};



