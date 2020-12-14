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

/// @file cnova_self.h

#ifndef CNOVA_CNOVA_SELF_H
#define CNOVA_CNOVA_SELF_H

#include <map>
#include "../lexical/lexical_definition.h"

namespace cnova::vm {

class CNovaSelf {
public:
    explicit operator std::map<std::string, lexical::CNovaData>&() const {
        return *_table;
    }
private:
    std::map<std::string, lexical::CNovaData>* _table;
protected:
    inline void registerItem(const std::string& name, lexical::nova_pointer* item) {
        if (_table->find(name) != _table->end()) {
            // TODO:
        }

        lexical::CNovaData data;
        data.pointer_data = item;
        (*_table)[name] = data;
    }

    inline void registerItem(const std::string& name, const lexical::nova_int& item) {
        if (_table->find(name) != _table->end()) {
            // TODO:
        }

        lexical::CNovaData data;
        data.int_data = item;
        (*_table)[name] = data;
    }

    inline void registerItem(const std::string& name, const lexical::nova_float& item) {
        if (_table->find(name) != _table->end()) {
            // TODO:
        }

        lexical::CNovaData data;
        data.float_data = item;
        (*_table)[name] = data;
    }

    inline void registerItem(const std::string& name, const lexical::nova_string & item) {
        if (_table->find(name) != _table->end()) {
            // TODO:
        }

        lexical::CNovaData data;
        data.string_data = item;
        (*_table)[name] = data;
    }
};

} // namespace cnova::vm

#endif //CNOVA_CNOVA_SELF_H
