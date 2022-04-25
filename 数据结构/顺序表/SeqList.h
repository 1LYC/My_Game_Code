#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

enum Option
{
	EXIT,
	SEQLISTPUSHBACK,
	SEQLISTPUSHFRONT,
	SEQLISTPRINT,
	SEQLISTPOPBACK,
	SEQLISTPOPFRONT,
	SEQLISTINSERT,
	SEQLISTERASE,
	SEQLISTFIND,
	SEQLISTMODITY,
};

// 增强程序可维护性
typedef int SQDataType;
typedef struct SeqList
{
	SQDataType* a;
	int size;     // 有效数据的个数
	int capacity; // 容量
}SL;

void SeqListInit(SL* ps);//初始化

void SeqListPushBack(SL* ps, SQDataType x);//尾插
void SeqListPushFront(SL* ps, SQDataType x);//头插

void SeqListPrint(SL* ps);//打印

void SeqListPopBack(SL* ps);//尾删
void SeqListPopFront(SL* ps);//头删

void SeqListInsert(SL* ps, int pos, SQDataType x);//任意位置插
void SeqListErase(SL* ps, int pos);//任意位置删

int SeqListFind(SL* ps, SQDataType x);//查找
void SeqListModity(SL* ps, int pos, SQDataType x);//修改

void SeqListDestory(SL* ps);//清除顺序表