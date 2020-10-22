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

#include "lexical_exceptions.h"

namespace cnova::lexical {
UnknownCharacterException::UnknownCharacterException(const char& ch, const int& line) : LineNumberMark(line) {
    _info = &"can't solve character " [ch] ;
    _info += " at " + std::to_string(line);
}

const char* UnknownCharacterException::what() const noexcept {
    return _info.c_str();
}

UnexpectedDotInNumberException::UnexpectedDotInNumberException(const int& line) : LineNumberMark(line) {
    _info = "too many dots in the number expression at " + std::to_string(line);
}

const char* UnexpectedDotInNumberException::what() const noexcept {
    return _info.c_str();
}

UnexpectedEOFException::UnexpectedEOFException() : _info("unexpected eof") {
}

const char* UnexpectedEOFException::what() const noexcept {
    return _info.c_str();
}
} // namespace cnova::lexical