/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ����ݣ����������ʵ��
******************************************************************/

#ifndef _CGH_FUNCTION_OBJ_H_
#define _CGH_FUNCTION_OBJ_H_

#include "cghStl_funcbase.h"

namespace CGH{

#pragma region �����ࣨArithmetic����������

	/* ��� */
	template<class T>
	struct plus : public binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const
		{
			return x + y;
		}
	};

	/* ��� */
	template<class T>
	struct minus : public binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const
		{
			return x - y;
		}
	};

	/* ��� */
	template<class T>
	struct multiplies : public binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const
		{
			return x * y;
		}
	};

	/* ��� */
	template<class T>
	struct divides : public binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const
		{
			return x / y;
		}
	};

	/* ���� */
	template<class T>
	struct modulus : public binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const
		{
			return x % y;
		}
	};

	/* ȡ�� */
	template<class T>
	struct negate : public unary_function<T, T>
	{
		T operator()(const T& x) const
		{
			return -x;
		}
	};

#pragma endregion

#pragma region ��ϵ�����ࣨRelational����������

	/* ���� */
	template<class T>
	struct equal_to : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x == y;
		}
	};

	/* ������ */
	template<class T>
	struct not_equal_to : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x != y;
		}
	};

	/* ���� */
	template<class T>
	struct greater : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x > y;
		}
	};

	/* С�� */
	template<class T>
	struct less : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x < y;
		}
	};

	/* ���ڵ��� */
	template<class T>
	struct greater_equal : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x >= y;
		}
	};

	/* С�ڵ��� */
	template<class T>
	struct less_equal : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x <= y;
		}
	};

#pragma endregion

#pragma region �߼������ࣨlogical����������

	/* �߼��� */
	template<class T>
	struct logical_and : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x && y;
		}
	};

	/* �߼��� */
	template<class T>
	struct logical_or : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x || y;
		}
	};

	/* �߼��� */
	template<class T>
	struct logical_not : public unary_function<T, bool>
	{
		bool operator()(const T& x) const
		{
			return !x;
		}
	};

#pragma endregion

}

#endif