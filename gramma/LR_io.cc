#include "LR_io.h"
//从文件读取文法并生成产生式
void genProduction(std::string &filename)
{
    std::string s, s_right;
    std::vector<std::string> tmp_result;
    gen_LR::P_right p_right;
    std::ifstream f(filename);
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
            std::string p = tmp_result[i];
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