//构造LR分析表的程序
#include <bits/stdc++.h>
//生成LR表所需的数据结构
namespace gen_LR
{
    //符号
    struct V_T
    {
        bool type;            //是否为终结符，1为终结符
        std::string raw_info; //原始的符号字面量
        V_T() = default;
        V_T(bool s_type, const std::string &s_s) : type(type), raw_info(s_s) {}
        bool operator==(const V_T &e) const
        {
            return type == e.type && raw_info == e.raw_info;
        }
        bool operator<(const V_T &e) const
        {
            return raw_info < e.raw_info;
        }
    };

    //胡乱写的一个哈希函数
    struct NodeHash
    {
        size_t operator()(const V_T &e) const
        {
            return e.raw_info.size() * 7 + e.type * 5;
        }
    };

    using P_left = V_T;                            //产生式左部
    using P_right = std::vector<std::vector<V_T>>; //产生式右部
    std::set<V_T> V_list;                          //非终结符表
    std::set<V_T> T_list;                          //终结符表

    std::unordered_map<P_left, P_right, NodeHash> tot_production; //总产生式集合。输入后先放在这里
    //带点的产生式
    struct dot_P
    {
        size_t dot_index;         //·的位置，规定·位于dot_index的符号的前面. dot_index为长度时是说明读完
        P_left p_left;            //产生式左部
        std::vector<V_T> p_right; //产生式右部
    };

    //一个项目
    struct Item
    {
        std::vector<dot_P> P_list; //一个项目的所有带点产生式
        int id;
    };

    struct Edge
    {
        int to;        //指向的结点
        V_T condition; //读入condition后跳转到to
    };

    std::vector<std::vector<Edge>> G; //项目集规范族.G[i]表示第i个结点的边

    //字符串分割函数。str为源字符串，pattern为要以此为分割的匹配串，result为最终的结果
    inline void split(std::string str, std::string pattern, std::vector<std::string> &result)
    {
        std::string::size_type pos;

        str += pattern; //扩展字符串以方便操作
        size_t size = str.size();

        for (size_t i = 0; i < size; i++)
        {
            pos = str.find(pattern, i);
            if (pos < size)
            {
                std::string s = str.substr(i, pos - i);
                result.push_back(s);
                i = pos + pattern.size() - 1;
            }
        }
    }
    
    //从文件读取文法并生成产生式
    void genProduction(std::string &filename);

    //todo:把main中的改为这个。用文件读取。读data中的input.txt
    void getV_T(std::string&filename);
}; // namespace gen_LR
