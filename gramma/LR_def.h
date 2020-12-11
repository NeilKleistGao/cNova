 #include<string>
 #include<set>
 #include<vector>
 #include<unordered_map>
  namespace LR::def
 {
     //符号类型
     enum Symbol_Type
        {
            TERMINAL,
            VARIABLE
        };
    //符号
    struct V_T
    {
        Symbol_Type type;     //是否为终结符，1为终结符
        std::string raw_info; //原始的符号字面量
        V_T() = default;
        V_T(Symbol_Type s_type, const std::string &s_s) : type(s_type), raw_info(s_s) {}
        V_T(const V_T& e):type(e.type),raw_info(e.raw_info){}
        V_T operator=(const V_T&e){
            type=e.type;
            raw_info = e.raw_info;
        }
        bool operator==(const V_T &e) const
        {
            return type == e.type && raw_info == e.raw_info;
        }
        bool operator<(const V_T &e) const
        {
            return raw_info < e.raw_info;
        }
    };

    //符号用的哈希函数
    struct V_T_Hash
    {
        size_t operator()(const V_T &e) const
        {
            return e.raw_info.size() * 7 + e.type * 5;
        }
    };

    using P_left = V_T;                            //产生式左部
    using P_right = std::vector<std::vector<V_T>>; //产生式右部(允许多个)
    using Character_set = std::set<def::V_T>;
    
   
    //带点的产生式
    struct dot_P
    {
        size_t dot_index;         //·的位置，规定·位于dot_index的符号的前面. dot_index为长度时是说明读完
        P_left dot_p_left;            //产生式左部
        std::vector<V_T> dot_p_right; //产生式右部
        dot_P(size_t _i,const P_left& _l,const std::vector<V_T>& _r):
        dot_index(_i),dot_p_left(_l),dot_p_right(_r){}

    };
    //带点的产生式的哈希函数
    struct dot_P_Hash{
         size_t operator()(const dot_P &e) const
        {
            return e.dot_index * 7 + e.dot_p_left.type * 11 + e.dot_p_right.size();
        }
    };

   

    //一个项目
    struct Item
    {
        int id;
        std::vector<dot_P> P_list; //一个项目的所有带点产生式
        bool operator()(const Item& a,const Item& b)const{
            
            if(a.id==b.id){
                return a.P_list == b.P_list;
            }
        }
    };

    struct Item_cmp{
        bool operator()(const Item& a,const Item& b)const{
            return a.P_list == b.P_list;
        }
    };
   
    struct Edge
    {
        int to;        //指向的结点
        V_T condition; //读入condition后跳转到to
    };

      //带有展望符的带点产生式. first为带点的产生式，second为展望符
      using dot_P_forward = std::unordered_map<def::dot_P, std::set<V_T>,def::dot_P_Hash>;
  
   
 } // namespace name
 
 