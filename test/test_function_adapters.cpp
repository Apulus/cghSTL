/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ���ܣ����Ժ��������
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
	/// ���� cgh_not1 �� cgh_bind2nd
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "************************* ���� cgh_not1 �� cgh_bind2nd *************************" << std::endl;
	std::cout << "���� vec1[6] = { 2, 21, 12, 7, 19, 23 }; " << std::endl;
	std::cout << std::endl << "���� count_if(vec1.begin(), vec1.end(), cgh_not1(cgh_bind2nd(less<int>(), 12)))" << std::endl;
	std::cout << std::endl << "�ҳ���С�� 12 ��Ԫ�ظ�����";
	cghVector<int> vec1;
	vec1.push_back(2);
	vec1.push_back(21);
	vec1.push_back(12);
	vec1.push_back(7);
	vec1.push_back(19);
	vec1.push_back(23);
	std::cout << count_if(vec1.begin(), vec1.end(), cgh_not1(cgh_bind2nd(less<int>(), 12))) << std::endl << std::endl << std::endl;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// ���� cgh_compose1 �� cgh_bind2nd
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "************************* ���� cgh_compose1 �� cgh_bind2nd *********************" << std::endl;
	std::cout << "���� vec1[6] = { 2, 21, 12, 7, 19, 23 }; " << std::endl;
	std::cout << std::endl << "��ÿһ��Ԫ�� v ִ�� ( v + 2 ) * 3����������";
	std::ostream_iterator<int> outit(std::cout, " ");
	CGH::transform(vec1.begin(), vec1.end(), outit, cgh_compose1(cgh_bind2nd(multiplies<int>(), 3), cgh_bind2nd(plus<int>(), 2)));
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	/// ���� cgh_ptr_fun
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	std::cout << "************************* ���� cgh_ptr_fun *************************************" << std::endl;
	std::cout << "���� vec1[6] = { 2, 21, 12, 7, 19, 23 }; " << std::endl;
	std::cout << std::endl << "�� cgh_ptr_fun ��װ print��������ָ�룩" << std::endl;
	std::cout << std::endl << "���� for_each(vec1.begin(), vec1.end(), cgh_ptr_fun(print));" << std::endl;
	std::cout << std::endl << "���δ�ӡ vec1��";
	for_each(vec1.begin(), vec1.end(), cgh_ptr_fun(print));

	std::cout << std::endl;
	std::cout << std::endl;
	system("pause");
	return 0 ;
}