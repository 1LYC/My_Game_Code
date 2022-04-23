#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
typedef int LTDataType;
typedef struct ListNode
{
	struct ListNode* prev;
	LTDataType data;
	struct ListNode* next;
}ListNode;

ListNode* ListInit();//��ʼ��

void ListPrint(ListNode* phead);//��ӡ
void ListDestory(ListNode* phead);//����

// posλ��֮ǰ����x
void ListInsert(ListNode* pos, LTDataType x);
// ɾ��posλ�õ�ֵ
void ListErase(ListNode* pos);
//���ҽڵ�
ListNode* ListFind(ListNode* phead, LTDataType x);

void ListPushBack(ListNode* phead, LTDataType x);//β��
void ListPushFront(ListNode* phead, LTDataType x);//ͷ��
void ListPopBack(ListNode* phead);//βɾ
void ListPopFront(ListNode* phead);//ͷɾ

bool ListEmpty(ListNode* phead);//�Ƿ�����
int ListSize(ListNode* phead);//��ڵ����