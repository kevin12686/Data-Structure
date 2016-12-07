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
void postfix(char*, char*);
tree* getnode(char);
void init(tree**, char*);
void preorder(tree*);
void postorder(tree*);
void inorder(tree*);

char op[] = {'+', '-', '*', '/'};
int opw[] = {0, 0, 1, 1};
char stack[30];
int top = -1;

void main(){
	tree *head = NULL;
	char s[30], in[30];
	printf(" Input Infix : ");
	gets(s);
	postfix(s, in);
	init(&head, in);
	printf(" prefix : ");
	preorder(head);
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

void postfix(char *s, char *in){
	top = -1;
	int i = 0, len = strlen(s), temp = 0;;
	for(; i < len; i++){
		if(isop(s[i])){
			if(top == -1){
				push(s[i]);
			}
			else{
				while(weight(stack[top]) >= weight(s[i]))	in[temp++] = pop();
				push(s[i]);
			}
		}
		else	in[temp++] = s[i];
	}
	while(top > -1)	in[temp++] = pop();
	in[temp] = '\n';
}

tree* getnode(char c){
	tree *temp = (tree*)malloc(sizeof(tree));
	temp->data = c;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}


void init(tree **head, char *s){
	top = -1;
	int i, len = strlen(s);
	for(i = 0; i < len; i++){
		if(!isop(s[i])){
			push(s[i]);
		}
		else if(*head != NULL){
			tree *flag = *head;
			*head = getnode(s[i]);
			(*head)->left = flag;
			(*head)->right = getnode(pop());
		}
		else{
			*head = getnode(s[i]);
			(*head)->left = getnode(pop());
			(*head)->right = getnode(pop());
		}
	}
}

void preorder(tree *head){
	if(head != NULL){
		putchar(head->data);
		preorder(head->left);
		preorder(head->right);
	}
}

void postorder(tree *head){
	if(head != NULL){
		postorder(head->left);
		postorder(head->right);
		putchar(head->data);
	}
}

void inorder(tree *head){
	if(head != NULL){
		inorder(head->left);
		putchar(head->data);
		inorder(head->right);	
	}
}
