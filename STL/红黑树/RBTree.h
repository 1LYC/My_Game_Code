#pragma once
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include <time.h>
#include <assert.h>
using namespace std;

// 枚举定义颜色 - 红/黑
enum Colour
{
	RED,
	BLACK
};

// 红黑树为了封装map和set,模型还是Key-Value模型
template<class K, class V>
struct RBTreeNode
{
	RBTreeNode<K, V>* _left;
	RBTreeNode<K, V>* _right;
	RBTreeNode<K, V>* _parent;

	RBTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
	{}

	pair<K, V> _kv;
	Colour _col;
};

template<class K, class V>
struct RBTree
{
	typedef RBTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		// 第一个根节点为黑色
		if (_root == nullptr)
		{
			_root = new Node(kv);
			_root->_col = BLACK;
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		// 这里新插入节点统一处理成红色
		cur = new Node(kv);
		cur->_col = RED;
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}
		cur->_parent = parent;

		// 上面代码已经将新节点插入并链接上了红黑树中了
		// 下面代码处理情况一,情况二,情况三,保持红黑树的规则不变
		while (parent && parent->_col == RED)
		{

			Node* grandfater = parent->_parent;

			assert(grandfater);
			assert(grandfater->_col == BLACK);

			// 关键看叔叔
			if (parent == grandfater->_left)
			{
				Node* uncle = grandfater->_right;
				// 情况一 : uncle存在且为红，变色+继续往上处理
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfater->_col = RED;
					// 继续往上处理
					cur = grandfater;
					parent = cur->_parent;
				}
				// 情况二 + 三：uncle不存在 + 存在且为黑
				else
				{
					// 情况二：右单旋+变色
					//     g 
					//   p   u
					// c
					if (cur == parent->_left)
					{
						RotateR(grandfater);
						parent->_col = BLACK;
						grandfater->_col = RED;
					}
					else
					{
						// 情况三：左右单旋+变色
						//     g 
						//   p   u
						//     c
						RotateL(parent);
						RotateR(grandfater);
						cur->_col = BLACK;
						grandfater->_col = RED;
					}

					break;
				}
			}
			else // (parent == grandfater->_right)
			{
				Node* uncle = grandfater->_left;
				// 情况一
				if (uncle && uncle->_col == RED)
				{
					parent->_col = uncle->_col = BLACK;
					grandfater->_col = RED;
					// 继续往上处理
					cur = grandfater;
					parent = cur->_parent;
				}
				else
				{
					// 情况二：左单旋+变色
					//     g 
					//   u   p
					//         c
					if (cur == parent->_right)
					{
						RotateL(grandfater);
						parent->_col = BLACK;
						grandfater->_col = RED;
					}
					else
					{
						// 情况三：右左单旋+变色
						//     g 
						//   u   p
						//     c
						RotateR(parent);
						RotateL(grandfater);
						cur->_col = BLACK;
						grandfater->_col = RED;
					}

					break;
				}
			}

		}

		_root->_col = BLACK;
		return true;
	}

	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	// 判断是否符合红黑树的规则
	bool IsBalance()
	{
		if (_root == nullptr)
		{
			return true;
		}

		if (_root->_col == RED)
		{
			cout << "根节点不是黑色" << endl;
			return false;
		}
		int benchmark = 0;// 黑色节点数量基准值
		
		// 检查每一条路径中黑色节点的个数
		return PrevCheck(_root, 0, benchmark);
	}

private:
	// 检查每一条路径中黑色节点的个数
	// DFS 前序的深度优先遍历
	bool PrevCheck(Node* root, int blackNum, int& benchmark)
	{
		if (root == nullptr)
		{
			if (benchmark == 0)
			{
				// 这条代码只会执行一次,递归到最左节点,返回的时候,执行这条代码
				benchmark = blackNum;
				return true;
			}

			// benchmark 是引用传参,只有一份,
			if (blackNum != benchmark)
			{
				cout << "某条黑色节点的数量不相等" << endl;
				return false;
			}
			else
			{
				return true;
			}
		}

		if (root->_col == BLACK)
		{
			++blackNum;// 黑色节点个数 + 1
		}

		if (root->_col == RED && root->_parent->_col == RED)
		{
			cout << "存在连续的红色节点" << endl;
			return false;
		}

		return PrevCheck(root->_left, blackNum, benchmark)
			&& PrevCheck(root->_right, blackNum, benchmark);
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}

	// 左旋
	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		Node* ppNode = parent->_parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (_root == parent)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}

			subR->_parent = ppNode;
		}

	}

	// 右旋
	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}

		Node* ppNode = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (_root == parent)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}

			subL->_parent = ppNode;
		}

	}

	// 红黑树没有平衡因子,所以不需要单独写一个双旋的函数,
	// 左旋 与 右旋 的组合 就可以达到双旋的效果
private:
	Node* _root = nullptr;
};

void TestRBTree1()
{
	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14, 0,5,30,25,20,4,13,30,28,27 };  // 测试双旋平衡因子调节
	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	RBTree<int, int> t1;
	for (auto e : a)
	{
		t1.Insert(make_pair(e, e));
	}

	t1.InOrder();
	cout << "IsBalance:" << t1.IsBalance() << endl;
}

void TestRBTree2()
{
	size_t N = 1000;
	srand(time(0));
	RBTree<int, int> t1;
	for (size_t i = 0; i < N; ++i)
	{
		int x = rand();
		//cout << "Insert:" << x << ":" << i << endl;
		t1.Insert(make_pair(x, i));
	}
	cout << "IsBalance:" << t1.IsBalance() << endl;
}