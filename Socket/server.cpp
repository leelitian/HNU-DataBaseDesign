#include <WINSOCK2.H>
#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include "Thread.h"
#include "Thread.cpp"
#include "slove.cpp"

#define SERVER_PORT		10000
#define MSGSIZE			1024
//#define

#pragma comment(lib, "ws2_32.lib")
using namespace std;


class CMyTask: public CTask
{
	public:
		CMyTask() = default;
		int Run()
		{
			//printf("%s\n", (char*)m_ptrData);
			//int x = rand()%4 + 1;
			//sleep(x);
			//return 0;

			int connfd= GetConnFd();
			cout<<"正在监听与线程"<<pthread_self()<<"连接的客户端信息"<<endl;
			while(1)
			{
				char *szMessage;
				char *zsMessage;
				int retSize = recv(connfd, szMessage, MSGSIZE, 0);
				if (retSize < 0)
				{
					cout << "与线程"<<pthread_self()<<"绑定的客户端中断连接" << endl;
					break;
				}
				szMessage[retSize] = '\0';
				cout<<"接收到与线程"<<pthread_self()<<"连接的客户端信息："<<szMessage<<endl;


				zsMessage=deal(szMessage);

				int sendSize = send(connfd, zsMessage, MSGSIZE, 0);
				if (sendSize < 0)
				{
					cout << "发送失败，可能是因为与线程"<<pthread_self()<<"连接的客户端连接中断！" << endl;
					break;
				}
				cout<<"成功响应与线程"<<pthread_self()<<"连接的客户端  ";
				cout<<"正在监听与线程"<<pthread_self()<<"连接的客户端信息"<<endl;

			}
			closesocket(connfd);
			return 0;
		}
};

int main()
{
	WSADATA wsaData;
	int sListen;

	SOCKET localServer;
	SOCKET localClient;
	//SOCKET
	SOCKADDR_IN local;
	SOCKADDR_IN client;

	int retSize;
	int sendSize;
	WSAStartup(0x0202, &wsaData);

	sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	local.sin_family = AF_INET;
	local.sin_port = htons(SERVER_PORT);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sListen, (struct sockaddr *) &local, sizeof(SOCKADDR_IN));

	listen(sListen, 1);
	CThreadPool Pool(5);


	while (TRUE)
	{
		int addrSize = sizeof(SOCKADDR_IN);
		int sClient = accept(sListen, (struct sockaddr *) &client, &addrSize);
		if(sClient<0)
		{
			printf("cli connect failed.");
			// throw  std::exception();

		}
		//收到客户端请求，即添加到任务队列去
		else
		{
			CTask* ta=new CMyTask;
			ta->SetConnFd(sClient);
			Pool.AddTask(ta);
		}
	}
	return 0;
}

