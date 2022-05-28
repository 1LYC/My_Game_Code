#include "Heap.h"
void Test()
{
	HP hp;
	HeapInit(&hp);
	int arr[] = { 27, 15, 19, 18, 28, 34, 65, 49, 25, 37 };
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		HeapPush(&hp, arr[i]);
	}
	HeapPintf(&hp, hp.size);
	printf("%d\n", HeapTop(&hp));
	HeapPop(&hp);
	HeapPintf(&hp, hp.size);
	printf("%d\n", HeapTop(&hp));
	printf("%d\n", HeapSize(&hp));
	if (HeapEmpty(&hp))
	{
		printf("Пе\n");
	}
	HeapDestroy(&hp);
}
int main()
{
	Test();
	return 0;
}