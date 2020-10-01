//
// Created by geray on 2020/10/1.
//

#ifndef CNOVALEX_NOVALEX_H
#define CNOVALEX_NOVALEX_H
#include<string>

static std::string CNova_tokens[]={
        "register","extern","auto","return",
        "if","else","while","this","true",
        "false","break","continue","int",
        "float","bool","string","nullptr"
};
enum RESERVED{
    TK_REGISTER=257,
    TK_EXTERN,
    TK_AUTO,
    TK_RETURN,
    TK_IF,
    TK_ELSE,
    TK_WHILE,
    TK_THIS,
    TK_TRUE,
    TK_FLASE,
    TK_BREAK,
    TK_CONTINUE;
    TK_INT,
    TK_FLOAT,
    TK_BOOL,
    TK_STRING,
    TK_NULLPTR,
};
// 用来描述当前token的信息，可能是整数，浮点数，或者字符串
typedef union {
    float r;
    int i;
    std::string ts;
}Seminfo;
typedef struct Token {
    int token;
    Seminfo  seminfo;
}Token;
//负责从文件中读取、缓存字符，并提供字符的模块
//1. 可以直接全部读入缓冲区
//2. 参照lua的策略，部分读入缓冲区
typedef struct IOmodule {

};
typedef struct CNovaState{
    Token t; // 当前的token
    Token lookahead;
    int linenumber; // 当前的行号
    std::string Buffer; // 暂存的字符
    std::string source;// 分析文件名称实例
}CNovaState;
/* LUA 词法分析器接口
模块初始化
void luaX_init(struct lua_State* L);
词法分析器实例初始化
void luaX_setinput(struct lua_State* L, LexState* ls, Zio* z, struct MBuffer* buffer,
                   struct Dyndata* dyd, TString* source, TString* env);
提前获取下一个token的信息，并暂存
int luaX_lookahead(struct lua_State* L, LexState* ls);
获取下一个token，如果有lookahead暂存的token，就直接获取，否则通过
llex函数获取下一个token
int luaX_next(struct lua_State* L, LexState* ls);
抛出词法分析错误
void luaX_syntaxerror(struct lua_State* L, LexState* ls, const char* error_text);
 address https://manistein.github.io/blog/post/program/let-us-build-a-lua-interpreter/%E6%9E%84%E5%BB%BAlua%E8%A7%A3%E9%87%8A%E5%99%A8part6/
 */
#endif //CNOVALEX_NOVALEX_H
