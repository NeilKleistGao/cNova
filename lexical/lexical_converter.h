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

#ifndef CNOVA_LEXICAL_CONVERTER_H
#define CNOVA_LEXICAL_CONVERTER_H

#include <vector>
#include <map>

#include "lexical_definition.h"
#include "../io/input_stream.h"

namespace cnova::lexical {
class LexicalConverter {
public:
    explicit LexicalConverter(const std::string&);
    ~LexicalConverter();

    LexicalConverter(const LexicalConverter&) = delete;
    LexicalConverter& operator= (const LexicalConverter&) = delete;

    std::vector<TokenData> parseTokens();
private:
    io::InputStream* _stream;

    static constexpr size_t BUFF_SIZE = 256;
    static const std::map<std::string, TokenData::TokenType> KEYWORDS_MAPPING;
    static const std::map<std::string, TokenData::TokenType> NOTATIONS_MAPPING;

    TokenData parseVariableOrKeyword();
    TokenData parseNumberLiteral();
    TokenData parseStringLiteral();
    TokenData parseNotations();
};

} // namespace cnova::lexical

#endif //CNOVA_LEXICAL_CONVERTER_H
