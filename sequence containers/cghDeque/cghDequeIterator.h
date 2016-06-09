/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  功能:cghDeque的迭代器的实现代码
******************************************************************/

#ifndef _CGH_DEQUE_ITERATOR_
#define _CGH_DEQUE_ITERATOR_

#include <memory>
#include "cghSTL_iterator.h"
namespace CGH{

	template<class T, class Ref, class Ptr, size_t BufSiz>
	struct __deque_iterator : public random_access_iterator<T, ptrdiff_t>
	{

		#pragma region typedef和成员变量的定义

		typedef T			value_type;
		typedef Ptr			pointer;
		typedef Ref			reference;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type; // ptrdiff_t的使用要#include <memory>
		typedef T**			map_pointer; // 迭代器所属缓冲区，该缓冲区由cghDeque的管控中心管理
		typedef __deque_iterator self;
		typedef __deque_iterator<T, T&, T*, BufSiz>		iterator;

		T* cur; // 当前位置
		T* first; // 缓冲区头部
		T* last; // 缓冲区尾部
		map_pointer	node; // 迭代器所属缓冲区，该缓冲区由cghDeque的管控中心管理

		#pragma endregion

		#pragma region 迭代器管控中心和cghDeque管控中心的衔接

		/*
			输入参数：new_node，cghDeque传过来的缓冲区位置（管控中心的某个节点）
		*/
		void set_node(map_pointer new_node)
		{
			node = new_node; // 连接cghDeque管控中心的某个节点和迭代器缓冲区
			first = *new_node; // 缓冲区头部
			last = first + difference_type(buffer_size()); // 缓冲区尾部
		}

		#pragma endregion

		#pragma region 确定每个缓冲区的大小

		/*
			缓冲区默认大小为512字节
			1.如果BufSiz不为0，传回BufSiz，表示buffer_size由用户自定义
			2.如果BufSiz，表示buffer_size使用默认值，那么如果元素大小（sizeof(T)）小于512字节，传回size_t(512 / sizeof(T)
			  如果元素大小（sizeof(T)）大于512字节，传回1
		*/

		size_t buffer_size()
		{
			return BufSiz != 0 ? BufSiz : (sizeof(T) < 512 ? size_t(512 / sizeof(T)) : size_t(1));
		}
		#pragma endregion
		
		#pragma region 迭代器基本操作

			#pragma region 解除引用

		reference operator*() const{ return *cur; }
		pointer operator->()const{ return &(operator*()); }

		#pragma endregion

			#pragma region 迭代器的单步移动

		self& operator++()
		{
			++cur; // 切换至下一个元素
			// 如果到所在缓冲区的尾端，注意缓冲区是前闭后开的空间，last是缓冲区结束的哨兵，到达last就该切换缓冲区了
			if (cur == last) 
			{
				set_node(node + 1); // 就切换至管控中心的下一个节点（也即缓冲区）
				cur = first; // 下一个缓冲区的第一个元素
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
			if (cur == first) // 如果到达所在缓冲区的头部
			{
				set_node(node - 1); // 就切换至管控中心的前一个节点（也即缓冲区）
				cur = last; // 下一个缓冲区的最后一个元素
			}
			// 注意缓冲区是前闭后开的空间，last是缓冲区结束的哨兵，本身没有意义，last的前一个元素才有正确的值域
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

			#pragma region 迭代器的随机移动

		/*
			实现随机存取（random access）
		*/
		self& operator+=(difference_type n)
		{
			difference_type offset = n + (cur - first); // 偏移
			// 1.offset >= 0：向后偏移
			// 2.offset < difference_type(buffer_size())：偏移小于缓冲区长度
			if (offset >= 0 && offset < difference_type(buffer_size()))
			{
				cur += n;
			}
			else
			{
				difference_type node_offset = offset > 0
					? offset / difference_type(buffer_size()) // 向后偏移：确定管控中心的偏移的节点（偏移多少个缓冲区）
					: -difference_type((-offset - 1) / buffer_size()) - 1; // 向前偏移：确定管控中心的偏移的节点（偏移多少个缓冲区）
				set_node(node + node_offset); // 从管控中心中选择新的节点，切换缓冲区
				cur = first + (offset - node_offset*difference_type(buffer_size()));
			}
			return *this;
		}

		/*
			实现随机存取（random access）
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

			#pragma region 迭代器的相互比较

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