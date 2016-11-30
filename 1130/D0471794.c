#include <stdio.h>
#include <stdlib.h>

typedef struct LIST{
	int data;
	struct LIST *front, *next;
}List;

void add(List **, int , int );
void print(List *, int );

void main(){
	List *head = NULL;
	int i, j;
	for(i = 0; i < 10; i++){
		printf("Please key in %d number : ", i+1);
		scanf(" %d", &j);
		add(&head, i, j);
	}
	while(1){
		printf("Please key in place and number : ");
		scanf(" %d %d", &i, &j);
		if(i >= 0){
			add(&head, i, j);
		}
		else if(i == -1 || i == -2){
			print(head, i);
			break;
		}
	}
	system("PAUSE");
}

void add(List **head, int place, int data){
	List *flag = *head;
	List *temp = (List*)malloc(sizeof(List));
	temp->data = data;
	if(!flag){
		*head = temp;
		temp->next = temp;
		temp->front = temp;
	}
	else if(place == 0){
		temp->next = flag;
		temp->front = flag->front;
		flag->front = temp;
		temp->front->next = temp;
		*head = temp;
	}
	else{
		for(flag = flag->next; flag != *head && place > 1; flag = flag->next, place--);
		temp->next = flag;
		temp->front = flag->front;
		flag->front = temp;
		temp->front->next = temp;
	}
}

void print(List *head, int op){
	List *flag = head;
	switch(op){
		case -1:
			printf("%d ", flag->data);
			for(flag = flag->next ;flag != head; flag = flag->next){
				printf("%d ", flag->data);
			}
			break;
		case -2:
			for(flag = flag->front ;flag != head; flag = flag->front){
				printf("%d ", flag->data);
			}
			printf("%d", flag->data);
			break;
	}
	printf("\n");
}
