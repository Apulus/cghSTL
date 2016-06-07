/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ����ݣ������߼������ࣨLogical���������󣨷º�����
******************************************************************/

#include "stdafx.h"
#include <iostream>
#include "cgh_function_obj.h"


int _tmain(int argc, _TCHAR* argv[])
{
	using namespace::CGH;

	logical_and<int> logical_and_obj;
	logical_or<int> logical_or_obj;
	logical_not<int> logical_not_obj;

	std::cout << std::endl;
	std::cout << "�߼��ຯ������3����logical_and��logical_or��logical_not" << std::endl << std::endl;
	std::cout << "************************ �����߼��ຯ������1 ***************************" << std::endl << std::endl;

	std::cout << "logical_and_obj(3, 5) = " << logical_and_obj(3, 5) << std::endl << std::endl;
	std::cout << "logical_or_obj(3, 5) = " << logical_or_obj(3, 5) << std::endl << std::endl;
	std::cout << "logical_not_obj(3) = " << logical_not_obj(3) << std::endl << std::endl;

	std::cout << "************************* �����߼��ຯ������2 **************************" << std::endl << std::endl;

	std::cout << "logical_and_obj<int>()(3, 5) = " << logical_and<int>()(3, 5) << std::endl << std::endl;
	std::cout << "logical_or_obj<int>()(3, 5) = " << logical_or<int>()(3, 5) << std::endl << std::endl;
	std::cout << "logical_not_obj<int>()(3) = " << logical_not<int>()(3) << std::endl << std::endl;

	system("pause");
	return 0;
}