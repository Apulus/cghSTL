/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ���ܣ����Ե����������
******************************************************************/

#include "stdafx.h"
#include <iostream>
#include "cghDeque.h"
#include "cgh_iterator_adapters.h"
#include "cghStl_algobase.h"

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace CGH;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// ���� cgh_back_inserter
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << std::endl << "************************ ���� cgh_back_inserter ***************************" << std::endl;
	cghDeque<int> deque1;
	deque1.push_back(1);
	deque1.push_back(2);
	deque1.push_back(3);
	deque1.push_back(4);
	deque1.push_back(5);
	cghDeque<int> deque2;
	deque2.push_back(6);
	deque2.push_back(7);
	deque2.push_back(8);
	deque2.push_back(9);
	deque2.push_back(10);
	std::cout << std::endl << "���� deque1 = { 1, 2, 3, 4, 5 }; \n     deque2 = { 6, 7, 8, 9, 10 };" << std::endl << std::endl;
	std::cout << "���ã�copy(test2.begin(), test2.end(), cgh_back_inserter(test1));\n\n�� deque2 ���뵽 deque1 �ĺ��棬��������" ;
	copy(deque2.begin(), deque2.end(), cgh_back_inserter(deque1));
	for (int i = 0; i < deque1.size(); ++i)
	{
		std::cout << deque1[i] << ", ";
	}
	std::cout << std::endl << std::endl;


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// ���� cgh_front_inserter
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << std::endl << "************************ ���� cgh_front_inserter ***************************" << std::endl;
	cghDeque<int> deque3;
	deque3.push_back(1);
	deque3.push_back(2);
	deque3.push_back(3);
	deque3.push_back(4);
	deque3.push_back(5);
	cghDeque<int> deque4;
	deque4.push_back(6);
	deque4.push_back(7);
	deque4.push_back(8);
	deque4.push_back(9);
	deque4.push_back(10);
	std::cout << std::endl << "���� deque3 = { 1, 2, 3, 4, 5 }; \n     deque4 = { 6, 7, 8, 9, 10 };" << std::endl << std::endl;
	std::cout << "���ã�copy(deque4.begin(), deque4.end(), cgh_front_inserter(deque3));\n\n�� deque4 ���뵽 deque3 ��ǰ�棬��������" ;
	copy(deque4.begin(), deque4.end(), cgh_front_inserter(deque3));
	for (int i = 0; i < deque3.size(); ++i)
	{
		std::cout << deque3[i] << ", ";
	}
	std::cout << std::endl << std::endl;


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// ���� cgh_inserter
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << std::endl << "************************ ���� cgh_inserter ***************************" << std::endl;
	cghDeque<int> deque5;
	deque5.push_back(1);
	deque5.push_back(2);
	deque5.push_back(3);
	deque5.push_back(4);
	deque5.push_back(5);
	cghDeque<int> deque6;
	deque6.push_back(6);
	deque6.push_back(7);
	deque6.push_back(8);
	deque6.push_back(9);
	deque6.push_back(10);
	std::cout << std::endl << "���� deque5 = { 1, 2, 3, 4, 5 }; \n     deque6 = { 6, 7, 8, 9, 10 };" << std::endl << std::endl;
	std::cout << "���ã�\n   copy(deque6.begin(), deque6.end(), cgh_inserter(deque5, deque5.begin() + 3));\n�� deque6 ���뵽 1, 2, 3,_����_, 4, 5����������" ;
	copy(deque6.begin(), deque6.end(), cgh_inserter(deque5, deque5.begin() + 3));
	for (int i = 0; i < deque5.size(); ++i)
	{
		std::cout << deque5[i] << ", ";
	}
	std::cout << std::endl << std::endl;


	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// ���� cgh_reverse_iterator
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << std::endl << "************************ ���� cgh_reverse_iterator ***************************" << std::endl;
	cghDeque<int> deque7;
	deque7.push_back(1);
	deque7.push_back(2);
	deque7.push_back(3);
	deque7.push_back(4);
	deque7.push_back(5);
	std::cout << std::endl << "���� deque7 = { 1, 2, 3, 4, 5 };" << std::endl << std::endl;
	std::cout << "���Է������ deque7 ��" ;
	cghDeque<int>::reverse_iterator reverse_iter(deque7.rbegin());
	for (int i = 0; i < 5; ++i, ++reverse_iter)
	{
		std::cout << *reverse_iter << ", ";
	}
	std::cout << std::endl << std::endl;

	system("pause");
	return 0 ;
}