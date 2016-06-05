/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ����:cghSTL�Ĺ�����
******************************************************************/

#ifndef _CGH_UTIL_
#define _CGH_UTIL_

namespace CGH{
	/* �Զ����pair */
	template<class T1,class T2>
	struct cghPair {
		typedef T1	first_type;
		typedef T2	second_type;

		T1 first;
		T2 second;

		cghPair() :first(T1()), second(T2()){}
		cghPair(const T1& a, const T2&b) :first(a), second(b){}
	};

	/* �������� */
	template <class T> 
	void swap(T& a, T& b)
	{
		T c(a); a = b; b = c;
	}

	/* ���ƺ��� */
	void * __cdecl cgh_memmove ( void * dst, const void * src, size_t count)
	{
		void * ret = dst;
		if (dst <= src || (char *)dst >= ((char *)src + count))
		{
			// ��dst��src����û���ص��������ʼ����ʼ��һ����
			while (count--)
			{
				*(char *)dst = *(char *)src;
				dst = (char *)dst + 1;
				src = (char *)src + 1;
			}
		}
		else
		{ // ��dst��src ���򽻲棬���β����ʼ����ʼλ�ÿ������������Ա������ݳ�ͻ
			dst = (char *)dst + count - 1;
			src = (char *)src + count - 1;
			while (count--)
			{
				*(char *)dst = *(char *)src;
				dst = (char *)dst - 1;
				src = (char *)src - 1;
			}
		}
		return(ret);
	}

	/* ���ƺ��� */
	void * __cdecl cgh_memcpy(void * dst, const void * src, size_t count)
	{
		void * ret = dst;
		while (count--)
		{ // ע�⣬ cgh_memcpy����û�д���dst��src�����Ƿ��ص�������
			*(char *)dst = *(char *)src;
			dst = (char *)dst + 1;
			src = (char *)src + 1;
		}
		return(ret);
	}
}
#endif