# Gramma Design Doc

## gramma
+ S' -> S
+ S -> sentence | sentence S
+ sentence -> line | block
+ line -> extern_line | calc_line | return_line | declaration_line | register_line | break_line | continue_line
+ block -> if_block | while_block
+ extern_line -> `extern` var_list `;`
+ var_list -> `var` | `var` `,` varlist
+ calc_line -> expr `;` | left_type `=` calc_line
+ expr -> `(`expr`)` | expr `+` expr | expr `-` expr | expr `*` expr | expr `/` expr | expr `**` expr | expr `&` expr | expr `|` expr | expr `^` expr | expr `<<` expr | expr `>>` expr | expr `+` expr | expr `==` expr | expr `!=` expr | expr `<` expr | expr `>` expr | expr `<=` expr | expr `>=` expr | expr `&&` expr | expr `||` expr | expr `->` expr | expr `+=` expr | expr `-=` expr | expr `*=` expr | expr `/=` expr | expr `**=` expr | expr `&=` expr | expr `|=` expr | expr `^=` expr | expr `<<=` expr | expr `>>=` expr | `-` expr | `~` expr | `!` expr | expr `++` | expr `--` | `++` expr | `--` expr | `{`dict_list`}` | `[`arr_list`]` | `var` | `literal` | `nullptr`
+ left_type -> `var` | `var[literal]` | `var[var]`
+ dict_list -> dict_type | `,` dict_type
+ dict_type -> `{var, literal}` | `{var, var}` | `{literal, literal}` | `{literal, var}`
+ arr_list -> `var` | `literal` | `, var` | `, literal`
+ return_line -> `return` var_list `;`
+ declaration_line -> `auto var = var;` | `auto var = literal;`
+ register_line -> `register literal;`
+ break_line -> `break;`
+ continue_line -> `continue;`
+ if_block -> `if(` expr `){` S `}` | `if(` expr `){` S `}`else_if_block | `if(` expr `){` S `}`else_if_block`else{` S `}`
+ else_if_block -> `else if(` expr `){` S `}` | `else if(` expr `){` S `}` else_if_block
+ while_block -> `while(` expr `){` S `}`

## tips
+ `var` means both variable and keyword `this`