#include"List.h"

ListNode* ListInit()
{
	ListNode* phead = (ListNode*)malloc(sizeof(ListNode) * 1);
	if (phead == NULL)
	{
		return NULL;
	}
	phead->prev = phead;
	phead->data = 0;
	phead->next = phead;
	return phead;
}

void ListPrint(ListNode* phead)
{
	ListNode* tail = phead->next;
	while (tail != phead)
	{
		printf("%d->", tail->data);
		tail = tail->next;
	}
	printf("NULL\n");
}

void ListDestory(ListNode* phead)
{
	ListNode* tail = phead->next;
	while (tail != phead)
	{
		ListNode* cur = tail;
		tail = tail->next;
		free(cur);
		cur = NULL;
	}
	free(phead);
	phead = NULL;
}

ListNode* BuyListNode(LTDataType x)
{
	ListNode* newnode = (ListNode*)malloc(sizeof(ListNode) * 1);
	if (newnode == NULL)
	{
		return NULL;
	}
	newnode->prev = NULL;
	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}

void ListInsert(ListNode* pos, LTDataType x)
{
	assert(pos);
	ListNode* prev = pos->prev;//前
	ListNode* newnode = BuyListNode(x);
	ListNode* next = pos;//后

	prev->next = newnode;
	newnode->next = next;

	next->prev = newnode;
	newnode->prev = prev;
}

void ListErase(ListNode* pos)
{
	//没有节点，还删除就报错
	assert(pos != pos->next);

	ListNode* prev = pos->prev;//前
	ListNode* cur = pos;
	ListNode* next = pos->next;//后

	prev->next = next;
	next->prev = prev;
	free(cur);
	cur = NULL;
}

ListNode* ListFind(ListNode* phead, LTDataType x)
{
	assert(phead != phead->next);
	ListNode* tail = phead->next;
	while (tail != phead)
	{
		if (tail->data == x)
		{
			return tail;
		}
		tail = tail->next;
	}
	return NULL;
}

void ListPushBack(ListNode* phead, LTDataType x)
{
	ListInsert(phead, x);
}

void ListPushFront(ListNode* phead, LTDataType x)
{
	ListInsert(phead->next, x);
}

void ListPopBack(ListNode* phead)
{
	ListErase(phead->prev);
}

void ListPopFront(ListNode* phead)
{
	ListErase(phead->next);
}

bool ListEmpty(ListNode* phead)
{
	if (phead == phead->next) {
		return true;//空
	}
	else {
		return false;//非空
	}
}

int ListSize(ListNode* phead)
{
	int count = 0;
	ListNode* tail = phead->next;
	while (tail != phead)
	{
		count++;
		tail = tail->next;
	}
	return count;
}