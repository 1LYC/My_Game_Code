#pragma once

#include "RBTree.h"

namespace bit
{
	template<class K, class V>
	class map
	{
		// 为区分set和map的比较
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;// map的比较是比较key
			}
		};
	public:
		// RBTree<K, pair<K, V>, MapKeyOfT>::iterator 是一个类型
		typedef typename RBTree<K, pair<K, V>, MapKeyOfT>::iterator iterator;

		iterator begin()
		{
			return _t.begin();// 底层是调用红黑树的
		}

		iterator end()
		{
			return _t.end();// 底层是调用红黑树的
		}

		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);// 底层是调用红黑树的
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = insert(make_pair(key, V()));
			return ret.first->second;
		}
	private:
		
		RBTree<K, pair<K, V>, MapKeyOfT> _t;
	};
}