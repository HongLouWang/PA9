#pragma once
#ifndef _UDP_CLIENT_SENDER_H_
#define _UDP_CLIENT_SENDER_H_
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")


#include <string>


using namespace std;

class udp_client_sender
{
public:
	udp_client_sender()
	{
		port = 0;
		ZeroMemory(ip, 256);
		ZeroMemory(message, 4096);
	}

	~udp_client_sender(){}

	//send message
	void sendMessage();

	void setMessage(char mess[4096]);
	void setIP(char addr[256]);
	void setPort(int p);

	string getMessage();
	string getIP();
	int getPort();

	//free message
	void freeMessage();
private:

	char message[4096];
	char ip[256];
	int port;

};

#endif //!_UDP_CLIENT_SENDER_H_