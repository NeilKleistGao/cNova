// #pragma once
// #include <string>
// #include <set>
// #include <vector>
// #include <unordered_map>

// namespace LR
// {
//     //符号类型
//     enum SymbolType
//     {
//         TERMINAL,
//         VARIABLE
//     };
//     //符号
//     struct VT
//     {
//         SymbolType type;     //是否为终结符，1为终结符
//         std::string raw_info; //原始的符号字面量
//         VT() = default;
//         VT(SymbolType s_type, const std::string &s_s) : type(s_type), raw_info(s_s) {}
//         VT(const VT &e) : type(e.type), raw_info(e.raw_info) {}
//         VT& operator=(const VT &e)
//         {
//             type = e.type;
//             raw_info = e.raw_info;
//             return *this;
//         }
//         bool operator==(const VT &e) const
//         {
//             return type == e.type && raw_info == e.raw_info;
//         }
//         bool operator<(const VT &e) const
//         {
//             return raw_info < e.raw_info;
//         }
//     };

//     //符号用的哈希函数
//     struct VTHash
//     {
//         size_t operator()(const VT &e) const
//         {
//             return e.raw_info.size() * 7 + e.type * 5;
//         }
//     };

//     using PLeft = VT;                            //产生式左部
//     using PRight = std::vector<std::vector<VT>>; //产生式右部(允许多个)
//     using CharacterSet = std::set<VT>;

//     //带点的产生式
//     struct DotP
//     {
//         size_t dot_index;             //·的位置，规定·位于dot_index的符号的前面. dot_index为长度时是说明读完
//         PLeft dot_p_left;            //产生式左部
//         std::vector<VT> dot_p_right; //产生式右部
//         DotP(size_t _i, const PLeft &_l, const std::vector<VT> &_r) : dot_index(_i), dot_p_left(_l), dot_p_right(_r) {}
//     };
//     //带点的产生式的哈希函数
//     struct DotPHash
//     {
//         size_t operator()(const DotP &e) const
//         {
//             return e.dot_index * 7 + e.dot_p_left.type * 11 + e.dot_p_right.size();
//         }
//     };

//     //一个项目
//     struct Item
//     {
//         int id;
//         std::vector<DotP> P_list; //一个项目的所有带点产生式
//         bool operator()(const Item &a, const Item &b) const
//         {

//             if (a.id == b.id)
//             {
//                 return a.P_list == b.P_list;
//             }
//         }
//     };

//     struct ItemCmp
//     {
//         bool operator()(const Item &a, const Item &b) const
//         {
//             return a.P_list == b.P_list;
//         }
//     };

//     struct Edge
//     {
//         int to;        //指向的结点
//         VT condition; //读入condition后跳转到to
//     };

//     //带有展望符的带点产生式. first为带点的产生式，second为展望符
//     using DotPForward = std::unordered_map<DotP, std::set<VT>, DotPHash>;

// } // namespace name
