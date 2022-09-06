#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

namespace bit
{
	class string
	{
	public:
		// --------迭代器的实现-------
		typedef char* iterator;
		typedef const char* const_iterator;
		iterator begin()
		{
			return _str;
		}
		iterator end()
		{
			return _str + _size;
		}
		const_iterator begin() const
		{
			return _str;
		}
		const_iterator end() const
		{
			return _str + _size;
		}
		// --------迭代器的实现-------

		// --------构造函数的实现-------
		// 这里初始化不能为nullptr,因为存在c_str
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];

			strcpy(_str, str);
		}
		// --------构造函数的实现-------

		// -------拷贝构造函数的实现-------
		void swap(string& tmp)
		{
			::swap(_str, tmp._str);
			::swap(_size, tmp._size);
			::swap(_capacity, tmp._capacity);
		}
		string(const string& s)
			:_str(nullptr)
			, _size(0)
			, _capacity(0)
		{
			string tmp(s._str);// 这里会去调用构造函数
			swap(tmp); 
		}
		// -------拷贝构造函数的实现-------

		// -------operator=的实现-------
		// 这里是传值传参，会去调用拷贝构造函数
		string& operator=(string s)
		{
			swap(s);
			return *this;
		}
		// -------operator=的实现-------

		// -------析构函数的实现-------
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		// -------析构函数的实现-------

		// -------c_str的实现-------
		const char* c_str() const
		{
			return _str;
		}
		// -------c_str的实现-------

		// -------size和capacity的实现-------
		size_t size() const
		{
			return _size;
		}
		size_t capacity() const
		{
			return _capacity;
		}
		// -------size和capacity的实现-------

		// -------operator[]的实现-------
		const char& operator[](size_t pos) const
		{
			assert(pos < _size);

			return _str[pos];
		}

		char& operator[](size_t pos)
		{
			assert(pos < _size);

			return _str[pos];
		}
		// -------operator[]的实现-------
		
		// -------reserve的实现-------
		// reserve只改变空间
		void reserve(size_t n)
		{
			if (n > _capacity)// 感觉这里没有if也行
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;

				_str = tmp;
				_capacity = n;
			}
		}
		// -------reserve的实现-------

		// -------resize的实现-------
		// resize 开空间和初始化
		void resize(size_t n, char ch = '\0')
		{
			if (n > _size)
			{
				// 插入数据
				reserve(n);
				for (size_t i = _size; i < n; ++i)
				{
					_str[i] = ch;
				}
				_str[n] = '\0';
				_size = n;
			}
			else
			{
				// 删除数据
				_str[n] = '\0';
				_size = n;
			}
		}
		// -------resize的实现-------
		
		// -------insert的实现-------
		string& insert(size_t pos, char ch)
		{
			assert(pos <= _size);

			// 满了就扩容
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}

			// 挪动数据,需要考虑特殊情况：头插
			size_t end = _size + 1;
			while (end > pos)
			{
				_str[end] = _str[end - 1];
				--end;
			}
			_str[pos] = ch;
			++_size;
			return *this;
		}
		string& insert(size_t pos, const char* str)
		{
			assert(pos <= _size);
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}

			// 挪动数据,需要考虑特殊情况：头插
			size_t end = _size + len;
			while (end >= pos + len)
			{
				_str[end] = _str[end - len];
				--end;
			}

			strncpy(_str + pos, str, len);
			_size += len;

			return *this;
		}
		// -------insert的实现-------

		// -------erase的实现-------
		void erase(size_t pos, size_t len = npos)
		{
			assert(pos < _size);

			if (len == npos || pos + len >= _size)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				strcpy(_str + pos, _str + pos + len);
				_size -= len;
			}
		}
		// -------erase的实现-------

		// -------push_back和append的实现-------
		void push_back(char ch)
		{
			insert(_size, ch);
		}
		void append(const char* str)
		{
			insert(_size, str);
		}
		// -------push_back和append的实现-------

		// -------operator+=的实现-------
		string& operator+=(char ch)
		{
			push_back(ch);
			return *this;
		}
		string& operator+=(const char* str)
		{
			append(str);
			return *this;
		}
		// -------operator+=的实现-------

		// -------clear的实现-------
		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}
		// -------clear的实现-------

		// -------find的实现-------
		size_t find(char ch, size_t pos = 0) const
		{
			assert(pos < _size);
			for (size_t i = pos; i < _size; ++i)
			{
				if (ch == _str[i])
				{
					return i;
				}
			}
			return npos;
		}
		size_t find(const char* sub, size_t pos = 0) const
		{
			assert(sub);
			assert(pos < _size);

			// kmp/bm
			// strstr字符串查找，用的是暴力查找
			const char* ptr = strstr(_str + pos, sub);
			if (ptr == nullptr){
				return npos;
			}
			else{
				return ptr - _str;
			}
		}
		// -------find的实现-------

		// -------substr的实现-------
		string substr(size_t pos, size_t len = npos) const
		{
			assert(pos < _size);
			size_t realLen = len;
			if (len == npos || pos + len > _size)
			{
				realLen = _size - pos;// 调整范围
			}

			string sub;
			for (size_t i = 0; i < realLen; ++i)
			{
				sub += _str[pos + i];
			}

			return sub;
		}
		// -------substr的实现-------

		// -------各种比较的实现-------
		// 只需要实现两个，其他的直接复用
		bool operator>(const string& s) const
		{
			return strcmp(_str, s._str) > 0;
		}

		bool operator==(const string& s) const
		{
			return strcmp(_str, s._str) == 0;
		}

		bool operator>=(const string& s) const
		{
			return *this > s || *this == s;
		}

		bool operator<=(const string& s) const
		{
			return !(*this > s);
		}

		bool operator<(const string& s) const
		{
			return !(*this >= s);
		}

		bool operator!=(const string& s) const
		{
			return !(*this == s);
		}
		// -------各种比较的实现-------

	private:
		size_t _capacity;
		size_t _size;
		char* _str;
	public:
		// const static 语法特殊处理
		const static size_t npos = -1;// 这里是定义
	};

	// -------operator<< &&operator >>的实现-------
	ostream& operator<<(ostream& out, const string& s)
	{
		for (size_t i = 0; i < s.size(); ++i)
		{
			out << s[i];
		}

		return out;
	}

	istream& operator>>(istream& in, string& s)
	{
		s.clear();// 输入前需要清空
		char ch;
		ch = in.get();// get能将' '和'\n'分开
		const size_t N = 32;
		char buff[N];
		size_t i = 0;
		// 先将数据放在buff中临时保存，然后等buff满了之后，再一起放入string中
		while (ch != ' ' && ch != '\n')
		{
			buff[i++] = ch;
			if (i == N - 1)
			{
				buff[i] = '\0';
				s += buff;
				i = 0;
			}
			ch = in.get();
		}
		// 最后再处理一下，buff空间里的数据(此时没有满)
		buff[i] = '\0';
		s += buff;

		return in;
	}
	// -------operator<< &&operator >>的实现-------
}