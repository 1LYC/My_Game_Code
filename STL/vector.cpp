#pragma once
#include <assert.h> 
#include <iostream>
using namespace std;

namespace bit
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		// ---------迭代器实现---------
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator begin() const
		{
			return _start;
		}
		const_iterator end() const
		{
			return _finish;
		}
		// ---------迭代器实现---------

		// -------构造函数实现---------
		vector()
			:_start(nullptr)// 如果不初始化,默认就是随机值,会出现野指针的情况
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{}

		// 通过迭代器区间,调用拷贝构造
		// int类型也可以当做模板参数,也有默认构造函数,
		template <class InputIterator>
		vector(InputIterator first, InputIterator last)
			: _start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		// 这里如果是vector v1(10,1),编译器会报错,
		// 10是int型,1也是int型,编译器会默认调用->迭代器区间的那个构造函数
		vector(size_t n, const T& val = T())
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				push_back(val);
			}
		}
		vector(int n, const T& val = T())
			:_start(nullptr)
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{
			reserve(n);
			for (size_t i = 0; i < n; ++i)
			{
				push_back(val);
			}
		}
		// -------构造函数实现---------
		
		// -------拷贝构造函数实现---------
		// 方案一:现代写法
		//vector(const vector<T>& v)
		//	:_start(nullptr)
		//	, _finish(nullptr)
		//	, _end_of_storage(nullptr)
		//{
		//	// 调用构造函数,间接实现拷贝构造
		//	vector<T> tmp(v.begin(), v.end());
		//	swap(tmp);
		//}
		// 方案二:传统写法
		vector(const vector<T>& v)
		{
			_start = new T[v.size()]; // v.capacity()也可以
			// 这里尽量不要使用memcpy,memcpy也是属于浅拷贝,
			// 防止出现vector <vector <int>> v1;需要调用拷贝构造返回的情况
			//memcpy(_start, v._start, sizeof(T)*v.size());
			for (size_t i = 0; i < v.size(); ++i)
			{
				_start[i] = v._start[i];// 直接一个一个的拷贝
			}
			_finish = _start + v.size();
			_end_of_storage = _start + v.size();
		}
		// -------拷贝构造函数实现---------
		
		// -------析构函数实现---------
		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}
		// -------析构函数实现---------

		// -------capacity实现---------
		size_t capacity() const
		{
			return _end_of_storage - _start;
		}
		// -------capacity实现---------
		
		// -------operator[]实现---------
		const T& operator[](size_t pos) const
		{
			assert(pos < size());

			return _start[pos];
		}
		T& operator[](size_t pos)
		{
			assert(pos < size());

			return _start[pos];
		}
		// -------operator[]实现---------

		// -------size实现---------
		size_t size() const
		{
			return _finish - _start;
		}
		// -------size实现---------

		// -------reserve实现---------
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				// 这里要先记录原来空间中元素的个数，防止迭代器失效的问题
				size_t sz = size();
				T* tmp = new T[n];
				if (_start)
				{
					// 这里尽量不要使用memcpy,memcpy也是属于浅拷贝,
					// 防止出现vector <vector <int>> v1;需要调用拷贝构造返回的情况
					//memcpy(tmp, _start, sizeof(T)*sz);
					for (size_t i = 0; i < sz; ++i)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}

				_start = tmp;
				_finish = _start + sz;// 防止迭代器失效的问题
				_end_of_storage = _start + n;// 防止迭代器失效的问题
			}
		}
		// -------reserve实现---------
		
		// -------resize实现---------
		void resize(size_t n, const T& val = T())
		{
			if (n > capacity())
			{
				// 开空间
				reserve(n);
			}

			if (n > size())
			{
				// 初始化填值
				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
			else
			{
				// 缩小空间
				_finish = _start + n;
			}
		}
		// -------resize实现---------

		// -------push_back实现---------
		void push_back(const T& x)
		{
			insert(end(), x);
		}
		// -------push_back实现---------

		// -------pop_back实现---------
		void pop_back()
		{
			assert(_finish > _start);
			--_finish;
		}
		// -------pop_back实现---------
		
		// -------swap实现---------
		void swap(vector<T>& v)
		{
			//调用库里面的swap
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}
		// -------swap实现---------

		// -------insert && erase实现---------
		// 补充：insert/erase pos位置，不要再次直接访问pos，
		// 可能出现各种出乎意料的结果，这就是所谓的迭代器失效
		iterator insert(iterator pos, const T& x)
		{
			assert(pos >= _start);
			assert(pos <= _finish);

			if (_finish == _end_of_storage)
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;// 更新pos
			}

			// 挪动数据
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = x;

			++_finish;
			return pos;// STL 规定erase返回删除位置下一个位置迭代器
		}

		iterator erase(iterator pos)
		{
			assert(pos >= _start);
			assert(pos < _finish);

			iterator begin = pos + 1;
			while (begin < _finish)
			{
				*(begin - 1) = *begin;
				++begin;
			}
			--_finish;
			return pos;// STL 规定erase返回删除位置下一个位置迭代器
		}
		// -------insert && erase实现---------
		
		// -------operator=实现---------
		// 注意这里是传值传参,所以v的改变不会影响实参
		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}
		// -------operator=实现---------

		// -------front && back实现---------
		T& front()
		{
			assert(size() > 0);

			return *_start;
		}

		T& back()
		{
			assert(size() > 0);

			return *(_finish - 1);
		}
		// -------front && back实现---------

	private:
		iterator _start;// 第一个元素
		iterator _finish;// 最后一个元素的下一个
		iterator _end_of_storage;// 存储容量
	};
}

int main()
{
	bit::vector<int> v1;
	v1.push_back(1);
	bit::vector<int> v2;
	v2.push_back(2);
	v1 = v2;
	//v1.swap(v2);
	cout << v1[0] << endl;
	cout << v2[0] << endl;
	return 0; 
}