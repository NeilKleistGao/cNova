#include <iostream>
#include "cNova_lex.h"
#include "input_stream.h"
using namespace lecxical;
//打印value值的函数
void printValue(std::list<lecxical::cNova_token>::iterator iterator){
    if(iterator->value.type==Novatokendata::FLOAT)
        std::cout<<iterator->value.data.float_data;
    else if(iterator->value.type==Novatokendata::INTEGER)
        std::cout<<iterator->value.data.int_data;
    else if(iterator->value.type==Novatokendata::STRING)
        std::cout<<iterator->value.data.string_data;
}
int main()
{
    std::string tokenDataTypeList[]={
            "INTEGER",
            "FLOAT",
            "STRING",
            "ARRAY",
            "DICTIONARY",
            "POINTER",
            "FUNCTION",
            "LESS",
            "LEFT_SHIFT_AND_ASSIGN",
            "LEFT_SHIFT",
            "LESS_OR_EQUAL",
            "GREATER_OR_EQUAL",
            "GREATER",
            "RIGHT_SHIFT_AND_ASSIGN",
            "RIGHT_SHIFT",
            "ADD",
            "INCREMENT",
            "ADD_AND_ASSIGN",
            "SUB",
            "SUB_AND_ASSIGN",
            "DECREASE",
            "MULT_AND_ASSIGN",
            "POWER_AND_ASSIGN",
            "POWER",
            "MULT",
            "DIV",
            "DIV_AND_ASSIGN",
            "LOGICAL_AND",
            "BIT_AND",
            "AND_AND_ASSIGN",
            "BIT_OR",
            "LOGICAL_OR",
            "OR_AND_ASSIGN",
            "BIT_XOR",
            "XOR_AND_ASSIGN",
            "BIT_NOT",
            "EQUAL",
            "ASSIGN",
            "LOGICAL_NOT",
            "NOT_EQUAL",
            "LEFT_PARENTTHESE",   //左小括号
            "RIGHT_PARENTTHESE",   //左小括号
            "LEFT_SQUARE_BRACKETS",  //左中括号
            "RIGHT_SQUARE_BRACKETS",  //右中括号
            "LEFT_BRACES",			//左大括号
            "RIGHT_BRACES" ,//右大括号
            "COMMA",		  //逗号
            "FULL_STOP",     //句号
            "PTR",
            "COLON",
            "SEMICOLON",
            "KEYWORD"
    };
    std::string tokenTypeList[]={"REGISTER",
                            "EXTERN",
                            "AUTO",
                            "RETURN",
                            "IF",
                            "ELSE",
                            "WHILE",
                            "THIS",
                            "TRUE",
                            "FALSE",
                            "BREAK",
                            "CONTINUE",
                            "INT",
                            "FLOAT",
                            "BOOL",
                            "STRING",
                            "NULLPTR",
                            "VARIABLE",
                            "NOTATION",
                            "LITERATE_STRING",
                            "LITERATE_INT",
                            "LITERATE_FLOAT",
                            "IGNORE"};
    std::list<lecxical::cNova_token> isl;

    convert_to_Token("test/test.txt", isl);
    std::cout<<"Total lexeme number: "<<isl.size()<<std::endl;
    std::list<lecxical::cNova_token>::iterator i;
    i=isl.begin();
    for(;i!=isl.end();++i){
        std::cout<<tokenTypeList[i->type]<<" "<<tokenDataTypeList[i->value.type]<<" ";
        printValue(i);
        std::cout<<std::endl;
    }


    //std::cout<<i->type<<" "<<i->value.type<<" "<<std::endl;



    //std::list<lecxical::cNova_token> isl;
    //isl.push_back(test());
    //std::cout<<*(isl.begin()->value.data.string_data);


}
