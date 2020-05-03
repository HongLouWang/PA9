#pragma once
#ifndef _UDP_CLIENT_RECEIVER_H_
#define _UDP_CLIENT_RECEIVER_H_
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std;
class udp_client_receiver
{
public:
	udp_client_receiver()
	{
		port = 0;
		out = "";
		isMessage = false;
		ZeroMemory(clientIP, 256);
		ZeroMemory(message, 4096);
	}
	~udp_client_receiver() {}

	//start udp client
	void startUDPclient();

	void setPort(int p);
	void setOut(string str);
	void setData(WSADATA wsaData);
	void setVersion(WORD ver);
	void setMessage(char mess[4096]);
	void setClientIP(char client[256]);

	//free message
	void freeMessage();

	int getPort();
	string getOut();
	WSADATA getData();
	WORD getVersion();
	char* getMessage();
	char getClientIP();

private:
	int port;
	string out;
	bool isMessage;

	WSADATA data;
	WORD version;
	sockaddr_in client;

	char message[4096];
	char clientIP[256];
};
#endif // !_UDP_CLIENT_RECEIVER_H_
