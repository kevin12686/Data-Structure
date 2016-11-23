#include <stdio.h>
#include <stdlib.h>

typedef struct LIST{
	int data;
	struct LIST *next;
}List;

void print(List*);
void insert(List**, int);

void main(){
	List *head = NULL;
	int a;
	printf("input -1 to stop\n\n");
	do{
		printf("input : ");
		scanf(" %d", &a);
		insert(&head, a);
	}while(a != -1);
	print(head);
}

void print(List *head){
	while(head != NULL){
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n");
}

void insert(List **head, int data){
	List *temp = (List*)malloc(sizeof(List));
	temp->data = data;
	if(*head == NULL || (*head)->data > data){
		temp->next = *head;
		*head = temp;
	}
	else{
		List *flag = *head;
		while(flag->next != NULL && flag->next->data < data){
			flag = flag->next;
		}
		if(flag->next == NULL){
			temp->next = flag->next;
			flag->next = temp;
		}
		else{
			temp->next = flag->next;
			flag->next = temp;
		}
	}
	
}
