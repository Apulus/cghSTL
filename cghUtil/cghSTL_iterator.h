

#ifndef __SGI_STL_INTERNAL_ITERATOR_H  
#define __SGI_STL_INTERNAL_ITERATOR_H  

namespace CGH{


	////////////////////////////////////////////////////////////////////////////////  
	// STL����������  
	////////////////////////////////////////////////////////////////////////////////  
	// STL�������ֵ���������  
	// Input Iterator               read only  
	// Output Iterator              write only  
	// Forward Iterator             ����"д����"�㷨����ָ��������в���  
	// Bidirectional Iterator       �ṩ˫���������  
	// Random Access Iterator       ֧��ԭ��ָ����е�ȫ������  
	////////////////////////////////////////////////////////////////////////////////  
	// ���ʹ�����ϵ, ���������ڽ��ܸ������͵��㷨, ����Ч�ʿ��ܲ���  
	//  
	//              Input Iterator  
	//                    ��  
	//             Forward Iterator  
	//                    ��  
	//           Bidirectional Iterator  
	//                    ��  
	//           Random Access Iterator  
	////////////////////////////////////////////////////////////////////////////////  

	// ���ڱ�ǵ���������  
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag : public input_iterator_tag {};
	struct bidirectional_iterator_tag : public forward_iterator_tag {};
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

	template <class T, class Distance> struct input_iterator
	{
		typedef input_iterator_tag iterator_category;
		typedef T                  value_type;
		typedef Distance           difference_type;
		typedef T*                 pointer;
		typedef T&                 reference;
	};

	struct output_iterator
	{
		typedef output_iterator_tag iterator_category;
		typedef void                value_type;
		typedef void                difference_type;
		typedef void                pointer;
		typedef void                reference;
	};

	template <class T, class Distance> struct forward_iterator
	{
		typedef forward_iterator_tag iterator_category;
		typedef T                    value_type;
		typedef Distance             difference_type;
		typedef T*                   pointer;
		typedef T&                   reference;
	};

	template <class T, class Distance> struct bidirectional_iterator
	{
		typedef bidirectional_iterator_tag iterator_category;
		typedef T                          value_type;
		typedef Distance                   difference_type;
		typedef T*                         pointer;
		typedef T&                         reference;
	};

	template <class T, class Distance> struct random_access_iterator
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T                          value_type;
		typedef Distance                   difference_type;
		typedef T*                         pointer;
		typedef T&                         reference;
	};



 /* __STL_CLASS_PARTIAL_SPECIALIZATION */  

	// ��������֧��partial specialization of class templates(ģ����ƫ�ػ�)  
	// ��Ҫ�����е��������Ͷ��ṩ����  

	template <class T, class Distance>
	inline input_iterator_tag
		iterator_category(const input_iterator<T, Distance>&)
	{
		return input_iterator_tag();
	}

	inline output_iterator_tag iterator_category(const output_iterator&)
	{
		return output_iterator_tag();
	}

	template <class T, class Distance>
	inline forward_iterator_tag
		iterator_category(const forward_iterator<T, Distance>&)
	{
		return forward_iterator_tag();
	}

	template <class T, class Distance>
	inline bidirectional_iterator_tag
		iterator_category(const bidirectional_iterator<T, Distance>&)
	{
		return bidirectional_iterator_tag();
	}

	template <class T, class Distance>
	inline random_access_iterator_tag
		iterator_category(const random_access_iterator<T, Distance>&)
	{
		return random_access_iterator_tag();
	}

	template <class T>
	inline random_access_iterator_tag iterator_category(const T*)
	{
		return random_access_iterator_tag();
	}

	template <class T, class Distance>
	inline T* value_type(const input_iterator<T, Distance>&)
	{
		return (T*)(0);
	}

	template <class T, class Distance>
	inline T* value_type(const forward_iterator<T, Distance>&)
	{
		return (T*)(0);
	}

	template <class T, class Distance>
	inline T* value_type(const bidirectional_iterator<T, Distance>&)
	{
		return (T*)(0);
	}

	template <class T, class Distance>
	inline T* value_type(const random_access_iterator<T, Distance>&)
	{
		return (T*)(0);
	}

	template <class T>
	inline T* value_type(const T*) { return (T*)(0); }

	template <class T, class Distance>
	inline Distance* distance_type(const input_iterator<T, Distance>&)
	{
		return (Distance*)(0);
	}

	template <class T, class Distance>
	inline Distance* distance_type(const forward_iterator<T, Distance>&)
	{
		return (Distance*)(0);
	}

	template <class T, class Distance>
	inline Distance*
		distance_type(const bidirectional_iterator<T, Distance>&)
	{
		return (Distance*)(0);
	}

	template <class T, class Distance>
	inline Distance*
		distance_type(const random_access_iterator<T, Distance>&)
	{
		return (Distance*)(0);
	}

	template <class T>
	inline ptrdiff_t* distance_type(const T*) { return (ptrdiff_t*)(0); }




	////////////////////////////////////////////////////////////////////////////////  
	// template <class InputIterator, class Distance>  
	// inline void distance(InputIterator first, InputIterator last, Distance& n)  
	////////////////////////////////////////////////////////////////////////////////  
	//                                distance  
	//                                   |  
	//                                   |---------------- �жϵ���������  
	//                 Input Iterator    ��   Random Access Iterator  
	//               -------------------------------------------  
	//               |                                         |  
	//               |                                         |  
	//               ��                                         |  
	// __distance(..., input_iterator_tag)                     |  
	// while (first != last) { ++first; ++n; }                 |  
	//                                                         ��  
	//                                __distance(..., random_access_iterator_tag)  
	//                                n += last - first;  
	////////////////////////////////////////////////////////////////////////////////  

	template <class InputIterator, class Distance>
	inline void __distance(InputIterator first, InputIterator last, Distance& n,
		input_iterator_tag)
	{
		while (first != last) { ++first; ++n; }
	}

	template <class RandomAccessIterator, class Distance>
	inline void __distance(RandomAccessIterator first, RandomAccessIterator last,
		Distance& n, random_access_iterator_tag)
	{
		n += last - first;
	}

	template <class InputIterator, class Distance>
	inline void distance(InputIterator first, InputIterator last, Distance& n)
	{
		__distance(first, last, n, iterator_category(first));
	}

	////////////////////////////////////////////////////////////////////////////////  
	// advance()ʵ�ֲ���  
	////////////////////////////////////////////////////////////////////////////////  
	//                                advance  
	//                                   |  
	//                                   |---------------- �жϵ���������  
	//     Input Iterator                ��  
	//   ---------------------------------------------------------------------  
	//   |             Random Access Iterator |      Bidirectional Iterator  |  
	//   |                                    |                              |  
	//   ��                                    |                              |  
	// __advance(..., input_iterator_tag)     |                              |  
	// while (n--) ++i;                       |                              |  
	//                                        |                              |  
	//                                        ��                              |  
	//               __advance(..., random_access_iterator_tag)              |  
	//               i += n;                                                 |  
	//                                                                       |  
	//                                                                       ��  
	//                                   __advance(..., bidirectional_iterator_tag)  
	//                                   if (n >= 0)  
	//                                      while (n--) ++i;  
	//                                   else  
	//                                      while (n++) --i;  
	////////////////////////////////////////////////////////////////////////////////  

	template <class InputIterator, class Distance>
	inline void __advance(InputIterator& i, Distance n, input_iterator_tag)
	{
		while (n--) ++i;
	}

	template <class BidirectionalIterator, class Distance>
	inline void __advance(BidirectionalIterator& i, Distance n,
		bidirectional_iterator_tag)
	{
		if (n >= 0)
			while (n--) ++i;
		else
			while (n++) --i;
	}

	template <class RandomAccessIterator, class Distance>
	inline void __advance(RandomAccessIterator& i, Distance n,
		random_access_iterator_tag)
	{
		i += n;
	}

	template <class InputIterator, class Distance>
	inline void advance(InputIterator& i, Distance n)
	{
		__advance(i, n, iterator_category(i));
	}

	////////////////////////////////////////////////////////////////////////////////  
	// back_insert_iteratorʵ�ֲ���  
	////////////////////////////////////////////////////////////////////////////////  

	template <class Container>
	class back_insert_iterator
	{
	protected:
		Container* container;
	public:
		typedef output_iterator_tag iterator_category;
		typedef void                value_type;
		typedef void                difference_type;
		typedef void                pointer;
		typedef void                reference;

		explicit back_insert_iterator(Container& x) : container(&x) {}

		// ֻ���ṩ��push_back()��������������ʹ��back_insert_iterator  
		back_insert_iterator<Container>&
			operator=(const typename Container::value_type& value)
		{
			container->push_back(value);
			return *this;
		}

		back_insert_iterator<Container>& operator*() { return *this; }
		back_insert_iterator<Container>& operator++() { return *this; }
		back_insert_iterator<Container>& operator++(int) { return *this; }
	};

	template <class Container>
	inline back_insert_iterator<Container> back_inserter(Container& x)
	{
		return back_insert_iterator<Container>(x);
	}

	////////////////////////////////////////////////////////////////////////////////  
	// front_insert_iteratorʵ�ֲ���  
	////////////////////////////////////////////////////////////////////////////////  

	template <class Container>
	class front_insert_iterator
	{
	protected:
		Container* container;
	public:
		typedef output_iterator_tag iterator_category;
		typedef void                value_type;
		typedef void                difference_type;
		typedef void                pointer;
		typedef void                reference;

		explicit front_insert_iterator(Container& x) : container(&x) {}

		// ֻ���ṩ��push_front()��������������ʹ��front_insert_iterator  
		front_insert_iterator<Container>&
			operator=(const typename Container::value_type& value)
		{
			container->push_front(value);
			return *this;
		}
		front_insert_iterator<Container>& operator*() { return *this; }
		front_insert_iterator<Container>& operator++() { return *this; }
		front_insert_iterator<Container>& operator++(int) { return *this; }
	};

	template <class Container>
	inline output_iterator_tag
		iterator_category(const front_insert_iterator<Container>&)
	{
		return output_iterator_tag();
	}

	template <class Container>
	inline front_insert_iterator<Container> front_inserter(Container& x)
	{
		return front_insert_iterator<Container>(x);
	}

	////////////////////////////////////////////////////////////////////////////////  
	// insert_iteratorʵ�ֲ���  
	////////////////////////////////////////////////////////////////////////////////  

	template <class Container>
	class insert_iterator
	{
	protected:
		Container* container;
		typename Container::iterator iter;
	public:
		typedef output_iterator_tag iterator_category;
		typedef void                value_type;
		typedef void                difference_type;
		typedef void                pointer;
		typedef void                reference;

		insert_iterator(Container& x, typename Container::iterator i)
			: container(&x), iter(i) {}

		// ֻ���ṩ��insert��������������ʹ��insert_iterator  
		insert_iterator<Container>&
			operator=(const typename Container::value_type& value)
		{
			iter = container->insert(iter, value);
			++iter;
			return *this;
		}
		insert_iterator<Container>& operator*() { return *this; }
		insert_iterator<Container>& operator++() { return *this; }
		insert_iterator<Container>& operator++(int) { return *this; }
	};

	template <class Container>
	inline output_iterator_tag
		iterator_category(const insert_iterator<Container>&)
	{
		return output_iterator_tag();
	}

	template <class Container, class Iterator>
	inline insert_iterator<Container> inserter(Container& x, Iterator i)
	{
		typedef typename Container::iterator iter;
		return insert_iterator<Container>(x, iter(i));
	}

	////////////////////////////////////////////////////////////////////////////////  
	// reverse_bidirectional_iteratorʵ�ֲ���  
	////////////////////////////////////////////////////////////////////////////////  

	// reverse_bidirectional_iteratorʹ�õ���BidirectionalIterator  
	// ����Ҫ��operator *(), ++(), ++(int)���ṩ����  
	// ͬʱ��Ϊ�Ƿ��������, ��������������Ĳ���Ҫ���⴦��  
	template <class BidirectionalIterator, class T, class Reference = T&,
	class Distance = ptrdiff_t>
	class reverse_bidirectional_iterator
	{
		typedef reverse_bidirectional_iterator<BidirectionalIterator, T, Reference,
			Distance> self;
	protected:
		BidirectionalIterator current;
	public:
		typedef bidirectional_iterator_tag iterator_category;
		typedef T                          value_type;
		typedef Distance                   difference_type;
		typedef T*                         pointer;
		typedef Reference                  reference;

		reverse_bidirectional_iterator() {}
		explicit reverse_bidirectional_iterator(BidirectionalIterator x)
			: current(x) {}
		BidirectionalIterator base() const { return current; }
		Reference operator*() const {
			BidirectionalIterator tmp = current;
			return *--tmp;
		}
		pointer operator->() const { return &(operator*()); }
		self& operator++() {
			--current;
			return *this;
		}
		self operator++(int) {
			self tmp = *this;
			--current;
			return tmp;
		}
		self& operator--() {
			++current;
			return *this;
		}
		self operator--(int) {
			self tmp = *this;
			++current;
			return tmp;
		}
	};

	template <class BidirectionalIterator, class T, class Reference,
	class Distance>
		inline bidirectional_iterator_tag
		iterator_category(const reverse_bidirectional_iterator<BidirectionalIterator,
		T,
		Reference, Distance>&)
	{
		return bidirectional_iterator_tag();
	}

	template <class BidirectionalIterator, class T, class Reference,
	class Distance>
		inline T*
		value_type(const reverse_bidirectional_iterator<BidirectionalIterator, T,
		Reference, Distance>&)
	{
		return (T*)0;
	}

	template <class BidirectionalIterator, class T, class Reference,
	class Distance>
		inline Distance*
		distance_type(const reverse_bidirectional_iterator<BidirectionalIterator, T,
		Reference, Distance>&)
	{
		return (Distance*)0;
	}

	template <class BidirectionalIterator, class T, class Reference,
	class Distance>
		inline bool operator==(
		const reverse_bidirectional_iterator<BidirectionalIterator, T, Reference,
		Distance>& x,
		const reverse_bidirectional_iterator<BidirectionalIterator, T, Reference,
		Distance>& y)
	{
		return x.base() == y.base();
	}

	// �����֧��partial specialization of class templates(ģ����ƫ�ػ�)  
	// ��ʹ��HP STL��ʵ��  

	// This is the old version of reverse_iterator, as found in the original  
	//  HP STL.  It does not use partial specialization.  

	template <class RandomAccessIterator, class T, class Reference = T&,
	class Distance = ptrdiff_t> 
	class reverse_iterator
	{
		typedef reverse_iterator<RandomAccessIterator, T, Reference, Distance>
			self;
	protected:
		RandomAccessIterator current;
	public:
		typedef random_access_iterator_tag iterator_category;
		typedef T                          value_type;
		typedef Distance                   difference_type;
		typedef T*                         pointer;
		typedef Reference                  reference;

		reverse_iterator() {}
		explicit reverse_iterator(RandomAccessIterator x) : current(x) {}
		RandomAccessIterator base() const { return current; }
		Reference operator*() const { return *(current - 1); }
		pointer operator->() const { return &(operator*()); }
		self& operator++() {
			--current;
			return *this;
		}
		self operator++(int) {
			self tmp = *this;
			--current;
			return tmp;
		}
		self& operator--() {
			++current;
			return *this;
		}
		self operator--(int) {
			self tmp = *this;
			++current;
			return tmp;
		}
		self operator+(Distance n) const {
			return self(current - n);
		}
		self& operator+=(Distance n) {
			current -= n;
			return *this;
		}
		self operator-(Distance n) const {
			return self(current + n);
		}
		self& operator-=(Distance n) {
			current += n;
			return *this;
		}
		Reference operator[](Distance n) const { return *(*this + n); }
	};

	template <class RandomAccessIterator, class T, class Reference, class Distance>
	inline random_access_iterator_tag
		iterator_category(const reverse_iterator<RandomAccessIterator, T,
		Reference, Distance>&)
	{
		return random_access_iterator_tag();
	}

	template <class RandomAccessIterator, class T, class Reference, class Distance>
	inline T* value_type(const reverse_iterator<RandomAccessIterator, T,
		Reference, Distance>&)
	{
		return (T*)0;
	}

	template <class RandomAccessIterator, class T, class Reference, class Distance>
	inline Distance* distance_type(const reverse_iterator<RandomAccessIterator, T,
		Reference, Distance>&)
	{
		return (Distance*)0;
	}


	template <class RandomAccessIterator, class T, class Reference, class Distance>
	inline bool operator==(const reverse_iterator<RandomAccessIterator, T,
		Reference, Distance>& x,
		const reverse_iterator<RandomAccessIterator, T,
		Reference, Distance>& y)
	{
		return x.base() == y.base();
	}

	template <class RandomAccessIterator, class T, class Reference, class Distance>
	inline bool operator<(const reverse_iterator<RandomAccessIterator, T,
		Reference, Distance>& x,
		const reverse_iterator<RandomAccessIterator, T,
		Reference, Distance>& y)
	{
		return y.base() < x.base();
	}

	template <class RandomAccessIterator, class T, class Reference, class Distance>
	inline Distance operator-(const reverse_iterator<RandomAccessIterator, T,
		Reference, Distance>& x,
		const reverse_iterator<RandomAccessIterator, T,
		Reference, Distance>& y)
	{
		return y.base() - x.base();
	}

	template <class RandomAccessIter, class T, class Ref, class Dist>
	inline reverse_iterator<RandomAccessIter, T, Ref, Dist>
		operator+(Dist n, const reverse_iterator<RandomAccessIter, T, Ref, Dist>& x)
	{
		return reverse_iterator<RandomAccessIter, T, Ref, Dist>(x.base() - n);
	}


}

#endif 