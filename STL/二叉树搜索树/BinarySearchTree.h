//#pragma once
//#include <iostream>
//#include <utility>
//using namespace std;
//
//// ���������������и���С��������,���и�������������
//namespace Key
//{
//	// ------���Ľڵ�------
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
//	// ------���Ľڵ�------
//
//	// ------����������------
//	template<class K>
//	class BSTree
//	{
//		typedef BSTreeNode<K> Node;
//	public:
//		// ------Insert����------
//		bool Insert(const K& key)
//		{
//			if (_root == nullptr)
//			{
//				_root = new Node(key);
//				return true;
//			}
//			// ������Ҫ�ҵ�����ڵ�,��������,������Ҫ��ǰ�ڵ����һ��
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
//					// �������������в��������ֵ��ͬ�Ľڵ�
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
//		// ------Insert����------
//
//		// ------Find����------
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
//		// ------Find����------
//
//		// ------Erase����------
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
//					// �ҵ��ڵ� + ��ʼɾ��
//					// ���һ: ��Ϊ��
//					if (cur->_left == nullptr)
//					{
//						// �������: Ҫɾ���Ľڵ��Ǹ��ڵ�
//						if (cur == _root)
//						{
//							_root = cur->_right;
//						}
//						else
//						{
//							// һ�����: Ҫɾ���Ľڵ��ǷǸ��ڵ�
//							if (cur == parent->_left)
//							{
//								// �������: Ҫɾ���Ľڵ���Ҷ�ӽڵ�
//								parent->_left = cur->_right;
//							}
//							else
//							{
//								// �������: Ҫɾ���Ľڵ���Ҷ�ӽڵ�
//								parent->_right = cur->_right;// ��Ҫɾ���ڵ������,ȫ�����ӵ���һ��
//							}
//						}
//
//						delete cur;
//						cur = nullptr;
//					}
//					// �����: ��Ϊ��
//					else if (cur->_right == nullptr)
//					{
//						// �������: Ҫɾ���Ľڵ��Ǹ��ڵ�
//						if (_root == cur)
//						{
//							_root = cur->_left;
//						}
//						else
//						{
//							// һ�����: Ҫɾ���Ľڵ��ǷǸ��ڵ�
//							if (cur == parent->_left)
//							{
//								// �������: Ҫɾ���Ľڵ���Ҷ�ӽڵ�
//								parent->_left = cur->_left;
//							}
//							else
//							{
//								// �������: Ҫɾ���Ľڵ���Ҷ�ӽڵ�
//								parent->_right = cur->_left;// ��Ҫɾ���ڵ������,ȫ�����ӵ���һ��
//							}
//						}
//
//						delete cur;
//						cur = nullptr;
//					}
//					// �����: ����������Ϊ��
//					else
//					{
//						// �滻��: ���Ҫɾ���Ľڵ� �� ��������С�ڵ� ���� ������������� ���н���
//						// �������: �ҵ���������С�ڵ�����滻
//						// �������: Ҫɾ���Ľڵ��Ǹ��ڵ�
//						Node* minParent = cur;// ���ﲻ�ܳ�ʼ��Ϊ��,��Ϊ�����Ǹ��������
//						Node* min = cur->_right;
//						while (min->_left)
//						{
//							minParent = min;
//							min = min->_left;
//						}
//
//						swap(cur->_key, min->_key);
//						if (minParent->_left == min) {
//							// �������: �滻֮��Ľڵ���Ҷ�ӽڵ�
//							minParent->_left = min->_right;
//
//						}
//						else {
//							// �������: Ҫɾ���Ľڵ��Ǹ��ڵ�
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
//		// ------Erase����------
//
//		// �ݹ���Ҫ������,����Ϊthisָ�������
//		// ����Ƕ��һ����������
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
//		// ------��������------
//		~BSTree()
//		{
//			_Destory(_root);
//		}
//		// ------��������------
//
//		// ------���캯��------
//		BSTree() = default;// C++���÷���ǿ�Ʊ���������Ĭ�ϵĹ���
//
//		BSTree(const BSTree<K>& t)
//		{
//			_root = _Copy(t._root);
//		}
//		// ------���캯��------
//
//		// ------operator=����------
//		BSTree<K>& operator=(BSTree<K> t)
//		{
//			swap(_root, t._root);
//			return *this;
//		}
//		// ------operator=����------
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
//		// ���漸�����������õݹ�ʵ��
//		// �ؼ���: ���������ô���,����root����һ���root��һ����,
//		//		   ���Բ�Ҫ����parent�ҵ�ǰ�ڵ����һ��,��������
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
//				// �ҵ��ڵ� + ��ʼɾ��
//				Node* del = root;
//				// ���һ: ������Ϊ��
//				if (root->_left == nullptr)
//				{
//					root = root->_right;
//				}
//				// �����: ������Ϊ��
//				else if (root->_right == nullptr)
//				{
//					root = root->_left;
//				}
//				// �����: ���������ǿ�
//				else
//				{
//					// ������������ڵ��滻ɾ��
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
//		// ------_InOrder����------
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
//		// ------_InOrder����------
//	private:
//		Node* _root = nullptr;
//	};
//	// ------����������------
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
//		// ����+ȥ��
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
//		// ����+ȥ��
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
//// Key �� Valueǿ��
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
//		dict.Insert("sort", "����");
//		dict.Insert("left", "���");
//		dict.Insert("right", "�ұ�");
//		dict.Insert("string", "�ַ���");
//		dict.Insert("insert", "����");
//		string str;
//		while (cin >> str)
//		{
//			BSTreeNode<string, string>* ret = dict.Find(str);
//			if (ret)
//			{
//				cout << "��Ӧ������:" << ret->_value << endl;
//			}
//			else
//			{
//				cout << "��Ӧ������->�޴˵���" << endl;
//			}
//		}
//	}
//
//	// ͳ�ƴ���
//	void TestBSTree2()
//	{
//		string arr[] = { "�㽶", "ƻ��", "�㽶", "��ݮ", "�㽶", "ƻ��", "ƻ��", "ƻ��" };
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