#include "LR_io.hpp"
namespace gen_LR
{
    std::set<dot_P> closure(std::set<dot_P> &I)
    {
        auto J = std::set<dot_P>(I);
        do
        {
            auto J_new = std::set<dot_P>(J);
            for (auto p : J_new)
            {
                //如果·后面是非终结符
                if(p.p_right[p.dot_index].type==0){
                    
                }
            }
        }
    }
} // namespace gen_LR
