/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件内容:cgh_hash_table的测试
******************************************************************/

#include "stdafx.h"
#include "cgh_hash_table.h"
using namespace::std;

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace::CGH;

	cgh_hash_table<int, int, std::hash<int>, std::identity<int>, std::equal_to<int>> test(50, std::hash<int>(), std::equal_to<int>());

	std::cout << "**************** unique（不允许键值重复）插入测试 ****************" << endl << endl;
	std::cout << "依次插入：59，63，108，2，53，55" << endl << endl;
	test.insert_unique(59);
	test.insert_unique(63);
	test.insert_unique(108);
	test.insert_unique(2);
	test.insert_unique(53);
	test.insert_unique(55);

	std::cout << "遍历cgh_hash_table，打印插入结果：";
	cgh_hash_table<int, int, std::hash<int>, std::identity<int>, std::equal_to<int>>::iterator it = test.begin();
	cgh_hash_table<int, int, std::hash<int>, std::identity<int>, std::equal_to<int>>::iterator it2 = test.end();
	for (int i = 0; i < test.size(); ++i, ++it)
	{
		cout << *it << "，";
	}
	std::cout << endl << endl << "遍历cgh_hash_table的所有bucket，如果节点个数不为0，就打印节点个数：" << endl << endl;
	for (int i = 0; i < test.bucket_count(); ++i)
	{
		int n = test.elems_in_bucket(i);
		if (n != 0)
		{
			cout << "bucket[" << i << "] 有 " << n << " 个节点" << endl;
		}
	}
	cout << endl << "cgh_hash_table的节点个数：" << test.size() << endl;
	cout << endl << "cgh_hash_table的bucket个数：" << test.bucket_count() << endl;
	cout << "-----------------------------" << endl << endl << endl;


	std::cout << "**************** equal（允许键值重复）插入测试 ****************" << endl << endl;
	std::cout << "在unique插入测试的基础上，继续插入：1，2，3，...，46，47" << endl << endl;
	for (int i = 0; i <= 47; ++i)
	{
		test.insert_equal(i);
	}
	std::cout << "遍历cgh_hash_table，打印插入结果：" << endl << endl;
	it = test.begin();
	for (int i = 0; i < test.size(); ++i, ++it)
	{
		cout << *it << " ";
		if (i % 15 == 0 && i != 0)
		{
			cout << endl;
		}
	}
	cout << endl << endl << "cgh_hash_table的节点个数：" << test.size() << endl;
	cout << endl << "cgh_hash_table的bucket个数：" << test.bucket_count() << endl;
	std::cout << endl << endl << "遍历cgh_hash_table的所有bucket，如果节点个数不为0，就打印节点个数：" << endl << endl;
	for (int i = 0; i < test.bucket_count(); ++i)
	{
		int n = test.elems_in_bucket(i);
		if (n != 0)
		{
			cout << "bucket[" << i << "] 有 " << n << " 个节点" << endl;
		}
	}
	cout << "-----------------------------" << endl << endl << endl;
	system("pause");
	return 0;
}