#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct course{
	char name[30];
	int score;
	int time;
	struct course *next;
}course_t;

typedef struct student{
	char name[30];
	struct student *next;
	course_t *head;
}student_t;

void add(student_t **, char *, char *, int , int );
void addcourse(course_t **, char *, int , int );

void main(){
	FILE* input = fopen("transcript.txt", "r");
	student_t *list = NULL;
	char name[30], course[30], temp[100];
	int score;
	if(input){
		fscanf(input," %s", name);
		while(fscanf(input," %s", temp) != EOF){
			sscanf(temp, "%[^,]", name);
			sscanf(temp + sizeof(char) * strlen(name) + 1, "%[^,]", course);
			sscanf(temp + sizeof(char) * (strlen(name) + strlen(course)) + 2, "%d", &score);
			//printf("%s, %s, %d\n", name, course, score);
			add(&list, name, course, score, 1);
		}
		//printf("--------------------------\n");
		while(list != NULL){
			printf("%s", list->name);
			while(list->head != NULL){
				printf(", %s : %.2f", list->head->name, (float)list->head->score / list->head->time);
				list->head = list->head->next;
			}
			printf("\n");
			list = list->next;
		}
	}
	else{
		printf("File not found.");
	}
	fclose(input);
	system("PAUSE");
}

void addcourse(course_t **head, char *name, int score, int time){
	if(*head == NULL){
		course_t *temp = (course_t*)malloc(sizeof(course_t));
		strcpy(temp->name, name);
		temp->score = score;
		temp->time = time;
		temp->next = NULL;
		*head = temp;
	}
	else if(strcmp((*head)->name, name) == 0){
		(*head)->score += score;
		(*head)->time += time;
	}
	else{
		int find = 0;
		course_t *flag = *head;
		while(flag->next != NULL){
			if(strcmp(flag->next->name, name) == 0){
				find = 1;
				break;
			}
			flag = flag->next;
		}
		if(find == 0){
			course_t *temp = (course_t*)malloc(sizeof(course_t));
			strcpy(temp->name, name);
			temp->score = score;
			temp->time = time;
			temp->next = NULL;
			flag->next = temp;
		}
		else{
			flag->next->score += score;
			flag->next->time += time;
		}
	}
}

void add(student_t **head, char *name, char *course, int score, int time){
	if(*head == NULL){
		student_t *temp = (student_t*)malloc(sizeof(student_t));
		strcpy(temp->name, name);
		temp->next = NULL;
		temp->head = NULL;
		addcourse(&(temp->head), course, score, time);
		*head = temp;
	}
	else if(strcmp((*head)->name, name) == 0){
		addcourse(&((*head)->head), course, score, time);
	}
	else{
		int find = 0;
		student_t *flag = *head;
		while(flag->next != NULL){
			if(strcmp(flag->next->name, name) == 0){
				find = 1;
				break;
			}
			flag = flag->next;
		}
		if(find == 0){
			student_t *temp = (student_t*)malloc(sizeof(student_t));
			strcpy(temp->name, name);
			temp->next = NULL;
			temp->head = NULL;
			addcourse(&(temp->head), course, score, time);
			flag->next = temp;
		}
		else{
			addcourse(&(flag->next->head), course, score, time);
		}
	}
}
