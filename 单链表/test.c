#include"SList.h"
int main()
{
	SLTNode* phead = NULL;
	SListPushFront(&phead, 1);
	SListPushFront(&phead, 2);

	////��������Ľڵ�λ��
	//SLTNode* pos = SListFind(phead, 1);
	//SListInsert(&phead,pos, 520);

	//��������Ľڵ�λ��
	SLTNode* pos = SListFind(phead, 1);
	SListErase(&phead, pos);

	SListPrint(phead);
	return 0;
}