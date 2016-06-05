/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件内容：cghStl_algobase.h 中的数值算法的测试
******************************************************************/

#include "stdafx.h"
#include "cghVector.h"
#include "cghStl_algobase.h"
#include <string>
#include <iterator>
#include "cghUtil.h"

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace::CGH;

	std::cout << "创建vector1，依次 puah_back 1、2、3、4、5" << std::endl << std::endl;
	cghVector<int> vector1;
	vector1.push_back(1);
	vector1.push_back(2);
	vector1.push_back(3);
	vector1.push_back(4);
	vector1.push_back(5);
	std::cout << "创建vector2，依次 puah_back 1、2、8、9、0" << std::endl << std::endl;
	cghVector<int> vector2;
	vector2.push_back(1);
	vector2.push_back(2);
	vector2.push_back(8);
	vector2.push_back(9);
	vector2.push_back(0);
	std::ostream_iterator<int> oite(std::cout, " ");


	std::cout << "***********************测试 mismatch 算法**********************" << std::endl << std::endl;
	std::cout << "返回一对迭代器，指出 vector1 和 vector2 的第一个不相等元素：" ;
	std::cout << *(CGH::mismatch(vector1.begin(), vector1.end(), vector2.begin()).first) << ", ";
	std::cout << *(CGH::mismatch(vector1.begin(), vector1.end(), vector2.begin()).second);
	std::cout << std::endl << std::endl << std::endl;

	std::cout << "************************测试 equal 算法************************" << std::endl << std::endl;
	std::cout << "判断 vector1 和 vector2 是否相等：";
	std::string isEqual = equal(vector1.begin(), vector1.end(), vector2.begin(), vector2.end()) == 0 ? "不相等" : "相等" ;
	std::cout << isEqual << std::endl << std::endl;

	std::cout << "用户指定 less<int>() 函数，判断 vector1 和 vector2 的大小：";
	std::string isLess = equal(vector1.begin(), vector1.end(), vector2.begin(), std::less<int>()) == 0 ? "vector1 小于 vector2" : "vector1 大于 vector2" ;
	std::cout << isLess << std::endl << std::endl << std::endl;


	std::cout << "*************************测试 fill 算法************************" << std::endl << std::endl;
	std::cout << "将 vector1 的所有元素改填为 9：" << std::endl << std::endl;
	CGH::fill(vector1.begin(), vector1.end(), 9);
	for (int i = 0; i < vector1.size(); ++i)
	{
		std::cout << "vector1[" << i << "] = " << vector1[i] << std::endl;
	}
	std::cout << std::endl << std::endl;


	std::cout << "************************测试 fill_n 算法***********************" << std::endl << std::endl;
	std::cout << "将 vector1 的前3个元素改填为 0：" << std::endl << std::endl;
	CGH::fill_n(vector1.begin(), 3, 0);
	for (int i = 0; i < vector1.size(); ++i)
	{
		std::cout << "vector1[" << i << "] = " << vector1[i] << std::endl;
	}
	std::cout << std::endl << std::endl;


	std::cout << "***********************测试 iter_sawp 算法**********************" << std::endl << std::endl;
	std::cout << "交换 vector1[0] 和 vector2[0]，交换前，vector1[0] = " << vector1[0] << "，vector2[0] = " << vector2[0] << std::endl;
	CGH::iter_swap(vector1.begin(), vector2.begin());
	std::cout << std::endl;
	std::cout << "交换后，vector1[0] = " << vector1[0] << "，vector2[0] = " << vector2[0] << std::endl;
	std::cout << std::endl << std::endl;


	std::cout << "****************测试 lexicographical_compare 算法***************" << std::endl << std::endl;
	std::string str1[] = {"test", "Cgh"};
	std::string str2[] = {"test", "cgh"};
	std::cout << "现有 str1[] = {\"test\", \"Cgh\"}  和  str2[] = {\"test\", \"cgh\"}" << std::endl << std::endl;
	std::cout << "比较 str1[] 和 str2[] 的大小：" ;
	std::string str1Str2 = CGH::lexicographical_compare(str1, str1 + 1, str2, str2 + 1) == true ? "str1[] 大于 str2[]" : "str1[] 小于 str2[]";
	std::cout << str1Str2 << std::endl;
	std::cout << std::endl << std::endl;

	std::cout << std::endl;
	system("pause");
	return 0;
}