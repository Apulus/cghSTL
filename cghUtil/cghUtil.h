/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  内容:cghSTL的工具类
******************************************************************/

#ifndef _CGH_PAIR
#define _CGH_PAIR

namespace CGH{
	template<class T1,class T2>
	struct cghPair {
		typedef T1	first_type;
		typedef T2	second_type;

		T1 first;
		T2 second;

		cghPair() :first(T1()), second(T2()){}
		cghPair(const T1& a, const T2&b) :first(a), second(b){}
	};

	template <class T> 
	void swap(T& a, T& b)
	{
		T c(a); a = b; b = c;
	}
}

#endif