/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件内容：equal、fill、fill_n、iter_sawp、max、min、
*			 lexicographical_compare、mismatch、copy 算法的实现
******************************************************************/

#ifndef _CGH_STL_ALGO_H_
#define _CGH_STL_ALGO_H_

#include "cghSTL_iterator.h"
#include "cghStl_algobase.h"

namespace CGH{

#pragma region adjacent_find
	/*
		找出第一组满足条件的相邻元素。这里所谓的条件，在版本一种指的是“两元素相等”
		在版本二中，允许用户指定一个二元运算，二元运算的操作数分别是相邻的第一个元素和第二个元素
	*/
	template<class ForwardIterator>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last)
	{
		if (first == last)
		{
			return last;
		}
		ForwardIterator next = first;
		while (++next != last)
		{
			if (*first == *next)
			{
				return first;
			}
			first = next;
		}
		return last;
	}

	/* 查找相邻的重复元素，版本二 */
	template<class ForwardIterator, class binaryPredicate>
	ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, binaryPredicate binary_pred)
	{
		if (first == last)
		{
			return last;
		}
		ForwardIterator next = first;
		while (++next != last)
		{
			if (binary_pred(*first, *next))
			{
				return first;
			}
			first = next;
		}
		return last;
	}
#pragma endregion

#pragma region count
	/* 运用equality操作符，将 [ first, last ) 区间内的每一个元素拿来和指定值 value 做比较，返回与 value 相等的元素个数 */
	template<class InputIterator, class T>
	typename std::iterator_traits<InputIterator>::difference_type
	count(InputIterator first, InputIterator last, const T& value)
	{
		typename std::iterator_traits<InputIterator>::difference_type n = 0;
		for (; first != last; ++first)
		{
			if (*first == value)
			{
				++n;
			}
		}
		return n;
	}
#pragma endregion

#pragma region count_if
	/* 将指定操作 pred 实施于 [ first, last )区间内的每一个元素，并返回“造成 pred 计算结果为 true ”的元素个数 */
	template<class InputIterator, class predicate>
	typename std::iterator_traits<InputIterator>::difference_type
	count_if(InputIterator first, InputIterator last, predicate pred)
	{
		typename std::iterator_traits<InputIterator>::difference_type n = 0;
		for (; first != last; ++first)
		{
			if (pred(*first))
			{
				++n;
			}
		}
		return n;
	}
#pragma endregion

#pragma region find
	/* 
		根据equality操作符，循序查找 [ first, last ) 内所有元素，找出第一个匹配“等同条件”者，如果找到，
		返回 InputIterator 指向该元素，反则返回迭代器的last
	*/
	template<class InputIterator, class T>
	InputIterator find(InputIterator first, InputIterator last, const T& value)
	{
		while (first != last && *first != value)
		{
			++first;
		}
		return first;
	}
#pragma endregion

#pragma region find_if
	/* 
		根据指定的 pred 运算条件，循序查找 [ first, last ) 内的所有元素，找出第一个令 pred 运算结果为真者 
		如果找到，返回 InputIterator 指向该元素
		没有找到，返回 last
	*/
	template<class InputIterator, class predicate>
	InputIterator find_if(InputIterator first, InputIterator last, predicate pred)
	{
		while (first != last && !pred(*first))
		{
			++first;
		}
		return first;
	}
#pragma endregion

#pragma region for_each
	/*
		将仿函数 f 实施于 [ first, last ) 区间内的每一个元素上。
		f 不可以改变元素内容，因为 first，last 都是 InputIterator ，不保证接受赋值行为
	*/
	template<class InputIterator, class function>
	function for_each(InputIterator first, InputIterator last, function f)
	{
		for (; first != last; ++first)
		{
			f(*first);
		}
		return f;
	}
#pragma endregion

#pragma region generate
	/* 将仿函数 gen 的元素结果填写在 [ first, last ) 区间内的所有元素上，填写使用了迭代器的 assignment 操作符 */
	template<class ForwardIterator, class Generator>
	void generate(ForwardIterator first, ForwardIterator last, Generator gen)
	{
		for (; first != last; ++first)
		{
			*first = get() ;
		}
	}
#pragma endregion

#pragma region generate_n
	/* 将仿函数 gen 的元素结果填写在 first 开始的 n 个元素上，填写使用了迭代器的 assignment 操作符 */
	template<class OutputIterator, class size, class Generator>
	void generate_n(OutputIterator first, size n, Generator gen)
	{
		for (; n > 0; --n, ++first)
		{
			*first = get() ;
		}
	}
#pragma endregion

}

#endif