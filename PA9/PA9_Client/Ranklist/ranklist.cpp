#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "../UDP/udp_client_sender.h"
#include "../UDP/udp_client_receiver.h"
#include "ranklist.h"
#include "../UDP/udp_config.h"

void ranklist::sendScore(char username[128], char score[128])
{
	char mess[4096];
	char ip[256] = DEFAULT_SERVER_IP;	//THE SERVER IP
	strcat(mess, "0003-");	//0003--SEND SCORE
	strcat(mess, username);
	strcat(mess, "-");
	strcat(mess, score);

	udp_send.setIP(ip);
	udp_send.setPort(DEFAULT_SEND_PORT);	//THE SERVER PORT
	udp_send.setMessage(mess);
	udp_send.sendMessage();

	udp_send.freeMessage();
}

void ranklist::getScoreList(char username[128])
{
	char ip[256] = DEFAULT_SERVER_IP;
	char mess[4096];
	udp_send.setIP(ip);
	udp_send.setPort(DEFAULT_SEND_PORT);
	strcat(mess, "0004-");	//0003--REQUEST SCORE
	strcat(mess, username);
	udp_send.sendMessage();
	udp_send.freeMessage();
	udp_rec.setPort(DEFAULT_RECE_PORT);
	udp_rec.startUDPclient();

	//char receive[4096];
	//ZeroMemory(receive, 4096);
	
	while (strcmp(udp_rec.getMessage(), "") != 0)
	{
		if (strcmp(udp_rec.getMessage(), "**********") != 0)
		{

			//Set message to list
			list = list + udp_rec.getMessage(); 
		}
	}
	
}

string ranklist::getList()
{
	return list;
}
