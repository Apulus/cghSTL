/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ�����:cghHeap�����Ĳ��Դ���
******************************************************************/

#include "stdafx.h"
#include "cghHeap.h"
using namespace::std;

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace::CGH;

	cghHeap<int> test1;
	std::cout << "************************ heap ���ɲ���************************" << endl << endl;
	std::cout << "����ѹ��Ԫ�أ�\t0��1��2��3��4��8��9��3��5������Ҫ��ѹ���Ԫ���ų�һ����ȫ������" << endl << endl;
	test1.push_back(0);
	test1.push_back(1);
	test1.push_back(2);
	test1.push_back(3);
	test1.push_back(4);
	test1.push_back(8);
	test1.push_back(9);
	test1.push_back(3);
	test1.push_back(5);
	test1.make_heap(test1.begin(), test1.end()); // ����heap
	std::cout << "���� heap��\t" ;
	for (cghHeap<int>::iterator it = test1.begin(); it != test1.end(); ++it)
	{
		std::cout << *it << "��";
	}
	std::cout << endl << endl;


	std::cout << "************************ heap ѹ�����************************" << endl << endl;
	std::cout << "ѹ��Ԫ�أ�\t\t7��ѹ�������Ҫ��heap�����ȫ��������������" << endl << endl;
	test1.push_back(7);
	test1.push_heap(test1.begin(), test1.end()); // ��������
	std::cout << "ѹ�� 7 ֮��� heap��\t";
	for (cghHeap<int>::iterator it = test1.begin(); it != test1.end(); ++it)
	{
		std::cout << *it << "��";
	}
	std::cout << endl << endl;

	std::cout << "************************ heap ��������************************" << endl << endl;
	std::cout << "����ֻ�ܵ��� heap ��Ŷ������ĸ��ڵ�" << endl << endl;
	test1.pop_heap(test1.begin(), test1.end());
	std::cout << "�������ڵ� 9 ֮��� heap��\t";
	test1.pop_back();
	for (cghHeap<int>::iterator it = test1.begin(); it != test1.end(); ++it)
	{
		std::cout << *it << "��";
	}
	std::cout << endl << endl;

	system("pause");
	return 0;
}

