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

/// @file cnova_interpreter.h

#ifndef CNOVA_CNOVA_INTERPRETER_H
#define CNOVA_CNOVA_INTERPRETER_H

#include "cnova_vm.h"
#include "cnova_self.h"
#include "../parser/parser.h"
#include "../lexical/lexical_converter.h"

namespace cnova::vm {

class CNovaInterpreter {
public:
    using nova_int = CNovaVM::nova_int;
    using nova_float = CNovaVM::nova_float;
    using nova_string = CNovaVM::nova_string;
    using nova_pointer = CNovaVM::nova_pointer;
    using nova_data = CNovaVM::nova_data;

    CNovaInterpreter() : CNovaInterpreter(nullptr, "") {
    }
    explicit CNovaInterpreter(CNovaSelf* parent) : CNovaInterpreter(parent, "") {
    }

    explicit CNovaInterpreter(const std::string& filename) : CNovaInterpreter(nullptr, filename) {
    }

    CNovaInterpreter(CNovaSelf* parent, const std::string& filename)
        : _lex_converter{nullptr},
          _parser{new parser::Parser(_tokens)},
          _parent(parent) {
        if (!filename.empty()) {
            this->load(filename);
        }
    }

    ~CNovaInterpreter();

    CNovaInterpreter(const CNovaInterpreter&) = delete;
    CNovaInterpreter& operator= (const  CNovaInterpreter&) = delete;

    void load(const std::string& filename);

    template<typename ...Args>
    void execute(Args ...args) {
        if (_tokens.empty()) {
            return;
        }
        auto vm = new CNovaVM();
        vm->initParam(args...);
        vm->initThis(_parent);
        _result = _parser->start(vm);

        delete vm;
        vm = nullptr;
    }

    template<typename T>
    inline T getResult() const {
        return reinterpret_cast<T>(_result.data.pointer_data);
    }

    inline nova_int getIntResult() const {
        return _result.data.int_data;
    }

    inline nova_float getFloatResult() const {
        return _result.data.float_data;
    }

    inline nova_string getStringResult() const {
        return _result.data.string_data;
    }

    inline bool getBoolResult() const {
        return _result.data.int_data != 0;
    }

    inline std::vector<nova_data> getArrayResult() const {
        return *reinterpret_cast<std::vector<nova_data>*>(_result.data.pointer_data);
    }

    inline std::map<std::string, nova_data> getDictionaryResult() const {
        return *reinterpret_cast<std::map<std::string, nova_data>*>(_result.data.pointer_data);
    }

private:
    cnova::lexical::LexicalConverter* _lex_converter;
    std::vector<cnova::lexical::TokenData> _tokens;
    cnova::parser::Parser* _parser;
    CNovaSelf* _parent;
    cnova::lexical::CNovaData _result;
};

} // namespace cnova::vm

#endif //CNOVA_CNOVA_INTERPRETER_H
