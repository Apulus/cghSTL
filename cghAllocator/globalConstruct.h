/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ����:ȫ�ֹ����������ʵ�ִ���
******************************************************************/

#include "stdafx.h"
#include <new.h>
#include <type_traits>
#ifndef _CGH_GLOBAL_CONSTRUCT_
#define _CGH_GLOBAL_CONSTRUCT_


namespace CGH
{
	#pragma region ͳһ�Ĺ�����������
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
		// ����������Ҫʹ��������ȡ����traits��̼��ɣ��ж�Ԫ���Ƿ�Ϊnon-trivial
		// non-trivial��Ԫ�ؿ���ֱ���ͷ��ڴ�
		// trivial��Ԫ��Ҫ����������������Ȼ���ͷ��ڴ�
		for (; first < last; ++first)
			destroy(&*first);
	}
	#pragma endregion 
}

#endif