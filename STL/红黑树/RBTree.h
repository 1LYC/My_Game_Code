//#pragma once
//#include <iostream>
//#include <map>
//#include <string>
//#include <algorithm>
//#include <time.h>
//#include <assert.h>
//using namespace std;
//
//// ö�ٶ�����ɫ - ��/��
//enum Colour
//{
//	RED,
//	BLACK
//};
//
//// �����Ϊ�˷�װmap��set,ģ�ͻ���Key-Valueģ��
//template<class K, class V>
//struct RBTreeNode
//{
//	RBTreeNode<K, V>* _left;
//	RBTreeNode<K, V>* _right;
//	RBTreeNode<K, V>* _parent;
//
//	RBTreeNode(const pair<K, V>& kv)
//		:_left(nullptr)
//		, _right(nullptr)
//		, _parent(nullptr)
//		, _kv(kv)
//	{}
//
//	pair<K, V> _kv;
//	Colour _col;
//};
//
//template<class K, class V>
//struct RBTree
//{
//	typedef RBTreeNode<K, V> Node;
//public:
//	bool Insert(const pair<K, V>& kv)
//	{
//		// ��һ�����ڵ�Ϊ��ɫ
//		if (_root == nullptr)
//		{
//			_root = new Node(kv);
//			_root->_col = BLACK;
//			return true;
//		}
//
//		Node* parent = nullptr;
//		Node* cur = _root;
//		while (cur)
//		{
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
//				return false;
//			}
//		}
//
//		// �����²���ڵ�ͳһ����ɺ�ɫ
//		cur = new Node(kv);
//		cur->_col = RED;
//		if (parent->_kv.first < kv.first)
//		{
//			parent->_right = cur;
//		}
//		else
//		{
//			parent->_left = cur;
//		}
//		cur->_parent = parent;
//
//		// ��������Ѿ����½ڵ���벢�������˺��������
//		// ������봦�����һ,�����,�����,���ֺ�����Ĺ��򲻱�
//		while (parent && parent->_col == RED)
//		{
//
//			Node* grandfater = parent->_parent;
//
//			assert(grandfater);
//			assert(grandfater->_col == BLACK);
//
//			// �ؼ�������
//			if (parent == grandfater->_left)
//			{
//				Node* uncle = grandfater->_right;
//				// ���һ : uncle������Ϊ�죬��ɫ+�������ϴ���
//				if (uncle && uncle->_col == RED)
//				{
//					parent->_col = uncle->_col = BLACK;
//					grandfater->_col = RED;
//					// �������ϴ���
//					cur = grandfater;
//					parent = cur->_parent;
//				}
//				// ����� + ����uncle������ + ������Ϊ��
//				else
//				{
//					// ��������ҵ���+��ɫ
//					//     g 
//					//   p   u
//					// c
//					if (cur == parent->_left)
//					{
//						RotateR(grandfater);
//						parent->_col = BLACK;
//						grandfater->_col = RED;
//					}
//					else
//					{
//						// ����������ҵ���+��ɫ
//						//     g 
//						//   p   u
//						//     c
//						RotateL(parent);
//						RotateR(grandfater);
//						cur->_col = BLACK;
//						grandfater->_col = RED;
//					}
//
//					break;
//				}
//			}
//			else // (parent == grandfater->_right)
//			{
//				Node* uncle = grandfater->_left;
//				// ���һ
//				if (uncle && uncle->_col == RED)
//				{
//					parent->_col = uncle->_col = BLACK;
//					grandfater->_col = RED;
//					// �������ϴ���
//					cur = grandfater;
//					parent = cur->_parent;
//				}
//				else
//				{
//					// �����������+��ɫ
//					//     g 
//					//   u   p
//					//         c
//					if (cur == parent->_right)
//					{
//						RotateL(grandfater);
//						parent->_col = BLACK;
//						grandfater->_col = RED;
//					}
//					else
//					{
//						// �������������+��ɫ
//						//     g 
//						//   u   p
//						//     c
//						RotateR(parent);
//						RotateL(grandfater);
//						cur->_col = BLACK;
//						grandfater->_col = RED;
//					}
//
//					break;
//				}
//			}
//
//		}
//
//		_root->_col = BLACK;
//		return true;
//	}
//
//	void InOrder()
//	{
//		_InOrder(_root);
//		cout << endl;
//	}
//
//	// �ж��Ƿ���Ϻ�����Ĺ���
//	bool IsBalance()
//	{
//		if (_root == nullptr)
//		{
//			return true;
//		}
//
//		if (_root->_col == RED)
//		{
//			cout << "���ڵ㲻�Ǻ�ɫ" << endl;
//			return false;
//		}
//		int benchmark = 0;// ��ɫ�ڵ�������׼ֵ
//		
//		// ���ÿһ��·���к�ɫ�ڵ�ĸ���
//		return PrevCheck(_root, 0, benchmark);
//	}
//
//private:
//	// ���ÿһ��·���к�ɫ�ڵ�ĸ���
//	// DFS ǰ���������ȱ���
//	bool PrevCheck(Node* root, int blackNum, int& benchmark)
//	{
//		if (root == nullptr)
//		{
//			if (benchmark == 0)
//			{
//				// ��������ֻ��ִ��һ��,�ݹ鵽����ڵ�,���ص�ʱ��,ִ����������
//				benchmark = blackNum;
//				return true;
//			}
//
//			// benchmark �����ô���,ֻ��һ��,
//			if (blackNum != benchmark)
//			{
//				cout << "ĳ����ɫ�ڵ�����������" << endl;
//				return false;
//			}
//			else
//			{
//				return true;
//			}
//		}
//
//		if (root->_col == BLACK)
//		{
//			++blackNum;// ��ɫ�ڵ���� + 1
//		}
//
//		if (root->_col == RED && root->_parent->_col == RED)
//		{
//			cout << "���������ĺ�ɫ�ڵ�" << endl;
//			return false;
//		}
//
//		return PrevCheck(root->_left, blackNum, benchmark)
//			&& PrevCheck(root->_right, blackNum, benchmark);
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
//		cout << root->_kv.first << ":" << root->_kv.second << endl;
//		_InOrder(root->_right);
//	}
//
//	// ����
//	void RotateL(Node* parent)
//	{
//		Node* subR = parent->_right;
//		Node* subRL = subR->_left;
//
//		parent->_right = subRL;
//		if (subRL)
//			subRL->_parent = parent;
//
//		Node* ppNode = parent->_parent;
//
//		subR->_left = parent;
//		parent->_parent = subR;
//
//		if (_root == parent)
//		{
//			_root = subR;
//			subR->_parent = nullptr;
//		}
//		else
//		{
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
//
//	}
//
//	// ����
//	void RotateR(Node* parent)
//	{
//		Node* subL = parent->_left;
//		Node* subLR = subL->_right;
//
//		parent->_left = subLR;
//		if (subLR)
//		{
//			subLR->_parent = parent;
//		}
//
//		Node* ppNode = parent->_parent;
//
//		subL->_right = parent;
//		parent->_parent = subL;
//
//		if (_root == parent)
//		{
//			_root = subL;
//			subL->_parent = nullptr;
//		}
//		else
//		{
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
//
//	}
//
//	// �����û��ƽ������,���Բ���Ҫ����дһ��˫���ĺ���,
//	// ���� �� ���� ����� �Ϳ��Դﵽ˫����Ч��
//private:
//	Node* _root = nullptr;
//};
//
//void TestRBTree1()
//{
//	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14, 0,5,30,25,20,4,13,30,28,27 };  // ����˫��ƽ�����ӵ���
//	//int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
//	RBTree<int, int> t1;
//	for (auto e : a)
//	{
//		t1.Insert(make_pair(e, e));
//	}
//
//	t1.InOrder();
//	cout << "IsBalance:" << t1.IsBalance() << endl;
//}
//
//void TestRBTree2()
//{
//	size_t N = 1000;
//	srand(time(0));
//	RBTree<int, int> t1;
//	for (size_t i = 0; i < N; ++i)
//	{
//		int x = rand();
//		//cout << "Insert:" << x << ":" << i << endl;
//		t1.Insert(make_pair(x, i));
//	}
//	cout << "IsBalance:" << t1.IsBalance() << endl;
//}