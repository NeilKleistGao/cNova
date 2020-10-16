#pragma once

#include <fstream>

class input_stream
{
private:
	const int SIZE;
	char * buffer1;
	char * buffer2;
	char * lexemeBegin;
	char * forward;
	char * current;
	std::ifstream in;

	//utility funcitons
	bool addEOF();
	bool load();
public:
	input_stream(std::string fileName, int size);
	~input_stream();
	
	input_stream(input_stream &input) = delete;
	//读取当前字符
	char getChar();
	//读取并且forward前进一位
	char getCharAndMove();
	//窥视下一个字符
	//不想写，还没写
	char peek();
	//读取下一个字符
	char next();
	//回溯上n个字符
	//若为-1则表示前移失败
	char moveBack(int n = 1);
	//leximeBegin指针跳到下一个词素
	void hopBegin();
	//获取当前lexemeBegin指针和forward指针之间字符(包含两个指针所指字符)
	std::string getLexeme();
};
