#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "../UDP/udp_client_sender.h"
#include "../UDP/udp_client_receiver.h"
#include "ranklist.h"

void ranklist::sendScore(char username[128], char score[128])
{
	char mess[4096];
	char ip[256] = "127.0.0.1";	//THE SERVER IP
	strcat(mess, "0003-");	//0003--SEND SCORE
	strcat(mess, username);
	strcat(mess, "-");
	strcat(mess, score);

	udp_send.setIP(ip);
	udp_send.setPort(54000);	//THE SERVER PORT
	udp_send.setMessage(mess);
	udp_send.sendMessage();

	udp_send.freeMessage();
}
