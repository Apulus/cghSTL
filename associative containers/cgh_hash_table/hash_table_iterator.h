/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ����:cgh_hash_table�ĵ�����
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
		���������õ���cgh_hash_table������#include "hash_table.h"���⣬����Ҫ����������һ��cgh_hash_table 
		��Ȼ�Ļ�����hash_table_iterator��
		typedef cgh_hash_table<value, key, hashFun, extractKey, equalEey, Alloc> cgh_hash_table;
		����error C2143: �﷨���� : ȱ�١�;��(�ڡ�<����ǰ��)
	*/
	template<class value, class key, class hashFun, class extractKey, class equalKey, class Alloc = cghAllocator<key>>
	class cgh_hash_table;

	template<class value,class key,class hashFun, class extractKey,class equalEey,class Alloc=cghAllocator<key>>
	struct hash_table_iterator{

		#pragma region typedef �� ��Ա����

		typedef hash_table_iterator<value, key, hashFun, extractKey, equalEey, Alloc>	iterator; // ����������
		typedef hash_table_node<value>	node; // �����ڵ�
		typedef cgh_hash_table<value, key, hashFun, extractKey, equalEey, Alloc> cgh_hash_table; // ����hash_table

		/* hash_table�ĵ�����û�к��˲�����ֻ��ǰ�� */
		typedef std::forward_iterator_tag	iterator_category;
		typedef value						value_type; // ����ʵֵ����
		typedef ptrdiff_t					difference_type; // ��ʾ��������֮ǰ�ľ���
		typedef size_t						size_type;
		typedef value&						reference; // ������������
		typedef value*						pointer; // ����ָ������

		node* cur; // �ڵ�͵�������ϵ��Ŧ��
		cgh_hash_table* ht; // ��������cgh_hash_table��ϵ��Ŧ��

		#pragma endregion

		#pragma region �������Ĺ���

		hash_table_iterator(node* n, cgh_hash_table* tab) :cur(n), ht(tab){}
		hash_table_iterator(){}

		#pragma endregion

		#pragma region ��������һ�����

		/* ������ã����ؽڵ�ʵֵ */
		reference operator*()const { return cur->val; }

		/* ������� */
		pointer operator->()const{ return &(operator*()); }

		/* ������ע�⣬cgh_hash_table�ĵ�����ֻ��ǰ����*/
		iterator& operator++()
		{
			const node* old = cur; // �����������ǰλ��
			// ���ڽڵ㱻������list�ڣ���������nextָ��������׽���ǰ������
			cur = cur->next;
			// ���ǰ��һ������֮������listβ�������Ǿ�Ҫ������һ��bucket��
			if (!cur)
			{
				size_type bucket = ht->bkt_num(old->val); // ��õ�ǰbucket��λ��
				// ++bucket��������һ��bucket
				// cur = ht->buckets[bucket]����һ��bucket�����list��ͷ�ڵ㣬���cur == NULL
				// ˵����һ��bucketΪ�գ�����whileѭ����ֱ���ҵ�һ����Ϊ�յ�bucket
				while (!cur && ++bucket < ht->buckets.size())
				{
					cur = ht->buckets[bucket];
				}
				return *this;
			}
		}

		/* ������ע�⣬cgh_hash_table�ĵ�����ֻ��ǰ����*/
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