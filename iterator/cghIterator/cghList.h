/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ����:cghIterator�е��������ʵ�ִ���
******************************************************************/

#ifndef _CGH_LIST
#define _CGH_LIST

#include"ListItem.h"
#include <iostream>

template<typename T>
class cghList{
public:
	void insert_front(T value);
	void insert_end(T value);
	void display(std::ostream& os = std::cout)const;
	cghList() :_end(NULL), _front(NULL) { }
	ListItem<T>* front()const{ return _front; }
	ListItem<T>* end()const{ return _end; }
private:
	ListItem<T>* _end;
	ListItem<T>* _front;
	long _size;
};

/**
*  ����ڵ㵽�����ͷ��
*/
template<typename T>
void cghList<T>::insert_front(T value){
	cghList<T>::_size++;
	ListItem<T>* tmp = new ListItem<T>(value);
	if (typename cghList<T>::_front == NULL) {
		typename cghList<T>::_front = tmp;
		typename cghList<T>::_end = tmp;
	}
	else{
		tmp->_next = _front;
		_front = tmp;
	}
}

/**
*  ����ڵ㵽�����β��
*/
template<typename T>
void cghList<T>::insert_end(T value){
	cghList<T>::_size++;
	ListItem<T>* tmp = new ListItem<T>(value);
	if (typename cghList<T>::_front == NULL) {
		typename cghList<T>::_front = tmp;
		typename cghList<T>::_end = tmp;
	}
	else{
		typename cghList<T>::_end->_next = tmp;
		typename cghList<T>::_end = typename cghList<T>::_end->_next;
	}
}

/**
*  ��ͷ��ʼѭ����ӡ����
*/
template<typename T>
void cghList<T>::display(std::ostream& os = std::cout)const{
	if (typename cghList<T>::_front == NULL || typename cghList<T>::_end == NULL){
		return;
	}
	ListItem<T>* tmp = typename cghList<T>::_front;
	while (tmp != NULL){
		std::cout << tmp->_value << std::endl;
		tmp = tmp->_next;
	}
}
#endif