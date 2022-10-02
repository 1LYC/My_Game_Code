#pragma once

#include <assert.h>
#include <list>
#include <iostream>
using namespace std;
#include "reverse_iterator.h"
namespace bit
{
	// --------链表节点-------
	template<class T>
	struct list_node
	{
		T _data;// 数据
		list_node<T>* _next;// 类的指针
		list_node<T>* _prev;// 类的指针

		// --------构造函数实现-------
		// T()是匿名对象,这里给的是缺省值,不传->将调用int的构造函数
		list_node(const T& x = T())
			:_data(x)
			, _next(nullptr)
			, _prev(nullptr)
		{}
		// --------构造函数实现-------
	};
	// --------链表节点-------

	// STL中是通过  类模板参数  来实现普通迭代器,和const迭代器
	// typedef __list_iterator<T, T&, T*>             iterator;
	// typedef __list_iterator<T, const T&, const T*> const_iterator;

	// --------迭代器实现-------
	template<class T, class Ref, class Ptr>
	struct __list_iterator
	{
		typedef list_node<T> Node;// 这个Node就是链表节点
		typedef __list_iterator<T, Ref, Ptr> iterator;// 这个iterator就是迭代器

		Node* _node;// 就是一个指向链表节点的指针
		
		// --------拷贝构造实现-------
		__list_iterator(Node* node)
			:_node(node)
		{}
		// --------拷贝构造实现-------
		
		// 前置++
		iterator& operator++()
		{
			_node = _node->_next;
			return *this;
		}

		// 后置++
		iterator operator++(int)
		{
			iterator tmp(*this);
			_node = _node->_next;
			return tmp;
		}

		// 前置--
		iterator& operator--()
		{
			_node = _node->_prev;
			return *this;
		}

		// 后置--
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
			return _node->_data;// 返回引用
		}

		//T* operator->() 
		Ptr operator->()
		{
			// 实际用的时候可能会省略一个->
			// return &(_node->_data),
			return &(operator*());// 返回指针
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
	// --------迭代器实现-------

	template<class T>
	class list
	{
		typedef list_node<T> Node;
	public:
		typedef __list_iterator<T, T&, T*> iterator;//T&是引用,T*是指针
		typedef __list_iterator<T, const T&, const T*> const_iterator;
		
		typedef __reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef __reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;
		
		// --------begin && end实现-------
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
		// --------begin && end实现-------
		
		// --------rbegin && rend实现-------
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		// --------begin && end实现-------

		// --------构造函数实现-------
		void empty_init()
		{
			// 创建并初始化哨兵位头结点
			_head = new Node;
			_head->_next = _head;
			_head->_prev = _head;
		}

		list()
		{
			empty_init();
		}
		// 迭代器区间构造
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
		// --------构造函数实现-------

		// --------拷贝构造函数实现-------
		list(const list<T>& lt)
		{
			empty_init();
			list<T> tmp(lt.begin(), lt.end());
			swap(tmp);
		}
		// --------拷贝构造函数实现-------

		// --------析构函数实现-------
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
		// --------析构函数实现-------
		
		// --------clear实现-------
		void clear()
		{
			iterator it = begin();
			while (it != end())
			{
				it = erase(it);
			}
		}
		// --------clear实现-------

		// --------operator=实现-------
		list<T>& operator=(list<T> lt)
		{
			swap(lt);
			return *this;
		}
		// --------operator=实现-------

		// --------swap实现-------
		void swap(list<T>& x)
		{
			std::swap(_head, x._head);
		}
		// --------swap实现-------

		// --------push_back && push_front实现-------
		void push_back(const T& x)
		{
			insert(end(), x);
		}
		void push_front(const T& x)
		{
			insert(begin(), x);
		}
		// --------push_back && push_front实现-------

		// --------insert实现-------
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
		// --------insert实现-------

		// --------pop_back && pop_front实现-------
		void pop_back()
		{
			erase(--end());
		}

		void pop_front()
		{
			erase(begin());
		}
		// --------pop_back && pop_front实现-------

		// --------erase函数实现-------
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
		// --------erase函数实现-------

	private:
		Node* _head;// 头节点
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