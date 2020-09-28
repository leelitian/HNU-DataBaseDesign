#include <WINSOCK2.H>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <iostream>
using namespace std;

#pragma comment(lib,"ws2_32.lib")

#define SERVER_ADDRESS 	"127.0.0.1"
#define PORT           	10000
#define MSGSIZE        	10240

#define SUCCESS 		0x01
#define FAILE 			0X02

WSADATA wsaData;
SOCKET socketClient;
SOCKADDR_IN server;
int retSize;
int sendSize;

char szMessage[MSGSIZE];
char zsMessage[MSGSIZE];

void startClient(int port, string server_address)
{
	port = PORT;
	server_address = SERVER_ADDRESS;

	WSAStartup(0x0202, &wsaData);

	socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&server, 0, sizeof(SOCKADDR_IN));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS);

	connect(socketClient, (struct sockaddr*)&server, sizeof(SOCKADDR_IN));
}

string clientSendMsg(string recv_msg)
{
	const char* zsMessage = recv_msg.c_str();
	string errorMsg = "";
	send(socketClient, zsMessage, strlen(zsMessage), 0);
	if (sendSize < 0)
	{
		cout << "接受失败，可能是因为连接中断！" << endl;
		errorMsg = "error";
	}
	// cout << "正在等待服务器响应：" << endl;

	retSize = recv(socketClient, szMessage, MSGSIZE, 0);
	if (retSize < 0)
	{
		cout << "接受失败，可能是因为连接中断！" << endl;
		errorMsg = "error";
		return "Error";
	}
	//cout << retSize << endl;
	szMessage[retSize] = '\0';

	return string(szMessage, szMessage + retSize);
}


void cleanClient()
{
	closesocket(socketClient);
	WSACleanup();
}
