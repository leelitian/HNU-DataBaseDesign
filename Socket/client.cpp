#include<iostream>
#include"client_method.cpp"
using namespace std;
int main()
{
	int port;
	string server_address;
	char* zsMessage=new char[1024];
	char flags;
	cout<<"是否使用默认配置？（y/n）"<<endl;
	cin>>flags;

	while(1)
	{
		if(flags=='y'||flags=='Y')
		{
			startClient(10000,"127.0.0.1");
			cout<<"客户端配置完成。"<<endl;
			break;
		}
		else if(flag=='n'||flag=='N')
		{
			cout<<"请输入服务器ip地址："<<endl;
			cin>>server_address;
			cout<<"请输入服务器端口号："<<endl;
			cin>>port;
			startClient(port, server_address);
			cout<<"客户端配置完成。"<<endl;
			break;
		}
		else
		{
			cout<<"错误参数，请重新输入"<<endl;
			continue;
		}
	}


	while(1)
	{
		cout<<"请输入sql语句："<<endl;
		cin>>zsMessage;
		char* result=clientSendMsg (zsMessage);
		cout<<"结果："<<' '<<result<<endl;
	}

	cleanClient();
	return 0;
}
