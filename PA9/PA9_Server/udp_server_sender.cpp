#include "udp_server_sender.h"

void udp_server_sender::sendMessage()
{
	//Startup winsock
	WSADATA data;
	WORD version = MAKEWORD(2, 2);

	int wsOK = WSAStartup(version, &data);
	if (wsOK != 0)
	{
		cout << "Can't start Winsock!";
	}

	//Create a hint structure for the server
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	inet_pton(AF_INET, ip, &server.sin_addr);

	//socket creation
	SOCKET out = socket(AF_INET, SOCK_DGRAM, 0);
	int sendOK = sendto(out, getMessage().c_str(), getMessage().size() + 1, 0, (sockaddr*)&server, sizeof(server));

	if (sendOK == SOCKET_ERROR)
	{
		cout << "That didn't work!" << WSAGetLastError() << endl;
	}

	//close socket
	closesocket(out);
	//shutdown winsock
	WSACleanup();
}

void udp_server_sender::setMessage(char mess[4096])
{
	strcpy(message, mess);
}
void udp_server_sender::setIP(char addr[256])
{
	strcpy(ip, addr);
}

void udp_server_sender::setPort(int p)
{
	port = p;
}

string udp_server_sender::getMessage()
{
	return message;
}

string udp_server_sender::getIP()
{
	return ip;
}
int udp_server_sender::getPort()
{
	return port;
}

