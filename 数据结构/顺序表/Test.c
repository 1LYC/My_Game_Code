#include"Seqlist.h"

int g_x = 0;
int g_pos = 0;

int main()
{
	int input = 0;
	SL s;
	SeqListInit(&s);//��ʼ��
	do
	{
		menu();
		printf("��ѡ��:");
		scanf("%d", &input);
		switch (input)
		{
		case SEQLISTPUSHBACK:
			printf("����������β�������");
			scanf("%d", &g_x);
			SeqListPushBack(&s, g_x);
			break;
		case SEQLISTPUSHFRONT:
			printf("����������ͷ�������");
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
			printf("��������������λ�ú�����");
			scanf("%d %d", &g_pos, &g_x);
			SeqListInsert(&s, g_pos, g_x);
			break;
		case SEQLISTERASE:
			printf("����������ɾ������λ�ã�");
			scanf("%d", &g_pos);
			SeqListErase(&s, g_pos);
			break;
		case SEQLISTFIND:
			printf("������������ҵ�����");
			scanf("%d", &g_x);
			int position = SeqListFind(&s, g_x);
			if (-1 == position) {
				printf("�Ҳ���\n");
			}
			else {
				printf("������ֵ��±��ǣ�%d\n", position);
			}
			break;
		case SEQLISTMODITY:
			printf("�����������޸�����λ�ã�");
			scanf("%d", &g_pos);
			printf("�����������޸ĳɵ����֣�");
			scanf("%d", &g_x);
			SeqListModity(&s, g_pos, g_x);
			break;
		case EXIT:
			SeqListDestory(&s);
			exit(0);//�ɹ��˳�
			break;
		default:
			printf("����������������룺");
			break;
		}
	} while (input);
	return 0;
}