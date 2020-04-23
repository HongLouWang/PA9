/*******************************************************************************************
* Programmer: Shutian Wang *
* Class: CptS 122, Spring, 2020; Lab Section 14 *
* Programming Assignment: PA9 *
* Date: Feb 24, 2020 *
* Description: PA9 SERVER SIDE UDP RECEIVER*
*******************************************************************************************/
#include "udp_server_receiver.h"

using namespace std;

void udp_server_windows::startServer()
{
	//Startup winsock
	WSADATA data;
	WORD version = MAKEWORD(2, 2);

	int wsOK = WSAStartup(version, &data);
	if (wsOK != 0)
	{
		cout << "Can't start Winsock!";
	}

	//Bingd socket to ip address and port
	SOCKET in = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in serverHint;
	serverHint.sin_addr.S_un.S_addr = ADDR_ANY;
	serverHint.sin_family = AF_INET;
	serverHint.sin_port = htons(port);

	if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
	{
		cout << "Can't bind socket! " << WSAGetLastError() << endl;
	}
}

