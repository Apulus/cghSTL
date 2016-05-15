/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ����:cghIterator��Ԫ�ص�ʵ�ִ���
******************************************************************/

#ifndef _CGH_LIST_ITEM_
#define _CGH_LIST_ITEM_

// ��������ڵ�����
template<typename T>
class ListItem{
public:
	T value() const{ return _value; }
	ListItem* next() const{ return _next; }
	ListItem(T value) : _value(value), _next(NULL) { }
public:
	T _value; // ��������Ľڵ�Ԫ�ص�ֵ��
	ListItem* _next; // ��������Ľڵ�Ԫ�ص�ָ����
};

#endif