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
//从文件读取文法并生成产生式
void genProduction()
{
    string s, s_right;
    vector<string> tmp_result;
    gen_LR::P_right p_right;
    ifstream f("../test/test_data/gramma/LR_io/test1.txt");
    while (getline(f, s))
    {
        //将字符串按照->分割，左边的为产生式左部符号
        gen_LR::split(s, "->", tmp_result);

        gen_LR::P_left p_left = {0, tmp_result[0]};

        //取产生式右边符号
        s_right = tmp_result[1];
        tmp_result.clear();

        //有多个产生式的话以|隔开，并将结果放入tmp_result中
        gen_LR::split(s_right, "|", tmp_result);
        s_right.clear();

        //右部产生式调整大小
        p_right.resize(tmp_result.size());

        //对每个产生式做操作：
        for (size_t i = 0; i < p_right.size(); ++i)
        {
            string p = tmp_result[i];
            tmp_result.clear();
            //按照空格分割为不同的符号
            gen_LR::split(p, " ", tmp_result);

            for (auto word : tmp_result)
            {
                //如果该符号是非终结符
                if (gen_LR::V_list.count({0, word}))
                {
                    p_right[i].push_back({0, word});
                }
                //否则就是终结符
                else if (gen_LR::T_list.count({1, word}))
                    p_right[i].push_back({1, word});
                else
                {
                    //报错
                }
            }
        }
        gen_LR::tot_production[p_left] = p_right;
        p_right.clear();
        tmp_result.clear();
    }
    f.close();
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
    genProduction();
    print();
}
