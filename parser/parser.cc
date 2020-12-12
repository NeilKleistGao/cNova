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

#include "parser.h"
#include "parser_exceptions.h"

namespace cnova::parser
{
    //简化名命空间
    typedef lexical::TokenData::TokenType terminalEnum;
    std::unordered_map<std::string, std::set<lexical::TokenData::TokenType> > Parser::first_set = {
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
    //Writen by ZhanHao Liang
    void Parser::parserStart()
    {
        try {
            cur = tokenStream.begin();
            procS();
        } catch (ParserException e) {
            e.printstack();
        }
    }
    void Parser::procS()
    {
        procSentence();
        procA();
    }
    void Parser::procSentence()
    {
        //如果当前的符号是line的First集中的元素
        //则执行    procLine();
        //如果当前的符号是block的First集中的元素
        //则执行    procBlock();
        //否则      报错
        auto type = (*cur).type;
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
        else if (type == terminalEnum::IF || type == terminalEnum::WHILE)
        {
            procBlock();
        }
        else
        {
            throw parser::ParserException("sentence error");
        }
        return;
    }
    void Parser::procA()
    {
        //如果当前的符号是S的First集中的元素
        //则执行    procS();

        //否则      pass
        auto type = (*cur).type;
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
            procS();
        }
        return;
    }
    void Parser::procLine()
    {
        //if *cur in first(extern_line)
        //procExtern_line()
        //if *cur in first(calc_line)
        //procCalc_line()
        //...
        //else error()
        auto type = (*cur).type;
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
            procCalLine();
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
        auto type = (*cur).type;
        if (type == terminalEnum::IF)
        {
            procIfBlock();
        }
        else if (type == terminalEnum::WHILE)
        {
            procWhileBlock();
        }
        else
        {
            throw parser::ParserException("block");
        }
    }
    void Parser::procExternLine()
    {
        if ((*cur).type == terminalEnum::EXTERN)
        {
            cur++;
            procVarList();
            if ((*cur).type == terminalEnum::SEMICOLON)
            {
                return;
            }
        }
        throw parser::ParserException("extern_line");
    }
    void Parser::procVarList()
    {
        if ((*cur).type == terminalEnum::VARIABLE)
        {
            cur++;
            procB();
            return;
        }
        else
        {
            throw parser::ParserException("var_list");
        }
    }
    void Parser::procB()
    {
        if ((*cur).type == terminalEnum::COMMA)
        {
            cur++;
            procVarList();
        }
        return;
    }

    //Writen by ShaoXuan Yun

    void Parser::procCalLine() {
        if(first_set["expr"].count((*cur).type)){
            procExpr();
            if((*cur).type == terminalEnum::SEMICOLON){
                ++cur;
                return ;
            }
        }else if(first_set["left_type"].count((*cur).type)){
            procLeftType();
            if((*cur).type==terminalEnum::EQUAL){
                ++cur;
                if(first_set["calc_line"].count((*cur).type)){
                    procCalLine();
                }else throw parser::ParserException("missing calc_line");
            }else throw parser::ParserException("missing =");
        }else throw parser::ParserException("missing expr or left_type");
    }
    void Parser::procLeftType()
    {
        if ((*cur).type == terminalEnum::VARIABLE)
        {
            cur++;
            procC();
        }
        else
        {
            throw parser::ParserException("LeftType");
        }
        return;
    }

    void Parser::procC()
    {
        if ((*cur).type == terminalEnum::LEFT_SQUARE_BRACKETS)
        {
            cur++;
            auto type = (*cur).type;
            if (type == terminalEnum::VAL_FLOAT || type == terminalEnum::VAL_INTEGER || type == terminalEnum::VAL_STRING || type == terminalEnum::VARIABLE)
            {
                cur++;
                if ((*cur).type == terminalEnum::RIGHT_SQUARE_BRACKETS)
                    cur++;
                else
                    throw parser::ParserException("C");
            }
            else
            {

                throw parser::ParserException("C");
            }
        }
        return;
    }

    void Parser::procDictList()
    {
        auto type = (*cur).type;
        if (type == terminalEnum::LEFT_BRACES)
        {
            procDictType();
        }
        else if (type == terminalEnum::COMMA)
        {
            cur++;
            procDictType();
        }
        else
        {

            throw parser::ParserException("DictList");
        }
    }

    void Parser::procDictType()
    {

        if ((*cur).type == terminalEnum::LEFT_BRACES)
        { //左大括号
            cur++;
            auto type = (*cur).type;
            if (type == terminalEnum::VAL_FLOAT || type == terminalEnum::VAL_INTEGER || type == terminalEnum::VAL_STRING || type == terminalEnum::VARIABLE)
            {
                cur++;
                if ((*cur).type == terminalEnum::COMMA)
                {
                    cur++;
                    procD();
                }
                else
                    throw parser::ParserException("DictType");
            }
            else
            {
                throw parser::ParserException("DictType");
            }
        }
        else
        {

            throw parser::ParserException("DictType");
        }
    }

    void Parser::procD()
    {
        auto type = (*cur).type;
        if (type == terminalEnum::VAL_FLOAT || type == terminalEnum::VAL_INTEGER || type == terminalEnum::VAL_INTEGER || type == terminalEnum::VARIABLE)
        {
            cur++;
            if ((*cur).type == terminalEnum::RIGHT_SQUARE_BRACKETS)
                cur++;
            else
                throw parser::ParserException("D");
        }
        else
        {

            throw parser::ParserException("D");
        }
    }

    void Parser::procArrList()
    {
        auto type = (*cur).type;
        if (type == terminalEnum::VAL_FLOAT || type == terminalEnum::VAL_INTEGER || type == terminalEnum::VAL_INTEGER || type == terminalEnum::VARIABLE)
        {
            cur++;
        }
        else if (type == terminalEnum::COMMA)
        {
            cur++;
            procE();
        }
        else
        {
            throw parser::ParserException("ArrList");
        }
    }

    // void Parser::procE(){
    //     auto type=(*cur).type;
    //     if(type==terminalEnum::VAL_FLOAT
    // || type==terminalEnum::VAL_INTEGER
    // || type==terminalEnum::VAL_INTEGER
    // || type==terminalEnum::VARIABLE){
    //         cur++;
    //     }else
    //         throw parser::ParserException("E");

    // }

    // void Parser::procReturnLine(){
    //     if((*cur).type==terminalEnum::RETURN){
    //         cur++;
    //         procVarList();
    //         if((*cur).type==terminalEnum::SEMICOLON)
    //             cur++;
    //         else
    //         {
    //             throw parser::ParserException("ReturnLine");
    //         }
    //     }else
    //     {
    //             throw parser::ParserException("ReturnLine");
    //     }
    // }
    void Parser::procE()
    {
        auto type = (*cur).type;
        if (type == terminalEnum::VARIABLE|| type == terminalEnum::VAL_STRING||
        (*cur).type==terminalEnum::VAL_FLOAT||(*cur).type==terminalEnum::VAL_INTEGER){
            cur++;
            return;
        }
        else
        {
            throw parser::ParserException("missing E");
        }
    }
    void Parser::procReturnLine(){
        if((*cur).type == terminalEnum::RETURN){
            cur++;
            if (first_set["var_list"].count((*cur).type))
            {
                procVarList();
                ++cur;
                if ((*cur).type == terminalEnum::SEMICOLON)
                {
                    ++cur;
                    return;
                }
            }
            else
            {
                throw parser::ParserException("missing ReturnLine");
            }
        }
        else
        {
            throw parser::ParserException("missing return");
        }
    }
    void Parser::procDeclarationLine()
    {
        if ((*cur).type == terminalEnum::AUTO)
        {
            ++cur;
            if ((*cur).type == terminalEnum::VARIABLE)
            {
                ++cur;
                if ((*cur).type == terminalEnum::EQUAL)
                {
                    ++cur;
                    if (first_set["F"].count((*cur).type))
                    {
                        procF();
                        return;
                    }
                    else
                        throw parser::ParserException("missing L");
                }
                else
                    throw parser::ParserException("missing =");
            }
            else
                throw parser::ParserException("missing variable");
        }
        else
            throw parser::ParserException("missing auto");
    }
    void Parser::procF(){
        if((*cur).type == terminalEnum::VAL_STRING
           ||(*cur).type==terminalEnum::VAL_FLOAT
           ||(*cur).type==terminalEnum::VAL_INTEGER){
            ++cur;
            return;
        }
        else
            throw parser::ParserException("missing literal");
    }
    void Parser::procRegisterLine()
    {
        if ((*cur).type == terminalEnum::REGISTER)
        {
            ++cur;
            if ((*cur).type == terminalEnum::VAL_STRING)
            {
                ++cur;
                return;
            }
            else
                throw parser::ParserException("missing literal");
        }
        else
            throw parser::ParserException("missing register");
    }
    void Parser::procBreakLine()
    {
        if ((*cur).type == terminalEnum::BREAK)
        {
            ++cur;
            if((*cur).type == terminalEnum::VAL_STRING
            ||(*cur).type==terminalEnum::VAL_FLOAT
            ||(*cur).type==terminalEnum::VAL_INTEGER){
                ++cur;
                return;
            }
            else
                throw parser::ParserException("misson ;");
        }
        else
            throw parser::ParserException("missing break");
    }
    void Parser::procContinueLine()
    {
        if ((*cur).type == terminalEnum::CONTINUE)
        {
            ++cur;
            if ((*cur).type == terminalEnum::SEMICOLON)
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
    void Parser::procIfBlock()
    {
        // proc if( expr ){ S } G
        if ((*cur).type == terminalEnum::IF)
        {
            ++cur;
            if ((*cur).type == terminalEnum::LEFT_PARENTHESES)
            {
                ++cur;
                if (first_set["expr"].count((*cur).type))
                {
                    procExpr();
                    if ((*cur).type == terminalEnum::RIGHT_PARENTHESES)
                    {
                        ++cur;
                        if ((*cur).type == terminalEnum::LEFT_BRACES)
                        {
                            ++cur;
                            if (first_set["S"].count((*cur).type))
                            {
                                procS();
                                if ((*cur).type == terminalEnum::RIGHT_BRACES)
                                {
                                    cur++;
                                    if (first_set["G"].count((*cur).type))
                                    {
                                        procG();
                                        return;
                                    }
                                    else
                                        throw parser::ParserException("missing G");
                                }
                                else
                                    throw parser::ParserException("missing }");
                            }
                            else
                                throw parser::ParserException("missing S");
                        }
                        else
                            throw parser::ParserException("missing {");
                    }
                    else
                        throw parser::ParserException("missing )");
                }
                else
                    throw parser::ParserException("missing expr");
            }
            else
                throw parser::ParserException("missing (");
        }
        else
            throw parser::ParserException("missing if");
    }

    //Writen by BaiTong Zhang
    void Parser::procType()
    {
        auto type = (*cur).type;
        if (type == terminalEnum::INT)
        {
            ++cur;
        }
        else if (type == terminalEnum::FLOAT)
        {
            ++cur;
        }
        else if (type == terminalEnum::BOOL)
        {
            ++cur;
        }
        else if (type == terminalEnum::STRING)
        {
            ++cur;
        }
        else
        {
            throw parser::ParserException("Type");
        }
    }

    void Parser::procBop()
    {
        auto type = (*cur).type;
        if (type == terminalEnum::ADD)
        {
            ++cur;
        }
        else if (type == terminalEnum::SUB)
        {
            ++cur;
        }
        else if (type == terminalEnum::MULTIPLY)
        {
            ++cur;
        }
        else if (type == terminalEnum::DIV)
        {
            ++cur;
        }
        else if (type == terminalEnum::POWER)
        {
            ++cur;
        }
        else if (type == terminalEnum::BIT_AND)
        {
            ++cur;
        }
        else if (type == terminalEnum::BIT_OR)
        {
            ++cur;
        }
        else if (type == terminalEnum::BIT_XOR)
        {
            ++cur;
        }
        else if (type == terminalEnum::LEFT_SHIFT)
        {
            ++cur;
        }
        else if (type == terminalEnum::RIGHT_SHIFT)
        {
            ++cur;
        }
        else if (type == terminalEnum::EQUAL)
        {
            ++cur;
        }
        else if (type == terminalEnum::NOT_EQUAL)
        {
            ++cur;
        }
        else if (type == terminalEnum::LESS)
        {
            ++cur;
        }
        else if (type == terminalEnum::GREATER)
        {
            ++cur;
        }
        else if (type == terminalEnum::LESS_OR_EQUAL)
        {
            ++cur;
        }
        else if (type == terminalEnum::GREATER_OR_EQUAL)
        {
            ++cur;
        }
        else if (type == terminalEnum::LOGICAL_AND)
        {
            ++cur;
        }
        else if (type == terminalEnum::LOGICAL_OR)
        {
            ++cur;
        }
        else if (type == terminalEnum::PTR)
        {
            ++cur;
        }
        else if (type == terminalEnum::ADD_AND_ASSIGN)
        {
            ++cur;
        }
        else if (type == terminalEnum::SUB_AND_ASSIGN)
        {
            ++cur;
        }
        else if (type == terminalEnum::MULTIPLY_AND_ASSIGN)
        {
            ++cur;
        }
        else if (type == terminalEnum::DIV_AND_ASSIGN)
        {
            ++cur;
        }
        else if (type == terminalEnum::POWER_AND_ASSIGN)
        {
            ++cur;
        }
        else if (type == terminalEnum::AND_AND_ASSIGN)
        {
            ++cur;
        }
        else if (type == terminalEnum::OR_AND_ASSIGN)
        {
            ++cur;
        }
        else if (type == terminalEnum::XOR_AND_ASSIGN)
        {
            ++cur;
        }
        else if (type == terminalEnum::LEFT_SHIFT_AND_ASSIGN)
        {
            ++cur;
        }
        else if (type == terminalEnum::RIGHT_SHIFT_AND_ASSIGN)
        {
            ++cur;
        }
        else
        {
            throw parser::ParserException("Type");
        }
    }

    void Parser::procUop()
    {
        auto type = (*cur).type;
        if (type == terminalEnum::DECREASE)
        {
            ++cur;
        }
        else if (type == terminalEnum::INCREMENT)
        {
            ++cur;
        }
        else if (type == terminalEnum::LOGICAL_NOT)
        {
            ++cur;
        }
        else if (type == terminalEnum::BIT_NOT)
        {
            ++cur;
        }
        else
        {
            throw parser::ParserException("Type");
        }
    }

    void Parser::procJ()
    {
        auto type = (*cur).type;
        //type和expr的first集没有重复，可以直接判断
        if (first_set["type"].count(type))
        {
            procType();
            if ((*cur).type == terminalEnum::LEFT_PARENTHESES)
            {
                ++cur;
                procExpr();
            }
            else
            {
                throw parser::ParserException("J");
            }
        }
        else if (first_set["expr"].count(type))
        {
            procExpr();
            if ((*cur).type == terminalEnum::RIGHT_PARENTHESES)
            {
                ++cur;
                return;
            }
            else
            {
                throw parser::ParserException("J");
            }
        }

        else
        {
            throw parser::ParserException("J");
        }
        // if (type == terminalEnum::INT ||
        //     type == terminalEnum::FLOAT ||
        //     type == terminalEnum::BOOL ||
        //     type == terminalEnum::STRING)
        // {
        //     procType();
        //     if ((*cur).type == terminalEnum::LEFT_PARENTHESES)
        //     {
        //         ++cur;
        //         if ((*cur).type == terminalEnum::SEMICOLON)
        //         {
        //             ++cur;
        //             return;
        //         }
        //         else
        //         {
        //             throw parser::ParserException("J");
        //         }
        //     }
        //     else
        //     {
        //         throw parser::ParserException("J");
        //     }
        // }
        // else if (type == terminalEnum::LEFT_BRACES ||
        //          type == terminalEnum::LEFT_PARENTHESES ||
        //          type == terminalEnum::LEFT_SQUARE_BRACKETS ||
        //          type == terminalEnum::VARIABLE ||
        //          // terminalEnum::VAL_INTEGER,
        //          // terminalEnum::VAL_FLOAT,
        //          // terminalEnum::VAL_STRING,
        //          type == terminalEnum::NULLPTR ||
        //          type == terminalEnum::TRUE ||
        //          type == terminalEnum::FALSE ||
        //          type == terminalEnum::BIT_NOT ||
        //          type == terminalEnum::LOGICAL_NOT ||
        //          type == terminalEnum::INCREMENT ||
        //          type == terminalEnum::DECREASE)
        // {
        //     procExpr();
        //     if ((*cur).type == terminalEnum::RIGHT_PARENTHESES)
        //     {
        //         ++cur;
        //         return;
        //     }
        //     else
        //     {
        //         throw parser::ParserException("J");
        //     }
        // }
        // else
        // {
        //     throw parser::ParserException("J");
        // }
    }

    void Parser::procK()
    {
        auto type = (*cur).type;
        //bop和uop的first集没有重复，可以直接判断
        if (first_set["bop"].count(type))
        {
            procBop();
            procExpr();
            procK();
        }
        else if (first_set["uop"].count(type))
        {
            procUop();
            procK();
        }
        else
            return;
    }

    void Parser::procL()
    {
        auto type = (*cur).type;
        if (first_set["plist"].count(type))
        {
            procPlist();
            if ((*cur).type == terminalEnum::RIGHT_PARENTHESES)
            {
                ++cur;
                if ((*cur).type == terminalEnum::SEMICOLON)
                {
                    ++cur;
                    return;
                }
                else
                {
                    throw parser::ParserException("missing ;");
                }
            }
            else
            {
                throw parser::ParserException("missing )");
            }
        }
        else if ((*cur).type == terminalEnum::RIGHT_PARENTHESES)
        {
            ++cur;
            if ((*cur).type == terminalEnum::SEMICOLON)
            {
                ++cur;
                return;
            }
            else
            {
                throw parser::ParserException("missing ;");
            }
        }
        else
        {
            throw parser::ParserException("L");
        }
    }

    void Parser::procPlist()
    {
        auto type = (*cur).type;
        if (first_set["expr"].count(type))
        {
            procExpr();
            procM();
        }
        else
        {
            throw parser::ParserException("Plist");
        }
    }

    void Parser::procM()
    {
        if ((*cur).type == terminalEnum::COMMA)
        {
            ++cur;
            procPlist();
        }
        else
            return;
    }

    void Parser::procExpr()
    {
        auto type = (*cur).type;
        if (type == terminalEnum::LEFT_PARENTHESES)
        {
            ++cur;
            procJ();
            procK();
        }
        else if (first_set["uop"].count(type))
        {
            procUop();
            procExpr();
            procK();
        }
        else if (type == terminalEnum::LEFT_BRACES)
        {
            ++cur;
            procDictList();
            if ((*cur).type == terminalEnum::RIGHT_BRACES)
            {
                ++cur;
                procK();
            }
            else
            {
                throw parser::ParserException("missing }");
            }
        }
        else if (type == terminalEnum::LEFT_SQUARE_BRACKETS)
        {
            ++cur;
            procArrList();
            if ((*cur).type == terminalEnum::RIGHT_SQUARE_BRACKETS)
            {
                ++cur;
                procK();
            }
            else
            {
                throw parser::ParserException("missing ]");
            }
        }

        else if (type == terminalEnum::NULLPTR || type == terminalEnum::TRUE || type == terminalEnum::FALSE || type == terminalEnum::VAL_STRING || terminalEnum::VAL_FLOAT ||
                     terminalEnum::VAL_INTEGER )
        {
            ++cur;
            procK();
        }

        else if (type == terminalEnum::VARIABLE)
        {
            //后看一位判断是var还是fname
            ++cur;

            //如果是 ( 就认为是fname:
            if ((*cur).type == terminalEnum::LEFT_PARENTHESES)
            {
                ++cur;
                procL();
                procK();
            }
            //否则认为是var
            else
            {
                procK();
            }
        }
        else
        {
            throw parser::ParserException("expression error");
        }
    }

    void Parser::procWhileBlock()
    {
        if ((*cur).type == terminalEnum::WHILE)
        {
            ++cur;
            if ((*cur).type == terminalEnum::LEFT_PARENTHESES)
            {
                ++cur;
                procExpr();
                if ((*cur).type == terminalEnum::RIGHT_PARENTHESES)
                {
                    ++cur;
                    if ((*cur).type == terminalEnum::LEFT_BRACES)
                    {
                        ++cur;
                        procS();
                        if ((*cur).type == terminalEnum::RIGHT_BRACES)
                        {
                            ++cur;
                            return;
                        }
                        else
                        {
                            throw parser::ParserException("while missing }");
                        }
                    }
                    else
                    {
                        throw parser::ParserException("while error");
                    }
                }
                else
                {
                    throw parser::ParserException("while missing )");
                }
            }
            else
            {
                throw parser::ParserException("while error");
            }
        }
        else
        {
            throw parser::ParserException("while error");
        }
    }

    void Parser::procH()
    {
        if (first_set["else_if_block"].count((*cur).type))
        {
            procElseIfBlock();
        }
        else
            return;
    }

    void Parser::procElseIfBlock()
    {
        if ((*cur).type == terminalEnum::ELSE)
        {
            ++cur;
            if ((*cur).type == terminalEnum::IF)
            {
                ++cur;
                if ((*cur).type == terminalEnum::LEFT_PARENTHESES)
                {
                    procExpr();
                    if ((*cur).type == terminalEnum::RIGHT_PARENTHESES)
                    {
                        ++cur;
                        if ((*cur).type == terminalEnum::LEFT_BRACES)
                        {
                            ++cur;
                            procS();
                            if ((*cur).type == terminalEnum::RIGHT_BRACES)
                            {
                                ++cur;
                                procH();
                                return;
                            }
                            else
                            {
                                throw parser::ParserException("else if missing }");
                            }
                        }
                        else
                        {
                            throw parser::ParserException("else if error");
                        }
                    }
                    else
                    {
                        throw parser::ParserException("else if missing )");
                    }
                }
                else
                {
                    throw parser::ParserException("Else if error");
                }
            }
            else
            {
                throw parser::ParserException("Else if error");
            }
        }
        else
        {
            throw parser::ParserException("Else if error");
        }
    }

    void Parser::procG()
    {
        //G的两个产生式的first集有冲突，不能通过first来判断。
        //需要试探然后回退
        if ((*cur).type == terminalEnum::ELSE)
        {
            ++cur;
            if ((*cur).type == terminalEnum::LEFT_PARENTHESES)
            {
                ++cur;
                procS();
                if ((*cur).type == terminalEnum::RIGHT_PARENTHESES)
                {
                    ++cur;
                    return;
                }
                else
                {
                    throw parser::ParserException("else missing }");
                }
            }
            else if ((*cur).type == terminalEnum::IF)
            {
                --cur;
                --cur; //回退到else if的开始处
                procElseIfBlock();
            }
            else
            {
                throw parser::ParserException("G error");
            }
        }
        else
            return;
    }

    Parser::Parser(const std::vector<lexical::TokenData> &tokenStream) : tokenStream(tokenStream) {}
} // namespace cnova::parser
