#pragma once
#include <iostream>
#include <deque>
using namespace std;

namespace bit
{
	template<class T, class Container = deque<T>>
	class queue
	{
	public:
		void push(const T& x)
		{
			_con.push_back(x);
		}

		void pop()
		{
			_con.pop_front();
		}

		T& back()
		{
			return _con.back();
		}

		T& front()
		{
			return _con.front();
		}

		const T& back() const
		{
			return _con.back();
		}

		const T& front() const
		{
			return _con.front();
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