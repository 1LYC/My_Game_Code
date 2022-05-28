#define _CRT_SECURE_NO_WARNINGS 1
#include"TreeNode.h"
int main()
{
    char arr[100] = { 0 };
    scanf("%s", arr);
    int len = strlen(arr);
    int i = 0;
    BTNode* root = BinaryTreeCreate(arr,len, &i);
    printf("%d\n", BinaryTreeSize(root));
    printf("%d\n", BinaryTreeLeafSize(root));
    printf("%d\n", BinaryTreeLevelKSize(root, 4));
    BTNode* tmp = BinaryTreeFind(root, 'F');
    printf("%c\n", tmp->_data);
    BinaryTreeLevelOrder(root);
    int _bool1 = BinaryTreeComplete(root);
    printf("%d\n", _bool1);
    BinaryTreePostOrder(root);
    BinaryTreeDestory(&root);
    root = NULL;
    return 0;
}