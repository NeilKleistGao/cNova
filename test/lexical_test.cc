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

#include <iostream>
#include <iomanip>
#include "../lexical/lexical_converter.h"

using namespace cnova::lexical;
using namespace cnova::io;
namespace TestType
{
    std::string tokenTypeList[] = {"REGISTER",
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
                                   "VAL_INTEGER",
                                   "VAL_FLOAT",
                                   "VAL_STRING",
                                   "NULLPTR",
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
                                   "MULTIPLY_AND_ASSIGN",
                                   "POWER_AND_ASSIGN",
                                   "POWER",
                                   "MULTIPLY",
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
                                   "LEFT_PARENTHESES",
                                   "RIGHT_PARENTHESES",
                                   "LEFT_SQUARE_BRACKETS",
                                   "RIGHT_SQUARE_BRACKETS",
                                   "LEFT_BRACES",
                                   "RIGHT_BRACES",
                                   "COMMA",
                                   "PTR",
                                   "SEMICOLON",
                                   "VARIABLE",
                                   "MOD",
                                   "MOD_AND_EQUAL"};
}
void printValue(std::vector<TokenData>::iterator iterator, std::ofstream &of)
{
    if (iterator->type == TokenData::TokenType::VAL_FLOAT)
    {
        of <<std::setprecision(7)<< iterator->data.float_data;
    }
    else if (iterator->type == TokenData::TokenType::VAL_INTEGER)
    {
        of << iterator->data.int_data;
    }
    else if (iterator->type == TokenData::TokenType::VAL_STRING)
    {
        of << iterator->data.string_data;
    }
    else if (iterator->type == TokenData::TokenType::VARIABLE)
    {
        of << iterator->data.string_data;
    }
}

int main()
{
    std::array<std::string, 5> files = {
        "../test/test_data/lexical/test_keyword.txt",
        "../test/test_data/lexical/test_number.txt", 
        "../test/test_data/lexical/test_string.txt",
        "../test/test_data/lexical/test_symbol.txt",
        "../test/test_data/lexical/test_variables.txt"};

    std::ofstream testOut;
    testOut.open("test/outcome.txt");
    for (const auto &file : files)
    {
        testOut << file << std::endl;
        auto converter = new LexicalConverter(file);
        auto list = converter->parseTokens();
        testOut << "Total lexeme number: " << list.size() << std::endl;
        for (auto i = list.begin(); i != list.end(); ++i)
        {
            testOut << TestType::tokenTypeList[i->type] << " ";
            printValue(i, testOut);
            testOut << std::endl;
        }
        testOut << std::endl;
    }

    testOut.close();

    return 0;
}
