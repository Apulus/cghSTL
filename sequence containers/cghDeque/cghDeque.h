/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ����:cghDeque��ʵ�ִ���
******************************************************************/

#ifndef _CGH_DEQUE_
#define _CGH_DEQUE_

#include "cghAlloc.h"
#include "globalConstruct.h"
#include "cghDequeIterator.h"
#include <algorithm>

namespace CGH{
	template<class T, class Alloc = cghAllocator<T>, size_t BufSiz = 0>
	class cghDeque{

		#pragma region typedef�ͳ�Ա�����Ķ���
	public:
		typedef T				value_type;
		typedef value_type*		pointer;
		typedef value_type&		reference;
		typedef size_t			size_type;
		typedef ptrdiff_t	difference_type;
		typedef typename __deque_iterator<T, T&, T*, BufSiz>::iterator iterator; // ��������#include "cghDequeIterator.h"

	protected:
		typedef pointer* map_pointer;
	protected:
		iterator start;
		iterator finish;
		map_pointer map; // �ܿ�����
		size_type map_size;

		#pragma endregion

		#pragma region ��������

	protected:
		/*
			�ܿ����ģ�map��ÿ���ڵ�ָ��Ļ�������С
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
				
		#pragma region cghDeque�ĳ�ʼ��

	protected:
		typedef simple_alloc<value_type, Alloc>		data_allocator; // cghDeque�ڵ�Ŀռ�������
		typedef simple_alloc<pointer, Alloc>		map_allocator; // cghDeque�ܿ����ģ�map���Ŀռ�������
	public:
		/*
		���캯��
		*/
		cghDeque(int n, const value_type& value) :start(), finish(), map(0), map_size(0)
		{
			fill_initialize(n, value);
		}
	protected:

		/*
		���ֳ�ʼ��
		*/
		void fill_initialize(size_type n, const value_type& value)
		{
			create_map_and_nodes(n);
			map_pointer cur;
			for (cur = start.node; cur < finish.node; ++cur)
			{
				std::uninitialized_fill(*cur, *cur + buffer_size(), value);
			}
			std::uninitialized_fill(finish.first, finish.cur, value);
		}

		/*
		��ʼ���ܿ����ģ�map�����ܿ�����ÿ���ڵ����Ļ�������С
		*/
		void create_map_and_nodes(size_type num_elements)
		{
			// ��Ҫ��ʼ���Ľڵ��� = ��Ԫ�ظ��� / ÿ�������������ɵ�Ԫ�ظ����� +����
			size_type num_nodes = num_elements / buffer_size() + 1;
			// һ���ܿ����ģ�map��Ҫ�������ڵ㣬����8��������ǡ�����ڵ��� + 2��
			map_size = std::max(initial_map_size(), num_nodes + 2); // std::max ��Ҫ #include <algorithm>
			// ���ó�һ�����С�map_size���ڵ㡱�Ĺܿ����ģ�map��
			map = map_allocator::allocate(map_size);
			// ��nstart��nfinishָ��ܿ����ģ�map�����нڵ���м�
			// �������м䣬��ʹͷβ������������һ����
			map_pointer nstart = map + (map_size - num_nodes) / 2;
			map_pointer nfinish = nstart + num_nodes - 1;

			// Ϊ�ܿ����ģ�map����ÿ�����ýڵ����û����������л���������������cghDeque�Ŀ��ÿռ�
			map_pointer cur;
			for (cur = nstart; cur <= nfinish; ++cur)
			{
				*cur = allocate_node(); // ���û�����
			}
			start.set_node(nstart); // �ν�start������
			finish.set_node(nfinish); // �ν�finish������
			start.cur = start.first; // ȷ��start���������α�
			finish.cur = finish.first + num_elements % buffer_size(); // ȷ��finish���������α�
		}

		/*
		�ܿ����ģ�map����С�ڵ���
		*/
		size_type initial_map_size(){ return (size_type)8; }

		/*
		���ùܿ����ģ�map��ÿ���ڵ�Ļ�������С
		*/
		pointer allocate_node()
		{
			return data_allocator::allocate(buffer_size() / sizeof(T));
		}

		/*
		�ͷŹܿ����ģ�map���ڵ�Ļ�����
		*/
		void deallocate_node(void* node)
		{
			data_allocator::deallocate(node);
		}

		#pragma endregion

		#pragma region cghDeque�Ĳ�ѯ����

	public:
		iterator begin(){ return start; } // ���cghDeque��ͷ��

		iterator end(){ return finish; } // ���cghDeque��β��

		reference operator[](size_type n){ return start[difference_type(n)]; } // ���cghDeque��n��Ԫ��

		reference front(){ return *start; } // ���cghDeque��ͷ����ֵ

		/*
			��Ϊ��������ǰ�պ󿪵����䣬���cghDeque��β��ʱ��Ҫfinish����һ������
		*/
		reference back()
		{
			iterator tmp = finish;
			--tmp;
			return *tmp;
		}

		/*
			���cghDeque�ĳ���
		*/
		size_type size()
		{
			return finish - start;
		}

		size_type max_size() const{ return finish - start; } // ���cghDeque�����̳���

		bool empty()const{ return finish == start; } // cghDeque�Ƿ�Ϊ��

		#pragma endregion

		#pragma region cghDequeԪ�ص���Ӻ�ɾ������

	public:

		/*
			��cghDequeβ������Ԫ��
		*/
		void push_back(const value_type& t)
		{
			// ��������ǰ�պ󿪵����䣬finish��������lastԪ�����ڱ�
			// �������finish.last��˵��������β������������push_back_aux�������ܿ����ģ�map������һ���ڵ㣬Ҳ������һ��������
			if (finish.cur != finish.last - 1)
			{
				construct(finish.cur, t);
				++finish.cur;
			}
			else
			{
				push_back_aux(t);
			}
		}
		
		/*
			��cghDequeͷ������Ԫ��
		*/
		void push_front(const value_type& t)
		{
			// ���û�е��ﻺ����ͷ����˵��������ǰ�벿����ʣ�ֱ࣬�Ӳ���
			// �������start.first��˵��������ͷ������������push_front_aux�������ܿ����ģ�map������һ���ڵ㣬Ҳ������һ��������
			if (start.cur != start.first)
			{
				construct(start.cur - 1, t);
				--start.cur;
			}
			else
			{
				push_front_aux(t);
			}
		}

		/*
			��cghDequeβ������Ԫ��
		*/
		void pop_back()
		{
			// ���û�е���finish��������ͷ����ֱ��destroy
			if (finish.cur != finish.first)
			{
				--finish.cur;
				destroy(finish.cur);
			}
			else
			{
				pop_back_aux(); // �������finish��ͷ����˵������Ҫ���ٵ�Ԫ�ؿ��˻�����������Ҫ����һ��������ȥɾ��Ԫ��
			}
		}

		/*
			��cghDequeͷ������Ԫ��
		*/
		void pop_front()
		{
			// ���û�е���start��������β��ֱ��destroy
			if (start.cur != start.last - 1)
			{
				destroy(start.cur);
				++start.cur;
			}
			else
			{
				pop_front_aux(); // �������start��β��˵������Ҫ���ٵ�Ԫ�ؿ��˻�����������Ҫ����һ��������ȥɾ��Ԫ��
			}
		}

		/*
			���cghDeque������Ԫ��
		*/
		void clear()
		{
			// [start.node, finish.node]����Ա�ģ����������[start.node, finish.node]��λ�������Ԫ��
			for (map_pointer node = start.node + 1; node < finish.node; ++node)
			{
				destroy(*node, *node + buffer_size());
				data_allocator::deallocate(*node, buffer_size());
			}
			// ���start.node != finish.node��˵��start��������finish���������˹ܿ����ĵĽڵ㣬Ҫ�ֱ����
			if (start.node != finish.node)
			{
				destroy(start.cur, start.last);
				destroy(finish.first, finish.last);
				data_allocator::deallocate(finish.first, buffer_size());
			}
			else // ���start.node == finish.node��˵��start��������finish�������ڹܿ�����ͬһ���ڵ���
			{
				destroy(start.cur, finish.cur);
			}
			finish = start; // ��Ҫ���ˣ�
		}
	protected:

		/*
			���������ʱ�ĺ��
		*/
		void push_back_aux(const value_type& t)
		{
			value_type t_copy = t;
			*(finish.node + 1) = allocate_node(); // ���ܿ����ģ�map������һ���ڵ㣨Ҳ������һ���������������ڴ�
			construct(finish.cur, t_copy); // ����Ԫ��
			finish.set_node(finish.node + 1); // ����finish��������ָ����һ��������
			finish.cur = finish.first; // ����finish���������α�
		}

		/*
			���������ʱ��ǰ��
		*/
		void push_front_aux(const value_type& t)
		{
			value_type t_copy = t;
			*(start.node - 1) = allocate_node(); // ���ܿ����ģ�map������һ���ڵ㣨Ҳ������һ���������������ڴ�
			start.set_node(start.node - 1); // ����start��������ָ����һ��������
			start.cur = start.last - 1; // ����start���������α�
			construct(start.cur, t_copy); // ����Ԫ��
		}

		/*
			���������ʱ�ĺ�ɾ
		*/
		void pop_back_aux()
		{
			deallocate_node(finish.first); // �ͷ��ڴ�
			finish.set_node(finish.node - 1); // ��һ��������
			finish.cur = finish.last - 1; // ����Ԫ�أ�ע�⻺������ǰ�պ�
			destroy(finish.cur); // ������һ�������������һ��Ԫ��
		}

		/*
			���������ʱ��ǰɾ
		*/
		void pop_front_aux()
		{
			destroy(start.cur); // ����Ԫ��
			deallocate_node(start.first); // �ͷ��ڴ�
			start.set_node(start.node + 1); // ��һ��������
			start.cur = start.first; // �����α�
		}

		#pragma endregion
	};
}
#endif