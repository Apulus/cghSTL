/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  功能：测试函数配接器
******************************************************************/

#include "stdafx.h"
#include <iostream>
#include <iterator>
#include "cghStl_algo.h"
#include "cgh_function_obj.h"
#include "cgh_function_adapters.h"
#include "cghVector.h"

void print(int i)
{
	std::cout << i << " " ;
}

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace CGH;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// 测试 cgh_not1 和 cgh_bind2nd
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "************************* 测试 cgh_not1 和 cgh_bind2nd *************************" << std::endl;
	std::cout << "现有 vec1[6] = { 2, 21, 12, 7, 19, 23 }; " << std::endl;
	std::cout << std::endl << "调用 count_if(vec1.begin(), vec1.end(), cgh_not1(cgh_bind2nd(less<int>(), 12)))" << std::endl;
	std::cout << std::endl << "找出不小于 12 的元素个数：";
	cghVector<int> vec1;
	vec1.push_back(2);
	vec1.push_back(21);
	vec1.push_back(12);
	vec1.push_back(7);
	vec1.push_back(19);
	vec1.push_back(23);
	std::cout << count_if(vec1.begin(), vec1.end(), cgh_not1(cgh_bind2nd(less<int>(), 12))) << std::endl << std::endl << std::endl;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// 测试 cgh_compose1 和 cgh_bind2nd
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "************************* 测试 cgh_compose1 和 cgh_bind2nd *********************" << std::endl;
	std::cout << "现有 vec1[6] = { 2, 21, 12, 7, 19, 23 }; " << std::endl;
	std::cout << std::endl << "对每一个元素 v 执行 ( v + 2 ) * 3，输出结果：";
	std::ostream_iterator<int> outit(std::cout, " ");
	CGH::transform(vec1.begin(), vec1.end(), outit, cgh_compose1(cgh_bind2nd(multiplies<int>(), 3), cgh_bind2nd(plus<int>(), 2)));
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// 测试 cgh_ptr_fun
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "************************* 测试 cgh_ptr_fun *************************************" << std::endl;
	std::cout << "现有 vec1[6] = { 2, 21, 12, 7, 19, 23 }; " << std::endl;
	std::cout << std::endl << "用 cgh_ptr_fun 封装 print（函数裸指针）" << std::endl;
	std::cout << std::endl << "调用 for_each(vec1.begin(), vec1.end(), cgh_ptr_fun(print));" << std::endl;
	std::cout << std::endl << "依次打印 vec1：";
	for_each(vec1.begin(), vec1.end(), cgh_ptr_fun(print));

	std::cout << std::endl;
	std::cout << std::endl;
	system("pause");
	return 0 ;
}