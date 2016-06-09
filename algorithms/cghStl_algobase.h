/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  �ļ����ݣ�equal��fill��fill_n��iter_sawp��max��min��
			 lexicographical_compare��mismatch��copy �㷨��ʵ��
******************************************************************/


#ifndef _CGH_STL_ALGOBASE_
#define _CGH_STL_ALGOBASE_

#include "cghUtil.h"
#include "cghSTL_type_traits.h"
#include "cghSTL_iterator.h"

namespace CGH{

	#pragma region equal

	/* ������������� [ first, last ] ��������ȣ�equal() ����true�����Եڶ������е�Ԫ�ض�����Ĳ��� */
	template<class InputIterator1, class InputIterator2>
	inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (*first1 != *first2)
			{
				return false ; // ���ͬһλ���ϵ�����Ԫ��ֵ����ȣ�����false
			}
		}
		// ����һ����������ʱ���ڶ�������һ��Ҫ�ȵ�һ�������Ҳ����ǵڶ������ж�����Ĳ��֣�
		// ����������ͬλ�õ�Ԫ��ȫ����ȣ�����true
		return true ;
	}

	/* 
		������������� [ first, last ] ��������ȣ�equal() ����true�����Եڶ������е�Ԫ�ض�����Ĳ��� 
		binaryPredicate���û��Զ���ıȽϺ���
	*/
	template<class InputIterator1, class InputIterator2, class binaryPredicate>
	inline bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, binaryPredicate binary_pred)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(binaryPredicate(*first1, *first2)))
			{
				return false ; // ���ͬһλ���ϵ�����Ԫ��ֵ����ȣ������û��Զ���Ĵ�С�ȽϺ�����binaryPredicate��������false
			}
		}
		// ����һ����������ʱ���ڶ�������һ��Ҫ�ȵ�һ�������Ҳ����ǵڶ������ж�����Ĳ��֣�
		// ����������ͬλ�õ�Ԫ��ȫ����ȣ�����true
		return true ;
	}

	#pragma endregion

	#pragma region fill

	/* �� [ first, last ) �ڵ�����Ԫ��ֵ����Ϊ value */
	template<class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		for (; first != last; ++first)
		{
			*first = value ;
		}
	}

	#pragma endregion

	#pragma region fill_n

	/* �� [ first, last ) �ڵ�ǰ n ��Ԫ��ֵ����Ϊ value �����ص�������ָ����������һ��Ԫ�ص���һλ�� */
	template<class OutputIterator, class size, class T>
	OutputIterator fill_n(OutputIterator first, size n, const T& value)
	{
		for (; n > 0; --n, ++first)
		{
			*first = value;
		}
		return first;
	}

	#pragma endregion

	#pragma region iter_sawp

	/* ��������������ForwardIterator����ָ�Ķ���Ե� */
	template<class ForwardIterator1, class ForwardIterator2>
	void iter_swap(ForwardIterator1 first, ForwardIterator2 last)
	{
		// iterator_traits��������ȡ������õ�����ָ���ֵ����
		std::iterator_traits<ForwardIterator1>::value_type tmp = *first;
		*first = *last;
		*last = tmp;
	}

	#pragma endregion

	#pragma region max  min

	/* �Ƚϴ�С */
	template<class T>
	inline const T& max(const T& a, const T& b)
	{
		return a > b ? a : b ;
	}

	/* compare���û��Զ���Ĵ�С�ȽϺ��� */
	template<class T, class compare>
	inline const T& max(const T& a, const T& b, compare comp)
	{
		return comp(a, b) ? a : b ;
	}

	/* �Ƚϴ�С */
	template<class T>
	inline const T& min(const T& a, const T& b)
	{
		return a < b ? a : b ;
	}

	/* compare���û��Զ���Ĵ�С�ȽϺ��� */
	template<class T, class compare>
	inline const T& min(const T& a, const T& b, compare comp)
	{
		return comp(a, b) ? b : a ;
	}

	#pragma endregion

	#pragma region lexicographical_compare

	/*
		�ԡ��ֵ����з�ʽ������������ [ first1, last1 ) �� [ first2, last2 )���бȽϣ���һ���������ֵ�����С�ڵڶ�������
		�Ƚϲ���������������ж�Ӧλ���ϵ�Ԫ�ؽ��У�ֱ��һ��������֣�
		1.������ͬһλ���ϵ�Ԫ�ز���ȣ�
		2.ͬʱ���� last1 �� last2����������ȣ���
		3.���� last1 ���� last2�������в���ȣ���
	*/
	/*
		�����е�һ�γ���ͬһλ����Ԫ�ز����ʱ��lexicographical_compare() �����ķ���ֵ��һ�¿��ܣ�
		1.�����һ�����е�Ԫ�رȽ�С������ true �����򷵻� false��
		2.������� last1 ����δ���� last2������ true��
		3.������� last2 ����δ���� last1������ false��
		4.���ͬʱ���� last1 �� last2��ע�⣬���е�������ǰ�պ󿪣�ͬʱ���� last ˵������Ԫ�ض�ƥ�䣩������false��
	*/
	template<class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{
		// �����κ�һ�����е���β�ˣ��ͽ�����������������һһ�ȶ���ӦԪ��
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (*first1 < *first2)
			{
				return true ; // ��һ����ֵС�ڵڶ�������Ӧֵ������ true
			}
			if (*first2 < *first1)
			{
				return false ; // ��һ����ֵ���ڵڶ�������Ӧֵ������ false
			}
			// ���������ͬһλ��Ԫ����ȣ����������ǰ������һ�ֱȽ�
		}
		// �����һ�����е���β�ˣ����ǵڶ�����������ʣ�࣬��ô��һ������С�ڵڶ�������
		return first1 == last1 && first2 != last2 ;
	}

	/* compare���û�ָ���Ĵ�С�ȽϷ��� */
	template<class InputIterator1, class InputIterator2, class compare>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, compare comp)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if ( comp( *first1, *first2 ) )
			{
				return true ;
			}
			if ( comp(*first2, *first1) )
			{
				return false ;
			}
		}
		return first1 == last1 && first2 != last2 ;
	}

	/* Ϊ����ǿЧ�ʣ�������ػ��棬ʹ��ԭ��ָ�� const unsigned char* */
	bool lexicographical_compare(const unsigned char* first1, const unsigned char* last1, const unsigned char* first2, const unsigned char* last2)
	{
		const size_t len1 = last1 - first1 ; // ��һ�����еĳ���
		const size_t len2 = last2 - first2 ; // �ڶ������еĳ���
		const int result = memcmp(first1, first2, CGH::min(len1, len2)); // ʹ��memcmp�Ƚϳ�����ͬ�Ĳ���
		return result != 0 ? result < 0 : len1 < len2 ; // ����������£��򳤶Ƚϳ�����Ϊ�Ƚϴ�
	}
	#pragma endregion

	#pragma region mismatch

	/* 
		�Ƚ��������У�ָ������֮���һ����ƥ��ĵ㣬����һ�Ե��������ֱ�ָ���������в�ƥ��ĵ�
		��������ж�ӦԪ�ض�ƥ�䣬���صı��������и��Ե� last ������
		����ڶ������бȵ�һ�����г������Զ�����Ĳ���
		Ĭ��������� equality �������Ƚ�Ԫ��
	*/
	template<class InputIterator1, class InputIterator2>
	cghPair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		while (first1 != last1 && *first1 == *first2)
		{
			++first1;
			++first2;
		}
		return cghPair<InputIterator1, InputIterator2>(first1, first2) ;
	}

	/* BinaryPredicator���û��Զ���Ƚϲ��� */
	template<class InputIterator1, class InputIterator2, class BinaryPredicator>
	cghPair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicator binary_pre)
	{
		while (first1 != last1 && binary_pre(*first1, *first2))
		{
			++first1;
			++first2;
		}
		return cghPair<InputIterator1, InputIterator2>(first1, first2) ;
	}

	#pragma endregion

}

namespace CGH{
	#pragma region copy

#pragma region ��һ�㣺copy �㷨���

	/* copy �㷨Ψһ�Ķ���ӿڣ���ȫ�����棩*/
	template<class InputIterator, class OutputIterator>
	inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result)
	{
		return copy_dispatch<InputIterator, OutputIterator>()(first, last, result);
	}

	#pragma region copy���ػ��棨specialization��

	/* copy �㷨���const char* �汾���ػ��� */
	inline char* copy(const char* first, const char* last, char* result)
	{
		// ���� memmove �ķ�ʽֱ�Ӹ������ݣ�cgh_memmove ����λ�� cghUtil.h �ļ�
		cgh_memmove(result, first, last - first) ;
		return result + (last - first) ;
	}

	/* copy �㷨���const wchar_t* �汾���ػ��� */
	inline wchar_t* copy(const wchar_t* first, const wchar_t* last, wchar_t* result)
	{
		// ���� memmove �ķ�ʽֱ�Ӹ������ݣ�cgh_memmove ����λ�� cghUtil.h �ļ�
		cgh_memmove(result, first, sizeof(wchar_t) * (last - first)) ;
		return result + (last - first) ;
	}
	#pragma endregion

#pragma endregion

#pragma region �ڶ��㣺copy_dispatch

	template<class InputIterator, class OutputIterator>
	struct copy_dispatch{
		OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result)
		{
			return _copy(first, last, result, CGH::iterator_category(first));
		}
	};

	#pragma region copy_dispatch ��ƫ�ػ��汾

	/*
		�ڲ���Ϊԭ��ָ�������£���һ��̽��ָ��ָ��Ķ����Ƿ���� trivial assignment operator
		assignment operator ��Ч�ʵ�Ӱ�첻С
		1.���ָ��ָ��Ķ������ non-trivial assignment operator�����Ʋ����ͱ���ͨ�� trivial assignment operator ����
		2.���ָ��ָ��Ķ������ trivial assignment operator��������ȫ����ͨ�������ڴ濽����memmove���У�
	*/
	template<class T>
	struct copy_dispatch<T*, T*>{
		T* operator()(T* first, T* last, T* result)
		{
			// ͨ��������ȡ����cghSTL_type_traits������ö��� assignment operator ����
			typedef typename cghSTL_type_traits<T>::has_trivial_assignment_operator	t;
			return _copy_t(first, last, result, t());
		}
	};

	/*
		�ڲ���Ϊԭ��ָ�������£���һ��̽��ָ��ָ��Ķ����Ƿ���� trivial assignment operator
		assignment operator ��Ч�ʵ�Ӱ�첻С
		1.���ָ��ָ��Ķ������ non-trivial assignment operator�����Ʋ����ͱ���ͨ�� trivial assignment operator ����
		2.���ָ��ָ��Ķ������ trivial assignment operator��������ȫ����ͨ�������ڴ濽����memmove���У�
	*/
	template<class T>
	struct copy_dispatch<const T*, T*>{
		T* operator()(T* first, T* last, T* result)
		{
			// ͨ��������ȡ����cghSTL_type_traits������ö��� assignment operator ����
			typedef typename cghSTL_type_traits<T>::has_trivial_assignment_operator	t;
			return _copy_t(first, last, result, t());
		}
	};

	#pragma endregion

#pragma endregion

#pragma region ������
	template<class InputIterator, class OutputIterator>
	inline OutputIterator _copy(InputIterator first, InputIterator last, OutputIterator result, CGH::input_iterator_tag)
	{
		// �Ե������Ƿ񵽴�ĩβ������ѭ���������ٶ���
		for (; first != last; ++result, ++first)
		{
			*result = *first ;
		}
		return result ;
	}

	template<class RandomAccessIterator, class OutputIterator>
	inline OutputIterator _copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, CGH::random_access_iterator_tag)
	{
		return _copy_d(first, last, result, distance_type(first)) ;
	}

	/* �������ӵ�� non-trivial assignment operator ��ôֱ�ӽ����ڴ濽�� */
	template<class T>
	inline T* _copy_t(const T* first, const T* last, T* result, true_type)
	{
		cgh_memmove(result, first, sizeof(T) * (last - first)) ;
		return result + (last - first) ;
	}

	/* �������ӵ�� trivial assignment operator ��ô����_copy_d�����Զ���� assignment operator���������󿽱� */
	template<class T>
	inline T* _copy_t(const T* first, const T* last, T* result, false_type)
	{
		return _copy_d(first, last, result, (ptrdiff_t*)0);
	}

	template<class RandomAccessIterator, class OutputIterator, class Distance>
	inline OutputIterator _copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, Distance*)
	{
		// �� n ����ѭ���������ٶȱ��õ���������ѭ����������Ч
		for (Distance n = last - first; n > 0; --n, ++result, ++first)
		{
			*result = *first ;
		}
		return result ;
	}
#pragma endregion

	#pragma endregion

#pragma region copy_backward

#pragma region ��һ�㣺copy_backward �㷨���

	/*
		�� [ first,last ) �ڵ�ÿһ��Ԫ�أ������еķ����Ƶ��� result - 1 Ϊ��㣬����ҲΪ���е�������]
		* ( result - 1 ) = * ( last - 1 ) ;
		* ( result - 2 ) = * ( last - 2 ) ;
		* ( result - 3 ) = * ( last - 3 ) ;
		...
	*/
	template <class InputIterator, class OutputIterator>
	inline OutputIterator copy_backward(InputIterator first, InputIterator last, OutputIterator result)
	{
		return copy_backward_dispatch<InputIterator, OutputIterator>()(first, last, result);
	}

#pragma endregion

#pragma region �ڶ��㣺copy_backward_dispatch

	template <class InputIterator, class OutputIterator>
	struct copy_backward_dispatch
	{
		OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result)
		{
			return __copy_backward(first, last, result);
		}
	};

	#pragma region copy_backward_dispatch ���ػ���
	template <class T>
	struct copy_backward_dispatch<T*, T*>
	{
		T* operator()(T* first, T* last, T* result)
		{
			typedef typename cghSTL_type_traits<T>::has_trivial_assignment_operator t;
			return __copy_backward_t(first, last, result, t());
		}
	};

	template <class T>
	struct copy_backward_dispatch<const T*, T*>
	{
		T* operator()(const T* first, const T* last, T* result)
		{
			typedef typename cghSTL_type_traits<T>::has_trivial_assignment_operator t;
			return __copy_backward_t(first, last, result, t());
		}
	};
	#pragma endregion

#pragma endregion

#pragma region ������

	template <class InputIterator, class OutputIterator>
	inline OutputIterator __copy_backward(OutputIterator first, InputIterator last, OutputIterator result)
	{
		while (first != last) *--result = *--last;
		return result;
	}

	template <class T>
	inline T* __copy_backward_t(const T* first, const T* last, T* result, true_type)
	{
		const ptrdiff_t N = last - first;
		memmove(result - N, first, sizeof(T) * N);
		return result - N;
	}

	template <class T>
	inline T* __copy_backward_t(const T* first, const T* last, T* result,
		false_type)
	{
		return __copy_backward(first, last, result);
	}

#pragma endregion

#pragma endregion
}

#endif