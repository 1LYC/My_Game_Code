#pragma once

#include "RBTree.h"

namespace bit
{
	template<class K, class V>
	class map
	{
		// Ϊ����set��map�ıȽ�
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;// map�ıȽ��ǱȽ�key
			}
		};
	public:
		// RBTree<K, pair<K, V>, MapKeyOfT>::iterator ��һ������
		typedef typename RBTree<K, pair<K, V>, MapKeyOfT>::iterator iterator;

		iterator begin()
		{
			return _t.begin();// �ײ��ǵ��ú������
		}

		iterator end()
		{
			return _t.end();// �ײ��ǵ��ú������
		}

		pair<iterator, bool> insert(const pair<K, V>& kv)
		{
			return _t.Insert(kv);// �ײ��ǵ��ú������
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