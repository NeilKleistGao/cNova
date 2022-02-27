// MIT License
//
// Copyright (c) 2020 NeilKleistGao, ZhanHao Liang
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

#include "parser.h"
#include "parser_exceptions.h"
#include "types.h"

namespace cnova::parser
{
    //简化名命空间
    using terminalEnum = vm::nova_data::TokenType;
    std::unordered_map<std::string, std::set<vm::nova_data::TokenType> > Parser::first_set = {
        {"S",{
                terminalEnum::EXTERN,
                terminalEnum::BIT_NOT,
                terminalEnum::LOGICAL_NOT,
                terminalEnum::INCREMENT,
                terminalEnum::DECREASE,
                terminalEnum::LEFT_PARENTHESES,
                terminalEnum::LEFT_SQUARE_BRACKETS,
                terminalEnum::LEFT_BRACES,
                terminalEnum::VARIABLE,
                terminalEnum::VAL_STRING,
                terminalEnum::NULLPTR,
                terminalEnum::TRUE,
                terminalEnum::FALSE,
                terminalEnum::RETURN,
                terminalEnum::AUTO,
                terminalEnum::REGISTER,
                terminalEnum::BREAK,
                terminalEnum::CONTINUE,
                terminalEnum ::IF,
                terminalEnum ::WHILE,
            }},
        {"A",{
                 terminalEnum::EXTERN,
                 terminalEnum::BIT_NOT,
                 terminalEnum::LOGICAL_NOT,
                 terminalEnum::INCREMENT,
                 terminalEnum::DECREASE,
                 terminalEnum::LEFT_PARENTHESES,
                 terminalEnum::LEFT_SQUARE_BRACKETS,
                 terminalEnum::LEFT_BRACES,
                 terminalEnum::VARIABLE,
                 terminalEnum::VAL_STRING,
                 terminalEnum::NULLPTR,
                 terminalEnum::TRUE,
                 terminalEnum::FALSE,
                 terminalEnum::RETURN,
                 terminalEnum::AUTO,
                 terminalEnum::REGISTER,
                 terminalEnum::BREAK,
                 terminalEnum::CONTINUE,
                 terminalEnum::IF,
                 terminalEnum::WHILE,
             }},
        {"sentence",{
                     terminalEnum::EXTERN,
                     terminalEnum::BIT_NOT,
                     terminalEnum::LOGICAL_NOT,
                     terminalEnum::INCREMENT,
                     terminalEnum::DECREASE,
                     terminalEnum::LEFT_PARENTHESES,
                     terminalEnum::LEFT_SQUARE_BRACKETS,
                     terminalEnum::LEFT_BRACES,
                     terminalEnum::VARIABLE,
                     terminalEnum::VAL_STRING,
                     terminalEnum::NULLPTR,
                     terminalEnum::TRUE,
                     terminalEnum::FALSE,
                     terminalEnum::RETURN,
                     terminalEnum::AUTO,
                     terminalEnum::REGISTER,
                     terminalEnum::BREAK,
                     terminalEnum::CONTINUE,
                     terminalEnum::IF,
                     terminalEnum::WHILE,
             }},
        {"line",{
                     terminalEnum::EXTERN,
                     terminalEnum::BIT_NOT,
                     terminalEnum::LOGICAL_NOT,
                     terminalEnum::INCREMENT,
                     terminalEnum::DECREASE,
                     terminalEnum::LEFT_PARENTHESES,
                     terminalEnum::LEFT_SQUARE_BRACKETS,
                     terminalEnum::LEFT_BRACES,
                     terminalEnum::VARIABLE,
                     terminalEnum::VAL_STRING,
                     terminalEnum::NULLPTR,
                     terminalEnum::TRUE,
                     terminalEnum::FALSE,
                     terminalEnum::RETURN,
                     terminalEnum::AUTO,
                     terminalEnum::REGISTER,
                     terminalEnum::BREAK,
                     terminalEnum::CONTINUE,
             }},
        {"block",{
                     terminalEnum::IF,
                     terminalEnum::WHILE,
             }},
        {"extern_line",{
                     terminalEnum::EXTERN,
             }},
        {"var_list",{
                     terminalEnum::VARIABLE,
             }},
        {"B",{
                     terminalEnum ::COMMA,
             }},
        {"type",{
                        terminalEnum::INT,
                        terminalEnum::FLOAT,
                        terminalEnum::BOOL,
                        terminalEnum::STRING,
             }},
        {"bop",{
                       terminalEnum::ADD,
                       terminalEnum::SUB,
                       terminalEnum::MULTIPLY,
                       terminalEnum::DIV,
                       terminalEnum::POWER,
                       terminalEnum::BIT_AND,
                       terminalEnum::BIT_OR,
                       terminalEnum::BIT_XOR,
                       terminalEnum::LEFT_SHIFT,
                       terminalEnum::RIGHT_SHIFT,
                       terminalEnum::EQUAL,
                       terminalEnum::NOT_EQUAL,
                       terminalEnum::LESS,
                       terminalEnum::GREATER,
                       terminalEnum::LESS_OR_EQUAL,
                       terminalEnum::GREATER_OR_EQUAL,
                       terminalEnum::LOGICAL_AND,
                       terminalEnum::LOGICAL_OR,
                       terminalEnum::PTR,
                       terminalEnum::ADD_AND_ASSIGN,
                       terminalEnum::SUB_AND_ASSIGN,
                       terminalEnum::MULTIPLY_AND_ASSIGN,
                       terminalEnum::DIV_AND_ASSIGN,
                       terminalEnum::POWER_AND_ASSIGN,
                       terminalEnum::AND_AND_ASSIGN,
                       terminalEnum::OR_AND_ASSIGN,
                       terminalEnum::XOR_AND_ASSIGN,
                       terminalEnum::LEFT_SHIFT_AND_ASSIGN,
                       terminalEnum::RIGHT_SHIFT_AND_ASSIGN,
                       terminalEnum::ASSIGN,
                       terminalEnum::MOD,
                       terminalEnum::MOD_AND_EQUAL
                }},
        {"uop",{
                       terminalEnum::BIT_NOT,
                       terminalEnum::LOGICAL_NOT,
                       terminalEnum::INCREMENT,
                       terminalEnum::DECREASE,
                }},
        {"expr", {
                     terminalEnum::LEFT_BRACES,
                     terminalEnum::LEFT_PARENTHESES,
                     terminalEnum::LEFT_SQUARE_BRACKETS,
                     terminalEnum::VARIABLE,
                     terminalEnum::VAL_STRING,
                     terminalEnum::VAL_FLOAT,
                     terminalEnum::VAL_INTEGER,
                     terminalEnum::NULLPTR,
                     terminalEnum::TRUE,
                     terminalEnum::FALSE,
                     terminalEnum::BIT_NOT,
                     terminalEnum::LOGICAL_NOT,
                     terminalEnum::INCREMENT,
                     terminalEnum::DECREASE,

                 }},
        {"plist", {
                      terminalEnum::LEFT_BRACES,
                      terminalEnum::LEFT_PARENTHESES,
                      terminalEnum::LEFT_SQUARE_BRACKETS,
                      terminalEnum::VARIABLE,
                      terminalEnum::VAL_STRING,
                      terminalEnum::VAL_FLOAT,
                      terminalEnum::VAL_INTEGER,
                      terminalEnum::NULLPTR,
                      terminalEnum::TRUE,
                      terminalEnum::FALSE,
                      terminalEnum::BIT_NOT,
                      terminalEnum::LOGICAL_NOT,
                      terminalEnum::INCREMENT,
                      terminalEnum::DECREASE,
                  }},
        {"J", {
                  terminalEnum::INT,
                  terminalEnum::FLOAT,
                  terminalEnum::BOOL,
                  terminalEnum::STRING,
                  terminalEnum::LEFT_BRACES,
                  terminalEnum::LEFT_PARENTHESES,
                  terminalEnum::LEFT_SQUARE_BRACKETS,
                  terminalEnum::VARIABLE,
                  terminalEnum::VAL_STRING,
                  terminalEnum::VAL_FLOAT,
                  terminalEnum::VAL_INTEGER,
                  terminalEnum::NULLPTR,
                  terminalEnum::TRUE,
                  terminalEnum::FALSE,
                  terminalEnum::BIT_NOT,
                  terminalEnum::LOGICAL_NOT,
                  terminalEnum::INCREMENT,
                  terminalEnum::DECREASE,
              }},
        {"K", {
                  terminalEnum::BIT_NOT,
                  terminalEnum::LOGICAL_NOT,
                  terminalEnum::INCREMENT,
                  terminalEnum::DECREASE,
                  terminalEnum::ADD,
                  terminalEnum::SUB,
                  terminalEnum::MULTIPLY,
                  terminalEnum::DIV,
                  terminalEnum::POWER,
                  terminalEnum::BIT_AND,
                  terminalEnum::BIT_OR,
                  terminalEnum::BIT_XOR,
                  terminalEnum::LEFT_SHIFT,
                  terminalEnum::RIGHT_SHIFT,
                  terminalEnum::EQUAL,
                  terminalEnum::NOT_EQUAL,
                  terminalEnum::LESS,
                  terminalEnum::GREATER,
                  terminalEnum::LESS_OR_EQUAL,
                  terminalEnum::GREATER_OR_EQUAL,
                  terminalEnum::LOGICAL_AND,
                  terminalEnum::LOGICAL_OR,
                  terminalEnum::PTR,
                  terminalEnum::ADD_AND_ASSIGN,
                  terminalEnum::SUB_AND_ASSIGN,
                  terminalEnum::MULTIPLY_AND_ASSIGN,
                  terminalEnum::DIV_AND_ASSIGN,
                  terminalEnum::POWER_AND_ASSIGN,
                  terminalEnum::AND_AND_ASSIGN,
                  terminalEnum::OR_AND_ASSIGN,
                  terminalEnum::XOR_AND_ASSIGN,
                  terminalEnum::LEFT_SHIFT_AND_ASSIGN,
                  terminalEnum::RIGHT_SHIFT_AND_ASSIGN,

              }},
        {"M", {terminalEnum::COMMA}},
        {"L", {terminalEnum::LEFT_BRACES, terminalEnum::LEFT_PARENTHESES, terminalEnum::LEFT_SQUARE_BRACKETS, terminalEnum::VARIABLE, terminalEnum::VAL_STRING, terminalEnum::VAL_FLOAT, terminalEnum::VAL_INTEGER, terminalEnum::NULLPTR, terminalEnum::TRUE, terminalEnum::FALSE, terminalEnum::BIT_NOT, terminalEnum::LOGICAL_NOT, terminalEnum::INCREMENT, terminalEnum::DECREASE, terminalEnum::RIGHT_PARENTHESES}},
        {"while_block", {terminalEnum::WHILE}},
        {"H", {terminalEnum::ELSE}},
        {"else_if_block", {terminalEnum::ELSE}},
        {"G", {terminalEnum::ELSE}},
        {"E",{
                terminalEnum::VARIABLE,
                terminalEnum::VAL_STRING
                  }},
        {"return_line",{terminalEnum::RETURN}},
        {"declaration_line",{terminalEnum::AUTO}},
        {"F",{terminalEnum::VAL_STRING}},
        {"register_line", {terminalEnum::REGISTER}},
        {"break_line", {terminalEnum::BREAK}},
        {"continue_line", {terminalEnum::CONTINUE}},
        {"if_block", {terminalEnum::IF}},

        {"return_line", {terminalEnum::RETURN}},
        {"declaration_line", {terminalEnum::AUTO}},
        {"F", {
                  terminalEnum::VAL_STRING,
                  terminalEnum::VAL_FLOAT,
                  terminalEnum::VAL_INTEGER,
              }},
        {"register_line", {terminalEnum::REGISTER}},
        {"break_line", {terminalEnum::BREAK}},
        {"continue_line", {terminalEnum::CONTINUE}},
        {"if_block", {terminalEnum::IF}},
        {"dict_type",{terminalEnum::LEFT_BRACES}},
        {"left_type",{terminalEnum::VARIABLE}}
    };

    std::unordered_map<terminalEnum, unsigned short> Parser::PRIORITY_TABLE = {
            {terminalEnum::INCREMENT, 0},
            {terminalEnum::DECREASE, 0},
            {terminalEnum::LOGICAL_NOT, 1},
            {terminalEnum::BIT_NOT, 1},
            {terminalEnum::MULTIPLY, 2},
            {terminalEnum::DIV, 2},
            {terminalEnum::MOD, 2},
            {terminalEnum::ADD, 3},
            {terminalEnum::SUB, 3},
            {terminalEnum::LEFT_SHIFT, 4},
            {terminalEnum::RIGHT_SHIFT, 4},
            {terminalEnum::LESS, 5},
            {terminalEnum::LESS_OR_EQUAL, 5},
            {terminalEnum::GREATER, 5},
            {terminalEnum::GREATER_OR_EQUAL, 5},
            {terminalEnum::EQUAL, 6},
            {terminalEnum::NOT_EQUAL, 6},
            {terminalEnum::BIT_AND, 7},
            {terminalEnum::BIT_XOR, 8},
            {terminalEnum::BIT_OR, 9},
            {terminalEnum::LOGICAL_AND, 10},
            {terminalEnum::LOGICAL_OR, 11},
            {terminalEnum::ASSIGN, 12},
            {terminalEnum::ADD_AND_ASSIGN, 13},
            {terminalEnum::SUB_AND_ASSIGN, 13},
            {terminalEnum::MULTIPLY_AND_ASSIGN, 14},
            {terminalEnum::DIV_AND_ASSIGN, 14},
            {terminalEnum::MOD_AND_EQUAL, 14},
            {terminalEnum::LEFT_SHIFT_AND_ASSIGN, 15},
            {terminalEnum::RIGHT_SHIFT_AND_ASSIGN, 15},
            {terminalEnum::AND_AND_ASSIGN, 16},
            {terminalEnum::OR_AND_ASSIGN, 16},
            {terminalEnum::XOR_AND_ASSIGN, 16}
    };

    std::vector<vm::nova_data> Parser::start(vm::CNovaVM* vm)
    {
        try {
            _vm = vm;
            cur = token_stream.begin();
            procStart();
        } catch (ParserException e) {
            e.printstack();
        }

        return _results;
    }
    void Parser::procStart()
    {
        procSentence();
        procAhead();
    }
    void Parser::procSentence()
    {
        //如果当前的符号是line的First集中的元素
        //则执行    procLine();
        //如果当前的符号是block的First集中的元素
        //则执行    procBlock();
        //否则      报错
        auto type = cur->type;
        if (type == terminalEnum::EXTERN || type == terminalEnum::BIT_NOT ||
            type == terminalEnum::LOGICAL_NOT || type == terminalEnum::INCREMENT ||
            type == terminalEnum::DECREASE || type == terminalEnum::LEFT_PARENTHESES ||
            type == terminalEnum::LEFT_SQUARE_BRACKETS || type == terminalEnum::LEFT_BRACES ||
            type == terminalEnum::VARIABLE || type == terminalEnum::VAL_STRING ||
            type == terminalEnum::NULLPTR || type == terminalEnum::TRUE || type == terminalEnum::FALSE ||
            type == terminalEnum::RETURN || type == terminalEnum::AUTO || type == terminalEnum::REGISTER ||
            type == terminalEnum::BREAK || type == terminalEnum::CONTINUE)
        {
            procLine();
        }
        else if (type == terminalEnum::IF || type == terminalEnum::WHILE) {
            procBlock();
        }
        else {
            throw parser::ParserException("sentence error");
        }
        return;
    }
    void Parser::procAhead()
    {
        //如果当前的符号是S的First集中的元素
        //则执行    procStart();

        //否则      pass

        if (_breaking || cur == token_stream.end()) {
            return;
        }

        cur++;
        auto type = cur->type;
        if (type == terminalEnum::EXTERN || type == terminalEnum::BIT_NOT ||
            type == terminalEnum::LOGICAL_NOT || type == terminalEnum::INCREMENT ||
            type == terminalEnum::DECREASE || type == terminalEnum::LEFT_PARENTHESES ||
            type == terminalEnum::LEFT_SQUARE_BRACKETS || type == terminalEnum::LEFT_BRACES ||
            type == terminalEnum::VARIABLE || type == terminalEnum::VAL_STRING ||
            type == terminalEnum::NULLPTR || type == terminalEnum::TRUE || type == terminalEnum::FALSE ||
            type == terminalEnum::RETURN || type == terminalEnum::AUTO || type == terminalEnum::REGISTER ||
            type == terminalEnum::BREAK || type == terminalEnum::CONTINUE || type == terminalEnum::IF ||
            type == terminalEnum::WHILE)
        {
            procStart();
        }
        else if (type == terminalEnum::RIGHT_BRACES && (cur - 1)->type != vm::nova_data::SEMICOLON) {
            --cur;
        }
    }

    void Parser::procLine()
    {
        //if *cur in first(extern_line)
        //procExtern_line()
        //if *cur in first(calc_line)
        //procCalc_line()
        //...
        //else error()
        auto type = cur->type;
        if (type == terminalEnum::EXTERN)
        {
            procExternLine();
        }
        else if (type == terminalEnum::BIT_NOT ||
                 type == terminalEnum::LOGICAL_NOT || type == terminalEnum::INCREMENT ||
                 type == terminalEnum::DECREASE || type == terminalEnum::LEFT_PARENTHESES ||
                 type == terminalEnum::LEFT_SQUARE_BRACKETS || type == terminalEnum::LEFT_BRACES ||
                 type == terminalEnum::VARIABLE || type == terminalEnum::VAL_STRING ||
                 type == terminalEnum::NULLPTR || type == terminalEnum::TRUE || type == terminalEnum::FALSE)
        {
            procExpr(true);
        }
        else if (type == terminalEnum::RETURN)
        {
            procReturnLine();
        }
        else if (type == terminalEnum::AUTO)
        {
            procDeclarationLine();
        }
        else if (type == terminalEnum::REGISTER)
        {
            procRegisterLine();
        }
        else if (type == terminalEnum::BREAK)
        {
            procBreakLine();
        }
        else if (type == terminalEnum::CONTINUE)
        {
            procContinueLine();
        }
        else
        {
            throw parser::ParserException("line");
        }

        return;
    }
    void Parser::procBlock()
    {
        auto type = cur->type;
        if (type == terminalEnum::IF)
        {
            procIfBlock();
        }
        else if (type == terminalEnum::WHILE)
        {
            while(procWhileBlock());
        }
        else
        {
            throw parser::ParserException("block");
        }
    }
    void Parser::procExternLine()
    {
        if (cur->type == terminalEnum::EXTERN)
        {
            cur++;
            procVarList([&](const std::string& name) {
                _vm->addInputToSymbolTable(name);
            });
            if (cur->type == terminalEnum::SEMICOLON)
            {
                return;
            }
        }
        throw parser::ParserException("extern_line");
    }

    void Parser::procVarList(std::function<void(const std::string&)> op, const bool& ext) {
        while (true) {
            auto data = procExpr();
            if (data.type == terminalEnum::VARIABLE) {
                op(data.data.string_data);
//            cur++;
//                procVarListRest(op, ext);
//                return;
            }
            else if (!ext) {
                _results.push_back(data);
//                procVarListRest(op, ext);
//                return;
            }
            else {
                throw parser::ParserException("var_list");
            }

            if (cur->type == terminalEnum::COMMA) {
                cur++;
//                procVarList(op, ext);
            }
            else {
                break;
            }
        }
    }

//    void Parser::procVarListRest(std::function<void(const std::string&)> op, const bool& ext) {
//        if (cur->type == terminalEnum::COMMA) {
//            cur++;
//            procVarList(op, ext);
//        }
//        return;
//    }

    //Writen by ShaoXuan Yun

    vm::nova_data Parser::procRef(const vm::nova_data& parent) {
        if (cur->type == terminalEnum::LEFT_SQUARE_BRACKETS) {
            ++cur;
            auto index = procExpr();
            if (index.type == lexical::TokenData::VARIABLE) {
                index = _vm->getSymbolData(index.data.string_data);
            }

            auto temp = parent;
            if (temp.type == lexical::TokenData::VARIABLE) {
                temp = _vm->getSymbolData(temp.data.string_data);
            }

            vm::nova_data res{};
            if (temp.type == lexical::TokenData::DICTIONARY && index.type == lexical::TokenData::VAL_STRING) {
                auto dic_p = reinterpret_cast<vm::nova_dictionary>(temp.data.pointer_data);
                if (dic_p->find(index.data.string_data) == dic_p->end()) {
                    (*dic_p)[index.data.string_data] = {};
                    (*dic_p)[index.data.string_data].type = lexical::TokenData::NULLPTR;
                }

                res.type = lexical::TokenData::REFERENCE;
                res.data.pointer_data = &(*dic_p)[index.data.string_data];
            }
            else if (temp.type == lexical::TokenData::ARRAY && index.type == lexical::TokenData::VAL_INTEGER) {
                auto arr_p = reinterpret_cast<vm::nova_array>(temp.data.pointer_data);
                if (arr_p->size() <= index.data.int_data) {
                    // TODO:
                }

                res.type = lexical::TokenData::REFERENCE;
                res.data.pointer_data = &(*arr_p)[index.data.int_data];
            }
            else {
                // TODO:
            }

            if (cur->type == lexical::TokenData::RIGHT_SQUARE_BRACKETS) {
                ++cur;
            }
            else {
                //TODO:
            }

            return res;
        }
        else {
            throw parser::ParserException("LeftType");
        }
    }

    void Parser::procC()
    {
        if (cur->type == terminalEnum::LEFT_SQUARE_BRACKETS)
        {
            cur++;
            auto type = cur->type;
            if (type == terminalEnum::VAL_FLOAT || type == terminalEnum::VAL_INTEGER || type == terminalEnum::VAL_STRING || type == terminalEnum::VARIABLE)
            {
                cur++;
                if (cur->type == terminalEnum::RIGHT_SQUARE_BRACKETS)
                    cur++;
                else
                    throw parser::ParserException("C");
            }
            else
            {

                throw parser::ParserException("C");
            }
        }
    }

    void Parser::procDictList()
    {
        auto type = cur->type;
        if (type == terminalEnum::LEFT_BRACES) {
//            procDictType();
            ++cur;
            if (cur->type != terminalEnum::RIGHT_BRACES) {
                // TODO:
            }
        }
        else {
            // TODO:
        }
//        else if (type == terminalEnum::COMMA)
//        {
//            cur++;
//            procDictType();
//        }
//        else
//        {
//            throw parser::ParserException("DictList");
//        }
    }

//    void Parser::procDictType()
//    {
//        if (cur->type == terminalEnum::LEFT_BRACES)
//        { //左大括号
//            cur++;
//            auto type = cur->type;
//            if (type == terminalEnum::VAL_FLOAT || type == terminalEnum::VAL_INTEGER || type == terminalEnum::VAL_STRING || type == terminalEnum::VARIABLE)
//            {
//                cur++;
//                if (cur->type == terminalEnum::COMMA)
//                {
//                    cur++;
//                    procD();
//                }
//                else
//                    throw parser::ParserException("DictType");
//            }
//            else
//            {
//                throw parser::ParserException("DictType");
//            }
//        }
//        else
//        {
//            throw parser::ParserException("DictType");
//        }
//    }

    void Parser::procD()
    {
        auto type = cur->type;
        if (type == terminalEnum::VAL_FLOAT || type == terminalEnum::VAL_STRING || type == terminalEnum::VAL_INTEGER || type == terminalEnum::VARIABLE)
        {
            cur++;
            if (cur->type == terminalEnum::RIGHT_SQUARE_BRACKETS)
                cur++;
            else
                throw parser::ParserException("D");
        }
        else
        {

            throw parser::ParserException("D");
        }
    }

    void Parser::procArrList(vm::nova_array arr)
    {
        while (true) {
            auto temp = *cur;
            auto type = temp.type;
            if (temp.type == lexical::TokenData::VARIABLE) {
                temp = _vm->getSymbolData(temp.data.string_data);
            }
            if (temp.type == lexical::TokenData::REFERENCE) {
                temp = *reinterpret_cast<vm::nova_data*>(temp.data.pointer_data);
            }

            if (type == terminalEnum::VAL_FLOAT ||
                type == terminalEnum::VAL_INTEGER ||
                type == terminalEnum::VAL_STRING)
            {
                arr->push_back(temp);
                cur++;
            }
            else if (type == terminalEnum::COMMA) {
                cur++;
//                procE();
            }
            else if (type == terminalEnum::RIGHT_SQUARE_BRACKETS) {
                break;
            }
            else {
                throw parser::ParserException("ArrList");
            }
        }
    }

    void Parser::procE()
    {
        auto type = cur->type;
        if (type == terminalEnum::VARIABLE|| type == terminalEnum::VAL_STRING||
        cur->type==terminalEnum::VAL_FLOAT||cur->type==terminalEnum::VAL_INTEGER){
            cur++;
            return;
        }
        else
        {
            throw parser::ParserException("missing E");
        }
    }
    void Parser::procReturnLine() {
        if(cur->type == terminalEnum::RETURN){
            cur++;
            if (first_set["var_list"].count(cur->type)) {
                procVarList([&](const std::string& name){
                    _results.push_back(_vm->getSymbolData(name));
                }, false);
                ++cur;
                if (cur->type == terminalEnum::SEMICOLON) {
                    return;
                }
            }
            else {
                throw parser::ParserException("missing ReturnLine");
            }
        }
        else {
            throw parser::ParserException("missing return");
        }
    }

    void Parser::procDeclarationLine()
    {
        if (cur->type == terminalEnum::AUTO)
        {
            ++cur;
            if (cur->type == terminalEnum::VARIABLE)
            {
                std::string var_name = cur->data.string_data;
                ++cur;
                if (cur->type == terminalEnum::ASSIGN)
                {
                    ++cur;
                    if (first_set["expr"].count(cur->type))
                    {
                        auto data = procExpr(true);
                        if (data.type == vm::nova_data::VARIABLE) {
                            auto temp = _vm->getSymbolData(data.data.string_data);
                            _vm->modifySymbol(var_name, temp);
                        }
                        else {
                            _vm->modifySymbol(var_name, data);
                        }
                        return;
                    }
                    else {
                        throw parser::ParserException("missing expression");
                    }
                }
                else {
                    throw parser::ParserException("missing =");
                }
            }
            else {
                throw parser::ParserException("missing variable");
            }
        }
        else {
            throw parser::ParserException("missing auto");
        }
    }
    void Parser::procF(){
        if(cur->type == terminalEnum::VAL_STRING
           ||cur->type==terminalEnum::VAL_FLOAT
           ||cur->type==terminalEnum::VAL_INTEGER){
            ++cur;
            return;
        }
        else {
            throw parser::ParserException("missing literal");
        }
    }
    void Parser::procRegisterLine() {
        if (cur->type == terminalEnum::REGISTER) {
            ++cur;
            if (cur->type == terminalEnum::VAL_STRING) {
                _vm->registerSTLLib(cur->data.string_data);
                ++cur;
                return;
            }
            else {
                throw parser::ParserException("missing literal");
            }
        }
        else {
            throw parser::ParserException("missing register");
        }
    }
    void Parser::procBreakLine() {
        if (cur->type == terminalEnum::BREAK) {
            if (!_vm->isInALoop()) {
                // TODO:
            }

            ++cur;
            if (cur->type == vm::nova_data::SEMICOLON) {
                cur = _vm->popLoop();
                --cur;
                _breaking = true;
                return;
            }
            else {
                throw parser::ParserException("missing ;");
            }
        }
        else {
            throw parser::ParserException("missing break");
        }
    }

    void Parser::procContinueLine()
    {
        if (cur->type == terminalEnum::CONTINUE)
        {
            ++cur;
            if (cur->type == terminalEnum::SEMICOLON)
            {
                ++cur;
                return;
            }
            else
                throw parser::ParserException("misson ;");
        }
        else
            throw parser::ParserException("missing continue");
    }

    void Parser::procIfBlock() {
        // proc if( expr ){ S } G
        if (cur->type == terminalEnum::IF) {
            ++cur;
            if (cur->type == terminalEnum::LEFT_PARENTHESES) {
                ++cur;
                if (first_set["expr"].count(cur->type)) {
                    auto data = procExpr(true);
                    if (cur->type == terminalEnum::RIGHT_PARENTHESES) {
                        ++cur;
                        if (Operators::isExpressionFalse(data)) {
                            parseUntilBlockEnd();

                            if (first_set["G"].count(cur->type))
                            {
                                procElseOrElseIf();
                            }
                            else {
                                --cur;
                            }
                            return;
                        }

                        _vm->enterSubSpace();
                        if (cur->type == terminalEnum::LEFT_BRACES) {
                            ++cur;
                            if (first_set["S"].count(cur->type)) {
                                procStart();
                                if (_breaking) {
                                    _vm->exitSubSpace();
                                    return;
                                }

                                if (cur->type == terminalEnum::RIGHT_BRACES) {
                                    cur++;
                                    if (first_set["G"].count(cur->type)) {
                                        procElseOrElseIf(true);
                                        return;
                                    }
                                }
                                else {
                                    throw parser::ParserException("missing }");
                                }
                            }
                            else {
                                throw parser::ParserException("missing S");
                            }
                        }
                        else {
                            throw parser::ParserException("missing {");
                        }
                    }
                    else {
                        throw parser::ParserException("missing )");
                    }
                }
                else {
                    throw parser::ParserException("missing expr");
                }
            }
            else {
                throw parser::ParserException("missing (");
            }
        }
        else {
            throw parser::ParserException("missing if");
        }
    }

    //Writen by BaiTong Zhang
    vm::nova_data Parser::procType() {
        auto type = cur->type;
        if (type == terminalEnum::INT ||
            type == terminalEnum::FLOAT ||
            type == terminalEnum::BOOL ||
            type == terminalEnum::STRING) {
            auto temp = *cur;
            ++cur;
            if (cur->type != terminalEnum::RIGHT_PARENTHESES) {
                // TODO:
            }
            ++cur;
            return temp;
        }
        else {
            throw parser::ParserException("Type");
        }
    }

    Parser::bop_func Parser::procBop()
    {
        auto type = cur->type;
        bop_func func;
        if (type == terminalEnum::ADD || type == terminalEnum::ADD_AND_ASSIGN) {
            func = Operators::add;
        }
        else if (type == terminalEnum::SUB || type == terminalEnum::SUB_AND_ASSIGN) {
            func = Operators::sub;
        }
        else if (type == terminalEnum::MULTIPLY || type == terminalEnum::MULTIPLY_AND_ASSIGN) {
            func = Operators::multiply;
        }
        else if (type == terminalEnum::DIV || type == terminalEnum::DIV_AND_ASSIGN) {
            func = Operators::div;
        }
        else if (type == terminalEnum::POWER) {
            // TODO:
        }
        else if (type == terminalEnum::BIT_AND) {
            func = Operators::bit_and;
        }
        else if (type == terminalEnum::BIT_OR) {
            // TODO:
        }
        else if (type == terminalEnum::BIT_XOR) {
            // TODO:
        }
        else if (type == terminalEnum::LEFT_SHIFT) {
            // TODO:
        }
        else if (type == terminalEnum::RIGHT_SHIFT || type == terminalEnum::RIGHT_SHIFT_AND_ASSIGN) {
            func = Operators::right_shift;
        }
        else if (type == terminalEnum::EQUAL) {
            func = Operators::equal;
        }
        else if (type == terminalEnum::NOT_EQUAL) {
            // TODO:
        }
        else if (type == terminalEnum::LESS) {
            // TODO:
        }
        else if (type == terminalEnum::GREATER) {
            func = Operators::greater;
        }
        else if (type == terminalEnum::LESS_OR_EQUAL) {
            // TODO:
        }
        else if (type == terminalEnum::GREATER_OR_EQUAL) {
            // TODO:
        }
        else if (type == terminalEnum::LOGICAL_AND) {
            // TODO:
        }
        else if (type == terminalEnum::LOGICAL_OR) {
            // TODO:
        }
        else if (type == terminalEnum::PTR) {
            // TODO:
        }
        else if (type == terminalEnum::DIV_AND_ASSIGN) {
            // TODO:
        }
        else if (type == terminalEnum::POWER_AND_ASSIGN) {
            // TODO:
        }
        else if (type == terminalEnum::AND_AND_ASSIGN) {
            // TODO:
        }
        else if (type == terminalEnum::OR_AND_ASSIGN) {
            // TODO:
        }
        else if (type == terminalEnum::XOR_AND_ASSIGN) {
            // TODO:
        }
        else if (type == terminalEnum::LEFT_SHIFT_AND_ASSIGN) {
            // TODO:
        }
        else if (type == terminalEnum::ASSIGN) {
            func = Operators::assign;
        }
        else if (type == terminalEnum::MOD || type == terminalEnum::MOD_AND_EQUAL) {
            func = Operators::mod;
        }
        else {
            throw parser::ParserException("Type");
        }

        _priority.push(PRIORITY_TABLE[cur->type]);
        ++cur;
        return func;
    }

    Parser::uop_func Parser::procUop(const bool& sure_front)
    {
        uop_func func;
        auto type = cur->type;
        if (type == terminalEnum::DECREASE) {
            // TODO:
        }
        else if (type == terminalEnum::INCREMENT) {
            func = Operators::increase;
        }
        else if (type == terminalEnum::LOGICAL_NOT) {
            // TODO:
        }
        else if (type == terminalEnum::BIT_NOT) {
            // TODO:
        }
        else if (type == terminalEnum::SUB) {
            func = Operators::minus;
        }
        else {
            throw parser::ParserException("Type");
        }

        _priority.push(PRIORITY_TABLE[type]);
        ++cur;
        return func;
    }

    vm::nova_data Parser::procParentheses() {
        auto type = cur->type;
        //type和expr的first集没有重复，可以直接判断
        if (first_set["type"].count(type)) {
            auto type = procType();
            if (cur->type == terminalEnum::LEFT_PARENTHESES) {
                ++cur;
                auto res = procExpr(true);
                if (cur->type != terminalEnum::RIGHT_PARENTHESES) {
                    // TODO:
                }

                res = transform(res, type);
                return res;
            }
            else {
                throw parser::ParserException("J");
            }
        }
        else if (first_set["expr"].count(type)) {
            auto res = procExpr(true);
            if (cur->type == terminalEnum::RIGHT_PARENTHESES) {
                ++cur;
                return res;
            }
            else {
                throw parser::ParserException("J");
            }
        }

        else {
            throw parser::ParserException("J");
        }
    }

    vm::nova_data Parser::procExprRest(const vm::nova_data& data)
    {
        auto type = cur->type;
        //bop和uop的first集没有重复，可以直接判断
        if (first_set["bop"].count(type)) {
            auto func = procBop();
            auto right = procExpr();

            auto temp = cur;
            while(temp != token_stream.end() &&
                    temp->type != vm::nova_data::SEMICOLON &&
                    temp->type != vm::nova_data::RIGHT_BRACES &&
                    temp->type != vm::nova_data::RIGHT_PARENTHESES &&
                    temp->type != vm::nova_data::RIGHT_SQUARE_BRACKETS &&
                    temp->type != vm::nova_data::COMMA &&
                    !first_set["bop"].count(type)) {
                ++temp;
            }

            if (temp != token_stream.end()) {
                // TODO:
            }

            vm::nova_data res{};
            if (temp->type == vm::nova_data::SEMICOLON ||
                temp->type == vm::nova_data::RIGHT_BRACES ||
                temp->type == vm::nova_data::RIGHT_PARENTHESES ||
                temp->type == vm::nova_data::RIGHT_SQUARE_BRACKETS ||
                temp->type == vm::nova_data::COMMA ||
                (_priority.top() <= PRIORITY_TABLE[temp->type] && _priority.top() < 12)) {
                auto temp1 = data, temp2 = right;

                if (data.type == vm::nova_data::VARIABLE) {
                    temp1 = _vm->getSymbolData(data.data.string_data);
                }
                else if (data.type == lexical::TokenData::REFERENCE) {
                    temp1 = *reinterpret_cast<vm::nova_data*>(data.data.pointer_data);
                }
                else if (_priority.top() >= 12) {
                    // TODO:
                }
                if (right.type == vm::nova_data::VARIABLE) {
                    temp2 = _vm->getSymbolData(right.data.string_data);
                }

                res = procExprRest(func(temp1, temp2));
                if (_priority.top() >= 12) {
                    if (data.type == vm::nova_data::VARIABLE) {
                        _vm->modifySymbol(data.data.string_data, res);
                    }
                    else if (data.type == lexical::TokenData::REFERENCE) {
                        reinterpret_cast<vm::nova_data*>(data.data.pointer_data)->type = res.type;
                        reinterpret_cast<vm::nova_data*>(data.data.pointer_data)->data = res.data;
                    }
                }
            }
            else {
                auto temp1 = data, inter = procExprRest(right), temp2 = inter;

                if (data.type == vm::nova_data::VARIABLE) {
                    temp1 = _vm->getSymbolData(data.data.string_data);
                }
                else if (_priority.top() >= 12) {
                    // TODO:
                }
                if (inter.type == vm::nova_data::VARIABLE) {
                    temp2 = _vm->getSymbolData(inter.data.string_data);
                }

                res = func(data, temp2);
                if (_priority.top() >= 12) {
                    _vm->modifySymbol(data.data.string_data, res);
                }
            }

            _priority.pop();
            return res;
        }
        else if (first_set["uop"].count(type)) {
            auto func = procUop(false);
            vm::nova_data res, temp = data;
            if (data.type == lexical::TokenData::VARIABLE) {
                temp = _vm->getSymbolData(data.data.string_data);
            }
            else if (data.type == lexical::TokenData::REFERENCE) {
                temp = *reinterpret_cast<vm::nova_data*>(data.data.pointer_data);
            }

            if (_priority.top() == 0) {
                res = procExprRest(func(temp, false));
                temp.data.int_data++;
                if (data.type == lexical::TokenData::VARIABLE) {
                    _vm->modifySymbol(data.data.string_data, temp);
                }
                else if (data.type == lexical::TokenData::REFERENCE) {
                    reinterpret_cast<vm::nova_data*>(data.data.pointer_data)->type = temp.type;
                    reinterpret_cast<vm::nova_data*>(data.data.pointer_data)->data = temp.data;
                }
                else {
                    // TODO:
                }
            }
            else {
                res = procExprRest(data);
            }

            _priority.pop();
            return res;
        }
        else {
            return data;
        }
    }

//    void Parser::procL()
//    {
//
//    }

    void Parser::procPlist() {
        _param_pos.push(_param_list.size());
        while (true) {
            auto type = cur->type;
            if (cur->type == terminalEnum::RIGHT_PARENTHESES) {
                break;
            }
            else if (first_set["expr"].count(type)) {
                auto data = procExpr(true);
                if (data.type == lexical::TokenData::VARIABLE) {
                    data = _vm->getSymbolData(data.data.string_data);
                }
                _param_list.push_back(data);

                if (cur->type == terminalEnum::COMMA) {
                    ++cur;
                }
            }
            else {
                // TODO:
            }
        }
    }

//    void Parser::procM()
//    {
//        if (cur->type == terminalEnum::COMMA)
//        {
//            ++cur;
//            procPlist();
//        }
//        else
//            return;
//    }

    vm::nova_data Parser::procExpr(const bool& first)
    {
        auto type = cur->type;
        if (type == terminalEnum::LEFT_PARENTHESES) {
            ++cur;
            auto temp = procParentheses();
            if (first) {
                return procExprRest(temp);
            }
            else {
                return temp;
            }
        }
        else if (first_set["uop"].count(type) || type == lexical::TokenData::SUB) {
            auto func = procUop(true);
            auto temp = procExpr();
            _priority.pop();
            if (first) {
                return procExprRest(func(temp, true));
            }
            else {
                return func(temp, true);
            }
        }
        else if (type == terminalEnum::LEFT_BRACES) {
            ++cur;
            if (cur->type == terminalEnum::RIGHT_BRACES) {
                ++cur;
                if (cur->type == terminalEnum::SEMICOLON) {
                    auto dic = new std::map<std::string, vm::nova_data>{};
                    vm::nova_data data{};
                    data.type = lexical::TokenData::DICTIONARY;
                    data.data.pointer_data = reinterpret_cast<void*>(dic);
                    return data;
                }
                else {
                    // TODO:
                }
            }
            else {
                // TODO:
            }
//            procDictList();
        }
        else if (type == terminalEnum::LEFT_SQUARE_BRACKETS) {
            ++cur;
            vm::nova_data data;
            data.type = lexical::TokenData::ARRAY;
            auto vec = new std::vector<vm::nova_data>{};
            data.data.pointer_data = reinterpret_cast<void*>(vec);
            procArrList(vec);
            if (cur->type == terminalEnum::RIGHT_SQUARE_BRACKETS) {
                ++cur;
                return data;
            }
            else {
                throw parser::ParserException("missing ]");
            }
        }
        else if (type == terminalEnum::NULLPTR ||
                 type == terminalEnum::TRUE ||
                 type == terminalEnum::FALSE ||
                 type == terminalEnum::VAL_STRING ||
                 type == terminalEnum::VAL_FLOAT ||
                 type == terminalEnum::VAL_INTEGER )
        {
            vm::nova_data data{};
            data.type = type;
            data.data = cur->data;
            ++cur;
            if (first) {
                return procExprRest(data);
            }
            else {
                return data;
            }

        }
        else if (type == terminalEnum::VARIABLE)
        {
            //后看一位判断是var还是fname
            auto data = *cur;
            ++cur;

            //如果是 ( 就认为是fname:
            if (cur->type == terminalEnum::LEFT_PARENTHESES) {
                ++cur;
                procPlist();
                auto start = _param_pos.top();
                auto size = _param_list.size() - start;
                _param_pos.pop();
                vm::nova_data res{};
                auto fp = _vm->getSymbolData(data.data.string_data).data.pointer_data;
                switch (size) {
                    case 0:
                        break;
                    case 1:
                        res = (*reinterpret_cast<std::function<vm::nova_data(const vm::nova_data&)>*>(fp))(_param_list[start]);
                        break;
                    case 2:
                        res = (*reinterpret_cast<std::function<vm::nova_data(const vm::nova_data&, const vm::nova_data&)>*>(fp))(_param_list[start], _param_list[start + 1]);
                        break;
                    case 3:
                        res = (*reinterpret_cast<std::function<vm::nova_data(const vm::nova_data&, const vm::nova_data&, const vm::nova_data&)>*>(fp))(_param_list[start], _param_list[start + 1], _param_list[start + 2]);
                        break;
                    default:
                        // TODO:
                        break;
                }

                while (_param_list.size() > start) {
                    _param_list.pop_back();
                }

                if (cur->type != lexical::TokenData::RIGHT_PARENTHESES) {
                    // TODO:
                }

                auto temp = (cur + 1)->type;
                if (temp == lexical::TokenData::SEMICOLON ||
                    temp == lexical::TokenData::COMMA ||
                    temp == lexical::TokenData::RIGHT_PARENTHESES) {
                    ++cur;
                }

                if (first) {
                    return procExprRest(res);
                }
                else {
                    return res;
                }
            }
            else if (cur->type == terminalEnum::LEFT_SQUARE_BRACKETS) {
                if (first) {
                    return procExprRest(procRef(data));
                }
                else {
                    return procRef(data);
                }

            }
            //否则认为是var
            else {
                if (first) {
                    return procExprRest(data);
                }
                else {
                    return data;
                }
            }
        }
        else {
            throw parser::ParserException("expression error");
        }
    }

    bool Parser::procWhileBlock()
    {
        decltype(cur) next = token_stream.end(), entry = cur;
        if (cur->type == terminalEnum::WHILE) {
            ++cur;
            if (cur->type == terminalEnum::LEFT_PARENTHESES) {
                ++cur;
                if (!_vm->isInLoop(entry)) {
                    parseUntilBlockEnd();

                    next = cur;
                    _vm->pushLoop(next, entry);
                    _vm->enterSubSpace();
                    cur = entry;
                    return true;
                }

                auto data = procExpr();
                if (Operators::isExpressionFalse(data)) {
                    _vm->exitSubSpace();
                    cur = _vm->popLoop();
                    return false;
                }


                if (cur->type == terminalEnum::RIGHT_PARENTHESES) {
                    ++cur;
                    if (cur->type == terminalEnum::LEFT_BRACES) {
                        ++cur;
                        procStart();
                        if (_breaking) {
                            if (cur->type != terminalEnum::RIGHT_BRACES) {
                                // TODO:
                            }
                            _breaking = false;
                            return false;
                        }

                        if (cur->type == terminalEnum::RIGHT_BRACES) {
                            cur = entry;
                            return true;
                        }
                        else {
                            throw parser::ParserException("while missing }");
                        }
                    }
                    else {
                        throw parser::ParserException("while error");
                    }
                }
                else {
                    throw parser::ParserException("while missing )");
                }
            }
            else {
                throw parser::ParserException("while error");
            }
        }
        else {
            throw parser::ParserException("while error");
        }
    }

    void Parser::procElseIfCheck(const bool& skip) {
        if (first_set["else_if_block"].count(cur->type)) {
            procElseIfBlock(skip);
        }
    }

    void Parser::procElseIfBlock(const bool& skip)
    {
        if (cur->type == terminalEnum::ELSE) {
            ++cur;
            if (cur->type == terminalEnum::IF) {
                ++cur;
                if (cur->type == terminalEnum::LEFT_PARENTHESES) {
                    auto data = procExpr(true);

                    if (cur->type == terminalEnum::RIGHT_PARENTHESES) {
                        ++cur;
                        if (Operators::isExpressionFalse(data) || skip) {
                            parseUntilBlockEnd();
                            procElseIfCheck(skip);
                            return;
                        }

                        if (cur->type == terminalEnum::LEFT_BRACES) {
                            _vm->enterSubSpace();
                            ++cur;
                            if (first_set["S"].count(cur->type)) {
                                procStart();
                                if (_breaking) {
                                    return;
                                }
                            }
                            if (cur->type == terminalEnum::RIGHT_BRACES) {
                                _vm->exitSubSpace();
                                procElseIfCheck(true);
                                return;
                            }
                            else {
                                throw parser::ParserException("else if missing }");
                            }
                        }
                        else {
                            throw parser::ParserException("else if error");
                        }
                    }
                    else {
                        throw parser::ParserException("else if missing )");
                    }
                }
                else {
                    throw parser::ParserException("Else if error");
                }
            }
            else {
                throw parser::ParserException("Else if error");
            }
        }
        else {
            throw parser::ParserException("Else if error");
        }
    }

    void Parser::procElseOrElseIf(const bool& skip)
    {
        //G的两个产生式的first集有冲突，不能通过first来判断。
        //需要试探然后回退
        if (cur->type == terminalEnum::ELSE) {
            ++cur;
            if (cur->type == terminalEnum::LEFT_BRACES)
            {
                if (skip) {
                    parseUntilBlockEnd();
                    --cur;
                    return;
                }

                _vm->enterSubSpace();
                ++cur;
                if (first_set["S"].count(cur->type)) {
                    procStart();
                    if (_breaking) {
                        return;
                    }
                }

                if (cur->type == terminalEnum::RIGHT_BRACES) {
                    _vm->exitSubSpace();
                    return;
                }
                else {
                    throw parser::ParserException("else missing }");
                }
            }
            else if (cur->type == terminalEnum::IF) {
                --cur;
                --cur; //回退到else if的开始处
                procElseIfBlock(skip);
            }
            else {
                throw parser::ParserException("G error");
            }
        }
        else {
            return;
        }
    }

    void Parser::parseUntilBlockEnd() {
        int counter = 0; bool flag = true;
        while (counter > 0 || flag) {
            if (cur->type == vm::nova_data::LEFT_BRACES) {
                ++counter;
                flag = false;
            }
            else if (cur->type == vm::nova_data::RIGHT_BRACES) {
                --counter;
            }

            ++cur;
        }
    }

    vm::nova_data Parser::transform(const vm::nova_data& d, const vm::nova_data& to) {
        vm::nova_data res{}, from = d;
        if (from.type == lexical::TokenData::VARIABLE) {
            from = _vm->getSymbolData(from.data.string_data);
        }

        switch (from.type) {
            case lexical::TokenData::VAL_INTEGER: {
                switch (to.type) {
                    case lexical::TokenData::STRING:
                        res.type = lexical::TokenData::VAL_STRING;
                        res.data.string_data = Types::transformIntToString(from.data.int_data);
                        break;
                    default:
                        break;
                }
                break;
            }
            case lexical::TokenData::VAL_FLOAT:
                break;
            case lexical::TokenData::STRING:
                break;
            case lexical::TokenData::DICTIONARY:
                break;
            case lexical::TokenData::ARRAY:
                break;
            default:
                break;
        }

        return res;
    }

    Parser::Parser(std::vector<vm::nova_data> &token_stream) : token_stream(token_stream), _breaking(false) {}
} // namespace cnova::parser
