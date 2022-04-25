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

// ��ǿ�����ά����
typedef int SQDataType;
typedef struct SeqList
{
	SQDataType* a;
	int size;     // ��Ч���ݵĸ���
	int capacity; // ����
}SL;

void SeqListInit(SL* ps);//��ʼ��

void SeqListPushBack(SL* ps, SQDataType x);//β��
void SeqListPushFront(SL* ps, SQDataType x);//ͷ��

void SeqListPrint(SL* ps);//��ӡ

void SeqListPopBack(SL* ps);//βɾ
void SeqListPopFront(SL* ps);//ͷɾ

void SeqListInsert(SL* ps, int pos, SQDataType x);//����λ�ò�
void SeqListErase(SL* ps, int pos);//����λ��ɾ

int SeqListFind(SL* ps, SQDataType x);//����
void SeqListModity(SL* ps, int pos, SQDataType x);//�޸�

void SeqListDestory(SL* ps);//���˳���