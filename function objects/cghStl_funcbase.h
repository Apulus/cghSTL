/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件内容：算术类（Arthmetic）仿函数的实现
******************************************************************/

#ifndef _CGH_STL_FUNC_BASE_H_
#define _CGH_STL_FUNC_BASE_H_

namespace CGH{

	/*
		unary_function 用来呈现一元函数的参数类型和返回值类型
		STL 规定，每一个 adaptable unary function 都应该继承 unary_function
	*/
	template<class arg, class result>
	struct unary_function
	{
		typedef arg		argument_type;
		typedef result	result_type;
	};

	/*
		binary_function 用来呈现二元函数的第一个参数类型、第二个参数类型、返回值类型
		STL 规定，每一个 adaptable binary function 都应该继承 binary_function
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