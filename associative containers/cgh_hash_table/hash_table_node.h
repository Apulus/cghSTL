/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ����:cgh_hash_table�Ľڵ�
******************************************************************/

#ifndef _CGH_HASH_TABLE_NODE_
#define _CGH_HASH_TABLE_NODE_

namespace CGH{
	template<class value>
	struct hash_table_node{
		hash_table_node* next; // ָ����һ���ڵ�
		value val; // �ڵ��ֵ��
	};
}

#endif