#ifndef __TABLE__
#define __TABLE__
#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
#include <vector>
#include <cstdio>
#include <windows.h>
#include <cstring>
#include <sstream>
class table
{
public:
    std::string table_name;//表名
    std::vector<std::string> col_name;//字段名
    std::vector<std::string> type_value;//字段类型名·
    std::vector<int> condition;//0表示无约束条件
    int col_len;//属性个数
    int remcount = 0;//元组个数
    //bool check_exist(std::string table_name);
    void create_table(std::string op, int& flag, std::vector<table>& tab);
};

#endif