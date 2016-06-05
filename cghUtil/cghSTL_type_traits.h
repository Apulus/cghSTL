/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  内容:cghSTL的特性萃取机
******************************************************************/

#ifndef CGH_STL_TYPE_TRAITS_  
#define CGH_STL_TYPE_TRAITS_  

/*
	特性萃取机的定义使用了“模板显示专用化”技术
	关于“模板显示专用化”，参见 MSDN：https://msdn.microsoft.com/zh-cn/library/c401y1kb.aspx
	
	关于 non-trivial 和 trivial
	参见：http://stackoverflow.com/questions/3899223/what-is-a-non-trivial-constructor-in-c
	      http://blog.csdn.net/a627088424/article/details/48595525
*/
namespace CGH{
	struct true_type { };

	struct false_type { };

	template <class type>
	struct cghSTL_type_traits
	{ 
		typedef true_type     this_dummy_member_must_be_first;

		typedef false_type    has_trivial_default_constructor;
		typedef false_type    has_trivial_copy_constructor;
		typedef false_type    has_trivial_assignment_operator;
		typedef false_type    has_trivial_destructor;
		typedef false_type    is_POD_type;
	};

	template <> struct cghSTL_type_traits<char>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template <> struct cghSTL_type_traits<signed char>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template <> struct cghSTL_type_traits<unsigned char>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template <> struct cghSTL_type_traits<short>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template <> struct cghSTL_type_traits<unsigned short>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template <> struct cghSTL_type_traits<int>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template <> struct cghSTL_type_traits<unsigned int>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template <> struct cghSTL_type_traits<long>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template <> struct cghSTL_type_traits<unsigned long>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template <> struct cghSTL_type_traits<float>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template <>struct cghSTL_type_traits<double>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template <>struct cghSTL_type_traits<long double>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	// 针对指针提供特化  
	template <class T>
	struct cghSTL_type_traits<T*>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template <>
	struct cghSTL_type_traits<char*>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template <>
	struct cghSTL_type_traits<signed char*>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

	template <>
	struct cghSTL_type_traits<unsigned char*>
	{
		typedef true_type    has_trivial_default_constructor;
		typedef true_type    has_trivial_copy_constructor;
		typedef true_type    has_trivial_assignment_operator;
		typedef true_type    has_trivial_destructor;
		typedef true_type    is_POD_type;
	};

}
#endif 