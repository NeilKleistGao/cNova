//构造LR分析表的程序
#include <bits/stdc++.h>
//生成LR表所需的数据结构
namespace gen_LR
{
   enum Symbol_Type
        {
            TERMINAL,
            VARIABLE
        };
    //符号
    struct V_T
    {
        Symbol_Type type;     //是否为终结符，1为终结符
        std::string raw_info; //原始的符号字面量
        V_T() = default;
        V_T(Symbol_Type s_type, const std::string &s_s) : type(s_type), raw_info(s_s) {}
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
   void genProduction(const std::string &filename = "../data/gramma.txt")
    {
        std::string s, s_right;
        std::vector<std::string> tmp_result;
        std::vector<std::string> tmp_r_result; //产生式右部
        gen_LR::P_right p_right;
        std::ifstream _in(filename);
        std::vector<std::string> tmp_V_result; //用以分割非终结符

        while (getline(_in, s))
        {
            //将字符串按照->分割，左边的为产生式左部符号
            gen_LR::split(s, "-%", tmp_result);

            gen_LR::P_left p_left = {Symbol_Type::VARIABLE, tmp_result[0]};

            //取产生式右边符号
            s_right = tmp_result[1];
            tmp_result.clear();

            //有多个产生式的话以|隔开，并将结果放入tmp_result中
            gen_LR::split(s_right, "·", tmp_r_result);
            s_right.clear();

            //右部产生式调整大小
            p_right.resize(tmp_r_result.size());

            //对每个产生式做操作：
            for (size_t i = 0; i < p_right.size(); ++i)
            {
                std::string p = tmp_r_result[i];
                tmp_result.clear();
                //按照`分割为不同的符号
                gen_LR::split(p, "`", tmp_result);

                for (auto word : tmp_result)
                {
                    //如果该符号是终结符
                    if (gen_LR::T_list.count({Symbol_Type::TERMINAL, word}))
                    {
                        //直接放入
                        p_right[i].push_back({Symbol_Type::TERMINAL, word});
                    }
                    //否则就是带空格的非终结符
                    else
                    {
                        gen_LR::split(word, " ", tmp_V_result);
                        for (auto _v : tmp_V_result)
                        {
                            if (gen_LR::V_list.count({Symbol_Type::VARIABLE, _v}))
                                p_right[i].push_back({Symbol_Type::VARIABLE, _v});
                        }
                        tmp_V_result.clear();
                    }
                }
            }
            tmp_r_result.clear();
            gen_LR::tot_production[p_left] = p_right;
            p_right.clear();
            tmp_result.clear();
        }
        _in.close();
    }

    //读取终结符和非终结符
    void getV_T()
    {
        std::ifstream _in;
        _in.open("../data/input_V.txt");
        std::string s;
        while (getline(_in, s))
        {
            if (!gen_LR::V_list.count(V_T(Symbol_Type::VARIABLE, s)))
                gen_LR::V_list.insert(V_T(Symbol_Type::VARIABLE, s));
        }
        _in.close();
        //读入非终结符
        _in.open("../data/input_T.txt");
        while (getline(_in, s))
        {
            if (!gen_LR::T_list.count(V_T(Symbol_Type::TERMINAL, s)))
                gen_LR::T_list.insert(V_T(Symbol_Type::TERMINAL, s));
        }
        _in.close();
    }

    //打印。调试用
    void print()
    {
        std::ofstream of;
        of.open("../test/test_data/gramma/LR_io/test_IO_result.txt");
        //打印调试
        for (auto i : gen_LR::tot_production)
        {
            of << i.first.raw_info << "->";
            for (size_t j = 0; j < i.second.size(); ++j)
            {
                for (size_t k = 0; k < i.second[j].size(); ++k)
                {
                    of << i.second[j][k].raw_info << " ";
                }
                if (j != i.second.size() - 1)
                    of << "|";
            }
            of << std::endl;
        }
    }
}; // namespace gen_LR
