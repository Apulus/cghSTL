/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ�����:stack�Ĳ��Դ���
******************************************************************/

#include "stdafx.h"
#include "cghQueue.h"

using namespace::std;

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace::CGH;

	cghQueue<int> test;
	std::cout << "************************ѹ�����************************" << endl << endl;
	std::cout << "queueֻ�ܴӺ�˵���" << endl << endl;
	std::cout << "ѹ��Ԫ�أ�";
	for (int i = 0; i < 4; ++i)
	{
		std::cout << i << ",";
		test.push(i);
	}
	std::cout << endl << endl << "ǰ��Ԫ�أ�";
	std::cout << test.front() << endl;
	std::cout << endl <<  "���Ԫ�أ�";
	std::cout << test.back() << endl << endl;
	std::cout << "ջ�ĳ��ȣ�" << test.size() << endl;
	std::cout << endl << endl;


	std::cout << "************************��������************************" << endl << endl;
	std::cout << "queueֻ�ܴ�ǰ�˵���" << endl;
	for (int i = 0; i < 4; ++i)
	{
		std::cout << endl << "ǰ��Ԫ�أ�";
		std::cout << test.front() << endl;
		std::cout << endl << "���Ԫ�أ�";
		std::cout << test.back() << endl << endl;
		std::cout << "ջ�ĳ��ȣ�" << test.size() << endl;
		std::cout << "-------------------" << endl;
		test.pop();
	}
	std::cout << endl << endl;

	system("pause");
	return 0;
}