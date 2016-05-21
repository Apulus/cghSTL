/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ�����:stack��ʵ�ִ���
******************************************************************/

#ifndef _CGH_DEQUE_STACK_
#define _CGH_DEQUE_STACK_

#include "cghDeque.h"
#include"cghAlloc.h"
#include "globalConstruct.h"

namespace CGH{
	/*
		����cghDeque��Ϊstack�ĵײ�ʵ��
	*/
	template<class T, class sequence = cghDeque<T>>
	class cghStack{
	public:
		typedef typename sequence::value_type		value_type;
		typedef typename sequence::size_type		size_type;
		typedef typename sequence::reference		reference;

	protected:
		sequence s;

	public:
		cghStack() :s(){ } // ���캯��
		bool empty() const{ return s.empty(); } // stack�Ƿ�Ϊ��
		size_type size() { return s.size(); } // stack�ĳ���
		reference top() { return s.back(); } // ջ��Ԫ��
		void push(const value_type& x){ s.push_back(x); } // ѹջ
		void pop(){ s.pop_back(); } // ��ջ
	};
}

#endif