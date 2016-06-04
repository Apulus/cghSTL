/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ����ݣ�cghSTL ��ֵ�㷨
******************************************************************/

#ifndef _CGH_STL_ALGORITHMS_NUMERIC_
#define _CGH_STL_ALGORITHMS_NUMERIC_

#include "cghUtil.h"

namespace CGH{

	#pragma region accumulate

	/*
		accumulate�㷨�������� init �� [ first, last )������Ԫ�ص��ܺ�
		�����ṩ init ����Ϊ�� [ first, last )Ϊ��ʱ���ܻ��һ����ȷ�����ֵ
		���ϣ������ [ first, last )��������ֵ���ܺͣ�Ӧ�ý� init ��Ϊ 0
	*/
	template<class iterator, class T>
	T accumulate(iterator first, iterator last, T init)
	{
		for (; first != last; ++first)
		{
			init = init + *first; // ��ÿ��Ԫ��ֵ�ۼӵ� init ��
		}
		return init;
	}

	/* binaryOp���û�ָ���ļ��㷽�� */
	template<class iterator, class T, class binaryOp>
	T accumulate(iterator first, iterator last, T init, binaryOp binary_op)
	{
		for (; first != last; ++first)
		{
			init = binary_op(init, *first); // binary_op���ض��ļ��㷽ʽ
		}
		return init;
	}

	#pragma endregion

	#pragma region ajacent_difference

	/*
		ajacent_difference �㷨��������[ first, last ] ������Ԫ�صĲ��
	*/
	template<class InputIterator, class OutputIterator>
	OutputIterator ajacent_difference(InputIterator first, InputIterator last, OutputIterator result)
	{
		if (first == last)
		{
			return result;
		}
		*result = *first; // ��¼��һ��Ԫ��
		iterator_traits<InputIterator>::value_type value = *first; // ����������ȡ��ȡ��value_type������
		while (++first != last)
		{
			iterator_traits<InputIterator>::value_type tmp = *first; // ����������Ԫ�صĲ�ֵ����result
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
		*result = *first; // ��¼��һ��Ԫ��
		iterator_traits<InputIterator>::value_type value = *first; // ����������ȡ��ȡ��value_type������
		while (++first != last)
		{
			iterator_traits<InputIterator>::value_type tmp = *first;
			*++result = binary_op(tmp, value); // ���û��Զ���ķ�ʽ������������Ԫ�ص�ֵ��������result
			value = tmp;
		}
		return ++result;
	}

	#pragma endregion

	#pragma region inner_product

	/* 
		inner_product�ܹ�����[ first1, last1 ] �� [ fisrt2, first2 + ( last1 - fisrt1 ) ] ��һ���ڻ���generalied inner product��
		�����ṩ��ֵ��ȷ�� [ fisrt, last ] Ϊ��ʱ��������ȷ����
	*/
	template<class InputIterator1,class InputIterator2,class T>
	T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			init = init + (*first1) * (*first2); // �����ڻ�
		}
		return init;
	}

	template<class InputIterator1, class InputIterator2, class T, class binaryOp1, class binaryOp2>
	T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init, binaryOp1 binary_op1, binaryOp2 binary_op2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			init = binary_op1(init, binary_op2(*first1, *first2)); // �����û��Զ���ĺ�����binary_op1��binary_op2�������ڻ�
		}
		return init;
	}

	#pragma endregion

	#pragma region partial_sum

	/*
		partial_sum��������ֲ��ܺͣ����Ὣ *first ��ֵ�� *result ���� *first�� *(first + ��)�ĺ͸�ֵ�� *( result + 1 ),
		�Դ����ƣ�ע�⣬result ���Ե��� first����ʹ�����ǵ�����ɾ͵ؼ��㡣
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
			value = value + *first ; // ֵ���ۼ�
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
			value = binary_op( value, *first ) ; // ���û�ָ���ķ����ۼ�ֵ
			*++result = value ;
		}
		return ++result ;
	}

	#pragma endregion

	#pragma region power

	/* 
		����ĳ���� n ����
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