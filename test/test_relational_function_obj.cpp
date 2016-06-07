/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件内容：测试关系运算类（Relational）函数对象（仿函数）
******************************************************************/

#include "stdafx.h"
//#include <iostream>
//#include "cgh_function_obj.h"
//
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	using namespace::CGH;
//
//	equal_to<int> equal_to_obj;
//	not_equal_to<int>not_equal_to_obj;
//	greater<int> greater_obj;
//	greater_equal<int> greater_equal_obj;
//	less<int> less_obj;
//	less_equal<int> less_equal_obj;
//
//	std::cout << "************************ 测试函数对象1 ***************************" << std::endl << std::endl;
//
//	std::cout << "equal_to_obj(3, 5) = " << equal_to_obj(3, 5) << std::endl << std::endl;
//	std::cout << "not_equal_to_obj(3, 5) = " << not_equal_to_obj(3, 5) << std::endl << std::endl;
//	std::cout << "greater_obj(3, 5) = " << greater_obj(3, 5) << std::endl << std::endl;
//	std::cout << "greater_equal_obj(3, 5) = " << greater_equal_obj(3, 5) << std::endl << std::endl;
//	std::cout << "less_obj(3, 5) = " << less_obj(3, 5) << std::endl << std::endl;
//	std::cout << "less_equal_obj(3, 5) = " << less_equal_obj(3, 5) << std::endl << std::endl;
//
//	std::cout << "************************* 测试函数对象2 **************************" << std::endl << std::endl;
//
//	std::cout << "equal_to<int>()(3, 5) = " << equal_to<int>()(3, 5) << std::endl << std::endl;
//	std::cout << "not_equal_to<int>()(3, 5) = " << not_equal_to<int>()(3, 5) << std::endl << std::endl;
//	std::cout << "greater<int>()(3, 5) = " << greater<int>()(3, 5) << std::endl << std::endl;
//	std::cout << "greater_equal<int>()(3, 5) = " << greater_equal<int>()(3, 5) << std::endl << std::endl;
//	std::cout << "less<int>()(3, 5) = " << less<int>()(3, 5) << std::endl << std::endl;
//	std::cout << "less_equal<int>()(3, 5) = " << less_equal<int>()(3, 5) << std::endl << std::endl;
//
//	system("pause");
//	return 0;
//}