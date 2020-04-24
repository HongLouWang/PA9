#include "udp_server_sender.h"

void udp_server_sender::sendMessage()
{

}

void udp_server_sender::setMessage(char mess[4096])
{
	strcpy(message, mess);
}
void udp_server_sender::setIP(char addr[256])
{
	strcpy(ip, addr);
}
void setPort(int p);

string getMessage();
string getIP();
int getPort();

