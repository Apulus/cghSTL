/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ����ݣ�equal��fill��fill_n��iter_sawp��max��min��
*			 lexicographical_compare��mismatch��copy �㷨��ʵ��
******************************************************************/

#ifndef _CGH_STL_ALGO_H_
#define _CGH_STL_ALGO_H_

#include "cghSTL_iterator.h"
#include "cghStl_algobase.h"

namespace CGH{

#pragma region adjacent_find
	/*
		�ҳ���һ����������������Ԫ�ء�������ν���������ڰ汾һ��ָ���ǡ���Ԫ����ȡ�
		�ڰ汾���У������û�ָ��һ����Ԫ���㣬��Ԫ����Ĳ������ֱ������ڵĵ�һ��Ԫ�غ͵ڶ���Ԫ��
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

	/* �������ڵ��ظ�Ԫ�أ��汾�� */
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
	/* ����equality���������� [ first, last ) �����ڵ�ÿһ��Ԫ��������ָ��ֵ value ���Ƚϣ������� value ��ȵ�Ԫ�ظ��� */
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
	/* ��ָ������ pred ʵʩ�� [ first, last )�����ڵ�ÿһ��Ԫ�أ������ء���� pred ������Ϊ true ����Ԫ�ظ��� */
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
		����equality��������ѭ����� [ first, last ) ������Ԫ�أ��ҳ���һ��ƥ�䡰��ͬ�������ߣ�����ҵ���
		���� InputIterator ָ���Ԫ�أ����򷵻ص�������last
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
		����ָ���� pred ����������ѭ����� [ first, last ) �ڵ�����Ԫ�أ��ҳ���һ���� pred ������Ϊ���� 
		����ҵ������� InputIterator ָ���Ԫ��
		û���ҵ������� last
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
		���º��� f ʵʩ�� [ first, last ) �����ڵ�ÿһ��Ԫ���ϡ�
		f �����Ըı�Ԫ�����ݣ���Ϊ first��last ���� InputIterator ������֤���ܸ�ֵ��Ϊ
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
	/* ���º��� gen ��Ԫ�ؽ����д�� [ first, last ) �����ڵ�����Ԫ���ϣ���дʹ���˵������� assignment ������ */
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
	/* ���º��� gen ��Ԫ�ؽ����д�� first ��ʼ�� n ��Ԫ���ϣ���дʹ���˵������� assignment ������ */
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