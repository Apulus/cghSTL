/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件名称:_cghList的测试代码
******************************************************************/

#include "stdafx.h"
#include "cghAlloc.h"
#include "globalConstruct.h"
#include "_cghList.h"
using namespace::std;

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace::CGH;

	_cghList<int> list;
	int i = 0;
	list.push_back(1); // 在list尾部插入1
	list.push_back(2); // 在list尾部插入2
	list.push_back(2); // 在list尾部插入2
	list.push_back(2); // 在list尾部插入2
	list.push_front(3); // 在list头部插入1

	std::cout << "-----------------插入元素----------------" << endl;
	std::cout << "在list尾部依次插入1、2、2、2，在list头部插入3" << endl;
	// 取得list的长度
	std::cout << "list的长度：" << list.size() << endl;
	// 遍历list
	for (_cghList<int>::iterator iter = list.begin(); iter != list.end(); iter++)
	{
		std::cout << "第" << i << "个元素：" << *iter << endl;
		i++;
	}

	std::cout << endl << endl << "-----------------值保留一个值等于2的元素----------------" << endl;
	// 值保留一个值等于2的元素
	list.unique(2);
	// 取得list的长度
	std::cout << "list的长度：" << list.size() << endl;
	// 遍历list
	i = 0;
	for (_cghList<int>::iterator iter = list.begin(); iter != list.end(); iter++)
	{
		std::cout << "第" << i << "个元素：" << *iter << endl;
		i++;
	}

	std::cout << endl << endl << "-----------------删除值等于2的元素----------------" << endl;
	list.remove(2);// 删除值等于2的元素
	// 取得list的长度
	std::cout << "list的长度：" << list.size() << endl;
	// 遍历list
	i = 0;
	for (_cghList<int>::iterator iter = list.begin(); iter != list.end(); iter++)
	{
		std::cout << "第" << i << "个元素：" << *iter << endl;
		i++;
	}

	std::cout << endl << endl << "-----------------清空list----------------" << endl;
	list.clear(); // 清空
	// 取得list的长度
	std::cout << "list的长度：" << list.size() << endl;
	// 遍历list
	i = 0;
	for (_cghList<int>::iterator iter = list.begin(); iter != list.end(); iter++)
	{
		std::cout << "第" << i << "个元素：" << *iter << endl;
		i++;
	}

	system("pause");
	return 0;
}