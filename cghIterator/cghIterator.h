/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  功能:cghIterator迭代器的实现代码
******************************************************************/

#ifndef _CGH_ITERATOR_
#define _CGH_ITERATOR

template<typename Item>
struct ListIter : public std::iterator<std::forward_iterator_tag, Item>
{
	Item* ptr; // 

	ListIter(Item* p = 0) :ptr(p) { }

	Item& operator*() const { return *ptr; }
	Item* operator->() const { return ptr; }

	ListIter& operator++(){
		ptr = ptr->next();
		return *this;
	}

	ListIter& operator++(int){
		ListIter tmp = *this;
		++*this;
		return tmp;
	}

	bool operator==(const ListIter& i) const{
		return ptr == i.ptr;
	}

	bool operator!=(const ListIter& i) const{
		return ptr != i.ptr;
	}

	Item& begin(){return }

};

#endif