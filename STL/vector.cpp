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
		// ---------������ʵ��---------
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
		// ---------������ʵ��---------

		// -------���캯��ʵ��---------
		vector()
			:_start(nullptr)// �������ʼ��,Ĭ�Ͼ������ֵ,�����Ұָ������
			, _finish(nullptr)
			, _end_of_storage(nullptr)
		{}

		// ͨ������������,���ÿ�������
		// int����Ҳ���Ե���ģ�����,Ҳ��Ĭ�Ϲ��캯��,
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

		// ���������vector v1(10,1),�������ᱨ��,
		// 10��int��,1Ҳ��int��,��������Ĭ�ϵ���->������������Ǹ����캯��
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
		// -------���캯��ʵ��---------
		
		// -------�������캯��ʵ��---------
		// ����һ:�ִ�д��
		//vector(const vector<T>& v)
		//	:_start(nullptr)
		//	, _finish(nullptr)
		//	, _end_of_storage(nullptr)
		//{
		//	// ���ù��캯��,���ʵ�ֿ�������
		//	vector<T> tmp(v.begin(), v.end());
		//	swap(tmp);
		//}
		// ������:��ͳд��
		vector(const vector<T>& v)
		{
			_start = new T[v.size()]; // v.capacity()Ҳ����
			// ���ﾡ����Ҫʹ��memcpy,memcpyҲ������ǳ����,
			// ��ֹ����vector <vector <int>> v1;��Ҫ���ÿ������췵�ص����
			//memcpy(_start, v._start, sizeof(T)*v.size());
			for (size_t i = 0; i < v.size(); ++i)
			{
				_start[i] = v._start[i];// ֱ��һ��һ���Ŀ���
			}
			_finish = _start + v.size();
			_end_of_storage = _start + v.size();
		}
		// -------�������캯��ʵ��---------
		
		// -------��������ʵ��---------
		~vector()
		{
			delete[] _start;
			_start = _finish = _end_of_storage = nullptr;
		}
		// -------��������ʵ��---------

		// -------capacityʵ��---------
		size_t capacity() const
		{
			return _end_of_storage - _start;
		}
		// -------capacityʵ��---------
		
		// -------operator[]ʵ��---------
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
		// -------operator[]ʵ��---------

		// -------sizeʵ��---------
		size_t size() const
		{
			return _finish - _start;
		}
		// -------sizeʵ��---------

		// -------reserveʵ��---------
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				// ����Ҫ�ȼ�¼ԭ���ռ���Ԫ�صĸ�������ֹ������ʧЧ������
				size_t sz = size();
				T* tmp = new T[n];
				if (_start)
				{
					// ���ﾡ����Ҫʹ��memcpy,memcpyҲ������ǳ����,
					// ��ֹ����vector <vector <int>> v1;��Ҫ���ÿ������췵�ص����
					//memcpy(tmp, _start, sizeof(T)*sz);
					for (size_t i = 0; i < sz; ++i)
					{
						tmp[i] = _start[i];
					}
					delete[] _start;
				}

				_start = tmp;
				_finish = _start + sz;// ��ֹ������ʧЧ������
				_end_of_storage = _start + n;// ��ֹ������ʧЧ������
			}
		}
		// -------reserveʵ��---------
		
		// -------resizeʵ��---------
		void resize(size_t n, const T& val = T())
		{
			if (n > capacity())
			{
				// ���ռ�
				reserve(n);
			}

			if (n > size())
			{
				// ��ʼ����ֵ
				while (_finish < _start + n)
				{
					*_finish = val;
					++_finish;
				}
			}
			else
			{
				// ��С�ռ�
				_finish = _start + n;
			}
		}
		// -------resizeʵ��---------

		// -------push_backʵ��---------
		void push_back(const T& x)
		{
			insert(end(), x);
		}
		// -------push_backʵ��---------

		// -------pop_backʵ��---------
		void pop_back()
		{
			assert(_finish > _start);
			--_finish;
		}
		// -------pop_backʵ��---------
		
		// -------swapʵ��---------
		void swap(vector<T>& v)
		{
			//���ÿ������swap
			std::swap(_start, v._start);
			std::swap(_finish, v._finish);
			std::swap(_end_of_storage, v._end_of_storage);
		}
		// -------swapʵ��---------

		// -------insert && eraseʵ��---------
		// ���䣺insert/erase posλ�ã���Ҫ�ٴ�ֱ�ӷ���pos��
		// ���ܳ��ָ��ֳ������ϵĽ�����������ν�ĵ�����ʧЧ
		iterator insert(iterator pos, const T& x)
		{
			assert(pos >= _start);
			assert(pos <= _finish);

			if (_finish == _end_of_storage)
			{
				size_t len = pos - _start;
				reserve(capacity() == 0 ? 4 : capacity() * 2);
				pos = _start + len;// ����pos
			}

			// Ų������
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = x;

			++_finish;
			return pos;// STL �涨erase����ɾ��λ����һ��λ�õ�����
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
			return pos;// STL �涨erase����ɾ��λ����һ��λ�õ�����
		}
		// -------insert && eraseʵ��---------
		
		// -------operator=ʵ��---------
		// ע�������Ǵ�ֵ����,����v�ĸı䲻��Ӱ��ʵ��
		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}
		// -------operator=ʵ��---------

		// -------front && backʵ��---------
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
		// -------front && backʵ��---------

	private:
		iterator _start;// ��һ��Ԫ��
		iterator _finish;// ���һ��Ԫ�ص���һ��
		iterator _end_of_storage;// �洢����
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