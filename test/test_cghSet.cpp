/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ�����:cghSet�Ĳ���
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
//	std::cout << endl << "������룺3��2��5��4��1" << endl << endl;
//	std::cout << "��set���������Ľ����" << endl << endl;
//	for (cghSet<int>::iterator iter = test.begin(); iter != test.end(); ++iter)
//	{
//		std::cout << *iter << ", ";
//	}
//
//	std::cout << endl << endl << "----------------------";
//	std::cout << endl << endl << "ʹ��find������set����ֵΪ3��Ԫ��" << endl << endl;
//	cghSet<int>::iterator iter = test.find(3);
//	if (iter != test.end())
//	{
//		std::cout << "iter != test.end()���ҵ��ˣ�*iter = " << *iter;
//	}
//
//	std::cout << endl << endl << "----------------------";
//	std::cout << endl << endl << "ʹ��find������set����ֵΪ6��Ԫ��" << endl << endl;
//	cghSet<int>::iterator iter2 = test.find(6);
//	if (iter2 == test.end())
//	{
//		std::cout << "iter2 == test.end()��û���ҵ�";
//	}
//
//	std::cout << endl << endl << "----------------------";
//	std::cout << endl << endl << "set�Ĵ�С��" << test.size() << endl << endl;
//
//	system("pause");
//	return 0;
//}