/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ����ݣ�cghStl_numeric.h �е���ֵ�㷨�Ĳ���
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
//	std::cout << "����һ��vector������ puah_back 1��2��3��4��5" << endl << endl;
//	cghVector<int> test;
//	test.push_back(1);
//	test.push_back(2);
//	test.push_back(3);
//	test.push_back(4);
//	test.push_back(5);
//	ostream_iterator<int> oite(cout, " "); // ostream_iterator<int>��һ������������ostream_iterator<int>�󶨵�cout����Ϊ���ʹ��
//
//	std::cout << "******************���� accumulate �㷨************************" << endl << endl;
//	cout << "ȱʡ����plus�ۼӣ�1 + 2 + 3 + 4 + 5 = ";
//	cout << accumulate(test.begin(), test.end(), 0) << endl << endl;
//	cout << "�û�ָ�� minus ������-1 - 2 - 3 - 4 - 5 = ";
//	cout << accumulate(test.begin(), test.end(), 0, minus<int>()) << endl << endl;
//
//	std::cout << "******************���� ajacent_difference �㷨************************" << endl << endl;
//	cout << "Ĭ������£����� 1��2��3��4��5 ����֮��Ĳ�ֵ��";
//	ajacent_difference(test.begin(), test.end(), oite);
//	cout << endl << endl;
//	cout << "�û�ָ�� plus ���������� 1��2��3��4��5 ����֮��Ĳ�ֵ���ټ� 1��";
//	ajacent_difference(test.begin(), test.end(), oite, plus<int>());
//	cout << endl << endl;
//
//	std::cout << "******************���� inner_product �㷨************************" << endl << endl;
//	cout << "1��1 + 2��2 + 3��3 + 4��4 +��5��5 = ";
//	cout << inner_product(test.begin(), test.end(), test.begin(), 0);
//	cout << endl << endl;
//	cout << "-( 1+1 ) -  ( 2+2 ) - ( 3+3 ) - ( 4+4 ) -��( 5+5 ) = ";
//	cout << inner_product(test.begin(), test.end(), test.begin(), 0, minus<int>(), plus<int>());
//	cout << endl << endl;
//
//	std::cout << "******************���� partial_sum �㷨************************" << endl << endl;
//	cout << "Ĭ������£����� �� n ����Ԫ����ǰ n ����Ԫ�ص�����ܼƣ�";
//	partial_sum(test.begin(), test.end(), oite);
//	cout << endl << endl;
//	cout << "�û�ָ�� minus ������";
//	partial_sum(test.begin(), test.end(), oite, minus<int>());
//	cout << endl << endl;
//
//	std::cout << "******************���� power �㷨************************" << endl << endl;
//	cout << "Ĭ������£����� 10 �� 3 �η���";
//	cout << power(10, 3) << endl ;
//	cout << endl;
//	cout << "�û�ָ�� plus ���������� 10 + 10 + 10��";
//	cout << power(10, 3, plus<int>()) << endl ;
//	cout << endl;
//
//	system("pause");
//	return 0;
//}