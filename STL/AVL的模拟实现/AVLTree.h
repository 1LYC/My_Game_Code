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
//	// ����������: ����_parent�Ļ�,�������ƽ������,������������ת�ĸ��Ӷ�
//	AVLTreeNode<K, V>* _left;
//	AVLTreeNode<K, V>* _right;
//	AVLTreeNode<K, V>* _parent;
//
//	pair<K, V> _kv;
//	// ƽ�����Ӳ��Ǳ����
//	int _bf;  // ƽ������ = (���ڸ����������ͼ�1) + (���ڸ����������ͼ�-1);
//
//	// -------���캯��-------
//	AVLTreeNode(const pair<K, V>& kv)
//		:_left(nullptr)
//		, _right(nullptr)
//		, _parent(nullptr)
//		, _kv(kv)
//		, _bf(0)
//	{}
//	// -------���캯��-------
//};
//
//template<class K, class V>
//struct AVLTree
//{
//	typedef AVLTreeNode<K, V> Node;
//public:
//	bool Insert(const pair<K, V>& kv)
//	{
//		// step1: �Ҳ����λ��
//		if (_root == nullptr)
//		{
//			_root = new Node(kv);
//			return true;
//		}
//
//		Node* parent = nullptr;// Ϊ���ҵ�֮��,������ȥ
//		Node* cur = _root;
//		while (cur)
//		{
//			// cur->_kv.first ��ʾ��ǰ�ڵ��key,
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
//				// ����������ͬ��
//				return false;
//			}
//		}
//		// curΪ��,����һ���½ڵ�,Ȼ��������ȥ
//		// parentֻ�Ǽ�¼��cur����һ���ڵ�,������ȷ�������� ������� ���� �����ұ�
//		cur = new Node(kv);
//		if (parent->_kv.first < kv.first)
//		{
//			parent->_right = cur;
//		}
//		else
//		{
//			parent->_left = cur;
//		}
//		cur->_parent = parent;// �ǵø����½ڵ��_parent
//
//		// step2:����ƽ������ + ����ƽ��
//		while (parent)
//		{
//			// step2.1: ��������parent->bf++,��������parent->bf--
//			if (cur == parent->_right)
//			{
//				parent->_bf++;
//			}
//			else
//			{
//				parent->_bf--;
//			}
//
//			// step2.3:���º�prent->bf == 0,
//			// ˵������ǰ:parent��ƽ��������1 or -1,��������һ�߸�һ�ߵ�
//			//	   �����:����һ����,����������˰����Ǳ�,parent���������ĸ߶Ȳ���,
//			//	   ����Ҫ�������ϸ���
//			if (parent->_bf == 0)
//			{
//				break;
//			}
//
//			// step2.2:���º�parent->bf == 1 or -1,
//			// ˵������ǰ: parent��ƽ��������0,˵�����������߶����,
//			//     �����: ��һ�߸���,��parent�ĸ߶ȱ���
//			//     ��Ҫ�������ϸ���
//			else if (abs(parent->_bf) == 1)
//			{
//				parent = parent->_parent;
//				cur = cur->_parent;
//			}
//
//			// step2.4:���º�,parent->bf == 2 of -2
//			// ˵������ǰ: parent��ƽ��������1 or -1,�Ѿ�����ƽ���ٽ�ֵ,
//			//	   �����: ���2 or -2,����ƽ��,parent����������Ҫ��ת����
//			//	   ����Ҫ�������ϸ���
//			else if (abs(parent->_bf) == 2)
//			{
//				// step3: ˵��parent���������Ѿ���ƽ���ˣ���Ҫ��ת����
//				if (parent->_bf == 2 && cur->_bf == 1)
//				{
//					// step3.1: �½ڵ����ϸ����������Ҳ�--����: ����
//					RotateL(parent);
//				}
//				else if ((parent->_bf == -2 && cur->_bf == -1))
//				{
//					// step3.2: �½ڵ����ϸ������������--����: �ҵ���
//					RotateR(parent);
//				}
//				else if (parent->_bf == -2 && cur->_bf == 1)
//				{
//					// step3.3: ����˫��ת�����
//					RotateLR(parent);
//				}
//				else if (parent->_bf == 2 && cur->_bf == -1)
//				{
//					// step3.4: ����˫��ת�����
//					RotateRL(parent);
//				}
//				else
//				{
//					assert(false);// ֱ�Ӷ���
//				}
//
//				break;
//			}
//			// step2.5:���º�:parent->bf > 2 or < -2��ֵ,
//			// ������,�������,��˵������ǰ�Ͳ���AVL��,��Ҫȥ���֮ǰ�Ĳ���������
//			else
//			{
//				assert(false);// ֱ�Ӷ���
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
//	// ��Ϊ�����������,������ת������һ�㸴��
//	void RotateL(Node* parent)
//	{
//		// Ϊ���������¼һ�½ڵ�
//		Node* subR = parent->_right;
//		Node* subRL = subR->_left;
//
//		parent->_right = subRL;
//		// ע��: subRl�����ǿ�����
//		if (subRL)
//			subRL->_parent = parent;
//
//		Node* ppNode = parent->_parent;// ��¼һ��
//
//		subR->_left = parent;
//		parent->_parent = subR;
//		
//		// parent�����Ǹ��ڵ�,Ҳ�����Ǹ�������
//		if (_root == parent)
//		{
//			_root = subR;
//			subR->_parent = nullptr;
//		}
//		else
//		{
//			// ppNodeֻ�Ǽ�¼��parent����һ��,��ȷ��parent�Ƿ�����������
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
//		// ����ٸ���һ��ƽ������
//		subR->_bf = parent->_bf = 0;
//	}
//
//	void RotateR(Node* parent)
//	{
//		// Ϊ���������¼һ�½ڵ�
//		Node* subL = parent->_left;
//		Node* subLR = subL->_right;
//
//		parent->_left = subLR;
//		// ע��: subRl�����ǿ�����
//		if (subLR){
//			subLR->_parent = parent;
//		}
//
//		Node* ppNode = parent->_parent;// ��¼һ��
//
//		subL->_right = parent;
//		parent->_parent = subL;
//
//		// parent�����Ǹ��ڵ�,Ҳ�����Ǹ�������
//		if (_root == parent)
//		{
//			_root = subL;
//			subL->_parent = nullptr;
//		}
//		else
//		{
//			// ppNodeֻ�Ǽ�¼��parent����һ��,��ȷ��parent�Ƿ�����������
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
//		// ����ٸ���һ��ƽ������
//		subL->_bf = parent->_bf = 0;
//	}
//
//	void RotateLR(Node* parent)
//	{
//		// ƽ�����ӵĸı��е���
//		Node* subL = parent->_left;
//		Node* subLR = subL->_right;
//		int bf = subLR->_bf;// ���ƽ��������Ҫ��¼
//
//		RotateL(parent->_left);// ������
//		RotateR(parent);// ������
//
//		subLR->_bf = 0;// �������Ǹ��ڵ�,��Ϊ�Ѿ���ת��,����Ϊ0
//		if (bf == 1)
//		{
//			parent->_bf = 0;
//			subL->_bf = -1;
//		}
//		else if (bf == -1)
//		{
//			// ���
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
//		// root->_kv.first��key,root->second��value
//		cout << root->_kv.first << ":" << root->_kv.second << endl;
//		_InOrder(root->_right);
//	}
//
//	// ��һ���ڵ�ĸ߶�,Ҳ������һ���������
//	int Height(Node* root)
//	{
//		if (root == nullptr)
//			return 0;
//
//		return max(Height(root->_left), Height(root->_right)) + 1;
//	}
//
//	// �ж��Ƿ�����߶�ƽ�������������
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
//		int diff = rightHT - leftHT;// �õ�ƽ������
//
//		if (diff != root->_bf)
//		{
//			cout << root->_kv.first << "ƽ�������쳣" << endl;
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
//	//int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };  // ����˫��ƽ�����ӵ���
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
//	// ʹ����������м��
//	size_t N = 10000;
//	srand(time(0));// ��C������ֻ�ܲ���3��������,�ٶ�����ظ�����
//	AVLTree<int, int> t1;
//	// �����ע�͵�Ŀ����: ������,�����ƽ������������,��������Ĵ���,���е���
//	for (size_t i = 0; i < N; ++i)
//	{
//		int x = rand();
//		/*if (x = ĳ����) {
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