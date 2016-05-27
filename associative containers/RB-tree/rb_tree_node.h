/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件内容:红黑树的节点
******************************************************************/

#ifndef _CGH_RB_TREE_NODE_
#define _CGH_RB_TREE_NODE_

namespace CGH{
	typedef bool __rb_tree_color_type; // 用布尔类型定义红黑树的颜色
	const __rb_tree_color_type __rb_tree_red = false; // 红色为0
	const __rb_tree_color_type __rb_tree_black = true; // 黑色为1

	/* 基层节点 */
	struct __rb_tree_node_base{
		typedef __rb_tree_color_type	color_type; // 节点颜色
		typedef __rb_tree_node_base*	base_ptr; // 节点指针

		color_type color; // 节点颜色
		base_ptr parent; // 父节点指针
		base_ptr left; // 左子节点指针
		base_ptr right; // 右子节点指针

		/*
			给定某个节点位置，找到最左边的节点
			如果给定根节点的位置，可以找到整颗红黑树最左边的节点（也就是找到了最小值节点）
			返回节点位置
		*/
		static base_ptr minimum(base_ptr x)
		{
			while (x->left != 0)
			{
				x = x->left; // 一直向左走，就能找到最小节点
			}
			return x;
		}

		/*
			给定某个节点位置，找到最右边的节点
			如果给定根节点的位置，可以找到整颗红黑树最右边的节点（也就是找到了最大值节点）
			返回节点位置
		*/
		static base_ptr maximum(base_ptr x)
		{
			while (x->right != 0)
			{
				x = x->right; // 一直向左右走，就能找到最大节点
			}
			return x;
		}
	};

	/* 正规节点 */
	template<class value>
	struct __rb_tree_node :public __rb_tree_node_base{
		/* 子类继承了父类的成员：color、parent、left、right，value_field用来表示节点的值域 */
		typedef __rb_tree_node<value>* link_type;
		value value_field; // 节点值域
	};
}

#endif