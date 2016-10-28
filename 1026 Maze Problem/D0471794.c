#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 30

typedef struct dir{
	int row, col;
}Dir;

typedef struct route{
	int row, col, dir;
}Route;

void init_dir();
void init_maze(int, int);
void push(int, int, int);
Route pop();
void move();
void print_maze();
void print_ans();

int maze[8][11] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
				{1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1},
				{1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1},
				{1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1},
				{1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1},
				{1, 0, 0, 0 ,1, 0, 1, 0, 0, 1, 1},
				{1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1},
				{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}	};
				
char ans[8][11] = {0};
Dir d[4];
int top = -1;
Route stack[MAX_SIZE] = {0};

void main(){
	init_dir();
	init_maze(1, 1);
	print_maze();
	move();
	print_ans();
}

void init_dir(){
	d[0].row = -1;
	d[0].col = 0;
	d[1].row = 0;
	d[1].col = 1;
	d[2].row = 1;
	d[2].col = 0;
	d[3].row = 0;
	d[3].col = -1;
}

void init_maze(int x, int y){
	int i, j;
	for(i = 0; i < 8; i++){
		for(j = 0; j < 11; j++){
			if(maze[i][j] == 1)	ans[i][j] = '1';
			else if(i == x && j == y)	ans[i][j] = 'E';
			else	ans[i][j] = '0';
		}
	}
}

void push(int row, int col, int dir){
	if(top < MAX_SIZE - 1){
		stack[++top].row = row;
		stack[top].col = col;
		stack[top].dir = dir;
	}
	else	printf("Stack is full.\n");
}

Route pop(){
	if(top > -1)	return stack[top--];
	else	printf("Stack is empty.\n");
}

void move(){
	int go = 0, r = 6, c = 9, nr, nc, dd = 0, status = 0;
	Route p;
	while(!status){
		for(; dd < 4; dd++){
			nr = r + d[dd].row;
			nc = c + d[dd].col;
			if(ans[nr][nc] == 'E'){
				status = 1;
				break;
			}
			else if(maze[nr][nc] == 0 && ans[nr][nc] == '0'){
				go = 1;
				break;
			}
		}
		if(status){
			ans[r][c] = '#';
		}
		else if(go){
			push(r, c, dd);
			ans[r][c] = '#';
			r = nr;
			c = nc;
			dd = 0;
			go = 0;
		}
		else{
			p = pop();
			ans[r][c] = 'X';
			dd = p.dir;
			r -= d[dd].row;
			c -= d[dd].col;
			dd++;
		}
	}
}

void print_maze(){
	int i, j;
	printf("迷宮:\n");
	for(i = 0; i < 8; i++){
		for(j = 0; j < 11; j++){
			printf("%2d", maze[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void print_ans(){
	int i, j;
	printf("迷宮路徑圖:\n");
	for(i = 0; i < 8; i++){
		for(j = 0; j < 11; j++){
			printf("%2c", ans[i][j]);
		}
		printf("\n");
	}
	printf("\n1: 牆壁\n#: 走過的路徑\nX: 回溯路徑\n");
}

void print_stack(){
	int i;
	for(i = 0; i < MAX_SIZE; i++){
		printf("%3d, %3d, %3d\t", stack[i].row, stack[i].col, stack[i].dir);
	}
}
