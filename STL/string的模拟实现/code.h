#pragma once
#include <iostream>
#include <assert.h>
using namespace std;

namespace bit
{
	class string
	{
	public:
		// --------��������ʵ��-------
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
		// --------��������ʵ��-------

		// --------���캯����ʵ��-------
		// �����ʼ������Ϊnullptr,��Ϊ����c_str
		string(const char* str = "")
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity + 1];

			strcpy(_str, str);
		}
		// --------���캯����ʵ��-------

		// -------�������캯����ʵ��-------
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
			string tmp(s._str);// �����ȥ���ù��캯��
			swap(tmp); 
		}
		// -------�������캯����ʵ��-------

		// -------operator=��ʵ��-------
		// �����Ǵ�ֵ���Σ���ȥ���ÿ������캯��
		string& operator=(string s)
		{
			swap(s);
			return *this;
		}
		// -------operator=��ʵ��-------

		// -------����������ʵ��-------
		~string()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}
		// -------����������ʵ��-------

		// -------c_str��ʵ��-------
		const char* c_str() const
		{
			return _str;
		}
		// -------c_str��ʵ��-------

		// -------size��capacity��ʵ��-------
		size_t size() const
		{
			return _size;
		}
		size_t capacity() const
		{
			return _capacity;
		}
		// -------size��capacity��ʵ��-------

		// -------operator[]��ʵ��-------
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
		// -------operator[]��ʵ��-------
		
		// -------reserve��ʵ��-------
		// reserveֻ�ı�ռ�
		void reserve(size_t n)
		{
			if (n > _capacity)// �о�����û��ifҲ��
			{
				char* tmp = new char[n + 1];
				strcpy(tmp, _str);
				delete[] _str;

				_str = tmp;
				_capacity = n;
			}
		}
		// -------reserve��ʵ��-------

		// -------resize��ʵ��-------
		// resize ���ռ�ͳ�ʼ��
		void resize(size_t n, char ch = '\0')
		{
			if (n > _size)
			{
				// ��������
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
				// ɾ������
				_str[n] = '\0';
				_size = n;
			}
		}
		// -------resize��ʵ��-------
		
		// -------insert��ʵ��-------
		string& insert(size_t pos, char ch)
		{
			assert(pos <= _size);

			// ���˾�����
			if (_size == _capacity)
			{
				reserve(_capacity == 0 ? 4 : _capacity * 2);
			}

			// Ų������,��Ҫ�������������ͷ��
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

			// Ų������,��Ҫ�������������ͷ��
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
		// -------insert��ʵ��-------

		// -------erase��ʵ��-------
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
		// -------erase��ʵ��-------

		// -------push_back��append��ʵ��-------
		void push_back(char ch)
		{
			insert(_size, ch);
		}
		void append(const char* str)
		{
			insert(_size, str);
		}
		// -------push_back��append��ʵ��-------

		// -------operator+=��ʵ��-------
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
		// -------operator+=��ʵ��-------

		// -------clear��ʵ��-------
		void clear()
		{
			_str[0] = '\0';
			_size = 0;
		}
		// -------clear��ʵ��-------

		// -------find��ʵ��-------
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
			// strstr�ַ������ң��õ��Ǳ�������
			const char* ptr = strstr(_str + pos, sub);
			if (ptr == nullptr){
				return npos;
			}
			else{
				return ptr - _str;
			}
		}
		// -------find��ʵ��-------

		// -------substr��ʵ��-------
		string substr(size_t pos, size_t len = npos) const
		{
			assert(pos < _size);
			size_t realLen = len;
			if (len == npos || pos + len > _size)
			{
				realLen = _size - pos;// ������Χ
			}

			string sub;
			for (size_t i = 0; i < realLen; ++i)
			{
				sub += _str[pos + i];
			}

			return sub;
		}
		// -------substr��ʵ��-------

		// -------���ֱȽϵ�ʵ��-------
		// ֻ��Ҫʵ��������������ֱ�Ӹ���
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
		// -------���ֱȽϵ�ʵ��-------

	private:
		size_t _capacity;
		size_t _size;
		char* _str;
	public:
		// const static �﷨���⴦��
		const static size_t npos = -1;// �����Ƕ���
	};

	// -------operator<< &&operator >>��ʵ��-------
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
		s.clear();// ����ǰ��Ҫ���
		char ch;
		ch = in.get();// get�ܽ�' '��'\n'�ֿ�
		const size_t N = 32;
		char buff[N];
		size_t i = 0;
		// �Ƚ����ݷ���buff����ʱ���棬Ȼ���buff����֮����һ�����string��
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
		// ����ٴ���һ�£�buff�ռ��������(��ʱû����)
		buff[i] = '\0';
		s += buff;

		return in;
	}
	// -------operator<< &&operator >>��ʵ��-------
}