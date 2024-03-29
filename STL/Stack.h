#pragma once
#include <iostream>
#include <deque>
using namespace std;

namespace bit
{
	template<class T, class Container = deque<T>>
	class stack
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_back();
		}

		T& top()
		{
			return _con.back();
		}

		const T& top() const
		{
			return _con.back();
		}

		bool empty()  const
		{
			return _con.empty();
		}

		size_t size() const
		{
			return _con.size();
		}
	private:
		//vector<T> _con;
		Container _con;
	};
}