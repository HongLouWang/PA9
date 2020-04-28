#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <WS2tcpip.h>
#pragma comment (lib, "ws2_32.lib")

using namespace std;

typedef struct userinfo
{
	char username[128];
	char password[128];
	struct userinfo* previous;
	struct userinfo* next;
}userinfo;

void split(char* src, const char* separator, char** dest, int* num)
{
	char* pNext;
	int count = 0;
	if (src == NULL || strlen(src) == 0)
	{
		return;
	}
	if (separator == NULL || strlen(separator) == 0)
	{
		return;
	}

	pNext = strtok(src, separator);

	while (pNext != NULL)
	{
		*dest++ = pNext;
		++count;
		pNext = strtok(NULL, separator);
	}

	*num = count;
}

userinfo* load()
{
	userinfo* head = NULL;
	FILE* fp = NULL;
	fp = fopen("user.db", "r");

	if (fp == NULL)
	{
		perror("my_fgets fopen");
		return NULL;
	}
	char line[20000];
	int count = 0;
	while (!feof(fp))
	{
		strcpy(line, "\n");
		fgets(line, sizeof(line), fp);

		userinfo* user = (userinfo*)new userinfo;
		char* content[10];
		int num = 0;
		num = sizeof(line);
		char username[128], password[128];
		ZeroMemory(username, 128);
		ZeroMemory(password, 128);
		split(line, ",", content, &num);

		strcpy(user->username, content[0]);
		strcpy(user->password, content[1]);

		if (head == NULL)
		{
			head = user;
			head->previous = NULL;
			head->next = NULL;
		}
		else
		{
			userinfo* last = NULL;
			if (head->next == NULL)
			{
				head->next = user;
				user->next = NULL;
				user->previous = head;
			}
			else
			{
				last = head;
				while (last->next != NULL)
				{
					last = last->next;
				}
				last->next = user;
				user->next = NULL;
				user->previous = last;
			}
		}

	}
	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
	return head;
}

bool login_match(char username[128], char password[128])
{
	userinfo* user = load();
	userinfo* current = user;
	if (strcmp(username, user->username) == 0)
	{
		//username match!
		if (strcmp(password, user->password) == 0)
		{
			//password match
			return true;
		}
		else
		{
			//password unmatch
			return false;
		}
	}
	else
	{
		while (current != NULL && strcmp(username, current->username) != 0)
		{
			current = current->next;
		}
		if (current == NULL)
		{
			//username unmatch
			return false;
		}
		else if (strcmp(username, current->username) == 0)
		{
			//username match
			if (strcmp(password, current->password) == 0)
			{
				//password match
				return true;
			}
			else
			{
				//password unmatch
				return false;
			}
		}
		else
		{
			//something went wrong
		}
	}
}

bool signup_infocheck(char username[128])
{
	userinfo* user = load();
	userinfo* current = user;
	if (strcmp(username, user->username) == 0)
	{
		//username exist
		return false;
	}
	else
	{
		while (current != NULL && strcmp(username, current->username) != 0)
		{
			current = current->next;
		}
		if (current == NULL)
		{
			//username not exist
			return true;
		}
		else if (strcmp(username, current->username) == 0)
		{
			//username exist
			return false;
		}
	}
}

void sign_up(char username[128], char password[128], userinfo* head)
{
	userinfo* user = (userinfo*)new userinfo;

	strcpy(user->username, username);
	strcpy(user->password, password);

	if (head == NULL)
	{
		head = user;
		user->next = NULL;
		user->previous = NULL;
		//sign up success
	}
	else
	{
		user->next = head;
		user->previous = NULL;
		head = user;
		//sign up success
	}
}