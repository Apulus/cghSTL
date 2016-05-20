/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件名称:cghDeque容器的测试代码
******************************************************************/

#include "stdafx.h"
#include "cghVector.h"
#include "cghDeque.h"
using namespace::std;

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace::CGH;



	/***************************************************************************************/
	/***************************************************************************************/
	std::cout << "************************初始化、前插、后插测试************************" << endl;
	std::cout << endl;
	cghDeque<int> test(1, 1); // 初始化
	test.push_back(2); // 后插
	test.push_back(3); // 后插
	test.push_back(4); // 后插
	test.push_front(0); // 前插
	test.push_front(-1); // 前插

	std::cout << "当前元素：";
	for (cghDeque<int>::iterator iter = test.begin(); iter != test.end(); ++iter){
		std::cout << *iter << ",";
	}
	std::cout << endl;
	std::cout << endl;
	std::cout << "长度：" << test.size() << endl;
	std::cout << endl;




	/***************************************************************************************/
	/***************************************************************************************/
	std::cout << "************************前删、后删测试************************" << endl;
	std::cout << endl;
	test.pop_front(); // 前删
	test.pop_back(); // 后删
	std::cout << "当前元素：";
	for (cghDeque<int>::iterator iter = test.begin(); iter != test.end(); ++iter){
		std::cout << *iter << ",";
	}
	std::cout << endl;
	std::cout << endl;
	std::cout << "长度：" << test.size() << endl;
	std::cout << endl;




	/***************************************************************************************/
	/***************************************************************************************/
	std::cout << "************************清空测试************************" << endl;
	std::cout << endl;
	test.clear(); // 前删
	std::cout << "当前元素：";
	for (cghDeque<int>::iterator iter = test.begin(); iter != test.end(); ++iter){
		std::cout << *iter << ",";
	}
	std::cout << endl;
	std::cout << endl;
	std::cout << "长度：" << test.size() << endl;
	std::cout << endl;




	/***************************************************************************************/
	/***************************************************************************************/
	std::cout << "************************跨主控节点后插测试************************" << endl;
	std::cout << endl;
	std::cout << "缓冲区默认大小为512字节，一个int占4字节，512 / 4 = 128" << endl << endl;
	std::cout << "当插入的元素量 > 128 时就会跨主控节点" << endl;
	std::cout << endl;
	test.clear(); // 前删
	for (int i = 0; i < 150; i++){
		test.push_back(i);
	}
	std::cout << "当前元素：";
	for (cghDeque<int>::iterator iter = test.begin(); iter != test.end(); ++iter){
		std::cout << *iter << ",";
	}
	std::cout << endl;
	std::cout << endl;
	std::cout << "长度：" << test.size() << endl;
	std::cout << endl;




	/***************************************************************************************/
	/***************************************************************************************/
	std::cout << "************************跨主控节点前插测试************************" << endl;
	std::cout << endl;
	std::cout << "缓冲区默认大小为512字节，一个int占4字节，512 / 4 = 128" << endl << endl;
	std::cout << "当插入的元素量 > 128 时就会跨主控节点" << endl;
	std::cout << endl;
	test.clear(); // 前删
	for (int i = 0; i < 150; i++){
		test.push_front(i);
	}
	std::cout << "当前元素：";
	for (cghDeque<int>::iterator iter = test.begin(); iter != test.end(); ++iter){
		std::cout << *iter << ",";
	}
	std::cout << endl;
	std::cout << endl;
	std::cout << "长度：" << test.size() << endl;
	std::cout << endl;

	std::cout << "************************测试结束************************" << endl;
	std::cout << endl;
	system("pause");
	return 0;
}

