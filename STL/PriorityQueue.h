#pragma once
#include <iostream>
#include <deque>
#include <vector>
using namespace std;

namespace bit
{
	// Compare���бȽϵķº��� less->���
	// Compare���бȽϵķº��� greater->С��
	template<class T, class Container = vector<T>, class Compare = std::less<T>>
	class priority_queue
	{
	public:
		// --------���캯��ʵ��-------
		template <class InputIterator>
		priority_queue(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				_con.push_back(*first);
				++first;
			}
			// ���� - �����һ����Ҷ�ӽڵ㿪ʼ
			for (int i = (_con.size() - 1 - 1) / 2; i >= 0; --i)
			{
				adjust_down(i);// �����µ����㷨��ʱ�临�Ӷ���O(N)
			}
		}
		// --------���캯��ʵ��-------

		// --------adjust_upʵ��-------
		void adjust_up(size_t child)
		{
			Compare com;
			size_t parent = (child - 1) / 2;
			while (child > 0)
			{
				//if (_con[parent] < _con[child])
				if (com(_con[parent], _con[child]))
				{
					std::swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
			}
		}
		// --------adjust_upʵ��-------

		// --------adjust_downʵ��-------
		void adjust_down(size_t parent)
		{
			Compare com;
			size_t child = parent * 2 + 1;// Ĭ��������
			while (child < _con.size())
			{
				// ѡ�����Һ����д����һ��
				//if (child + 1 < _con.size() && _con[child] < _con[child + 1])
				if (child + 1 < _con.size() && com(_con[child], _con[child + 1]))
				{
					++child;
				}

				//if (_con[parent] < _con[child])
				if (com(_con[parent], _con[child]))
				{
					std::swap(_con[child], _con[parent]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
				{
					break;
				}
			}
		}
		// --------adjust_downʵ��-------

		// --------push && popʵ��-------
		void push(const T& x)
		{
			_con.push_back(x);
			adjust_up(_con.size() - 1);// �������ϵ����㷨
		}
		void pop()
		{
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();// �������µ����㷨
			adjust_down(0);
		}
		// --------push && popʵ��-------

		// --------topʵ��-------
		const T& top()
		{
			return _con[0];
		}
		// --------topʵ��-------
		
		// --------emptyʵ��-------
		bool empty()  const
		{
			return _con.empty();
		}
		// --------emptyʵ��-------
		
		// --------sizeʵ��-------
		size_t size() const
		{
			return _con.size();
		}
		// --------sizeʵ��-------

	private:
		Container _con;
	};
}