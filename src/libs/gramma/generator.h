// #pragma once
// #include <gramma/defines.h>>
// #include <gramma/io.h>

// namespace LR
// {
//     class Generator
//     {
//     private:
//         std::vector<std::vector<std::string>> m_table;                                  //最终构造的表
//         InputStream *m_source;                                                     //读入的产生式等内容
//         std::unordered_map<PLeft, CharacterSet, VTHash> m_first_set; //FITST set
//         std::set<Item, ItemCmp> m_items;                                     //存放item
//         std::vector<std::vector<Edge>> m_graph;                                        //项目集规范族.G[i]表示第i个结点的边

//         void appendSet(CharacterSet &toBeAppended, CharacterSet &toAppend);
//         void cascadingUpdate(PLeft updatedNode,
//                              std::unordered_map<PLeft, CharacterSet, VTHash> &influenceList,
//                              std::set<PLeft> &updatedList);

//         ~Generator();

//     public:
//         Generator(const std::string &filename);
//         Generator(const Generator &) = delete;
//         Generator &operator=(const Generator &) = delete;

//         //得到所有的First集
//         void generateTotFirst();

//         //求一个序列的First集
//         std::set<VT> generateFirst(std::vector<VT>);

//         //求一个带点的产生式的闭包
//         typename DotPForward Generator::generateClosure(typename DotPForward &I);

//         //得到生成的图
//         void generateGraph();

//         //得到LR分析表
//         void generateTable();
//     };
// } // namespace LR
