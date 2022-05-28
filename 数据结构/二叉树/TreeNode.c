#define _CRT_SECURE_NO_WARNINGS 1
#include"TreeNode.h"
#include"Queue.h"
// ������ǰ����� 
void BinaryTreePrevOrder(BTNode* root)
{
	if (root == NULL) {
		printf("NULL ");
		return;
	}
	printf("%c ", root->_data);
	BinaryTreePrevOrder(root->_left);
	BinaryTreePrevOrder(root->_right);
}

// �������������
void BinaryTreeInOrder(BTNode* root)
{
	if (root == NULL) {
		printf("NULL ");
		return;
	}
	BinaryTreeInOrder(root->_left);
	printf("%c ", root->_data);
	BinaryTreeInOrder(root->_right);
}

// �������������
void BinaryTreePostOrder(BTNode* root)
{
	if (root == NULL) {
		printf("NULL ");
		return;
	}
	BinaryTreePostOrder(root->_left);
	BinaryTreePostOrder(root->_right);
	printf("%c ", root->_data);
}

// ͨ��ǰ�����������"ABD##E#H##CF##G##"����������
BTNode* BinaryTreeCreate(BTDataType* a, int n, int* pi)
{
	if (a[*pi] == '#')
	{
		++(*pi);
		return NULL;
	}
	BTNode* root = (BTNode*)malloc(sizeof(BTNode));
	if (root == NULL)
	{
		return NULL;
	}
	root->_data = a[*pi];
	++(*pi);
	root->_left = BinaryTreeCreate(a,n, pi);
	root->_right = BinaryTreeCreate(a,n, pi);
	return root;
}

// ����������
void BinaryTreeDestory(BTNode** root)
{
	if (*root == NULL)
		return;
	BinaryTreeDestory(&(*root)->_left);
	BinaryTreeDestory(&(*root)->_right);
	free(*root);
	//���ﲻ��*root = NULL;
	//�β���ʵ�ε���ʱ�������ں�������root�ÿ�û��
	return;
}

// �������ڵ����
int BinaryTreeSize(BTNode* root)
{
	return root == NULL ? 0 : BinaryTreeSize(root->_left) + BinaryTreeSize(root->_right) + 1;
}

// ������Ҷ�ӽڵ����
int BinaryTreeLeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;

	if (root->_left == NULL && root->_right == NULL)
		return 1;

	//��������Ҷ�ӽڵ�ĸ����������Լ�
	return BinaryTreeLeafSize(root->_left)+ BinaryTreeLeafSize(root->_right);
}

// ��������k��ڵ����
int BinaryTreeLevelKSize(BTNode* root, int k)
{
	assert(k >= 1);
	if (root == NULL)
		return 0;
	if (k == 1)
		return 1;

	return BinaryTreeLevelKSize(root->_left, k - 1)
		+ BinaryTreeLevelKSize(root->_right, k - 1);
}

// ����������ֵΪx�Ľڵ�
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
	//����
	if (root == NULL)
		return NULL;

	//����
	if (root->_data == x)
		return root;

	//���ϵĽӽ�����
	BTNode* ret1 = BinaryTreeFind(root->_left, x);
	if (ret1)
		return ret1;

	//���ϵĽӽ�����
	BTNode* ret2 = BinaryTreeFind(root->_right, x);
	if (ret2)
		return ret2;

	return NULL;
}

// �������
void BinaryTreeLevelOrder(BTNode* root)
{
	Queue tree;
	QueueInit(&tree);
	if(root)
		QueuePush(&tree, root);
	while (!QueueEmpty(&tree))
	{
		BTNode*tmp = QueueFront(&tree);
		QueuePop(&tree);
		printf("%c ", tmp->_data);
		if(tmp->_left)
			QueuePush(&tree, tmp->_left);
		if(tmp->_right)
			QueuePush(&tree, tmp->_right);
	}
	printf("\n");
	QueueDestory(&tree);
}

// �ж϶������Ƿ�����ȫ������
int BinaryTreeComplete(BTNode* root)
{
	//������Ҫ�õ����������˼·
	Queue tree;
	QueueInit(&tree);
	if (root)
		QueuePush(&tree, root);

	while (!QueueEmpty(&tree))
	{
		BTNode* tmp = QueueFront(&tree);
		//�������Ժ�ֱ�������������
		if (tmp == NULL)
			break;
		QueuePop(&tree);
		QueuePush(&tree, tmp->_left);
		QueuePush(&tree, tmp->_right);
	}
	//1.�������ȫ�ǿգ�������ȫ������
	//2.����պ��滹�зǿգ�������ȫ������
	while (!QueueEmpty(&tree))
	{
		BTNode* tmp = QueueFront(&tree);
		if (tmp) {
			QueueDestory(&tree);
			return 0;
		}
		QueuePop(&tree);
	}
	QueueDestory(&tree);
	return 1;
}