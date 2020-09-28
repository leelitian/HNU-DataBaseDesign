#include "table.h"
/*
bool table::check_exist(std::string table_name) {
    std::ifstream fin;
    fin.open("table.txt");
    bool find = false;
    std::string s;

    while (!fin.eof())//eof（）这个函数来判断文件是否为空或者是否读到文件结尾
    {
        getline(fin, s);
        if (s.find("表名：" + table_name) != std::string::npos) {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}
*/
void table::create_table(std::string op, int& flag, std::vector<table>& tab)
{
    std::string s = "create table ";
    int f = 1;
    for (int i = 0; i < s.length(); ++i)
    {
        if (op[i] != s[i])
        {
            f = 0;
            break;
        }
    }
    if (f)
    {
        flag = 2;
        //create_table(op);
        table t;
        t.col_len = 0;
        int flag;

        std::string tmp = "create table ";
        int k = tmp.length();
        //获取表的名字
        t.table_name = "";
        for (; (op[k] != '\n' || op[k] != '(' || op[k] != ' ') && k < op.length(); ++k)
            t.table_name += op[k];
        //获取表中字段名及字段类型
        std::string s;
        while (std::getline(std::cin, s) && s != ")")//只有回车会终止getline操作，每次回车进行一次循环，到出现）终止
        {
            t.col_len++;
            int f = 1;
            int i = 0;
            tmp = "";
            //输入一个字符串，计算其长度

            while (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')))//防止在第二行开头出现（或者空格的情况导致无法建表
                ++i;

            for (; s[i] != ' ' && i < s.length(); ++i)//将该字符串即字段名存下来
            {
                tmp += s[i];
            }

            if (tmp.length() == 0)
            {
                std::cout << "create 语法错误！" << std::endl;
                return ;
            }

            int m = 0;
            tmp = "";

            while (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')))//防止字段名和字段类型中间空格个数不可控
                ++i;

            for (; s[i] != '(' && s[i] != ' ' && s[i] != ',' && i < s.length(); ++i)//将该字符串即字段类型存下来
            {
                tmp += s[i];
                // m=i;
            }

            //判断字段类型是否正确
            if ((tmp != "char") && (tmp != "int") && (tmp != "float") && (tmp != "double") && (tmp != "time") && (tmp != "date"))
            {
                std::cout << "字段类型错误！" << std::endl;
                return;
            }

            if (tmp.length() == 0)
            {
                std::cout << "create 语法错误！" << std::endl;
                return;
            }

            //去除了结尾的逗号，以及第二行开始的（，全都变成空格
            for (int i = 0; i < s.length(); i++)
                if (s[i] == ',')
                    s[i] = ' ';
            if (s[0] == '(')
                s[0] = ' ';

            //如果加约束的话，因为约束不是一个字符串，所以不能像之前的挨个字符串判断，在判断前两个字符串是否符合字段名和字段类型之后，
            //然后判断剩余的字符串是否是限定条件

            std::stringstream ss(s);//将输入的第一行转换成流，按照空格对输入的字符串截断
            std::string s1;
            std::vector<std::string> in;
            while (ss >> s1)//抽取ss中的值到s1，每个循环中ss就被按照空格截断
                in.push_back(s1);
            t.col_name.push_back(in[0]); //字段名
            t.type_value.push_back(in[1]); //字段类型

            std::string yueshu = "";
            for (int i = 2; i < in.size(); i++)
            {
                yueshu += in[i];//第二个字符串后面的全部为约束条件
                if (i != in.size() - 1) yueshu += " ";//把约束条件中的空格也读取出来
            }

            if (yueshu == "primary key")
                t.condition.push_back(1);
            else if (yueshu == "unique")
                t.condition.push_back(2);
            else if (yueshu == "not null")
                t.condition.push_back(3);
            else t.condition.push_back(0);
            //cout << "---" << t.condition << yueshu << endl;
        }
        /*
        if (check_exist(table_name))
            goto TABLE_EXIST;
        */
        //把t表存入table向量数组
        tab.push_back(t);
        //存储整个数据表
        std::ofstream fout;
        fout.open("table.txt", std::ios::app);//以追加的方式打开文件
        //把内容输入到文件中
        fout << t.table_name << " " << t.col_len << std::endl;
        for (int i = 0; i < t.col_name.size(); ++i)//size()函数返回容器中当前元素的个数
        {
            fout << t.col_name[i];
            fout << " " << t.type_value[i];
            fout << ' ' << t.condition[i] << std::endl;
        }
        fout << std::endl;
        fout.close();


        //当建立一个表之后，不仅在table文档中会显示，同时会生成一个以表名为名的txt文件，专门储存这一个表中的数据
        char file[30];
        std::string tt = "table/" + t.table_name + ".txt";
        for (int i = 0; i < tt.length(); ++i)
            file[i] = tt[i];
        file[tt.length()] = '\0';
        //打开这个txt文件
        fout.open(file);
        for (int i = 0; i < t.col_name.size() - 1; ++i)
            fout << t.col_name[i] << " ";
        fout << t.col_name[t.col_name.size() - 1] << std::endl;
        fout.close();


        std::cout << "建表成功！" << std::endl;
    }
    return ;
}
