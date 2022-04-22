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

// ����ı������ͷָ�룬��һ��ָ��
void SListPrint(SLTNode* phead);

// ���ܻ�ı������ͷָ�룬������ָ��
void SListPushBack(SLTNode** pphead, SLTDataType x);
void SListPushFront(SLTNode** pphead, SLTDataType x);
void SListPopBack(SLTNode** pphead);
void SListPopFront(SLTNode** pphead);

// ��pos��ǰ�����x
void SListInsert(SLTNode** phead, SLTNode* pos, SLTDataType x);
// ɾ��posλ�õ�ֵ
void SListErase(SLTNode** pphead, SLTNode* pos);

SLTNode* SListFind(SLTNode* phead, SLTDataType x);

// ��Щ�ط�Ҳ��������
//// ��pos��ǰ�����x
//void SListInsert(SLTNode** phead, int i, SLTDataType x);
//// ɾ��posλ�õ�ֵ
//void SListErase(SLTNode** phead, int i);