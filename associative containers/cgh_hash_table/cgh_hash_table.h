/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ����:cgh_hash_table��ʵ��
******************************************************************/


#include "globalConstruct.h" // ȫ�ֹ�������������
#include "cghAlloc.h" // �ռ�������
#include "hash_table_node.h"
#include "hash_table_iterator.h"
#include "cghVector.h" // vector
#include "cghUtil.h" // ������
#include <algorithm> // ��Ҫ�õ��㷨

#ifndef _CGH_HASH_TABLE_
#define _CGH_HASH_TABLE_
namespace CGH{
	/*
		value��		�ڵ��ʵֵ����
		key��		�ڵ�ļ�ֵ����
		hashFun��	hash faction�ĺ�������
		extractKey���ӽڵ���ȡ����ֵ�ķ���
		equalKey��	�жϼ�ֵ�Ƿ���ͬ�ķ���
		Alloc��		�ռ�������
	*/
	template<class value, class key, class hashFun, class extractKey, class equalKey, class Alloc = cghAllocator<key>>
	class cgh_hash_table{

		#pragma region typedef �� ��Ա����

	public:
		typedef hashFun		hasher;
		typedef equalKey	key_equal;
		typedef size_t		size_type;
		typedef value		value_type; // ʵֵ����
		typedef key			key_type; // ��ֵ����
		typedef hash_table_iterator<value, key, hasher, extractKey, equalKey, Alloc>	iterator; // ������

	private:
		hasher hash; // hash faction
		key_equal equals; // �жϼ�ֵ�Ƿ���ͬ�ķ���
		extractKey get_key; // �ӽڵ���ȡ����ֵ�ķ���

		typedef hash_table_node<value> node; // �ڵ�
		typedef simple_alloc<node, Alloc> node_allocator; // �ռ�������

	public:
		size_type num_elements; // hash_table����Ч�Ľڵ����
		cghVector<node*, Alloc> buckets; // ��cghVector��Ϊbucket�ĵײ�ʵ��

		#pragma endregion
		
		#pragma region cgh_hash_table�Ĺ���������

	private:
		/*�������½ڵ㡡*/
		node* new_node(const value_type& obj)
		{
			node* n = node_allocator::allocate(); // �ռ�����������ڵ�ռ�
			n->next = 0; // ��ʼ���ڵ��nextָ��ָ��NULL
			construct(&n->val, obj); // ȫ�ֹ��캯������ʼ���ڵ�ʵֵ
			return n; // �����½ڵ��ָ��
		}

		/*�����ٽڵ㡡*/
		void delete_node(node* n)
		{
			destroy(&n->val); // ȫ���������������ٽڵ�ʵֵ
			node_allocator::deallocate(n); // �ͻ��ڵ��ڴ�
		}

		/*
			��������������Ʊ���С����28���������𽥳��ִ�Լ�����Ĺ�ϵ�������
			__stl_next_prime�������ڲ�ѯ��28�������У�����ӽ�ĳ��������ĳ����������
			__stl_num_primes = 28; // ��ʾ28������
			__stl_prime_list��ָ�����飬�����ڱ��ļ���ĩβ
		*/
		inline unsigned long __stl_next_prime(unsigned long n)
		{
			const unsigned long* first = __stl_prime_list; // ָ������ͷ����ָ��
			const unsigned long* last = __stl_prime_list + __stl_num_primes; // ָ������β����ָ��
			// �����õ��˱�׼���lower_bound�㷨�����������飨__stl_prime_list�����򣨴�С����
			const unsigned long* pos = std::lower_bound(first, last, n);
			return pos == last ? *(last - 1) : *pos;
		}

		/* ����nֵ�����غ��ʵ�buckets��С */
		size_type next_size(size_type n){ return __stl_next_prime(n); }

		/* ��ʼ��buckets��buckets��ÿ���ڵ��Ӧһ��list��������Ľڵ�������hash_table_node */
		void initialize_buckets(size_type n)
		{
			const size_type n_buckets = next_size(n); // ȡ�ó�ʼ����buckets��Ԫ�ظ���
			buckets.insert(buckets.end(), n_buckets, 0); // ÿ��Ԫ�ض�Ӧ��list�����ʼ��Ϊ��
		}

	public:
		/* cgh_hash_table�Ĺ��캯�� */
		cgh_hash_table(size_type n, const hashFun& hf, const equalKey& eql)
			:hash(hf), equals(eql), get_key(extractKey()), num_elements(0)
		{
			initialize_buckets(n);
		}

		#pragma endregion
		
		#pragma region �ṩ���û���API

			#pragma region ������

	public:
		/* ���ص�ǰbucket������ */
		size_type bucket_count(){ return buckets.size(); }

		/* ���bucket�� */
		size_type max_bucket_count()const{ return __stl_prime_list[__stl_num_primes - 1]; }

		/* ���ص�ǰcgh_hash_table����Ч�ڵ�ĸ��� */
		size_type size()const{ return num_elements; }

		/* ���ص�������ָ���һ���ڵ� */
		iterator begin()
		{
			///�ҵ���һ���ǿյ�Ͱ,�õ����һ��Ԫ��
			for (size_type n = 0; n < buckets.size(); ++n)
			{
				if (buckets[n])
				{
					return iterator(buckets[n], this);
				}
			}
			return end(); // ���cgh_hash_tableΪ�գ�����β��
		}

		/* ���ص�������ָ���һ���ڵ� */
		iterator end() { return iterator(0, this); }

		/* ����ָ��bucket��װ�Ľڵ�������ڵ�����Ϊhash_table_node */
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

		/* �����ֵ������һ����������ָ���ֵ��Ӧ�Ľڵ� */
		iterator find(const key_type& key)
		{
			size_type n = bkt_num(key); // �����ֵ�����ĸ�bucket����
			node* first; // ָ��bucket�ĵ�һ���ڵ�
			// ��һ�Ƚ�bucket��Ӧ��list��ÿ���ڵ�ļ�ֵ
			for (first = buckets[n]; first && !equals(get_key(first->val), key); first = first->next){}
			return iterator(first, this);
		}

		/* ���ؼ�ֵΪkey�Ľڵ���� */
		size_type count(const key_type& key)
		{
			size_type n = bkt_num(key); // ȷ��key�����ĸ�bucket��
			size_type result = 0;
			// ����bucket��Ӧ��list��ÿ���ڵ�
			for (const node* cur = buckets[n]; cur; cur = cur->next)
			{
				if (equals(get_key(cur->val), key)) // ����ڵ��ֵ����key
				{
					++result;
				}
			}
			return result;
		}

			#pragma endregion

			#pragma region д����

				#pragma region �û��ӿ�
	public:
		/* ����Ԫ�أ��������ֵ�ظ� */
		cghPair<iterator, bool> insert_unique(const value_type& obj)
		{
			resize(num_elements + 1); // �ж��Ƿ���Ҫ�ؽ����
			return insert_unique_noresize(obj); // ���ø�������
		}

		/* ����Ԫ�أ������ֵ�ظ� */
		iterator insert_equal(const value_type& obj)
		{
			resize(num_elements + 1); // �ж��Ƿ���Ҫ�ؽ����
			return insert_equal_noresize(obj); // ���ø�������
		}

#pragma endregion

				#pragma region ��������
	private:
		/* �Ƿ���Ҫ�ؽ���� */
		void resize(size_type num_elements_hint)
		{
			/*
			�ж��ؽ�����ԭ��
			�Ƚ�Ԫ�ظ�������������Ԫ�أ���bucket vector�Ĵ�С
			Ԫ�ظ��� > bucket vector�Ĵ�С => �ؽ����
			�ɴ˿�֪��ÿ��bucket��list�������������bucket vector�Ĵ�С��ͬ
			��һ�� n * n �ľ���
			*/
			const size_type old_n = buckets.size(); // ���bucket vector�Ĵ�С
			if (num_elements_hint > old_n) // ��� Ԫ�ظ��� > bucket vector�Ĵ�С�����Ǿ�Ҫ�ؽ����
			{
				// �ҳ���һ��������Ҳ���Ǵ��ؽ��ı���С
				const size_type n = next_size(num_elements_hint);
				if (n > old_n)
				{
					cghVector<node*, Alloc> tmp(n, (node*)0); // �����µ�buckets
					// ����ÿһ���ɵ�bucket
					for (size_type bucket = 0; bucket < old_n; ++bucket)
					{
						node* first = buckets[bucket];// �ɵ�buckets�У�ÿ��Ԫ�أ�bucket��ָ���list���
						while (first) // ѭ������list
						{
							size_type new_bucket = bkt_num(first->val, n); // �ҳ��ڵ�������һ����bucket��
							buckets[bucket] = first->next; // 1.���bucketָ��������Ӧ��list����һ���ڵ�
							first->next = tmp[new_bucket]; //2��3.����ǰ�ڵ���뵽��bucket�ڣ���Ϊ��list�ĵ�һ���ڵ�
							tmp[new_bucket] = first;
							first = buckets[bucket]; // 4.�ص���bucket��ָ���list��׼��������һ���ڵ�
						}
					}
					buckets.swap(tmp); // �����¾�buckets
				} // �뿪ʱ��tmp���ͷ�
			}
		}

		/* �������ֵ�ظ��Ĳ��� */
		cghPair<iterator, bool> insert_unique_noresize(const value_type& obj)
		{
			const size_type n = bkt_num(obj); // ���ݼ�ֵ���������ĸ�bucket��
			node* first = buckets[n]; // ��firstָ��bucket��Ӧ��list
			for (node* cur = first; cur; cur = cur->next) // ����list
			{
				if (equals(get_key(cur->val), get_key(obj))) // ������ּ�ֵ�ظ�
				{
					return cghPair<iterator, bool>(iterator(cur, this), false); // ���ز���ʧ��
				}
			}
			node* tmp = new_node(obj); // �����½ڵ�
			tmp->next = first; // ͷ�巨�������½ڵ㵽listͷ��
			buckets[n] = tmp;
			++num_elements; // �ڵ�����1
			return cghPair<iterator, bool>(iterator(tmp, this), true); // ���ؽ��
		}

		/* �����ֵ�ظ��Ĳ��� */
		iterator insert_equal_noresize(const value_type& obj)
		{
			const size_type n = bkt_num(obj); // ���ݼ�ֵ���������ĸ�bucket��
			node* first = buckets[n]; // ��firstָ��bucket��Ӧ��list
			for (node* cur = first; cur; cur = cur->next) // ����list
			{
				if (equals(get_key(cur->val), get_key(obj))) // ������ּ�ֵ�ظ�
				{
					node* tmp = new_node(obj); // �����½ڵ�
					tmp->next = cur->next; // ͷ�巨�������½ڵ㵽cur��ǰ��
					cur->next = tmp;
					++num_elements; // �ڵ�����1
					return iterator(tmp, this); // ���ؽ��
				}
			}
			node* tmp = new_node(obj); // �����½ڵ�
			tmp->next = first; // ͷ�巨�������½ڵ㵽first��ǰ��
			buckets[n] = tmp;
			++num_elements; // �ڵ�����1
			return iterator(tmp, this); // ���ؽ��
		}
#pragma endregion 
			#pragma endregion

		#pragma endregion

		#pragma region ������ֵ������bucket

		/*
			����hash_table���ԣ�����Ҫ�ľ���ȷ��key��Ӧ��bucket������hash faction������
			���ǰ�hash faction��װһ�㣬�������ĸ���������hash faction
		*/
	public:
		/* ����ʵֵ��buckets���� */
		size_type bkt_num(const value_type& obj, size_type n)
		{
			return bkt_num_key(get_key(obj), n);
		}

		/* ֻ����ʵֵ */
		size_type bkt_num(const value_type& obj)
		{
			return bkt_num_key(get_key(obj));
		}

		/* ֻ���ܼ�ֵ */
		size_type bkt_num_key(const key_type& key)
		{
			return bkt_num_key(key, buckets.size());
		}

		/* ���ܼ�ֵ��buckets���� */
		size_type bkt_num_key(const key_type& key, size_type n)
		{
			return hash(key) % n; // ����hash faction������bucket
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