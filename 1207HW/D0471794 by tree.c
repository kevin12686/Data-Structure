#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct TREE{
	char data;
	struct TREE *left, *right;
}tree;

int isop(char);
void push(char);
char pop(void);
int weight(char);
void prefix(char*, char*);
tree* init(char*, int*);
void preorder(tree*);
void inorder(tree*);
void postorder(tree*);

char op[] = {'+', '-', '*', '/'};
int opw[] = {0, 0, 1, 1};
char stack[30];
int top = -1;

void main(){
	tree *head = NULL;
	int i = 0;
	char s[30], in[30];
	printf(" Input Infix : ");
	gets(s);
	prefix(s, in);
	head = init(in, &i);
	printf(" prefix : ");
	preorder(head);
	printf("\n infix : ");
	inorder(head);
	printf("\n postfix : ");
	postorder(head);
	printf("\n ");
	system("pause");
	
}

int isop(char c){
	switch(c){
		case '+':
		case '-':
		case '*':
		case '/':
			return 1;
			break;
		default:
			return 0;
	}
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

void prefix(char *s, char *out){
	top = -1;
	int i = 0, len = strlen(s), temp = len + 1;
	out[len] = '\0';
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
}

tree* init(char *s, int *zero){
	tree *temp = (tree*)malloc(sizeof(tree));
	temp->data = s[*zero];
	(*zero)++;
	if(!isop(s[(*zero)-1])){
		temp->left = NULL;
		temp->right = NULL;
		return temp;
	}
	temp->left = init(s, zero);
	temp->right = init(s, zero);
	return temp;
}

void preorder(tree *head){
	if(head != NULL){
		putchar(head->data);
		preorder(head->left);
		preorder(head->right);
	}
}

void inorder(tree *head){
	if(head != NULL){
		inorder(head->left);
		putchar(head->data);
		inorder(head->right);	
	}
}

void postorder(tree *head){
	if(head != NULL){
		postorder(head->left);
		postorder(head->right);
		putchar(head->data);
	}
}

