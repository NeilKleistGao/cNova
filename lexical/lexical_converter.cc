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

#include "lexical_converter.h"

namespace cnova::lexical {
const std::map<std::string, TokenData::TokenType> LexicalConverter::KEYWORDS_MAPPING = {
    {"register", TokenData::TokenType::REGISTER},
    {"extern", TokenData::TokenType::EXTERN},
    {"auto", TokenData::TokenType::AUTO},
    {"return", TokenData::TokenType::RETURN},
    {"if", TokenData::TokenType::IF},
    {"else", TokenData::TokenType::ELSE},
    {"while", TokenData::TokenType::WHILE},
    {"this", TokenData::TokenType::THIS},
    {"true", TokenData::TokenType::TRUE},
    {"false", TokenData::TokenType::FALSE},
    {"break", TokenData::TokenType::BREAK},
    {"continue", TokenData::TokenType::CONTINUE},
    {"int", TokenData::TokenType::INT},
    {"float", TokenData::TokenType::FLOAT},
    {"bool", TokenData::TokenType::BOOL},
    {"string", TokenData::TokenType::STRING},
    {"nullptr", TokenData::TokenType::NULLPTR}
};

const std::map<std::string, TokenData::TokenType> LexicalConverter::NOTATIONS_MAPPING = {
    {"<", TokenData::TokenType::LESS},
    {"<<=", TokenData::TokenType::LEFT_SHIFT_AND_ASSIGN},
    {"<<", TokenData::TokenType::LEFT_SHIFT},
    {"<=", TokenData::TokenType::LESS_OR_EQUAL},
    {">=", TokenData::TokenType::GREATER_OR_EQUAL},
    {">", TokenData::TokenType::GREATER},
    {">>=", TokenData::TokenType::RIGHT_SHIFT_AND_ASSIGN},
    {">>", TokenData::TokenType::RIGHT_SHIFT},
    {"+", TokenData::TokenType::ADD},
    {"++", TokenData::TokenType::INCREMENT},
    {"+=", TokenData::TokenType::ADD_AND_ASSIGN},
    {"-", TokenData::TokenType::SUB},
    {"-=", TokenData::TokenType::SUB_AND_ASSIGN},
    {"--", TokenData::TokenType::DECREASE},
    {"*=", TokenData::TokenType::MULTIPLY_AND_ASSIGN},
    {"**=", TokenData::TokenType::POWER_AND_ASSIGN},
    {"**", TokenData::TokenType::POWER},
    {"*", TokenData::TokenType::MULTIPLY},
    {"/", TokenData::TokenType::DIV},
    {"/=", TokenData::TokenType::DIV_AND_ASSIGN},
    {"&&", TokenData::TokenType::LOGICAL_AND},
    {"&", TokenData::TokenType::BIT_AND},
    {"&=", TokenData::TokenType::AND_AND_ASSIGN},
    {"|", TokenData::TokenType::BIT_OR},
    {"||", TokenData::TokenType::LOGICAL_OR},
    {"|=", TokenData::TokenType::OR_AND_ASSIGN},
    {"^", TokenData::TokenType::BIT_XOR},
    {"^=", TokenData::TokenType::XOR_AND_ASSIGN},
    {"~", TokenData::TokenType::BIT_NOT},
    {"==", TokenData::TokenType::EQUAL},
    {"=", TokenData::TokenType::ASSIGN},
    {"!", TokenData::LOGICAL_NOT},
    {"!=", TokenData::TokenType::NOT_EQUAL},
    {"(", TokenData::TokenType::LEFT_PARENTHESES},
    {")", TokenData::TokenType::RIGHT_PARENTHESES},
    {"[", TokenData::TokenType::LEFT_SQUARE_BRACKETS},
    {"]", TokenData::TokenType::RIGHT_SQUARE_BRACKETS},
    {"{", TokenData::TokenType::LEFT_BRACES},
    {"}", TokenData::TokenType::RIGHT_BRACES},
    {",", TokenData::TokenType::COMMA},
    {"->", TokenData::TokenType::PTR},
    {";", TokenData::TokenType::SEMICOLON},
    {"%", TokenData::TokenType::MOD},
    {"%=", TokenData::TokenType::MOD_AND_EQUAL}
};

LexicalConverter::LexicalConverter(const std::string& filename) : _stream(nullptr) {
    _stream = new io::InputStream(filename, BUFF_SIZE);
}

LexicalConverter::~LexicalConverter() {
    delete _stream;
    _stream = nullptr;
}

std::vector<TokenData> LexicalConverter::parseTokens() {
    std::vector<TokenData> tokens;
    while (_stream->getChar()) {
        if (isalpha(_stream->getChar()) || _stream->getChar() == '_') {
            tokens.push_back(parseVariableOrKeyword());
        }
        else if (isdigit(_stream->getChar())) {
            tokens.push_back(parseNumberLiteral());
        }
        else if (_stream->getChar() == '"') {
            tokens.push_back(parseStringLiteral());
        }
        else if (!isblank(_stream->getChar())) {
            tokens.push_back(parseNotations());
        }
        else {
            //TODO: throw
        }

//        _stream->moveNext();
        _stream->hopBegin();
    }

    return tokens;
}

TokenData LexicalConverter::parseVariableOrKeyword() {
    _stream->hopBegin();
    while (true) {
        if (isalnum(_stream->getChar()) || _stream->getChar() == '_') {
            _stream->moveNext();
        }
        else {
            break;
        }
    }

    _stream->moveBack();
    std::string lexemeString = _stream->getLexeme();
    //if it's a keyword
    TokenData result{};
    if (KEYWORDS_MAPPING.find(lexemeString) != KEYWORDS_MAPPING.end()) {
        result.type = KEYWORDS_MAPPING.find(lexemeString)->second;
        result.data.pointer_data = nullptr;
    }
    else {
        result.type = TokenData::TokenType::VARIABLE;
        char *lexemeCString = new char[lexemeString.length() + 1];
        std::strcpy(lexemeCString, lexemeString.c_str());
        result.data.string_data = lexemeCString;
    }

    _stream->hopBegin();
    return result;
}

TokenData LexicalConverter::parseNumberLiteral() {
    
}

TokenData LexicalConverter::parseStringLiteral() {
    _stream->hopBegin();
    _stream->moveNext();
    std::string str;

    bool flag = true;
    while (_stream->getChar() != '"') {
        if (!_stream->getChar()) {
            flag = false;
            break;
        }

        str += _stream->getChar();
        _stream->moveNext();
    }

    if (!flag) {
        //TODO: throw
    }

    TokenData result{};
    result.type = TokenData::TokenType::VAL_STRING;
    result.data.string_data = new char[str.length()];
    std::strcpy(result.data.string_data, str.c_str());
    return result;
}

TokenData LexicalConverter::parseNotations() {
    _stream->hopBegin();
    TokenData result{};

    char ch = _stream->getChar();
    std::string notation;
    while (ch && !isblank(ch) && !isalnum(ch) && ch != '_') {
        notation += ch;
        auto it = NOTATIONS_MAPPING.find(notation);
        if (it != NOTATIONS_MAPPING.end()) {
            result.type = it->second;
            result.data.pointer_data = nullptr;
        }
        else {
            break;
        }

        _stream->moveNext();
        ch = _stream->getChar();
    }

    return result;
}

} // namespace cnova::lexical