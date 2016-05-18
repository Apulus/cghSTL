/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ�����:_cghList�Ĳ��Դ���
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
	list.push_back(1); // ��listβ������1
	list.push_back(2); // ��listβ������2
	list.push_back(2); // ��listβ������2
	list.push_back(2); // ��listβ������2
	list.push_front(3); // ��listͷ������1

	std::cout << "-----------------����Ԫ��----------------" << endl;
	std::cout << "��listβ�����β���1��2��2��2����listͷ������3" << endl;
	// ȡ��list�ĳ���
	std::cout << "list�ĳ��ȣ�" << list.size() << endl;
	// ����list
	for (_cghList<int>::iterator iter = list.begin(); iter != list.end(); iter++)
	{
		std::cout << "��" << i << "��Ԫ�أ�" << *iter << endl;
		i++;
	}

	std::cout << endl << endl << "-----------------ֵ����һ��ֵ����2��Ԫ��----------------" << endl;
	// ֵ����һ��ֵ����2��Ԫ��
	list.unique(2);
	// ȡ��list�ĳ���
	std::cout << "list�ĳ��ȣ�" << list.size() << endl;
	// ����list
	i = 0;
	for (_cghList<int>::iterator iter = list.begin(); iter != list.end(); iter++)
	{
		std::cout << "��" << i << "��Ԫ�أ�" << *iter << endl;
		i++;
	}

	std::cout << endl << endl << "-----------------ɾ��ֵ����2��Ԫ��----------------" << endl;
	list.remove(2);// ɾ��ֵ����2��Ԫ��
	// ȡ��list�ĳ���
	std::cout << "list�ĳ��ȣ�" << list.size() << endl;
	// ����list
	i = 0;
	for (_cghList<int>::iterator iter = list.begin(); iter != list.end(); iter++)
	{
		std::cout << "��" << i << "��Ԫ�أ�" << *iter << endl;
		i++;
	}

	std::cout << endl << endl << "-----------------���list----------------" << endl;
	list.clear(); // ���
	// ȡ��list�ĳ���
	std::cout << "list�ĳ��ȣ�" << list.size() << endl;
	// ����list
	i = 0;
	for (_cghList<int>::iterator iter = list.begin(); iter != list.end(); iter++)
	{
		std::cout << "��" << i << "��Ԫ�أ�" << *iter << endl;
		i++;
	}

	system("pause");
	return 0;
}