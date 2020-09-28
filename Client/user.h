#ifndef __USER__
#define __USER__
#include <iostream>
#include <string>
#include <map>
#include <fstream>
class user
{
public:
	std::string name;
	std::string password;
	std::map<std::string, std::string> permission;
	user(std::string name,std::string password, std::map<std::string, bool> permission);
	user();
	void create_user();
	static user stringToUSER(std::string s);
	user query_user(std::string name, std::string password);
};

#endif