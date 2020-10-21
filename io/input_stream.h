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

#ifndef CNOVA_INPUT_STREAM_H
#define CNOVA_INPUT_STREAM_H

#include <fstream>

namespace cnova::io {
class InputStream
{
public:
    InputStream(const std::string&, const size_t&);
    ~InputStream();

    InputStream(const InputStream&) = delete;
    InputStream& operator= (const InputStream&) = delete;
    InputStream(InputStream&&) = delete;

    inline char getChar() {
        return *_forward;
    }

    inline void hopBegin() {
        _lexemeBegin = _forward;
    }

    char moveNext();
    char moveBack(const size_t& n = 1);
    std::string getLexeme();
private:
    const size_t _SIZE;
    char* _buffer1;
    char* _buffer2;
    char* _lexemeBegin;
    char* _forward;
    char* _current;
    std::ifstream _in;

    bool load();
};

} // namespace cnova::io

#endif
