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

/// @file operators.h

#ifndef CNOVA_OPERATORS_H
#define CNOVA_OPERATORS_H

#include <functional>

#include "../vm/cnova_vm.h"

namespace cnova::parser {

class Operators {
public:
    using uop_func = std::function<vm::nova_data(const vm::nova_data&, const bool&)>;
    using bop_func = std::function<vm::nova_data(const vm::nova_data&, const vm::nova_data&)>;

    inline static bool isExpressionFalse(const lexical::CNovaData& data) {
        return data.type == lexical::TokenData::FALSE ||
               data.type == lexical::TokenData::NULLPTR ||
               (data.type == lexical::TokenData::VAL_INTEGER && data.data.int_data == 0) ||
               (data.type == lexical::TokenData::VAL_FLOAT && data.data.float_data == 0.0) ||
               (data.type == lexical::TokenData::VAL_STRING && std::strlen(data.data.string_data) == 0);
    }

    static vm::nova_data add(const vm::nova_data&, const vm::nova_data&);
    static vm::nova_data sub(const vm::nova_data&, const vm::nova_data&);
    static vm::nova_data multiply(const vm::nova_data&, const vm::nova_data&);
    static vm::nova_data div(const vm::nova_data&, const vm::nova_data&);
    static vm::nova_data mod(const vm::nova_data&, const vm::nova_data&);
    static vm::nova_data logic_and(const vm::nova_data&, const vm::nova_data&);
    static vm::nova_data logic_or(const vm::nova_data&, const vm::nova_data&);
    static vm::nova_data bit_and(const vm::nova_data&, const vm::nova_data&);
    static vm::nova_data bit_or(const vm::nova_data&, const vm::nova_data&);
    static vm::nova_data equal(const vm::nova_data&, const vm::nova_data&);
    static vm::nova_data not_equal(const vm::nova_data&, const vm::nova_data&);
    static vm::nova_data right_shift(const vm::nova_data&, const vm::nova_data&);
    static vm::nova_data assign(const vm::nova_data&, const vm::nova_data&);
    static vm::nova_data greater(const vm::nova_data&, const vm::nova_data&);
    static vm::nova_data increase(const vm::nova_data&, const bool&);
    static vm::nova_data minus(const vm::nova_data&, const bool&);
};

} // namespace cnova::parser

#endif //CNOVA_OPERATORS_H
