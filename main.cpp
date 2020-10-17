#include <iostream>
#include <iomanip>
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
//打印value值的函数
void printValueToFile(std::list<lecxical::cNova_token>::iterator iterator,std::ofstream& of)
{
    if (iterator->value.type == Novatokendata::FLOAT)
        of <<std::setprecision(PRECISION) << iterator->value.data.float_data;
    else if (iterator->value.type == Novatokendata::INTEGER)
        of << std::setprecision(PRECISION) << iterator->value.data.int_data;
    else if (iterator->value.type == Novatokendata::STRING)
        of << std::setprecision(PRECISION) << iterator->value.data.string_data;
}
int main()
{
    std::string tokenDataTypeList[] = {
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
        "LEFT_PARENTTHESE",      //左小括号
        "RIGHT_PARENTTHESE",     //左小括号
        "LEFT_SQUARE_BRACKETS",  //左中括号
        "RIGHT_SQUARE_BRACKETS", //右中括号
        "LEFT_BRACES",           //左大括号
        "RIGHT_BRACES",          //右大括号
        "COMMA",                 //逗号
        "FULL_STOP",             //句号
        "PTR",
        "COLON",
        "SEMICOLON",
        "KEYWORD",
        "PERCENT",
        "PERCENT_AND_EQUAL"
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
                            "IGNORE"
                            };
    std::list<lecxical::cNova_token> isl;

    std::list<lecxical::cNova_token>::iterator i;

    std::array<std::__cxx11::string, 6> files = {
        "test/single_judge.txt",
        "test/test_keyword.txt",
        "test/test_number.txt",
        "test/test_symbol.txt",
        "test/test_variables.txt",
        "test/test.txt"};
    
    std::ofstream testOut;
    testOut.open("test/outcome.txt");
    for (auto file : files)
    {
        testOut << file << std::endl;
        convert_to_Token(file, isl);
        i = isl.begin();
        testOut << "Total lexeme number: " << isl.size() << std::endl;
        for (; i != isl.end(); ++i)
        {
            testOut << tokenTypeList[i->type] << " " << tokenDataTypeList[i->value.type] << " ";
            printValueToFile(i,testOut);
            testOut << std::endl;
        }
        testOut<<std::endl;
        isl.clear();
    }
    
    //std::list<lecxical::cNova_token> isl;
    //isl.push_back(test());
    //std::cout<<*(isl.begin()->value.data.string_data);


}
