/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  内容:cgh_hash_table的迭代器
******************************************************************/

#ifndef _CGH_HASH_TABLE_ITERATOR_
#define _CGH_HASH_TABLE_ITERATOR_

#include "globalConstruct.h"
#include "cghAlloc.h"
#include "hash_table_node.h"
#include "cgh_hash_table.h"
#include <memory>

using namespace::std;

namespace CGH{
	/* 
		迭代器中用到了cgh_hash_table，除了#include "hash_table.h"以外，我们要在这里声明一下cgh_hash_table 
		不然的话，在hash_table_iterator中
		typedef cgh_hash_table<value, key, hashFun, extractKey, equalEey, Alloc> cgh_hash_table;
		报错：error C2143: 语法错误 : 缺少“;”(在“<”的前面)
	*/
	template<class value, class key, class hashFun, class extractKey, class equalKey, class Alloc = cghAllocator<key>>
	class cgh_hash_table;

	template<class value,class key,class hashFun, class extractKey,class equalEey,class Alloc=cghAllocator<key>>
	struct hash_table_iterator{

		#pragma region typedef 和 成员变量

		typedef hash_table_iterator<value, key, hashFun, extractKey, equalEey, Alloc>	iterator; // 声明迭代器
		typedef hash_table_node<value>	node; // 声明节点
		typedef cgh_hash_table<value, key, hashFun, extractKey, equalEey, Alloc> cgh_hash_table; // 声明hash_table

		/* hash_table的迭代器没有后退操作，只能前进 */
		typedef std::forward_iterator_tag	iterator_category;
		typedef value						value_type; // 声明实值类型
		typedef ptrdiff_t					difference_type; // 表示两迭代器之前的距离
		typedef size_t						size_type;
		typedef value&						reference; // 声明引用类型
		typedef value*						pointer; // 声明指针类型

		node* cur; // 节点和迭代器联系的纽带
		cgh_hash_table* ht; // 迭代器和cgh_hash_table联系的纽带

		#pragma endregion

		#pragma region 迭代器的构造

		hash_table_iterator(node* n, cgh_hash_table* tab) :cur(n), ht(tab){}
		hash_table_iterator(){}

		#pragma endregion

		#pragma region 迭代器的一般操作

		/* 解除引用，返回节点实值 */
		reference operator*()const { return cur->val; }

		/* 解除引用 */
		pointer operator->()const{ return &(operator*()); }

		/* 步进（注意，cgh_hash_table的迭代器只能前进）*/
		iterator& operator++()
		{
			const node* old = cur; // 保存迭代器当前位置
			// 由于节点被安置在list内，所以利用next指针可以轻易进行前进操作
			cur = cur->next;
			// 如果前进一个步长之后来到list尾部，我们就要跳到下一个bucket上
			if (!cur)
			{
				size_type bucket = ht->bkt_num(old->val); // 获得当前bucket的位置
				// ++bucket：来到下一个bucket
				// cur = ht->buckets[bucket]：下一个bucket保存的list的头节点，如果cur == NULL
				// 说明下一个bucket为空，继续while循环，直到找到一个不为空的bucket
				while (!cur && ++bucket < ht->buckets.size())
				{
					cur = ht->buckets[bucket];
				}
				return *this;
			}
		}

		/* 步进（注意，cgh_hash_table的迭代器只能前进）*/
		iterator& operator++(int)
		{
			iterator tmp = *this;
			++*this;
			return tmp;
		}

		#pragma endregion
	};
}

#endif