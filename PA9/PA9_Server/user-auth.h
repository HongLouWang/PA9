#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

#ifndef _USER_AUTH_H_
#define _USER_AUTH_H_

using namespace std;

typedef struct userinfo
{
	char username[128];
	char password[128];
	struct userinfo* previous;
	struct userinfo* next;
}userinfo;

void split(char* src, const char* separator, char** dest, int* num);
userinfo* load();
bool login_match(char username[128], char password[128]);
bool sign_up_infocheck(char username[128]);
void sign_up(char username[128], char password[128], userinfo* head);
void store(userinfo* head);



#endif // !_USER_AUTH_H_
