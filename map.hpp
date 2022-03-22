#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <iostream>
#include <stdexcept>
#include "AVL_tree.hpp"

namespace ft
{

	// 	Key
	// Type of the keys. Each element in a map is uniquely identified by its key value.
	// Aliased as member type map::key_type.

	// T
	// Type of the mapped value. Each element in a map stores some data as its mapped value.
	// Aliased as member type map::mapped_type.

	// Compare
	// A binary predicate that takes two element keys as arguments and returns a bool. The expression comp(a,b), where comp is an 
	// object of this type and a and b are key values, shall return true if a is considered to go before b in the strict weak ordering 
	// the function defines.
	// The map object uses this expression to determine both the order the elements follow in the container and whether two element
	// keys are equivalent (by comparing them reflexively: they are equivalent if !comp(a,b) && !comp(b,a)). No two elements in a map 
	// container can have equivalent keys.
	// This can be a function pointer or a function object (see constructor for an example). This defaults to less<T>, which returns 
	// the same as applying the less-than operator (a<b).
	// Aliased as member type map::key_compare.

	// Alloc
	// Type of the allocator object used to define the storage allocation model. By default, the allocator class template is used, 
	// which defines the simplest memory allocation model and is value-independent.
	// Aliased as member type map::allocator_type.
	template <	class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map
	{
//----------------------------------------typedefs----------------------------------------
		public:
			typedef Key																key_type;
			typedef T																mapped_type;
			typedef ft::pair<const key_type,mapped_type>							value_type;
			typedef Compare															key_compare;
			typedef std::allocator<ft::pair<const Key,T> >							allocator_type;
			typedef value_type&														reference;
			typedef const value_type&												const_reference;
			typedef value_type*														pointer;
			typedef const value_type*												const_pointer;
			typedef int																difference_type;
			typedef size_t															size_type;
			typedef ft::Node<const Key, T>											node;
			typedef ft::map_iterator<value_type, node>								iterator;
			typedef ft::map_iterator<const value_type, node>						const_iterator;
			typedef ft::map_reverse_iterator<value_type, node>						reverse_iterator;
			typedef ft::map_reverse_iterator<const value_type, node>				const_reverse_iterator;
			typedef ft::tree<key_type, mapped_type, key_compare, allocator_type>	tree;

//----------------------------------------classes / struct imbriquées----------------------------------------
		private:
			// std::map::value_comp has as a return type a value_compare
			// The comparison object returned is an object of the member type map::value_compare, which is a nested class that uses 
			// the internal comparison object to generate the appropriate comparison functional class. 
			class value_compare
			{
				protected:
					Compare comp;
				public:
					value_compare (Compare c) : comp(c) {}
					bool operator() (const value_type& x, const value_type& y) const
					{
						return comp(x.first, y.first);
					}
			};

//----------------------------------------attributes----------------------------------------
		private:
			allocator_type			_alloc;
			tree					_tree;
			key_compare				_comp;

//----------------------------------------canon----------------------------------------
		public:
			// (1) empty container constructor (default constructor)
			// Constructs an empty container, with no elements.
			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _tree(tree()), _comp(comp)
			{}

			// (2) range constructor
			// Constructs a container with as many elements as the range [first,last), with each element constructed from its 
			// corresponding element in that range.

			//https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/enable-if
			// the enable if is used to prevent compilation conflicts with the fill constructor, it will be enabled only if the params are 
			// not integrals
			template <class InputIterator>
			map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type(),
			typename ft::enable_if<!ft::is_Integral<InputIterator>::value >::type* dummy = 0 ) :
			_alloc(alloc), _tree(tree()), _comp(comp)
			{
				(void) dummy;
				this->insert(first,last);
			}

			// (3) copy constructor
			// Constructs a container with a copy of each of the elements in x.
			map (const map& x)
			{
				*this = x;
			}

			// the deallocation of the nodes of the AVL tree are happening at the destruction of _tree
			~map()
			{}

			map& operator= (const map& x)
			{
				this->clear();
				this->insert(x.begin(), x.end());
				return (*this);
			}

//----------------------------------------member ft----------------------------------------
			//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Iterators~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			// Returns an iterator referring to the first element in the map container.
			// Because map containers keep their elements ordered at all times, begin points to the element 
			// that goes first following the container's sorting criterion.
			// If the map object is const-qualified, the function returns a const_iterator. Otherwise, it returns an iterator.
			iterator begin()
			{
				return(iterator(this->_tree.begin()));
			}

			const_iterator begin() const
			{
				return(const_iterator(this->_tree.begin()));
			}

			// Returns an iterator referring to the past-the-end element in the map container.
			// The past-the-end element is the theoretical element that would follow the last element in 
			// the map container. It does not point to any element, and thus shall not be dereferenced.
			iterator end()
			{
				return(iterator(this->_tree.end()));
			}

			const_iterator end() const
			{
				return(const_iterator(this->_tree.end()));
			}

			// Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
			// Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
			// If the map object is const-qualified, the function returns a const_reverse_iterator. Otherwise, it returns a reverse_iterator.
			reverse_iterator rbegin()
			{
				return(reverse_iterator(this->_tree.rbegin()));
			}

			const_reverse_iterator rbegin() const
			{
				return(const_reverse_iterator(this->_tree.rbegin()));
			}

			// Returns a reverse iterator pointing to the theoretical element right before the first element in the 
			// map container (which is considered its reverse end).
			reverse_iterator rend()
			{
				return(reverse_iterator(this->_tree.rend()));
			}

			const_reverse_iterator rend() const
			{
				return(const_reverse_iterator(this->_tree.rend()));
			}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Capacity~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			bool empty() const { return this->_tree.empty(); }

			size_type size() const { return this->_tree.size(); }

			// Returns the maximum number of elements that the map container can hold.
			// This is the maximum potential size the container can reach due to known system or library implementation 
			// limitations, but the container is by no means guaranteed to be able to reach that size: it can still fail 
			// to allocate storage at any point before that size is reached.
			size_type max_size() const { return this->_tree.max_size(); }

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Element access~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			// If k matches the key of an element in the container, the function returns a reference to its mapped value.

			// If k does not match the key of any element in the container, the function inserts a new element with that 
			// key and returns a reference to its mapped value. Notice that this always increases the container size by one, even 
			// if no mapped value is assigned to the element (the element is constructed using its default constructor).

			// A call to this function is equivalent to:
			// (*((this->insert(make_pair(k,mapped_type()))).first)).second
			mapped_type& operator[] (const key_type& k)
			{
				return (this->_tree.brackets(k));
			}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Modifiers~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			// Extends the container by inserting new elements, effectively increasing the container size by the number of 
			// elements inserted.

			// Because element keys in a map are unique, the insertion operation checks whether each inserted element 
			// has a key equivalent to the one of an element already in the container, and if so, the element is not 
			// inserted, returning an iterator to this existing element (if the function returns a value).

			// For a similar container allowing for duplicate elements, see multimap.

			// An alternative way to insert elements in a map is by using member function map::operator[].

			// Internally, map containers keep all their elements sorted by their key following the criterion specified 
			// by its comparison object. The elements are always inserted in its respective position following this ordering.
			
			// single element (1)
			ft::pair<iterator,bool> insert (const value_type& val)
			{
				return (this->_tree.insert(val));
			}

			// with hint (2)
			iterator insert (iterator position, const value_type& val)
			{
				(void)position;
				ft::pair<iterator,bool> ret = this->_tree.insert(val);
				return (ret.first);
			}

			// range (3)
			// To prevent conflict
			// we enable the iterator ft only if the passed type is not an integral (otherwise the dereferencement
			// of *first would cause a problem), so that the overloaded non templated ft is choosen at compile-time

			// template <class T1, class T2>
			// pair<T1,T2> make_pair (T1 x, T2 y);
			// Constructs a pair object with its first element set to x and its second element set to y.
			// The template types can be implicitly deduced from the arguments passed to make_pair.
			template <class InputIterator>
			void insert (InputIterator first, InputIterator last,
			typename ft::enable_if<!ft::is_Integral<InputIterator>::value >::type* dummy = 0 )
			{
				(void) dummy;
				while(first != last)
				{
					this->_tree.insert(ft::make_pair(first->first, first->second)); 
					first++;
				}
			}

			// Removes from the map container either a single element or a range of elements ([first,last)).
			// This effectively reduces the container size by the number of elements removed,
			// which are destroyed.
			
			// Iterator pointing to a single element to be removed from the map.
			void erase (iterator position)
			{
				key_type i = position->first;
				this->_tree.erase_key(i);
			}

			// Key of the element to be removed from the map.
			size_type erase (const key_type& k)
			{
				return (this->_tree.erase_key(k));
			}

			// Iterators specifying a range within the map container to be removed: [first,last). i.e., the range 
			// includes all the elements between first and last, including the element pointed by first 
			// but not the one pointed by last.
			void erase (iterator first, iterator last)
			{
				this->_tree.erase_iter(first, last);
			}

			// Exchanges the content of the container by the content of x, which is another map of the same type. 
			// Sizes may differ.
			// After the call to this member function, the elements in this container are those which were 
			// in x before the call, and the elements of x are those which were in this. All iterators, 
			// references and pointers remain valid for the swapped objects.
			// Since _tree contains several variables, the _tree has its own swapped function swapping the variables
			// used for the AVL tree
			void swap (map& x)
			{
				allocator_type	alloc_tmp;
				key_compare		comp_tmp;

				alloc_tmp = this->_alloc;
				comp_tmp = this->_comp;

				this->_alloc = x._alloc;
				this->_comp = x._comp;

				x._alloc = alloc_tmp;
				x._comp = comp_tmp;

				this->_tree.swap(x._tree);
			}

			// Removes all elements from the map container (which are destroyed), leaving the container with a size of 0.
			void clear()
			{
				this->_tree.erase_iter(this->begin(), this->end());
			}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Observers~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			// Returns a copy of the comparison object used by the container to compare keys.
			// The comparison object of a map object is set on construction. Its type (member key_compare) is the third 
			// template parameter of the map template. By default, this is a less object, which returns the same as operator<.

			// This object determines the order of the elements in the container: it is a function pointer or 
			// a function object that takes two arguments of the same type as the element keys, and returns
			// true if the first argument is considered to go before the second in the strict weak ordering 
			// it defines, and false otherwise.
			key_compare key_comp() const {return this->_comp;}

			// Returns a comparison object that can be used to compare two elements to get whether the key of the first 
			// one goes before the second.

			// The arguments taken by this function object are of member type value_type (defined in map as an alias of 
			// pair<const key_type,mapped_type>), but the mapped_type part of the value is not taken into consideration 
			// in this comparison.

			// The comparison object returned is an object of the member type map::value_compare, which is a nested 
			// class that uses the internal comparison object to generate the appropriate comparison functional class.
			value_compare value_comp() const {return value_compare(this->_comp);}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Operations~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			// Searches the container for an element with a key equivalent to k and returns an iterator to it if found, 
			// otherwise it returns an iterator to map::end.

			// Two keys are considered equivalent if the container's comparison object returns false reflexively 
			// (i.e., no matter the order in which the elements are passed as arguments).

			// Another member function, map::count, can be used to just check whether a particular key exists.
			iterator find (const key_type& k)
			{
				return (this->_tree.find(k));
			}

			const_iterator find (const key_type& k) const
			{
				return (this->_tree.find(k));
			}

			// Searches the container for elements with a key equivalent to k and returns the number of matches.

			// Because all elements in a map container are unique, the function can only return 1 
			// (if the element is found) or zero (otherwise).
			size_type count (const key_type& k) const
			{
				return (this->_tree.count(k));
			}

			// Returns an iterator pointing to the first element in the container whose key is not considered to go 
			// before k (i.e., either it is equivalent or goes after).

			// The function uses its internal comparison object (key_comp) to determine this, returning an iterator to the 
			// first element for which key_comp(element_key,k) would return false.

			// If the map class is instantiated with the default comparison type (less), the function returns an iterator
			// to the first element whose key is not less than k.

			// A similar member function, upper_bound, has the same behavior as lower_bound, except in the case that the
			// map contains an element with a key equivalent to k: In this case, lower_bound returns an iterator pointing to 
			// that element, whereas upper_bound returns an iterator pointing to the next element.
			iterator lower_bound (const key_type& k)
			{
				return (this->_tree.lower_bound(k));
			}

			const_iterator lower_bound (const key_type& k) const
			{
				return (this->_tree.const_lower_bound(k));
			}

			iterator upper_bound (const key_type& k)
			{
				return (this->_tree.upper_bound(k));
			}

			const_iterator upper_bound (const key_type& k) const
			{
				return (this->_tree.const_upper_bound(k));
			}

			pair<iterator,iterator> equal_range (const key_type& k)
			{
				return (this->_tree.equal_range(k));
			}

			// Returns the bounds of a range that includes all the elements in the container which have a key equivalent to k.

			// Because the elements in a map container have unique keys, the range returned will contain a single element at most.

			// If no matches are found, the range returned has a length of zero, with both iterators pointing to the 
			// first element that has a key considered to go after k according to the container's internal comparison object (key_comp).

			// Two keys are considered equivalent if the container's comparison object returns false reflexively 
			// (i.e., no matter the order in which the keys are passed as arguments).
			pair<const_iterator,const_iterator> equal_range (const key_type& k) const
			{
				return (this->_tree.const_equal_range(k));
			}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Allocator~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			allocator_type get_allocator() const { return this->_alloc; }
	};
//----------------------------------------Non-member function overloads----------------------------------------
	// The contents of container x are exchanged with those of y. Both container objects must be of the same 
	// type (same template parameters), although sizes may differ.
	// After the call to this member function, the elements in x are those which were in y before the call, 
	// and the elements of y are those which were in x. All iterators, references and pointers remain valid for 
	// the swapped objects.
	template <class Key, class T, class Compare, class Alloc>
	void swap (map<Key,T,Compare,Alloc>& x, map<Key,T,Compare,Alloc>& y)
	{
		x.swap(y);
	}

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
	// a>b		b<a
	// a<=b		!(b<a)
	// a>=b		!(a<b)
	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )
	{
		typename map<Key, T, Compare, Alloc>::const_iterator lhs_it = lhs.begin();
		typename map<Key, T, Compare, Alloc>::const_iterator rhs_it = rhs.begin();
		while(lhs_it != lhs.end() && rhs_it != rhs.end())
		{
			if(lhs_it->first != rhs_it->first)
				return (0);
			lhs_it++;
			rhs_it++;
		}
		if (lhs.size() != rhs.size())
			return (0);
		return (1);

	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs==rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )
	{
		return !(rhs < lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )
	{
		return (rhs<lhs);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const map<Key,T,Compare,Alloc>& lhs,
						const map<Key,T,Compare,Alloc>& rhs )
	{
		return (!(lhs<rhs));
	}
}
#endif