#include"Stack.h"

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
	printf("%d ", ps->a[ps->top - 1]);
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
	return ps->top;
}

void StackDestory(Stack* ps)
{
	free(ps->a);
	ps->a = NULL;
	ps->capacity = ps->top = 0;
}