//// iterator.cpp : 定义控制台应用程序的入口点。
////
//
#include "stdafx.h"
#include "cghList.h"
#include "cghIterator.h"
#include "ListItem.h"
#include<iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	cghList<int> myList;
	for (int i = 0; i < 5; i++){
		myList.insert_front(i);
	}

	//myList.display();

	for (ListIter<ListItem<int>> iter = myList.front(); iter != myList.end(); iter++){
		std::cout << iter->_value << std::endl;
	}
	system("pause");
	return 0;
}

