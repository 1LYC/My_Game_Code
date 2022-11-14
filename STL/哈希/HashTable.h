#pragma once

template<class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key;
	}
};

// 特化  
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
	template<class K, class V>
	struct HashNode
	{
		pair<K, V> _kv;
		HashNode<K, V>* _next;

		HashNode(const pair<K, V>& kv)
			:_kv(kv)
			, _next(nullptr)
		{}
	};

	// 休息：20
	template<class K, class V, class Hash = HashFunc<K>>
	class HashTable
	{
		typedef HashNode<K, V> Node;
	public:

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

		bool Insert(const pair<K, V>& kv)
		{
			// 去重
			if (Find(kv.first))
			{
				return false;
			}

			Hash hash;
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

						size_t hashi = hash(cur->_kv.first) % newTables.size();
						cur->_next = newTables[hashi];
						newTables[hashi] = cur;

						cur = next;
					}

					_tables[i] = nullptr;
				}

				_tables.swap(newTables);
			}

			size_t hashi = hash(kv.first) % _tables.size();
			// 头插
			Node* newnode = new Node(kv);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_size;

			return true;
		}

		Node* Find(const K& key)
		{
			if (_tables.size() == 0)
			{
				return nullptr;
			}

			Hash hash;
			size_t hashi = hash(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
				{
					return cur;
				}

				cur = cur->_next;
			}

			return nullptr;
		}

		bool Erase(const K& key)
		{
			if (_tables.size() == 0)
			{
				return nullptr;
			}

			Hash hash;
			size_t hashi = hash(key) % _tables.size();
			Node* prev = nullptr;
			Node* cur = _tables[hashi];
			while (cur)
			{
				if (cur->_kv.first == key)
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

	void TestHT1()
	{
		int a[] = { 1, 11, 4, 15, 26, 7, 44,55,99,78 };
		HashTable<int, int> ht;
		for (auto e : a)
		{
			ht.Insert(make_pair(e, e));
		}

		ht.Insert(make_pair(22, 22));

		ht.Erase(44);
		ht.Erase(4);
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

		int n = 19000000;
		vector<int> v;
		v.reserve(n);
		srand(time(0));
		for (int i = 0; i < n; ++i)
		{
			//v.push_back(i);
			v.push_back(rand() + i);  // 重复少
			//v.push_back(rand());  // 重复多
		}

		size_t begin1 = clock();
		HashTable<int, int> ht;
		for (auto e : v)
		{
			ht.Insert(make_pair(e, e));
		}
		size_t end1 = clock();

		cout << "数据个数:" << ht.Size() << endl;
		cout << "表的长度:" << ht.TablesSize() << endl;
		cout << "桶的个数:" << ht.BucketNum() << endl;
		cout << "平均每个桶的长度:" << (double)ht.Size() / (double)ht.BucketNum() << endl;
		cout << "最长的桶的长度:" << ht.MaxBucketLenth() << endl;
		cout << "负载因子:" << (double)ht.Size() / (double)ht.TablesSize() << endl;
	}
}