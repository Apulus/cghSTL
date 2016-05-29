/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ�����:cghSet��ʵ��
******************************************************************/

#ifndef _CGH_MULTI_SET_
#define _CGH_MULTI_SET_

#include "globalConstruct.h"
#include "cghAlloc.h"
#include "rb_tree.h"

namespace CGH{
	template<class key, class compare = std::less<key>, class Alloc = cghAllocator<key>>/* Ĭ������²��õ������� */
	class cghMultiset{

#pragma region typedef

	private:
		typedef key		key_type;
		typedef key		value_type;
		typedef compare key_compare;
		typedef compare value_compare;
		typedef	cgh_rb_tree<key_type, value_type, std::identity<value_type>, key_compare, Alloc>	rep_type;
		rep_type t;
	public:
		typedef typename rep_type::const_pointer	pointer;
		typedef typename rep_type::const_pointer	const_pointer;
		typedef typename rep_type::const_reference	reference;
		typedef typename rep_type::const_reference	const_ference;
		typedef typename rep_type::iterator			iterator;
		typedef typename rep_type::size_type		size_type;
		typedef typename rep_type::difference_type	difference_type;

#pragma endregion

#pragma region ���캯��
	public:
		cghMultiset() :t(compare()){}
		cghMultiset(const cghMultiset<key, compare, Alloc>&x) :t(x.t){}
		cghMultiset<key, compare, Alloc>& operator=(const cghMultiset<key, compare, Alloc>&x)
		{
			t = x.t;
			return *this;
		}
#pragma endregion

#pragma region �ṩ���û��ĺ���
		/* ���ؼ��ȽϺ��� */
		key_compare key_comp()const{ return t.key_comp(); }

		/* ����ֵ�ȽϺ��� */
		value_compare value_comp()const{ return t.key_comp(); }

		/* ���ص�������ָ��cghMultiset�ĵ�һ��Ԫ�� */
		iterator begin(){ return t.begin(); }

		/* ���ص�������ָ��cghMultiset�����һ��Ԫ�� */
		iterator end(){ return t.end(); }

		/* cghMultiset�Ƿ�Ϊ�� */
		bool empty() const{ return t.empty(); }

		/* cghMultiset��С */
		size_type size()const{ return t.size(); }

		/* cghMultiset������� */
		size_type max_size()const{ return t.max_size(); }

		/* ����Ԫ�ص�cghMultiset�� */
		iterator insert(const value_type&x)
		{
			//std::pair<typename rep_type::iterator, bool> p = t.insert_equal(x);
			return t.insert_equal(x);
		}

		/*
		���ص�������ָ��Ҫ���ҵ�Ԫ��
		���û���ҵ�������end
		*/
		iterator find(const key_type&x){ return t.find(x); }
#pragma endregion

	};
}

#endif