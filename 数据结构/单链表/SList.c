#include"SList.h"

void SListPrint(SLTNode* phead)
{
	SLTNode* tail = phead;
	while (tail)
	{
		printf("%d->", tail->data);
		tail = tail->next;
	}
	printf("NULL\n");
}

SLTNode* BuySLTNode(SLTDataType x)
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode) * 1);
	if (newnode == NULL)
	{
		perror("SListPushBack");
		exit(-1);
	}
	newnode->data = x;
	newnode->next = NULL;
	return newnode;
}

void SListPushBack(SLTNode** pphead, SLTDataType x)
{
	//开节点
	SLTNode* newnode = BuySLTNode(x);

	//连接尾节点
	SLTNode* tail = *pphead;
	if (tail == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		while (tail->next != NULL)
		{
			tail = tail->next;
		}
		tail->next = newnode;
	}
}

void SListPushFront(SLTNode** pphead, SLTDataType x)
{
	//开节点
	SLTNode* newnode = BuySLTNode(x);
	if (*pphead == NULL)
	{
		*pphead = newnode;
	}
	else
	{
		newnode->next = *pphead;
		*pphead = newnode;
	}
}

void SListPopBack(SLTNode** pphead)
{
	//找尾节点
	SLTNode* tail = *pphead;
	SLTNode* prev = NULL;
	//情况1：空节点
	if (tail == NULL)
	{
		return;
	}
	//情况2：只有一个节点
	else if (tail->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
	}
	else
	{
		while (tail->next != NULL)
		{
			prev = tail;
			tail = tail->next;
		}
		free(tail);
		tail = NULL;
		prev->next = NULL;
	}
}

void SListPopFront(SLTNode** pphead)
{
	SLTNode* cur = *pphead;
	if (cur == NULL)
	{
		return;
	}
	else
	{
		*pphead = cur->next;
		free(cur);
		cur = NULL;
	}
}

SLTNode* SListFind(SLTNode* phead, SLTDataType x)
{
	SLTNode* tail = phead;
	while (tail->data != x)
	{
		tail = tail->next;
	}
	return tail;
}

void SListInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x)
{
	if (pos == *pphead)
	{
		SListPushFront(pphead, x);
	}
	else
	{
		SLTNode* newnode = BuySLTNode(x);
		SLTNode* prev = *pphead;
		while (prev->next != pos)
		{
			prev = prev->next;
		}

		prev->next = newnode;
		newnode->next = pos;
	}
}

void SListErase(SLTNode** pphead, SLTNode* pos)
{
	if (pos == *pphead)
	{
		SListPopFront(pphead);
	}
	else
	{
		SLTNode* prev = *pphead;
		while (prev->next != pos)
		{
			prev = prev->next;
		}

		prev->next = pos->next;
		free(pos);
	}
}