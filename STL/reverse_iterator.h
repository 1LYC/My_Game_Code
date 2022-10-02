#pragma once

namespace bit
{
	// --------反向迭代器实现-------
	// 适配器的核心就是: 复用
	template<class Iterator, class Ref, class Ptr>
	struct __reverse_iterator
	{
		Iterator _cur;// 迭代器
		typedef __reverse_iterator<Iterator, Ref, Ptr> RIterator;// RIterator反向迭代器类型
		
		// --------拷贝构造实现-------
		__reverse_iterator(Iterator it)
			:_cur(it)
		{}
		// --------拷贝构造实现-------

		// 前置++
		RIterator operator++()
		{
			--_cur;
			return *this;
		}

		// 后置++
		RIterator operator++(int)
		{
			RIterator tmp(_cur);
			--_cur;
			return tmp;
		}

		// 前置--
		RIterator operator--()
		{
			++_cur;
			return *this;
		}

		// 后置--
		RIterator operator--()
		{
			RIterator tmp(_cur);
			++_cur;
			return tmp;
		}

		// 在库里面的rbegin() = end(),rend() = begin(),它是对称设计的
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
	// --------反向迭代器实现-------
}