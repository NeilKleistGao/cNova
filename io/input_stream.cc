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

#include "input_stream.h"

#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>

namespace cnova::io {

InputStream::InputStream(const std::string& filename, const size_t& size)
    : _SIZE(size), _buffer1(nullptr), _buffer2(nullptr),
    _current(nullptr), _forward(nullptr), _lexemeBegin(nullptr),
    _in(filename, std::ios::in)
{
    _buffer1 = new char[_SIZE];
    _buffer2 = new char[_SIZE];
    _current = _buffer1;
    _lexemeBegin = _buffer1;
    _forward = _buffer1;

    std::memset(_buffer1, 0, sizeof(char) * _SIZE);
    std::memset(_buffer2, 0, sizeof(char) * _SIZE);
    if (!_in.is_open()) {
        //TODO: throw
        std::cout << "failed" << std::endl;
    }
    else {
        load();
    }
}

InputStream::~InputStream()
{
    if (_in.is_open()) {
        _in.close();
    }

    delete[] _buffer1;
    delete[] _buffer2;
    _buffer1 = nullptr;
    _buffer2 = nullptr;
    _forward = nullptr;
    _lexemeBegin = nullptr;
    _current = nullptr;
}

bool InputStream::load() {
    _current = (_current == _buffer1) ? _buffer2 : _buffer1;
    if (!_in.eof()) {
        std::memset(_current, 0, sizeof(char) * _SIZE);
        _in.get(_current, _SIZE, '\0');
        _forward = _current;
        return true;
    }

    return false;
}

char InputStream::moveNext() {
    if ((_forward - _current) < _SIZE) {
        _forward++;
        if (getChar() && (_forward - _current) == _SIZE) {
            if (load()) {
                return getChar();
            }
        }
    }

    return 0;
}

char InputStream::moveBack(const size_t& n) {
    if (_lexemeBegin - _current < _SIZE && _lexemeBegin - _current >= 0) {
        if (_forward - _lexemeBegin < n) {
            _forward = _lexemeBegin;
        }
        else {
            _forward -= n;
        }

        return getChar();
    }
    else {
        if (_forward - _current < n) {
            _in.seekg(-_SIZE, std::ios::cur);
            _forward = (_current == _buffer1) ? _buffer2 + _SIZE - 1 : _buffer1 + _SIZE - 1;
            _current = (_current == _buffer1) ? _buffer2 : _buffer1;
            if (_forward - _lexemeBegin < n) {
                _forward = _lexemeBegin;
            }
            else {
                _forward -= n;
            }
            return getChar();
        }
        else
        {
            _forward -= n;
            return getChar();
        }
    }
}

std::string InputStream::getLexeme() {
    std::string between;
    if (_lexemeBegin - _current < _SIZE && _lexemeBegin - _current >= 0) {
        for (char* i = _lexemeBegin; i <= _forward; i++)
            between += *i;
    }
    else {
        for (char* i = _lexemeBegin; *i != EOF; i++)
            between += *i;
        for (char* i = _current; i <= _forward; i++)
            between += *i;
    }
    return between;
}

} // namespace cnova::io
