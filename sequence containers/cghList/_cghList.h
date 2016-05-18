/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  功能:_cghList的实现代码
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

	#pragma region 内存控制、节点构造与析构
	protected:
		link_type node; // _cghList中唯一的节点指针，指向_cghList的尾部
		typedef simple_alloc<list_node, Alloc> list_node_allocator; // 定义空间配置器
		link_type get_node(){ return list_node_allocator::allocate(); } // 申请一个节点的内存空间
		void put_node(link_type p){ list_node_allocator::deallocate(p); } // 释放一个节点的内存空间

		/*
			创建一个节点：
			1.调用get_node申请节点内存;
			2.调用construct构造节点
		*/ 
		link_type create_node(const T& x)
		{
			link_type p = get_node();
			construct(&p->data, x);
			return p;
		}

		/*
			销毁一个节点：
			1.调用destroy析构节点;
			2.调用put_node释放内存
		*/
		void destroy_node(link_type p)
		{
			destroy(&p->data);
			put_node(p);
		}

	public:
		/*
			构造函数：
			调用empty_initialize
		*/
		_cghList(){ empty_initialize(); }
	protected:
		/*
			构造一个空链表：
			1.申请一个节点内存
			2.初始化尾节点
		*/
		void empty_initialize()
		{
			node = get_node();
			node->next = node;
			node->prev = node;
		}
	#pragma endregion 

	public:
		#pragma region 链表的查询操作

		/*
			返回头节点：
			_cghList中的node成员变量保存了链表的尾指针
			链表的尾指针不参与运算，仅标识链表结尾
		*/
		iterator begin()const { return (link_type)((*node).next); }

		/*
			返回尾节点：
			_cghList中的node成员变量保存了链表的尾指针
			链表的尾指针不参与运算，仅标识链表结尾
		*/
		iterator end()const{ return node; }

		/*
			判断链表是否为空：
			_cghList中的node成员变量保存了链表的尾指针
			链表的尾指针不参与运算，仅标识链表结尾
		*/
		bool empty() const{ return node->next == node; }

		/*
			返回链表长度：
			_cghList中的node成员变量保存了链表的尾指针
			链表的尾指针不参与运算，仅标识链表结尾
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

		#pragma region 插入链表元素，包括头插和尾插

		/*
			插入到链表头部
		*/
		void push_back(const T& x){ insert(end(), x); }

		/*
			插入到链表尾部
		*/
		void push_front(const T& x){ insert(begin(), x); }

		/*
			执行具体的插入操作
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

		#pragma region 删除链表元素

		/*
			删除指定位置的链表节点
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
			删除链表头节点
		*/
		void pop_front(){ erase(begin()); }

		/*
			删除链表尾节点
		*/
		void pop_back()
		{
			iterator tmp = end();
			erase(--tmp);
		}

		/*
			清除整个链表
		*/
		void clear()
		{
			link_type cur = (link_type)node->next; //拿到头结点
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
			移除节点值为 value 的链表节点
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
			清除链表中连续存放的有相同节点值的元素
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
