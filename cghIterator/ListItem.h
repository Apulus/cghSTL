/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  功能:cghIterator中元素的实现代码
******************************************************************/

#ifndef _CGH_LIST_ITEM_
#define _CGH_LIST_ITEM_

// 定义链表节点类型
template<typename T>
class ListItem{
public:
	T value() const{ return _value; }
	ListItem* next() const{ return _next; }
	ListItem(T value) : _value(value), _next(NULL) { }
public:
	T _value; // 单向链表的节点元素的值域
	ListItem* _next; // 单向链表的节点元素的指针域
};

#endif