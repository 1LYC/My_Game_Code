#pragma once

#include <assert.h>
#include <list>
#include <iostream>
using namespace std;
#include "reverse_iterator.h"
namespace bit
{
	// --------����ڵ�-------
	template<class T>
	struct list_node
	{
		T _data;// ����
		list_node<T>* _next;// ���ָ��
		list_node<T>* _prev;// ���ָ��

		// --------���캯��ʵ��-------
		// T()����������,���������ȱʡֵ,����->������int�Ĺ��캯��
		list_node(const T& x = T())
			:_data(x)
			, _next(nullptr)
			, _prev(nullptr)
		{}
		// --------���캯��ʵ��-------
	};
	// --------����ڵ�-------

	// STL����ͨ��  ��ģ�����  ��ʵ����ͨ������,��const������
	// typedef __list_iterator<T, T&, T*>             iterator;
	// typedef __list_iterator<T, const T&, const T*> const_iterator;

	// --------������ʵ��-------
	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef list_node<T> Node;// ���Node��������ڵ�
		typedef __list_iterator<T, Ref, Ptr> iterator;// ���iterator���ǵ�����

		Node* _node;// ����һ��ָ������ڵ��ָ��
		
		// --------��������ʵ��-------
		__list_iterator(Node* node)
			:_node(node)
		{}
		// --------��������ʵ��-------
		
		// ǰ��++
		iterator& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		// ����++
		iterator operator++(int)
		{
			iterator tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		// ǰ��--
		iterator& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		// ����--
		iterator operator--(int)
		{
			iterator tmp(*this);
			_node = _node->_prev;
			return tmp;
		}

		// const T& operator*()
		// T& operator*()
		Ref operator*()
		{
			return _node->_data;// ��������
		}

		//T* operator->() 
		Ptr operator->()
		{
			// ʵ���õ�ʱ����ܻ�ʡ��һ��->
			// return &(_node->_data),
			return &(operator*());// ����ָ��
		}

		bool operator!=(const iterator& it) const
		{
			return _node != it._node;
		}

		bool operator==(const iterator& it) const
		{
			return _node == it._node;
		}
	};
	// --------������ʵ��-------

	template<class T>
	class list
	{
		typedef list_node<T> Node;
	public:
		typedef __list_iterator<T, T&, T*> iterator;//T&������,T*��ָ��
		typedef __list_iterator<T, const T&, const T*> const_iterator;
		
		typedef __reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef __reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
		
		// --------begin && endʵ��-------
		const_iterator begin() const
		{
			return const_iterator(_head->_next);
		}

		const_iterator end() const
		{
			return const_iterator(_head);
		}

		iterator begin()
		{
			/*iterator ret(_head->_next);
			return ret;*/
			return iterator(_head->_next);
		}

		iterator end()
		{
			return iterator(_head);
		}
		// --------begin && endʵ��-------
		
		// --------rbegin && rendʵ��-------
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		// --------begin && endʵ��-------

		// --------���캯��ʵ��-------
		void empty_init()
		{
			// ��������ʼ���ڱ�λͷ���
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		list()
		{
			empty_init();
		}
		// ���������乹��
		template <class InputIterator>
		list(InputIterator first, InputIterator last)
		{
			empty_init();

			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		// --------���캯��ʵ��-------

		// --------�������캯��ʵ��-------
		list(const list<T>& lt)
		{
			empty_init();
			list<T> tmp(lt.begin(), lt.end());
			swap(tmp);
		}
		// --------�������캯��ʵ��-------

		// --------��������ʵ��-------
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
		// --------��������ʵ��-------
		
		// --------clearʵ��-------
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}
		// --------clearʵ��-------

		// --------operator=ʵ��-------
		list<T>& operator=(list<T> lt)
		{
			swap(lt);
			return *this;
		}
		// --------operator=ʵ��-------

		// --------swapʵ��-------
		void swap(list<T>& x)
		{
			std::swap(_head, x._head);
		}
		// --------swapʵ��-------

		// --------push_back && push_frontʵ��-------
		void push_back(const T& x)
		{
			insert(end(), x);
		}
		void push_front(const T& x)
		{
			insert(begin(), x);
		}
		// --------push_back && push_frontʵ��-------

		// --------insertʵ��-------
		iterator insert(iterator pos, const T& x)
		{
			Node* cur = pos._node;
			Node* prev = cur->_prev;

			Node* newnode = new Node(x);

			// prev newnode cur
			prev->_next = newnode;
			newnode->_prev = prev;
			newnode->_next = cur;
			cur->_prev = newnode;

			return iterator(newnode);
		}
		// --------insertʵ��-------

		// --------pop_back && pop_frontʵ��-------
		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}
		// --------pop_back && pop_frontʵ��-------

		// --------erase����ʵ��-------
		iterator erase(iterator pos)
		{
			assert(pos != end());

			Node* cur = pos._node;
			Node* prev = cur->_prev;
			Node* next = cur->_next;

			prev->_next = next;
			next->_prev = prev;
			delete cur;

			return iterator(next);
		}
		// --------erase����ʵ��-------

	private:
		Node* _head;// ͷ�ڵ�
	};

	void test1()
	{
		list <int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		auto begin = lt.rbegin();
		while (begin != lt.rend())
		{
			cout << *begin << " ";
			begin++;
		}
		cout << endl;

		auto pos = lt.rbegin();
		auto pos1 = pos++;
		cout << *pos1 << endl;
		cout << *pos << endl;

		auto pos2 = ++pos;
		cout << *pos2 << endl;
		cout << *pos << endl;

	}

	void test2()
	{
		list <int> lt;
		lt.push_back(1);
		lt.push_back(2);
		lt.push_back(3);
		auto begin = lt.begin();
		while (begin != lt.end())
		{
			cout << *begin << " ";
			begin++;
		}
		cout << endl;

		auto pos = lt.begin();
		auto pos1 = pos++;
		cout << *pos1 << endl;
		cout << *pos << endl;

		auto pos2 = ++pos;
		cout << *pos2 << endl;
		cout << *pos << endl;
	}
}