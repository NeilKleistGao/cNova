# Grammar Modified Design Doc
—— After eliminating the left common factor and left recursion
## grammar
+ S -> sentence A
+ A -> S| `#`
+ sentence -> line | block
+ line -> extern_line | calc_line | return_line | declaration_line | register_line | break_line | continue_line
+ block -> if_block | while_block
+ extern_line -> `extern` var_list `;`
+ var_list -> `var` B
+ B -> `,` var_list | `#`
+ calc_line -> expr `;` | left_type `=` calc_line
+ left_type ->  `var` C
+ C -> `[literal]` | `[var]` | `#`
+ dict_list -> dict_type | `,` dict_type
+ dict_type -> `{var ,` D | `{literal,` D
+ D -> `literal}`|`var}`
+ arr_list ->  `var` | `literal` |`, `E
+ E -> `var`|`literal`
+ return_line -> `return` var_list `;`
+ declaration_line -> `auto var = ` F
+ F -> `literal;`
+ register_line -> `register literal;`
+ break_line -> `break;`
+ continue_line -> `continue;`
+ if_block -> `if(` expr `){` S `}` G
+ G -> else_if_block | `else{` S `}` |`#`
+ else_if_block -> `else if(` expr `){` S `}` H
+ H -> else_if_block| `#`
+ while_block -> `while(` expr `){` S `}`
+ type -> `int` | `float` | `bool` | `string`
+ expr-> `(`J K| uop expr K | `{`dict_list`}` K | `[`arr_list`]` K | `var` K| `literal` K| `nullptr` K| `true` K| `false` K
+ K -> bop expr K |uop K | `#`
+ J->type`)`expr|expr`)` 
+ bop -> `+`|`-`|`*`|`/`|`**`|`&`|`|`|`^`|`<<`|`>>`|`+`|`==`|`!=`|`<`|`>`|`<=`|`>=`|`&&`|`||`|`->`|`+=`|`-=`|`*=`|`/=`|`**=`|`&=`|`|=`|`^=`|`<<=`|`>>=`
+ uop -> `~`|`!`|`++`|`--`
+ expr -> `fname();` | `fnanem(` plist `);`
+ plist -> expr | expr `,` plist
## tips
+ `var` means both variable and keyword `this`
+ `#` means null