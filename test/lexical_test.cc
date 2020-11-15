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

void printValue(std::vector<TokenData>::iterator iterator, std::ofstream& of){
    if (iterator->type == TokenData::TokenType::VAL_FLOAT) {
        of << iterator->data.float_data;
    }
    else if (iterator->type == TokenData::TokenType::VAL_INTEGER) {
        of << iterator->data.int_data;
    }
    else if (iterator->type == TokenData::TokenType::VAL_STRING) {
        of << iterator->data.string_data;
    }
}

int main()
{
    std::array<std::string, 5> files = {
            "../test/test_data/lexical/test_keyword.txt",
            "../test/test_data/lexical/test_number.txt",
            "../test/test_data/lexical/test_symbol.txt",
            "../test/test_data/lexical/test_variables.txt",
            "../test/test_data/lexical/test.txt"
    };
    
    std::ofstream testOut;
    testOut.open("outcome.txt");
    for (const auto& file : files)
    {
        testOut << file << std::endl;
        auto converter = new LexicalConverter(file);
        auto list = converter->parseTokens();
        testOut << "Total lexeme number: " << list.size() << std::endl;
        for (auto i = list.begin(); i != list.end(); ++i)
        {
            printValue(i, testOut);
            testOut << std::endl;
        }
        testOut << std::endl;
    }

    testOut.close();

    return 0;
}
