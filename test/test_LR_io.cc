#include <bits/stdc++.h>
#include "../gramma/LR_io.h"
using namespace std;
//读入终结符和非终结符列表
//todo:改为从文件读取
//测试数据为
/*
a b
#
H S B
#
*/
void getV_T()
{
    string s;
    cout << "输入非终结符，以#结尾" << endl;
    while (cin >> s)
    {
        if (s == "#")
            break;
        //产生式左部符号入列表中
        gen_LR::T_list.insert({1, s});
    }
    cout << "输入终结符，以#结尾" << endl;
    while (cin >> s)
    {
        if (s == "#")
            break;
        //产生式左部符号入列表中
        gen_LR::V_list.insert({0, s});
        s.clear();
    }
}

void print()
{

    //打印调试
    for (auto i : gen_LR::tot_production)
    {
        cout << i.first.raw_info << "->";
        for (size_t j = 0; j < i.second.size(); ++j)
        {
            for (size_t k = 0; k < i.second[j].size(); ++k)
            {
                cout << i.second[j][k].raw_info << " ";
            }
            cout << " | ";
        }
        cout << endl;
    }
}
int main()
{
    getV_T();
    genProduction("../test/test_data/gramma/LR_io/test1.txt");
    print();
}
