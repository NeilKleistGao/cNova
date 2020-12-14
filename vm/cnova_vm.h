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
public:
    CNovaVM();
    ~CNovaVM();

    using nova_int = cnova::lexical::nova_int;
    using nova_float = cnova::lexical::nova_float;
    using nova_string = cnova::lexical::nova_string;
    using nova_pointer = cnova::lexical::nova_pointer;
    using nova_data = cnova::lexical::CNovaData;

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

    template<typename First, typename ...Args>
    void initParam(First first, Args ...args) {

    }

    template<typename Last>
    void initParam(Last p) {
        if (_sym_table.find("this") == _sym_table.end()) {

        }
    }

    inline nova_data& getSymbolData(const std::string& name) {
        return _sym_table[name];
    }
private:
    using symbol_table = std::map<std::string, nova_data>;
    using layer = std::pair<unsigned int, symbol_table::iterator>;
    symbol_table _sym_table;
    std::vector<nova_data> _input;
    std::stack<layer> _layers;
    unsigned int _level;

    inline void eraseSymbol(symbol_table::iterator it) {

        _sym_table.erase(it);
    }

    void eraseData(nova_data& data);
};

} // namespace cnova::vm

#endif //CNOVA_CNOVA_VM_H
