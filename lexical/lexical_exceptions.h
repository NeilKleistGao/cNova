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

#ifndef CNOVA_LEXICAL_EXCEPTIONS_H
#define CNOVA_LEXICAL_EXCEPTIONS_H

#include <exception>
#include <string>

namespace cnova::lexical {

class LineNumberMark {
public:
    explicit LineNumberMark(const int& line) : _line(line) {
    }
    ~LineNumberMark() = default;

    inline int getLineNumber() const noexcept {
        return _line;
    }
private:
    int _line;
};

class UnknownCharacterException : public std::exception, public LineNumberMark {
public:
    UnknownCharacterException(const char&, const int&);
    const char* what() const noexcept override;
    ~UnknownCharacterException() override = default;
private:
    std::string _info;
};

class UnexpectedDotInNumberException : public std::exception, public LineNumberMark {
public:
    explicit UnexpectedDotInNumberException(const int&);
    ~UnexpectedDotInNumberException() override = default;
    const char* what() const noexcept override;
private:
    std::string _info;
};

class UnexpectedEOFException : public std::exception {
public:
    UnexpectedEOFException();
    ~UnexpectedEOFException() override = default;
    const char* what() const noexcept override;
private:
    std::string _info;
};

}

#endif //CNOVA_LEXICAL_EXCEPTIONS_H
