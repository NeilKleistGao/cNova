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

/// @file cnova_vm.cc

#include "cnova_vm.h"

namespace cnova::vm {

CNovaVM::CNovaVM() : _level(0) {

}

CNovaVM::~CNovaVM() {
    _input.clear();
    while (!_layers.empty()) {
        _layers.pop();
    }

    for (auto& p : _sym_table) {
        eraseData(p.second);
    }
    _sym_table.clear();
}

void CNovaVM::initThis(CNovaSelf* self) {
    if (self == nullptr) {
        return;
    }

    for (const auto p: static_cast<std::map<std::string, lexical::CNovaData>>(*self)) {
        _sym_table.insert(p);
    }
}

void CNovaVM::modifySymbol(const std::string& name, const cnova::lexical::CNovaData& data) {
    if (_sym_table.find(name) == _sym_table.end()) {
        _layers.push(std::make_pair(_level, _sym_table.find(name)));
    }

    _sym_table[name] = data;
}

void CNovaVM::exitSubSpace() {
    _level--;
    while (!_layers.empty() && _layers.top().first > _level) {
        auto it = _layers.top();
        _layers.pop();
        eraseSymbol(it.second);
    }
}

void CNovaVM::eraseData(nova_data& data) {
    if (data.type == nova_data::VAL_STRING) {
        delete data.data.string_data;
        data.data.string_data = nullptr;
    }
    else if (data.type == nova_data::ARRAY) {
        auto a = reinterpret_cast<std::vector<nova_data>*>(data.data.pointer_data);
        for (auto& child : *a) {
            eraseData(child);
        }
        a->clear();
        delete a;
        data.data.pointer_data = nullptr;
    }
    else if (data.type == nova_data::DICTIONARY) {
        auto d = reinterpret_cast<std::map<std::string, nova_data>*>(data.data.pointer_data);
        for (auto& child : *d) {
            eraseData(child.second);
        }
        d->clear();
        delete d;
        data.data.pointer_data = nullptr;
    }
}

} // namespace cnova::vm
