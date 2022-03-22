#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <iostream>
#include "iterator_vector.hpp"
#include "utils.hpp"
#include <stdexcept>

namespace ft
{
	// Std::allocator class template : the default Allocator used by all standard library containers if no user-specified allocator is provided.
	// How to use std::allocator
	// ->construct: It is used to construct an object : void construct(pointer ptr, const Type& val); 
	// 			ptr : A pointer to the location where the object is to be constructed.
	// 			val : The value with which the object being constructed is to be initialized.)

	// ->destroy: It is used to destruct an object in allocated storage : void destroy(pointer ptr);
	// 			ptr : A pointer designating the address of the object to be destroyed.

	// ->allocate: Used for allocation of memory : pointer allocate(size_type count, const void* _Hint);
	// 			return value : A pointer to the allocated object or null if memory was not allocated.
	
	// ->deallocate: Used for deallocation of memory : void deallocate(pointer ptr, size_type count);
	// 			ptr : A pointer to the first object to be deallocated from storage.
	// 			count : The number of objects to be deallocated from storage.
	// https://docs.microsoft.com/en-us/cpp/standard-library/allocator-class?view=msvc-170


	template <typename T, typename Allocator = std::allocator<T> >
	class vector
	{
//----------------------------------------typedef----------------------------------------
		public:
			typedef T										value_type;
			typedef std::allocator<T>						allocator_type;
			typedef size_t									size_type;
			typedef int										difference_type;
			typedef T&										reference;
			typedef const T&								const_reference;
			typedef T*										pointer;
			typedef ft::iterator<T>							iterator;
			typedef ft::iterator<const T>					const_iterator;
			typedef ft::reverse_iterator<T>					reverse_iterator;
			typedef ft::reverse_iterator<const T>			const_reverse_iterator;

//----------------------------------------attributes----------------------------------------
		private:
			allocator_type		_alloc;
			pointer				_data;
			size_type			_size;
			size_type			_capacity;

//----------------------------------------canon----------------------------------------
		public:
			// (1) empty container constructor (default constructor)
			// Constructs an empty container, with no elements.
			vector(const allocator_type& alloc = allocator_type()) : _alloc(alloc), _data(NULL), _size(0), _capacity(0) {}

			// (2) fill constructor
			// Constructs a container with n elements. Each element is a copy of val.
			vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()):
			_alloc(alloc), _data(NULL), _size(n), _capacity(n)
			{
				this->_data = this->_alloc.allocate(this->_capacity);
				for(size_type i = 0; i < this->_size; ++i)
					this->_alloc.construct(&this->_data[i], val);
			}

			// (3) range constructor
			// Constructs a container with as many elements as the range [first,last), with each element constructed from its corresponding element
			// in that range, in the same order.

			//https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/enable-if
			// the enable if is used to prevent compilation conflicts with the fill constructor, it will be enabled only if the params are not integrals
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_Integral<InputIterator>::value >::type* dummy = 0 ):
			_alloc(alloc)
			{
				(void) dummy;
				size_type span = 0;
				for(InputIterator tmp = first; tmp != last; ++tmp)
					span++;
				this->_capacity = span;
				this->_size = span;
				this->_data = this->_alloc.allocate(this->_capacity);
				for(size_type index = 0; index < this->_size; ++index, ++first)
					this->_alloc.construct(&this->_data[index], *first);
			}

			// (4) copy constructor
			// Constructs a container with a copy of each of the elements in x, in the same order.
			vector(const vector<T> &x) : _size(x.size()), _capacity(x.capacity())
			{
				this->_data = this->_alloc.allocate(this->_capacity);
				for(size_type index = 0; index < this->_size; ++index)
					this->_alloc.construct(&this->_data[index], x._data[index]);
			}

			~vector()
			{
				this->_alloc.deallocate(this->_data, this->_capacity);
			}

			vector<T> const &operator=(vector<T> const &rhs)
			{
				vector tmp(rhs);
				swap(tmp);
				return(*this);
			}

//----------------------------------------ft----------------------------------------
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Iterators~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			// Returns an iterator pointing to the first element in the vector.
			// If the vector object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
			iterator begin()
			{
				return(iterator(_data));
			}
			
			const_iterator begin() const
			{
				return(const_iterator(_data));
			}

			// Returns an iterator referring to the past-the-end element in the vector container.
			// The past-the-end element is the theoretical element that would follow the last element in the vector. 
			// It does not point to any element, and thus shall not be dereferenced.
			iterator end()
			{
				return(iterator(_data + _size));
			}
			
			const_iterator end() const
			{
				return(const_iterator(_data + _size));
			}

			// Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
			// Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
			// rbegin points to the element right before the one that would be pointed to by member end.
			// https://en.cppreference.com/w/cpp/iterator/reverse_iterator
			reverse_iterator rbegin()
			{
				return(reverse_iterator(_data + _size - 1));
			}

			const_reverse_iterator rbegin() const
			{
				return(const_reverse_iterator(_data + _size - 1));
			}

			// Returns a reverse iterator pointing to the theoretical element preceding the first element in the 
			// vector (which is considered its reverse end).
			reverse_iterator rend()
			{
				return(reverse_iterator(_data - 1));
			}

			const_reverse_iterator rend() const
			{
				return(const_reverse_iterator(_data - 1));
			}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Capacity~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			size_type size() const { return this->_size;}

			// Returns the maximum number of elements that the vector can hold.
			// This is the maximum potential size the container can reach due to known system or library implementation limitations, 
			// but the container is by no means guaranteed to be able to reach that size: it can still fail to allocate storage at 
			// any point before that size is reached.
			size_type max_size() const { return this->_alloc.max_size(); }


			// Resizes the container so that it contains n elements.
			// -->If n is smaller than the current container size, the content is reduced to its first n elements, removing those 
			// beyond (and destroying them).
			// -->If n is greater than the current container size, the content is expanded by inserting at the end as many elements 
			// as needed to reach a size of n.
			// If val is specified, the new elements are initialized as copies of val, otherwise, they are value-initialized.
			// -->If n is also greater than the current container capacity, an automatic reallocation of the allocated storage space takes place.
			// Notice that this function changes the actual content of the container by inserting or erasing elements from it.
			// Parameters
			// n --->		New container size, expressed in number of elements.
			// val --->	Object whose content is copied to the added elements in case that n is greater than the current container size.
			// 			If not specified, the default constructor is used instead.
			void resize (size_type n, value_type val = value_type())
			{
				if (n <= this->_size)
				{
					for(size_type i = this->_size; i > n; --i)
						this->_alloc.destroy(&this->_data[i]);
					this->_size = n;
					return ;
				}
				if (n > this->_size && n <= this->_capacity)
				{
					for(size_type i = this->_size; i < n; ++i)
						this->_alloc.construct(&this->_data[i], val);
					this->_size = n;
				}
				else if (n > this->_size && n > this->_capacity)
				{
					this->ft_reallocate(n * 2);
					for(size_type i = this->_size; i < n; ++i)
						this->_alloc.construct(&this->_data[i], val);
					this->_size = n;
				}
			}

			size_type capacity() const {return this->_capacity;}

			bool empty() const { if (this->_size) return 0; else return 1;}

			// Requests that the vector capacity be at least enough to contain n elements.
			// If n is greater than the current vector capacity, the function causes the container to reallocate its storage 
			// increasing its capacity to n (or greater).
			// In all other cases, the function call does not cause a reallocation and the vector capacity is not affected.
			// This function has no effect on the vector size and cannot alter its elements.
			void reserve (size_type n)
			{
				if (this->_capacity > n)
					return ;
				this->ft_reallocate(n);
			}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Element access~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			// Returns a reference to the element at position n in the vector container.
			// A similar member function, vector::at, has the same behavior as this operator function, except that 
			// vector::at is bound-checked and signals if the requested position is out of range by throwing an 
			// out_of_range exception.
			reference operator[] (size_type n)
			{
				return (this->_data[n]);
			}

			const_reference operator[] (size_type n) const
			{
				return (this->_data[n]);
			}

			reference at (size_type n)
			{
				if (n < this->_size)
					return (this->_data[n]);
				throw std::out_of_range("vector");
			}

			const_reference at (size_type n) const
			{
				if (n < this->_size)
					return (this->_data[n]);
				throw std::out_of_range("vector");
			}

			// Returns a reference to the first element in the vector.
			// Calling this function on an empty container causes undefined behavior.
			reference front() 
			{
				return (this->_data[0]);
			}

			const_reference front() const
			{
				return (this->_data[0]);
			}

			// Returns a reference to the last element in the vector.
			// Calling this function on an empty container causes undefined behavior.
			reference back()
			{
				return (this->_data[this->_size - 1]);
			}

			const_reference back() const
			{
				return (this->_data[this->_size - 1]);
			}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Modifiers~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			//Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.

			// Any elements held in the container before the call are destroyed and replaced by newly constructed elements.
			// This causes an automatic reallocation of the allocated storage space if -and only if- the new vector size 
			// surpasses the current vector capacity.
			
			// We have two assign ft, on templated (so could take anything), not the other. To prevent conflict
			// we enable the iterator ft only if the passed type is not an integral (otherwise the dereferencement
			// of *first would cause a problem), so that the overloaded non templated ft is choosen at compile-time

			// In the range version (1), the new contents are elements constructed from each of the elements in the range 
			// between first and last, in the same order.
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_Integral<InputIterator>::value >::type* dummy = 0)
			{
				(void) dummy;
				size_type span = 0;
				for(InputIterator tmp = first; tmp != last; ++tmp)
					span++;
				if (span > this->_capacity)
					this->ft_reallocate(span);

				for(size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(&this->_data[i]);
				
				this->_size = span;
				for(size_type i = 0; i < this->_size; ++i)
				{
					this->_alloc.construct(&this->_data[i], *first);
					first++;
				}
			}

			// In the fill version (2), the new contents are n elements, each initialized to a copy of val.
			void assign (size_type n, const value_type& val)
			{
				if (n > this->_capacity)
					this->ft_reallocate(n);
				this->_size = n;
				for(size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(&this->_data[i]);
				for(size_type i = 0; i < this->_size; ++i)
					this->_alloc.construct(&this->_data[i], val);
			}

			// Adds a new element at the end of the vector, after its current last element. The content of val is 
			// copied (or moved) to the new element.
			// This effectively increases the container size by one, which causes an automatic reallocation of the 
			// allocated storage space if -and only if- the new vector size surpasses the current vector capacity.
			void push_back (const value_type& val)
			{
				if (this->_size < this->_capacity)
				{
					this->_alloc.construct(&this->_data[this->_size], val);
					this->_size++;
				}
				else
				{
					if (this->_capacity == 0)
						this->ft_reallocate(1);
					else
						this->ft_reallocate(this->_capacity * 2);
					this->_alloc.construct(&this->_data[this->_size], val);
					this->_size++;
				}
			}

			// Removes the last element in the vector, effectively reducing the container size by one.
			// This destroys the removed element.
			void pop_back()
			{

				this->_alloc.destroy(&this->_data[this->_size]);
				this->_size --;
			}

			// The vector is extended by inserting new elements before the element at the specified position, 
			// effectively increasing the container size by the number of elements inserted.
			// This causes an automatic reallocation of the allocated storage space if -and only if- the new 
			// vector size surpasses the current vector capacity.

			// single element (1) : position -> Position in the vector where the new elements are inserted.
			iterator insert (iterator position, const value_type& val)
			{
				size_type index = position - this->_data;
				size_type j = index;
				pointer tmp;
				iterator ret;
				
				if (this->_capacity > this->_size && this->_capacity != 0)
					tmp = this->_alloc.allocate(this->_capacity);

				else if (this->_capacity == 0)
				{
					this->_capacity++;
					tmp = this->_alloc.allocate(this->_capacity);
				}
				else
				{
					tmp = this->_alloc.allocate(this->_capacity * 2);
					this->_capacity*=2;
				}

				size_type i = 0;
				while(i < index)
				{
					this->_alloc.construct(&tmp[i], this->_data[i]);
					i++;
				}
				this->_alloc.construct(&tmp[i], val);
				i++;
				
				while(j < this->_size)
				{
					this->_alloc.construct(&tmp[i], this->_data[j]);
					i++;
					j++;
				}
				
				for(size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(&this->_data[i]);
				this->_alloc.deallocate(this->_data, this->_capacity);

				this->_size++;
				this->_data = tmp;
				ret = &this->_data[index];
				return ret;
			}

			// fill (2) : n -> Number of elements to insert. Each element is initialized to a copy of val.
			// Will insert n elements at position position, all initialized to val
			void insert (iterator position, size_type n, const value_type& val)
			{
				size_type index = position - this->_data;
				pointer tmp;
				size_type i = 0;
				size_type j = 0;

				if (this->_capacity > this->_size + n)
					tmp = this->_alloc.allocate(this->_capacity);
				else
				{
					tmp = this->_alloc.allocate(this->_capacity + n);
					this->_capacity += n;
				}
				while(i < index)
				{
					this->_alloc.construct(&tmp[i], this->_data[i]);
					i++;
				}
				while(j < n)
				{
					this->_alloc.construct(&tmp[i + j], val);
					j++;
				}
				j+=i;
				while(i < this->_size)
				{
					this->_alloc.construct(&tmp[j], this->_data[i]);
					i++;
					j++;
				}
				for(size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(&this->_data[i]);
				this->_alloc.deallocate(this->_data, this->_capacity);

				this->_size+=n;
				this->_data = tmp;
			}

			// range (3) -> will insert at position the elements between first and last :
			// Iterators specifying a range of elements. Copies of the elements in the range [first,last) are inserted at 
			// position (in the same order).
			// Notice that the range includes all the elements between first and last, including the element pointed by 
			// first but not the one pointed by last.
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_Integral<InputIterator>::value >::type* dummy = 0)
			{
				(void) dummy;
				size_type index = position - this->_data;
				pointer tmp;
				size_type i = 0;
				size_type j = 0;
				size_type n = 0;
				for(InputIterator tmp = first; tmp != last; tmp++)
					n++;

				if (this->_capacity > this->_size + n)
					tmp = this->_alloc.allocate(this->_capacity);

				else
				{
					tmp = this->_alloc.allocate(this->_capacity + n);
					this->_capacity += n;
				}

				while(i < index)
				{
					this->_alloc.construct(&tmp[i], this->_data[i]);
					i++;
				}
				while(j < n)
				{
					this->_alloc.construct(&tmp[i + j], (*first));
					j++;
					first++;
				}
				j+=i;
				while(i < this->_size)
				{
					this->_alloc.construct(&tmp[j], this->_data[i]);
					i++;
					j++;
				}
				for(size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(&this->_data[i]);
				this->_alloc.deallocate(this->_data, this->_capacity);

				this->_size+=n;
				this->_data = tmp;
			}

			// Removes from the vector either a single element (position) or a range of elements ([first,last)).
			// This effectively reduces the container size by the number of elements removed, which are destroyed.
			iterator erase (iterator position)
			{
				return (this->erase(position, position + 1));
			}

			iterator erase (iterator first, iterator last)
			{
				size_type index_beg = first - this->_data;
				size_type index_end = last - this->_data;
				pointer tmp = this->_alloc.allocate(this->_capacity);
				size_type i = 0;
				size_type j = 0;
				iterator ret;
				while(i < this->_size)
				{
					if(i >= index_beg && i < index_end)
					{
						i++;
						continue;
					}
					this->_alloc.construct(&tmp[j], this->_data[i]);
					i++;
					j++;
				}
				this->_alloc.deallocate(this->_data, this->_capacity);
				this->_data = tmp;
				ret = &this->_data[index_beg];
				this->_size -= index_end - index_beg;
				return ret;
			}

			// Exchanges the content of the container by the content of x, which is another vector object of the same type. 
			// Sizes may differ. After the call to this member function, the elements in this container are those which 
			// were in x before the call, and the elements of x are those which were in this. All iterators, references 
			// and pointers remain valid for the swapped objects.
			void swap (vector& x)
			{
				allocator_type alloc_tmp;
				pointer		data_tmp = NULL;
				size_type	size_tmp = 0;
				size_type	capacity_tmp = 0;
				if (this->_alloc == x._alloc && this->_data == x._data 
				&& this->_size == x._size && this->_capacity == x._capacity)
					return ;
				alloc_tmp = this->_alloc;
				data_tmp = this->_data;
				size_tmp = this->_size;
				capacity_tmp = this->_capacity;

				this->_alloc = x._alloc;
				this->_data = x._data;
				this->_size = x._size;
				this->_capacity = x._capacity;

				x._alloc = alloc_tmp;
				x._data = data_tmp;
				x._size = size_tmp;
				x._capacity = capacity_tmp;
			}

			// Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
			void clear()
			{
				for (size_type i = 0; i < this->_size; ++i)
					this->_alloc.destroy(&this->_data[i]);
				this->_size = 0;
			}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Allocator~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			allocator_type get_allocator() const
			{
				allocator_type tmp = this->_alloc;
				return tmp;
			}
//----------------------------------------helper ft----------------------------------------
		private:
			// function used to increase the capacity of a vector. The elements of _data
			// are constructed in a temporary pointer with the right capacity
			void ft_reallocate(size_type new_capacity)
			{
				pointer tmp = this->_alloc.allocate(new_capacity);
				for(size_type i = 0; i < this->_size; ++i)
				{
					this->_alloc.construct(&tmp[i], this->_data[i]);
					this->_alloc.destroy(&this->_data[i]);
				}
				this->_alloc.deallocate(this->_data, this->_capacity);
				this->_data = tmp;
				this->_capacity = new_capacity;
			}
	};

//----------------------------------------Non-member function overloads----------------------------------------
	// Performs the appropriate comparison operation between the vector containers lhs and rhs.

	// The equality comparison (operator==) is performed by first comparing sizes, and if they match, the elements 
	// are compared sequentially using operator==, stopping at the first mismatch (as if using algorithm equal).

	// The less-than comparison (operator<) behaves as if using algorithm lexicographical_compare, which compares 
	// the elements sequentially using operator< in a reciprocal manner (i.e., checking both a<b and b<a) and 
	// stopping at the first occurrence.

	// The other operations also use the operators == and < internally to compare the elements, behaving as if 
	// the following equivalent operations were performed:
	
	// operation	equivalent operation
	// a!=b		!(a==b)
	// a>b			b<a
	// a<=b		!(b<a)
	// a>=b		!(a<b)

	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return(false);
		for(size_t i = 0; i < lhs.size(); ++i)
		{
			if(lhs[i] != rhs[i])
				return(false);
		}
		return (true);
	}

	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs==rhs));
	}

	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs<lhs);
	}

	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs<rhs));
	}

	// The contents of container x are exchanged with those of y. Both container objects must be of the same 
	// type (same template parameters), although sizes may differ.
	// After the call to this member function, the elements in x are those which were in y before the call, 
	// and the elements of y are those which were in x. All iterators, references and pointers remain valid for 
	// the swapped objects.
	template<class T, class Alloc>
	void swap(vector<T, Alloc>& x, vector<T, Alloc>& y)
	{ x.swap(y); }
}

#endif
