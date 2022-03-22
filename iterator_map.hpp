#ifndef ITERATOR_MAP_HPP
#define ITERATOR_MAP_HPP

#include <iostream>
#include "utils.hpp"

namespace ft
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Prototypes~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Needed for the constructions of a reverse from a normal and vice versa
	template<typename value_type, typename Node>
		class map_iterator;

	template<typename value_type, typename Node>
		class map_reverse_iterator;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ITERATOR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	template<typename value_type, typename Node>
	class map_iterator
	{
		public:
		//-------------------aliases/struct iterator_traits<T*>-------------------------
			typedef std::random_access_iterator_tag			iterator_category;
			typedef value_type&								reference;
			typedef value_type*								pointer;
			typedef int										difference_type;
			typedef size_t									size_type;
			typedef	typename value_type::first_type			key_type;
			typedef	typename value_type::second_type		mapped_type;
			typedef map_iterator<value_type, Node>			iterator_type;

		//-------------------attributes-------------------------
		private:
			Node * _node;
			Node * _null;
			Node * _root;

		//-------------------canon-------------------------
		public:
			map_iterator() : _node(NULL), _null(NULL), _root(NULL) {}

			map_iterator(Node * p, Node * null, Node * root)
			{
				this->_node = p;
				this->_null = null;
				this->_root = root;
			}

			map_iterator(const map_iterator<value_type, Node>& it) : _node(it.get_node()), _null(it.get_null()), _root(it.get_root())
			{}

			// Without the dummy : ambiguous call (this constructor is used for the base ft of the reverse iterators)
			map_iterator(const map_reverse_iterator<value_type, Node>& it, int dummy) : _node(it.get_node()), _null(it.get_null()), _root(it.get_root())
			{
				(void)dummy;
			}

			operator	map_iterator<value_type const, Node>() const
			{ return (map_iterator<value_type const, Node>(this->_node, this->_null, this->_root)); }
			//https://docs.microsoft.com/en-us/cpp/cpp/cast-operator-parens?view=msvc-170

			~map_iterator() {}

			map_iterator &operator=(const map_iterator &rhs)
			{
				this->_node = rhs.get_node();
				this->_null = rhs.get_null();
				this->_root = rhs.get_root();
				return (*this);
			}

		//-------------------helper ft-------------------------
		public:
			Node* get_node() const {return this->_node;}
			Node* get_null() const {return this->_null;}
			Node* get_root() const {return this->_root;}
		
		//-------------------member ft------------------------
			pointer operator->() const //Returns a pointer to the element pointed to by the iterator
			{
				return &(operator*());
			}

			reference operator*() const// Returns a reference to the element pointed to by the iterator.
			{ 
				return this->_node->data;
			}

			map_iterator& operator++() // ++i
			{
				if(this->_node == this->_null)
				{
					this->_node = min_val_node(this->_root);
					return (*this);
				}
				if (this->_node == max_val_node(this->_root))
				{
					this->_node = this->_null;
					return (*this);
				}
				this->_node = find_next(this->_node);
				return (*this);
			}

			map_iterator operator++(int) // i++
			{ 
				map_iterator<value_type, Node> tmp(*this);
				this->operator++();
				return tmp;
			}

			map_iterator& operator--() // --i
			{	
				if (this->_node == this->_null) // this is in case a null node need to be decremented : it needs to go to the max value
				{
					this->_node = max_val_node(this->_root);
					return (*this);
				}
				this->_node = find_prev(this->_node);
				return (*this);
			}

			map_iterator operator--(int) // i--
			{
				map_iterator<value_type, Node> tmp(*this);
				this->operator--();
				return tmp;
			}

			bool operator==(const map_iterator&rhs) const
			{
				return this->_node == rhs.get_node();
			}

			bool operator!=(const map_iterator&rhs) const
			{
				return this->_node != rhs.get_node();
			}
		//-------------------helper ft------------------------
			// cf AVL_tree
			Node* find_next(Node * node)
			{
				Node * next;
				if (node->right == this->_null)
				{
					next = node;
					while (next->parent && next == next->parent->right)
						next = next->parent;
					next = next->parent;
				}
				else
				{
					next = node->right;
					while (next->left != this->_null)
						next = next->left;
				}
				return (next);
			}

			Node* find_prev(Node * node)
			{
				Node * prev;
				if (node->left == this->_null || node->left == NULL)
				{
					prev = node;
					while (prev->parent && prev == prev->parent->left)
						prev = prev->parent;
					prev = prev->parent;
				}
				else
				{
					prev = node->left;
					while (prev->right != this->_null)
						prev = prev->right;
				}
				return (prev);
			}

			Node * max_val_node(Node *node) const // returns the node with the lowest data value
			{
				if(node == this->_null)
					return node;
				if (node->right && node->right != this->_null)
					return max_val_node(node->right);
				return node;
			}

			Node* min_val_node(Node *node) const
			{
				if (node->left && node->left != this->_null)
					return min_val_node(node->left);
				return node;
			}
	};

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~REVERSE_ITERATOR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	template<class value_type, class Node>
	class map_reverse_iterator
	{
		public:
		//-------------------aliases/struct iterator_traits<T*>-------------------------
			typedef std::random_access_iterator_tag			iterator_category;
			typedef value_type&								reference;
			typedef value_type*								pointer;
			typedef int										difference_type;
			typedef size_t									size_type;
			typedef	typename value_type::first_type			key_type;
			typedef	typename value_type::second_type		mapped_type;
			typedef map_iterator<value_type, Node>			iterator_type;

		//-------------------attributes-------------------------
		private:
			Node * _node;
			Node * _null;
			Node * _root;

		//-------------------canon-------------------------
		public:
			map_reverse_iterator() : _node(NULL), _null(NULL), _root(NULL) {}
			map_reverse_iterator(Node * p, Node * null, Node * root) : _node(p), _null(null), _root(root) {}

			template <class v, class n>
			map_reverse_iterator (const map_reverse_iterator<v, n>& rit)
			{
				this->_node = rit.get_node();
				this->_null = rit.get_null();
				this->_root = rit.get_root();
			}

			template <class v, class n>
			map_reverse_iterator (const map_iterator<v, n>& it)
			{
				this->_null = it.get_null();
				this->_root = it.get_root();
				this->_node = it.get_node();
				if (this->_node == min_val_node(this->_root))
					this->_node = this->_null;
			}

			operator	map_reverse_iterator<value_type const, Node>() const
			{ return (map_reverse_iterator<value_type const, Node>(this->_node, this->_null, this->_root)); }

			~map_reverse_iterator() {}
			
			map_reverse_iterator &operator=(const map_reverse_iterator &rhs)
			{
				this->_node = rhs.get_node();
				this->_null = rhs.get_null();
				this->_root = rhs.get_root();
				return (*this);
			}

		//-------------------helper ft-------------------------
		public:
			Node* get_node() const {return this->_node;}
			Node* get_null() const {return this->_null;}
			Node* get_root() const {return this->_root;}
		
		//-------------------member ft------------------------
			iterator_type base() const
			{
				map_iterator<value_type, Node> tmp(*this, 0);
				tmp++;
				return (tmp);
			}

			pointer operator->() const
			{
				return &(operator*());
			}

			reference operator*() const
			{ 
				return this->_node->data;
			}

			map_reverse_iterator& operator--()
			{
				if (this->_node == this->_null)
				{
					this->_node = min_val_node(this->_root);
					return (*this);
				}
				this->_node = find_next(this->_node);
				return (*this);
			}

			map_reverse_iterator operator--(int)
			{ 
				map_reverse_iterator<value_type, Node> tmp(*this);
				this->operator--();
				return tmp;
			}

			map_reverse_iterator& operator++()
			{	
				if (this->_node == this->_null || this->_node == min_val_node(this->_root)) // this is in case a null node need to be decremented : it needs to go to the max value
				{
					this->_node = this->_null;
					return (*this);
				}
				this->_node = find_prev(this->_node);
				return (*this);
			}

			map_reverse_iterator operator++(int)
			{
				map_reverse_iterator<value_type, Node> tmp(*this);
				this->operator++();
				return tmp;
			}

			bool operator==(const map_reverse_iterator&rhs) const
			{
				return this->_node == rhs.get_node();
			}

			bool operator!=(const map_reverse_iterator&rhs) const
			{
				return this->_node != rhs.get_node();
			}
		//-------------------helper ft------------------------
			Node* find_next(Node * node) const
			{
				Node * next;
				if (node->right == this->_null)
				{
					next = node;
					while (next->parent && next == next->parent->right)
						next = next->parent;
					next = next->parent;
				}
				else
				{
					next = node->right;
					while (next->left != this->_null)
						next = next->left;
				}
				return (next);
			}

			Node* find_prev(Node * node) const
			{
				Node * prev;
				if (node->left == this->_null || node->left == NULL)
				{
					prev = node;
					while (prev->parent && prev == prev->parent->left)
						prev = prev->parent;
					prev = prev->parent;
				}
				else
				{
					prev = node->left;
					while (prev->right != this->_null)
						prev = prev->right;
				}
				return (prev);
			}

			Node * max_val_node(Node *root) const // returns the node with the lowest data value
			{
				if (root->right && root->right != this->_null)
					return max_val_node(root->right);
				return root;
			}

			Node* min_val_node(Node *root) const
			{
				if (root->left && root->left != this->_null)
					return min_val_node(root->left);
				return root;
			}
	};
}
#endif
