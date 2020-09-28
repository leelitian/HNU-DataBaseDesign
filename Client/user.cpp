#include "user.h"

user::user(std::string name, std::string password, std::map<std::string, bool> permission) {
	this->name = name;
	this->password = password;
	this->permission["write"] = permission["write"];
	this->permission["read"] = permission["read"];
	this->permission["insert"] = permission["insert"];
	this->permission["select"] = permission["select"];
	this->permission["update"] = permission["update"];
	this->permission["delete"] = permission["delete"];
}
user::user() {
	this->name = "\0";
	this->password = "\0";
	this->permission["write"] = "false";
	this->permission["read"] = "false";
	this->permission["insert"] = "false";
	this->permission["select"] = "false";
	this->permission["update"] = "false";
	this->permission["delete"] = "false";
}
void user::create_user() {
    user u;
    std::string name;
    std::cout << "请输入用户名：" << std::endl;
    std::cin >> name;

    std::string password;
    std::cout << "请输入密码：" << std::endl;
    std::cin >> password;

    std::string have;
    std::cout << "请输入该用户的权限（w->写权限，r->读权限，wr->读写权限）：" << std::endl;
    std::cin >> have;

    u.name = name;
    u.password = password;
    for (int i = 0; i < have.length(); ++i)
    {
        if (have[i] == 'w')
        {
            u.permission["write"] = "true";
            u.permission["delete"] = "true";
            u.permission["insert"] = "true";
            u.permission["select"] = "true";
            u.permission["update"] = "true";
        }

        if (have[i] == 'r')
            u.permission["read"] = "true";
    }

    std::ofstream fout;
    fout.open("user.txt", std::ios::app);//以追加方式打开txt文件
    fout << "姓名：" << u.name << " 密码：" << u.password
        << " 写权限 " << u.permission["write"]
        << " 读权限 " << u.permission["read"] 
        << " 插入 " << u.permission["insert"]
        << " 删除 " << u.permission["delete"]
        << " 筛选 " << u.permission["select"]
        << " 更新 " << u.permission["update"] << std::endl;
    fout.close();
    //std::cout << "用户创建成功，请登录！" << std::endl;
}

user user::stringToUSER(std::string s)//存储用户和访问权限的信息
{
    user temp;
    std::string t = "";
    int i = 6;
    int len = s.size();


    //不读取文件中的中文，只读取英文
    while (i < len)
    {
        if (s[i] == ' ') break;
        else t += s[i];
        i++;
    }
    temp.name = t;
    t = "";

    i = i + 7;
    while (i < len)
    {
        if (s[i] == ' ') break;
        else t += s[i];
        i++;
    }
    temp.password = t;
    t = "";

    i = i + 8;
    while (i < len)
    {
        if (s[i] == ' ') break;
        else t += s[i];
        i++;
    }
    temp.permission["write"] = t;
    t = "";

    i = i + 8;
    while (i < len)
    {
        if (s[i] == ' ') break;
        else t += s[i];
        i++;
    }
    temp.permission["read"] = t;
    t = "";
    return temp;
}

user user::query_user(std::string name, std::string password) {

    user tmp;
    std::ifstream fin;
    fin.open("user.txt");
    bool find = false;
    std::string s;

    while (!fin.eof())//eof（）这个函数来判断文件是否为空或者是否读到文件结尾
    {
        getline(fin, s);//从输入流fin中读取一行字符到s中
        tmp = stringToUSER(s);
        if (tmp.name == name && tmp.password == password)
        {
            fin.close();
            return tmp;
        }
    }
    fin.close();
    user t;
    return t;
}
