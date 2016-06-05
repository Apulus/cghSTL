/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  内容:cghSTL的工具类
******************************************************************/

#ifndef _CGH_UTIL_
#define _CGH_UTIL_

namespace CGH{
	/* 自定义的pair */
	template<class T1,class T2>
	struct cghPair {
		typedef T1	first_type;
		typedef T2	second_type;

		T1 first;
		T2 second;

		cghPair() :first(T1()), second(T2()){}
		cghPair(const T1& a, const T2&b) :first(a), second(b){}
	};

	/* 交换函数 */
	template <class T> 
	void swap(T& a, T& b)
	{
		T c(a); a = b; b = c;
	}

	/* 复制函数 */
	void * __cdecl cgh_memmove ( void * dst, const void * src, size_t count)
	{
		void * ret = dst;
		if (dst <= src || (char *)dst >= ((char *)src + count))
		{
			// 若dst和src区域没有重叠，则从起始处开始逐一拷贝
			while (count--)
			{
				*(char *)dst = *(char *)src;
				dst = (char *)dst + 1;
				src = (char *)src + 1;
			}
		}
		else
		{ // 若dst和src 区域交叉，则从尾部开始向起始位置拷贝，这样可以避免数据冲突
			dst = (char *)dst + count - 1;
			src = (char *)src + count - 1;
			while (count--)
			{
				*(char *)dst = *(char *)src;
				dst = (char *)dst - 1;
				src = (char *)src - 1;
			}
		}
		return(ret);
	}

	/* 复制函数 */
	void * __cdecl cgh_memcpy(void * dst, const void * src, size_t count)
	{
		void * ret = dst;
		while (count--)
		{ // 注意， cgh_memcpy函数没有处理dst和src区域是否重叠的问题
			*(char *)dst = *(char *)src;
			dst = (char *)dst + 1;
			src = (char *)src + 1;
		}
		return(ret);
	}
}
#endif