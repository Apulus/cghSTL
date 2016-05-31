/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ����:cghVector������ʵ�ִ���
******************************************************************/

#ifndef _CGH_VECTOR_
#define _CGH_VECTOR_

#include "globalConstruct.h"
#include "cghAlloc.h"
#include <memory>

namespace CGH
{
	template<class T, class Alloc = cghAllocator<T>>
	class cghVector
	{
	public:
		typedef T				value_type;
		typedef value_type*		pointer;
		typedef value_type*		iterator;
		typedef value_type&		reference;
		typedef size_t			size_type;
		typedef ptrdiff_t		difference_type;

		//typedef __false_type	has_trivial_default_constructor;
		//typedef __false_type	has_trivial_copy_destructor;
		//typedef __false_type	has_trivial_assignment_operator;
		//typedef __false_type	has_trivial_destructor;
		//typedef __false_type	is_POD_type;

	protected:
		typedef simple_alloc<value_type, Alloc> data_allocator; // ����ռ�������
		iterator start;
		iterator finish;
		iterator end_of_storage;

		void insert_aux(iterator position, const T& value)
		{
			if (finish != end_of_storage)
			{
				construct(finish, *(finish - 1));
				++finish;
				T x_copy = value;
				std::copy_backward(position, finish - 2, finish - 1);
				*position = x_copy;
			}
			else
			{
				ptrdiff_t old_size = size();
				const size_type len = old_size != 0 ? 2 * old_size : 1;
				/*
					����ԭ�����ԭ��СΪ0��������1��Ԫ�ش�С
					���ԭ��С��Ϊ0��������ԭ��С������
				*/
				iterator new_start = data_allocator::allocate(len);
				iterator new_finish = new_start;
				try
				{
					// �� start �� position ����ڴ濽���� new_start ��,���� new_finish = new_start + ( position - start )
					new_finish = std::uninitialized_copy(start, position, new_start); 
					construct(new_finish, value); // �� new_finish ��������Ԫ��
					++new_finish;
					//new_finish = std::uninitialized_copy(position, finish, new_finish);
				}
				catch (std::exception ex)
				{
					// ���ִ��ʧ�ܾ�Ҫ�ع�
					destroy(new_start, new_finish);
					data_allocator::deallocate(new_start, len);
					throw;
				}
				destroy(begin(), end());
				deallocate();
				start = new_start;
				finish = new_finish;
				end_of_storage = new_start + len;
			}
		}

		#pragma region �ͷ��ڴ������Ԫ��
		void deallocate()
		{
			if (start)
			{
				data_allocator::deallocate(start);
			}
		}
		#pragma endregion

		#pragma region �����ڴ�͹���Ԫ��
		/*
		 *	fill_initialize��allocate_and_fill��cghVector�ĳ�ʼ����Ϊ��������
		 *	1.fill_initialize��ְ���Ƿ���һ���ڴ�
		 *	2.fill_initialize����allocate_and_fill���ڷ�����ڴ��е��ù��캯������cghVector��Ԫ��
		 */
		void fill_initialize(size_type n, const T& value)
		{
			start = allocate_and_fill(n, value);
			finish = start + n;
			end_of_storage = finish;
		}

		iterator allocate_and_fill(size_type n, const T& x)
		{
			iterator result = data_allocator::allocate(n);
			iterator cur = result;
			for (; n > 0; --n, ++cur)
			{
				construct(&*cur, x);
			}
			return result;
		}
		#pragma endregion
	public:
		#pragma region ��cghVector�Ķ�����
		iterator begin(){ return start; } // ����cghVectorͷԪ�صĵ�ַ
		iterator end(){ return finish; } // ����cghVectorβԪ�صĵ�ַ
		size_type size(){ return size_type(int(end() - begin())); } // cghVector�ĳ��� = βԪ�ص�ַ - ͷԪ�ص�ַ
		size_type capacity()const{ return size_type(end_of_storage - start); } // cghVector������ = ���������ַ - ͷԪ�ص�ַ
		bool empty()const { return begin() == end(); } // cghVector�Ƿ�Ϊ�գ�ͷԪ�ص�ַ �Ƿ���� βԪ�ص�ַ
		reference operator[](size_type n){ return *(begin() + n); } // ����ָ��λ�õ�Ԫ������
		reference front(){ return *begin(); } // ���ͷԪ��λְ
		reference back(){ return *(end() - 1); } // ���βԪ��λ��
		#pragma endregion

		#pragma region ���캯��
		cghVector() :start(0), finish(0), end_of_storage(0) { } // ��ʼ���յ�cghVector
		cghVector(size_type n, const T& value){ fill_initialize(n, value); } // ��ʼ������n��ֵΪvalue��cghVector
		cghVector(int n, const T& value){ fill_initialize(n, value); } // ͬ��
		cghVector(long n, const T& value){ fill_initialize(n, value); } // ͬ��
		explicit cghVector(size_type n){ fill_initialize(n, T()); } // ��ʼ��cghVector�ĳ���Ϊn
		#pragma endregion 

		#pragma region ��������
		~cghVector()
		{
			destroy(start, finish); // �ȵ���cghVector��Ԫ�ص���������
			deallocate(); // ���ͷ�cghVectorռ�õ��ڴ�
		}
		#pragma endregion

		#pragma region ��cghVector��д����
		/**
		*  ����βԪ��
		*/
		void pop_back() 
		{
			--finish;
			destroy(finish);
		}

		/**
		*  ��cghVectorĩβ����һ��Ԫ��
		*/
		void push_back(const T& x)
		{
			// �ж�cghVector�������Ƿ����ˣ����û������ֱ�������е��ڴ������Ϲ���Ԫ��
			if (finish != end_of_storage)
			{
				construct(finish, x);
				++finish;
			}
			else // ����������Ǿ�Ҫ���·����ڴ沢���¹��캯��
			{
				insert_aux(end(), x);
			}
		}

		/**
		*  ���[first, last)�����ڵ�Ԫ��
		*/
		iterator erase(iterator first, iterator last)
		{
			// ��last��finish���Ԫ�ؿ�����first��Ϊ��ʼ�����ڴ�ռ䣬����first + ( finish - last ) �ĵ�ַ
			iterator i = std::copy(last, finish, first);
			destroy(i, finish); // ����(first + ( finish - last ), finish]����ڴ�
			finish = finish - (last - first); // ��������finish
			return first;
		}

		/**
		*  ���ĳ��λ���ϵ�Ԫ��
		*/
		iterator erase(iterator position)
		{
			if (position + 1 != end())
			{
				copy(position + 1, finish, position);
			}
			--finish;
			destroy(finish);
			return position;
		}

		/* ��position��ʼ������n��Ԫ�أ�Ԫ�س�ֵΪx */
		void insert(iterator position, size_type n, const T& x)
		{
			if (n != 0) // ��n != 0 ʱ�Ų���
			{
				if (size_type(end_of_storage - finish) >= n) // ���ÿռ��������Ԫ�ظ���
				{
					T x_copy = x;
					const size_type elems_after = finish - position;
					iterator old_finish = finish;
					if (elems_after > n)
					{
						uninitialized_copy(finish - n, finish, finish);
						finish += n;
						copy_backward(position, old_finish - n, old_finish);
						fill(position, position + n, x_copy);
					}
					else
					{
						uninitialized_fill_n(finish, n - elems_after, x_copy);
						finish += n - elems_after;
						uninitialized_copy(position, old_finish, finish);
						finish += elems_after;
						fill(position, old_finish, x_copy);
					}
				}
				else
				{
					const size_type old_size = size();
					const size_type len = old_size + max(old_size, n);
					iterator new_start = data_allocator::allocate(len);
					iterator new_finish = new_start;
					new_finish = uninitialized_copy(start, position, new_start);
					new_finish = uninitialized_fill_n(new_finish, n, x);
					new_finish = uninitialized_copy(position, finish, new_finish);
					destroy(start, finish);
					deallocate();
					start = new_start;
					finish = new_finish;
					end_of_storage = new_start + len;
				}
			}
		}

		void swap(cghVector<T, Alloc>& __x) {
			std::swap(start, __x.start);
			std::swap(finish, __x.finish);
			std::swap(end_of_storage, __x.end_of_storage);
		}
		#pragma endregion

		#pragma region heap
		inline void make_heap(iterator first, iterator last)
		{
			if (last - first < 2)return;
			difference_type len = last - first;
			difference_type parent = len / 2;
			while (true)
			{
				_adjust_heap(first, parent, len, T(*(first + parent)));
				if (parent == 0)return;
				--parent;
			}
		}

		inline void push_heap(iterator first, iterator last)
		{
			difference_type holeIndex = last - first - 1;
			difference_type topIndex = 0;
			T value = T(*(last - 1));
			_push_heap(first, holeIndex, topIndex, value);
		}

		inline void pop_heap(iterator first, iterator last)
		{
			__pop_heap(first, last - 1, last - 1, T(*(last - 1)));
		}

		inline void sort_heap(iterator first, iterator last)
		{
			while (last - first > 1)
			{
				pop_heap(first, last -- );
			}
		}
	protected:
		void __pop_heap(iterator first, iterator last, iterator result, T value)
		{
			*result = *first;
			_adjust_heap(first, difference_type(0), difference_type(last - first), value);
		}

		void _adjust_heap(iterator first, difference_type holeIndex, difference_type len, T value)
		{
			difference_type topIndex = holeIndex;
			difference_type secondChild = 2 * holeIndex + 2;
			while (secondChild < len)
			{
				if (*(first + secondChild) < *(first + (secondChild - 1)))
				{
					--secondChild;
				}
				*(first + holeIndex) = *(first + secondChild);
				holeIndex = secondChild;
				secondChild = 2 * (secondChild + 1);
			}
			if (secondChild == len)
			{
				*(first + holeIndex) = *(first + (secondChild - 1));
				holeIndex = secondChild - 1;
			}
			_push_heap(first, holeIndex, topIndex, value);
		}

		void _push_heap(iterator first, difference_type holeIndex, difference_type topIndex, T value)
		{
			difference_type parent = (holeIndex - 1) / 2;
			while (holeIndex>topIndex && *(first + parent) < value)
			{
				*(first + holeIndex) = *(first + parent);
				holeIndex = parent;
				parent = (holeIndex - 1) / 2;
			}
			*(first + holeIndex) = value;
		}
		#pragma endregion
	};
}

#endif