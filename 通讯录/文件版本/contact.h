#pragma once

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME 20
#define MAX_SEX 10
#define MAX_TELE 12
#define MAX_ADDR 30

#define MAX 1000

#define DEFAULT_SZ 3
#define INC_SZ 2

//���͵Ķ���
typedef struct PeoInfo
{
	char name[MAX_NAME];
	char sex[MAX_SEX];
	int age;
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
}PeoInfo;

//��̬�汾
typedef struct contact
{
	PeoInfo* data;//ָ��̬����Ŀռ䣬���������ϵ�˵���Ϣ
	int sz;//��¼���ǵ�ǰͨѶ¼����Ч��Ϣ�ĸ���
	int capacity;//��¼��ǰͨѶ¼���������
}Contact;

//��ʼ��ͨѶ¼
void InitContact(Contact* pc);

//������ϵ��
void AddContact(Contact* pc);

//ɾ����ϵ�˵���Ϣ
void DelContact(Contact* pc);

//����ָ����ϵ��
void SearchContact(Contact* pc);

//�޸�ָ����ϵ��
void ModifyContact(Contact* pc);

//��ӡ��ϵ����Ϣ
void PrintContact(const Contact* pc);

//������ϵ�˵���Ϣ
void SortContact(Contact* pc);

//����ͨѶ¼
void Destorycontact(Contact* pc);

//����ͨѶ¼���ļ�
void SaveContact(Contact* pc);

//����ͨѶ¼
void LoadContact(Contact* pc);