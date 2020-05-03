#pragma once
#ifndef  _RANKLIST_H_
#define _RANKLIST_H_

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include "../UDP/udp_client_receiver.h"
#include "../UDP/udp_client_sender.h"
class ranklist
{
public:
	ranklist() {};
	~ranklist() {};

	//send score to server
	void sendScore(char username[128], char score[128]);

	//get score and rank list from server
	void getScoreList(char username[128]);

	//return the rank list
	string getList();

	string list;	//data receive from server

private:
	
};

#endif // ! _RANKLIST_H_


