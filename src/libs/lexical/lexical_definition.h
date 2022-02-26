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

#ifndef CNOVA_LEXICAL_DEFINITION_H
#define CNOVA_LEXICAL_DEFINITION_H

#include <string>
#include <map>
#include <cstring>
#include <list>
#include <sstream>

#include "../io/input_stream.h"

namespace cnova::lexical{
static constexpr size_t POINTER_SIZE = sizeof(void*);
#if (POINTER_SIZE == 4)
    using nova_int = int;
    using nova_float = float;
    using nova_string = char*;
    using nova_pointer = void*;
#else
    using nova_int = long long;
    using nova_float = double;
    using nova_string = char*;
    using nova_pointer = void*;
#endif

struct TokenData {
    enum TokenType {
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
        VAL_INTEGER,
        VAL_FLOAT,
        VAL_STRING,
        NULLPTR,
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
        MULTIPLY_AND_ASSIGN,
        POWER_AND_ASSIGN,
        POWER,
        MULTIPLY,
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
        LEFT_PARENTHESES,
        RIGHT_PARENTHESES,
        LEFT_SQUARE_BRACKETS,
        RIGHT_SQUARE_BRACKETS,
        LEFT_BRACES,
        RIGHT_BRACES,
        COMMA,
        PTR,
        SEMICOLON,
        VARIABLE,
        MOD,
        MOD_AND_EQUAL,
        FUNCTION,
        ARRAY,
        DICTIONARY,
        REFERENCE
    } type;
    union {
        nova_int int_data;
        nova_float float_data;
        nova_string string_data;
        nova_pointer pointer_data;
    } data;
};

using CNovaData = TokenData;

} // namespace cnova::lexical

#endif // CNOVA_LEXICAL_DEFINITION_H
