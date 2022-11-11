//#pragma once
//#include <iostream>
//#include <utility>
//using namespace std;
//
//// 二插搜索树的所有根都小于左子树,所有根都大于右子树
//namespace Key
//{
//	// ------树的节点------
//	template<class K>
//	struct BSTreeNode
//	{
//		BSTreeNode<K>* _left;
//		BSTreeNode<K>* _right;
//		K _key;
//
//		BSTreeNode(const K& key)
//			:_left(nullptr)
//			, _right(nullptr)
//			, _key(key)
//		{}
//	};
//	// ------树的节点------
//
//	// ------二插搜索树------
//	template<class K>
//	class BSTree
//	{
//		typedef BSTreeNode<K> Node;
//	public:
//		// ------Insert函数------
//		bool Insert(const K& key)
//		{
//			if (_root == nullptr)
//			{
//				_root = new Node(key);
//				return true;
//			}
//			// 这里需要找到这个节点,并且连接,所以需要当前节点的上一个
//			Node* parent = nullptr;
//			Node* cur = _root;
//			while (cur)
//			{
//				if (cur->_key < key)
//				{
//					parent = cur;
//					cur = cur->_right;
//				}
//				else if (cur->_key > key)
//				{
//					parent = cur;
//					cur = cur->_left;
//				}
//				else
//				{
//					// 在搜索二叉树中不允许出现值相同的节点
//					return false;
//				}
//			}
//
//			cur = new Node(key);
//			if (parent->_key < key)
//			{
//				parent->_right = cur;
//			}
//			else
//			{
//				parent->_left = cur;
//			}
//
//			return true;
//		}
//		// ------Insert函数------
//
//		// ------Find函数------
//		bool Find(const K& key)
//		{
//			Node* cur = _root;
//			while (cur)
//			{
//				if (cur->_key < key)
//				{
//					cur = cur->_right;
//				}
//				else if (cur->_key > key)
//				{
//					cur = cur->_left;
//				}
//				else
//				{
//					return true;
//				}
//			}
//			return false;
//		}
//		// ------Find函数------
//
//		// ------Erase函数------
//		bool Erase(const K& key)
//		{
//			Node* parent = nullptr;
//			Node* cur = _root;
//			while (cur)
//			{
//				if (cur->_key < key)
//				{
//					parent = cur;
//					cur = cur->_right;
//				}
//				else if (cur->_key > key)
//				{
//					parent = cur;
//					cur = cur->_left;
//				}
//				else
//				{
//					// 找到节点 + 开始删除
//					// 情况一: 左为空
//					if (cur->_left == nullptr)
//					{
//						// 特殊情况: 要删除的节点是根节点
//						if (cur == _root)
//						{
//							_root = cur->_right;
//						}
//						else
//						{
//							// 一般情况: 要删除的节点是非根节点
//							if (cur == parent->_left)
//							{
//								// 特殊情况: 要删除的节点是叶子节点
//								parent->_left = cur->_right;
//							}
//							else
//							{
//								// 特殊情况: 要删除的节点是叶子节点
//								parent->_right = cur->_right;// 将要删除节点的子树,全部连接到上一个
//							}
//						}
//
//						delete cur;
//						cur = nullptr;
//					}
//					// 情况二: 右为空
//					else if (cur->_right == nullptr)
//					{
//						// 特殊情况: 要删除的节点是根节点
//						if (_root == cur)
//						{
//							_root = cur->_left;
//						}
//						else
//						{
//							// 一般情况: 要删除的节点是非根节点
//							if (cur == parent->_left)
//							{
//								// 特殊情况: 要删除的节点是叶子节点
//								parent->_left = cur->_left;
//							}
//							else
//							{
//								// 特殊情况: 要删除的节点是叶子节点
//								parent->_right = cur->_left;// 将要删除节点的子树,全部连接到上一个
//							}
//						}
//
//						delete cur;
//						cur = nullptr;
//					}
//					// 情况三: 左右子树都为空
//					else
//					{
//						// 替换法: 这个要删除的节点 和 右子树最小节点 或者 是左子树的最大 进行交换
//						// 这里采用: 找到右子树最小节点进行替换
//						// 特殊情况: 要删除的节点是根节点
//						Node* minParent = cur;// 这里不能初始化为空,因为上面那个特殊情况
//						Node* min = cur->_right;
//						while (min->_left)
//						{
//							minParent = min;
//							min = min->_left;
//						}
//
//						swap(cur->_key, min->_key);
//						if (minParent->_left == min) {
//							// 特殊情况: 替换之后的节点是叶子节点
//							minParent->_left = min->_right;
//
//						}
//						else {
//							// 特殊情况: 要删除的节点是根节点
//							minParent->_right = min->_right;
//						}
//						delete min;
//					}
//
//					return true;
//				}
//			}
//
//			return false;
//		}
//		// ------Erase函数------
//
//		// 递归需要传参数,又因为this指针的问题
//		// 这里嵌套一层更方便调用
//		void InOrder()
//		{
//			_InOrder(_root);
//			cout << endl;
//		}
//
//		bool FindR(const K& key)
//		{
//			return _FindR(_root, key);
//		}
//
//		bool InsertR(const K& key)
//		{
//			return _InsertR(_root, key);
//		}
//
//		bool EraseR(const K& key)
//		{
//			return _EraseR(_root, key);
//		}
//
//		// ------析构函数------
//		~BSTree()
//		{
//			_Destory(_root);
//		}
//		// ------析构函数------
//
//		// ------构造函数------
//		BSTree() = default;// C++的用法：强制编译器生成默认的构造
//
//		BSTree(const BSTree<K>& t)
//		{
//			_root = _Copy(t._root);
//		}
//		// ------构造函数------
//
//		// ------operator=函数------
//		BSTree<K>& operator=(BSTree<K> t)
//		{
//			swap(_root, t._root);
//			return *this;
//		}
//		// ------operator=函数------
//
//	private:
//		Node* _Copy(Node* root)
//		{
//			if (root == nullptr)
//			{
//				return nullptr;
//			}
//
//			Node* copyRoot = new Node(root->_key);
//			copyRoot->_left = _Copy(root->_left);
//			copyRoot->_right = _Copy(root->_right);
//			return copyRoot;
//		}
//
//		void _Destory(Node*& root)
//		{
//			if (root == nullptr){
//				return;
//			}
//			_Destory(root->_left);
//			_Destory(root->_right);
//			delete root;
//			root = nullptr;
//		}
//
//		// 下面几个函数都是用递归实现
//		// 关键点: 这里是引用传参,这里root和上一层的root是一样的,
//		//		   所以不要定义parent找当前节点的上一个,进行连接
//		bool _EraseR(Node*& root, const K& key)
//		{
//			if (root == nullptr)
//				return false;
//
//			if (root->_key < key) {
//				return _EraseR(root->_right, key);
//			}
//			else if (root->_key > key) {
//				return _EraseR(root->_left, key);
//			}
//			else
//			{
//				// 找到节点 + 开始删除
//				Node* del = root;
//				// 情况一: 左子树为空
//				if (root->_left == nullptr)
//				{
//					root = root->_right;
//				}
//				// 情况二: 右子树为空
//				else if (root->_right == nullptr)
//				{
//					root = root->_left;
//				}
//				// 情况三: 左右子树非空
//				else
//				{
//					// 找右树的最左节点替换删除
//					Node* min = root->_right;
//					while (min->_left)
//					{
//						min = min->_left;
//					}
//					swap(root->_key, min->_key);
//					return _EraseR(root->_right, key);
//				}
//
//				delete del;
//				return true;
//			}
//		}
//
//		bool _InsertR(Node*& root, const K& key)
//		{
//			if (root == nullptr)
//			{
//				root = new Node(key);
//				return true;
//			}
//
//			if (root->_key < key)
//				return _InsertR(root->_right, key);
//			else if (root->_key > key)
//				return _InsertR(root->_left, key);
//			else
//				return false;
//		}
//
//		bool _FindR(Node* root, const K& key)
//		{
//			if (root == nullptr)
//				return false;
//
//			if (root->_key < key)
//				return _FindR(root->_right, key);
//			else if (root->_key > key)
//				return _FindR(root->_left, key);
//			else
//				return true;
//		}
//		
//		// ------_InOrder函数------
//		void _InOrder(Node* root)
//		{
//			if (root == nullptr)
//			{
//				return;
//			}
//
//			_InOrder(root->_left);
//			cout << root->_key << " ";
//			_InOrder(root->_right);
//		}
//		// ------_InOrder函数------
//	private:
//		Node* _root = nullptr;
//	};
//	// ------搜索二插树------
//	
//	void TestBSTree1()
//	{
//		BSTree<int> t;
//		int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3, 4 };
//		for (auto e : a)
//		{
//			t.Insert(e);
//		}
//
//		// 排序+去重
//		t.InOrder();
//
//		t.Erase(3);
//		t.InOrder();
//
//		t.Erase(8);
//		t.InOrder();
//		for (auto e : a)
//		{
//			t.Erase(e);
//			t.InOrder();
//		}
//	}
//
//	void TestBSTree2()
//	{
//		BSTree<int> t;
//		int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3, 4 };
//		for (auto e : a)
//		{
//			t.InsertR(e);
//		}
//
//		// 排序+去重
//		t.InOrder();
//
//		t.EraseR(14);
//		t.InOrder();
//
//		t.EraseR(8);
//		t.InOrder();
//
//		for (auto e : a)
//		{
//			t.Erase(e);
//			t.InOrder();
//		}
//	}
//
//	void TestBSTree3()
//	{
//		BSTree<int> t;
//		int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13, 4, 3, 4 };
//		for (auto e : a)
//		{
//			t.InsertR(e);
//		}
//
//		BSTree<int> copy = t;
//		copy.InOrder();
//		t.InOrder();
//
//		BSTree<int> t1;
//		t1.Insert(2);
//		t1.Insert(1);
//		t1.Insert(3);
//
//		copy = t1;
//		copy.InOrder();
//		t1.InOrder();
//	}
//}
//
//// Key 和 Value强绑定
//namespace KeyValue
//{
//	template<class K, class V>
//	struct BSTreeNode
//	{
//		BSTreeNode<K, V>* _left;
//		BSTreeNode<K, V>* _right;
//		K _key;
//		V _value;
//
//		BSTreeNode(const K& key, const V& value)
//			:_left(nullptr)
//			, _right(nullptr)
//			, _key(key)
//			, _value(value)
//		{}
//	};
//
//	template<class K, class V>
//	class BSTree
//	{
//		typedef BSTreeNode<K, V> Node;
//	public:
//		bool Insert(const K& key, const V& value)
//		{
//			if (_root == nullptr)
//			{
//				_root = new Node(key, value);
//				return true;
//			}
//
//			Node* parent = nullptr;
//			Node* cur = _root;
//			while (cur)
//			{
//				if (cur->_key < key)
//				{
//					parent = cur;
//					cur = cur->_right;
//				}
//				else if (cur->_key > key)
//				{
//					parent = cur;
//					cur = cur->_left;
//				}
//				else
//				{
//					return false;
//				}
//			}
//
//			cur = new Node(key, value);
//			if (parent->_key < key)
//			{
//				parent->_right = cur;
//			}
//			else
//			{
//				parent->_left = cur;
//			}
//
//			return true;
//		}
//
//		Node* Find(const K& key)
//		{
//			Node* cur = _root;
//			while (cur)
//			{
//				if (cur->_key < key)
//				{
//					cur = cur->_right;
//				}
//				else if (cur->_key > key)
//				{
//					cur = cur->_left;
//				}
//				else
//				{
//					return cur;
//				}
//			}
//
//			return nullptr;
//		}
//
//		bool Erase(const K& key)
//		{
//			//...
//
//			return true;
//		}
//
//		void InOrder()
//		{
//			_InOrder(_root);
//			cout << endl;
//		}
//	private:
//
//		void _InOrder(Node* root)
//		{
//			if (root == nullptr)
//			{
//				return;
//			}
//
//			_InOrder(root->_left);
//			cout << root->_key << ":" << root->_value << endl;
//			_InOrder(root->_right);
//		}
//	private:
//		Node* _root = nullptr;
//	};
//
//	void TestBSTree1()
//	{
//		BSTree<string, string> dict;
//		dict.Insert("sort", "排序");
//		dict.Insert("left", "左边");
//		dict.Insert("right", "右边");
//		dict.Insert("string", "字符串");
//		dict.Insert("insert", "插入");
//		string str;
//		while (cin >> str)
//		{
//			BSTreeNode<string, string>* ret = dict.Find(str);
//			if (ret)
//			{
//				cout << "对应的中文:" << ret->_value << endl;
//			}
//			else
//			{
//				cout << "对应的中文->无此单词" << endl;
//			}
//		}
//	}
//
//	// 统计次数
//	void TestBSTree2()
//	{
//		string arr[] = { "香蕉", "苹果", "香蕉", "草莓", "香蕉", "苹果", "苹果", "苹果" };
//
//		BSTree<string, int> countTree;
//		for (auto& str : arr)
//		{
//			//BSTreeNode<string, int>* ret = countTree.Find(str);
//			auto ret = countTree.Find(str);
//			if (ret)
//			{
//				ret->_value++;
//			}
//			else
//			{
//				countTree.Insert(str, 1);
//			}
//		}
//
//		countTree.InOrder();
//	}
//}