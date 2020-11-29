#ifndef CNOVA_LR_IO_H
#define CNOVA_LR_IO_H
#include <fstream>
#include "LR_def.h"
namespace LR::gen_io
{
    class InputStream
    {
    public:
        InputStream(const std::string &filename = "../data/gramma.txt"); //调用构造函数从文件读取生成产生式
        ~InputStream();

        InputStream(const InputStream &) = delete;
        InputStream &operator=(const InputStream &) = delete;
        InputStream(InputStream &&) = delete;

        std::set<def::V_T> V_list; //非终结符表
        std::set<def::V_T> T_list; //终结符表

        std::unordered_map<def::P_left, def::P_right, def::V_T_Hash> tot_production; //总产生式集合。输入后先放在这里
    private:
        //从文件读取文法并生成产生式
        void genProduction(const std::string &filename);
        //字符串分割函数
        inline void split(std::string str, std::string pattern, std::vector<std::string> &result);
        //读取终结符和非终结符
        void getV_T(const std::string &V_file = "../data/input_V.txt",const std::string &T_file = "../data/input_T.txt");
        //打印。调试用
        void print(const std::string &outputFile="../test/test_data/gramma/LR_io/test_IO_result.txt")const;
    };
} // namespace gen_LR::io
#endif