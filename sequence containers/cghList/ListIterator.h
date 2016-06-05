/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  功能:_cghList的迭代器的实现代码
******************************************************************/

#ifndef _CGH_LIST_ITERATOR_
#define _CGH_LIST_ITERATOR_

#include "ListNode.h"
#include <memory>
#include "cghSTL_iterator.h"
namespace CGH{
	template<class T, class Ref, class Ptr>
	struct __list_iterator : public bidirectional_iterator<T, ptrdiff_t>
	{
		typedef __list_iterator<T, T&, T*>		iterator;
		typedef __list_iterator<T, Ref, Ptr>	self;

		typedef T					value_type;
		typedef Ptr					pointer;
		typedef Ref					reference;
		typedef __list_node<T>*		link_type;
		typedef size_t				size_type;
		typedef ptrdiff_t			difference_type;

		link_type node; // 联系迭代器和链表节点的纽带

		#pragma region 构造函数

		__list_iterator(link_type x) : node(x){}
		__list_iterator(){}
		__list_iterator(const iterator& x) :node(x.node){}

		#pragma endregion

		#pragma region 迭代器的基本操作

		bool operator==(const self& x) const { return node == x.node; }
		bool operator!=(const self& x) const { return node != x.node; }
		reference operator*() const { return (*node).data; }
		reference operator->() const { return &(operator*()); }

		// 迭代器前进一个节点
		self& operator++()
		{
			node = (link_type)((*node).next);
			return *this;
		}
		self operator++(int)
		{
			self tmp = *this;
			++*this;
			return tmp;
		}

		// 迭代器递减1，后退一个节点
		self& operator--()
		{
			node = (link_type)((*node).prev);
			return *this;
		}
		self operator--(int)
		{
			self tmp = *this;
			--*this;
			return tmp;
		}

		#pragma endregion
	};
}
#endif