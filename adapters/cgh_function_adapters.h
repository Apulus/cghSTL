/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ���ܣ������������ʵ��
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
		predicate pred; // �ڲ���Ա
	public:
		explicit cgh_unary_negate(const predicate& x) : pred(x) {}
		bool operator()(const typename predicate::argument_type& x) const
		{
			return !pred(x); // �� pred �����������Ϸ񶨣�negate������
		}
	};

	/* ���º�������һ�������� cgh_unary_negate ������ʹ�����ǿ����Ժ������õķ�ʽʹ�ú������� */
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
			return !pred(x, y); // �� pred �����������Ϸ񶨣�negate������
		}
	};

	/* ���º�������һ�������� cgh_binary_negate ������ʹ�����ǿ����Ժ������õķ�ʽʹ�ú������� */
	template<class predicate>
	inline cgh_binary_negate<predicate> cgh_not2(const predicate& pred)
	{
		return cgh_binary_negate<predicate>(pred);
	}

	#pragma endregion

	#pragma region cgh_binder1st

	/* ������������Խ�ĳ�� Adaptable Binary function����Ԫ������ת��Ϊ Unary Function��һԪ������*/
	/* �������������һԪ�����󶨶�Ԫ�����ĵ�һ�����������Եڶ������� */
	template<class operation>
	class cgh_binder1st :public unary_function < typename operation::second_argument_type, 
												 typename operation::result_type >
	{
	protected:
		operation op; // �Բ����Ĳ�����ʽ
		typename operation::first_argument_type	value; // ��Ԫ�����ĵ�һ������ֵ
	public:
		cgh_binder1st(const operation& x, const typename operation::first_argument_type& y) :op(x), value(y) {}

		// operation::result_type������ֵ����
		typename operation::result_type operator()(const typename operation::second_argument_type& x) const
		{
			return op(value, x);
		}
	};

	/* ���º�������һ�������� cgh_binder1st ������ʹ�����ǿ����Ժ������õķ�ʽʹ�ú������� */
	template<class operation, class T>
	inline cgh_binder1st<operation> cgh_bind1st(const operation& op, const T& x)
	{
		typedef typename operation::first_argument_type	arg1_type; // �����Ԫ�����ĵ�һ����������Ϊ arg1_type
		return cgh_binder1st<operation>(op, arg1_type(x)); // ��һԪ�����󶨶�Ԫ�����ĵ�һ������
	}

	#pragma endregion

	#pragma region cgh_binder2nd

	/* ������������Խ�ĳ�� Adaptable Binary function����Ԫ������ת��Ϊ Unary Function��һԪ������*/
	/* �������������һԪ�����󶨶�Ԫ�����ĵڶ������������Ե�һ������ */
	template<class operation>
	class cgh_binder2nd :public unary_function < typename operation::first_argument_type,
												 typename operation::result_type >
	{
	protected:
		operation op; // �Բ����Ĳ�����ʽ
		typename operation::second_argument_type	value; // ��Ԫ�����ĵڶ�������ֵ
	public:
		cgh_binder2nd(const operation& x, const typename operation::second_argument_type& y) :op(x), value(y) {}

		// operation::result_type������ֵ����
		typename operation::result_type operator()(const typename operation::first_argument_type& x) const
		{
			return op(x, value);
		}
	};

	/* ���º�������һ�������� cgh_bind2nd ������ʹ�����ǿ����Ժ������õķ�ʽʹ�ú������� */
	template<class operation, class T>
	inline cgh_binder2nd<operation> cgh_bind2nd(const operation& op, const T& x)
	{
		typedef typename operation::second_argument_type	arg2_type; // �����Ԫ�����ĵڶ�����������Ϊ arg2_type
		return cgh_binder2nd<operation>(op, arg2_type(x)); // ��һԪ�����󶨶�Ԫ�����ĵڶ�������
	}

	#pragma endregion

	#pragma region cgh_compose1

	/* 
		��֪���� Adaptable Unary Functions f()��g()��cgh_unary_compose ��������Բ���һ�� h()
		ʹ�� h() = f(g(x))
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
			return op1(op2(x)); // ���������ĺϳ�
		}
	};

	/* ���º�������һ�������� cgh_unary_compose ������ʹ�����ǿ����Ժ������õķ�ʽʹ�ú������� */
	template<class operation1, class operation2>
	inline cgh_unary_compose<operation1, operation2> cgh_compose1(const operation1& op1, const operation2& op2)
	{
		return cgh_unary_compose<operation1, operation2>(op1, op2);
	}

	#pragma endregion

	#pragma region cgh_compose2

	/*
		��֪���� Adaptable Unary Functions f()��g()��cgh_unary_compose ��������Բ���һ�� h()
		ʹ�� h() = f(g(x))
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

	/* ���º�������һ�������� cgh_binary_compose ������ʹ�����ǿ����Ժ������õķ�ʽʹ�ú������� */
	template<class operation1, class operation2, class operation3>
	inline cgh_binary_compose<operation1, operation2, operation3> cgh_compose2(const operation1& op1, const operation2& op2, const operation3& op3)
	{
		return cgh_binary_compose<operation1, operation2, operation3>(op1, op2, op3);
	}

	#pragma endregion

	#pragma region	cgh_pointer_to_unary_function

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///	�������������ʹ���ǽ�һ�㺯�����ɺ���������ʹ�ã�һ�㺯�������������󴫵ݸ� STL �㷨��
	///	�����Բ������ǿ��Եģ�����ԭ��ָ����Ե������������ݸ� STL �㷨�����������ʹ�����¸������������һ���װ
	///	��ô�ú�����û�������������������������ӹ�ʹ��
	///	�����������һԪ����ָ���װ����
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class arg, class result>
	class cgh_pointer_to_unary_function : public unary_function < arg, result >
	{
	protected:
		result(*ptr)(arg); // �ڲ���Ա������ָ��
	public:
		cgh_pointer_to_unary_function(){}
		explicit cgh_pointer_to_unary_function(result(*x)(arg)) : ptr(x){}
		result operator()(arg x) const
		{
			return ptr(x); // �����������յ��ú�����ָ��
		}
	};

	/* ���º�������һ�������� cgh_pointer_to_unary_function ������ʹ�����ǿ����Ժ������õķ�ʽʹ�ú������� */
	template<class arg, class result>
	inline cgh_pointer_to_unary_function<arg, result> cgh_ptr_fun(result(*x)(arg))
	{
		return cgh_pointer_to_unary_function<arg, result>(x);
	}

	#pragma endregion

	#pragma region	cgh_pointer_to_binary_function

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///	�������������ʹ���ǽ�һ�㺯�����ɺ���������ʹ�ã�һ�㺯�������������󴫵ݸ� STL �㷨��
	///	�����Բ������ǿ��Եģ�����ԭ��ָ����Ե������������ݸ� STL �㷨�����������ʹ�����¸������������һ���װ
	///	��ô�ú�����û�������������������������ӹ�ʹ��
	///	����������Ѷ�Ԫ����ָ���װ����
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<class arg1, class arg2, class result>
	class cgh_pointer_to_binary_function : public binary_function < arg1, arg2, result >
	{
	protected:
		result(*ptr)(arg1, arg2); // �ڲ���Ա������ָ��
	public:
		cgh_pointer_to_binary_function(){}
		explicit cgh_pointer_to_binary_function(result(*x)(arg1, arg2)) : ptr(x){}
		result operator()(arg1 x, arg2 y) const
		{
			return ptr(x, y); // �����������յ��ú�����ָ��
		}
	};

	/* ���º�������һ�������� cgh_pointer_to_binary_function ������ʹ�����ǿ����Ժ������õķ�ʽʹ�ú������� */
	template<class arg1, class arg2, class result>
	inline cgh_pointer_to_binary_function<arg1, arg2, result> cgh_ptr_fun(result (*x)(arg1, arg2))
	{
		return cgh_pointer_to_binary_function<arg1, arg2, result>(x);
	}

	#pragma endregion

}

#endif