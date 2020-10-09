//
// Created by 云绍轩 on 2020/10/8.
//
// MIT License
//
//        Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
//        to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//        copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
//        copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//        AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#ifndef CNOVA_CNOVA_LEX_H
#define CNOVA_CNOVA_LEX_H

#endif //CNOVA_CNOVA_LEX_H
#include <string>



namespace lecxical{
	static constexpr size_t POINTER_SIZE = sizeof(void*);
#if (POINTER_SIZE == 4)
	using nova_int = int;
    using nova_float = float;
    using nova_string = char*;
    using nova_pointer = void*;
#else
	using nova_int = long long;
	using nova_float = double;
	using nova_string = char*;
	using nova_pointer = void*;
#endif

	const static std::string RESERVED_KEYWORD_STRING[] = {
			"register", "extern", "auto", "return",
			"if", "else", "while", "this", "true",
			"false", "break", "continue", "int",
			"float", "bool", "string", "nullptr"
	};


	struct  Novatokendata{    //This struct is a record of token data info
		enum tokendatatype{   //This enum  is a record of token data type
			INTEGER,
			FLOAT,
			STRING,
			ARRAY,
			DICTIONARY,
			POINTER,
			FUNCTION
		} ;
		union tokendata{        //This union is a record of data
			nova_int int_data;
			nova_float float_data;
			nova_string string_data;
			nova_pointer pointer_data;
		} ;

		tokendatatype type;
		tokendata data;


	};



	typedef  struct  cNova_token{
		enum tokentype{   //This enum is record of token type
			REGISTER,
			EXTERN,
			AUTO,
			RETURN,
			IF,
			ELSE,
			WHILE,
			THIS,
			TRUE,
			FALSE,
			BREAK,
			CONTINUE,
			INT,
			FLOAT,
			BOOL,
			STRING,
			NULLPTR,
			VARIABLE,
			NOTATION,
			LITERATE_STRING,
			LITERATE_INT,
			LITERATE_FLOAT
		} ;

		tokentype type;
		Novatokendata value;


	};




}