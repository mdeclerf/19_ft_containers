#ifndef ITERATOR_VECTOR_HPP
#define ITERATOR_VECTOR_HPP

#include <iostream>

namespace ft
{

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Prototypes~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	template<typename T>
		class iterator;

	template<typename T>
		class reverse_iterator;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ITERATOR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	template<typename T>
	class iterator
	{
		public:

			//-------------------aliases/struct iterator_traits<T*>-------------------------
			typedef std::random_access_iterator_tag			iterator_category;
			typedef T										value_type;
			typedef T* 										pointer;
			typedef T& 										reference;
			typedef int										difference_type;
			typedef size_t									size_type;
			typedef iterator<T>								iterator_type;

			//-------------------canon-------------------------
			iterator() {}

			iterator(pointer p) { this->_ptr = p; }

			template <class Iter>
			iterator (const iterator<Iter>& it)
			{
				this->_ptr = it.get_ptr();
			}

			template <class Iter>
			iterator (const reverse_iterator<Iter>& it)
			{
				this->_ptr = it.get_ptr();
			}

			~iterator() {}
			
			iterator &operator=(const iterator &rhs)
			{
				this->_ptr = rhs.get_ptr();
				return (*this);
			}
			//-------------------member ft------------------------
			iterator& operator++() { ++this->_ptr; return (*this);}
			iterator operator++(int) { return this->_ptr++;}
			iterator& operator--() { --this->_ptr; return (*this);}
			iterator operator--(int) { return this->_ptr--;}
			iterator& operator+=(size_type s) { this->_ptr += s; return (*this);}
			iterator& operator-=(size_type s) { this->_ptr -= s; return (*this);}

			pointer operator->() { return this->_ptr;}
			reference operator*() { return *this->_ptr;}
			reference operator[](size_type i) const { pointer tmp = this->_ptr + i; return *tmp;}

			iterator operator-(difference_type s) const { pointer tmp = this->_ptr - s; return (tmp);}
			iterator operator+(difference_type s) const { pointer tmp = this->_ptr + s; return (tmp);}

			difference_type operator-(iterator rhs) const { return (this->_ptr - rhs._ptr);}

			pointer get_ptr() const {return this->_ptr;}
			//-------------------non member overlaod ft------------------------
			template <class A, class B>
			friend bool operator== (const iterator<A>& lhs,
							const iterator<B>& rhs);
			template <class A, class B>
			friend bool operator!= (const iterator<A>& lhs,
							const iterator<B>& rhs);
			template <class A, class B>
			friend bool operator<  (const iterator<A>& lhs,
							const iterator<B>& rhs);
			template <class A, class B>
			friend bool operator<= (const iterator<A>& lhs,
							const iterator<B>& rhs);
			template <class A, class B>
			friend bool operator>  (const iterator<A>& lhs,
							const iterator<B>& rhs);
			template <class A, class B>
			friend bool operator>= (const iterator<A>& lhs,
							const iterator<B>& rhs);

			template <class A>
			friend iterator<A> operator+ ( typename iterator<A>::difference_type n, const iterator<A>& rev_it);

			template <class A>
			friend typename iterator<A>::difference_type operator- (const iterator<A>& lhs,
			const iterator<A>& rhs);

		private:
			pointer _ptr;
	};



//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~REVERSE ITERATOR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	template<typename T>
	class reverse_iterator
	{
		public:

			//-------------------aliases/struct iterator_traits<T*>-------------------------
			typedef std::random_access_iterator_tag			iterator_category;
			typedef T										value_type;
			typedef T*										pointer;
			typedef T&									 	reference;
			typedef int										difference_type;
			typedef size_t									size_type;
			typedef iterator<T>								iterator_type;

			//-------------------canon-------------------------
			reverse_iterator() {}

			reverse_iterator(pointer p) {this->_ptr = p;}

			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter>& rev_it)
			{
				this->_ptr = rev_it.get_ptr();
			}

			template <class Iter>
			reverse_iterator (const iterator<Iter>& it)
			{
				this->_ptr = it.get_ptr();
				--this->_ptr;
			}

			~reverse_iterator() {}

			reverse_iterator &operator=(const reverse_iterator &rhs)
			{
				this->_ptr = rhs._ptr;
				return (*this);
			}

			//-------------------member ft------------------------
			iterator_type base() const { reverse_iterator<T> tmp(*this); tmp--; return tmp;}
		
			reverse_iterator& operator++() { --this->_ptr; return (*this);}
			reverse_iterator operator++(int) { return this->_ptr--;}
			reverse_iterator& operator--() { ++this->_ptr; return (*this);}
			reverse_iterator operator--(int) { return this->_ptr++;}
			reverse_iterator& operator+=(size_type s) { this->_ptr -= s; return (*this);}
			reverse_iterator& operator-=(size_type s) { this->_ptr += s; return (*this);}
			
			reference operator*() { return *this->_ptr;}
			pointer operator->() { return this->_ptr;}
			reference operator[](size_type i) const { pointer tmp = this->_ptr - i; return *tmp;}

			reverse_iterator operator-(difference_type s) const { pointer tmp = this->_ptr + s; return (tmp);}
			reverse_iterator operator+(difference_type s) const { pointer tmp = this->_ptr - s; return (tmp);}
			
			difference_type operator-(reverse_iterator rhs) const { return (rhs._ptr - this->_ptr);}

			pointer get_ptr() const {return this->_ptr;}

			//-------------------overloads------------------------
			template <class A, class B>
			friend bool operator== (const reverse_iterator<A>& lhs,
							const reverse_iterator<B>& rhs);
			template <class A, class B>
			friend bool operator!= (const reverse_iterator<A>& lhs,
							const reverse_iterator<B>& rhs);
			template <class A, class B>
			friend bool operator<  (const reverse_iterator<A>& lhs,
							const reverse_iterator<B>& rhs);
			template <class A, class B>
			friend bool operator<= (const reverse_iterator<A>& lhs,
							const reverse_iterator<B>& rhs);
			template <class A, class B>
			friend bool operator>  (const reverse_iterator<A>& lhs,
							const reverse_iterator<B>& rhs);
			template <class A, class B>
			friend bool operator>= (const reverse_iterator<A>& lhs,
							const reverse_iterator<B>& rhs);

			template <class A>
			friend reverse_iterator<A> operator+ ( typename reverse_iterator<A>::difference_type n, const reverse_iterator<A>& it);

			template <class A>
			friend typename reverse_iterator<A>::difference_type operator- (const reverse_iterator<A>& lhs,
			const reverse_iterator<A>& rhs);

		private:
			pointer 	_ptr;
	};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Non member overload ft~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//-------------------iterator------------------------
	template <class A, class B>
	bool operator== (const iterator<A>& lhs,
					const iterator<B>& rhs) { return lhs._ptr == rhs._ptr;}
	template <class A, class B>
	bool operator!= (const iterator<A>& lhs,
					const iterator<B>& rhs) { return lhs._ptr != rhs._ptr;}
	template <class A, class B>
	bool operator<  (const iterator<A>& lhs,
					const iterator<B>& rhs) { return lhs._ptr < rhs._ptr;}
	template <class A, class B>
	bool operator<= (const iterator<A>& lhs,
					const iterator<B>& rhs) { return lhs._ptr <= rhs._ptr;}
	template <class A, class B>
	bool operator>  (const iterator<A>& lhs,
					const iterator<B>& rhs) { return lhs._ptr > rhs._ptr;}
	template <class A, class B>
	bool operator>= (const iterator<A>& lhs,
					const iterator<B>& rhs) { return lhs._ptr >= rhs._ptr;}
	
	template <class A>
	iterator<A> operator+ ( typename iterator<A>::difference_type n, const iterator<A>& it)
	{
		iterator<A> ret = it+n;
		return ret;
	}

	template <class A>
	typename iterator<A>::difference_type operator- (const iterator<A>& lhs,
	const iterator<A>& rhs)
	{
		return lhs.get_ptr()-rhs.get_ptr();
	}

//-------------------reverse iterator------------------------
	template <class A, class B>
	bool operator== (const reverse_iterator<A>& lhs,
					const reverse_iterator<B>& rhs) { return lhs._ptr == rhs._ptr;}
	template <class A, class B>
	bool operator!= (const reverse_iterator<A>& lhs,
					const reverse_iterator<B>& rhs) { return lhs._ptr != rhs._ptr;}
	template <class A, class B>
	bool operator<  (const reverse_iterator<A>& lhs,
					const reverse_iterator<B>& rhs) { return lhs._ptr > rhs._ptr;}
	template <class A, class B>
	bool operator<= (const reverse_iterator<A>& lhs,
					const reverse_iterator<B>& rhs) { return lhs._ptr >= rhs._ptr;}
	template <class A, class B>
	bool operator>  (const reverse_iterator<A>& lhs,
					const reverse_iterator<B>& rhs) { return lhs._ptr < rhs._ptr;}
	template <class A, class B>
	bool operator>= (const reverse_iterator<A>& lhs,
					const reverse_iterator<B>& rhs) { return lhs._ptr <= rhs._ptr;}
	
	template <class A>
	reverse_iterator<A> operator+ ( typename reverse_iterator<A>::difference_type n, const reverse_iterator<A>& rev_it)
	{
		reverse_iterator<A> ret = rev_it+n;
		return ret;
	}

	template <class A>
	typename reverse_iterator<A>::difference_type operator- (const reverse_iterator<A>& lhs,
	const reverse_iterator<A>& rhs)
	{
		return lhs.get_ptr()-rhs.get_ptr();
	}
}

#endif
