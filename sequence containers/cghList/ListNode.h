/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  功能:_cghList中元素的实现代码
******************************************************************/

#ifndef _CGH_LIST_NODE_
#define _CGH_LIST_NODE_

namespace CGH{
	// 定义双向链表节点类型
	template<typename T>
	struct __list_node
	{
		typedef void* void_pointer;
		void_pointer prev; // 指向前一个节点
		void_pointer next; // 指向后一个节点
		T data; // 节点的数据域
	};
}

#endif