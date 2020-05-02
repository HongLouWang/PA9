#include "udp_client_receiver.h"

void udp_client_receiver::startUDPclient()
{
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

	sockaddr_in client;
	int clientLength = sizeof(client);
	ZeroMemory(&client, clientLength);

	int timeout = 10000000;
	int bytesIn;
	while (true)
	{
		//Wait for message
		int bytesIn = recvfrom(in, message, 4096, 0, (sockaddr*)&client, &clientLength);
		if (bytesIn == SOCKET_ERROR)
		{
			cout << "Error receiving from client " << WSAGetLastError << endl;
			continue;
		}
		if (strcmp(message, "") != 0)
		{
			break;
		}
	}

	//close socket
	closesocket(in);
	//shutdown winsock
	WSACleanup();
}

void udp_client_receiver::setPort(int p)
{
	port = p;
}

void udp_client_receiver::setOut(string str)
{

}

void udp_client_receiver::setData(WSADATA wsaData)
{
	data = wsaData;
}

void udp_client_receiver::setVersion(WORD ver)
{
	version = ver;
}

void udp_client_receiver::setMessage(char mess[4096])
{
	strcpy(message, mess);
}

void udp_client_receiver::setClientIP(char client[256])
{
	strcpy(clientIP, client);
}

int udp_client_receiver::getPort()
{
	return port;
}

string udp_client_receiver::getOut()
{
	return "";
}

WSADATA udp_client_receiver::getData()
{
	return data;
}

char* udp_client_receiver::getMessage()
{
	return message;
}

WORD udp_client_receiver::getVersion()
{
	return version;
}

char udp_client_receiver::getClientIP()
{
	return *clientIP;
}

void udp_client_receiver::freeMessage()
{
	ZeroMemory(message, 4096);
}