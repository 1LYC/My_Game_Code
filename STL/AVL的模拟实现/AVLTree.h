//#pragma once
//#include <iostream>
//#include <map>
//#include <string>
//#include <algorithm>
//#include <time.h>
//#include <assert.h>
//using namespace std;
//
//template<class K, class V>
//struct AVLTreeNode
//{
//	// 定义三叉链: 有了_parent的话,方便更新平衡因子,但是增加了旋转的复杂度
//	AVLTreeNode<K, V>* _left;
//	AVLTreeNode<K, V>* _right;
//	AVLTreeNode<K, V>* _parent;
//
//	pair<K, V> _kv;
//	// 平衡因子不是必须的
//	int _bf;  // 平衡因子 = (存在根的右子树就加1) + (存在根的左子树就加-1);
//
//	// -------构造函数-------
//	AVLTreeNode(const pair<K, V>& kv)
//		:_left(nullptr)
//		, _right(nullptr)
//		, _parent(nullptr)
//		, _kv(kv)
//		, _bf(0)
//	{}
//	// -------构造函数-------
//};
//
//template<class K, class V>
//struct AVLTree
//{
//	typedef AVLTreeNode<K, V> Node;
//public:
//	bool Insert(const pair<K, V>& kv)
//	{
//		// step1: 找插入的位置
//		if (_root == nullptr)
//		{
//			_root = new Node(kv);
//			return true;
//		}
//
//		Node* parent = nullptr;// 为了找到之后,连接上去
//		Node* cur = _root;
//		while (cur)
//		{
//			// cur->_kv.first 表示当前节点的key,
//			if (cur->_kv.first < kv.first)
//			{
//				parent = cur;
//				cur = cur->_right;
//			}
//			else if (cur->_kv.first > kv.first)
//			{
//				parent = cur;
//				cur = cur->_left;
//			}
//			else
//			{
//				// 不允许有相同的
//				return false;
//			}
//		}
//		// cur为空,开辟一个新节点,然后连接上去
//		// parent只是记录了cur的上一个节点,并不能确定插在是 插在左边 还是 插在右边
//		cur = new Node(kv);
//		if (parent->_kv.first < kv.first)
//		{
//			parent->_right = cur;
//		}
//		else
//		{
//			parent->_left = cur;
//		}
//		cur->_parent = parent;// 记得更新新节点的_parent
//
//		// step2:更新平衡因子 + 控制平衡
//		while (parent)
//		{
//			// step2.1: 新增在右parent->bf++,新增在左parent->bf--
//			if (cur == parent->_right)
//			{
//				parent->_bf++;
//			}
//			else
//			{
//				parent->_bf--;
//			}
//
//			// step2.3:更新后prent->bf == 0,
//			// 说明插入前:parent的平衡因子是1 or -1,左右子树一边高一边低
//			//	   插入后:两边一样高,插入后填上了矮的那边,parent所在子树的高度不变,
//			//	   不需要继续往上更新
//			if (parent->_bf == 0)
//			{
//				break;
//			}
//
//			// step2.2:更新后parent->bf == 1 or -1,
//			// 说明插入前: parent的平衡因子是0,说明左右子树高度相等,
//			//     插入后: 有一边高了,则parent的高度变了
//			//     需要继续往上更新
//			else if (abs(parent->_bf) == 1)
//			{
//				parent = parent->_parent;
//				cur = cur->_parent;
//			}
//
//			// step2.4:更新后,parent->bf == 2 of -2
//			// 说明插入前: parent的平衡因子是1 or -1,已经到达平衡临界值,
//			//	   插入后: 变成2 or -2,打破平衡,parent所在子树需要旋转处理
//			//	   不需要继续往上更新
//			else if (abs(parent->_bf) == 2)
//			{
//				// step3: 说明parent所在子树已经不平衡了，需要旋转处理
//				if (parent->_bf == 2 && cur->_bf == 1)
//				{
//					// step3.1: 新节点插入较高右子树的右侧--右右: 左单旋
//					RotateL(parent);
//				}
//				else if ((parent->_bf == -2 && cur->_bf == -1))
//				{
//					// step3.2: 新节点插入较高左子树的左侧--左左: 右单旋
//					RotateR(parent);
//				}
//				else if (parent->_bf == -2 && cur->_bf == 1)
//				{
//					// step3.3: 左右双旋转的情况
//					RotateLR(parent);
//				}
//				else if (parent->_bf == 2 && cur->_bf == -1)
//				{
//					// step3.4: 右左双旋转的情况
//					RotateRL(parent);
//				}
//				else
//				{
//					assert(false);// 直接断死
//				}
//
//				break;
//			}
//			// step2.5:更新后:parent->bf > 2 or < -2的值,
//			// 不可能,如果存在,则说明插入前就不是AVL数,需要去检查之前的操作的问题
//			else
//			{
//				assert(false);// 直接断死
//			}
//		}
//
//		return true;
//	}
//	void InOrder()
//	{
//		_InOrder(_root);
//		cout << endl;
//	}
//
//	bool IsBalance()
//	{
//		return _IsBalance(_root);
//	}
//private:
//	// 因为设计了三叉链,所以旋转起来有一点复杂
//	void RotateL(Node* parent)
//	{
//		// 为方便操作记录一下节点
//		Node* subR = parent->_right;
//		Node* subRL = subR->_left;
//
//		parent->_right = subRL;
//		// 注意: subRl可能是空子树
//		if (subRL)
//			subRL->_parent = parent;
//
//		Node* ppNode = parent->_parent;// 记录一下
//
//		subR->_left = parent;
//		parent->_parent = subR;
//		
//		// parent可能是根节点,也可能是根的子树
//		if (_root == parent)
//		{
//			_root = subR;
//			subR->_parent = nullptr;
//		}
//		else
//		{
//			// ppNode只是记录了parent的上一层,不确定parent是否是左右子树
//			if (ppNode->_left == parent)
//			{
//				ppNode->_left = subR;
//			}
//			else
//			{
//				ppNode->_right = subR;
//			}
//
//			subR->_parent = ppNode;
//		}
//		// 最后再更新一下平衡因子
//		subR->_bf = parent->_bf = 0;
//	}
//
//	void RotateR(Node* parent)
//	{
//		// 为方便操作记录一下节点
//		Node* subL = parent->_left;
//		Node* subLR = subL->_right;
//
//		parent->_left = subLR;
//		// 注意: subRl可能是空子树
//		if (subLR){
//			subLR->_parent = parent;
//		}
//
//		Node* ppNode = parent->_parent;// 记录一下
//
//		subL->_right = parent;
//		parent->_parent = subL;
//
//		// parent可能是根节点,也可能是根的子树
//		if (_root == parent)
//		{
//			_root = subL;
//			subL->_parent = nullptr;
//		}
//		else
//		{
//			// ppNode只是记录了parent的上一层,不确定parent是否是左右子树
//			if (ppNode->_left == parent)
//			{
//				ppNode->_left = subL;
//			}
//			else
//			{
//				ppNode->_right = subL;
//			}
//
//			subL->_parent = ppNode;
//		}
//		// 最后再更新一下平衡因子
//		subL->_bf = parent->_bf = 0;
//	}
//
//	void RotateLR(Node* parent)
//	{
//		// 平衡因子的改变有点难
//		Node* subL = parent->_left;
//		Node* subLR = subL->_right;
//		int bf = subLR->_bf;// 这个平衡因子需要记录
//
//		RotateL(parent->_left);// 先左旋
//		RotateR(parent);// 再右旋
//
//		subLR->_bf = 0;// 插入后就是根节点,因为已经旋转了,所以为0
//		if (bf == 1)
//		{
//			parent->_bf = 0;
//			subL->_bf = -1;
//		}
//		else if (bf == -1)
//		{
//			// 错的
//			/*parent->_bf = 0;
//			subL->_bf = 1;*/
//
//			parent->_bf = 1;
//			subL->_bf = 0;
//		}
//		else if (bf == 0)
//		{
//			parent->_bf = 0;
//			subL->_bf = 0;
//		}
//		else
//		{
//			assert(false);
//		}
//	}
//
//	void RotateRL(Node* parent)
//	{
//		Node* subR = parent->_right;
//		Node* subRL = subR->_left;
//
//		int bf = subRL->_bf;
//
//		RotateR(parent->_right);
//		RotateL(parent);
//
//		subRL->_bf = 0;
//		if (bf == 1)
//		{
//			subR->_bf = 0;
//			parent->_bf = -1;
//		}
//		else if (bf == -1)
//		{
//			subR->_bf = 1;
//			parent->_bf = 0;
//		}
//		else if (bf == 0)
//		{
//			parent->_bf = 0;
//			subR->_bf = 0;
//		}
//		else
//		{
//			assert(false);
//		}
//	}
//	
//	void _InOrder(Node* root)
//	{
//		if (root == nullptr)
//		{
//			return;
//		}
//
//		_InOrder(root->_left);
//		// root->_kv.first是key,root->second是value
//		cout << root->_kv.first << ":" << root->_kv.second << endl;
//		_InOrder(root->_right);
//	}
//
//	// 求一个节点的高度,也可以求一棵树的深度
//	int Height(Node* root)
//	{
//		if (root == nullptr)
//			return 0;
//
//		return max(Height(root->_left), Height(root->_right)) + 1;
//	}
//
//	// 判断是否满足高度平衡二叉树的条件
//	bool _IsBalance(Node* root)
//	{
//		if (root == nullptr)
//		{
//			return true;
//		}
//
//		int leftHT = Height(root->_left);
//		int rightHT = Height(root->_right);
//
//		int diff = rightHT - leftHT;// 得到平衡因子
//
//		if (diff != root->_bf)
//		{
//			cout << root->_kv.first << "平衡因子异常" << endl;
//			return false;
//		}
//
//		return abs(diff) < 2 
//			&& _IsBalance(root->_left) 
//			&& _IsBalance(root->_right);
//	}
//private:
//	Node* _root = nullptr;
//};
//
//void TestAVLTree1()
//{
//	//int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };  // 测试双旋平衡因子调节
//	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
//	AVLTree<int, int> t1;
//	for (auto e : a){
//		t1.Insert(make_pair(e, e));
//	}
//
//	t1.InOrder();
//	cout << "IsBalance:" << t1.IsBalance() << endl;
//}
//
//void TestAVLTree2()
//{
//	// 使用随机数进行检查
//	size_t N = 10000;
//	srand(time(0));// 在C语言中只能产生3万多个种子,再多就是重复的数
//	AVLTree<int, int> t1;
//	// 下面的注释的目的是: 出错了,多半是平衡因子有问题,就用下面的代码,进行调试
//	for (size_t i = 0; i < N; ++i)
//	{
//		int x = rand();
//		/*if (x = 某个数) {
//			assert(false);
//		}*/
//		t1.Insert(make_pair(x, i));
//		/*bool ret = t1.IsBalance();
//		if (ret == false)
//		{
//			assert(false);
//		}
//		else
//		{
//			cout << "Insert:" << x << " IsBalance:" <<ret<< endl;
//		}*/
//	}
//	cout << "IsBalance:" << t1.IsBalance() << endl;
//}