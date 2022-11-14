#pragma once
// 处理头文件
#include <iostream>
#include <string>
#include <vector>
using namespace std;
template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

// 特化  20：12继续
template<>
struct HashFunc<string>
{
	// BKDR
	size_t operator()(const string& key)
	{
		size_t val = 0;
		for (auto ch : key)
		{
			val *= 131;
			val += ch;
		}

		return val;
	}
};

namespace CloseHash
{
	enum State
	{
		EMPTY,
		EXIST,
		DELETE
	};

	template<class K, class V>
	struct HashData
	{
		pair<K, V> _kv;
		State _state = EMPTY;
	};

	//struct HashFuncString
	//{
	//	size_t operator()(const string& key)
	//	{
	//		size_t val = 0;
	//		for (auto ch : key)
	//		{
	//			val += ch;
	//		}
	//
	//		return val;
	//	}
	//};


	template<class K, class V, class Hash = HashFunc<K>>
	class HashTable
	{
	public:
		bool Insert(const pair<K, V>& kv)
		{
			if (Find(kv.first))
				return false;

			// 负载因子到了就扩容
			if (_tables.size() == 0 || 10 * _size / _tables.size() >= 7) // 扩容
			{
				size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				HashTable<K, V, Hash> newHT;
				newHT._tables.resize(newSize);
				// 旧表的数据映射到新表
				for (auto e : _tables)
				{
					if (e._state == EXIST)
					{
						newHT.Insert(e._kv);
					}
				}

				_tables.swap(newHT._tables);
			}

			Hash hash;
			size_t hashi = hash(kv.first) % _tables.size();
			// 线性探测
			while (_tables[hashi]._state == EXIST)
			{
				hashi++;
				hashi %= _tables.size();
			}

			_tables[hashi]._kv = kv;
			_tables[hashi]._state = EXIST;
			++_size;


			//Hash hash;
			//size_t start = hash(kv.first) % _tables.size();
			//size_t i = 0;
			//size_t hashi = start;
			//// 二次探测
			//while (_tables[hashi]._state == EXIST)
			//{
			//	++i;
			//	hashi = start + i*i;
			//	hashi %= _tables.size();
			//}

			//_tables[hashi]._kv = kv;
			//_tables[hashi]._state = EXIST;
			//++_size;

			return true;
		}

		HashData<K, V>* Find(const K& key)
		{
			if (_tables.size() == 0)
			{
				return nullptr;
			}

			Hash hash;
			size_t start = hash(key) % _tables.size();
			size_t hashi = start;
			while (_tables[hashi]._state != EMPTY)
			{
				if (_tables[hashi]._state != DELETE && _tables[hashi]._kv.first == key)
				{
					return &_tables[hashi];
				}

				hashi++;
				hashi %= _tables.size();

				if (hashi == start)
				{
					break;
				}
			}

			return nullptr;
		}

		bool Erase(const K& key)
		{
			HashData<K, V>* ret = Find(key);
			if (ret)
			{
				ret->_state = DELETE;
				--_size;
				return true;
			}
			else
			{
				return false;
			}
		}

		void Print()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i]._state == EXIST)
				{
					printf("[%d:%d] ", i, _tables[i]._kv.first);
				}
				else
				{
					printf("[%d:*] ", i);
				}
			}
			cout << endl;
		}

	private:
		//vector<pair<K, V>> _table;
		vector<HashData<K, V>> _tables;
		size_t _size = 0; // 存储多少个有效数据
	};

	void TestHT1()
	{
		//int a[] = { 1, 11, 4, 15, 26, 7, 44, 9 };
		int a[] = { 1, 11, 4, 15, 26, 7, 44 };
		HashTable<int, int> ht;
		for (auto e : a)
		{
			ht.Insert(make_pair(e, e));
		}

		ht.Print();

		ht.Erase(4);
		cout << ht.Find(44)->_kv.first << endl;
		cout << ht.Find(4) << endl;
		ht.Print();

		ht.Insert(make_pair(-2, -2));
		ht.Print();

		cout << ht.Find(-2)->_kv.first << endl;
	}

	void TestHT2()
	{
		string arr[] = { "苹果", "西瓜", "苹果", "西瓜", "苹果", "苹果", "西瓜", "苹果", "香蕉", "苹果", "香蕉" };

		//HashTable<string, int, HashFuncString> countHT;
		HashTable<string, int> countHT;
		for (auto& str : arr)
		{
			auto ptr = countHT.Find(str);
			if (ptr)
			{
				ptr->_kv.second++;
			}
			else
			{
				countHT.Insert(make_pair(str, 1));
			}
		}
	}

	void TestHT3()
	{
		HashFunc<string> hash;
		cout << hash("abcd") << endl;
		cout << hash("bcad") << endl;
		cout << hash("eat") << endl;
		cout << hash("ate") << endl;
		cout << hash("abcd") << endl;
		cout << hash("aadd") << endl << endl;

		cout << hash("abcd") << endl;
		cout << hash("bcad") << endl;
		cout << hash("eat") << endl;
		cout << hash("ate") << endl;
		cout << hash("abcd") << endl;
		cout << hash("aadd") << endl << endl;
	}
}

namespace Bucket
{
	template<class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;

		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{}
	};

	// 前置声明
	template<class K, class T, class Hash, class KeyOfT>
	class HashTable;

	template<class K, class T, class Hash, class KeyOfT>
	struct __HashIterator
	{
		typedef HashNode<T> Node;
		typedef HashTable<K, T, Hash, KeyOfT> HT;
		typedef __HashIterator<K, T, Hash, KeyOfT> Self;

		Node* _node;
		HT* _pht;

		__HashIterator(Node* node, HT* pht)
			:_node(node)
			, _pht(pht)
		{}

		T& operator*()
		{
			return _node->_data;
		}

		T* operator->()
		{
			return &_node->_data;
		}

		Self& operator++()
		{
			if (_node->_next)
			{
				// 当前桶中迭代
				_node = _node->_next;
			}
			else
			{
				// 找下一个桶
				Hash hash;
				KeyOfT kot;
				size_t i = hash(kot(_node->_data)) % _pht->_tables.size();
				++i;
				for (; i < _pht->_tables.size(); ++i)
				{
					if (_pht->_tables[i])
					{
						_node = _pht->_tables[i];
						break;
					}
				}

				// 说明后面没有有数据的桶了
				if (i == _pht->_tables.size())
				{
					_node = nullptr;
				}
			}

			return *this;
		}

		bool operator!=(const Self& s) const
		{
			return _node != s._node;
		}

		bool operator==(const Self& s) const
		{
			return _node == s._node;
		}
	};

	template<class K, class T, class Hash, class KeyOfT>
	class HashTable
	{
		typedef HashNode<T> Node;

		template<class K, class T, class Hash, class KeyOfT>
		friend struct __HashIterator;
	public:
		typedef __HashIterator<K, T, Hash, KeyOfT> iterator;

		iterator begin()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i])
				{
					return iterator(_tables[i], this);
				}
			}

			return end();
		}

		iterator end()
		{
			return iterator(nullptr, this);
		}

		~HashTable()
		{
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}

		inline size_t __stl_next_prime(size_t n)
		{
			static const size_t __stl_num_primes = 28;
			static const size_t __stl_prime_list[__stl_num_primes] =
			{
				53, 97, 193, 389, 769,
				1543, 3079, 6151, 12289, 24593,
				49157, 98317, 196613, 393241, 786433,
				1572869, 3145739, 6291469, 12582917, 25165843,
				50331653, 100663319, 201326611, 402653189, 805306457,
				1610612741, 3221225473, 4294967291
			};

			for (size_t i = 0; i < __stl_num_primes; ++i)
			{
				if (__stl_prime_list[i] > n)
				{
					return __stl_prime_list[i];
				}
			}

			return -1;
		}

		pair<iterator, bool> Insert(const T& data)
		{
			Hash hash;
			KeyOfT kot;

			// 去重
			iterator ret = Find(kot(data));
			if (ret != end())
			{
				return make_pair(ret, false);
			}

			// 负载因子到1就扩容
			if (_size == _tables.size())
			{
				//size_t newSize = _tables.size() == 0 ? 10 : _tables.size() * 2;
				vector<Node*> newTables;
				//newTables.resize(newSize, nullptr);
				newTables.resize(__stl_next_prime(_tables.size()), nullptr);
				// 旧表中节点移动映射新表
				for (size_t i = 0; i < _tables.size(); ++i)
				{
					Node* cur = _tables[i];
					while (cur)
					{
						Node* next = cur->_next;

						size_t hashi = hash(kot(cur->_data)) % newTables.size();
						cur->_next = newTables[hashi];
						newTables[hashi] = cur;

						cur = next;
					}

					_tables[i] = nullptr;
				}

				_tables.swap(newTables);
			}

			size_t hashi = hash(kot(data)) % _tables.size();
			// 头插
			Node* newnode = new Node(data);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_size;

			return make_pair(iterator(newnode, this), true);
		}

		iterator Find(const K& key)
		{
			if (_tables.size() == 0)
			{
				return end();
			}

			Hash hash;
			KeyOfT kot;
			size_t hashi = hash(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					return iterator(cur, this);
				}

				cur = cur->_next;
			}

			return end();
		}

		bool Erase(const K& key)
		{
			if (_tables.size() == 0)
			{
				return false;
			}

			Hash hash;
			KeyOfT kot;
			size_t hashi = hash(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (kot(cur->_data) == key)
				{
					// 1、头删
					// 2、中间删
					if (prev == nullptr)
					{
						_tables[hashi] = cur->_next;
					}
					else
					{
						prev->_next = cur->_next;
					}

					delete cur;
					--_size;

					return true;
				}

				prev = cur;
				cur = cur->_next;
			}

			return false;
		}

		size_t Size()
		{
			return _size;
		}

		// 表的长度
		size_t TablesSize()
		{
			return _tables.size();
		}

		// 桶的个数
		size_t BucketNum()
		{
			size_t num = 0;
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				if (_tables[i])
				{
					++num;
				}
			}

			return num;
		}

		size_t MaxBucketLenth()
		{
			size_t maxLen = 0;
			for (size_t i = 0; i < _tables.size(); ++i)
			{
				size_t len = 0;
				Node* cur = _tables[i];
				while (cur)
				{
					++len;
					cur = cur->_next;
				}

				//if (len > 0)
					//printf("[%d]号桶长度:%d\n", i, len);

				if (len > maxLen)
				{
					maxLen = len;
				}
			}

			return maxLen;
		}

	private:
		vector<Node*> _tables;
		size_t _size = 0; // 存储有效数据个数
	};
}