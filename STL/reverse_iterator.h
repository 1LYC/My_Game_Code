#pragma once

namespace bit
{
	// --------���������ʵ��-------
	// �������ĺ��ľ���: ����
	template<class Iterator, class Ref, class Ptr>
	struct __reverse_iterator
	{
		Iterator _cur;// ������
		typedef __reverse_iterator<Iterator, Ref, Ptr> RIterator;// RIterator�������������
		
		// --------��������ʵ��-------
		__reverse_iterator(Iterator it)
			:_cur(it)
		{}
		// --------��������ʵ��-------

		// ǰ��++
		RIterator operator++()
		{
			--_cur;
			return *this;
		}

		// ����++
		RIterator operator++(int)
		{
			RIterator tmp(_cur);
			--_cur;
			return tmp;
		}

		// ǰ��--
		RIterator operator--()
		{
			++_cur;
			return *this;
		}

		// ����--
		RIterator operator--()
		{
			RIterator tmp(_cur);
			++_cur;
			return tmp;
		}

		// �ڿ������rbegin() = end(),rend() = begin(),���ǶԳ���Ƶ�
		Ref operator*()
		{
			//return *_cur;
			auto tmp = _cur;
			--tmp;
			return *tmp;
		}

		Ptr operator->()
		{
			//return _cur.operator->();
			return &(operator*());
		}

		bool operator!=(const RIterator& it) const
		{
			return _cur != it._cur;
		}

		bool operator==(const RIterator& it) const
		{
			return _cur == it._cur;
		}
	};
	// --------���������ʵ��-------
}