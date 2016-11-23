#include <stdio.h>
#include <stdlib.h>

typedef struct POLY{
	int coef, pow;
	struct POLY *next;
}Poly;

void print(Poly *a);
void add(Poly **a, Poly *b);
void insert(Poly **head, int coef, int pow);

void main(){
	Poly *a = NULL, *b = NULL;
	int c, p;
	
	printf("input 0 0 to stop\n\n");
	
	do{
		printf("a - input ( coef pow ) : ");
		scanf(" %d %d", &c, &p);
		if(c != 0)	insert(&a, c, p);
	}while(c != 0 || p != 0);
	printf("a = ");
	print(a);
	printf("\n");
	
	do{
		printf("b - input ( coef pow ) : ");
		scanf(" %d %d", &c, &p);
		if(c != 0)	insert(&b, c, p);
	}while(c != 0 || p != 0);
	printf("b = ");
	print(b);
	printf("\n");
	
	add(&a, b);
	printf("ans = ");
	print(a);
	printf("\n");
	system("PAUSE");
}

void print(Poly *a){
	if(a->pow != 0)	printf("%dx^%d", a->coef, a->pow);
	else	printf("%d", a->coef);
	a = a->next;
	while(a != NULL){
		if(a->pow != 0)	printf("+%dx^%d", a->coef, a->pow);
		else	printf("+%d", a->coef);
		a = a->next;
	}
	printf("\n");
}

void add(Poly **a, Poly *b){
	while(b != NULL){
		insert(&(*a), b->coef, b->pow);
		b = b->next;
	}
}

void insert(Poly **head, int coef, int pow){
	Poly *temp = (Poly*)malloc(sizeof(Poly));
	temp->coef = coef;
	temp->pow = pow;
	if((*head) == NULL || (*head)->pow <= pow){
		if((*head) != NULL && (*head)->pow == pow){
			((*head)->coef) += coef;
			free(temp);
		}
		else{
			temp->next = *head;
			(*head) = temp;
		}
	}
	else{
		Poly *flag = *head;
		while(flag->next != NULL && flag->next->pow > pow){
			flag = flag->next;
		}
		if(flag->next == NULL){
			temp->next = flag->next;
			flag->next = temp;
		}
		else if(flag->next->pow == pow){
			(flag->next->coef) += coef;
			free(temp);
		}
		else{
			temp->next = flag->next;
			flag->next = temp;
		}
	}
}
