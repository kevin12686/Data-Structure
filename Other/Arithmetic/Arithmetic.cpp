#include <iostream>
#include <sstream>
using namespace std;
/*
	���h�B�� a017
	���򦡹B��Bstringstring
	
	��J�d�� : "2 + 5 + 6 ( 3 + 2 ) * 6 / 5 % 20"		�`�N�G�������Ů� 
	�����ɫ� Ctrl + Z �M����U Enter 
*/

//-------------------------------------------------------------------------- 
string symbol = "+-*/%";					//�]�w�B��l���v��	(�v���V�j�A�u���v�V��) 
int weight[] = { 1,1,2,2,2 };
int num = symbol.length();
//-------------------------------------------------------------------------- 
int top;
string stack;
char do_stack(string function)				//�B�z���| 	INIT : ��l��  POP : ��X���  PUSH : ��J���  TOP : �Ǧ^��� 	char
{
	if (function == "INIT")					//��l�ư��| 
	{
		top = -1;
	}
	else if (top == -1)	return 0;			//�Ǧ^��=0�A���|�L��� 
	if (function == "POP")					//��X�̤W�h��� 
	{
		return stack[top--];
	}
	else if (function == "TOP")				//�Ǧ^�̤W�h��� 
	{
		return stack[top];
	}
}

char do_stack(string function, char data)	//�B�z���| 
{
	if (function == "PUSH")					//��J��Ʀܰ��|�̤W�h 
	{
		stack[++top] = data;
	}
}
//-------------------------------------------------------------------------- 
int itop;
int istack[999];
int do_istack(string function)				//�B�z���| 	INIT : ��l��  POP : ��X���  PUSH : ��J���  TOP : �Ǧ^��� 	int
{
	if (function == "INIT")					//��l�ư��| 
	{
		itop = -1;
	}
	else if (itop == -1)	return 0;		//�Ǧ^��=0�A���|�L��� 
	if (function == "POP")					//��X�̤W�h��� 
	{
		return istack[itop--];
	}
	else if (function == "TOP")				//�Ǧ^�̤W�h��� 
	{
		return istack[itop];
	}
}

int do_istack(string function, int data)	//�B�z���|
{
	if (function == "PUSH")					//��J��Ʀܰ��|�̤W�h 
	{
		istack[++itop] = data;
	}
}
//-------------------------------------------------------------------------- 
bool is_num(string s)						//�r��Y���B�⤸�A�^��true�F�_�h�A�^��false 
{
	int size = s.length();
	int i;
	for (i = 0; i < size; i++)
	{
		if (s[i]<'0' || s[i]>'9')
		{
			return false;
		}
	}
	return true;
}
//-------------------------------------------------------------------------- 
int priority(char Operator)					//�^�ǹB��l�v��	(�v���V�j�A�u���v�V��) 
{
	int i;
	for (i = 0; i < num; i++)
	{
		if (Operator == symbol[i])
		{
			return weight[i];
		}
	}
	return 0;
}
//-------------------------------------------------------------------------- 
int string_int(string data)					//�^�ǹB��l�v��	(�v���V�j�A�u���v�V��) 
{
	int i;
	istringstream temp(data);
	temp >> i;
	return i;
}
//-------------------------------------------------------------------------- 
string postfix(string data)					//���Ǧ����Ǧ� 
{
	do_stack("INIT");
	istringstream temp(data);
	ostringstream heap;
	while (getline(temp, data, ' '))
	{
		if (is_num(data)) heap << data << " ";
		else
		{
			if (do_stack("TOP") == 0 || data == "(")	do_stack("PUSH", data[0]);
			else if (data == ")")
			{
				while (do_stack("TOP") != '(')
				{
					heap << do_stack("POP") << " ";
				}
				do_stack("POP");
			}
			else
			{
				while (priority(data[0]) <= priority(do_stack("TOP")))
				{
					heap << do_stack("POP") << " ";
				}
				do_stack("PUSH", data[0]);
			}

		}
	}
	while (do_stack("TOP") != 0)
	{
		heap << do_stack("POP") << " ";
	}
	return heap.str();
}
//-------------------------------------------------------------------------- 
int calculate(string data)					//�p�⵲�G 
{
	int A,B;
	istringstream temp(data);
	do_istack("INIT");
	while(getline(temp,data,' '))
	{
		if(is_num(data))	do_istack("PUSH",string_int(data));
		else
		{
			B=do_istack("POP");
			A=do_istack("POP");
			switch(data[0])
			{
				case '+':
					do_istack("PUSH",A+B);
					break;
				case '-':
					do_istack("PUSH",A-B);
					break;
				case '*':
					do_istack("PUSH",A*B);
					break;
				case '/':
					do_istack("PUSH",A/B);
					break;
				case '%':
					do_istack("PUSH",A%B);
					break;
			}
		}
	}
	return do_istack("POP");
}
//-------------------------------------------------------------------------- 
int main()
{
	string data;
	while (getline(cin, data))
	{
		data = postfix(data);
		//cout << data << endl; 		//���Ǧ����Ǧ����� 
		cout << calculate(data) << endl;
	}
	return 0;
}
