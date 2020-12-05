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

    void Parser::parserStart(){
        cur=tokenStream.begin();
        procS();
    }
    void Parser::procS()
    {
        procSentence();
        procA();
    }

    void Parser::procSentence(){
        //如果当前的符号是line的First集中的元素
        //则执行    procLine();

        //如果当前的符号是block的First集中的元素
        //则执行    procBlock();

        //否则      报错
        auto type=(*cur).type;
        if(type==terminalEnum::EXTERN||type==terminalEnum::BIT_NOT||
        type==terminalEnum::LOGICAL_NOT||type==terminalEnum::INCREMENT||
        type==terminalEnum::DECREASE||type==terminalEnum::LEFT_PARENTHESES||
        type==terminalEnum::LEFT_SQUARE_BRACKETS||type==terminalEnum::LEFT_BRACES||
        type==terminalEnum::VARIABLE||type==terminalEnum::VAL_STRING||
        type==terminalEnum::NULLPTR||type==terminalEnum::TRUE||type==terminalEnum::FALSE||
        type==terminalEnum::RETURN||type==terminalEnum::AUTO||type==terminalEnum::REGISTER||
        type==terminalEnum::BREAK||type==terminalEnum::CONTINUE)
        {
            procLine();
        }
        else if(type==terminalEnum::IF||type==terminalEnum::WHILE)
        {
            procBlock();
        }
        else
        {
            throw parser::ParserException("sentence");
        }
        return;
    }
    void Parser::procA(){
        //如果当前的符号是S的First集中的元素
        //则执行    procS();
       
        //否则      pass
        auto type=(*cur).type;
        if(type==terminalEnum::EXTERN||type==terminalEnum::BIT_NOT||
        type==terminalEnum::LOGICAL_NOT||type==terminalEnum::INCREMENT||
        type==terminalEnum::DECREASE||type==terminalEnum::LEFT_PARENTHESES||
        type==terminalEnum::LEFT_SQUARE_BRACKETS||type==terminalEnum::LEFT_BRACES||
        type==terminalEnum::VARIABLE||type==terminalEnum::VAL_STRING||
        type==terminalEnum::NULLPTR||type==terminalEnum::TRUE||type==terminalEnum::FALSE||
        type==terminalEnum::RETURN||type==terminalEnum::AUTO||type==terminalEnum::REGISTER||
        type==terminalEnum::BREAK||type==terminalEnum::CONTINUE||type==terminalEnum::IF||
        type==terminalEnum::WHILE)
        {
            procS();
        }
        return;
    }
    void Parser::procLine(){
        //if *cur in first(extern_line)
        //procExtern_line()
        //if *cur in first(calc_line)
        //procCalc_line()
        //...
        //else error()
        auto type=(*cur).type;
        if(type==terminalEnum::EXTERN)
        {
            procExternLine();
        }
        else if(type==terminalEnum::BIT_NOT||
        type==terminalEnum::LOGICAL_NOT||type==terminalEnum::INCREMENT||
        type==terminalEnum::DECREASE||type==terminalEnum::LEFT_PARENTHESES||
        type==terminalEnum::LEFT_SQUARE_BRACKETS||type==terminalEnum::LEFT_BRACES||
        type==terminalEnum::VARIABLE||type==terminalEnum::VAL_STRING||
        type==terminalEnum::NULLPTR||type==terminalEnum::TRUE||type==terminalEnum::FALSE)
        {  
            procCalLine();
        }
        else if(type==terminalEnum::RETURN)
        {
            procReturnLine();
        }
        else if(type==terminalEnum::AUTO)
        {
            procDeclarationLine();
        }
        else if(type==terminalEnum::REGISTER)
        {
            procRegisterLine();
        }
        else if(type==terminalEnum::BREAK)
        {   
            procBreakLine();
        }
        else if(type==terminalEnum::CONTINUE)
        { 
            procContinueLine();
        }
        else
        {
            throw parser::ParserException("line");
        }
        return;
    }
    void Parser::procBlock(){
        auto type=(*cur).type;
        if(type==terminalEnum::IF)
        {
            procIfBlock();
        }
        else if(type==terminalEnum::WHILE)
        {
            procWhileBlock();
        }
        else
        {
            throw parser::ParserException("bolck");
        }   
    }
    void Parser::procExternLine(){
        if((*cur).type==terminalEnum::EXTERN)
        {
            cur++;
            procVarList();
            if((*cur).type==terminalEnum::SEMICOLON)
            {
                return;
            }
        }
        throw parser::ParserException("extern_line");
    }
    void Parser::procVarList()
    {
        if((*cur).type==terminalEnum::VARIABLE)
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
    void Parser::procB(){
        if((*cur).type==terminalEnum::COMMA)
        {
            cur++;
            procVarList();
        }
        return;
    }
} // namespace cnova::parser
