#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void push(char);
char pop(void);
int weight(char);
int isop(char);
void prefix(char*);
void postfix(char*);

char op[] = {'+', '-', '*', '/'};
int opw[] = {0, 0, 1, 1};
char stack[30];
int top = -1;

void main(){
	char s[30];
	printf(" Input infix : ");
	gets(s);
	printf("\n prefix : ");
	prefix(s);
	printf("\n postfix : ");
	postfix(s);
	system("pause");
}

void push(char c){
	if(top < 29)	stack[++top] = c;
}

char pop(){
	if(top > -1)	return stack[top--];
	else	return ' ';
}

int weight(char c){
	int i = 0;
	for(; i < 4; i++){
		if(c == op[i])	return opw[i];
	}
	return -1;
}

int isop(char c){
	int i = 0;
	for(; i < 4; i++){
		if(c == op[i])	return 1;
	}
	return 0;
}

void show(){
	int i;
	for(i = 0; i <= top; i++){
		printf("%c ", stack[i]);
	}
	if(top > -1)	printf("\n");
}

void prefix(char *s){
	top = -1;
	int i = 0, len = strlen(s), temp = len + 1;
	char out[len];
	for(i = len; i > -1; i--){
		if(isop(s[i])){
			if(top == -1){
				push(s[i]);
			}
			else{
				
				while(weight(stack[top]) > weight(s[i]))	out[--temp] = pop();
				push(s[i]);
			}
		}
		else	out[--temp] = s[i];
	}
	while(top > -1)	out[--temp] = pop();
	puts(out);
}

void postfix(char *s){
	top = -1;
	int i = 0, len = strlen(s);
	for(; i < len; i++){
		if(isop(s[i])){
			if(top == -1){
				push(s[i]);
			}
			else{
				while(weight(stack[top]) >= weight(s[i]))	putchar(pop());
				push(s[i]);
			}
		}
		else	putchar(s[i]);
	}
	while(top > -1)	putchar(pop());
}
