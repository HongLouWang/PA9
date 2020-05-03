#include "ranklist.h"

void ranklist::split(char* src, const char* separator, char** dest, int* num)
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

ranklist::ranklist()
{
}

ranklist::~ranklist()
{
}

list* ranklist::load()
{
	list* head = NULL;
	FILE* fp = NULL;

	fp = fopen("user-score.db", "r");
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

		list* l = (list*)new list;
		char* content[10];
		int num = 0;
		num = sizeof(line);
		char ranklist[4],username[128], score[128];
		ZeroMemory(ranklist, 4);
		ZeroMemory(username, 128);
		ZeroMemory(score, 128);

		split(line, ",", content, &num);

		strcpy(l->ranklist, content[0]);
		strcpy(l->username, content[1]);
		strcpy(l->score, content[2]);

		if (head == NULL)
		{
			head = l;
			head->previous = NULL;
			head->next = NULL;
		}
		else
		{
			list* last = NULL;
			if (head->next == NULL)
			{
				head->next = l;
				l->next = NULL;
				l->previous = head;
			}
			else
			{
				last = head;
				while (last->next != NULL)
				{
					last = last->next;
				}
				last->next = l;
				l->next = NULL;
				l->previous = last;
			}
		}
	}
}

int ranklist::getMaxRank()
{
	string line;
	ifstream file("user-score.db");
	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, line);
			line_cnt++;
		}
	}
	return line_cnt;
}

void ranklist::insert(char username[128],char score[128],list* head)
{
	list* l = (list*)new list;
	strcpy(l->score, score);
	strcpy(l->username, username);
	char inttemp[10] = { 0 };
	sprintf(inttemp, "%d", getMaxRank());
	strcpy(l->ranklist, inttemp);
	//strcpy(l->ranklist,atoi())

	if (head == NULL)
	{
		head = l;
		l->next = NULL;
		l->previous = NULL;
	}
	else
	{
		l->next = head;
		l->previous = NULL;
		head = l;
	}
	store(head);
}

void ranklist::update(char username[128],char score[128])
{
	list* l = load();
	list* current = l;
	if (strcmp(username, l->username) == 0)
	{
		//user exist
		strcpy(l->score, score);
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
			cout << "something went wrong!";
		}
		else if (strcmp(username, current->username) == 0)
		{
			//username exist
			strcpy(l->score, score);
		}
	}
	store(l);
}

bool ranklist::isExist(char username[128])
{
	list* l = load();
	list* current = l;
	if (strcmp(username, l->username) == 0)
	{
		//user exist
		return true;
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
			return false;
		}
		else if (strcmp(username, current->username) == 0)
		{
			//username exist
			return true;
		}
	}
}

void ranklist::store(list* head)
{
	FILE* fp = NULL;
	fp = fopen("user-score.db", "w+");

	if (fp == NULL)
	{
		perror("my_fputs fopen");
		return;
	}

	list* l = head;
	while (l != NULL)
	{
		char temp[1024];
		ZeroMemory(temp, 1024);
		strcat(temp, l->ranklist);
		strcat(temp, ",");

		strcat(temp, l->username);
		strcat(temp, ",");

		strcat(temp, l->score);
		strcat(temp, ",");

		fputs(temp, fp);
		l = l->next;
	}

	if (fp != NULL)
	{
		fclose(fp);
		fp = NULL;
	}
}