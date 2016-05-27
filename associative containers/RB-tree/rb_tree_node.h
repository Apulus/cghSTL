/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ�����:������Ľڵ�
******************************************************************/

#ifndef _CGH_RB_TREE_NODE_
#define _CGH_RB_TREE_NODE_

namespace CGH{
	typedef bool __rb_tree_color_type; // �ò������Ͷ�����������ɫ
	const __rb_tree_color_type __rb_tree_red = false; // ��ɫΪ0
	const __rb_tree_color_type __rb_tree_black = true; // ��ɫΪ1

	/* ����ڵ� */
	struct __rb_tree_node_base{
		typedef __rb_tree_color_type	color_type; // �ڵ���ɫ
		typedef __rb_tree_node_base*	base_ptr; // �ڵ�ָ��

		color_type color; // �ڵ���ɫ
		base_ptr parent; // ���ڵ�ָ��
		base_ptr left; // ���ӽڵ�ָ��
		base_ptr right; // ���ӽڵ�ָ��

		/*
			����ĳ���ڵ�λ�ã��ҵ�����ߵĽڵ�
			����������ڵ��λ�ã������ҵ����ź��������ߵĽڵ㣨Ҳ�����ҵ�����Сֵ�ڵ㣩
			���ؽڵ�λ��
		*/
		static base_ptr minimum(base_ptr x)
		{
			while (x->left != 0)
			{
				x = x->left; // һֱ�����ߣ������ҵ���С�ڵ�
			}
			return x;
		}

		/*
			����ĳ���ڵ�λ�ã��ҵ����ұߵĽڵ�
			����������ڵ��λ�ã������ҵ����ź�������ұߵĽڵ㣨Ҳ�����ҵ������ֵ�ڵ㣩
			���ؽڵ�λ��
		*/
		static base_ptr maximum(base_ptr x)
		{
			while (x->right != 0)
			{
				x = x->right; // һֱ�������ߣ������ҵ����ڵ�
			}
			return x;
		}
	};

	/* ����ڵ� */
	template<class value>
	struct __rb_tree_node :public __rb_tree_node_base{
		/* ����̳��˸���ĳ�Ա��color��parent��left��right��value_field������ʾ�ڵ��ֵ�� */
		typedef __rb_tree_node<value>* link_type;
		value value_field; // �ڵ�ֵ��
	};
}

#endif