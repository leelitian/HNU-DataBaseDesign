#include <iostream>
#include <WINSOCK2.H>
#include <string>

#include "client.h"
using namespace std;

int main(int argc, char** argv)
{
	int port;
	string server_address;
	char* zsMessage = new char[MSGSIZE];
	char flags;

	while (1)
	{
		cout << "是否使用默认配置？（y/n）" << endl;
		cin >> flags;
		if (flags == 'y' || flags == 'Y')
		{
			startClient(10000, "127.0.0.1");
			cout << "客户端配置完成。" << endl;
			break;
		}
		else if (flags == 'n' || flags == 'N')
		{
			cout << "请输入服务器ip地址：" << endl;
			cin >> server_address;
			cout << "请输入服务器端口号：" << endl;
			cin >> port;
			startClient(port, server_address);
			cout << "客户端配置完成。" << endl;
			break;
		}
		else
		{
			cout << "错误参数，请重新输入" << endl;
			continue;
		}
	}

	string name, password;
	char user_choose;
main_page:
	system("cls");

	cout << "                          *************************" << endl;
	cout << "                          *   欢迎来到HNUDBMS  *" << endl;
	cout << "                          *************************" << endl;
	cout << endl;
	cout << "--------------------------------------------------------------------------------" << endl;
	cout << "请选择您要进行的操作" << endl;
	cout << "用户登录-->1" << endl;
	cout << "注册用户-->2" << endl;

	cin >> user_choose;
	while (true)
	{
		if (user_choose == '1')
			goto usr_load;
		else if (user_choose == '2')
		{
			cout << "请输入用户名：" << endl;
			cin >> name;

			cout << "请输入密码：" << endl;
			cin >> password;

			string have;
			cout << "请输入该用户的权限（w->写权限，r->读权限，wr->读写权限）：" << endl;
			cin >> have;

			string result = clientSendMsg("2 " + name + " " + password + " " + have);
			break;
		}
		else
		{
			cout << "对不起，你输入的有误！" << endl;
			goto main_page;
		}
	}
	goto main_page;
usr_load:
	while (true)
	{
		printf("用户名: ");
		cin >> name;
		printf("密码:");
		cin >> password;

		string result = clientSendMsg("1 " + name + " " + password);

		// 发送用户名和密码
		if (result == "FAILED")
		{
			cout << "用户名或密码错误" << endl;
			continue;
		}
		else
		{
			cout << name << "你好，欢迎使用DBMS\n您拥有以下权限：" << endl;
			cout << result.substr(3);
			break;
		}
	}

	string operations;

	cin.get();
	while (true)
	{
		cout << "----------------------------------------------------" << endl;
		cout << "请输入SQL语句" << endl;
		cout << "----------------------------------------------------" << endl;

		getline(cin, operations);		//从输入流中读入字符，存入operations变量
		if(operations == "quit")
			goto main_page;
		string result = clientSendMsg(operations);
		cout << result << endl;
	}
	return 0;
}