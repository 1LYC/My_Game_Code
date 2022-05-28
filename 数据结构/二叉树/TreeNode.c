#define _CRT_SECURE_NO_WARNINGS 1
#include"TreeNode.h"
#include"Queue.h"
// 二叉树前序遍历 
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

// 二叉树中序遍历
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

// 二叉树后序遍历
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

// 通过前序遍历的数组"ABD##E#H##CF##G##"构建二叉树
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

// 二叉树销毁
void BinaryTreeDestory(BTNode** root)
{
	if (*root == NULL)
		return;
	BinaryTreeDestory(&(*root)->_left);
	BinaryTreeDestory(&(*root)->_right);
	free(*root);
	//这里不用*root = NULL;
	//形参是实参的临时拷贝，在函数里面root置空没用
	return;
}

// 二叉树节点个数
int BinaryTreeSize(BTNode* root)
{
	return root == NULL ? 0 : BinaryTreeSize(root->_left) + BinaryTreeSize(root->_right) + 1;
}

// 二叉树叶子节点个数
int BinaryTreeLeafSize(BTNode* root)
{
	if (root == NULL)
		return 0;

	if (root->_left == NULL && root->_right == NULL)
		return 1;

	//返回左右叶子节点的个数，不算自己
	return BinaryTreeLeafSize(root->_left)+ BinaryTreeLeafSize(root->_right);
}

// 二叉树第k层节点个数
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

// 二叉树查找值为x的节点
BTNode* BinaryTreeFind(BTNode* root, BTDataType x)
{
	//出口
	if (root == NULL)
		return NULL;

	//出口
	if (root->_data == x)
		return root;

	//不断的接近出口
	BTNode* ret1 = BinaryTreeFind(root->_left, x);
	if (ret1)
		return ret1;

	//不断的接近出口
	BTNode* ret2 = BinaryTreeFind(root->_right, x);
	if (ret2)
		return ret2;

	return NULL;
}

// 层序遍历
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

// 判断二叉树是否是完全二叉树
int BinaryTreeComplete(BTNode* root)
{
	//这里需要用到层序遍历的思路
	Queue tree;
	QueueInit(&tree);
	if (root)
		QueuePush(&tree, root);

	while (!QueueEmpty(&tree))
	{
		BTNode* tmp = QueueFront(&tree);
		//遇到空以后，直接跳出层序遍历
		if (tmp == NULL)
			break;
		QueuePop(&tree);
		QueuePush(&tree, tmp->_left);
		QueuePush(&tree, tmp->_right);
	}
	//1.如果后面全是空，则是完全二叉树
	//2.如果空后面还有非空，则不是完全二叉树
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