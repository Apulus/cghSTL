/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ����:cghDeque�ĵ�������ʵ�ִ���
******************************************************************/

#ifndef _CGH_DEQUE_ITERATOR_
#define _CGH_DEQUE_ITERATOR_

#include <memory>
#include "cghSTL_iterator.h"
namespace CGH{

	template<class T, class Ref, class Ptr, size_t BufSiz>
	struct __deque_iterator : public random_access_iterator<T, ptrdiff_t>
	{

		#pragma region typedef�ͳ�Ա�����Ķ���

		typedef T			value_type;
		typedef Ptr			pointer;
		typedef Ref			reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type; // ptrdiff_t��ʹ��Ҫ#include <memory>
		typedef T**			map_pointer; // �������������������û�������cghDeque�Ĺܿ����Ĺ���
		typedef __deque_iterator self;
		typedef __deque_iterator<T, T&, T*, BufSiz>		iterator;

		T* cur; // ��ǰλ��
		T* first; // ������ͷ��
		T* last; // ������β��
		map_pointer	node; // �������������������û�������cghDeque�Ĺܿ����Ĺ���

		#pragma endregion

		#pragma region �������ܿ����ĺ�cghDeque�ܿ����ĵ��ν�

		/*
			���������new_node��cghDeque�������Ļ�����λ�ã��ܿ����ĵ�ĳ���ڵ㣩
		*/
		void set_node(map_pointer new_node)
		{
			node = new_node; // ����cghDeque�ܿ����ĵ�ĳ���ڵ�͵�����������
			first = *new_node; // ������ͷ��
			last = first + difference_type(buffer_size()); // ������β��
		}

		#pragma endregion

		#pragma region ȷ��ÿ���������Ĵ�С

		/*
			������Ĭ�ϴ�СΪ512�ֽ�
			1.���BufSiz��Ϊ0������BufSiz����ʾbuffer_size���û��Զ���
			2.���BufSiz����ʾbuffer_sizeʹ��Ĭ��ֵ����ô���Ԫ�ش�С��sizeof(T)��С��512�ֽڣ�����size_t(512 / sizeof(T)
			  ���Ԫ�ش�С��sizeof(T)������512�ֽڣ�����1
		*/

		size_t buffer_size()
		{
			return BufSiz != 0 ? BufSiz : (sizeof(T) < 512 ? size_t(512 / sizeof(T)) : size_t(1));
		}
		#pragma endregion
		
		#pragma region ��������������

			#pragma region �������

		reference operator*() const{ return *cur; }
		pointer operator->()const{ return &(operator*()); }

		#pragma endregion

			#pragma region �������ĵ����ƶ�

		self& operator++()
		{
			++cur; // �л�����һ��Ԫ��
			// ��������ڻ�������β�ˣ�ע�⻺������ǰ�պ󿪵Ŀռ䣬last�ǻ������������ڱ�������last�͸��л���������
			if (cur == last) 
			{
				set_node(node + 1); // ���л����ܿ����ĵ���һ���ڵ㣨Ҳ����������
				cur = first; // ��һ���������ĵ�һ��Ԫ��
			}
			return *this;
		}

		self& operator++(int)
		{
			self tmp = *this;
			++*this;
			return tmp;
		}

		self& operator--()
		{
			if (cur == first) // ����������ڻ�������ͷ��
			{
				set_node(node - 1); // ���л����ܿ����ĵ�ǰһ���ڵ㣨Ҳ����������
				cur = last; // ��һ�������������һ��Ԫ��
			}
			// ע�⻺������ǰ�պ󿪵Ŀռ䣬last�ǻ������������ڱ�������û�����壬last��ǰһ��Ԫ�ز�����ȷ��ֵ��
			--cur;
			return *this;
		}

		self& operator--(int)
		{
			self tmp = *this;
			--*this;
			return tmp;
		}

		#pragma endregion

			#pragma region ������������ƶ�

		/*
			ʵ�������ȡ��random access��
		*/
		self& operator+=(difference_type n)
		{
			difference_type offset = n + (cur - first); // ƫ��
			// 1.offset >= 0�����ƫ��
			// 2.offset < difference_type(buffer_size())��ƫ��С�ڻ���������
			if (offset >= 0 && offset < difference_type(buffer_size()))
			{
				cur += n;
			}
			else
			{
				difference_type node_offset = offset > 0
					? offset / difference_type(buffer_size()) // ���ƫ�ƣ�ȷ���ܿ����ĵ�ƫ�ƵĽڵ㣨ƫ�ƶ��ٸ���������
					: -difference_type((-offset - 1) / buffer_size()) - 1; // ��ǰƫ�ƣ�ȷ���ܿ����ĵ�ƫ�ƵĽڵ㣨ƫ�ƶ��ٸ���������
				set_node(node + node_offset); // �ӹܿ�������ѡ���µĽڵ㣬�л�������
				cur = first + (offset - node_offset*difference_type(buffer_size()));
			}
			return *this;
		}

		/*
			ʵ�������ȡ��random access��
		*/
		self operator+(difference_type n) const
		{
			self tmp = *this;
			return tmp += n;
		}

		self& operator-=(difference_type n)const{ return *this += -n; }

		self operator-(difference_type n)const
		{
			self tmp = *this;
			return tnp -= n;
		}

		difference_type operator-(const self& x)
		{
			return difference_type(buffer_size())*(node - x.node - 1) + (cur - first) + (x.last - x.cur);
		}

		reference operator[](difference_type n)const{ return *(*this + n); }

		#pragma endregion

			#pragma region ���������໥�Ƚ�

		bool operator==(const self& x)const{ return cur == x.cur; }

		bool operator!=(const self& x)const{ return cur != x.cur; }

		bool operator<(const self& x)const
		{
			return (node == x.node) ? (cur < x.cur) : (node < x.node);
		}

		#pragma endregion

		#pragma endregion
	};
}

#endif