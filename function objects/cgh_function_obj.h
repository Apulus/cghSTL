/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件内容：函数对象的实现
******************************************************************/

#ifndef _CGH_FUNCTION_OBJ_H_
#define _CGH_FUNCTION_OBJ_H_

#include "cghStl_funcbase.h"

namespace CGH{

#pragma region 算术类（Arithmetic）函数对象

	/* 相加 */
	template<class T>
	struct plus : public binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const
		{
			return x + y;
		}
	};

	/* 相减 */
	template<class T>
	struct minus : public binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const
		{
			return x - y;
		}
	};

	/* 相乘 */
	template<class T>
	struct multiplies : public binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const
		{
			return x * y;
		}
	};

	/* 相除 */
	template<class T>
	struct divides : public binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const
		{
			return x / y;
		}
	};

	/* 求余 */
	template<class T>
	struct modulus : public binary_function<T, T, T>
	{
		T operator()(const T& x, const T& y) const
		{
			return x % y;
		}
	};

	/* 取反 */
	template<class T>
	struct negate : public unary_function<T, T>
	{
		T operator()(const T& x) const
		{
			return -x;
		}
	};

#pragma endregion

#pragma region 关系运算类（Relational）函数对象

	/* 等于 */
	template<class T>
	struct equal_to : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x == y;
		}
	};

	/* 不等于 */
	template<class T>
	struct not_equal_to : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x != y;
		}
	};

	/* 大于 */
	template<class T>
	struct greater : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x > y;
		}
	};

	/* 小于 */
	template<class T>
	struct less : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x < y;
		}
	};

	/* 大于等于 */
	template<class T>
	struct greater_equal : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x >= y;
		}
	};

	/* 小于等于 */
	template<class T>
	struct less_equal : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x <= y;
		}
	};

#pragma endregion

#pragma region 逻辑运算类（logical）函数对象

	/* 逻辑与 */
	template<class T>
	struct logical_and : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x && y;
		}
	};

	/* 逻辑或 */
	template<class T>
	struct logical_or : public binary_function<T, T, bool>
	{
		bool operator()(const T& x, const T& y) const
		{
			return x || y;
		}
	};

	/* 逻辑非 */
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