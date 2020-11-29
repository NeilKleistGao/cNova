
namespace gen_LR
{
    using Character_set=std::set<V_T>;
    std::unordered_map<P_left,Character_set,NodeHash> FIRST_set;//FITST set
    void generateFIRST();
    void appendSet(gen_LR::Character_set& toBeAppended,gen_LR::Character_set& toAppend);
    void cascadingUpdate(gen_LR::P_left updatedNode,
                     std::unordered_map<gen_LR::P_left, gen_LR::Character_set, gen_LR::NodeHash> &influenceList,
                     std::set<gen_LR::P_left> &updatedList);
}