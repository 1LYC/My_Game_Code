#pragma once

#include "RBTree.h"

namespace bit
{
	template<class K>
	class set
	{
		// 为区分set和map的比较
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		// RBTree<K, K, SetKeyOfT>::iterator 这是一个类型
		typedef typename RBTree<K, K, SetKeyOfT>::iterator iterator;

		iterator begin()
		{
			return _t.begin();// 底层是调用红黑树的
		}

		iterator end()
		{
			return _t.end();// 底层是调用红黑树的
		}

		pair<iterator, bool> insert(const K& key)
		{
			return _t.Insert(key);// 底层是调用红黑树的
		}
	private:
		RBTree<K, K, SetKeyOfT> _t;
	};
}