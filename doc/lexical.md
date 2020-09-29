# Lexical Design Doc

## keywords
+ `register`
+ `extern`
+ `auto`
+ `return`
+ `if`
+ `else`
+ `while`
+ `this`
+ `true`
+ `false`
+ `break`
+ `continue`
+ `int`
+ `float`
+ `bool`
+ `string`
+ `nullptr`

## data type
| name | example | data type in C++ |
| --- | --- | --- |
| int | 12 | int |
| float | 3.14 | float |
| string | "abc" | char* |
| bool | true | bool |
| array | [1, 2, 3] | CNovaObject[] |
| dictionary | {} | map<string, CNobaObject>* |
| pointer | this | void* |
| function | abs() | void* |
| null | null | nullptr |

## operator
| name | operator | example |
| --- | --- | --- |
| add | + | `x = 5 + 3;` |
| sub | - | `x = 4 - 1` |
| mult | * | `x = 3 * 2` |
| div | / | `x = 5 / 2` |
| power | ** | `x = 3**2` |
| bit and | & | `5 & 1` |
| bit or | \| | `x|y` |
| bit xor | ^ | `3^4` |
| bit not | ~ | `~444` |
| left shift | << | `10 << 2` |
| right shift | >> | `10 >> 2` |
| comment | /**/ | `/*hello*/` |
| assign | = | `x = 5;` |
| equal | == | `x == y` |
| not equal | != | `x != y` |
| less | < | `x < y` |
| less or equal | <= | `x <= y` |
| greater | > | `x > y` |
| greater or equal | >= | `x >= y` |
| logical and | && | `x && y` |
| logical or | \|\| | `x || y` |
| logical not | ! | `!x` |
| setter&getter | [] | `arr[0]` |
| access | -> | `this->foo` |
| add and assign | += | `a += 2` |
| sub and assign | -= | `a -= 2` |
| mult and assign | *= | `a *= 2` |
| div and assign | /= | `a /= 2` |
| and and assign | &= | `a &= 2` |
| or and assign | |= | `a |= 2` |
| xor and assign | ^= | `a ^= 2` |
| power and assign | **= | `a **= 2` |
| left shift and assign | <<= | `a <<= 2` |
| right shift and assign | >>= | `a >>= 2` |

## variable name and function name
begin with an alpha or an underline and it can include alphanumeric and underline.