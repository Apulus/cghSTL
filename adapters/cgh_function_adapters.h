/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  功能：函数配接器的实现
******************************************************************/

#ifndef _CGH_FUNCTION_ADAPTERS_H_
#define _CGH_FUNCTION_ADAPTERS_H_

#include "cghStl_funcbase.h"

namespace CGH{

	#pragma region cgh_unary_negate
	
	template<class predicate>
	class cgh_unary_negate : public unary_function < typename predicate::argument_type, bool >
	{
	protected:
		predicate pred; // 内部成员
	public:
		explicit cgh_unary_negate(const predicate& x) : pred(x) {}
		bool operator()(const typename predicate::argument_type& x) const
		{
			return !pred(x); // 将 pred 的运算结果加上否定（negate）运算
		}
	};

	/* 以下函数返回一个匿名的 cgh_unary_negate 对象，这使得我们可以以函数调用的方式使用函数对象 */
	template<class predicate>
	inline cgh_unary_negate<predicate> cgh_not1(const predicate& pred)
	{
		return cgh_unary_negate<predicate>(pred);
	}

	#pragma endregion

	#pragma region cgh_binary_negate

	template<class predicate>
	class cgh_binary_negate : public binary_function<typename predicate::first_arguement_type,
													 typename predicate::second_argument_type,
													 bool>
	{
	protected:
		predicate pred;
	public:
		explicit cgh_binary_negate(const predicate& x) : pred(x) {}
		bool operator()(const typename predicate::first_arguement_type& x,
						const typename predicate::second_argument_type& y) const
		{
			return !pred(x, y); // 将 pred 的运算结果加上否定（negate）运算
		}
	};

	/* 以下函数返回一个匿名的 cgh_binary_negate 对象，这使得我们可以以函数调用的方式使用函数对象 */
	template<class predicate>
	inline cgh_binary_negate<predicate> cgh_not2(const predicate& pred)
	{
		return cgh_binary_negate<predicate>(pred);
	}

	#pragma endregion

	#pragma region cgh_binder1st

	/* 以下配接器可以将某个 Adaptable Binary function（二元函数）转换为 Unary Function（一元函数）*/
	/* 具体的做法是让一元函数绑定二元函数的第一个参数，忽略第二个参数 */
	template<class operation>
	class cgh_binder1st :public unary_function < typename operation::second_argument_type, 
												 typename operation::result_type >
	{
	protected:
		operation op; // 对参数的操作方式
		typename operation::first_argument_type	value; // 二元函数的第一个参数值
	public:
		cgh_binder1st(const operation& x, const typename operation::first_argument_type& y) :op(x), value(y) {}

		// operation::result_type：返回值类型
		typename operation::result_type operator()(const typename operation::second_argument_type& x) const
		{
			return op(value, x);
		}
	};

	/* 以下函数返回一个匿名的 cgh_binder1st 对象，这使得我们可以以函数调用的方式使用函数对象 */
	template<class operation, class T>
	inline cgh_binder1st<operation> cgh_bind1st(const operation& op, const T& x)
	{
		typedef typename operation::first_argument_type	arg1_type; // 定义二元函数的第一个参数类型为 arg1_type
		return cgh_binder1st<operation>(op, arg1_type(x)); // 让一元函数绑定二元函数的第一个参数
	}

	#pragma endregion

	#pragma region cgh_binder2nd

	/* 以下配接器可以将某个 Adaptable Binary function（二元函数）转换为 Unary Function（一元函数）*/
	/* 具体的做法是让一元函数绑定二元函数的第二个参数，忽略第一个参数 */
	template<class operation>
	class cgh_binder2nd :public unary_function < typename operation::first_argument_type,
												 typename operation::result_type >
	{
	protected:
		operation op; // 对参数的操作方式
		typename operation::second_argument_type	value; // 二元函数的第二个参数值
	public:
		cgh_binder2nd(const operation& x, const typename operation::second_argument_type& y) :op(x), value(y) {}

		// operation::result_type：返回值类型
		typename operation::result_type operator()(const typename operation::first_argument_type& x) const
		{
			return op(x, value);
		}
	};

	/* 以下函数返回一个匿名的 cgh_bind2nd 对象，这使得我们可以以函数调用的方式使用函数对象 */
	template<class operation, class T>
	inline cgh_binder2nd<operation> cgh_bind2nd(const operation& op, const T& x)
	{
		typedef typename operation::second_argument_type	arg2_type; // 定义二元函数的第二个参数类型为 arg2_type
		return cgh_binder2nd<operation>(op, arg2_type(x)); // 让一元函数绑定二元函数的第二个参数
	}

	#pragma endregion

	#pragma region cgh_compose1

	/* 
		已知两个 Adaptable Unary Functions f()、g()，cgh_unary_compose 配接器可以产生一个 h()
		使得 h() = f(g(x))
	*/
	template<class operation1, class operation2>
	class cgh_unary_compose : public unary_function < typename operation2::argument_type,
													  typename operation1::argument_type >
	{
	protected:
		operation1 op1;
		operation2 op2;
	public:
		cgh_unary_compose(const operation1& x, const operation2& y) : op1(x), op2(y) {}
		
		typename operation1::result_type operator()(const typename operation2::argument_type& x) const
		{
			return op1(op2(x)); // 两个操作的合成
		}
	};

	/* 以下函数返回一个匿名的 cgh_unary_compose 对象，这使得我们可以以函数调用的方式使用函数对象 */
	template<class operation1, class operation2>
	inline cgh_unary_compose<operation1, operation2> cgh_compose1(const operation1& op1, const operation2& op2)
	{
		return cgh_unary_compose<operation1, operation2>(op1, op2);
	}

	#pragma endregion

	#pragma region cgh_compose2

	/*
		已知两个 Adaptable Unary Functions f()、g()，cgh_unary_compose 配接器可以产生一个 h()
		使得 h() = f(g(x))
	*/
	template<class operation1, class operation2, class operation3>
	class cgh_binary_compose : public unary_function < typename operation2::argument_type,
														typename operation1::result_type >
	{
	protected:
		operation1 op1;
		operation2 op2;
		operation3 op3;
	public:
		cgh_binary_compose(const operation1& x, const operation2& y, const operation3& z) : op1(x), op2(y), op3(z) {}

		typename operation1::result_type operator()(const typename operation2::argument_type& x) const
		{
			return op1(op2(x), op3(x));
		}
	};

	/* 以下函数返回一个匿名的 cgh_binary_compose 对象，这使得我们可以以函数调用的方式使用函数对象 */
	template<class operation1, class operation2, class operation3>
	inline cgh_binary_compose<operation1, operation2, operation3> cgh_compose2(const operation1& op1, const operation2& op2, const operation3& op3)
	{
		return cgh_binary_compose<operation1, operation2, operation3>(op1, op2, op3);
	}

	#pragma endregion

	#pragma region	cgh_pointer_to_unary_function

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///	以下配接器可以使我们将一般函数当成函数对象来使用，一般函数当做函数对象传递给 STL 算法，
	///	就语言层面上是可以的，就像原生指针可以当做迭代器传递给 STL 算法，但是如果不使用以下给出的配接器做一层封装
	///	那么该函数就没有配给能力，不能其他配接器接轨使用
	///	以下配接器把一元函数指针封装起来
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class arg, class result>
	class cgh_pointer_to_unary_function : public unary_function < arg, result >
	{
	protected:
		result(*ptr)(arg); // 内部成员：函数指针
	public:
		cgh_pointer_to_unary_function(){}
		explicit cgh_pointer_to_unary_function(result(*x)(arg)) : ptr(x){}
		result operator()(arg x) const
		{
			return ptr(x); // 函数对象最终调用函数裸指针
		}
	};

	/* 以下函数返回一个匿名的 cgh_pointer_to_unary_function 对象，这使得我们可以以函数调用的方式使用函数对象 */
	template<class arg, class result>
	inline cgh_pointer_to_unary_function<arg, result> cgh_ptr_fun(result(*x)(arg))
	{
		return cgh_pointer_to_unary_function<arg, result>(x);
	}

	#pragma endregion

	#pragma region	cgh_pointer_to_binary_function

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///	以下配接器可以使我们将一般函数当成函数对象来使用，一般函数当做函数对象传递给 STL 算法，
	///	就语言层面上是可以的，就像原生指针可以当做迭代器传递给 STL 算法，但是如果不使用以下给出的配接器做一层封装
	///	那么该函数就没有配给能力，不能其他配接器接轨使用
	///	以下配接器把二元函数指针封装起来
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class arg1, class arg2, class result>
	class cgh_pointer_to_binary_function : public binary_function < arg1, arg2, result >
	{
	protected:
		result(*ptr)(arg1, arg2); // 内部成员：函数指针
	public:
		cgh_pointer_to_binary_function(){}
		explicit cgh_pointer_to_binary_function(result(*x)(arg1, arg2)) : ptr(x){}
		result operator()(arg1 x, arg2 y) const
		{
			return ptr(x, y); // 函数对象最终调用函数裸指针
		}
	};

	/* 以下函数返回一个匿名的 cgh_pointer_to_binary_function 对象，这使得我们可以以函数调用的方式使用函数对象 */
	template<class arg1, class arg2, class result>
	inline cgh_pointer_to_binary_function<arg1, arg2, result> cgh_ptr_fun(result (*x)(arg1, arg2))
	{
		return cgh_pointer_to_binary_function<arg1, arg2, result>(x);
	}

	#pragma endregion

}

#endif