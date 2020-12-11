#include <iomanip>
#include "../lexical/lexical_converter.h"
#include "../parser/parser.h"
#include "../parser/parser_exceptions.h"

using namespace cnova::lexical;
using namespace cnova::io;
using namespace cnova::parser;
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
void printValue(std::vector<TokenData>::iterator iterator)
{
    if (iterator->type == TokenData::TokenType::VAL_FLOAT)
    {
        std::cout <<std::setprecision(7)<< iterator->data.float_data;
    }
    else if (iterator->type == TokenData::TokenType::VAL_INTEGER)
    {
        std::cout << iterator->data.int_data;
    }
    else if (iterator->type == TokenData::TokenType::VAL_STRING)
    {
        std::cout << iterator->data.string_data;
    }
    else if (iterator->type == TokenData::TokenType::VARIABLE)
    {
        std::cout << iterator->data.string_data;
    }
}
int main(){
    std::string inputFileName = "test_data/parser/input.txt";
    auto lexicalConverter = new LexicalConverter(inputFileName);
    auto lexicalResult = lexicalConverter->parseTokens();
/*    for (auto i = lexicalResult.begin(); i != lexicalResult.end(); ++i)
    {
        std::cout<<TestType::tokenTypeList[i->type] << " ";
        printValue(i);
        std::cout<<"\n";
    }*/
    auto parser = new  Parser(lexicalResult);
    try {
        parser->parserStart();
    } catch (cnova::parser::ParserException e) {
        e.what();
    }
}