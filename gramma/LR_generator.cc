#include "LR_generator.h"
#include <set>
namespace LR::gen
{

    LR_generator::LR_generator(const std::string &filename)
    {
        _source = new gen_io::InputStream(filename);
    }

    LR_generator::~LR_generator()
    {
        delete _source;
        _source = nullptr;
    }
    //generate FIRST set
    //Attention: the grammar can't have empty productions!!!
    //eliminate empty productions before using it.
    void LR_generator::appendSet(def::Character_set &toBeAppended, def::Character_set &toAppend)
    {
        std::set_union(toBeAppended.begin(),
                       toBeAppended.end(),
                       toAppend.begin(), toAppend.end(),
                       std::inserter(toBeAppended, toBeAppended.end()));
    }

    void LR_generator::cascadingUpdate(def::P_left updatedNode,
                                       std::unordered_map<def::P_left, def::Character_set, def::V_T_Hash> &influenceList,
                                       std::set<def::P_left> &updatedList)
    {
        for (auto influencedVariable : influenceList[updatedNode])
        {
            //To avoid infinite recursion caused by direct/indirect left recursion.
            if (0 == updatedList.count(influencedVariable))
            {
                appendSet(FIRST_set[influencedVariable],
                          FIRST_set[updatedNode]);
                updatedList.insert(influencedVariable);
                cascadingUpdate(influencedVariable, influenceList, updatedList);
            }
        }
    }
    void LR_generator::generateTotFirst()
    {
        bool changed = false;
        std::unordered_map<def::P_left, def::Character_set, def::V_T_Hash> influenceList;
        //initialization
        for (auto productions : _source.tot_production)
        {
            def::Character_set characterSet;
            FIRST_set[productions.first] = characterSet;
            influenceList[productions.first] = characterSet;
        }

        do
        {
            changed = false;
            for (auto productions : _source.tot_production)
            {
                def::P_right productionRight = productions.second;
                size_t originLenth = FIRST_set[productions.first].size();
                for (auto singleProduction : productionRight)
                {
                    //terminal
                    if (1 == singleProduction[0].type)
                    {
                        FIRST_set[productions.first].insert(singleProduction[0]);
                    }
                    //variable(not left recursive production)
                    else if (!(singleProduction[0] == productions.first))
                    {
                        appendSet(FIRST_set[productions.first],
                                  FIRST_set[singleProduction[0]]);
                        influenceList[singleProduction[0]].insert(productions.first);
                    }
                }
                size_t newLength = FIRST_set[productions.first].size();
                if (newLength > originLenth)
                {
                    changed = true;
                    std::set<def::P_left> updatedList;
                    updatedList.insert(productions.first);
                    //cascading change, to imporve efficiency.
                    cascadingUpdate(productions.first, influenceList, updatedList);
                }
            }
        } while (changed == true);
    }

    //输入：符号序列
    //输出：符号序列的first字符集合
    std::set<def::V_T> LR_generator::generateFirst(std::vector<def::V_T>)
    {
    }
    //输入：带点的产生式的集合I
    //输出：带点的产生式的集合J
    typename def::dot_P_forward LR_generator::generateClosure(typename def::dot_P_forward &I)
    {
        auto J = I;
        auto J_new=J;
        do
        {
            J_new = J;
            for (auto p : J_new)
            {
                //如果·后面是非终结符
                if (p.first.dot_p_right[p.first.dot_index].type == def::Symbol_Type::VARIABLE)
                {
                    auto B = p.first.dot_p_right[p.first.dot_index];
                    //B后面的beta序列
                    std::vector<def::V_T> beta(p.first.dot_p_right.begin() + p.first.dot_index + 1, p.first.dot_p_right.end());
                    //beta+a
                    beta.insert(beta.end(), p.second.begin(), p.second.end());
                    //求beta+a的first
                    auto _first = generateFirst(beta);
                    for (auto b : _first)
                    {
                        for (auto eta : _source->tot_production[B])
                        {
                            if(!J.count({0,B,eta})){
                                J[{0,B,eta}].insert(b);
                            }
                            else if(!J[{0,B,eta}].count(b)){
                                J[{0,B,eta}].insert(b);
                            }
                        }
                    }
                }
            }
        } while (J_new != J);
        return J;
    }

} // namespace LR::gen