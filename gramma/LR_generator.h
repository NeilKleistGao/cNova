#include "LR_def.h"
#include "LR_IO.h"

namespace LR::gen
{


    class LR_generator
    {
    private:
        std::vector<std::vector<std::string>> table;                                  //最终构造的表
        gen_io::InputStream *_source;                                                     //读入的产生式等内容
        std::unordered_map<def::P_left, def::Character_set, def::V_T_Hash> FIRST_set; //FITST set
        std::set<def::Item, def::Item_cmp> items;                                     //存放item
        std::vector<std::vector<def::Edge>> G;                                        //项目集规范族.G[i]表示第i个结点的边

        void appendSet(def::Character_set &toBeAppended, def::Character_set &toAppend);
        void cascadingUpdate(def::P_left updatedNode,
                             std::unordered_map<def::P_left, def::Character_set, def::V_T_Hash> &influenceList,
                             std::set<def::P_left> &updatedList);

    public:
        LR_generator(const std::string &filename = "../data/gramma.txt");
        ~LR_generator() = delete;
        LR_generator(const LR_generator &) = delete;
        LR_generator &operator=(const LR_generator &) = delete;

        //得到所有的First集
        void generateTotFirst();

        //求一个序列的First集
        std::set<def::V_T> generateFirst(std::vector<def::V_T>);

        //求一个带点的产生式的闭包
        std::unordered_map<def::dot_P, std::set<def::V_T>,def::dot_P_Hash> generateClosure(std::unordered_map<def::dot_P, std::set<def::V_T>,def::dot_P_Hash> &);

        //得到生成的图
        void generateGraph();

        //得到LR分析表
        void generateTable();
    };
} // namespace LR::gen
