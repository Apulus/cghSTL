/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件内容：cghStl_algobase.h 中的copy的测试
******************************************************************/

#include "stdafx.h"
#include "cghVector.h"
#include "_cghList.h"
#include "cghDeque.h"
#include "cghStl_algobase.h"

class C
{
public:
	C() :_data(0){}
	C(int n) :_data(n){}

	int _data;
};

int _tmain(int argc, _TCHAR* argv[])
{
	using namespace::CGH;

	std::cout << "********************** 测试 copy 针对const char* 的特化版 *********************" << std::endl << std::endl;
	std::cout << "调用的版本：copy ( const char* )" << std::endl;
	const char srcChar[5] = {'a', 'b', 'c', 'd', 'e'};
	char destChar[5];
	CGH::copy(srcChar, srcChar + 5, destChar);
	for (int i = 0; i < 5; ++i)
	{
		std::cout << "srcChar[" << i << "] = " << srcChar[i] << "\t\t" << "destChar[" << i << "] = " << destChar[i] << std::endl ;
	}
	std::cout << std::endl;

	std::cout << "********************* 测试 copy 针对const wchar_t* 的特化版 ********************" << std::endl;
	std::cout << "调用的版本：copy ( const wchar_t* )" << std::endl;
	const wchar_t srcWchar[5] = {'a', 'b', 'c', 'd', 'e'};
	wchar_t destWchar[5];
	CGH::copy(srcWchar, srcWchar + 5, destWchar);
	for (int i = 0; i < 5; ++i)
	{
		std::cout << "srcWchar[" << i << "] = " << srcWchar[i] << "\t\t" << "destWchar[" << i << "] = " << destWchar[i] << std::endl ;
	}
	std::cout << std::endl;

	std::cout << "********************* 测试 int[] ***********************************************" << std::endl;
	std::cout << "依次调用：copy() --> copy_dispatch() --> _copy( input_iterator )" << std::endl;
	int arrSrc[5] = {0, 1, 2, 3, 4};
	int arrDest[5];
	CGH::copy(arrSrc, arrSrc + 5, arrDest);
	for (int i = 0; i < 5; ++i)
	{
		std::cout << "arrSrc[" << i << "] = " << arrSrc[i] << "\t\t" << "arrDest[" << i << "] = " << arrDest[i] << std::endl;
	}
	std::cout << std::endl;

	std::cout << "********************* 测试 deque<C> （C为自定义的类）***************************" << std::endl;
	std::cout << "依次调用：copy() --> copy_dispatch() --> _copy( random_access_iterator_tag )\n\t\t\t\t\t\t\t  --> _copy_d()" << std::endl;
	C cDequeElem[5];
	cghDeque<C> cSrcDeq;
	cDequeElem[0]._data = 100;
	cDequeElem[1]._data = 101;
	cDequeElem[2]._data = 102;
	cDequeElem[3]._data = 103;
	cDequeElem[4]._data = 104;
	cSrcDeq.push_back(cDequeElem[0]);
	cSrcDeq.push_back(cDequeElem[1]);
	cSrcDeq.push_back(cDequeElem[2]);
	cSrcDeq.push_back(cDequeElem[3]);
	cSrcDeq.push_back(cDequeElem[4]);
	cghDeque<C> cDestDeq(5, cDequeElem[0]);
	copy(cSrcDeq.begin(), cSrcDeq.end(), cDestDeq.begin());
	int m_cDeq = 0;
	for (cghDeque<C>::iterator it = cDestDeq.begin(); it != cDestDeq.end(); ++it)
	{
		std::cout << "cSrcDeq[" << m_cDeq << "] = " << it->_data << "\t\t" << "cSrcDeq[" << m_cDeq << "] = " << it->_data << std::endl;
		m_cDeq++;
	}
	std::cout << std::endl;

	std::cout << "********************* 测试 vector<int> *****************************************" << std::endl;
	std::cout << "依次调用：copy() --> copy_dispatch( T*, T* ) --> _copy( true_type )" << std::endl;
	cghVector<int> vecIntSrc;
	vecIntSrc.push_back(1);
	vecIntSrc.push_back(2);
	vecIntSrc.push_back(3);
	vecIntSrc.push_back(4);
	vecIntSrc.push_back(5);
	cghVector<int> vecIntDest(5);
	CGH::copy(vecIntSrc.begin(), vecIntSrc.end(), vecIntDest.begin());
	for (int i = 0; i < 5; ++i)
	{
		std::cout << "vecIntSrc[" << i << "] = " << vecIntSrc[i] << "\t\t" << "vecIntDest[" << i << "] = " << vecIntDest[i] << std::endl;
	}
	std::cout << std::endl;

	std::cout << "********************* 测试 vector<C> （C为自定义的类）**************************" << std::endl;
	std::cout << "依次调用：copy() --> copy_dispatch( T*, T* ) --> _copy_t( false_type )\n\t\t\t\t\t\t\t  --> _copy_d()" << std::endl;
	C cVecSrcElem[5];
	cVecSrcElem[0]._data = 0;
	cVecSrcElem[1]._data = 1;
	cVecSrcElem[2]._data = 2;
	cVecSrcElem[3]._data = 3;
	cVecSrcElem[4]._data = 4;
	cghVector<C> cVecSrc;
	cVecSrc.push_back(cVecSrcElem[0]);
	cVecSrc.push_back(cVecSrcElem[1]);
	cVecSrc.push_back(cVecSrcElem[2]);
	cVecSrc.push_back(cVecSrcElem[3]);
	cVecSrc.push_back(cVecSrcElem[4]);
	cghVector<C> cVecDest(5);
	copy(cVecSrc.begin(), cVecSrc.end(), cVecDest.begin());
	int m_cVec = 0;
	for (cghVector<C>::iterator it = cVecDest.begin(); it != cVecDest.end(); ++it)
	{
		std::cout << "cVecSrc[" << m_cVec << "] = " << it->_data << "\t\t" << "cVecDest[" << m_cVec << "] = " << it->_data << std::endl;
		m_cVec++;
	}
	std::cout << std::endl;

	system("pause");
	return 0;
}