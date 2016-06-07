/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ����ݣ������ࣨArthmetic���º�����ʵ��
******************************************************************/

#ifndef _CGH_STL_FUNC_BASE_H_
#define _CGH_STL_FUNC_BASE_H_

namespace CGH{

	/*
		unary_function ��������һԪ�����Ĳ������ͺͷ���ֵ����
		STL �涨��ÿһ�� adaptable unary function ��Ӧ�ü̳� unary_function
	*/
	template<class arg, class result>
	struct unary_function
	{
		typedef arg		argument_type;
		typedef result	result_type;
	};

	/*
		binary_function �������ֶ�Ԫ�����ĵ�һ���������͡��ڶ����������͡�����ֵ����
		STL �涨��ÿһ�� adaptable binary function ��Ӧ�ü̳� binary_function
	*/
	template<class arg1, class arg2, class result>
	struct binary_function
	{
		typedef arg1		first_argument_type;
		typedef arg2		second_argument_type;
		typedef result		result_type;
	};

}

#endif