/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件名称:stack的测试代码
******************************************************************/

#include "stdafx.h"
#include "deque_stack.h"

using namespace::std;

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace::CGH;

	cghStack<int> test;
	std::cout << "************************压栈测试************************" << endl << endl;
	std::cout << "压入元素：";
	for (int i = 0; i < 4; ++i)
	{
		std::cout << i << ",";
		test.push(i);
	}
	std::cout << endl << endl << "栈顶元素：";
	std::cout << test.top() << endl << endl;
	std::cout << "栈的长度：" << test.size() << endl;
	std::cout << endl << endl;


	std::cout << "************************弹栈栈测试************************" << endl << endl;
	std::cout << "依次弹出：" << endl << endl;
	for (int i = 0; i < 4; ++i)
	{
		std::cout << "\t" << test.top() << endl << endl;
		test.pop();
	}
	std::cout << "栈的长度：" << test.size() << endl;
	std::cout << endl << endl;
	std::cout << "************************测试结束************************" << endl;

	system("pause");
	return 0;
}