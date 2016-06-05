/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ����ݣ�cghStl_algobase.h �е���ֵ�㷨�Ĳ���
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

	std::cout << "����vector1������ puah_back 1��2��3��4��5" << std::endl << std::endl;
	cghVector<int> vector1;
	vector1.push_back(1);
	vector1.push_back(2);
	vector1.push_back(3);
	vector1.push_back(4);
	vector1.push_back(5);
	std::cout << "����vector2������ puah_back 1��2��8��9��0" << std::endl << std::endl;
	cghVector<int> vector2;
	vector2.push_back(1);
	vector2.push_back(2);
	vector2.push_back(8);
	vector2.push_back(9);
	vector2.push_back(0);
	std::ostream_iterator<int> oite(std::cout, " ");


	std::cout << "***********************���� mismatch �㷨**********************" << std::endl << std::endl;
	std::cout << "����һ�Ե�������ָ�� vector1 �� vector2 �ĵ�һ�������Ԫ�أ�" ;
	std::cout << *(CGH::mismatch(vector1.begin(), vector1.end(), vector2.begin()).first) << ", ";
	std::cout << *(CGH::mismatch(vector1.begin(), vector1.end(), vector2.begin()).second);
	std::cout << std::endl << std::endl << std::endl;

	std::cout << "************************���� equal �㷨************************" << std::endl << std::endl;
	std::cout << "�ж� vector1 �� vector2 �Ƿ���ȣ�";
	std::string isEqual = equal(vector1.begin(), vector1.end(), vector2.begin(), vector2.end()) == 0 ? "�����" : "���" ;
	std::cout << isEqual << std::endl << std::endl;

	std::cout << "�û�ָ�� less<int>() �������ж� vector1 �� vector2 �Ĵ�С��";
	std::string isLess = equal(vector1.begin(), vector1.end(), vector2.begin(), std::less<int>()) == 0 ? "vector1 С�� vector2" : "vector1 ���� vector2" ;
	std::cout << isLess << std::endl << std::endl << std::endl;


	std::cout << "*************************���� fill �㷨************************" << std::endl << std::endl;
	std::cout << "�� vector1 ������Ԫ�ظ���Ϊ 9��" << std::endl << std::endl;
	CGH::fill(vector1.begin(), vector1.end(), 9);
	for (int i = 0; i < vector1.size(); ++i)
	{
		std::cout << "vector1[" << i << "] = " << vector1[i] << std::endl;
	}
	std::cout << std::endl << std::endl;


	std::cout << "************************���� fill_n �㷨***********************" << std::endl << std::endl;
	std::cout << "�� vector1 ��ǰ3��Ԫ�ظ���Ϊ 0��" << std::endl << std::endl;
	CGH::fill_n(vector1.begin(), 3, 0);
	for (int i = 0; i < vector1.size(); ++i)
	{
		std::cout << "vector1[" << i << "] = " << vector1[i] << std::endl;
	}
	std::cout << std::endl << std::endl;


	std::cout << "***********************���� iter_sawp �㷨**********************" << std::endl << std::endl;
	std::cout << "���� vector1[0] �� vector2[0]������ǰ��vector1[0] = " << vector1[0] << "��vector2[0] = " << vector2[0] << std::endl;
	CGH::iter_swap(vector1.begin(), vector2.begin());
	std::cout << std::endl;
	std::cout << "������vector1[0] = " << vector1[0] << "��vector2[0] = " << vector2[0] << std::endl;
	std::cout << std::endl << std::endl;


	std::cout << "****************���� lexicographical_compare �㷨***************" << std::endl << std::endl;
	std::string str1[] = {"test", "Cgh"};
	std::string str2[] = {"test", "cgh"};
	std::cout << "���� str1[] = {\"test\", \"Cgh\"}  ��  str2[] = {\"test\", \"cgh\"}" << std::endl << std::endl;
	std::cout << "�Ƚ� str1[] �� str2[] �Ĵ�С��" ;
	std::string str1Str2 = CGH::lexicographical_compare(str1, str1 + 1, str2, str2 + 1) == true ? "str1[] ���� str2[]" : "str1[] С�� str2[]";
	std::cout << str1Str2 << std::endl;
	std::cout << std::endl << std::endl;

	std::cout << std::endl;
	system("pause");
	return 0;
}