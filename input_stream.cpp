#include <iostream>
#include <fstream>
#include <string>
#include "input_stream.h"
using std::cout;
using std::cin;
using std::endl;


input_stream::input_stream(std::string fileName,int size):SIZE(size)
{
	std::ofstream tempOut;
	tempOut.open(fileName, std::ios::app);
	tempOut << " ";
	tempOut.close();
	in.open(fileName);
	buffer1 = new char[SIZE + 1];
	buffer2 = new char[SIZE + 1];
	current = buffer1;
	lexemeBegin = buffer1;
	forward = buffer1;
	if (!in.is_open())
		cout << "File Reading Failed." << endl;
	/*else if (in.peek() == EOF)
		cout << "The file is empty." << endl;*/
	else
	{
		cout << "Successfully opened the file." << endl;
		in.get(buffer1, SIZE+1, '\0');
		buffer1[SIZE] = EOF;
		buffer2[SIZE] = EOF;
		addEOF();
	}
}

input_stream::~input_stream(void)
{
	if (in.is_open())
		in.close();
	delete[] buffer1;
	delete[] buffer2;
}

bool input_stream::addEOF(void)
{
    //未读到文件结尾
	if (!in.eof())
		return false;
	//已读到文件结尾
	int index;

	for (index = SIZE - 1; index > 0; index--)
	{
		if (current[index] != '\0')
			break;
	}
	//已到buffer结尾
	if (index == SIZE - 1)
	{
		char * another = current == buffer1 ? buffer2 : buffer1;
		another[0] = EOF;
	}
	//整个buffer都是空的
	else if(current[index]=='\0')
	{
		current[index] = EOF;
	}
	else
	{
		current[index + 1] = EOF;
	}
	return true;
}

bool input_stream::load(void)
{
	char * another = current == buffer1 ? buffer2 : buffer1;
	if (!in.is_open())
		cout << "File Reading Failed." << endl;
	else if (!in.eof())
	{
		in.get(another, SIZE+1, '\0');
		current = current == buffer1 ? buffer2 : buffer1;
		forward = current;
		buffer1[SIZE] = EOF;
		buffer2[SIZE] = EOF;
		//读完了
		if (in.eof())
		{
			int index;
			for (index = 0; index <= SIZE; index++)
			{
				if (current[index] == '\0')
					break;
			}
			for (;index < SIZE; index++)
				current[index] = '\0';
		}
		addEOF();
		return true;
	}
	else
		//cout << "File Reading Finished." << endl;
	return false;
}

char input_stream::getChar()
{
	return *forward;
}
char input_stream::getCharAndMove()
{
	return *forward;
	next();
}
//deprecated
char input_stream::peek()
{
	if (*forward != EOF)
	{
		char * temp=forward+1;
		if (*temp == EOF)
		{
			//到达了缓冲区结尾
			if (forward - current == SIZE)
			{
				if (load())
				{
					return *forward;
				}
			}
			//文件阅读完了
			else
			{
				return EOF;
			}
		}
		else
		{
			return *forward;
		}
	}
	else
		return '\0';
}
char input_stream::next()
{
	if (*forward != EOF)
	{
		forward++;
		if (*forward == EOF)
		{
			//到达了缓冲区结尾
			if (forward - current == SIZE)
			{
				if (load())
				{
					return *forward;
				}
			}
			//文件阅读完了
			else
			{
				return EOF;
			}
		}
		else
		{
			return *forward;
		}
	}
	else
		//斟酌到底返回EOF还是统一返回\0
		return EOF;
}
char input_stream::moveBack(int n)
{
	//lexemeBegin和forward在同一个数组中
	if (lexemeBegin - current < SIZE&& lexemeBegin - current>=0)
	{
		if (forward - lexemeBegin < n)
			forward = lexemeBegin;
		else
			forward -= n;
		return *forward;
	}
	//lexemeBegin和forward在不同一个数组中
	else 
	{
		//forward须倒退一个buffer
		if (forward - current < n)
		{
			in.seekg(-(SIZE), std::ios::cur);
			int b = (forward - current);
			n -= (forward - current+1);
			forward = current == buffer1 ? buffer2 + SIZE - 1 : buffer1 + SIZE - 1;
			current = current == buffer1 ? buffer2 : buffer1;
			if (forward - lexemeBegin < n)
				forward = lexemeBegin;
			else
				forward -= n;
			return *forward;
		}
		else
		{
			forward -= n;
			return *forward;
		}
	}
}
//leximeBegin指针跳到下一个词素
void input_stream::hopBegin()
{
	lexemeBegin = forward;
}

std::string input_stream::getLexeme()
{
	std::string between= "";
	//lexemeBegin和forward在同一个数组中
	if (lexemeBegin - current < SIZE&& lexemeBegin - current >= 0)
	{
		for (char * i = lexemeBegin; i <= forward; i++)
			between += *i;
	}
	else
	{
		for (char * i = lexemeBegin; *i != EOF; i++)
			between += *i;
		for (char * i = current; i <= forward; i++)
			between += *i;
	}
	return between;

}
