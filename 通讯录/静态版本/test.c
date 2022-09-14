#define _CRT_SECURE_NO_WARNINGS 1
#include "contact.h"

void menu()
{
	printf("********************************\n");
	printf("******  1. add    2. del  ******\n");
	printf("******  3. search 4. modify*****\n");
	printf("******  5. sort   6. print *****\n");
	printf("******  0. exit            *****\n");
	printf("********************************\n");
}

enum Option
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SORT,
	PRINT
};

int main()
{
	int input = 0;
	//创建通讯录
	Contact con;//通讯录-类型是一个结构体
	//初始化通讯录
	InitContact(&con);
	do
	{
		menu();
		printf("请选择:>");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			//增加人的信息
			AddContact(&con);
			break;
		case DEL:
			//删除
			DelContact(&con);
			break;
		case SEARCH:
			SearchContact(&con);
			break;
		case MODIFY:
			ModifyContact(&con);
			break;
		case SORT:
			// 待完善
			break;
		case PRINT:
			PrintContact(&con);
			break;
		case EXIT:
			printf("退出通讯录\n");
			break;
		default:
			printf("选择错误,重新选择\n");
			break;
		}
	} while (input);

	return 0;
}
