#include <stdc++.h>
namespace gen_LR
{
    //Readable Stack
    //Can fetch a segment of the stack
    template <class T>
    class ReadableStack
    {
        private:
            std::vector<T> stack;
        public:
        void push(T element);
        void pop();
        //return -1 if no such element in the stack
        //return the index of the first same element in the stack
        int contain(T element);
        bool empty() const{
            return stack.empty();
        }
        std::vector<T> getRoute(int index);
        std::vector<T> getRoute(T element);
    };

    template <class T>
    void ReadableStack<T>::push(T element)
    {
        stack.push_back(element);
    }
    template <class T>
    void ReadableStack<T>::pop()
    {
        stack.pop_back();
    }
    template <class T>
    int ReadableStack<T>::contain(T element)
    {
        for(int i=0;i<stack.size();i++)
        {
            if(stack[i]==element)
            {
                return i;
            }
        }
        return -1;
    }
    template <class T>
    std::vector<T> ReadableStack<T>::getRoute(int index)
    {
        std::vector<T> route;
        route.insert(route.end(),stack.begin()+index,stack.end());
        return route;
    }
    template <class T>
    std::vector<T> ReadableStack<T>::getRoute(T element)
    {
        int index=contain(element);
        if(-1!=index)
        {
            return contain(index);
        }
        else
        {
            return std::vector<T> route;
        }
    }

    using Character_set=std::set<V_T>;
    std::unordered_map<P_left,Character_set,NodeHash> FIRST_set;//FITST set
    void generateFIRST();
}