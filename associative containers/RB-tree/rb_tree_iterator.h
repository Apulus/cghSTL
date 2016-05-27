/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ�����:������ĵ�����
******************************************************************/

#ifndef _CGH_RB_TREE_ITERATOR_
#define _CGH_RB_TREE_ITERATOR_

#include "rb_tree_node.h"
#include <memory> // ʹ��ptrdiff_t�������ͷ�ļ�

namespace CGH{

	/* ��������� */
	struct rb_tree_base_iterator
	{
		typedef __rb_tree_node_base::base_ptr		base_ptr; // ����ڵ�ָ��
		typedef std::bidirectional_iterator_tag		iterator_category;
		typedef ptrdiff_t							difference_type;

		base_ptr									node; // ��Ա������ָ����ڵ��ָ�룬������ϵ�������ͽڵ��Ŧ��

		/* ������������ʵ��operator++ʱ���ñ����� */
		void increment()
		{
			if (node->right != 0) // ��������ӽڵ�
			{
				node = node->right; // ��������
				while (node->left != 0) // Ȼ��һֱ���������ߵ���
				{
					node = node->left;
				}
			}
			else // û�����ӽڵ�
			{
				base_ptr y = node->parent; // �ҳ����ڵ�
				while (node == y->right) // ������нڵ㱾���Ǹ����ӽڵ�
				{
					node = y; // ��һֱ���ݣ�ֱ������Ϊ���ӽڵ㡱Ϊֹ
					y = y->parent;
				}
				if (node->right != y) // ����ʱ�����ӽڵ㲻���ڴ�ʱ�ĸ��ڵ㣬��ʱ�ĸ��ڵ㼴Ϊ���
				{					  // �����ʱ��nodeΪ���
					node = y;
				}
			}
		}

		/* ������������ʵ��operator--ʱ���ñ����� */
		void decrement()
		{
			if (node->color == __rb_tree_red&&node->parent->parent == node)
			{
				// ����Ǻ�ڵ㣬���游�ڵ�����Լ�����ô�ҽڵ㼴Ϊ���
				// �����������nodeΪheaderʱ��ע�⣬header�����ӽڵ㣨��mostright����ָ����������max�ڵ�
				node = node->right;
			}
			else if (node->left != 0) // ��������ӽڵ㣬��y
			{
				base_ptr y = node->left; // ��yָ�����ӽڵ�
				while (y->right != 0) // ��y�����ӽڵ�ʱ
				{
					y = y->right; // һֱ�����ӽڵ��ߵ���
				}
				node = y; // ���Ϊ��
			}
			else // ���Ǹ��ڵ㣬Ҳû�����ӽڵ�
			{
				base_ptr y = node->parent; // �ҳ����ڵ�
				while (node == y->left) // �����нڵ�Ϊ���ӽڵ�
				{
					node = y; // һֱ���������ߣ�ֱ�����нڵ�
					y = y->parent; // ��Ϊ���ӽڵ�
				}
				node = y; // ��ʱ���ڵ㼴Ϊ��
			}
		}
	};

	/* ��������� */
	template<class value,class ref,class ptr>
	struct __rb_tree_iterator :public rb_tree_base_iterator
	{
		#pragma region typedef
		/* 
			ע�⣬���������û�г�Ա������ֻ�̳��˻����������node����
			�����������node�����Ǻ�����ڵ�����������ӵ�Ŧ��
		*/
		typedef value											value_type;
		typedef ref												reference;
		typedef ptr												pointer;
		typedef __rb_tree_iterator<value, value&, value*>		iterator;
		typedef __rb_tree_iterator<value, ref, ptr>				self;
		typedef __rb_tree_node<value>*							link_type;
		typedef size_t											size_type;

		#pragma endregion

		#pragma region ���캯��

		__rb_tree_iterator(){} // default���캯��
		__rb_tree_iterator(link_type x){ node = x; } // ��ͨ���캯��
		__rb_tree_iterator(const iterator& it){ node = it.node; } // copy���캯��

		#pragma endregion

		#pragma region �������Ļ�������

		/* ������ã����ؽڵ�ֵ */
		reference operator*()const{ return link_type(node)->value_field; }

		/* ������ã����ؽڵ�ֵ */
		pointer operator->()const{ return *(operator*()); }

		/* ���ص�����ָ��Ľڵ����ɫ */
		__rb_tree_color_type color(){ return node->color == __rb_tree_red ? 0 : 1; }

		/* ���������� */
		self& operator++()const{ increment(); return *this; }

		/* ���������� */
		self& operator++(int)
		{
			self tmp = *this;
			increment();
			return tmp;
		}

		/* ���������� */
		self& operator--()const{ decrement(); return *this; }

		/* ���������� */
		self& operator--(int)
		{
			self tmp = *this;
			decrement();
			return tmp;
		}

		/* �Ƚ����������Ƿ�ָ��ͬһ���ڵ� */
		bool operator==(const self& x)const{ return x.node == node; }

		/* �Ƚ����������Ƿ�ָ��ͬһ���ڵ� */
		bool operator!=(const self& x)const{ return x.node != node; }

		#pragma endregion
	};
}

#endif