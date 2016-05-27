/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ�����:������Ĳ���
******************************************************************/

#include "stdafx.h"
#include "rb_tree.h"
using namespace::std;

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace::CGH;

	cgh_rb_tree<int, int, identity<int>, less<int>> test;

	test.insert_unique(10);
	test.insert_unique(7);
	test.insert_unique(8);
	test.insert_unique(15);
	test.insert_unique(5);
	test.insert_unique(6);
	test.insert_unique(11);
	test.insert_unique(13);
	test.insert_unique(12);

	cgh_rb_tree<int, int, identity<int>, less<int>>::iterator it = test.begin();
	int i = 1;
	for (; it != test.end(); it++)
	{
		string color = it.color() == true ? "��" : "��";
		std::cout << *it << " ( " << color.c_str() << " )" << endl << endl;
	}
	std::cout << "���ĸ��ڵ㣺" << test.root_value()<< endl << endl;
	std::cout << "���Ĵ�С��" << test.size() << endl << endl;

	system("pause");
	return 0;
}