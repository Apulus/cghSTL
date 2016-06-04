/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件内容：cghStl_numeric.h 中的数值算法的测试
******************************************************************/

#include "stdafx.h"
//#include "cghVector.h"
//#include "cghStl_numeric.h"
//#include <iterator>
//
//using namespace::std;
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	using namespace::CGH;
//
//	std::cout << "创建一个vector，依次 puah_back 1、2、3、4、5" << endl << endl;
//	cghVector<int> test;
//	test.push_back(1);
//	test.push_back(2);
//	test.push_back(3);
//	test.push_back(4);
//	test.push_back(5);
//	ostream_iterator<int> oite(cout, " "); // ostream_iterator<int>是一个迭代器，把ostream_iterator<int>绑定到cout，作为输出使用
//
//	std::cout << "******************测试 accumulate 算法************************" << endl << endl;
//	cout << "缺省采用plus累加：1 + 2 + 3 + 4 + 5 = ";
//	cout << accumulate(test.begin(), test.end(), 0) << endl << endl;
//	cout << "用户指定 minus 函数：-1 - 2 - 3 - 4 - 5 = ";
//	cout << accumulate(test.begin(), test.end(), 0, minus<int>()) << endl << endl;
//
//	std::cout << "******************测试 ajacent_difference 算法************************" << endl << endl;
//	cout << "默认情况下，计算 1、2、3、4、5 两两之间的差值：";
//	ajacent_difference(test.begin(), test.end(), oite);
//	cout << endl << endl;
//	cout << "用户指定 plus 函数，计算 1、2、3、4、5 两两之间的差值，再加 1：";
//	ajacent_difference(test.begin(), test.end(), oite, plus<int>());
//	cout << endl << endl;
//
//	std::cout << "******************测试 inner_product 算法************************" << endl << endl;
//	cout << "1×1 + 2×2 + 3×3 + 4×4 +　5×5 = ";
//	cout << inner_product(test.begin(), test.end(), test.begin(), 0);
//	cout << endl << endl;
//	cout << "-( 1+1 ) -  ( 2+2 ) - ( 3+3 ) - ( 4+4 ) -　( 5+5 ) = ";
//	cout << inner_product(test.begin(), test.end(), test.begin(), 0, minus<int>(), plus<int>());
//	cout << endl << endl;
//
//	std::cout << "******************测试 partial_sum 算法************************" << endl << endl;
//	cout << "默认情况下，计算 第 n 个新元素是前 n 个旧元素的相加总计：";
//	partial_sum(test.begin(), test.end(), oite);
//	cout << endl << endl;
//	cout << "用户指定 minus 函数：";
//	partial_sum(test.begin(), test.end(), oite, minus<int>());
//	cout << endl << endl;
//
//	std::cout << "******************测试 power 算法************************" << endl << endl;
//	cout << "默认情况下，计算 10 的 3 次方：";
//	cout << power(10, 3) << endl ;
//	cout << endl;
//	cout << "用户指定 plus 函数，计算 10 + 10 + 10：";
//	cout << power(10, 3, plus<int>()) << endl ;
//	cout << endl;
//
//	system("pause");
//	return 0;
//}