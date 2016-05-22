/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件名称:cghHeap容器的测试代码
******************************************************************/

#include "stdafx.h"
#include "cghHeap.h"
using namespace::std;

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace::CGH;

	cghHeap<int> test1;
	std::cout << "************************ heap 生成测试************************" << endl << endl;
	std::cout << "依次压入元素：\t0，1，2，3，4，8，9，3，5，我们要把压入的元素排成一颗完全二叉树" << endl << endl;
	test1.push_back(0);
	test1.push_back(1);
	test1.push_back(2);
	test1.push_back(3);
	test1.push_back(4);
	test1.push_back(8);
	test1.push_back(9);
	test1.push_back(3);
	test1.push_back(5);
	test1.make_heap(test1.begin(), test1.end()); // 生成heap
	std::cout << "生成 heap：\t" ;
	for (cghHeap<int>::iterator it = test1.begin(); it != test1.end(); ++it)
	{
		std::cout << *it << "，";
	}
	std::cout << endl << endl;


	std::cout << "************************ heap 压入测试************************" << endl << endl;
	std::cout << "压入元素：\t\t7，压入后我们要对heap这颗完全二叉树重新排序" << endl << endl;
	test1.push_back(7);
	test1.push_heap(test1.begin(), test1.end()); // 重新排序
	std::cout << "压入 7 之后的 heap：\t";
	for (cghHeap<int>::iterator it = test1.begin(); it != test1.end(); ++it)
	{
		std::cout << *it << "，";
	}
	std::cout << endl << endl;

	std::cout << "************************ heap 弹出测试************************" << endl << endl;
	std::cout << "我们只能弹出 heap 这颗二叉树的根节点" << endl << endl;
	test1.pop_heap(test1.begin(), test1.end());
	std::cout << "弹出根节点 9 之后的 heap：\t";
	test1.pop_back();
	for (cghHeap<int>::iterator it = test1.begin(); it != test1.end(); ++it)
	{
		std::cout << *it << "，";
	}
	std::cout << endl << endl;

	system("pause");
	return 0;
}

