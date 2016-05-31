/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  内容:cgh_hash_table的实现
******************************************************************/


#include "globalConstruct.h" // 全局构造与析构函数
#include "cghAlloc.h" // 空间配置器
#include "hash_table_node.h"
#include "hash_table_iterator.h"
#include "cghVector.h" // vector
#include "cghUtil.h" // 工具类
#include <algorithm> // 需要用到算法

#ifndef _CGH_HASH_TABLE_
#define _CGH_HASH_TABLE_
namespace CGH{
	/*
		value：		节点的实值类型
		key：		节点的键值类型
		hashFun：	hash faction的函数类型
		extractKey：从节点中取出键值的方法
		equalKey：	判断键值是否相同的方法
		Alloc：		空间配置器
	*/
	template<class value, class key, class hashFun, class extractKey, class equalKey, class Alloc = cghAllocator<key>>
	class cgh_hash_table{

		#pragma region typedef 和 成员变量

	public:
		typedef hashFun		hasher;
		typedef equalKey	key_equal;
		typedef size_t		size_type;
		typedef value		value_type; // 实值类型
		typedef key			key_type; // 键值类型
		typedef hash_table_iterator<value, key, hasher, extractKey, equalKey, Alloc>	iterator; // 迭代器

	private:
		hasher hash; // hash faction
		key_equal equals; // 判断键值是否相同的方法
		extractKey get_key; // 从节点中取出键值的方法

		typedef hash_table_node<value> node; // 节点
		typedef simple_alloc<node, Alloc> node_allocator; // 空间配置器

	public:
		size_type num_elements; // hash_table中有效的节点个数
		cghVector<node*, Alloc> buckets; // 用cghVector作为bucket的底层实现

		#pragma endregion
		
		#pragma region cgh_hash_table的构造与析构

	private:
		/*　构造新节点　*/
		node* new_node(const value_type& obj)
		{
			node* n = node_allocator::allocate(); // 空间配置器分配节点空间
			n->next = 0; // 初始化节点的next指针指向NULL
			construct(&n->val, obj); // 全局构造函数，初始化节点实值
			return n; // 返回新节点的指针
		}

		/*　销毁节点　*/
		void delete_node(node* n)
		{
			destroy(&n->val); // 全局析构函数，销毁节点实值
			node_allocator::deallocate(n); // 释还节点内存
		}

		/*
			我们以质数来设计表格大小，将28个质数（逐渐呈现大约两倍的关系）计算好
			__stl_next_prime函数用于查询这28个质数中，“最接近某数并大于某数”的质数
			__stl_num_primes = 28; // 表示28个质数
			__stl_prime_list：指数数组，定义在本文件的末尾
		*/
		inline unsigned long __stl_next_prime(unsigned long n)
		{
			const unsigned long* first = __stl_prime_list; // 指向数组头部的指针
			const unsigned long* last = __stl_prime_list + __stl_num_primes; // 指向数组尾部的指针
			// 这里用到了标准库的lower_bound算法，对质数数组（__stl_prime_list）排序（从小到大）
			const unsigned long* pos = std::lower_bound(first, last, n);
			return pos == last ? *(last - 1) : *pos;
		}

		/* 根据n值，返回合适的buckets大小 */
		size_type next_size(size_type n){ return __stl_next_prime(n); }

		/* 初始化buckets，buckets的每个节点对应一个list链表，链表的节点类型是hash_table_node */
		void initialize_buckets(size_type n)
		{
			const size_type n_buckets = next_size(n); // 取得初始化的buckets的元素个数
			buckets.insert(buckets.end(), n_buckets, 0); // 每个元素对应的list链表初始化为空
		}

	public:
		/* cgh_hash_table的构造函数 */
		cgh_hash_table(size_type n, const hashFun& hf, const equalKey& eql)
			:hash(hf), equals(eql), get_key(extractKey()), num_elements(0)
		{
			initialize_buckets(n);
		}

		#pragma endregion
		
		#pragma region 提供给用户的API

			#pragma region 读操作

	public:
		/* 返回当前bucket的总数 */
		size_type bucket_count(){ return buckets.size(); }

		/* 最大bucket数 */
		size_type max_bucket_count()const{ return __stl_prime_list[__stl_num_primes - 1]; }

		/* 返回当前cgh_hash_table中有效节点的个数 */
		size_type size()const{ return num_elements; }

		/* 返回迭代器，指向第一个节点 */
		iterator begin()
		{
			///找到第一个非空的桶,得到其第一个元素
			for (size_type n = 0; n < buckets.size(); ++n)
			{
				if (buckets[n])
				{
					return iterator(buckets[n], this);
				}
			}
			return end(); // 如果cgh_hash_table为空，返回尾部
		}

		/* 返回迭代器，指向第一个节点 */
		iterator end() { return iterator(0, this); }

		/* 返回指定bucket中装的节点个数，节点类型为hash_table_node */
		size_type elems_in_bucket(size_type num)
		{
			size_type result = 0;
			node* cur = buckets[num];
			for (node* cur = buckets[num]; cur; cur = cur->next)
			{
				result += 1;
			}
			return result;
		}

		/* 输入键值，返回一个迭代器，指向键值对应的节点 */
		iterator find(const key_type& key)
		{
			size_type n = bkt_num(key); // 计算键值落在哪个bucket里面
			node* first; // 指向bucket的第一个节点
			// 逐一比较bucket对应的list的每个节点的键值
			for (first = buckets[n]; first && !equals(get_key(first->val), key); first = first->next){}
			return iterator(first, this);
		}

		/* 返回键值为key的节点个数 */
		size_type count(const key_type& key)
		{
			size_type n = bkt_num(key); // 确定key落在哪个bucket里
			size_type result = 0;
			// 遍历bucket对应的list的每个节点
			for (const node* cur = buckets[n]; cur; cur = cur->next)
			{
				if (equals(get_key(cur->val), key)) // 如果节点键值等于key
				{
					++result;
				}
			}
			return result;
		}

			#pragma endregion

			#pragma region 写操作

				#pragma region 用户接口
	public:
		/* 插入元素，不允许键值重复 */
		cghPair<iterator, bool> insert_unique(const value_type& obj)
		{
			resize(num_elements + 1); // 判断是否需要重建表格
			return insert_unique_noresize(obj); // 调用辅助函数
		}

		/* 插入元素，允许键值重复 */
		iterator insert_equal(const value_type& obj)
		{
			resize(num_elements + 1); // 判断是否需要重建表格
			return insert_equal_noresize(obj); // 调用辅助函数
		}

#pragma endregion

				#pragma region 辅助函数
	private:
		/* 是否需要重建表格 */
		void resize(size_type num_elements_hint)
		{
			/*
			判断重建表格的原则：
			比较元素个数（计入新增元素）和bucket vector的大小
			元素个数 > bucket vector的大小 => 重建表格
			由此可知，每个bucket（list）的最大容量和bucket vector的大小相同
			是一个 n * n 的矩阵
			*/
			const size_type old_n = buckets.size(); // 获得bucket vector的大小
			if (num_elements_hint > old_n) // 如果 元素个数 > bucket vector的大小，我们就要重建表格
			{
				// 找出下一个质数，也就是待重建的表格大小
				const size_type n = next_size(num_elements_hint);
				if (n > old_n)
				{
					cghVector<node*, Alloc> tmp(n, (node*)0); // 设立新的buckets
					// 处理每一个旧的bucket
					for (size_type bucket = 0; bucket < old_n; ++bucket)
					{
						node* first = buckets[bucket];// 旧的buckets中，每个元素（bucket）指向的list起点
						while (first) // 循环遍历list
						{
							size_type new_bucket = bkt_num(first->val, n); // 找出节点落在哪一个新bucket内
							buckets[bucket] = first->next; // 1.令就bucket指向其所对应的list的下一个节点
							first->next = tmp[new_bucket]; //2、3.将当前节点插入到新bucket内，成为其list的第一个节点
							tmp[new_bucket] = first;
							first = buckets[bucket]; // 4.回到就bucket所指向的list，准备处理下一个节点
						}
					}
					buckets.swap(tmp); // 交换新旧buckets
				} // 离开时，tmp被释放
			}
		}

		/* 不允许键值重复的插入 */
		cghPair<iterator, bool> insert_unique_noresize(const value_type& obj)
		{
			const size_type n = bkt_num(obj); // 根据键值决定落在哪个bucket中
			node* first = buckets[n]; // 令first指向bucket对应的list
			for (node* cur = first; cur; cur = cur->next) // 遍历list
			{
				if (equals(get_key(cur->val), get_key(obj))) // 如果发现键值重复
				{
					return cghPair<iterator, bool>(iterator(cur, this), false); // 返回插入失败
				}
			}
			node* tmp = new_node(obj); // 创建新节点
			tmp->next = first; // 头插法：插入新节点到list头部
			buckets[n] = tmp;
			++num_elements; // 节点数加1
			return cghPair<iterator, bool>(iterator(tmp, this), true); // 返回结果
		}

		/* 允许键值重复的插入 */
		iterator insert_equal_noresize(const value_type& obj)
		{
			const size_type n = bkt_num(obj); // 根据键值决定落在哪个bucket中
			node* first = buckets[n]; // 令first指向bucket对应的list
			for (node* cur = first; cur; cur = cur->next) // 遍历list
			{
				if (equals(get_key(cur->val), get_key(obj))) // 如果发现键值重复
				{
					node* tmp = new_node(obj); // 创建新节点
					tmp->next = cur->next; // 头插法：插入新节点到cur的前面
					cur->next = tmp;
					++num_elements; // 节点数加1
					return iterator(tmp, this); // 返回结果
				}
			}
			node* tmp = new_node(obj); // 创建新节点
			tmp->next = first; // 头插法：插入新节点到first的前面
			buckets[n] = tmp;
			++num_elements; // 节点数加1
			return iterator(tmp, this); // 返回结果
		}
#pragma endregion 
			#pragma endregion

		#pragma endregion

		#pragma region 给定键值，计算bucket

		/*
			对于hash_table而言，最重要的就是确定key对应的bucket，这是hash faction的责任
			我们把hash faction封装一层，由下面四个函数调用hash faction
		*/
	public:
		/* 接受实值和buckets个数 */
		size_type bkt_num(const value_type& obj, size_type n)
		{
			return bkt_num_key(get_key(obj), n);
		}

		/* 只接受实值 */
		size_type bkt_num(const value_type& obj)
		{
			return bkt_num_key(get_key(obj));
		}

		/* 只接受键值 */
		size_type bkt_num_key(const key_type& key)
		{
			return bkt_num_key(key, buckets.size());
		}

		/* 接受键值和buckets个数 */
		size_type bkt_num_key(const key_type& key, size_type n)
		{
			return hash(key) % n; // 调用hash faction，返回bucket
		}

		#pragma endregion
	};
	
	static const int __stl_num_primes = 28;
	static const unsigned long __stl_prime_list[__stl_num_primes] =
	{
		53, 97, 193, 389, 769,
		1543, 3079, 6151, 12289, 24593,
		49157, 98317, 196613, 393241, 786433,
		1572869, 3145739, 6291469, 12582917, 25165843,
		50331653, 100663319, 201326611, 402653189, 805306457,
		1610612741, 3221225473ul, 4294967291ul
	};
}

#endif