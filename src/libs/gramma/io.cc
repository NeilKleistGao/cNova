// #include <gramma/io.h>
// #include <io/io_exceptions.h>
// #include <ROOT_PATH.h>
// namespace LR
// {
//     InputStream::InputStream(const std::string &filename)
//     {
//         std::string rootPath(ROOT_PATH);
//         m_v_path = rootPath + "/data/LR/input_v.txt";
//         m_t_path = rootPath + "/data/LR/input_t.txt";
//         readSymbols(SymbolType::TERMINAL);
//         readSymbols(SymbolType::VARIABLE);
//         genProduction(filename);
//     }
//     InputStream::~InputStream()
//     {
//     }
//     void InputStream::genProduction(const std::string &filename)
//     {
//         std::string s, s_right;
//         std::vector<std::string> tmp_result;
//         std::vector<std::string> tmp_r_result; //产生式右部
//         PRight p_right;
//         std::ifstream _in(filename);
//         std::vector<std::string> tmp_V_result; //用以分割非终结符

//         while (getline(_in, s))
//         {
//             //将字符串按照->分割，左边的为产生式左部符号
//             split(s, "-%", tmp_result);

//             PLeft p_left = {SymbolType::VARIABLE, tmp_result[0]};

//             //取产生式右边符号
//             s_right = tmp_result[1];
//             tmp_result.clear();

//             //有多个产生式的话以|隔开，并将结果放入tmp_result中
//             split(s_right, "·", tmp_r_result);
//             s_right.clear();

//             //右部产生式调整大小
//             p_right.resize(tmp_r_result.size());

//             //对每个产生式做操作：
//             for (size_t i = 0; i < p_right.size(); ++i)
//             {
//                 std::string p = tmp_r_result[i];
//                 tmp_result.clear();
//                 //按照`分割为不同的符号
//                 split(p, "`", tmp_result);

//                 for (auto word : tmp_result)
//                 {
//                     //如果该符号是终结符
//                     if (m_t_list.count({SymbolType::TERMINAL, word}))
//                     {
//                         //直接放入
//                         p_right[i].push_back({SymbolType::TERMINAL, word});
//                     }
//                     //否则就是带空格的非终结符
//                     else
//                     {
//                         split(word, " ", tmp_V_result);
//                         for (auto _v : tmp_V_result)
//                         {
//                             if (m_v_list.count({SymbolType::VARIABLE, _v}))
//                                 p_right[i].push_back({SymbolType::VARIABLE, _v});
//                         }
//                         tmp_V_result.clear();
//                     }
//                 }
//             }
//             tmp_r_result.clear();
//             m_productions[p_left] = p_right;
//             p_right.clear();
//             tmp_result.clear();
//         }
//         _in.close();
//     }
//     void InputStream::split(const std::string &str, const std::string &pattern, std::vector<std::string> &result)
//     {
//         std::string::size_type pos;

//         str += pattern; //扩展字符串以方便操作
//         size_t size = str.size();

//         for (size_t i = 0; i < size; i++)
//         {
//             pos = str.find(pattern, i);
//             if (pos < size)
//             {
//                 std::string s = str.substr(i, pos - i);
//                 result.push_back(s);
//                 i = pos + pattern.size() - 1;
//             }
//         }
//     }
//     void InputStream::readSymbols(SymbolType type)
//     {
//         std::string *path = nullptr;
//         std::set<VT> *list = nullptr;
//         if (type == SymbolType::VARIABLE)
//         {
//             path = &m_v_path;
//             list = &m_v_list;
//         }
//         else
//         {
//             path = &m_t_path;
//             list = &m_t_list;
//         }

//         std::ifstream _in(*path, std::ios::in);
//         if (!_in.is_open())
//         {
//             _in.close();
//             throw cnova::io::IOException(*path);
//         }
//         std::string s;
//         while (getline(_in, s))
//         {
//             list->insert({type, s});
//         }
//         _in.close();
//     }

//     void InputStream::print(const std::string &outputFile) const
//     {
//         std::ofstream of(outputFile, std::ios::out);
//         if (!of.is_open())
//         {
//             of.close();
//             throw cnova::io::IOException(outputFile);
//         }

//         //打印调试
//         for (auto i : m_productions)
//         {
//             of << i.first.raw_info << "->";
//             for (size_t j = 0; j < i.second.size(); ++j)
//             {
//                 for (size_t k = 0; k < i.second[j].size(); ++k)
//                 {
//                     of << i.second[j][k].raw_info << " ";
//                 }
//                 if (j != i.second.size() - 1)
//                     of << "|";
//             }
//             of << std::endl;
//         }
//         of.close();
//     }
// } // namespace LR::gen_io