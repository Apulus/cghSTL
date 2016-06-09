/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  功能：迭代器配接器的实现
******************************************************************/

#ifndef _CGH_ITERATOR_ADAPTERS_H_
#define _CGH_ITERATOR_ADAPTERS_H_

namespace CGH{

	#pragma region cgh_back_insert_iterator

	template<class container>
	class cgh_back_insert_iterator{
	protected:
		container* ctr; // 配接器的底层容器
	public:
		typedef output_iterator_tag		iterator_category;
		typedef void					value_type;
		typedef void					difference_type;
		typedef void					pointer;
		typedef void					referenc;

		/* 构造函数 */
		explicit cgh_back_insert_iterator(container& x) : ctr(&x) { }

		cgh_back_insert_iterator<container>&
		operator=(const typename container::value_type& value)
		{
			// 这里是理解的关键
			// copy 函数的 *result = *first，result 的类型就是这里的 cgh_back_insert_iterator
			// cgh_back_insert_iterator 重写了 operator=
			// copy::*result = *first ----> ctr->push_back(value);
			ctr->push_back(value);
			return *this;
		}

		cgh_back_insert_iterator<container>& operator*() { return *this; }

		cgh_back_insert_iterator<container>& operator++() { return *this; }

		cgh_back_insert_iterator<container>& operator++(int) { return *this; }
	};

	/* 辅助函数，方便我们使用 cgh_back_insert_iterator */
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
		container* ctr; // 配接器的底层容器
	public:
		typedef output_iterator_tag		iterator_category;
		typedef void					value_type;
		typedef void					difference_type;
		typedef void					pointer;
		typedef void					referenc;

		/* 构造函数 */
		explicit cgh_front_insert_iterator(container& x) : ctr(&x) { }

		cgh_front_insert_iterator<container>&
			operator=(const typename container::value_type& value)
		{
			// 这里是理解的关键
			// copy 函数的 *result = *first，result 的类型就是这里的 cgh_front_insert_iterator
			// cgh_front_insert_iterator 重写了 operator=
			// copy::*result = *first ----> ctr->push_front(value);
			ctr->push_front(value);
			return *this;
		}

		cgh_front_insert_iterator<container>& operator*() { return *this; }

		cgh_front_insert_iterator<container>& operator++() { return *this; }

		cgh_front_insert_iterator<container>& operator++(int) { return *this; }
	};

	/* 辅助函数，方便我们使用 cgh_front_insert_iterator */
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
		container* ctr; // 配接器的底层容器
		typename container::iterator	iter; // 底层容器的迭代器
	public:
		typedef output_iterator_tag		iterator_category;
		typedef void					value_type;
		typedef void					difference_type;
		typedef void					pointer;
		typedef void					referenc;

		/* 构造函数 */
		explicit cgh_insert_iterator(container& x, typename container::iterator i) : ctr(&x), iter(i) { }

		cgh_insert_iterator<container>&
			operator=(const typename container::value_type& value)
		{
			// 这里是理解的关键
			// copy 函数的 *result = *first，result 的类型就是这里的 cgh_insert_iterator
			// cgh_insert_iterator 重写了 operator=
			// copy::*result = *first ----> ctr->insert(iter, value);
			iter = ctr->insert(iter, value);
			++iter;
			return *this;
		}

		cgh_insert_iterator<container>& operator*() { return *this; }

		cgh_insert_iterator<container>& operator++() { return *this; }

		cgh_insert_iterator<container>& operator++(int) { return *this; }
	};

	/* 辅助函数，方便我们使用 cgh_insert_iterator */
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
		iterator current; // 正向迭代器
	public:
		typedef typename std::iterator_traits<iterator>::iterator_category	iterator_category;
		typedef typename std::iterator_traits<iterator>::value_type			value_type;
		typedef typename std::iterator_traits<iterator>::difference_type	difference_type;
		typedef typename std::iterator_traits<iterator>::pointer			pointer;
		typedef typename std::iterator_traits<iterator>::reference			reference;

		typedef iterator						iterator_type; // 代表正向迭代器
		typedef cgh_reverse_iterator<iterator>	self; // 代表反向迭代器

	public:

		#pragma region 构造函数

		cgh_reverse_iterator(){}
		explicit cgh_reverse_iterator(iterator_type x) : current(x){}
		cgh_reverse_iterator(const self& x) : current(x.current){}

		#pragma endregion

		iterator_type base() const
		{
			return current;
		}
		/* 指针解除引用 */
		reference operator*()const
		{
			iterator tmp = current;
			// 这里是理解的关键
			// 对逆向迭代器取值，就是将“对应的正向迭代器”后退一格，然后取值
			return *--tmp;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		self& operator++()
		{
			// current 记录的是正向迭代器
			// 逆向迭代器的 ++ 就是正向迭代器的 --
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
			// current 记录的是正向迭代器
			// 逆向迭代器的 -- 就是正向迭代器的 ++
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