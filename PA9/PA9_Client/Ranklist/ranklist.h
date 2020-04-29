#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
class ranklist
{
public:
	ranklist() {};
	~ranklist() {};
	
	udp_client_receiver udp_rec;
	udp_client_sender udp_send;

	void sendScore(char username[128], char score[128]);
	void getScoreList();

	void setList(string str);
	string getList();

private:
	string list;
};

