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

/// @file operators.cc

#include "operators.h"

namespace cnova::parser {

vm::nova_data Operators::add(const vm::nova_data& d1, const vm::nova_data& d2) {
    vm::nova_data res{};
    if (d1.type == lexical::TokenData::VAL_INTEGER && d2.type == lexical::TokenData::VAL_INTEGER) {
        res.type = lexical::TokenData::VAL_INTEGER;
        res.data.int_data = d1.data.int_data + d2.data.int_data;
    }
    return res;
}

vm::nova_data Operators::sub(const vm::nova_data& d1, const vm::nova_data& d2) {
    vm::nova_data res{};
    if (d1.type == lexical::TokenData::VAL_INTEGER && d2.type == lexical::TokenData::VAL_INTEGER) {
        res.type = lexical::TokenData::VAL_INTEGER;
        res.data.int_data = d1.data.int_data - d2.data.int_data;
    }
    return res;
}

vm::nova_data Operators::multiply(const vm::nova_data& d1, const vm::nova_data& d2) {
    vm::nova_data res{};
    if (d1.type == lexical::TokenData::VAL_INTEGER && d2.type == lexical::TokenData::VAL_INTEGER) {
        res.type = lexical::TokenData::VAL_INTEGER;
        res.data.int_data = d1.data.int_data * d2.data.int_data;
    }

    return res;
}

vm::nova_data Operators::div(const vm::nova_data& d1, const vm::nova_data& d2) {
    vm::nova_data res{};
    if (d1.type == lexical::TokenData::VAL_INTEGER && d2.type == lexical::TokenData::VAL_INTEGER) {
        res.type = lexical::TokenData::VAL_INTEGER;
        res.data.int_data = d1.data.int_data / d2.data.int_data;
    }

    return res;
}

vm::nova_data Operators::mod(const vm::nova_data& d1, const vm::nova_data& d2) {
    vm::nova_data res{};
    if (d1.type == lexical::TokenData::VAL_INTEGER && d2.type == lexical::TokenData::VAL_INTEGER && d2.data.int_data > 0) {
        res.type = lexical::TokenData::VAL_INTEGER;
        res.data.int_data = d1.data.int_data % d2.data.int_data;
    }

    return res;
}

vm::nova_data Operators::logic_and(const vm::nova_data& d1, const vm::nova_data& d2) {
    vm::nova_data res{};
    // TODO:
    return res;
}

vm::nova_data Operators::logic_or(const vm::nova_data& d1, const vm::nova_data& d2) {
    vm::nova_data res{};
    // TODO:
    return res;
}

vm::nova_data Operators::bit_and(const vm::nova_data& d1, const vm::nova_data& d2) {
    vm::nova_data res{};
    if (d1.type == lexical::TokenData::VAL_INTEGER && d2.type == lexical::TokenData::VAL_INTEGER) {
        res.type = lexical::TokenData::VAL_INTEGER;
        res.data.int_data = d1.data.int_data & d2.data.int_data;
    }

    return res;
}

vm::nova_data Operators::bit_or(const vm::nova_data& d1, const vm::nova_data& d2) {
    vm::nova_data res{};
    // TODO:
    return res;
}

vm::nova_data Operators::equal(const vm::nova_data& d1, const vm::nova_data& d2) {
    vm::nova_data res{};
    if (d1.type == d2.type && d1.data.int_data == d2.data.int_data) {
        res.type = lexical::TokenData::TRUE;
    }
    else {
        res.type = lexical::TokenData::FALSE;
    }

    return res;
}

vm::nova_data Operators::not_equal(const vm::nova_data& d1, const vm::nova_data& d2) {
    vm::nova_data res{};
    // TODO:
    return res;
}

vm::nova_data Operators::right_shift(const vm::nova_data& d1, const vm::nova_data& d2) {
    vm::nova_data res{};
    if (d1.type == lexical::TokenData::VAL_INTEGER && d2.type == lexical::TokenData::VAL_INTEGER) {
        res.type = lexical::TokenData::VAL_INTEGER;
        res.data.int_data = d1.data.int_data >> d2.data.int_data;
    }

    return res;
}

vm::nova_data Operators::assign(const vm::nova_data&, const vm::nova_data& d2) {
    return d2;
}

vm::nova_data Operators::greater(const vm::nova_data& d1, const vm::nova_data& d2) {
    vm::nova_data res{};
    if (d1.type == lexical::TokenData::VAL_INTEGER && d2.type == lexical::TokenData::VAL_INTEGER) {
        res.type = (d1.data.int_data > d2.data.int_data) ? vm::nova_data::TRUE : vm::nova_data::FALSE;
    }

    return res;
}

vm::nova_data Operators::increase(const vm::nova_data& data, const bool& front) {
    vm::nova_data res{};
    if (data.type == lexical::TokenData::VAL_INTEGER) {
        res.type = lexical::TokenData::VAL_INTEGER;
        if (front) {
            res.data.int_data = data.data.int_data + 1;
        }
        else {
            res.data.int_data = data.data.int_data;
        }
    }

    return res;
}

vm::nova_data Operators::minus(const vm::nova_data& data, const bool&) {
    vm::nova_data res{};
    if (data.type == lexical::TokenData::VAL_FLOAT) {
        res.type = lexical::TokenData::VAL_FLOAT;
        res.data.float_data = -data.data.float_data;
    }

    return res;
}

} // namespace cnova::parser