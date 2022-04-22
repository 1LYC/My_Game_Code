#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef int SLTDataType;
typedef struct SListNode
{
	SLTDataType data;
	struct SListNode* next;
}SLTNode;

// 不会改变链表的头指针，传一级指针
void SListPrint(SLTNode* phead);

// 可能会改变链表的头指针，传二级指针
void SListPushBack(SLTNode** pphead, SLTDataType x);
void SListPushFront(SLTNode** pphead, SLTDataType x);
void SListPopBack(SLTNode** pphead);
void SListPopFront(SLTNode** pphead);

// 在pos的前面插入x
void SListInsert(SLTNode** phead, SLTNode* pos, SLTDataType x);
// 删除pos位置的值
void SListErase(SLTNode** pphead, SLTNode* pos);

SLTNode* SListFind(SLTNode* phead, SLTDataType x);

// 有些地方也有这样的
//// 在pos的前面插入x
//void SListInsert(SLTNode** phead, int i, SLTDataType x);
//// 删除pos位置的值
//void SListErase(SLTNode** phead, int i);