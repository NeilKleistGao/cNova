// #pragma once
// #include <fstream>
// #include <gramma/defines.h>
// namespace LR
// {
//     class InputStream
//     {
//     public:
//         InputStream(const std::string &filename ); //从文件读取生成产生式
//         ~InputStream();

//         InputStream(const InputStream &) = delete;
//         InputStream &operator=(const InputStream &) = delete;
//         InputStream(InputStream &&) = delete;

//         std::set<VT> m_v_list; //非终结符表
//         std::set<VT> m_t_list; //终结符表

//         std::string m_v_path; //非终结符文件路径
//         std::string m_t_path;

//         std::unordered_map<PLeft, PRight, VTHash> m_productions; //总产生式集合。输入后先放在这里
//     private:
//         //从文件读取文法并生成产生式
//         void genProduction(const std::string &filename);
//         //字符串分割函数
//         inline void split(const std::string& str, const std::string& pattern, std::vector<std::string> &result);
//         //读取终结符和非终结符
//         void readSymbols(SymbolType type);
//         //打印。调试用
//         void print(const std::string &outputFile)const;
//     };
// } // namespace gen_LR::io
