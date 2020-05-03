#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <fstream>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

typedef struct list
{
	char ranklist[4];
	char username[128];
	char score[128];
	struct list* previous;
	struct list* next;
}list;

class ranklist
{
public:
	ranklist();
	~ranklist();

	void split(char* src, const char* separator, char** dest, int* num);
	list* load();
	list* insert(char username[128], char score[128], list** head_ptr);
	void update(char username[128], char score[128], list* l);
	bool isExist(char username[128]);
	int getMaxRank();
	void readyToSend(list* head);
	void store(list* head);
	string scoreToSend;
private:
	int line_cnt = 0;
	
};

