//
// Created by 云绍轩 on 2020/10/8.
//
// MIT License
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
#ifndef CNOVA_CNOVA_LEX_H
#define CNOVA_CNOVA_LEX_H

#endif //CNOVA_CNOVA_LEX_H

#include <string>
#include <map>
#include <cstring>
#include <list>
#include "input_stream.h"
#include <sstream>

namespace lecxical{
    static constexpr size_t POINTER_SIZE = sizeof(void*);
#if (POINTER_SIZE == 4)
    using nova_int = int;
    using nova_float = float;
    using nova_string = char*;
    using nova_pointer = void*;
    static constexpr size_t PRECISION = 7;
#else
    using nova_int = long long;
    using nova_float = double;
    using nova_string = char *;
    using nova_pointer = void*;
    static constexpr size_t PRECISION = 15;
#endif

    const static std::string RESERVED_KEYWORD_STRING[] = {
            "register", "extern", "auto", "return",
            "if", "else", "while", "this", "true",
            "false", "break", "continue", "int",
            "float", "bool", "string", "nullptr"
    };


    struct  Novatokendata{    //This struct is a record of token data info

        enum tokendatatype{   //This enum  is a record of token data type
            INTEGER,
            FLOAT,
            STRING,
            ARRAY,
            DICTIONARY,
            POINTER,
            FUNCTION,
            LESS,
            LEFT_SHIFT_AND_ASSIGN,
            LEFT_SHIFT,
            LESS_OR_EQUAL,
            GREATER_OR_EQUAL,
            GREATER,
            RIGHT_SHIFT_AND_ASSIGN,
            RIGHT_SHIFT,
            ADD,
            INCREMENT,
            ADD_AND_ASSIGN,
            SUB,
            SUB_AND_ASSIGN,
            DECREASE,
            MULT_AND_ASSIGN,
            POWER_AND_ASSIGN,
            POWER,
            MULT,
            DIV,
            DIV_AND_ASSIGN,
            LOGICAL_AND,
            BIT_AND,
            AND_AND_ASSIGN,
            BIT_OR,
            LOGICAL_OR,
            OR_AND_ASSIGN,
            BIT_XOR,
            XOR_AND_ASSIGN,
            BIT_NOT,
            EQUAL,
            ASSIGN,
            LOGICAL_NOT,
            NOT_EQUAL,
            LEFT_PARENTTHESE,   //左小括号
            RIGHT_PARENTTHESE,   //左小括号
            LEFT_SQUARE_BRACKETS,  //左中括号
            RIGHT_SQUARE_BRACKETS,  //右中括号
            LEFT_BRACES,			//左大括号
            RIGHT_BRACES ,//右大括号
            COMMA,		  //逗号
            FULL_STOP,     //句号
            PTR,
            COLON,
            SEMICOLON,
            KEYWORD,
            PERCENT,
            PERCENT_AND_EQUAL
            //关键字，表明了就无需加值了

        } ;
        union tokendata{        //This union is a record of data
            nova_int int_data;
            nova_float float_data;
            nova_string string_data;
            nova_pointer pointer_data;
        } ;
        tokendatatype type;
        tokendata data;
    };


    typedef  struct  {


        enum tokentype{   //This enum is record of token type
            REGISTER,
            EXTERN,
            AUTO,
            RETURN,
            IF,
            ELSE,
            WHILE,
            THIS,
            TRUE,
            FALSE,
            BREAK,
            CONTINUE,
            INT,
            FLOAT,
            BOOL,
            STRING,
            NULLPTR,
            VARIABLE,
            NOTATION,
            LITERATE_STRING,
            LITERATE_INT,
            LITERATE_FLOAT,
            IGNORE
        } ;

        tokentype type;
        Novatokendata value;

    }cNova_token;


    const static std::map<std::string,cNova_token::tokentype> KEYWORD_MAP= {
            {"register", cNova_token::tokentype::REGISTER},
            {"extern",   cNova_token::tokentype::EXTERN},
            {"auto",     cNova_token::tokentype::AUTO},
            {"return",   cNova_token::tokentype::RETURN},
            {"if",       cNova_token::tokentype::IF},
            {"else",     cNova_token::tokentype::ELSE},
            {"while",    cNova_token::tokentype::WHILE},
            {"this",     cNova_token::tokentype::THIS},
            {"true",     cNova_token::tokentype::TRUE},
            {"false",    cNova_token::tokentype::FALSE},
            {"break",    cNova_token::tokentype::BREAK},
            {"continue", cNova_token::tokentype::CONTINUE},
            {"int",      cNova_token::tokentype::INT},
            {"float",    cNova_token::tokentype::FLOAT},
            {"bool",     cNova_token::tokentype::BOOL},
            {"string",   cNova_token::tokentype::STRING},
            {"nullptr",  cNova_token::tokentype::NULLPTR}

    };


    bool judgeNu_Char(char c);
    bool judgeEsc(char c);
    cNova_token convert1 (input_stream *is);
    cNova_token variableAndKeyword(input_stream * is);
    void convert_to_Token(std::string filename,std::list<lecxical::cNova_token> &isl);


}
