#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<assert.h>
typedef struct position
{
	int row;
	int col;
}PT,STDataType;

typedef struct Stack
{
	STDataType* a;
	int top;
	int capacity;
}Stack;

void StackInit(Stack* ps)
{
	assert(ps);
	ps->a = (STDataType*)malloc(sizeof(STDataType) * 4);
	if (ps->a == NULL) {
		return;
	}
	ps->top = 0;//Õ»¶¥Îª0
	ps->capacity = 4;
}

void StackPush(Stack* ps, STDataType x)
{
	assert(ps);
	if (ps->top == ps->capacity)
	{
		//À©ÈÝ
		STDataType* new = (STDataType*)realloc(ps->a, ps->capacity * 2 * sizeof(STDataType));
		if (new == NULL) {
			return;
		}
		ps->a = new;
		ps->capacity *= 2;
	}
	ps->a[ps->top] = x;
	ps->top++;
}

void StackPop(Stack* ps)
{
	assert(ps);
	assert(ps->top);
	//printf("%d ", ps->a[ps->top - 1]);
	ps->top--;
}

STDataType StackTop(Stack* ps)
{
	assert(ps);
	assert(ps->top);
	return ps->a[ps->top - 1];
}

int StackSize(Stack* ps)
{
	assert(ps);
	return ps->top;
}

bool StackEmpty(Stack* ps)
{
	assert(ps);
	return ps->top == 0;
}

void StackDestory(Stack* ps)
{
	free(ps->a);
	ps->a = NULL;
	ps->capacity = ps->top = 0;
}
Stack s;
//---------------------------

bool IsMazePath(int** maze, int m, int n, PT pos)
{
	//判断坐标合法性
	if (pos.row >= m || pos.row<0
		|| pos.col>n || pos.col < 0)
	{
		return false;
	}
	//判断这个坐标是否能“过”
	if (maze[pos.row][pos.col] == 0) {
		return true;
	}
	return false;
}

//默认入口(0,0) 出口(M-1,N-1),保证一定会有正确的路径
bool GetMazePath(int**maze, int M, int N,PT pos)
{
	StackPush(&s, pos);
	if (pos.row == M - 1 && pos.col == N - 1)
	{
		return true;
	}
	
	//
	//将已经走过的位置堵死
	maze[pos.row][pos.col] = 2;
	
	PT next;
	// 上
	next = pos;
	next.row = next.row - 1;
	if (IsMazePath(maze, M, N, next))
	{
		if (GetMazePath(maze, M, N, next))
		{
			return true;
		}
	}

	//下
	next = pos;
	next.row = next.row + 1;
	if (IsMazePath(maze, M, N, next))
	{
		if (GetMazePath(maze, M, N, next))
		{
			return true;
		}
	}

	//左
	next = pos;
	next.col = next.col - 1;
	if (IsMazePath(maze, M, N, next))
	{
		if (GetMazePath(maze, M, N, next))
		{
			return true;
		}
	}

	//右
	next = pos;
	next.col = next.col + 1;
	if (IsMazePath(maze, M, N, next))
	{
		if (GetMazePath(maze, M, N, next))
		{
			return true;
		}
	}
	StackPop(&s);
	return false;
}

void Printpath()
{
	Stack tmp;
	StackInit(&tmp);
	while (!StackEmpty(&s))
	{
		//存入另一个栈
		StackPush(&tmp, StackTop(&s));
		StackPop(&s);
	}
	while (!StackEmpty(&tmp))
	{
		PT top = StackTop(&tmp);
		StackPop(&tmp);
		printf("(%d,%d)\n", top.row, top.col);
	}
	StackDestory(&tmp);
}

int main()
{
	int M, N = 0;
	scanf("%d %d", &M, &N);
	//int arr[m][n];//C99才支持变长数组
	int** arr = (int**)malloc(sizeof(int*) * M);
	if (arr == NULL) {
		printf("malloc fail!\n");
		exit(-1);
	}
	int i = 0;
	for (i = 0; i < M; i++)
	{
		arr[i] = (int*)malloc(sizeof(int) * N);
		if (arr == NULL) {
			printf("malloc fail!\n");
			exit(-1);
		}
	}

	for (i = 0; i < M; i++)
	{
		int j = 0;
		for (j = 0; j < N; j++)
		{
			scanf("%d", &arr[i][j]);
		}
	}

	PT pos = { 0,0 };
	StackInit(&s);
	if (GetMazePath(arr, M, N, pos))
		Printpath();
	else
		printf("不存在\n");
	//销毁需要一行一行的销毁
	for (i = 0; i < N; i++)
		free(arr[i]);
	free(arr);
	StackDestory(&s);
	return 0;
}

//5 5
//0 1 0 0 0
//0 1 1 1 0
//0 0 0 0 0
//0 1 1 1 0
//0 0 0 1 0
