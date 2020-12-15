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

/// @file string_lib.cc

#include "libs.h"

#include <cstring>
#include <functional>

#include "../lexical/lexical_definition.h"

namespace cnova::clib {
    const std::unordered_map<std::string, void*> StringLib::STRING_LIB_LIST = {
            {"strlen", reinterpret_cast<void*>(new std::function<lexical::CNovaData(const lexical::CNovaData&)>{
                +[](const lexical::CNovaData& str) -> lexical::CNovaData {
                lexical::CNovaData data{};
                data.type = lexical::TokenData::VAL_INTEGER;
                data.data.int_data = std::strlen(str.data.string_data);
                return data;
            }})},
            {"strstr", reinterpret_cast<void*>(new std::function<lexical::CNovaData(const lexical::CNovaData&, const lexical::CNovaData&)>{
                +[](const lexical::CNovaData& str, const lexical::CNovaData& sub) -> lexical::CNovaData {
                    lexical::CNovaData data{};
                    data.type = lexical::TokenData::VAL_INTEGER;
                    auto temp = std::strstr(str.data.string_data, sub.data.string_data);
                    if (temp == nullptr) {
                        data.data.int_data = -1;
                    }
                    else {
                        data.data.int_data = (temp - str.data.string_data);
                    }
                    return data;
            }})},
            {"substring", reinterpret_cast<void*>(new std::function<lexical::CNovaData(const lexical::CNovaData&, const lexical::CNovaData&, const lexical::CNovaData&)>{
                +[](const lexical::CNovaData& str, const lexical::CNovaData& start, const lexical::CNovaData& end) -> lexical::CNovaData {
                    lexical::CNovaData data{};
                    data.type = lexical::TokenData::VAL_STRING;
                    data.data.string_data = new char[end.data.int_data - start.data.int_data + 1];
                    for (int i = start.data.int_data; i < end.data.int_data; i++) {
                        data.data.string_data[i - start.data.int_data] = str.data.string_data[i];
                    }

                    data.data.string_data[end.data.int_data - start.data.int_data] = 0;
                    return data;
            }})}
    };
}
