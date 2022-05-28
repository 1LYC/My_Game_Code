#include "Heap.h"

void HeapInit(HP* php)
{
	assert(php);
	php->a = NULL;
	php->size = php->capacity = 0;
}

void HeapDestroy(HP* php)
{
	assert(php);
	free(php->a);
	php->a = NULL;
	php->size = php->capacity = 0;
}

void HeapPintf(HP* php, int n)
{
	assert(php);
	int i = 0;
	for (i = 0; i < n; i++)
	{
		printf("%d ", php->a[i]);
	}
	printf("\n");
}

void Swap(HPDataType* a, HPDataType*b)
{
	HPDataType tmp = *a;
	*a = *b;
	*b = tmp;
}

void AdjustUp(HPDataType* a, int child)
{
	int parent = (child - 1) / 2;
	while (child > 0)
	{
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}

void HeapPush(HP* php, HPDataType x)
{
	assert(php);
	if (php->size == php->capacity)
	{
		int newcapacity = php->capacity == 0 ? 4 : php->capacity * 2;
		HPDataType* arr = (HPDataType*)realloc(php->a,sizeof(HPDataType) * newcapacity);
		if (arr == NULL)
		{
			exit(-1);
		}
		php->a = arr;
		php->capacity = newcapacity;
	}
	php->a[php->size++] = x;
	//先上调整算法
	AdjustUp(php->a, php->size - 1);
}

void AdjustDwon(HPDataType* a, int size, int parent)
{
	int child = parent * 2 + 1;
	while (child < size)
	{
		//选出左右孩子中小的那个
		//这里默认左孩子更小，不对的话再调整
		if (child + 1< size && a[child + 1] < a[child])
		{
			++child;
		}

		//孩子跟父亲比较
		if (a[child] < a[parent])
		{
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else {
			break;
		}
	}
}

void HeapPop(HP* php)
{
	assert(php);
	//交换第一个和最后一个
	Swap(&php->a[0], &php->a[php->size-1]);
	php->size--;

	//向下调整
	AdjustDwon(php->a,php->size,0);
}

HPDataType HeapTop(HP* php)
{
	assert(php);
	assert(php->size);
	return php->a[0];
}

bool HeapEmpty(HP* php)
{
	assert(php);
	return php->size == 0;
}

int HeapSize(HP* php)
{
	assert(php);
	return php->size;
}