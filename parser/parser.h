// MIT License
//
// Copyright (c) 2020 NeilKleistGao
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef CNOVA_PARSER_H
#define CNOVA_PARSER_H
#include <vector>
#include "../lexical/lexical_definition.h"

namespace cnova::parser
{
    //递归调用预测分析
    //前提是First集没有冲突
    class Parser
    {
    private:
        std::vector<lexical::TokenData> tokenStream;  //输入字符序列流
        std::vector<lexical::TokenData>::iterator cur;  //字符序列流指针

        // //求所有符号的First集
        // void getTotFirst();

        // //std::multimap<V_T, V_T, V_T_Hash> firstSet;

        //解析文法符号
        void procS();
        void procSentence();
        void procA();
        void procLine();
        void procBlock();
        void procExtern_line();
        void procVar_list();
        void procB();

    public:
        void parserStart(); //开始语法分析，即S'->S
    };
} // namespace cnova::parser

#endif