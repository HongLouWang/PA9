/*******************************************************************************************
* Programmer: Shutian Wang *
* Class: CptS 122, Spring, 2020; Lab Section 14 *
* Programming Assignment: PA9 *
* Date: Apr 24, 2020 *
* Description: PA9 SERVER SIDE MAIN FUNCTION*
*******************************************************************************************/

#include <iostream>
#include "udp_server_receiver.h"

int main()
{
	udp_server_receiver udp;
	udp.setPort(54000);
	cout << "SERVER STARTING... " << endl;
	udp.startUDPServer();
	return 0;
}