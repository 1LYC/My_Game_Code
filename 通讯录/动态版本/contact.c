#define _CRT_SECURE_NO_WARNINGS 1

#include "contact.h"

//动态版本
//初始化通讯录
void InitContact(Contact* pc)
{
	pc->data = (PeoInfo*)malloc(DEFAULT_SZ * sizeof(PeoInfo));
	if (pc->data == NULL)
	{
		perror("Initcontact");
		return;
	}
	pc->sz = 0;//初始化后默认是0
	pc->capacity = DEFAULT_SZ;
}

int CheckCapacity(Contact* pc) 
{
	if (pc->sz == pc->capacity)
	{
		PeoInfo* ptr = (PeoInfo*)realloc(pc->data, (pc->capacity + 11111100000) * sizeof(PeoInfo));
		if (ptr != NULL)
		{
			pc->data = ptr;
			pc->capacity += INC_SZ;
			printf("增容成功\n");
			return 1;
		}
		else
		{
			perror("AddContact");
			printf("增加联系人失败\n");
			return 0;
		}
	}
	return 1;
}

//动态版本
//增加人的信息
void AddContact(Contact* pc)
{
	if (CheckCapacity(pc) == 1)
	{
		//增加一个人的信息
		printf("请输入名字:>");
		scanf("%s", pc->data[pc->sz].name);
		printf("请输入年龄:>");
		scanf("%d", &(pc->data[pc->sz].age));
		printf("请输入性别:>");
		scanf("%s", pc->data[pc->sz].sex);
		printf("请输入电话:>");
		scanf("%s", pc->data[pc->sz].tele);
		printf("请输入地址:>");
		scanf("%s", pc->data[pc->sz].addr);
		printf("增加成功\n");
		pc->sz++;
	}
	return;
}
//销毁通讯录
void Destorycontact(Contact* pc)
{
	free(pc->data);
	pc->data = NULL;
	pc->sz = 0;
	pc->capacity = 0;
}

void PrintContact(const Contact* pc)
{
	int i = 0;
	//打印标题
	printf("%-20s\t%-5s\t%-5s\t%-12s\t%-20s\n", "名字", "年龄", "性别", "电话", "地址");
	//打印数据
	for (i = 0; i < pc->sz; i++)
	{
		printf("%-20s\t%-5d\t%-5s\t%-12s\t%-20s\n", 
			pc->data[i].name, 
			pc->data[i].age,
			pc->data[i].sex,
			pc->data[i].tele,
			pc->data[i].addr);
	}
}

static int FindByName(Contact* pc, char name[])
{
	int i = 0;
	for (i = 0; i < pc->sz; i++)
	{
		if (strcmp(pc->data[i].name, name) == 0)
		{
			return i;
		}
	}
	return -1;//找不到
}

void DelContact(Contact* pc)
{
	char name[MAX_NAME] = {0};

	if (pc->sz == 0)
	{
		printf("通讯录为空，无需删除\n");
		return;
	}	
	printf("请输入要删除人的名字:>");
	scanf("%s", name);

	//1. 查找要删除的人
	//有/没有
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("要删除的人不存在\n");
		return;
	}
	//2. 删除
	int i = 0;
	for (i = pos; i < pc->sz-1; i++)
	{
		pc->data[i] = pc->data[i + 1];
	}
	// i < pc->sz-1
	//如果只有一个人的信息，且被删除的话，
	//只要sz--

	pc->sz--;
	printf("删除成功\n");
}


void SearchContact(Contact* pc)
{
	char name[MAX_NAME] = { 0 };
	printf("请输入要查找人的名字:>");
	scanf("%s", name);

	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("要查找的人不存在\n");
		return;
	}
	else
	{
		printf("%-20s\t%-5s\t%-5s\t%-12s\t%-20s\n", "名字", "年龄", "性别", "电话", "地址");
		//打印数据
		printf("%-20s\t%-5d\t%-5s\t%-12s\t%-20s\n",
				pc->data[pos].name,
				pc->data[pos].age,
				pc->data[pos].sex,
				pc->data[pos].tele,
				pc->data[pos].addr);
	}
}


void ModifyContact(Contact* pc)
{
	char name[MAX_NAME] = { 0 };
	printf("请输入要修改人的名字:>");
	scanf("%s", name);

	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("要修改的人不存在\n");
		return;
	}
	else
	{
		printf("请输入名字:>");
		scanf("%s", pc->data[pos].name);
		printf("请输入年龄:>");
		scanf("%d", &(pc->data[pos].age));
		printf("请输入性别:>");
		scanf("%s", pc->data[pos].sex);
		printf("请输入电话:>");
		scanf("%s", pc->data[pos].tele);
		printf("请输入地址:>");
		scanf("%s", pc->data[pos].addr);

		printf("修改成功\n");
	}
}


void SortContact(Contact* pc)
{
	int a = 0;
	char name[MAX_NAME] = { 0 };
	printf("请输入要排序人的名字:>");
	scanf("%s", name);
	int pos = FindByName(pc, name);
	if (pos == -1)
	{
		printf("要排序的人不存在\n");
		return;
	}
	printf("你需要把他移动到第几个：");
	scanf("%d", &a);
	//交换
	PeoInfo tmp ;
	memset(&tmp, 0, sizeof(PeoInfo));
	memcpy(&tmp, &(pc->data[pos]), sizeof(PeoInfo));
	memcpy(&(pc->data[pos]), &(pc->data[a-1]), sizeof(PeoInfo));
	memcpy(&(pc->data[a-1]), &tmp, sizeof(PeoInfo));
	printf("移动成功\n");
}
