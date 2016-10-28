#include <iostream>
#include <sstream>
using namespace std;
/*
	五則運算 a017
	後續式運算、stringstring
	
	輸入範例 : "2 + 5 + 6 ( 3 + 2 ) * 6 / 5 % 20"		注意：中間有空格 
	結束時按 Ctrl + Z 然後按下 Enter 
*/

//-------------------------------------------------------------------------- 
string symbol = "+-*/%";					//設定運算子及權重	(權重越大，優先權越高) 
int weight[] = { 1,1,2,2,2 };
int num = symbol.length();
//-------------------------------------------------------------------------- 
int top;
string stack;
char do_stack(string function)				//處理堆疊 	INIT : 初始化  POP : 輸出資料  PUSH : 輸入資料  TOP : 傳回資料 	char
{
	if (function == "INIT")					//初始化堆疊 
	{
		top = -1;
	}
	else if (top == -1)	return 0;			//傳回值=0，堆疊無資料 
	if (function == "POP")					//輸出最上層資料 
	{
		return stack[top--];
	}
	else if (function == "TOP")				//傳回最上層資料 
	{
		return stack[top];
	}
}

char do_stack(string function, char data)	//處理堆疊 
{
	if (function == "PUSH")					//輸入資料至堆疊最上層 
	{
		stack[++top] = data;
	}
}
//-------------------------------------------------------------------------- 
int itop;
int istack[999];
int do_istack(string function)				//處理堆疊 	INIT : 初始化  POP : 輸出資料  PUSH : 輸入資料  TOP : 傳回資料 	int
{
	if (function == "INIT")					//初始化堆疊 
	{
		itop = -1;
	}
	else if (itop == -1)	return 0;		//傳回值=0，堆疊無資料 
	if (function == "POP")					//輸出最上層資料 
	{
		return istack[itop--];
	}
	else if (function == "TOP")				//傳回最上層資料 
	{
		return istack[itop];
	}
}

int do_istack(string function, int data)	//處理堆疊
{
	if (function == "PUSH")					//輸入資料至堆疊最上層 
	{
		istack[++itop] = data;
	}
}
//-------------------------------------------------------------------------- 
bool is_num(string s)						//字串若為運算元，回傳true；否則，回傳false 
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
int priority(char Operator)					//回傳運算子權重	(權重越大，優先權越高) 
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
int string_int(string data)					//回傳運算子權重	(權重越大，優先權越高) 
{
	int i;
	istringstream temp(data);
	temp >> i;
	return i;
}
//-------------------------------------------------------------------------- 
string postfix(string data)					//中序式轉後序式 
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
int calculate(string data)					//計算結果 
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
		//cout << data << endl; 		//中序式轉後序式完成 
		cout << calculate(data) << endl;
	}
	return 0;
}
