#include"SeqList.h"
void menu()
{
	printf("*************0.EXIT*****************\n");
	printf("******1.尾插*2.头插*3.打印***********\n");
	printf("******4.尾删*5.头删*6.插入***********\n");
	printf("******7.删除*8.查找*9.修改***********\n");
	printf("************************************\n");
}

void SeqListInit(SL* ps)
{
	ps->a = NULL;
	ps->size = 0;
	ps->capacity = 0;
}

void SeqListCheckCapacity(SL* ps)
{
	int newcapacity = (ps->capacity == 0) ? 4 : ps->capacity * 2;
	if (ps->size == ps->capacity)
	{
		//增容
		SQDataType* pr = realloc(ps->a, newcapacity * sizeof(SQDataType));
		if (pr == NULL)
		{
			perror("SeqListPushBack");
		}
		else
		{
			ps->a = pr;
			ps->capacity = newcapacity;

		}
	}
}

void SeqListPushBack(SL* ps, SQDataType x)
{
	SeqListCheckCapacity(ps);
	SeqListInsert(ps, ps->size, x);
}

void SeqListPushFront(SL* ps, SQDataType x)
{
	SeqListCheckCapacity(ps);
	SeqListInsert(ps, 0, x);
	/*int end = ps->size;
	while (end--)
	{
		ps->a[end + 1] = ps->a[end];
	}
	ps->a[0] = x;
	ps->size++;*/
}

void SeqListPrint(SL* ps)
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		printf("%d ", ps->a[i]);
	}
	printf("\n");
}

void SeqListPopBack(SL* ps)
{
	SeqListErase(ps, ps->size);
	/*assert(ps->size > 0);
	ps->size--;*/
}

void SeqListPopFront(SL* ps)
{
	assert(ps->size > 0);
	SeqListErase(ps, 1);
	/*assert(ps->size > 0);
	int end = 0;
	while (end < ps->size - 1)
	{
		ps->a[end] = ps->a[end + 1];
		end++;
	}
	ps->size--;*/
}

void SeqListInsert(SL* ps, int pos, SQDataType x)
{
	//这里没有考虑位置为负数的情况
	assert(pos <= ps->size);
	SeqListCheckCapacity(ps);
	int end = ps->size - 1;
	while (end >= pos)
	{
		ps->a[end + 1] = ps->a[end];
		--end;
	}
	ps->a[pos] = x;
	ps->size++;
}

void SeqListErase(SL* ps, int pos)
{
	//这里没有考虑位置为负数的情况
	assert(pos < ps->size);
	int end = pos + 1;
	while (end < ps->size)
	{
		ps->a[end] = ps->a[end + 1];
		end++;
	}
	ps->size--;
}

int SeqListFind(SL* ps, SQDataType x)
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (ps->a[i] == x)
		{
			return i;
		}
	}
	return -1;
}

void SeqListModity(SL* ps, int pos, SQDataType x)
{
	assert(pos < ps->size);
	ps->a[pos] = x;
}

void SeqListDestory(SL* ps)
{
	free(ps->a);
	ps->a = NULL;
	ps->size = 0;
	ps->capacity = 0;
}