#include"Stack.h"
void Test1(Stack* ps)
{
	StackPush(ps, 1);
	StackPush(ps, 2);
	printf("%d\n",StackTop(ps));
	StackPush(ps, 3);
	StackPush(ps, 4);
	StackPush(ps, 5);
	printf("%d\n", StackSize(ps));
	while (StackEmpty(ps))
	{
		StackPop(ps);
	}
}

int main()
{
	Stack s;
	StackInit(&s);
	Test1(&s);
	StackDestory(&s);
	return 0;
}