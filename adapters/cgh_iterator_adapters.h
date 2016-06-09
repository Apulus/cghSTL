/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  ���ܣ��������������ʵ��
******************************************************************/

#ifndef _CGH_ITERATOR_ADAPTERS_H_
#define _CGH_ITERATOR_ADAPTERS_H_

namespace CGH{

	#pragma region cgh_back_insert_iterator

	template<class container>
	class cgh_back_insert_iterator{
	protected:
		container* ctr; // ������ĵײ�����
	public:
		typedef output_iterator_tag		iterator_category;
		typedef void					value_type;
		typedef void					difference_type;
		typedef void					pointer;
		typedef void					referenc;

		/* ���캯�� */
		explicit cgh_back_insert_iterator(container& x) : ctr(&x) { }

		cgh_back_insert_iterator<container>&
		operator=(const typename container::value_type& value)
		{
			// ���������Ĺؼ�
			// copy ������ *result = *first��result �����;�������� cgh_back_insert_iterator
			// cgh_back_insert_iterator ��д�� operator=
			// copy::*result = *first ----> ctr->push_back(value);
			ctr->push_back(value);
			return *this;
		}

		cgh_back_insert_iterator<container>& operator*() { return *this; }

		cgh_back_insert_iterator<container>& operator++() { return *this; }

		cgh_back_insert_iterator<container>& operator++(int) { return *this; }
	};

	/* ������������������ʹ�� cgh_back_insert_iterator */
	template<class container>
	inline cgh_back_insert_iterator<container> cgh_back_inserter(container& x)
	{
		return cgh_back_insert_iterator<container>(x);
	}

	#pragma endregion

	#pragma region cgh_front_insert_iterator

	template<class container>
	class cgh_front_insert_iterator{
	protected:
		container* ctr; // ������ĵײ�����
	public:
		typedef output_iterator_tag		iterator_category;
		typedef void					value_type;
		typedef void					difference_type;
		typedef void					pointer;
		typedef void					referenc;

		/* ���캯�� */
		explicit cgh_front_insert_iterator(container& x) : ctr(&x) { }

		cgh_front_insert_iterator<container>&
			operator=(const typename container::value_type& value)
		{
			// ���������Ĺؼ�
			// copy ������ *result = *first��result �����;�������� cgh_front_insert_iterator
			// cgh_front_insert_iterator ��д�� operator=
			// copy::*result = *first ----> ctr->push_front(value);
			ctr->push_front(value);
			return *this;
		}

		cgh_front_insert_iterator<container>& operator*() { return *this; }

		cgh_front_insert_iterator<container>& operator++() { return *this; }

		cgh_front_insert_iterator<container>& operator++(int) { return *this; }
	};

	/* ������������������ʹ�� cgh_front_insert_iterator */
	template<class container>
	inline cgh_front_insert_iterator<container> cgh_front_inserter(container& x)
	{
		return cgh_front_insert_iterator<container>(x);
	}

	#pragma endregion

	#pragma region cgh_insert_iterator

	template<class container>
	class cgh_insert_iterator{
	protected:
		container* ctr; // ������ĵײ�����
		typename container::iterator	iter; // �ײ������ĵ�����
	public:
		typedef output_iterator_tag		iterator_category;
		typedef void					value_type;
		typedef void					difference_type;
		typedef void					pointer;
		typedef void					referenc;

		/* ���캯�� */
		explicit cgh_insert_iterator(container& x, typename container::iterator i) : ctr(&x), iter(i) { }

		cgh_insert_iterator<container>&
			operator=(const typename container::value_type& value)
		{
			// ���������Ĺؼ�
			// copy ������ *result = *first��result �����;�������� cgh_insert_iterator
			// cgh_insert_iterator ��д�� operator=
			// copy::*result = *first ----> ctr->insert(iter, value);
			iter = ctr->insert(iter, value);
			++iter;
			return *this;
		}

		cgh_insert_iterator<container>& operator*() { return *this; }

		cgh_insert_iterator<container>& operator++() { return *this; }

		cgh_insert_iterator<container>& operator++(int) { return *this; }
	};

	/* ������������������ʹ�� cgh_insert_iterator */
	template<class container, class iterator>
	inline cgh_insert_iterator<container> cgh_inserter(container& x, iterator i)
	{
		typedef typename container::iterator	iter;
		return cgh_insert_iterator<container>(x, iter(i));
	}

	#pragma endregion

	#pragma region cgh_reverse_iterator

	template<class iterator>
	class cgh_reverse_iterator{
	protected:
		iterator current; // ���������
	public:
		typedef typename std::iterator_traits<iterator>::iterator_category	iterator_category;
		typedef typename std::iterator_traits<iterator>::value_type			value_type;
		typedef typename std::iterator_traits<iterator>::difference_type	difference_type;
		typedef typename std::iterator_traits<iterator>::pointer			pointer;
		typedef typename std::iterator_traits<iterator>::reference			reference;

		typedef iterator						iterator_type; // �������������
		typedef cgh_reverse_iterator<iterator>	self; // �����������

	public:

		#pragma region ���캯��

		cgh_reverse_iterator(){}
		explicit cgh_reverse_iterator(iterator_type x) : current(x){}
		cgh_reverse_iterator(const self& x) : current(x.current){}

		#pragma endregion

		iterator_type base() const
		{
			return current;
		}
		/* ָ�������� */
		reference operator*()const
		{
			iterator tmp = current;
			// ���������Ĺؼ�
			// �����������ȡֵ�����ǽ�����Ӧ�����������������һ��Ȼ��ȡֵ
			return *--tmp;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		self& operator++()
		{
			// current ��¼�������������
			// ����������� ++ ��������������� --
			--current;
			return *this;
		}

		self operator++(int)
		{
			self tmp = *this;
			--current;
			return tmp;
		}

		self& operator--()
		{
			// current ��¼�������������
			// ����������� -- ��������������� ++
			++current;
			return *this;
		}

		self operator--(int)
		{
			self tmp = *this;
			++current;
			return tmp;
		}

		self operator+(difference_type n) const
		{
			return self(current - n);
		}

		self& operator+=(difference_type n)
		{
			current -= n;
			return *this;
		}

		self operator-(difference_type n) const
		{
			return self(current + n);
		}

		self& operator-=(difference_type n)
		{
			current += n;
			return *this;
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n);
		}
	};

	#pragma endregion

};

#endif