#include"Seqlist.h"

int g_x = 0;
int g_pos = 0;

int main()
{
	int input = 0;
	SL s;
	SeqListInit(&s);//初始化
	do
	{
		menu();
		printf("请选择:");
		scanf("%d", &input);
		switch (input)
		{
		case SEQLISTPUSHBACK:
			printf("请输入你想尾插的数：");
			scanf("%d", &g_x);
			SeqListPushBack(&s, g_x);
			break;
		case SEQLISTPUSHFRONT:
			printf("请输入你想头插的数：");
			scanf("%d", &g_x);
			SeqListPushFront(&s, g_x);
			break;
		case SEQLISTPRINT:
			SeqListPrint(&s);
			break;
		case SEQLISTPOPBACK:
			SeqListPopBack(&s);
			break;
		case SEQLISTPOPFRONT:
			SeqListPopFront(&s);
			break;
		case SEQLISTINSERT:
			printf("请输入你想插入的位置和数：");
			scanf("%d %d", &g_pos, &g_x);
			SeqListInsert(&s, g_pos, g_x);
			break;
		case SEQLISTERASE:
			printf("请输入你想删除数的位置：");
			scanf("%d", &g_pos);
			SeqListErase(&s, g_pos);
			break;
		case SEQLISTFIND:
			printf("请输入你想查找的数：");
			scanf("%d", &g_x);
			int position = SeqListFind(&s, g_x);
			if (-1 == position) {
				printf("找不到\n");
			}
			else {
				printf("这个数字的下标是：%d\n", position);
			}
			break;
		case SEQLISTMODITY:
			printf("请输入你想修改数的位置：");
			scanf("%d", &g_pos);
			printf("请输入你想修改成的数字：");
			scanf("%d", &g_x);
			SeqListModity(&s, g_pos, g_x);
			break;
		case EXIT:
			SeqListDestory(&s);
			exit(0);//成功退出
			break;
		default:
			printf("输入错误请重新输入：");
			break;
		}
	} while (input);
	return 0;
}