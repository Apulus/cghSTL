/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  功能:全局构造和析构的实现代码
******************************************************************/

#include "stdafx.h"
#include <new.h>
#include <type_traits>
#ifndef _CGH_GLOBAL_CONSTRUCT_
#define _CGH_GLOBAL_CONSTRUCT_


namespace CGH
{
	#pragma region 统一的构造析构函数
	template<class T1, class  T2>
	inline void construct(T1* p, const T2& value)
	{
		new (p)T1(value);
	}

	template<class T>
	inline void destroy(T* pointer)
	{
		pointer->~T();
	}

	template<class ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last)
	{
		// 本来在这里要使用特性萃取机（traits编程技巧）判断元素是否为non-trivial
		// non-trivial的元素可以直接释放内存
		// trivial的元素要做调用析构函数，然后释放内存
		for (; first < last; ++first)
			destroy(&*first);
	}
	#pragma endregion 
}

#endif