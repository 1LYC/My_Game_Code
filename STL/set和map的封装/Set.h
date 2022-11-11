#pragma once

#include "RBTree.h"

namespace bit
{
	template<class K>
	class set
	{
		// Ϊ����set��map�ıȽ�
		struct SetKeyOfT
		{
			const K& operator()(const K& key)
			{
				return key;
			}
		};
	public:
		// RBTree<K, K, SetKeyOfT>::iterator ����һ������
		typedef typename RBTree<K, K, SetKeyOfT>::iterator iterator;

		iterator begin()
		{
			return _t.begin();// �ײ��ǵ��ú������
		}

		iterator end()
		{
			return _t.end();// �ײ��ǵ��ú������
		}

		pair<iterator, bool> insert(const K& key)
		{
			return _t.Insert(key);// �ײ��ǵ��ú������
		}
	private:
		RBTree<K, K, SetKeyOfT> _t;
	};
}