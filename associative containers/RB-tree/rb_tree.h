/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件内容:红黑树
******************************************************************/

#ifndef _CGH_RB_TREE_
#define _CGH_RB_TREE_

#include "globalConstruct.h" // 全局构造析构函数 
#include "cghAlloc.h" // 空间配置器
#include "rb_tree_node.h" // 红黑树节点
#include "rb_tree_iterator.h" // 红黑树迭代器
#include <memory> // 使用ptrdiff_t需包含此头文件

namespace CGH{
	template<class key, class value, class keyOfValue, class compare, class Alloc = cghAllocator<key>>
	class cgh_rb_tree{

		#pragma region typedef

	protected:
		typedef void*									void_pointer; // 空指针
		typedef __rb_tree_node_base*					base_ptr; // 基层节点指针
		typedef __rb_tree_node<value>					rb_tree_node; // 正规节点指针
		typedef simple_alloc<rb_tree_node, Alloc>		rb_tree_node_allocator; // 节点空间配置器
		typedef __rb_tree_color_type					color_type; // 节点颜色

	public:
		typedef key							key_type; // 键
		typedef value						value_type; //值
		typedef value_type*					pointer; // 值指针
		typedef const value_type*			const_pointer; // const值指针
		typedef value_type&					reference;  // 值引用
		typedef const value_type&			const_reference; // const值引用
		typedef rb_tree_node*				link_type; // 节点指针
		typedef size_t						size_type;
		typedef ptrdiff_t					difference_type;

		#pragma endregion

		#pragma region 红黑树的成员变量
	protected:

		size_type node_count; // 红黑树的节点数目
		link_type header; // 哨兵节点，其parent指针指向根节点
		compare key_compare; // 比较值大小的函数

	public:
		typedef __rb_tree_iterator<value_type, reference, pointer> iterator; // 定义红黑树的迭代器

		#pragma endregion

		#pragma region 树的初始化，节点的构造、析构、复制

	protected:
		/* 调用空间配置器申请一个节点 */
		link_type get_node(){ return rb_tree_node_allocator::allocate(); }

		/* 调用空间配置器释还一个节点 */
		void put_node(link_type p){ rb_tree_node_allocator::deallocate(p); }

		/* 申请并初始化节点 */
		link_type create_node(const value_type& x)
		{
			// x是节点的值
			link_type tmp = get_node(); // 申请一个节点
			construct(&tmp->value_field, x); // 调用全局构造函数初始化节点
			return tmp;
		}

		/* 克隆节点 */
		link_type clone_node(link_type x)
		{
			link_type tmp = create_node(x->value_field); // 申请并初始化节点
			tmp->color = x->color;
			tmp->left = 0;
			tmp->right = 0;
			return tmp;
		}

		/* 释还节点 */
		void destroy_node(link_type p)
		{
			destroy(&p->value_field); // 调用全局析构函数销毁节点值
			put_node(p); // 释还内存
		}

	private:
		/* 初始化红黑树 */
		void init()
		{
			header = get_node(); // 初始化header节点，header节点作为整颗红黑树的哨兵，header的parent指针指向根节点，header的类型是__rb_tree_node*
			color(header) = __rb_tree_red; // 设置header节点为红色
			root() = 0; // root()获得红黑树的根节点，header的parent指针指向根节点，初始化红黑树的根节点指针为null
			leftmost() = header; // 设置header节点的左子树指向自己
			rightmost() = header; // 设置header节点的右子树指向自己
		}

	public:
		/* 构造函数 */
		cgh_rb_tree(const compare& cmp = compare()) :node_count(0), key_compare(cmp){ init(); }

		/* 析构函数 */
		~cgh_rb_tree()
		{
			//clear();
			put_node(header);
		}

		#pragma endregion

		#pragma region protected：辅助函数

	protected:
		/* 获得根节点（header是哨兵，其parent执行根节点） */
		link_type& root()const{ return (link_type&)header->parent; }

		/* 获得整棵树最左边的节点 */
		link_type& leftmost()const{ return (link_type&)header->left; }

		/* 获得整棵树最右边的节点 */
		link_type& rightmost()const{ return (link_type&)header->right; }

		/* 返回节点的左子节点 */
		static link_type& left(link_type x){ return (link_type&)(x->left); }

		/* 返回节点的右子节点 */
		static link_type& right(link_type x){ return (link_type&)(x->right); }

		/* 返回节点的父节点 */
		static link_type& parent(link_type x){ return (link_type&)(x->parent); }

		/* 返回节点的value */
		static reference value(link_type x){ return (x->value_field); }

		/* 返回节点的颜色 */
		static color_type& color(link_type x){ return (color_type)(x->color); }

		/* 返回节点的value */
		static const key& key(base_ptr x){ return keyOfValue()(value(link_type(x))); }

		/* 返回最小值节点 */
		static link_type minimum(link_type x)
		{
			return (link_type)__rb_tree_node_base::minimum(x); // 调用基层节点的最小节点函数
		}

		/* 返回最大值节点 */
		static link_type maximum(link_type x)
		{
			return (link_type)__rb_tree_node_base::maximum(x); // 调用基层节点的最大节点函数
		}

		#pragma endregion
		
		#pragma region 提供给用户的工具函数

	public:
		/* 获得根节点的值（header是哨兵，其parent执行根节点）; return (link_type&)header->parent->; */
		value_type root_value(){ return value((link_type)header->parent); }

		/* 返回比较大小的函数 */
		compare key_comp()const{ return key_compare; }

		/* 返回一个迭代器，指向红黑树最左边的节点 */
		iterator begin(){ return leftmost(); }

		/* 返回一个迭代器，指向红黑树最右边的节点 */
		iterator end(){ return header; }

		/* 判断红黑树是否为空 */
		bool empty()const{ return node_count == 0; }

		/* 返回红黑树大小（节点数目） */
		size_type size() const{ return node_count; }

		/* 红黑树最大节点数 */
		size_type max_size()const{ return size_type(-1); }

		#pragma endregion

		#pragma region 红黑树操作

	public:
		/*
			插入新值，节点键值不能重复，如果重复则插入无效
			返回值是pair，pair的第一个元素是rb_tree迭代器，指向新节点
			第二个元素表示插入成功与否
		*/
		std::pair<iterator, bool> insert_unique(const value_type& v)
		{
			link_type y = header; // link_type的类型是__rb_tree_node*，header是哨兵，令y拿到header
			link_type x = root(); // x拿到红黑树的根节点，红黑树的根节点被初始化为null，因此插入第一个值时，x等于null
			bool comp = true; // 比较大小的布尔值
			while (x != 0) // x节点不为null，说明我们找到插入新节点的位置，于是执行while循环内的语句，不停向下遍历
			{
				y = x; // y保存着x节点的父节点
				// 如果待插入的值小于节点x的值，comp为true，否则comp为false。key_compare是比较大小的函数（由模板指定）
				comp = key_compare(keyOfValue()(v), key(x)); 
				// 如果comp为true，说明待插入值小于节点x的值，我们沿左走，令x为x的左子树
				// 如果comp为false，说明待插入值大于节点x的值，我们沿右走，令x为x的右子树
				x = comp ? left(x) : right(x);
			}
			iterator j = iterator(y); // 令j指向插入点的父节点
			if (comp) // 如果插入的值比父节点的值小（意味着我们要插入到父节点的左边），进入if
			{
				// begin()调用leftmost()，获得整颗树最左侧的节点，如果插入节点为整颗树的最左侧节点就进入if
				if (begin() == j) 
				{
					return std::pair<iterator, bool>(__insert(x, y, v), true); // x是插入点、y为插入点的父节点，v为插入的值
				}
				else
				{
					j--;
				}
			}
			// 新值不与既有节点值重复，可以插入
			if (key_compare(key(j.node), keyOfValue()(v)))
			{
				return std::pair<iterator, bool>(__insert(x, y, v), true);
			}
			return std::pair<iterator, bool>(j, false); // 如果到了这里，说明新值一定与树中键值重复，不能插入
		}

		/*
			插入新值，节点的键值允许重复
			返回红黑树的迭代器，该迭代器指向新节点
		*/
		iterator insert_equal(const value_type& v)
		{
			link_type y = header;
			link_type x = root(); // x指向根节点
			while (x != 0) // 从根节点开始向下寻找合适的插入点
			{
				y = x;
				// 遇大往右，遇小往左
				x = key_compare(keyOfValue()(v), key(x)) ? left(x) : right(x);
			}
			return __insert(x, y, v); // x为待插入点，y为插入点的父节点，v为插入的值
		}

		/* 寻找红黑树中是否有键值为k的节点 */
		iterator find(const value_type& k)
		{
			link_type y = header; // 令y等于哨兵节点（哨兵节点不是树的一部分，但是其parent指向根节点）
			link_type x = root(); // 拿到根节点

			while (x != 0)
			{
				// key_compare是比较大小的函数
				if (!key_compare(key(x), k)) // x值大于k
				{
					y = x; 
					x = left(x); // 遇到大值就向左走
				}
				else // x值与于k
				{
					x = right(x); // 遇到小值往左走
				}
			}
			iterator j = iterator(y);
			return (j == end() || key_compare(k, key(j.node))) ? end() : j;
		}

	private:
		/*
			插入操作
			x_：待插入节点
			y_：插入节点的父节点
			v：插入的值
		*/
		iterator __insert(base_ptr x_, base_ptr y_, const value_type& v)
		{
			// base_ptr实为__rb_tree_node_base*，link_type实为__rb_tree_node*
			// 我们把__rb_tree_node_base*向下强转为__rb_tree_node*
			// __rb_tree_node结构体比__rb_tree_node_base结构体多了value_field，value_field用于保存值
			link_type x = (link_type)x_; // x指向插入点
			link_type y = (link_type)y_; // y指向插入点的父节点
			link_type z;

			// 1.y == header：插入点的父节点为header（注意header是哨兵，header不属于树的一部分，但是header的parent指向根节点）。y == header说明插入点为根节点
			// 2.x == 0：说明插入点在叶子节点下方（叶子节点的左子树和右子树均为null），也就是在叶子节点下挂新的节点；x != 0说明插入点在树的内部某个节点上
			// 3.key_compare(keyOfValue()(v), key(y))：带插入节点的值要比父节点的值小（意味着我们要插入到父节点的左子树上）
			if (y == header || x != 0 || key_compare(keyOfValue()(v), key(y)))
			{
				z = create_node(v); // 创建新节点，令新节点的值（value_field）为v
				left(y) = z; // 令父节点的左子树为z，我们成功的把新节点加入到树中了
				if (y == header) // y == header：插入点的父节点为header，说明根节点还没有被初始化，进入if就是要初始化根节点
				{
					root() = z; // z成了根节点
					rightmost() = z; // 令z为整棵树最右边的节点
				}
				else if (y == leftmost()) // 如果父节点是整颗树最左边的节点
				{
					leftmost() = z; // 我们把新节点作为整棵树最左边的节点
				}
			}
			else
			{
				z = create_node(v); // 创建新节点
				right(y) = z; // 插入节点到父节点的右边
				if (y == rightmost()) // 如果父节点是整颗树最右边的节点
				{
					rightmost() = z; // 我们把新节点作为整棵树最右边的节点
				}
			}
			parent(z) = y; // 令新节点的父节点为y
			left(z) = 0; // 新节点的左子树为null
			right(z) = 0; // 新节点的右子树为null

			__rb_tree_rebalance(z, header->parent); // header是哨兵，一旦建立就不改变，header->parent执行树的根节点
			++node_count; // 增加节点数
			return iterator(z);
		}

		/*
			重新平衡红黑树（改变颜色和旋转树形）
			x是新增节点
			root为根节点
		*/
		inline void __rb_tree_rebalance(__rb_tree_node_base* x, __rb_tree_node_base*& root)
		{
			x->color = __rb_tree_red; // 新插入的节点是红色的
			// 如果新增节点（x）不为根节点，且新增节点的父节点为红色，那麻烦就大了，要进入while一顿折腾
			while (x != root && x->parent->color == __rb_tree_red)
			{
				if (x->parent == x->parent->parent->left) // 如果父节点是祖父节点的左子节点
				{
					__rb_tree_node_base* y = x->parent->parent->right; // 令y为伯父节点
					if (y && y->color == __rb_tree_red) // 如果伯父节点存在且为红
					{
						x->parent->color = __rb_tree_black;
						y->color = __rb_tree_black;
						x->parent->parent->color = __rb_tree_red;
						x = x->parent->parent;
					}
					else // 如果伯父节点不存在，或者伯父节点为黑
					{
						if (x == x->parent->right) // 如果新增节点为父节点的右子节点（为父节点的右子节点，这说明插入节点的方式是内插）
						{
							x = x->parent; // 父节点为旋转支点
							// 整理一下从while开始的条件判断分支，我们可以得出做左旋转的条件：
							// 1.新增节点不是根节点
							// 2.新增节点的父节点是红色
							// 3.父节点是祖父节点的左子节点
							// 4.伯父节点不存在，或者伯父节点为黑
							// 5.新增节点为父节点的右子节点
							__rb_tree_rotate_left(x, root); // 做左旋转
						}
						x->parent->color = __rb_tree_black; // 修改颜色
						x->parent->parent->color = __rb_tree_red; // 修改颜色
						__rb_tree_rotate_right(x->parent->parent, root); // 左旋完了接着右旋
					}
				}
				else // 如果父节点是祖父节点的右子节点
				{
					__rb_tree_node_base* y = x->parent->parent->left; // 令y为伯父节点
					if (y && y->color == __rb_tree_red) // 如果伯父节点存在且为红
					{
						x->parent->color = __rb_tree_black;
						y->color = __rb_tree_black;
						x->parent->parent->color = __rb_tree_red;
						x = x->parent->parent;
					}
					else // 如果伯父节点不存在，或者伯父节点为黑
					{
						// 如果新增节点为父节点的左子节点（为父节点的左子节点，这说明插入节点的方式是内插）
						if (x == x->parent->left)
						{
							x = x->parent; // 父节点为旋转支点
							// 整理一下从while开始的条件判断分支，我们可以得出做右旋转的条件：
							// 1.新增节点不是根节点
							// 2.新增节点的父节点是红色
							// 3.父节点是祖父节点的右子节点
							// 4.伯父节点不存在，或者伯父节点为黑
							// 5.新增节点为父节点的左子节点
							__rb_tree_rotate_right(x, root); // 做右旋转
						}
						x->parent->color = __rb_tree_black; // 修改颜色
						x->parent->parent->color = __rb_tree_red; // 修改颜色
						__rb_tree_rotate_left(x->parent->parent, root); // 右旋完了接着左旋
					}
				}
			}
			root->color = __rb_tree_black; // 树的根节点永远是黑
		}

		/*
			左旋转
			新节点比为红节点，如果插入节点的父节点也为共色，就违反了红黑树规则，此时必须做旋转
			x：左旋转的支点
			root：红黑树的根
		*/
		inline void __rb_tree_rotate_left(__rb_tree_node_base* x, __rb_tree_node_base*& root)
		{
			__rb_tree_node_base* y = x->right; // y为旋转点的右子节点
			x->right = y->left; // 旋转点为父，旋转点的右子节点为子，完成父子对换
			if (y->left != 0)
			{
				y->left->parent = x;
			}
			y->parent = x->parent;

			if (x == root)
			{
				root = y; // 令y为根节点
			}
			else if (x == x->parent->left)
			{
				x->parent->left = y; // 令旋转点的父节点的左子节点为y
			}
			else
			{
				x->parent->right = y; // 令旋转点的父节点的右子节点为y
			}
			y->left = x; // 右子节点的左子树为x
			x->parent = y; // 右子节点为旋转点的父节点
		}

		/*
			右旋转
			新节点比为红节点，如果插入节点的父节点也为共色，就违反了红黑树规则，此时必须做旋转
			x：右旋转的支点
			root：红黑树的根
		*/
		inline void __rb_tree_rotate_right(__rb_tree_node_base* x, __rb_tree_node_base*& root)
		{
			__rb_tree_node_base* y = x->left; // 令y为旋转点的左子节点
			x->left = y->right; // 令y的右子节点为旋转点的左子节点
			if (y->right != 0)
			{
				y->right->parent = x; // 设定父节点
			}
			y->parent = x->parent;

			// 令y完全顶替x的地位（必须将对其父节点的关系完全接收过来）
			if (x == root)
			{
				root = y; // x为根节点
			}
			else if (x == x->parent->right)
			{
				x->parent->right = y; // x为其父节点的右子节点
			}
			else
			{
				x->parent->left = y; // x为其父节点的左子节点
			}
			y->right = x;
			x->parent = y;
		}

		#pragma endregion

	};
}

#endif