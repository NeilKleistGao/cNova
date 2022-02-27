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

/// @file math_lib.cc

#include "libs.h"

#include <cmath>
#include <functional>

#include "../lexical/lexical_definition.h"
#include "../vm/cnova_vm.h"

namespace cnova::clib {
const std::unordered_map<std::string, void*> MathLib::MATH_LIB_LIST = {
        {"cos", reinterpret_cast<void*>(new std::function<lexical::CNovaData(const lexical::CNovaData&)>{
            +[](const lexical::CNovaData& theta) -> lexical::CNovaData {
                lexical::CNovaData data{};
                data.type = vm::nova_data::VAL_FLOAT;
                data.data.float_data = std::cos(theta.data.float_data);
                return data;
        }})},
        {"sin", reinterpret_cast<void*>(new std::function<lexical::CNovaData(const lexical::CNovaData&)>{
            +[](const lexical::CNovaData& theta) -> lexical::CNovaData {
                lexical::CNovaData data{};
                data.type = vm::nova_data::VAL_FLOAT;
                data.data.float_data = std::sin(theta.data.float_data);
                return data;
        }})},
};

} // namespace cnova::clib