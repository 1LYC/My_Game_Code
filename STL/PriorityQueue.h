#pragma once
#include <iostream>
#include <deque>
#include <vector>
using namespace std;

namespace bit
{
	// Compare进行比较的仿函数 less->大堆
	// Compare进行比较的仿函数 greater->小堆
	template<class T, class Container = vector<T>, class Compare = std::less<T>>
	class priority_queue
	{
	public:
		// --------构造函数实现-------
		template <class InputIterator>
		priority_queue(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				_con.push_back(*first);
				++first;
			}
			// 建堆 - 从最后一个非叶子节点开始
			for (int i = (_con.size() - 1 - 1) / 2; i >= 0; --i)
			{
				adjust_down(i);// 用向下调整算法的时间复杂度是O(N)
			}
		}
		// --------构造函数实现-------

		// --------adjust_up实现-------
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
		// --------adjust_up实现-------

		// --------adjust_down实现-------
		void adjust_down(size_t parent)
		{
			Compare com;
			size_t child = parent * 2 + 1;// 默认是左孩子
			while (child < _con.size())
			{
				// 选出左右孩子中大的那一个
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
		// --------adjust_down实现-------

		// --------push && pop实现-------
		void push(const T& x)
		{
			_con.push_back(x);
			adjust_up(_con.size() - 1);// 调用向上调整算法
		}
		void pop()
		{
			std::swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();// 调用向下调整算法
			adjust_down(0);
		}
		// --------push && pop实现-------

		// --------top实现-------
		const T& top()
		{
			return _con[0];
		}
		// --------top实现-------
		
		// --------empty实现-------
		bool empty()  const
		{
			return _con.empty();
		}
		// --------empty实现-------
		
		// --------size实现-------
		size_t size() const
		{
			return _con.size();
		}
		// --------size实现-------

	private:
		Container _con;
	};
}