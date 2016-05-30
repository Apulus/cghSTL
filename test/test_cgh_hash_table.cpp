/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ�����:cgh_hash_table�Ĳ���
******************************************************************/

#include "stdafx.h"
#include "cgh_hash_table.h"
using namespace::std;

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace::CGH;

	cgh_hash_table<int, int, std::hash<int>, std::identity<int>, std::equal_to<int>> test(50, std::hash<int>(), std::equal_to<int>());

	std::cout << "**************** unique���������ֵ�ظ���������� ****************" << endl << endl;
	std::cout << "���β��룺59��63��108��2��53��55" << endl << endl;
	test.insert_unique(59);
	test.insert_unique(63);
	test.insert_unique(108);
	test.insert_unique(2);
	test.insert_unique(53);
	test.insert_unique(55);

	std::cout << "����cgh_hash_table����ӡ��������";
	cgh_hash_table<int, int, std::hash<int>, std::identity<int>, std::equal_to<int>>::iterator it = test.begin();
	cgh_hash_table<int, int, std::hash<int>, std::identity<int>, std::equal_to<int>>::iterator it2 = test.end();
	for (int i = 0; i < test.size(); ++i, ++it)
	{
		cout << *it << "��";
	}
	std::cout << endl << endl << "����cgh_hash_table������bucket������ڵ������Ϊ0���ʹ�ӡ�ڵ������" << endl << endl;
	for (int i = 0; i < test.bucket_count(); ++i)
	{
		int n = test.elems_in_bucket(i);
		if (n != 0)
		{
			cout << "bucket[" << i << "] �� " << n << " ���ڵ�" << endl;
		}
	}
	cout << endl << "cgh_hash_table�Ľڵ������" << test.size() << endl;
	cout << endl << "cgh_hash_table��bucket������" << test.bucket_count() << endl;
	cout << "-----------------------------" << endl << endl << endl;


	std::cout << "**************** equal�������ֵ�ظ���������� ****************" << endl << endl;
	std::cout << "��unique������ԵĻ����ϣ��������룺1��2��3��...��46��47" << endl << endl;
	for (int i = 0; i <= 47; ++i)
	{
		test.insert_equal(i);
	}
	std::cout << "����cgh_hash_table����ӡ��������" << endl << endl;
	it = test.begin();
	for (int i = 0; i < test.size(); ++i, ++it)
	{
		cout << *it << " ";
		if (i % 15 == 0 && i != 0)
		{
			cout << endl;
		}
	}
	cout << endl << endl << "cgh_hash_table�Ľڵ������" << test.size() << endl;
	cout << endl << "cgh_hash_table��bucket������" << test.bucket_count() << endl;
	std::cout << endl << endl << "����cgh_hash_table������bucket������ڵ������Ϊ0���ʹ�ӡ�ڵ������" << endl << endl;
	for (int i = 0; i < test.bucket_count(); ++i)
	{
		int n = test.elems_in_bucket(i);
		if (n != 0)
		{
			cout << "bucket[" << i << "] �� " << n << " ���ڵ�" << endl;
		}
	}
	cout << "-----------------------------" << endl << endl << endl;
	system("pause");
	return 0;
}