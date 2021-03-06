/*******************************************************************************************
* Programmer: Shutian Wang *
* Class: CptS 122, Spring, 2020; Lab Section 14 *
* Programming Assignment: PA9 *
* Date: Apr 27, 2020 *
* Description: PA9 SERVER SIDE UDP RECEIVER*
*******************************************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "user-auth.h"
#include "udp_server_receiver.h"
#include "udp_server_sender.h"
#include "ranklist.h"
#include <cstdlib>
#include <Windows.h>
#include <chrono>
#include <thread>
#include <cstring>

using namespace std;

void udp_server_receiver::startUDPServer()
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
	serverHint.sin_addr.S_un.S_addr = DEFAULT_RECE_FROM;
	serverHint.sin_family = DEFAULT_ADDR_TYPE;
	serverHint.sin_port = htons(port);

	if (bind(in, (sockaddr*)&serverHint, sizeof(serverHint)) == SOCKET_ERROR)
	{
		cout << "Can't bind socket! " << WSAGetLastError() << endl;
	}

	sockaddr_in client;
	int clientLength = sizeof(client);
	ZeroMemory(&client, clientLength);

	cout << "SERVER STARTED!" << endl;
	while (true)
	{
		//Wait for message
		int bytesIn = recvfrom(in, message, 4096, 0, (sockaddr*)&client, &clientLength);
		if (bytesIn == SOCKET_ERROR)
		{
			cout << "Error receiving from client " << WSAGetLastError << endl;
			continue;
		}

		//Display message and client info
		inet_ntop(AF_INET, &client.sin_addr, clientIP, 256);
		cout << "Message recv from " << clientIP << ":" << message << endl;
		
		//Fetch the message send from user
		result_fetch(message);
		
	}

	//close socket
	cout << "SERVER STOPPING..." << endl;
	closesocket(in);
	//shutdown winsock
	WSACleanup();
	cout << "SERVER STOPPED!" << endl;
}
	
void udp_server_receiver::result_fetch(char result[4096])
{
	this_thread::sleep_for(chrono::milliseconds(100));
	if (strncmp(result, "0001", 4) == 0)	//LOGIN
	{
		char username[128], password[128];

		ZeroMemory(username, 128);
		ZeroMemory(password, 128);
		char* content[10];
		int num = sizeof(result);
		split(result, "-", content, &num);
		strcpy(username, content[1]);
		strcpy(password, content[2]);
		if (login_match(username,password) == true)
		{
			//username and password match
			udp_server_sender udp_send;
			char mess[4096];
			ZeroMemory(mess, 4096);
			strcpy(mess, "OK");
			udp_send.setIP(clientIP);
			udp_send.setPort(DEFAULT_SEND_PORT);
			udp_send.setMessage(mess);
			udp_send.sendMessage();

			//return true;
		}
		else
		{
			//username and password un match
			udp_server_sender udp_send;
			char mess[4096];
			ZeroMemory(mess, 4096);
			strcpy(mess, "ERROR");
			udp_send.setIP(clientIP);
			udp_send.setPort(54001);
			udp_send.setMessage(mess);
			udp_send.sendMessage();

			//return false;
		}
	}
	else if (strncmp(result, "0002", 4) == 0)	//SIGNUP
	{
		char username[128], password[128];

		ZeroMemory(username, 128);
		ZeroMemory(password, 128);

		char* content[10];
		int num = sizeof(result);
		split(result, "-", content, &num);
		strcpy(username, content[1]);
		strcpy(password, content[2]);
		if (sign_up_infocheck(username) == true)
		{
			//sign up success
			userinfo* user = load();
			sign_up(username, password, user);

			ranklist rank;
			list* l;
			list** l_ptr;
			char score[128] = "0000";
			l = rank.load();
			l_ptr = &l;
			rank.insert(username, score, l_ptr);
			rank.store(l);

			udp_server_sender udp_send;
			char mess[4096];
			ZeroMemory(mess, 4096);
			strcpy(mess, "OK");
			udp_send.setIP(clientIP);
			udp_send.setPort(DEFAULT_SEND_PORT);
			udp_send.setMessage(mess);
			udp_send.sendMessage();

			//return true;
		}
		else
		{
			//sign up false, username exist
			udp_server_sender udp_send;
			char mess[4096];
			ZeroMemory(mess, 4096);
			strcpy(mess, "ERROR");
			udp_send.setIP(clientIP);
			udp_send.setPort(54001);
			udp_send.setMessage(mess);
			udp_send.sendMessage();

			//return false;
		}
	}
	else if (strncmp(result, "0003", 4) == 0)	//SET SCORE
	{
		char username[128], score[128];
		ZeroMemory(username, 128);
		ZeroMemory(score, 128);

		char* content[10];
		int num = sizeof(result);
		split(result, "-", content, &num);
		strcpy(username, content[1]);
		strcpy(score, content[2]);

		//SET SCORE AT HERE
		ranklist rank;
		list* l;
		l = rank.load();
		rank.update(username,score,l);
	}
	else if (strncmp(result, "0004", 4) == 0)	//GET SCORE
	{
		char username[128];
		ZeroMemory(username, 128);
		char* content[10];
		int num = sizeof(result);
		split(result, "-", content, &num);
		strcpy(username, content[1]);

		//get rank at here
		string listscore;
		ranklist rank;
		list* l;
		l = rank.load();
		rank.readyToSend(l);
		listscore = rank.scoreToSend;

		//send rank to client
		udp_server_sender udp_send;
		udp_send.setIP(clientIP);
		udp_send.setPort(DEFAULT_SEND_PORT);

		char mess[4096];
		char *cont[1024];
		char list_cont[sizeof(list) + 1];
		strcpy(list_cont, listscore.c_str());

		udp_send.setMessage(list_cont);
		udp_send.sendMessage();
		udp_send.freeMessage();
		
		char endMessage[4096];
		ZeroMemory(endMessage, 4096);

		strcat(endMessage, "**********");	//SET END MESSAGE
		udp_send.setMessage(endMessage);
		udp_send.sendMessage();
		udp_send.freeMessage();
	}
	//All finish :)
}

void udp_server_receiver::setPort(int p)
{
	port = p;
}

void udp_server_receiver::setOut(string str)
{

}

void udp_server_receiver::setData(WSADATA wsaData)
{
	data = wsaData;
}

void udp_server_receiver::setVersion(WORD ver)
{
	version = ver;
}

void udp_server_receiver::setMessage(char mess[4096])
{
	strcpy(message, mess);
}

void udp_server_receiver::setClientIP(char client[256])
{
	strcpy(clientIP, client);
}

int udp_server_receiver::getPort()
{
	return port;
}

string udp_server_receiver::getOut()
{
	return "";
}

WSADATA udp_server_receiver::getData()
{
	return data;
}

WORD udp_server_receiver::getVersion()
{
	return version;
}

char udp_server_receiver::getMessage()
{
	return *message;
}

char udp_server_receiver::getClientIP()
{
	return *clientIP;
}

