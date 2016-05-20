/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  功能:cghDeque的实现代码
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

		#pragma region typedef和成员变量的定义
	public:
		typedef T				value_type;
		typedef value_type*		pointer;
		typedef value_type&		reference;
		typedef size_t			size_type;
		typedef ptrdiff_t	difference_type;
		typedef typename __deque_iterator<T, T&, T*, BufSiz>::iterator iterator; // 迭代器，#include "cghDequeIterator.h"

	protected:
		typedef pointer* map_pointer;
	protected:
		iterator start;
		iterator finish;
		map_pointer map; // 管控中心
		size_type map_size;

		#pragma endregion

		#pragma region 辅助函数

	protected:
		/*
			管控中心（map）每个节点指向的缓冲区大小
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
				
		#pragma region cghDeque的初始化

	protected:
		typedef simple_alloc<value_type, Alloc>		data_allocator; // cghDeque节点的空间配置器
		typedef simple_alloc<pointer, Alloc>		map_allocator; // cghDeque管控中心（map）的空间配置器
	public:
		/*
		构造函数
		*/
		cghDeque(int n, const value_type& value) :start(), finish(), map(0), map_size(0)
		{
			fill_initialize(n, value);
		}
	protected:

		/*
		各种初始化
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
		初始化管控中心（map）、管控中心每个节点管理的缓冲区大小
		*/
		void create_map_and_nodes(size_type num_elements)
		{
			// 需要初始化的节点数 = （元素个数 / 每个缓冲区可容纳的元素个数） +　１
			size_type num_nodes = num_elements / buffer_size() + 1;
			// 一个管控中心（map）要管理几个节点，最少8个，最多是“所需节点数 + 2”
			map_size = std::max(initial_map_size(), num_nodes + 2); // std::max 需要 #include <algorithm>
			// 配置出一个具有“map_size个节点”的管控中心（map）
			map = map_allocator::allocate(map_size);
			// 令nstart和nfinish指向管控中心（map）所有节点的中间
			// 保持在中间，可使头尾两端扩充能量一样大
			map_pointer nstart = map + (map_size - num_nodes) / 2;
			map_pointer nfinish = nstart + num_nodes - 1;

			// 为管控中心（map）的每个现用节点配置缓冲区，所有缓冲区加起来就是cghDeque的可用空间
			map_pointer cur;
			for (cur = nstart; cur <= nfinish; ++cur)
			{
				*cur = allocate_node(); // 配置缓冲区
			}
			start.set_node(nstart); // 衔接start迭代器
			finish.set_node(nfinish); // 衔接finish迭代器
			start.cur = start.first; // 确定start迭代器的游标
			finish.cur = finish.first + num_elements % buffer_size(); // 确定finish迭代器的游标
		}

		/*
		管控中心（map）最小节点数
		*/
		size_type initial_map_size(){ return (size_type)8; }

		/*
		配置管控中心（map）每个节点的缓冲区大小
		*/
		pointer allocate_node()
		{
			return data_allocator::allocate(buffer_size() / sizeof(T));
		}

		/*
		释放管控中心（map）节点的缓冲区
		*/
		void deallocate_node(void* node)
		{
			data_allocator::deallocate(node);
		}

		#pragma endregion

		#pragma region cghDeque的查询操作

	public:
		iterator begin(){ return start; } // 获得cghDeque的头部

		iterator end(){ return finish; } // 获得cghDeque的尾部

		reference operator[](size_type n){ return start[difference_type(n)]; } // 获得cghDeque第n个元素

		reference front(){ return *start; } // 获得cghDeque的头部的值

		/*
			因为缓冲区是前闭后开的区间，获得cghDeque的尾部时需要finish回退一个步长
		*/
		reference back()
		{
			iterator tmp = finish;
			--tmp;
			return *tmp;
		}

		/*
			获得cghDeque的长度
		*/
		size_type size()
		{
			return finish - start;
		}

		size_type max_size() const{ return finish - start; } // 获得cghDeque的最大程长度

		bool empty()const{ return finish == start; } // cghDeque是否为空

		#pragma endregion

		#pragma region cghDeque元素的添加和删除操作

	public:

		/*
			在cghDeque尾部插入元素
		*/
		void push_back(const value_type& t)
		{
			// 缓冲区是前闭后开的区间，finish迭代器的last元素做哨兵
			// 如果到达finish.last，说明缓冲区尾部已满，调用push_back_aux，来到管控中心（map）的下一个节点，也就是下一个缓冲区
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
			在cghDeque头部插入元素
		*/
		void push_front(const value_type& t)
		{
			// 如果没有到达缓冲区头部，说明缓冲区前半部分有剩余，直接插入
			// 如果到达start.first，说明缓冲区头部已满，调用push_front_aux，来到管控中心（map）的上一个节点，也就是上一个缓冲区
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
			从cghDeque尾部弹出元素
		*/
		void pop_back()
		{
			// 如果没有到达finish迭代器的头部，直接destroy
			if (finish.cur != finish.first)
			{
				--finish.cur;
				destroy(finish.cur);
			}
			else
			{
				pop_back_aux(); // 如果到达finish的头部，说明我们要销毁的元素跨了缓冲区，我们要到上一个缓冲区去删除元素
			}
		}

		/*
			从cghDeque头部弹出元素
		*/
		void pop_front()
		{
			// 如果没有到达start迭代器的尾，直接destroy
			if (start.cur != start.last - 1)
			{
				destroy(start.cur);
				++start.cur;
			}
			else
			{
				pop_front_aux(); // 如果到达start的尾，说明我们要销毁的元素跨了缓冲区，我们要到下一个缓冲区去删除元素
			}
		}

		/*
			清除cghDeque的所有元素
		*/
		void clear()
		{
			// [start.node, finish.node]是满员的，所以先清除[start.node, finish.node]这段缓冲区的元素
			for (map_pointer node = start.node + 1; node < finish.node; ++node)
			{
				destroy(*node, *node + buffer_size());
				data_allocator::deallocate(*node, buffer_size());
			}
			// 如果start.node != finish.node，说明start迭代器和finish迭代器跨了管控中心的节点，要分别清除
			if (start.node != finish.node)
			{
				destroy(start.cur, start.last);
				destroy(finish.first, finish.last);
				data_allocator::deallocate(finish.first, buffer_size());
			}
			else // 如果start.node == finish.node，说明start迭代器和finish迭代器在管控中心同一个节点中
			{
				destroy(start.cur, finish.cur);
			}
			finish = start; // 不要忘了！
		}
	protected:

		/*
			缓冲区溢出时的后插
		*/
		void push_back_aux(const value_type& t)
		{
			value_type t_copy = t;
			*(finish.node + 1) = allocate_node(); // 给管控中心（map）的下一个节点（也就是下一个缓冲区）分配内存
			construct(finish.cur, t_copy); // 构造元素
			finish.set_node(finish.node + 1); // 重置finish迭代器，指向下一个缓冲区
			finish.cur = finish.first; // 重置finish迭代器的游标
		}

		/*
			缓冲区溢出时的前插
		*/
		void push_front_aux(const value_type& t)
		{
			value_type t_copy = t;
			*(start.node - 1) = allocate_node(); // 给管控中心（map）的上一个节点（也就是上一个缓冲区）分配内存
			start.set_node(start.node - 1); // 重置start迭代器，指向上一个缓冲区
			start.cur = start.last - 1; // 重置start迭代器的游标
			construct(start.cur, t_copy); // 构造元素
		}

		/*
			缓冲区溢出时的后删
		*/
		void pop_back_aux()
		{
			deallocate_node(finish.first); // 释放内存
			finish.set_node(finish.node - 1); // 上一个缓冲区
			finish.cur = finish.last - 1; // 重置元素，注意缓冲区是前闭后开
			destroy(finish.cur); // 析构上一个缓冲区的最后一个元素
		}

		/*
			缓冲区溢出时的前删
		*/
		void pop_front_aux()
		{
			destroy(start.cur); // 析构元素
			deallocate_node(start.first); // 释放内存
			start.set_node(start.node + 1); // 下一个缓冲区
			start.cur = start.first; // 重置游标
		}

		#pragma endregion
	};
}
#endif