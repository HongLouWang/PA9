/*******************************************************************************************
* Programmer: Shutian Wang *
* Class: CptS 122, Spring, 2020; Lab Section 14 *
* Programming Assignment: PA9 *
* Date: Feb 24, 2020 *
* Description: PA9 SERVER SIDE UDP RECEIVER HEADER*
*******************************************************************************************/
#pragma once
#include <iostream>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std;
class udp_server_windows
{
public:
	udp_server_windows()
	{
		port = 0;
		out = "";
		ZeroMemory(clientIP, 256);
		ZeroMemory(message, 4096);
	}
	~udp_server_windows(){}

	void startServer();

	void setPort(int port);
	void setOut(string str);
	void setData(WSADATA wsaData);
	void setVersion(WORD ver);
	void setMessage(char mess[4096]);
	void setClientIP(char client[256]);

	int getPort();
	string getOut();
	WSADATA getData();
	WORD getVersion();
	char getMessage();
	char getClientIP();

private:
	int port;
	string out;

	WSADATA data;
	WORD version;
	sockaddr_in client;

	char message[4096];
	char clientIP[256];
};
