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
#include <set>
#include <unordered_map>
#include <functional>

#include "../lexical/lexical_definition.h"
#include "../vm/cnova_vm.h"
#include "../vm/cnova_self.h"
#include "operators.h"

namespace cnova::parser
{
    //递归调用预测分析
    //前提是First集没有冲突
    class Parser
    {
    private:
        std::vector<vm::nova_data>& token_stream;  //输入字符序列流
        std::vector<vm::nova_data>::iterator cur;  //字符序列流指针
        std::vector<vm::nova_data> _results;
        std::vector<vm::nova_data> _param_list;
        std::stack<unsigned int> _param_pos;
        std::stack<unsigned short> _priority;
        vm::CNovaVM* _vm;
        bool _breaking;

        using bop_func = Operators::bop_func;
        using uop_func = Operators::uop_func;

        // //求所有符号的First集
        // void getTotFirst();

        static std::unordered_map<std::string,std::set<vm::nova_data::TokenType>> first_set; //first集
        static std::unordered_map<vm::nova_data::TokenType, unsigned short> PRIORITY_TABLE;
        //解析文法符号
        void procStart();
        void procAhead();
        void procSentence();
        void procLine();
        void procBlock();
        void procExternLine();
        void procVarList(std::function<void(const std::string&)> op, const bool& ext = true);
//        void procVarListRest(std::function<void(const std::string&)> op, const bool& ext);
        vm::nova_data procRef(const vm::nova_data& parent);
        void procC();
        void procDictList();
//        void procDictType();
        void procD();
        void procArrList(vm::nova_array arr);
        void procE();
        void procReturnLine();
        void procDeclarationLine();
        void procF();
        void procRegisterLine();
        void procBreakLine();
        void procContinueLine();
        void procIfBlock();
        void procElseOrElseIf(const bool& skip = false);
        void procElseIfBlock(const bool& skip = false);
        void procElseIfCheck(const bool& skip);
        bool procWhileBlock();
        vm::nova_data procType();
        vm::nova_data procExpr(const bool& first = false);
        vm::nova_data procExprRest(const vm::nova_data&);
        vm::nova_data procParentheses();
        bop_func procBop();
        uop_func procUop(const bool& sure_front);
        void procPlist();
//        void procL();
//        void procM();

        void parseUntilBlockEnd();
        vm::nova_data transform(const vm::nova_data&, const vm::nova_data&);

    public:
        explicit Parser(std::vector<vm::nova_data> &token_stream);
        std::vector<vm::nova_data> start(vm::CNovaVM* vm); //开始语法分析，即S'->S
    };
} // namespace cnova::parser

#endif