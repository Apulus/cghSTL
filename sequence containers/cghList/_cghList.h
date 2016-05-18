/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ����:_cghList��ʵ�ִ���
******************************************************************/

#ifndef _CGH__LIST_
#define _CGH__LIST_

#include "ListNode.h"
#include "cghAlloc.h"
#include "globalConstruct.h"
#include "ListIterator.h"

namespace CGH{
	template<class T, class Alloc = cghAllocator<T>>
	class _cghList{
	protected:
		typedef __list_node<T>									list_node;
	public:
		typedef list_node*										link_type;
		typedef size_t											size_type;
		typedef typename __list_iterator<T, T&, T*>::iterator	iterator;

	#pragma region �ڴ���ơ��ڵ㹹��������
	protected:
		link_type node; // _cghList��Ψһ�Ľڵ�ָ�룬ָ��_cghList��β��
		typedef simple_alloc<list_node, Alloc> list_node_allocator; // ����ռ�������
		link_type get_node(){ return list_node_allocator::allocate(); } // ����һ���ڵ���ڴ�ռ�
		void put_node(link_type p){ list_node_allocator::deallocate(p); } // �ͷ�һ���ڵ���ڴ�ռ�

		/*
			����һ���ڵ㣺
			1.����get_node����ڵ��ڴ�;
			2.����construct����ڵ�
		*/ 
		link_type create_node(const T& x)
		{
			link_type p = get_node();
			construct(&p->data, x);
			return p;
		}

		/*
			����һ���ڵ㣺
			1.����destroy�����ڵ�;
			2.����put_node�ͷ��ڴ�
		*/
		void destroy_node(link_type p)
		{
			destroy(&p->data);
			put_node(p);
		}

	public:
		/*
			���캯����
			����empty_initialize
		*/
		_cghList(){ empty_initialize(); }
	protected:
		/*
			����һ��������
			1.����һ���ڵ��ڴ�
			2.��ʼ��β�ڵ�
		*/
		void empty_initialize()
		{
			node = get_node();
			node->next = node;
			node->prev = node;
		}
	#pragma endregion 

	public:
		#pragma region ����Ĳ�ѯ����

		/*
			����ͷ�ڵ㣺
			_cghList�е�node��Ա���������������βָ��
			�����βָ�벻�������㣬����ʶ�����β
		*/
		iterator begin()const { return (link_type)((*node).next); }

		/*
			����β�ڵ㣺
			_cghList�е�node��Ա���������������βָ��
			�����βָ�벻�������㣬����ʶ�����β
		*/
		iterator end()const{ return node; }

		/*
			�ж������Ƿ�Ϊ�գ�
			_cghList�е�node��Ա���������������βָ��
			�����βָ�벻�������㣬����ʶ�����β
		*/
		bool empty() const{ return node->next == node; }

		/*
			���������ȣ�
			_cghList�е�node��Ա���������������βָ��
			�����βָ�벻�������㣬����ʶ�����β
		*/
		size_type size()	const
		{
			size_type result = 0;
			iterator first = begin();
			iterator last = end();
			while (first != last)
			{
				++first;
				++result;
			}
			return result;
		}

		#pragma endregion

		#pragma region ��������Ԫ�أ�����ͷ���β��

		/*
			���뵽����ͷ��
		*/
		void push_back(const T& x){ insert(end(), x); }

		/*
			���뵽����β��
		*/
		void push_front(const T& x){ insert(begin(), x); }

		/*
			ִ�о���Ĳ������
		*/
		iterator insert(iterator position, const T& x)
		{
			link_type tmp = create_node(x);
			tmp->next = position.node;
			tmp->prev = position.node->prev;
			(link_type(position.node->prev))->next = tmp;
			position.node->prev = tmp;
			return tmp;
		}

		#pragma endregion

		#pragma region ɾ������Ԫ��

		/*
			ɾ��ָ��λ�õ�����ڵ�
		*/
		iterator erase(iterator position)
		{
			link_type next_node = link_type(position.node->next);
			link_type prev_node = link_type(position.node->prev);
			prev_node->next = next_node;
			next_node->prev = prev_node;
			destroy_node(position.node);
			return iterator(next_node);
		}

		/*
			ɾ������ͷ�ڵ�
		*/
		void pop_front(){ erase(begin()); }

		/*
			ɾ������β�ڵ�
		*/
		void pop_back()
		{
			iterator tmp = end();
			erase(--tmp);
		}

		/*
			�����������
		*/
		void clear()
		{
			link_type cur = (link_type)node->next; //�õ�ͷ���
			while (cur != node)
			{
				iterator tmp = cur;
				cur = (link_type)cur->next;
				destroy_node(tmp.node);
			}
			node->next = node;
			node->prev = node;
		}

		/*
			�Ƴ��ڵ�ֵΪ value ������ڵ�
		*/
		void remove(const T& value)
		{
			iterator first = begin();
			iterator last = end();
			while (first != last)
			{
				iterator next = first;
				++next;
				if (*first == value)erase(first);
				first = next;
			}
		}

		/*
			���������������ŵ�����ͬ�ڵ�ֵ��Ԫ��
		*/
		void unique(const T& value)
		{
			iterator first = begin();
			iterator last = end();
			if (first == last)return;
			iterator next = first;
			while (++next != last)
			{
				if (*first == *next)
				{
					erase(next);
				}
				else
				{
					first = next;
				}
				next = first;
			}
		}

		#pragma endregion
	};
}

#endif
