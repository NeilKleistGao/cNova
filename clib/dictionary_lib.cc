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

/// @file dictionary_lib.cc

#include "libs.h"

#include <functional>
#include <map>

#include "../lexical/lexical_definition.h"
#include "../vm/cnova_vm.h"

namespace cnova::clib {
    const std::unordered_map<std::string, void*> DictionaryLib::DICTIONARY_LIB_LIST = {
            {"find", reinterpret_cast<void*>(new std::function<lexical::CNovaData(const lexical::CNovaData&, const lexical::CNovaData&)>{
                +[](const lexical::CNovaData& dic, const lexical::CNovaData& key) -> lexical::CNovaData {
                    lexical::CNovaData data{};
                    auto map = *reinterpret_cast<cnova::vm::nova_dictionary>(dic.data.pointer_data);
                    data.type = (map.find(key.data.string_data) == map.end()) ? vm::nova_data::FALSE : vm::nova_data::TRUE;
                    return data;
            }})},
    };
}