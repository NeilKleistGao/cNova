/** MIT License
 * Copyright (c) 2020 NeilKleistGao
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/// @file cnova_vm.h

#ifndef CNOVA_CNOVA_VM_H
#define CNOVA_CNOVA_VM_H

#include <map>
#include <stack>
#include <vector>

#include "../lexical/lexical_definition.h"
#include "cnova_self.h"

namespace cnova::vm {

class CNovaVM {
private:
    using iterator = std::vector<lexical::TokenData>::iterator;
public:
    CNovaVM();
    ~CNovaVM();

    CNovaVM(const CNovaVM&) = delete;
    CNovaVM& operator= (const CNovaVM&) = delete;

    void initThis(CNovaSelf*);

    inline void clearInitParam() {
        _input.clear();
    }

    void modifySymbol(const std::string& name, const cnova::lexical::CNovaData& data);

    inline void enterSubSpace() {
        _level++;
    }

    void exitSubSpace();

    template<typename ...Args>
    void initParam(nova_int first, Args ...args) {
        auto data = nova_data{};
        data.data.int_data = first;
        data.type = lexical::TokenData::VAL_INTEGER;
        _input.push_back(data);
        initParam(args...);
    }

    template<typename ...Args>
    void initParam(nova_float first, Args ...args) {
        auto data = nova_data{};
        data.data.float_data = first;
        data.type = lexical::TokenData::VAL_FLOAT;
        _input.push_back(data);
        initParam(args...);
    }

    template<typename ...Args>
    void initParam(nova_string first, Args ...args) {
        auto data = nova_data{};
        data.data.string_data = first;
        data.type = lexical::TokenData::VAL_STRING;
        _input.push_back(data);
        initParam(args...);
    }

    template<typename ...Args>
    void initParam(nova_array first, Args ...args) {
        auto data = nova_data{};
        data.data.pointer_data = first;
        data.type = lexical::TokenData::ARRAY;
        _input.push_back(data);
        initParam(args...);
    }

    template<typename ...Args>
    void initParam(nova_dictionary first, Args ...args) {
        auto data = nova_data{};
        data.data.pointer_data = first;
        data.type = lexical::TokenData::DICTIONARY;
        _input.push_back(data);
        initParam(args...);
    }

    template<typename ...Args>
    void initParam(nova_pointer first, Args ...args) {
        auto data = nova_data{};
        data.data.pointer_data = first;
        data.type = lexical::TokenData::FUNCTION;
        _input.push_back(data);
        initParam(args...);
    }

    inline void initParam(nova_int i) {
        auto data = nova_data{};
        data.data.int_data = i;
        data.type = lexical::TokenData::VAL_INTEGER;

        _input.push_back(data);
    }

    inline void initParam(nova_float f) {
        auto data = nova_data{};
        data.data.float_data = f;
        data.type = lexical::TokenData::VAL_FLOAT;

        _input.push_back(data);
    }

    inline void initParam(nova_string s) {
        auto data = nova_data{};
        data.data.string_data = s;
        data.type = lexical::TokenData::VAL_STRING;

        _input.push_back(data);
    }

    inline void initParam(nova_array a) {
        auto data = nova_data{};
        data.data.pointer_data = a;
        data.type = lexical::TokenData::ARRAY;

        _input.push_back(data);
    }

    inline void initParam(nova_dictionary d) {
        auto data = nova_data{};
        data.data.pointer_data = d;
        data.type = lexical::TokenData::DICTIONARY;

        _input.push_back(data);
    }

    inline void initParam(nova_pointer p) {
        auto data = nova_data{};
        data.data.pointer_data = p;
        data.type = lexical::TokenData::FUNCTION;

        _input.push_back(data);
    }

    inline nova_data& getSymbolData(const std::string& name) {
        return _sym_table[name];
    }

    void addInputToSymbolTable(const std::string& name);

    void registerSTLLib(const std::string& name);

    void pushLoop(iterator next, iterator check);

    iterator popLoop();

    inline bool isInLoop(iterator entry) {
        return (!_check.empty() && _check.top() == entry);
    }

    inline bool isInALoop() {
        return !_check.empty();
    }
private:
    using symbol_table = std::map<std::string, nova_data>;
    using layer = std::pair<unsigned int, symbol_table::iterator>;
    symbol_table _sym_table;
    std::vector<nova_data> _input;
    std::stack<layer> _layers;
    std::stack<iterator> _next, _check;
    unsigned int _level;

    inline void eraseSymbol(symbol_table::iterator it) {

        _sym_table.erase(it);
    }

    void eraseData(nova_data& data);
};

} // namespace cnova::vm

#endif //CNOVA_CNOVA_VM_H
