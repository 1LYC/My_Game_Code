#pragma once

#include "HashTable.h"

namespace bit
{
	template<class K, class V, class Hash = HashFunc<K>>
	class unordered_map
	{
		struct MapKeyOfT
		{
			const K& operator()(const pair<K, V>& kv)
			{
				return kv.first;
			}
		};
	public:
		typedef typename Bucket::HashTable<K, pair<K, V>, Hash, MapKeyOfT>::iterator iterator;

		iterator begin()
		{
			return _ht.begin();
		}

		iterator end()
		{
			return _ht.end();
		}

		pair<iterator, bool> Insert(const pair<K, V>& kv)
		{
			return _ht.Insert(kv);
		}

		V& operator[](const K& key)
		{
			pair<iterator, bool> ret = _ht.Insert(make_pair(key, V()));
			return ret.first->second;
		}

	private:
		Bucket::HashTable<K, pair<K, V>, Hash, MapKeyOfT> _ht;
	};

	void test_map()
	{
		unordered_map<string, string> dict;
		dict.Insert(make_pair("sort", ""));
		dict.Insert(make_pair("string", "?"));
		dict.Insert(make_pair("left", ""));

		unordered_map<string, string>::iterator it = dict.begin();
		while (it != dict.end())
		{
			cout << it->first << ":" << it->second << endl;
			++it;
		}
		cout << endl;

		unordered_map<string, int> countMap;
		string arr[] = { "?", "", "?", "", "?", "?", "", "?", "?", "?", "?" };
		for (auto e : arr)
		{
			countMap[e]++;
		}

		for (auto& kv : countMap)
		{
			cout << kv.first << ":" << kv.second << endl;
		}
	}
}