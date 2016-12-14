#include <stdio.h>
#include <stdlib.h>

void print(int *, int );
void swapNode(int *, int , char );
int getNode(int *, int , char );
void refresh(int *, int );
void refresh_s(int *, int , int );
int search(int *, int , int );
int add(int *, int , int );
int del(int *, int , int );

void main(){
	int array[20] = {0}, count = -1, read, flag = 1, i;
	FILE *in = fopen("input.txt", "r");
	if(in){
		while(fscanf(in, " %d", &read) != EOF){
			count = add(array, count + 1, read);
		}
		fclose(in);
		print(array, count + 1);
		while(flag){
			printf("1. add, 2. del, 3. stop -> ");
			scanf(" %d", &i);
			switch(i){
				case 1:
					printf("num : ");
					scanf(" %d", &read);
					count = add(array, count + 1, read);
					print(array, count + 1);
					break;
				case 2:
					printf("num : ");
					scanf(" %d", &read);
					count = del(array, read, count + 1);
					print(array, count + 1);
					break;
				case 3:
					flag = 0;
					break;
				default:
					printf("GG!!\n");
			}
		}
		print(array, count + 1);
	}
	system("pause");
}

void print(int *array, int size){
	int i = 0;
	for(; i < size; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
}

void swapNode(int *array, int i, char c){
	int temp = array[i];
	switch(c){
		case 'l' :
			array[i] = array[i * 2 + 1];
			array[i * 2 + 1] = temp;;
			break;
		case 'r' :
			array[i] = array[i * 2 + 2];
			array[i * 2 + 1] = temp;;
			break;
		case 'f' :
			array[i] = array[(i - 1) / 2];
			array[(i - 1) / 2] = temp;;
			break;
	}
}

int getNode(int *array, int i, char c){
	switch(c){
		case 'l' :
			return array[i * 2 + 1];
			break;
		case 'r' :
			return array[i * 2 + 2];
			break;
		case 'f' :
			return array[(i - 1) / 2];
		default :
			return 0;
	}
}

void refresh(int *array, int i){
	while(i > 0){
		if(array[i] > getNode(array, i, 'f'))	swapNode(array, i, 'f');
		else	break;
		i = (i - 1) / 2;
	}
}

void refresh_s(int *array, int i, int size){
	while(i <= (size - 1) / 2){
		if(array[i] < getNode(array, i, 'l') || array[i] < getNode(array, i, 'r')){
			if(getNode(array, i, 'l') > getNode(array, i , 'r')){
				swapNode(array, i, 'l');
				i = i * 2 + 1;
			}
			else{
				swapNode(array, i, 'r');
				i = i * 2 + 2;
			}
		}
		else break;
	}
}

int search(int *array, int size, int target){
	int i = 0;
	for(; i < size; i++){
		if(array[i] == target)	return i;
	}
	return -1;
}

int add(int *array, int size, int v){
	array[size++] = v;
	refresh(array, size - 1);
	return size - 1;
}

int del(int *array, int target, int size){
	int i = search(array, size, target);
	if(i != -1){
		array[i] = array[--size];
		refresh_s(array, i, size);
	}
	return size - 1;
}
