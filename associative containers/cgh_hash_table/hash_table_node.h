/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  内容:cgh_hash_table的节点
******************************************************************/

#ifndef _CGH_HASH_TABLE_NODE_
#define _CGH_HASH_TABLE_NODE_

namespace CGH{
	template<class value>
	struct hash_table_node{
		hash_table_node* next; // 指向下一个节点
		value val; // 节点的值域
	};
}

#endif