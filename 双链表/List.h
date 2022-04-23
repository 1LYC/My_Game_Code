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

ListNode* ListInit();//初始化

void ListPrint(ListNode* phead);//打印
void ListDestory(ListNode* phead);//销毁

// pos位置之前插入x
void ListInsert(ListNode* pos, LTDataType x);
// 删除pos位置的值
void ListErase(ListNode* pos);
//查找节点
ListNode* ListFind(ListNode* phead, LTDataType x);

void ListPushBack(ListNode* phead, LTDataType x);//尾插
void ListPushFront(ListNode* phead, LTDataType x);//头插
void ListPopBack(ListNode* phead);//尾删
void ListPopFront(ListNode* phead);//头删

bool ListEmpty(ListNode* phead);//是否满了
int ListSize(ListNode* phead);//求节点个数