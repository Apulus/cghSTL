/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ�����:stack�Ĳ��Դ���
******************************************************************/

#include "stdafx.h"
#include "deque_stack.h"

using namespace::std;

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace::CGH;

	cghStack<int> test;
	std::cout << "************************ѹջ����************************" << endl << endl;
	std::cout << "ѹ��Ԫ�أ�";
	for (int i = 0; i < 4; ++i)
	{
		std::cout << i << ",";
		test.push(i);
	}
	std::cout << endl << endl << "ջ��Ԫ�أ�";
	std::cout << test.top() << endl << endl;
	std::cout << "ջ�ĳ��ȣ�" << test.size() << endl;
	std::cout << endl << endl;


	std::cout << "************************��ջջ����************************" << endl << endl;
	std::cout << "���ε�����" << endl << endl;
	for (int i = 0; i < 4; ++i)
	{
		std::cout << "\t" << test.top() << endl << endl;
		test.pop();
	}
	std::cout << "ջ�ĳ��ȣ�" << test.size() << endl;
	std::cout << endl << endl;
	std::cout << "************************���Խ���************************" << endl;

	system("pause");
	return 0;
}