/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件内容:cghSet的测试
******************************************************************/

#include "stdafx.h"
//#include "cghSet.h"
//using namespace::std;
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	using namespace::CGH;
//
//	cghSet<int> test;
//	test.insert(3);
//	test.insert(2);
//	test.insert(5);
//	test.insert(4);
//	test.insert(1);
//	std::cout << endl << "乱序插入：3，2，5，4，1" << endl << endl;
//	std::cout << "经set容器排序后的结果：" << endl << endl;
//	for (cghSet<int>::iterator iter = test.begin(); iter != test.end(); ++iter)
//	{
//		std::cout << *iter << ", ";
//	}
//
//	std::cout << endl << endl << "----------------------";
//	std::cout << endl << endl << "使用find函数在set中找值为3的元素" << endl << endl;
//	cghSet<int>::iterator iter = test.find(3);
//	if (iter != test.end())
//	{
//		std::cout << "iter != test.end()，找到了，*iter = " << *iter;
//	}
//
//	std::cout << endl << endl << "----------------------";
//	std::cout << endl << endl << "使用find函数在set中找值为6的元素" << endl << endl;
//	cghSet<int>::iterator iter2 = test.find(6);
//	if (iter2 == test.end())
//	{
//		std::cout << "iter2 == test.end()，没有找到";
//	}
//
//	std::cout << endl << endl << "----------------------";
//	std::cout << endl << endl << "set的大小：" << test.size() << endl << endl;
//
//	system("pause");
//	return 0;
//}