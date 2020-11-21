#include "LR_io.h"
#include "LR_first.h"
//generate FIRST set
//Attention: the grammar can't have empty productions!!!
//eliminate empty productions before using it.
void gen_LR::appendSet(gen_LR::Character_set &toBeAppended, gen_LR::Character_set &toAppend)
{
    std::set_union(toBeAppended.begin(),
                   toBeAppended.end(),
                   toAppend.begin(), toAppend.end(),
                   std::inserter(toBeAppended, toBeAppended.end()));
}

void gen_LR::cascadingUpdate(gen_LR::P_left updatedNode,
                     std::unordered_map<gen_LR::P_left, gen_LR::Character_set, gen_LR::NodeHash> &influenceList,
                     std::set<gen_LR::P_left> &updatedList)
{
    for (auto influencedVariable : influenceList[updatedNode])
    {
        //To avoid infinite recursion caused by direct/indirect left recursion.
        if (0 == updatedList.count(influencedVariable))
        {
            gen_LR::appendSet(gen_LR::FIRST_set[influencedVariable],
                              gen_LR::FIRST_set[updatedNode]);
            updatedList.insert(influencedVariable);
            gen_LR::cascadingUpdate(influencedVariable, influenceList,updatedList);
        }
    }
}
void gen_LR::generateFIRST()
{
    bool changed = false;
    std::unordered_map<gen_LR::P_left, gen_LR::Character_set, gen_LR::NodeHash> influenceList;
    //initialization
    for (auto productions : gen_LR::tot_production)
    {
        gen_LR::Character_set characterSet;
        gen_LR::FIRST_set[productions.first] = characterSet;
        influenceList[productions.first] = characterSet;
    }

    do
    {
        for (auto productions : gen_LR::tot_production)
        {
            gen_LR::P_right productionRight = productions.second;
            size_t originLenth = gen_LR::FIRST_set[productions.first].size();
            for (auto singleProduction : productionRight)
            {
                //terminal
                if (1 == singleProduction[0].type)
                {
                    gen_LR::FIRST_set[productions.first].insert(singleProduction[0]);
                }
                //variable(not left recursive production)
                else if(!(singleProduction[0]==productions.first))
                {
                    gen_LR::appendSet(gen_LR::FIRST_set[productions.first],
                                      gen_LR::FIRST_set[singleProduction[0]]);
                    influenceList[singleProduction[0]].insert(productions.first);
                }
            }
            size_t newLength = gen_LR::FIRST_set[productions.first].size();
            if (newLength > originLenth)
            {
                changed = true;
                std::set<gen_LR::P_left> updatedList;
                updatedList.insert(productions.first);
                //cascading change, to imporve efficiency.
                gen_LR::cascadingUpdate(productions.first,influenceList,updatedList);
            }
        }
    } while (changed == true);
}
