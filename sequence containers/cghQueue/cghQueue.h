/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ�����:queue��ʵ�ִ���
******************************************************************/

#ifndef _CGH_DEQUE_QUEUE_
#define _CGH_DEQUE_QUEUE_

#include "cghDeque.h"
#include"cghAlloc.h"
#include "globalConstruct.h"

namespace CGH{
	/*
		����cghDeque��ΪcghQueue�ĵײ�ʵ��
	*/
	template<class T, class sequence = cghDeque<T>>
	class cghQueue{
	public:
		typedef typename sequence::value_type		value_type;
		typedef typename sequence::size_type		size_type;
		typedef typename sequence::reference		reference;

	protected:
		sequence s;

	public:
		cghQueue() :s(){ } // ���캯��
		bool empty() const{ return s.empty(); } // queue�Ƿ�Ϊ��
		size_type size() { return s.size(); } // queue�ĳ���
		reference front(){ return s.front(); } // ǰ��Ԫ��
		reference back(){ return s.back(); } // ĩ��Ԫ��
		void push(const value_type& x){ s.push_back(x); } // ĩ�˽�
		void pop(){ s.pop_front(); } // ǰ�˳�
	};
}

#endif