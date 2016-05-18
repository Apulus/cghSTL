/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ����:_cghList��Ԫ�ص�ʵ�ִ���
******************************************************************/

#ifndef _CGH_LIST_NODE_
#define _CGH_LIST_NODE_

namespace CGH{
	// ����˫������ڵ�����
	template<typename T>
	struct __list_node
	{
		typedef void* void_pointer;
		void_pointer prev; // ָ��ǰһ���ڵ�
		void_pointer next; // ָ���һ���ڵ�
		T data; // �ڵ��������
	};
}

#endif