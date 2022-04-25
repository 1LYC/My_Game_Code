#include"SList.h"
int main()
{
	SLTNode* phead = NULL;
	SListPushFront(&phead, 1);
	SListPushFront(&phead, 2);

	////找这个数的节点位置
	//SLTNode* pos = SListFind(phead, 1);
	//SListInsert(&phead,pos, 520);

	//找这个数的节点位置
	SLTNode* pos = SListFind(phead, 1);
	SListErase(&phead, pos);

	SListPrint(phead);
	return 0;
}