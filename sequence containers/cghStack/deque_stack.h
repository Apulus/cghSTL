/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件名称:stack的实现代码
******************************************************************/

#ifndef _CGH_DEQUE_STACK_
#define _CGH_DEQUE_STACK_

#include "cghDeque.h"
#include"cghAlloc.h"
#include "globalConstruct.h"

namespace CGH{
	/*
		采用cghDeque作为stack的底层实现
	*/
	template<class T, class sequence = cghDeque<T>>
	class cghStack{
	public:
		typedef typename sequence::value_type		value_type;
		typedef typename sequence::size_type		size_type;
		typedef typename sequence::reference		reference;

	protected:
		sequence s;

	public:
		cghStack() :s(){ } // 构造函数
		bool empty() const{ return s.empty(); } // stack是否为空
		size_type size() { return s.size(); } // stack的长度
		reference top() { return s.back(); } // 栈顶元素
		void push(const value_type& x){ s.push_back(x); } // 压栈
		void pop(){ s.pop_back(); } // 弹栈
	};
}

#endif