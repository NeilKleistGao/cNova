#include <iostream>
#include "cNova_lex.h"
#include <list>
#include "input_stream.h"
using namespace lecxical;


bool judgeAlpha(char c){
	//This function is used for judge whether c is a alpha
	if(((c<=90)&&(c>=65))||((c>=97)&&(c<=122)))
		return true;
	else
		return false;

}
bool judgeNu_Char(char c){
	//This function is used for judge whether c is a number or notation
 		if(((c>=33)&&(c<=64))||((c>=91)&&(c<=96)&&(c!=92)||((c>=123)&&(c<=126))))
 			return true;
		else
			return false;
}
bool judgeEsc(char c){
//This function is used for judge whether c is a escape character
	if(((c>=7)&&(c<=12))||(c==34)||(c==39)||(c==63)||(c==92))
		return true;
	else
		return false;
}



//cNova_token
cNova_token convert1 (input_stream *is){
	int state=0;
	is->hopBegin();
	while (is->getChar()!=EOF){
		switch (state)
		{
			case 0:
				switch (is->getChar())
				{
				case '1':
					case '2':
						case '3':
							case '4':
								case '5':
									case '6':
										case '7':
											case '8':
												case '9':
													case '0':
															state =1;
															is->next();
														break;
				case '<':
					state=4;
					is->next();
					break;
				case '>':
					state=6;
					is->next();

					break;
				case '+':
					state=8;
					is->next();

					break;
				case '-':
					state=9;
					is->next();
					break;
				case '*':
					state=10;
					is->next();
					break;
				case '/':
					state=12;
					is->next();
					break;
				case '&':
					state=14;
					is->next();
					break;
				case '|':
					state=15;
					is->next();
					break;
				case '^':
					state=16;
					is->next();
					break;
				case '~':
					cNova_token c;
					c.type=cNova_token::NOTATION;
					c.value.type=Novatokendata::BIT_NOT;
					is->hopBegin();
					return c;
					break;
				case '=':
					state=17;
					is->next();
					break;
				case '!':
					state=18;
					is->next();
					break;
				case '"':
					state=19;
					is->next();
					break;
				case '{':
					cNova_token c1;
					c1.type=cNova_token::NOTATION;
					c1.value.type=Novatokendata::LEFT_BRACES;
					is->hopBegin();
					return c1;
					break;
				case '}':
					cNova_token c2;
					c2.type=cNova_token::NOTATION;
					c2.value.type=Novatokendata::RIGHT_BRACES;
					is->hopBegin();
					return c2;
					break;
				case '(':
					cNova_token c3;
					c3.type=cNova_token::NOTATION;
					c3.value.type=Novatokendata::LEFT_PARENTTHESE;
					is->hopBegin();
					return c3;
					break;
				case ')':
					cNova_token c4;
					c4.type=cNova_token::NOTATION;
					c4.value.type=Novatokendata::RIGHT_PARENTTHESE;
					is->hopBegin();
					return c4;
					break;
				case '[':
					cNova_token c5;
					c5.type=cNova_token::NOTATION;
					c5.value.type=Novatokendata::LEFT_SQUARE_BRACKETS;
					is->hopBegin();
					return c5;
					break;
				case ']':
					cNova_token c6;
					c6.type=cNova_token::NOTATION;
					c6.value.type=Novatokendata::RIGHT_SQUARE_BRACKETS;
					is->hopBegin();
					return c6;
					break;
				case ',':
					cNova_token c7;
					c7.type=cNova_token::NOTATION;
					c7.value.type=Novatokendata::COMMA;
					is->hopBegin();
					return c7;
					break;
				case '.':
					cNova_token c8;
					c8.type=cNova_token::NOTATION;
					c8.value.type=Novatokendata::FULL_STOP;
					is->hopBegin();
					return c8;
					break;
				case ':':
					cNova_token c9;
					c9.type=cNova_token::NOTATION;
					c9.value.type=Novatokendata::COLON;
					is->hopBegin();
					return c9;

					break;
				case ';':
					cNova_token c10;
					c10.type=cNova_token::NOTATION;
					c10.value.type=Novatokendata::SEMICOLON;
					is->hopBegin();
					return c10;
					break;


				}
				break;
			case 1:
				switch (is->getChar())
				{
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
				case '0':
						state=1;
						is->next();
					break;
				case '.':
					    state=2;
					    is->next();
					break;
				default:
						cNova_token c;

						c.type=cNova_token::INT;
					c.value.type=Novatokendata::INTEGER;
						is->moveBack();
						c.value.data.int_data=std::stoi(is->getLexeme());
 						is->hopBegin();
						return c;
				}
			break;
		case 2:
			switch (is->getChar())
			{
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '0':
				state=3;
				is->next();
				break;
			default:
				cNova_token c;
				c.type=cNova_token::FLOAT;
				c.value.type=Novatokendata::FLOAT;
				is->moveBack();
				c.value.data.float_data=std::stof(is->getLexeme()+"0");
				is->hopBegin();
				return c;


				break;



			}
			break;
		case 3:
			switch (is->getChar())
			{
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '0':
				state=3;
				is->next();
				break;
			default:
				cNova_token c;
				c.type=cNova_token::FLOAT;
				c.value.type=Novatokendata::FLOAT;
				is->moveBack();
				c.value.data.float_data=std::stof(is->getLexeme());
				is->hopBegin();
				return c;
				break;

			}
			break;
		case 4:
			switch (is->getChar())
			{
			case '<':
				state=5;
				is->next();
				break;
			case '=':
				cNova_token c1;
				c1.type=cNova_token::NOTATION;
				c1.value.type=Novatokendata::LESS_OR_EQUAL;
				is->hopBegin();
				return c1;
				break;
			default:
					cNova_token c;
					c.type=cNova_token::NOTATION;
					c.value.type=Novatokendata::LESS;
					is->moveBack();
					is->hopBegin();
					return c;
			}
			break;
		case 5:
			switch (is->getChar())
			{
			case '=':
				cNova_token c;
				c.type=cNova_token::NOTATION;
				c.value.type=Novatokendata::LEFT_SHIFT_AND_ASSIGN;
				is->hopBegin();
				return c;
				break;
			default:
				cNova_token c1;
				c1.type=cNova_token::NOTATION;
				c1.value.type=Novatokendata::LEFT_SHIFT;
				is->moveBack();
				is->hopBegin();
				return c1;
				break;


			}
			break;
		case 6:
			switch (is->getChar())
			{
			case '>':
				state=7;
				is->next();
				break;
			case '=':
				cNova_token c;
				c.type=cNova_token::NOTATION;
				c.value.type=Novatokendata::GREATER_OR_EQUAL;
				is->hopBegin();
				return c;
			break;
			default:
				cNova_token c1;
				c1.type=cNova_token::NOTATION;
				c1.value.type=Novatokendata::GREATER;
				is->hopBegin();
				return c1;


				break;
			}
			break;
		case 7:
			switch (is->getChar())
			{
			case '=':
				cNova_token c;
				c.type=cNova_token::NOTATION;
				c.value.type=Novatokendata::RIGHT_SHIFT_AND_ASSIGN;
				is->hopBegin();
				return c;
				break;
			default:
				cNova_token c1;
				c1.type=cNova_token::NOTATION;
				c1.value.type=Novatokendata::RIGHT_SHIFT;
				is->moveBack();
				is->hopBegin();
				return c1;
				break;
			}
			break;
		case 8:
			switch (is->getChar())
			{
				case '+':
					cNova_token c;
				c.type=cNova_token::NOTATION;
				c.value.type=Novatokendata::INCREMENT;
				is->hopBegin();
				return c;

					break;
				case '=':
					cNova_token c1;
				c1.type=cNova_token::NOTATION;
				c1.value.type=Novatokendata::ADD_AND_ASSIGN;
				is->hopBegin();
				return c1;
					break;
			default:
				cNova_token c2;
				c2.type=cNova_token::NOTATION;
				c2.value.type=Novatokendata::ADD;
				is->moveBack();
				is->hopBegin();
				return c2;
				break;
			}
			break;
		case 9:
			switch (is->getChar())
			{
			case '-':
				cNova_token c;
				c.type=cNova_token::NOTATION;
				c.value.type=Novatokendata::DECREASE;
				is->hopBegin();
				return c;

				break;
			case '=':
				cNova_token c1;
				c1.type=cNova_token::NOTATION;
				c1.value.type=Novatokendata::SUB_AND_ASSIGN;
				is->hopBegin();
				return c1;
				break;
			case '>':
				cNova_token c3;
				c3.type=cNova_token::NOTATION;
				c3.value.type=Novatokendata::POINTER;
				is->hopBegin();
				return c3;
				break;
			default:
				cNova_token c2;
				c2.type=cNova_token::NOTATION;
				c2.value.type=Novatokendata::SUB;
				is->moveBack();
				is->hopBegin();
				return c2;
				break;
			}
			break;
		case 10:
			switch (is->getChar())
			{
			case '*':
					state=11;
					is->next();
				break;
			case '=':
				cNova_token c;
				c.type=cNova_token::NOTATION;
				c.value.type=Novatokendata::MULT_AND_ASSIGN;
				is->hopBegin();
				return c;
				break;
			default:
				cNova_token c1;
				c1.type=cNova_token::NOTATION;
				c1.value.type=Novatokendata::MULT;
				is->moveBack();
				is->hopBegin();
				return c1;

				break;




			}
			break;
		case 11:
			switch (is->getChar())
			{
			case'=':
				cNova_token c;
				c.type=cNova_token::NOTATION;
				c.value.type=Novatokendata::POWER_AND_ASSIGN;
				is->hopBegin();
				return c;
				break;
			default:
				cNova_token c1;
				c1.type=cNova_token::NOTATION;
				c1.value.type=Novatokendata::POWER;
				is->moveBack();
				is->hopBegin();
				return c1;
				break;

			}
			break;
		case 12:
			switch (is->getChar())
			{
			case '/':
				state=13;
				is->next();
				break;
			case '=':
				cNova_token c;
				c.type=cNova_token::NOTATION;
				c.value.type=Novatokendata::DIV_AND_ASSIGN;
				is->hopBegin();
				return c;
				break;
			default:
				cNova_token c1;
				c1.type=cNova_token::NOTATION;
				c1.value.type=Novatokendata::DIV;
				is->hopBegin();
				return c1;
				break;
			}
			break;
		case 13:
				while (is->getChar()!='\n'){
					is->next();
				}
				is->hopBegin();
				cNova_token c;
				c.type=cNova_token::IGNORE;
				return c;
			break;
		case 14:
			switch (is->getChar())
			{
			case '&':
				cNova_token c;
				c.type=cNova_token::NOTATION;
				c.value.type=Novatokendata::LOGICAL_AND;
				is->hopBegin();
				return c;
				break;
			case '=':
				cNova_token c1;
				c1.type=cNova_token::NOTATION;
				c1.value.type=Novatokendata::AND_AND_ASSIGN;
				is->hopBegin();
				return c1;
				break;
			default:
				cNova_token c2;
				c2.type=cNova_token::NOTATION;
				c2.value.type=Novatokendata::BIT_AND;
				is->moveBack();
				is->hopBegin();
				return c2;
				break;
			}
			break;
		case 15:
			switch (is->getChar())
			{
				case '|':
					cNova_token c;
				c.type=cNova_token::NOTATION;
				c.value.type=Novatokendata::LOGICAL_OR;
				is->hopBegin();
				return c;
					break;
			case '=':
				cNova_token c1;
				c1.type=cNova_token::NOTATION;
				c1.value.type=Novatokendata::OR_AND_ASSIGN;
				is->hopBegin();
				return c1;
				break;
			default:
				cNova_token c2;
				c2.type=cNova_token::NOTATION;
				c2.value.type=Novatokendata::BIT_OR;
				is->moveBack();
				is->hopBegin();
				return c2;
				break;
			}
			break;
		case 16:
			switch (is->getChar())
			{
			case '=':
				cNova_token c;
				c.type=cNova_token::NOTATION;
				c.value.type=Novatokendata::XOR_AND_ASSIGN;
				is->hopBegin();
				return c;
				break;
			default:
				cNova_token c1;
				c1.type=cNova_token::NOTATION;
				c1.value.type=Novatokendata::BIT_XOR;
				is->hopBegin();
				return c1;
				break;
			}
			break;
		case 17:
			switch (is->getChar())
			{
			case '=':
				cNova_token c1;
				c1.type=cNova_token::NOTATION;
				c1.value.type=Novatokendata::EQUAL;
				is->hopBegin();
				return c1;
				break;
			default:
				cNova_token c;
				c.type=cNova_token::NOTATION;
				c.value.type=Novatokendata::ASSIGN;
				is->moveBack();
				is->hopBegin();
				return c;
				break;

			}
			break;
		case 18:
			switch (is->getChar())
			{
			case '=':
				cNova_token c;
				c.type=cNova_token::NOTATION;
				c.value.type=Novatokendata::NOT_EQUAL;
				is->moveBack();
				is->hopBegin();
				return c;
				break;
			default:
				cNova_token c1;
				c1.type=cNova_token::NOTATION;
				c1.value.type=Novatokendata::LOGICAL_NOT;
				is->moveBack();
				is->hopBegin();
				return c1;
				break;
			}
			break;
		case 19:
			char* ptmp = (char *)malloc(400);
			switch (is->getChar())
			{
			case '"':
				cNova_token c;
				c.type=cNova_token::STRING;
				c.value.type=Novatokendata::STRING;
				std::cout<<is->getLexeme().c_str()<<std::endl;
				memcpy(ptmp,is->getLexeme().c_str(),strlen(is->getLexeme().c_str()));
				c.value.data.string_data = ptmp;
				is->hopBegin();
				return c;
				break;
			default:
				is->next();
				break;
			}


			break;
		}

	}



}





void convert_to_Token(std::string filename,std::list<lecxical::cNova_token> &isl){
	input_stream *is=new input_stream(filename,1024);
	while (is->getChar()!=EOF){

		if(judgeAlpha(is->getChar())){
			//如果是字母,要将token加入isl
			is->next();
			is->hopBegin();
		}else if(judgeNu_Char(is->getChar())){
			//如果是字符+数字，要将token加入isl
			auto temp=convert1(is);
			if(temp.type!=cNova_token::IGNORE){
			//	std::cout<<temp.type;
					isl.push_back(temp);
			}
			is->next();
			is->hopBegin();
		}else if(judgeEsc(is->getChar())){
			//如果是转义符号
		//	std::cout<<is->getChar();
			is->next();
			is->hopBegin();
		}else if(is->getChar()==' '){
		//	std::cout<<is->getChar();
			is->next();
			is->hopBegin();
		}
		else{
			//出现其他+中文
//			std::cout<<is->getChar();
//			std::cout<<"出现不明字符串";
			is->next();
			is->hopBegin();
		}

	}

}
int main()
{
	std::list<lecxical::cNova_token> isl;

     convert_to_Token("test.cpp",isl);
     std::cout<<isl.size();
     std::list<lecxical::cNova_token>::iterator i;
     i=isl.begin();
     for(;i!=isl.end();++i){
     	std::cout<<i->type<<" "<<i->value.type<<" "<<std::endl;
}


	//std::cout<<i->type<<" "<<i->value.type<<" "<<std::endl;



	//std::list<lecxical::cNova_token> isl;
	//isl.push_back(test());
	//std::cout<<*(isl.begin()->value.data.string_data);


}
