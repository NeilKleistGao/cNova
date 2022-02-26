
// #include <set>
// #include <algorithm>
// #include <gramma/generator.h>
// namespace LR
// {

//     Generator::Generator(const std::string &filename)
//     {
//         m_source = new InputStream(filename);
//     }

//     Generator::~Generator()
//     {
//         delete m_source;
//         m_source = nullptr;
//     }
//     //generate FIRST set
//     //Attention: the grammar can't have empty productions!!!
//     //eliminate empty productions before using it.
//     void Generator::appendSet(CharacterSet &toBeAppended, CharacterSet &toAppend)
//     {
//         std::set_union(toBeAppended.begin(),
//                        toBeAppended.end(),
//                        toAppend.begin(), toAppend.end(),
//                        std::inserter(toBeAppended, toBeAppended.end()));
//     }

//     void Generator::cascadingUpdate(PLeft updatedNode,
//                                        std::unordered_map<PLeft, CharacterSet, VTHash> &influenceList,
//                                        std::set<PLeft> &updatedList)
//     {
//         for (auto influencedVariable : influenceList[updatedNode])
//         {
//             //To avoid infinite recursion caused by direct/indirect left recursion.
//             if (0 == updatedList.count(influencedVariable))
//             {
//                 appendSet(m_first_set[influencedVariable],
//                           m_first_set[updatedNode]);
//                 updatedList.insert(influencedVariable);
//                 cascadingUpdate(influencedVariable, influenceList, updatedList);
//             }
//         }
//     }
//     void Generator::generateTotFirst()
//     {
//         bool changed = false;
//         std::unordered_map<PLeft, CharacterSet, VTHash> influenceList;
//         //initialization
//         for (auto productions : m_source->m_productions)
//         {
//             CharacterSet characterSet;
//             m_first_set[productions.first] = characterSet;
//             influenceList[productions.first] = characterSet;
//         }

//         do
//         {
//             changed = false;
//             for (auto productions : m_source->m_productions)
//             {
//                 PRight productionRight = productions.second;
//                 size_t originLenth = m_first_set[productions.first].size();
//                 for (auto singleProduction : productionRight)
//                 {
//                     //terminal
//                     if (1 == singleProduction[0].type)
//                     {
//                         m_first_set[productions.first].insert(singleProduction[0]);
//                     }
//                     //variable(not left recursive production)
//                     else if (!(singleProduction[0] == productions.first))
//                     {
//                         appendSet(m_first_set[productions.first],
//                                   m_first_set[singleProduction[0]]);
//                         influenceList[singleProduction[0]].insert(productions.first);
//                     }
//                 }
//                 size_t newLength = m_first_set[productions.first].size();
//                 if (newLength > originLenth)
//                 {
//                     changed = true;
//                     std::set<PLeft> updatedList;
//                     updatedList.insert(productions.first);
//                     //cascading change, to imporve efficiency.
//                     cascadingUpdate(productions.first, influenceList, updatedList);
//                 }
//             }
//         } while (changed == true);
//     }

//     //输入：符号序列
//     //输出：符号序列的first字符集合
//     std::set<VT> Generator::generateFirst(std::vector<VT>)
//     {
//     }
//     //输入：带点的产生式的集合I
//     //输出：带点的产生式的集合J
//     typename DotPForward Generator::generateClosure(typename DotPForward &I)
//     {
//         auto J = I;
//         auto J_new = J;
//         do
//         {
//             J_new = J;
//             for (auto p : J_new)
//             {
//                 //如果·后面是非终结符
//                 if (p.first.dot_p_right[p.first.dot_index].type == SymbolType::VARIABLE)
//                 {
//                     auto B = p.first.dot_p_right[p.first.dot_index];
//                     //B后面的beta序列
//                     std::vector<VT> beta(p.first.dot_p_right.begin() + p.first.dot_index + 1, p.first.dot_p_right.end());
//                     //beta+a
//                     beta.insert(beta.end(), p.second.begin(), p.second.end());
//                     //求beta+a的first
//                     auto _first = generateFirst(beta);
//                     for (auto b : _first)
//                     {
//                         for (auto eta : m_source->m_productions[B])
//                         {
//                             if (!J.count({0, B, eta}))
//                             {
//                                 J[{0, B, eta}].insert(b);
//                             }
//                             else if (!J[{0, B, eta}].count(b))
//                             {
//                                 J[{0, B, eta}].insert(b);
//                             }
//                         }
//                     }
//                 }
//             }
//         } while (J_new != J);
//         return J;
//     }

// } 