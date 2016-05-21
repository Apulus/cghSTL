/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件名称:queue的实现代码
******************************************************************/

#ifndef _CGH_DEQUE_QUEUE_
#define _CGH_DEQUE_QUEUE_

#include "cghDeque.h"
#include"cghAlloc.h"
#include "globalConstruct.h"

namespace CGH{
	/*
		采用cghDeque作为cghQueue的底层实现
	*/
	template<class T, class sequence = cghDeque<T>>
	class cghQueue{
	public:
		typedef typename sequence::value_type		value_type;
		typedef typename sequence::size_type		size_type;
		typedef typename sequence::reference		reference;

	protected:
		sequence s;

	public:
		cghQueue() :s(){ } // 构造函数
		bool empty() const{ return s.empty(); } // queue是否为空
		size_type size() { return s.size(); } // queue的长度
		reference front(){ return s.front(); } // 前端元素
		reference back(){ return s.back(); } // 末端元素
		void push(const value_type& x){ s.push_back(x); } // 末端进
		void pop(){ s.pop_front(); } // 前端出
	};
}

#endif