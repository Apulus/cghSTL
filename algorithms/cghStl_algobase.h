/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件内容：equal、fill、fill_n、iter_sawp、max、min、
			 lexicographical_compare、mismatch、copy 算法的实现
******************************************************************/


#ifndef _CGH_STL_ALGOBASE_
#define _CGH_STL_ALGOBASE_

#include "cghUtil.h"
#include "cghSTL_type_traits.h"
#include "cghSTL_iterator.h"

namespace CGH{

	#pragma region equal

	/* 如果两个序列在 [ first, last ] 区间内相等，equal() 返回true，忽略第二个序列的元素多出来的部分 */
	template<class InputIterator1, class InputIterator2>
	inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (*first1 != *first2)
			{
				return false ; // 如果同一位置上的两个元素值不相等，返回false
			}
		}
		// 当第一个序列走完时（第二个序列一定要比第一个长，且不考虑第二个序列多出来的部分）
		// 两个序列相同位置的元素全部相等，返回true
		return true ;
	}

	/* 
		如果两个序列在 [ first, last ] 区间内相等，equal() 返回true，忽略第二个序列的元素多出来的部分 
		binaryPredicate：用户自定义的比较函数
	*/
	template<class InputIterator1, class InputIterator2, class binaryPredicate>
	inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, binaryPredicate binary_pred)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(binaryPredicate(*first1, *first2)))
			{
				return false ; // 如果同一位置上的两个元素值不相等（采用用户自定义的大小比较函数：binaryPredicate），返回false
			}
		}
		// 当第一个序列走完时（第二个序列一定要比第一个长，且不考虑第二个序列多出来的部分）
		// 两个序列相同位置的元素全部相等，返回true
		return true ;
	}

	#pragma endregion

	#pragma region fill

	/* 将 [ first, last ) 内的所有元素值改填为 value */
	template<class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		for (; first != last; ++first)
		{
			*first = value ;
		}
	}

	#pragma endregion

	#pragma region fill_n

	/* 将 [ first, last ) 内的前 n 个元素值改填为 value ，返回迭代器，指向被填入的最后一个元素的下一位置 */
	template<class OutputIterator, class size, class T>
	OutputIterator fill_n(OutputIterator first, size n, const T& value)
	{
		for (; n > 0; --n, ++first)
		{
			*first = value;
		}
		return first;
	}

	#pragma endregion

	#pragma region iter_sawp

	/* 将两个迭代器（ForwardIterator）所指的对象对调 */
	template<class ForwardIterator1, class ForwardIterator2>
	void iter_swap(ForwardIterator1 first, ForwardIterator2 last)
	{
		// iterator_traits：特性萃取机，获得迭代器指向的值类型
		std::iterator_traits<ForwardIterator1>::value_type tmp = *first;
		*first = *last;
		*last = tmp;
	}

	#pragma endregion

	#pragma region max  min

	/* 比较大小 */
	template<class T>
	inline const T& max(const T& a, const T& b)
	{
		return a > b ? a : b ;
	}

	/* compare：用户自定义的大小比较函数 */
	template<class T, class compare>
	inline const T& max(const T& a, const T& b, compare comp)
	{
		return comp(a, b) ? a : b ;
	}

	/* 比较大小 */
	template<class T>
	inline const T& min(const T& a, const T& b)
	{
		return a < b ? a : b ;
	}

	/* compare：用户自定义的大小比较函数 */
	template<class T, class compare>
	inline const T& min(const T& a, const T& b, compare comp)
	{
		return comp(a, b) ? b : a ;
	}

	#pragma endregion

	#pragma region lexicographical_compare

	/*
		以“字典排列方式”对两个序列 [ first1, last1 ) 和 [ first2, last2 )进行比较，第一个序列以字典排序不小于第二个序列
		比较操作针对两个序列中对应位置上的元素进行，直到一下情况出现：
		1.两序列同一位置上的元素不相等；
		2.同时到达 last1 和 last2（两序列相等）；
		3.到达 last1 或者 last2（两序列不相等）；
	*/
	/*
		两序列第一次出现同一位置上元素不相等时，lexicographical_compare() 函数的返回值有一下可能：
		1.如果第一个序列的元素比较小，返回 true ，否则返回 false；
		2.如果到达 last1 而尚未到达 last2，返回 true；
		3.如果到达 last2 而尚未到达 last1，返回 false；
		4.如果同时到达 last1 和 last2（注意，序列的区间是前闭后开，同时到达 last 说明所有元素都匹配），返回false；
	*/
	template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		// 以下任何一个序列到达尾端，就结束。，否则两序列一一比对相应元素
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (*first1 < *first2)
			{
				return true ; // 第一序列值小于第二序列相应值，返回 true
			}
			if (*first2 < *first1)
			{
				return false ; // 第一序列值大于第二序列相应值，返回 false
			}
			// 如果两序列同一位置元素相等，进入迭代器前进，下一轮比较
		}
		// 如果第一个序列到达尾端，但是第二个序列仍有剩余，那么第一个序列小于第二个序列
		return first1 == last1 && first2 != last2 ;
	}

	/* compare：用户指定的大小比较方法 */
	template<class InputIterator1, class InputIterator2, class compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, compare comp)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if ( comp( *first1, *first2 ) )
			{
				return true ;
			}
			if ( comp(*first2, *first1) )
			{
				return false ;
			}
		}
		return first1 == last1 && first2 != last2 ;
	}

	/* 为了增强效率，设计了特化版，使用原生指针 const unsigned char* */
	bool lexicographical_compare(const unsigned char* first1, const unsigned char* last1, const unsigned char* first2, const unsigned char* last2)
	{
		const size_t len1 = last1 - first1 ; // 第一个序列的长度
		const size_t len2 = last2 - first2 ; // 第二个序列的长度
		const int result = memcmp(first1, first2, CGH::min(len1, len2)); // 使用memcmp比较长度相同的部分
		return result != 0 ? result < 0 : len1 < len2 ; // 如果不相上下，则长度较长者视为比较大
	}
	#pragma endregion

	#pragma region mismatch

	/* 
		比较两个序列，指出两者之间第一个不匹配的点，返回一对迭代器，分别指向两序列中不匹配的点
		如果两序列对应元素都匹配，返回的便是两序列各自的 last 迭代器
		如果第二个序列比第一个序列长，忽略多出来的部分
		默认情况下是 equality 操作符比较元素
	*/
	template<class InputIterator1, class InputIterator2>
	cghPair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1 && *first1 == *first2)
		{
			++first1;
			++first2;
		}
		return cghPair<InputIterator1, InputIterator2>(first1, first2) ;
	}

	/* BinaryPredicator：用户自定义比较操作 */
	template<class InputIterator1, class InputIterator2, class BinaryPredicator>
	cghPair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicator binary_pre)
	{
		while (first1 != last1 && binary_pre(*first1, *first2))
		{
			++first1;
			++first2;
		}
		return cghPair<InputIterator1, InputIterator2>(first1, first2) ;
	}

	#pragma endregion

}

namespace CGH{
	#pragma region copy

#pragma region 第一层：copy 算法入口

	/* copy 算法唯一的对外接口（完全泛化版）*/
	template<class InputIterator, class OutputIterator>
	inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		return copy_dispatch<InputIterator, OutputIterator>()(first, last, result);
	}

	#pragma region copy的特化版（specialization）

	/* copy 算法针对const char* 版本的特化版 */
	inline char* copy(const char* first, const char* last, char* result)
	{
		// 采用 memmove 的方式直接复制数据，cgh_memmove 函数位于 cghUtil.h 文件
		cgh_memmove(result, first, last - first) ;
		return result + (last - first) ;
	}

	/* copy 算法针对const wchar_t* 版本的特化版 */
	inline wchar_t* copy(const wchar_t* first, const wchar_t* last, wchar_t* result)
	{
		// 采用 memmove 的方式直接复制数据，cgh_memmove 函数位于 cghUtil.h 文件
		cgh_memmove(result, first, sizeof(wchar_t) * (last - first)) ;
		return result + (last - first) ;
	}
	#pragma endregion

#pragma endregion

#pragma region 第二层：copy_dispatch

	template<class InputIterator, class OutputIterator>
	struct copy_dispatch{
		OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result)
		{
			return _copy(first, last, result, CGH::iterator_category(first));
		}
	};

	#pragma region copy_dispatch 的偏特化版本

	/*
		在参数为原生指针的情况下，进一步探测指针指向的对象是否具有 trivial assignment operator
		assignment operator 对效率的影响不小
		1.如果指针指向的对象具有 non-trivial assignment operator，复制操作就必须通过 trivial assignment operator 进行
		2.如果指针指向的对象具有 trivial assignment operator，我们完全可以通过最快的内存拷贝（memmove进行）
	*/
	template<class T>
	struct copy_dispatch<T*, T*>{
		T* operator()(T* first, T* last, T* result)
		{
			// 通过特性萃取机（cghSTL_type_traits），获得对象 assignment operator 类型
			typedef typename cghSTL_type_traits<T>::has_trivial_assignment_operator	t;
			return _copy_t(first, last, result, t());
		}
	};

	/*
		在参数为原生指针的情况下，进一步探测指针指向的对象是否具有 trivial assignment operator
		assignment operator 对效率的影响不小
		1.如果指针指向的对象具有 non-trivial assignment operator，复制操作就必须通过 trivial assignment operator 进行
		2.如果指针指向的对象具有 trivial assignment operator，我们完全可以通过最快的内存拷贝（memmove进行）
	*/
	template<class T>
	struct copy_dispatch<const T*, T*>{
		T* operator()(T* first, T* last, T* result)
		{
			// 通过特性萃取机（cghSTL_type_traits），获得对象 assignment operator 类型
			typedef typename cghSTL_type_traits<T>::has_trivial_assignment_operator	t;
			return _copy_t(first, last, result, t());
		}
	};

	#pragma endregion

#pragma endregion

#pragma region 第三层
	template<class InputIterator, class OutputIterator>
	inline OutputIterator _copy(InputIterator first, InputIterator last, OutputIterator result, CGH::input_iterator_tag)
	{
		// 以迭代器是否到达末尾，决定循环结束，速度慢
		for (; first != last; ++result, ++first)
		{
			*result = *first ;
		}
		return result ;
	}

	template<class RandomAccessIterator, class OutputIterator>
	inline OutputIterator _copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, CGH::random_access_iterator_tag)
	{
		return _copy_d(first, last, result, distance_type(first)) ;
	}

	/* 如果对象拥有 non-trivial assignment operator 那么直接进行内存拷贝 */
	template<class T>
	inline T* _copy_t(const T* first, const T* last, T* result, true_type)
	{
		cgh_memmove(result, first, sizeof(T) * (last - first)) ;
		return result + (last - first) ;
	}

	/* 如果对象拥有 trivial assignment operator 那么调用_copy_d，用自定义的 assignment operator，挨个对象拷贝 */
	template<class T>
	inline T* _copy_t(const T* first, const T* last, T* result, false_type)
	{
		return _copy_d(first, last, result, (ptrdiff_t*)0);
	}

	template<class RandomAccessIterator, class OutputIterator, class Distance>
	inline OutputIterator _copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, Distance*)
	{
		// 以 n 决定循环次数，速度比用迭代器决定循环次数更高效
		for (Distance n = last - first; n > 0; --n, ++result, ++first)
		{
			*result = *first ;
		}
		return result ;
	}
#pragma endregion

	#pragma endregion

#pragma region copy_backward

#pragma region 第一层：copy_backward 算法入口

	/*
		将 [ first,last ) 内的每一个元素，以逆行的方向复制到以 result - 1 为起点，方向也为逆行的区间上]
		* ( result - 1 ) = * ( last - 1 ) ;
		* ( result - 2 ) = * ( last - 2 ) ;
		* ( result - 3 ) = * ( last - 3 ) ;
		...
	*/
	template <class InputIterator, class OutputIterator>
	inline OutputIterator copy_backward(InputIterator first, InputIterator last, OutputIterator result)
	{
		return copy_backward_dispatch<InputIterator, OutputIterator>()(first, last, result);
	}

#pragma endregion

#pragma region 第二层：copy_backward_dispatch

	template <class InputIterator, class OutputIterator>
	struct copy_backward_dispatch
	{
		OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result)
		{
			return __copy_backward(first, last, result);
		}
	};

	#pragma region copy_backward_dispatch 的特化版
	template <class T>
	struct copy_backward_dispatch<T*, T*>
	{
		T* operator()(T* first, T* last, T* result)
		{
			typedef typename cghSTL_type_traits<T>::has_trivial_assignment_operator t;
			return __copy_backward_t(first, last, result, t());
		}
	};

	template <class T>
	struct copy_backward_dispatch<const T*, T*>
	{
		T* operator()(const T* first, const T* last, T* result)
		{
			typedef typename cghSTL_type_traits<T>::has_trivial_assignment_operator t;
			return __copy_backward_t(first, last, result, t());
		}
	};
	#pragma endregion

#pragma endregion

#pragma region 第三层

	template <class InputIterator, class OutputIterator>
	inline OutputIterator __copy_backward(OutputIterator first, InputIterator last, OutputIterator result)
	{
		while (first != last) *--result = *--last;
		return result;
	}

	template <class T>
	inline T* __copy_backward_t(const T* first, const T* last, T* result, true_type)
	{
		const ptrdiff_t N = last - first;
		memmove(result - N, first, sizeof(T) * N);
		return result - N;
	}

	template <class T>
	inline T* __copy_backward_t(const T* first, const T* last, T* result,
		false_type)
	{
		return __copy_backward(first, last, result);
	}

#pragma endregion

#pragma endregion
}

#endif