#include "parser.h"
namespace cnova::parser
{
    void Parser::parserStart(){
        current_position=tokenStream.begin();
        procS();
    }
    void Parser::procS()
    {
        procSentence();
        procA();
    }

    void Parser::procSentence(){
        //如果当前的符号是line的First集中的元素
        //则执行    procLine();

        //如果当前的符号是block的First集中的元素
        //则执行    procBlock();

        //否则      报错
    }
    void Parser::procA(){
        //如果当前的符号是S的First集中的元素
        //则执行    procS();
       
        //否则      pass
    }
    void Parser::procLine(){

    }
} // namespace cnova::parser
