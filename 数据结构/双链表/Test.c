#include"List.h"
void Test1(ListNode* phead)
{
	ListInsert(phead, 1);//头节点的前面就是最后一个
	ListPrint(phead);
	ListInsert(phead, 2);
	ListPrint(phead);
	ListInsert(phead, 3);
	ListPrint(phead);
	ListInsert(phead, 4);
	ListPrint(phead);
	ListNode* pos = ListFind(phead, 4);
	if (pos != NULL)
	{
		ListErase(pos);
	}
	ListPrint(phead);
}

void Test2(ListNode* phead)
{
	ListPushBack(phead, 1);
	ListPushBack(phead, 2);
	ListPushBack(phead, 3);
	ListPrint(phead);
	ListPushFront(phead, 4);
	ListPushFront(phead, 5);
	ListPushFront(phead, 6);
	ListPrint(phead);
	ListNode* pos = ListFind(phead, 4);
	if (pos != NULL)
	{
		ListInsert(pos, 520);
	}
	ListPrint(phead);
}

void Test3(ListNode* phead)
{
	ListPushBack(phead, 1);
	ListPushBack(phead, 2);
	ListPushBack(phead, 3);
	ListPrint(phead);
	ListPopBack(phead);
	ListPrint(phead);
	ListPopFront(phead);
	ListPrint(phead);
}

void Test4(ListNode* phead)
{
	if (ListEmpty(phead)) {
		printf("空\n");
	}
	ListPushBack(phead, 1);
	ListPushBack(phead, 2);
	ListPushBack(phead, 3);
	ListPrint(phead);
	if (ListEmpty(phead)) {
		printf("空\n");
	}
	if (!ListEmpty(phead)) {
		printf("非空\n");
	}
	int count = ListSize(phead);
	printf("节点个数是：%d\n", count);
}

int main()
{
	//创建头节点并初始化,如果不初始化就变成了一个指针了,
	ListNode* phead = ListInit();
	//Test1(phead);
	//Test2(phead);
	//Test3(phead);
	Test4(phead);
	ListDestory(phead);//销毁
	return 0;
}