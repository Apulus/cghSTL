/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件内容：cghSTL 数值算法
******************************************************************/

#ifndef _CGH_STL_ALGORITHMS_NUMERIC_
#define _CGH_STL_ALGORITHMS_NUMERIC_

#include "cghUtil.h"

namespace CGH{

	#pragma region accumulate

	/*
		accumulate算法用来计算 init 和 [ first, last )内所有元素的总和
		必须提供 init ，因为当 [ first, last )为空时仍能获得一个明确定义的值
		如果希望计算 [ first, last )中所有数值的总和，应该将 init 设为 0
	*/
	template<class iterator, class T>
	T accumulate(iterator first, iterator last, T init)
	{
		for (; first != last; ++first)
		{
			init = init + *first; // 将每个元素值累加到 init 上
		}
		return init;
	}

	/* binaryOp：用户指定的计算方法 */
	template<class iterator, class T, class binaryOp>
	T accumulate(iterator first, iterator last, T init, binaryOp binary_op)
	{
		for (; first != last; ++first)
		{
			init = binary_op(init, *first); // binary_op：特定的计算方式
		}
		return init;
	}

	#pragma endregion

	#pragma region ajacent_difference

	/*
		ajacent_difference 算法用来计算[ first, last ] 中相邻元素的差额
	*/
	template<class InputIterator, class OutputIterator>
	OutputIterator ajacent_difference(InputIterator first, InputIterator last, OutputIterator result)
	{
		if (first == last)
		{
			return result;
		}
		*result = *first; // 记录第一个元素
		iterator_traits<InputIterator>::value_type value = *first; // 利用特性萃取机取出value_type的类型
		while (++first != last)
		{
			iterator_traits<InputIterator>::value_type tmp = *first; // 将相邻两个元素的差值赋给result
			*++result = tmp - value;
			value = tmp;
		}

		iterator_traits<InputIterator>::value_type tmp = *first;
		*first = *last;
		*last = tmp;

		return ++result;
	}

	template<class InputIterator, class OutputIterator, class binaryOp>
	OutputIterator ajacent_difference(InputIterator first, InputIterator last, OutputIterator result, binaryOp binary_op)
	{
		if (first == last)
		{
			return result;
		}
		*result = *first; // 记录第一个元素
		iterator_traits<InputIterator>::value_type value = *first; // 利用特性萃取机取出value_type的类型
		while (++first != last)
		{
			iterator_traits<InputIterator>::value_type tmp = *first;
			*++result = binary_op(tmp, value); // 以用户自定义的方式计算相邻两个元素的值，并赋给result
			value = tmp;
		}
		return ++result;
	}

	#pragma endregion

	#pragma region inner_product

	/* 
		inner_product能够计算[ first1, last1 ] 和 [ fisrt2, first2 + ( last1 - fisrt1 ) ] 的一般内积（generalied inner product）
		必须提供初值，确保 [ fisrt, last ] 为空时，仍有明确定义
	*/
	template<class InputIterator1,class InputIterator2,class T>
	T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			init = init + (*first1) * (*first2); // 计算内积
		}
		return init;
	}

	template<class InputIterator1, class InputIterator2, class T, class binaryOp1, class binaryOp2>
	T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init, binaryOp1 binary_op1, binaryOp2 binary_op2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			init = binary_op1(init, binary_op2(*first1, *first2)); // 根据用户自定义的函数：binary_op1、binary_op2，计算内积
		}
		return init;
	}

	#pragma endregion

	#pragma region partial_sum

	/*
		partial_sum用来计算局部总和，它会将 *first 赋值给 *result ，将 *first和 *(first + １)的和赋值给 *( result + 1 ),
		以此类推，注意，result 可以等于 first，这使得我们得以完成就地计算。
	*/
	template<class InputIterator, class OutputIterator>
	OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result)
	{
		if (first == last)
		{
			return result;
		}
		*result = *first;
		iterator_traits<InputIterator>::value_type value = *first;
		while (++first != last)
		{
			value = value + *first ; // 值的累加
			*++result = value ;
		}
		return ++result ;
	}

	template<class InputIterator, class OutputIterator, class binaryOp>
	OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result, binaryOp binary_op)
	{
		if(first == last)
		{
			return result;
		}
		*result = *first;
		iterator_traits<InputIterator>::value_type value = *first;
		while(++first != last)
		{
			value = binary_op( value, *first ) ; // 以用户指定的方法累加值
			*++result = value ;
		}
		return ++result ;
	}

	#pragma endregion

	#pragma region power

	/* 
		计算某数的 n 次幂
	*/
	template<class T, class Integer>
	inline T power(T x, Integer n)
	{
		return power(x, n, multiplies<T>()) ;
	}

	template<class T, class Integer, class MonoidOp>
	T power(T x, Integer n, MonoidOp op)
	{
		while ((n & 1) == 0)
		{
			n = n >> 1 ;
			x = op(x, x) ;
		}
		T result = x ;
		n = n >> 1 ;
		while (n != 0)
		{
			x = op(x, x) ;
			if ((n & 1) != 0)
			{
				result = op(result, x) ;
			}
			n = n >> 1 ;
		}
		return result ;
	}

	#pragma endregion

}

#endif