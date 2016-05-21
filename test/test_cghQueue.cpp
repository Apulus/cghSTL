/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件名称:stack的测试代码
******************************************************************/

#include "stdafx.h"
#include "cghQueue.h"

using namespace::std;

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace::CGH;

	cghQueue<int> test;
	std::cout << "************************压入测试************************" << endl << endl;
	std::cout << "queue只能从后端弹出" << endl << endl;
	std::cout << "压入元素：";
	for (int i = 0; i < 4; ++i)
	{
		std::cout << i << ",";
		test.push(i);
	}
	std::cout << endl << endl << "前端元素：";
	std::cout << test.front() << endl;
	std::cout << endl <<  "后端元素：";
	std::cout << test.back() << endl << endl;
	std::cout << "栈的长度：" << test.size() << endl;
	std::cout << endl << endl;


	std::cout << "************************弹出测试************************" << endl << endl;
	std::cout << "queue只能从前端弹出" << endl;
	for (int i = 0; i < 4; ++i)
	{
		std::cout << endl << "前端元素：";
		std::cout << test.front() << endl;
		std::cout << endl << "后端元素：";
		std::cout << test.back() << endl << endl;
		std::cout << "栈的长度：" << test.size() << endl;
		std::cout << "-------------------" << endl;
		test.pop();
	}
	std::cout << endl << endl;

	system("pause");
	return 0;
}