#include"List.h"
void Test1(ListNode* phead)
{
	ListInsert(phead, 1);//ͷ�ڵ��ǰ��������һ��
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
		printf("��\n");
	}
	ListPushBack(phead, 1);
	ListPushBack(phead, 2);
	ListPushBack(phead, 3);
	ListPrint(phead);
	if (ListEmpty(phead)) {
		printf("��\n");
	}
	if (!ListEmpty(phead)) {
		printf("�ǿ�\n");
	}
	int count = ListSize(phead);
	printf("�ڵ�����ǣ�%d\n", count);
}

int main()
{
	//����ͷ�ڵ㲢��ʼ��,�������ʼ���ͱ����һ��ָ����,
	ListNode* phead = ListInit();
	//Test1(phead);
	//Test2(phead);
	//Test3(phead);
	Test4(phead);
	ListDestory(phead);//����
	return 0;
}