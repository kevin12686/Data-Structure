#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CPS 1000.0
#define size 100

void swap(int *, int *);
void show(int *);
void initRan(int *);
void copyArray(int *, int *);
double insertion_sort(int *);
double selection_sort(int *);
int sequential_search(int *, int );
int binary_search(int *, int );

void main(){
	int s[size] = {}, i[size] = {}, target, resultA, resultB;
	double timeA, timeB;
	clock_t S, E;
	initRan(s);
	copyArray(s, i);
	show(i);
	timeA = selection_sort(s);
	timeB = insertion_sort(i);
	printf("Selection sort execution time: %lf\n", timeA);
	printf("Insertion sort execution time: %lf\n\n", timeB);
	printf("Insertion Sort array:\n");
	show(i);
	printf("Selecttion Sort array:\n");
	show(s);
	
	printf("\nInput: ");
	scanf(" %d", &target);
	printf("\n");
	
	S = clock();
	resultA = sequential_search(s, target);
	E = clock();
	timeA = ((double)(E - S)) / CPS;
	
	S = clock();
	resultB = binary_search(s, target);
	E = clock();
	timeB = ((double)(E - S)) / CPS;
	printf("Sequential search execution time: %lf\n", timeA);
	printf("Binary search execution time: %lf\n\n", timeB);
	printf("Sequential search result:%d\n", resultA);
	printf("Binary search result:%d\n", resultB);
}

void swap(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}

void show(int *num){
	int i = 0;
	for(; i < size; i++){
		printf("%4d", num[i]);
	}
	printf("\n");
}

void initRan(int *num){
	int i = 0;
	for(; i < size; i++){
		num[i] = i + 1;
	}
	
	srand(time(NULL));
	for(i = 0; i < size; i++){
		swap(&num[i], &num[rand() % 100]);
	}
}

void copyArray(int *from, int *to){
	int i = 0;
	for(; i < size; i++){
		to[i] = from[i];
	}
}

double insertion_sort(int *num){
	double RunTime = 0;
	clock_t S,E;
	S = clock();
	
	int i = 1, j = 0, temp = 0;
	for(; i < size; i++){
		j = i - 1;
		temp = num[i];
		while(j >= 0 && temp < num[j]){
			num[j + 1] = num[j];
			j--;
		}
		num[j + 1] = temp;
	}
	printf("Insertion sort ...Done\n");
	
	E = clock();
	RunTime = ((double)(E - S)) / CPS;
	return RunTime;
}

double selection_sort(int *num){
	double RunTime = 0;
	clock_t S,E;
	S = clock();
	
	int i = 0, j = 0, min = 0;
	for(; i < size - 1; i++){
		min = i;
		for(j = i + 1; j < size; j++){
			if(num[min] > num[j])	min = j;
		}
		swap(&num[i], &num[min]);
	}
	printf("Selection sort ...Done\n");
	
	E = clock();
	RunTime = ((double)(E - S)) / CPS;
	return RunTime;
}

int sequential_search(int *num, int target){
	int i = 0;
	for(; i < size; i++){
		if(num[i] == target){
			printf("Sequential search ...Done\n");
			return i;
		}	
	}
	printf("Sequential search ...Done\n");
	return -1;
}

int binary_search(int *num, int target){
	int left = 0, right = size - 1, middle;
	while(left <= right){
		middle = (left + right) / 2;
		//printf("%d %d %d\n", left, middle, right);
		if(num[middle] == target){
			printf("Binary search ...Done\n");
			return middle;
		}
		else if(num[middle] > target)	right = middle - 1;
		else	left = middle + 1;
	}
	printf("Binary search ...Done\n");
	return -1;
}
