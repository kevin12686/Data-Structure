#include <stdio.h>
#include <stdlib.h>

typedef struct TREE{
	char data;
	struct TREE *left, *right;
}tree;

void init(tree**);
void preorder(tree*);
void inorder(tree*);
void postorder(tree*);

void main(){
	tree *head;
	init(&head);
	printf(" pre-order : ");
	preorder(head);
	printf("\n in-order : ");
	inorder(head);
	printf("\n post-order : ");
	postorder(head);
	printf("\n ");
	system("Pause");
}

void init(tree **head){
	*head = (tree*)malloc(sizeof(tree));
	(*head)->data = '+';
	tree *flag = *head;
	flag->right = (tree*)malloc(sizeof(tree));
	flag->right->data = 'E';
	flag->right->left = NULL;
	flag->right->right = NULL;
	flag->left = (tree*)malloc(sizeof(tree));
	flag->left->data = '*';
	flag->left->right = (tree*)malloc(sizeof(tree));
	flag->left->right->data = 'D';
	flag->left->right->left = NULL;
	flag->left->right->right = NULL;
	flag->left->left = (tree*)malloc(sizeof(tree));
	flag->left->left->data = '*';
	flag->left->left->right = (tree*)malloc(sizeof(tree));
	flag->left->left->right->data = 'C';
	flag->left->left->right->left = NULL;
	flag->left->left->right->right = NULL;
	flag->left->left->left = (tree*)malloc(sizeof(tree));
	flag->left->left->left->data = '/';
	flag->left->left->left->left = (tree*)malloc(sizeof(tree));
	flag->left->left->left->left->data = 'A';
	flag->left->left->left->left->left = NULL;
	flag->left->left->left->left->right = NULL;
	flag->left->left->left->right = (tree*)malloc(sizeof(tree));
	flag->left->left->left->right->data = 'B';
	flag->left->left->left->right->left = NULL;
	flag->left->left->left->right->right = NULL;
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
