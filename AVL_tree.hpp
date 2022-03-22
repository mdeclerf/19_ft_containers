#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <memory>
#include <iostream>
#include "iterator_map.hpp"
#include "utils.hpp"
#include <stdexcept>

namespace ft
{
	template<class Key, class T>
	class Node
	{
		public:
			ft::pair<const Key,T>	data;
			Node *					left;
			Node *					right;
			Node *					parent;
			size_t					height;
	};

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> >, class Node = Node<const Key, T> >
	class tree
	{

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Aliases~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		public :
			typedef Key													key_type;
			typedef T													mapped_type;
			typedef ft::pair<const Key,T>								value_type;
			typedef Compare												key_compare;
			typedef std::allocator<ft::pair<const Key,T> >				allocator_type;
			typedef std::allocator<ft::Node<const Key,T> >				allocator_type_node;
			typedef int													difference_type;
			typedef size_t												size_type;
			typedef ft::map_iterator<value_type, Node>					iterator;
			typedef ft::map_iterator<const value_type, Node>			const_iterator;
			typedef ft::map_reverse_iterator<value_type, Node>			reverse_iterator;
			typedef ft::map_reverse_iterator<const value_type, Node>	const_reverse_iterator;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Attributes~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		private:
			Node *					_root;
			Node *					_null;
			key_compare				_comp;
			allocator_type			_alloc_pair;
			allocator_type_node		_alloc_node;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~canon~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		public:
			// The constructor of the binary tree is when the _null node is created. It will be used to end every
			// leaf of the tree (and handle the past end element of iterators). The null node has a value type of default
			tree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _comp(comp), _alloc_pair(alloc)
			{
				this->_null = new_node(value_type());
				this->_null->left = NULL;
				this->_null->right = NULL;
				this->_null->height = 0;
				this->_null->parent = NULL;
				this->_root = this->_null;
			}

			// erase_iter destroyed and deallocates nodes from the begin to the end of the tree, _null is also deallocated
			~tree ()
			{
				// preOrder(this->_root);
				// printTree(this->_root, nullptr, false, 0);
				erase_iter (this->begin(), this->end());
				_alloc_node.deallocate(this->_null, 1);
			}

			tree& operator= (const tree& x)
			{
				erase_iter (this->begin(), this->end());
				iterator it = x.begin();
				iterator ite = x.end();
				while(it != ite)
				{
					this->insert(ft::make_pair(it->first, it->second));
					it++;
				}
				return (*this);
			}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Member functions~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//----------------------------------------Iterators----------------------------------------
			// Two cases : or the tree is empty and the iterator takes three this->_null as param
			// or the min_val_node function is used to get the smallest node and create an iterator 
			// from it.
			iterator begin()
			{
				if (this->_root == this->_null)
					return(iterator(this->_root, this->_null, this->_root));
				Node * i = min_val_node(this->_root);
				return iterator(i, this->_null, this->_root);
			}

			// The past-the-end element is the theoretical element that would follow the last element in the 
			// vector. It does not point to any element, and thus shall not be dereferenced.
			// Here our this->_null
			iterator end()
			{
				return iterator(this->_null, this->_null, this->_root);
			}

			reverse_iterator rbegin()
			{
				if (this->_root == this->_null)
					return(reverse_iterator(this->_root, this->_null, this->_root));
				Node * i = max_val_node(this->_root);
				return reverse_iterator(i, this->_null, this->_root);
			}

			reverse_iterator rend()
			{
				return reverse_iterator(this->_null, this->_null, this->_root);
			}

			const_iterator begin() const
			{
				if (this->_root == this->_null)
					return(const_iterator(this->_root, this->_null, this->_root));
				Node * i = min_val_node(this->_root);
				return const_iterator(i, this->_null, this->_root);
			}

			const_iterator end() const
			{
				return const_iterator(this->_null, this->_null, this->_root);
			}

			const_reverse_iterator rbegin() const
			{
				if (this->_root == this->_null)
					return(const_reverse_iterator(this->_root, this->_null, this->_root));
				Node * i = max_val_node(this->_root);
				return const_reverse_iterator(i, this->_null, this->_root);
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(this->_null, this->_null, this->_root);
			}

		//----------------------------------------Capacity----------------------------------------
			bool empty() const
			{
				if(this->size())
					return 0;
				return 1;
			}

			size_type size() const
			{
				size_type size = 0;
				for(const_iterator it = this->begin(); it !=this->end(); ++it)
					size++;
				return (size);
			}

			size_type	max_size() const { return (this->_alloc_node.max_size()); }

		//----------------------------------------Element access----------------------------------------
			mapped_type& brackets(const key_type& k)
			{
				return (*((this->insert(ft::make_pair(k,mapped_type()))).first)).second; // https://www.cplusplus.com/reference/map/map/operator[]/
			}

		//----------------------------------------Modifiers----------------------------------------
			// The single element versions (1) return a pair, with its member pair::first set to an iterator 
			// pointing to either the newly inserted element or to the element with an equivalent key in the map. 
			// The pair::second element in the pair is set to true if a new element was inserted or false if 
			// an equivalent key already existed.
			pair<iterator, bool>	insert(value_type val)
			{
				if (this->_root == this->_null) // if no node yet
				{
					this->_root = insert_node(this->_root, val);
					return (ft::make_pair(iterator(this->_root, this->_null, this->_root), true));
				}

				Node * node = min_val_node(this->_root); // first loop to check if the value key doesn't exist yet in the tree, in which case nothing is inserted
				while(this->_comp(node->data.first, max_val_node(this->_root)->data.first)) // (node->data.first < max_val_node(this->_root)->data.first)
				{
					if (node->data.first == val.first)
						return(ft::make_pair(iterator(node, this->_null, this->_root), false));
					node = find_next(node);
				}
				if (max_val_node(this->_root)->data.first == val.first)
					return(ft::make_pair(iterator(node, this->_null, this->_root), false)); // check the last value
				this->_root = insert_node(this->_root, val); // node insertion

				node = min_val_node(this->_root); // second loop to get the return iterator at the right position, starting from the smallest node
				while(node != this->_null)
				{
					if (node->data.first == val.first)
						break;
					node = find_next(node);
				}
				return(ft::make_pair(iterator(node, this->_null, this->_root), true));
			}

			size_type erase_key (const key_type& i)
			{
				size_type ret  = 0;
				if (this->count(i)) // check if i is the key of one of the nodes
					ret = 1;
				delete_node(this->_root, i);
				return (ret);
			}

			void erase_iter (iterator first, iterator last) // here because if call erase from map, issue when root is deleted 
			// for iterator (need to create a new iterator for first every time, otherwise first keeps the original root, which causes problems
			// when the tree is balanced and or this root is deleted)
			{
				while(first != last)
				{
					Node * min = min_val_node(this->_root);
					Node * max = max_val_node(this->_root);
					Node * node_tmp = this->_null;
					while(min != max) // iterate through the tree looking for the key of first
					{
						if (min->data.first == first->first)
							node_tmp = find_next(min); // need to backup the element in the tree after the one matching the first key
						min = find_next(min);
					}
					if (max->data.first == first->first)
						node_tmp = this->_null; // past end element
					
					delete_node(this->_root, first->first); // delete the node
					iterator tmp(node_tmp, this->_null, this->_root); // create a new iterator with an updated root and the elem after the deleted one as node
					first = tmp;
				}
			}

		//----------------------------------------Operations----------------------------------------
			iterator	find(const key_type& k)
			{
				if (this->_root == this->_null)
					return this->end();
				Node * min = min_val_node(this->_root);
				Node * max = max_val_node(this->_root);
				while(min != max)
				{
					if (min->data.first == k)
						return(iterator(min, this->_null, this->_root));
					min = find_next(min);
				}
				if (max->data.first == k)
					return(iterator(max, this->_null, this->_root));
				else
					return this->end();
			}

			const_iterator	find(const key_type& k) const
			{
				if (this->_root == this->_null)
					return this->end();
				Node * min = min_val_node(this->_root);
				Node * max = max_val_node(this->_root);
				while(min != max)
				{
					if (min->data.first == k)
						return(const_iterator(min, this->_null, this->_root));
					min = find_next(min);
				}
				if (max->data.first == k)
					return(const_iterator(max, this->_null, this->_root));
				else
					return this->end();
			}

			size_type	count(const key_type& k) const
			{
				const_iterator it = this->find(k);
				if (this->find(k) == this->end())
					return 0;
				return 1;
			}

			// Key_compare : equivalent to operator < (returns true if the first argument is considered to go before the second)
			// 		operator>(lhs, rhs) -> this->_comp(rhs, lhs)
			// 		operator<(lhs, rhs) -> this->_comp(lhs, rhs)
			// 		operator<=(lhs, rhs) -> !this->_comp(rhs, lhs)
			// 		operator>=(lhs, rhs) -> !this->_comp(lhs, rhs)

			// If the map class is instantiated with the default comparison type (less), 
			// the function returns an iterator to the first element whose key is not less than k.
			iterator lower_bound (const key_type& k)
			{
				if (this->_root == this->_null)
					return (this->end());

				iterator ret = this->begin();
				for(; ret != this->end(); ++ret)
				{
					if (!this->_comp(ret->first, k)) // equivalent ret->first >= k
						break;
				}
				return ret;
			}

			const_iterator const_lower_bound (const key_type& k) const
			{
				if (this->_root == this->_null)
					return (this->end());

				const_iterator ret = this->begin();
				for(; ret != this->end(); ++ret)
				{
					if (!this->_comp(ret->first, k)) // equivalent ret->first >= k
						break;
				}
				return ret;
			}

			// If the map class is instantiated with the default comparison type (less), 
			// the function returns an iterator to the first element whose key is greater than k.
			iterator upper_bound (const key_type& k)
			{
				if (this->_root == this->_null)
					return (this->end());

				iterator ret = this->begin();
				for(; ret != this->end(); ++ret)
				{
					if (this->_comp(k, ret->first)) // equivalent ret->first > k
						break;
				}
				return ret;
			}

			const_iterator const_upper_bound (const key_type& k) const
			{
				if (this->_root == this->_null)
					return (this->end());

				const_iterator ret = this->begin();
				for(; ret != this->end(); ++ret)
				{
					if (this->_comp(k, ret->first)) // equivalent ret->first > k
						break;
				}
				return ret;
			}

			// Returns the bounds of a range that includes all the elements in the container 
			// which have a key equivalent to k.
			// Because the elements in a map container have unique keys, the range returned 
			// will contain a single element at most.
			pair<iterator,iterator> equal_range (const key_type& k)
			{
				iterator itend = this->upper_bound(k);
				iterator it;
				if (this->lower_bound(k) == this->end())
					it = this->upper_bound(k);
				else
					it = this->lower_bound(k);
				return (ft::make_pair<iterator, iterator>(it, itend));
			}

			pair<const_iterator,const_iterator> const_equal_range (const key_type& k) const
			{
				const_iterator itend = this->const_upper_bound(k);
				const_iterator it;
				if (this->const_lower_bound(k) == this->end())
					it = this->const_upper_bound(k);
				else
					it = this->const_lower_bound(k);
				return (ft::make_pair<const_iterator, const_iterator>(it, itend));
			}

			void swap(tree &x)
			{
				Node *					backup_root;
				Node *					backup_null;
				key_compare				backup_comp;
				allocator_type			backup_alloc_pair;
				allocator_type_node		backup_alloc_node;

				backup_root = this->_root;
				backup_null = this->_null;
				backup_comp = this->_comp;
				backup_alloc_pair = this->_alloc_pair;
				backup_alloc_node = this->_alloc_node;

				this->_root = x._root;
				this->_null = x._null;
				this->_comp = x._comp;
				this->_alloc_pair = x._alloc_pair;
				this->_alloc_node = x._alloc_node;

				x._root = backup_root;
				x._null = backup_null;
				x._comp = backup_comp;
				x._alloc_pair = backup_alloc_pair;
				x._alloc_node = backup_alloc_node;
			}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Utils~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//----------------------------------------Node utils----------------------------------------
			// Two allcoator used to be able to deconstruct and reconstruct the key value of a node
			// _alloc_pair is the one given in the tempate, alloc_node allocates memory for the node
			// This function returns a newly allocated node with as value_type i
			Node * new_node(value_type i)
			{
				Node *node = this->_alloc_node.allocate(1);
				this->_alloc_pair.construct(&node->data, i);
				node->left = this->_null;
				node->right = this->_null;
				node->parent = NULL;
				node->height = 1;
				return (node);
			}

			// Returns the biggest out of two size_t
			size_type	max(size_type a, size_type b)
			{
				return (this->_comp(b, a)) ? a : b;
			}

			// Returns the height of a node and updates the _node->height variable of the node 
			// given as a parameter
			// The height of a node is the number of edges on the longest path from that node 
			// to a leaf node. As such, the height of the tree would be the height of 
			// its root node. Meanwhile, the leaf nodes have a height of 0.
			size_type height(Node *node)
			{
				if (node == this->_null) // null ptr
					node->height = 0;
				else if (node->left == this->_null && node->right == this->_null) // leaf
					node->height = 1;
				else if (node->left == this->_null && node->right != this->_null) // node has only a right child
					node->height = node->right->height + 1;
				else if (node->left != this->_null && node->right == this->_null) // node has only a left child
					node->height = node->left->height + 1;
				else
					node->height = max(node->left->height, node->right->height) + 1; 
				return node->height;
			}

			// The balance of a node is the difference between the height of its left child and the 
			// height of its right child
			difference_type get_balance(Node *node)
			{
				if(!node || node == this->_null)
					return 0;
				return height(node->left) - height(node->right);
			}

		//----------------------------------------Min max prev next----------------------------------------
			// returns the node with the heighest key value
			Node * max_val_node(Node *node) const 
			{
				if (node->right && node->right != this->_null)
					return max_val_node(node->right);
				return node;
			}

			// returns the node with the lowest key value
			Node* min_val_node(Node *node) const
			{
				if (node->left && node->left != this->_null)
					return min_val_node(node->left);
				return node;
			}

			// Returns the node coming next after the one given in param (according to the key values)
			Node* find_next(Node * node) const
			{
				Node * next;
				if (node->right == this->_null) // if the node does not have a right child, the next one has to be upper in the tree
				// We go up and check if the node is a right child of its parent. If it's the case we keep on going up
				{
					next = node;
					while (next->parent && next == next->parent->right)
						next = next->parent;
					next = next->parent;
				}
				else // if the node has a right child, the next node has to be lower in the tree. We move to the right subtree
				// and to the left until reaching a leaf
				{
					next = node->right;
					while (next->left != this->_null)
						next = next->left;
				}
				return (next);
			}

			// Returns the node coming before the one given in param (according to the key values)
			// Same method as before except we look left when we looked right and vice versa
			Node* find_prev(Node * node) const
			{
				Node * prev;
				if (node->left == this->_null)
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

		//----------------------------------------Tree balancing----------------------------------------
			// T1, T2 and T3 are subtrees of the tree 
			// rooted with y (on the left side) or x (on 
			// the right side)           
			// 	y                               x
			// 	/ \     Right Rotation          /  
			// x   T3   - - - - - - - >        T1   y 
			// / \       < - - - - - - -            / 
			// T1  T2     Left Rotation            T2  T3
			// Keys in both of the above trees follow the 
			// following order 
			// keys(T1) < key(x) < keys(T2) < key(y) < keys(T3)

			Node * rotate_right(Node * y)
			{
				Node * x = y->left;
				Node * subtree = x->right;
				
				Node * backup_y_parent = y->parent;

				x->right = y;
				y->left = subtree;

				x->height = height(x);
				y->height = height(y);
				subtree->height = height(subtree);

				y->parent = x;
				x->parent = backup_y_parent;
				subtree->parent = y;

				if(x->parent == NULL) // update root
					this->_root = x;

				return (x);
			}

			Node * rotate_left(Node * x)
			{
				Node * y = x->right;
				Node * subtree = y->left;
				
				Node * backup_x_parent = x->parent;

				y->left = x;
				x->right = subtree;

				x->height = height(x);
				y->height = height(y);
				subtree->height = height(subtree);


				x->parent = y;
				y->parent = backup_x_parent;
				subtree->parent = x;
				
				if(y->parent == NULL) // update root
					this->_root = y;
				return (y);
			}
			
			// Re-balance the tree by performing appropriate rotations on the subtree rooted with z.
			// There can be 4 possible cases that needs to be handled as x, y and z can be arranged 
			// in 4 ways. Following are the possible 4 arrangements: 
			// 	a) y is left child of z and x is left child of y (Left Left Case) 
			// 	b) y is left child of z and x is right child of y (Left Right Case) 
			// 	c) y is right child of z and x is right child of y (Right Right Case) 
			// 	d) y is right child of z and x is left child of y (Right Left Case)

			// 1) Update the height of the current node.
			// 2) Get the balance factor (left subtree height – right subtree height) of the current node. 
			// 3) If balance factor is greater than 1, then the current node is unbalanced and we are either in Left Left case or left Right case. 
			// 	If balance factor is less than -1, then the current node is unbalanced and we are either in Right Right case or Right-Left case. 
			Node *balance_tree(Node * node)
			{
				node->height = height(node);
				difference_type balance = get_balance(node);
				if(balance > 1 && get_balance(node->left) >= 0) // left left
				{
					node = rotate_right(node);
				}
				if(balance > 1 && get_balance(node->left) < 0) // left right
				{
					node->left = rotate_left(node->left);
					node = rotate_right(node);
				}
				if(balance < -1 && get_balance(node->right) <= 0) // right right
				{
					node = rotate_left(node);
				}
				if(balance < -1 && get_balance(node->right) > 0) // right left
				{
					node->right = rotate_right(node->right);
					node = rotate_left(node);
				}
				return (node);
			}

		//----------------------------------------Insert delete----------------------------------------
			// https://www.geeksforgeeks.org/avl-tree-set-1-insertion/
			Node *insert_node(Node *node, value_type i)
			{
				if(this->_root == this->_null) // In case empty tree 
				{
					this->_root = new_node(i);
					return (this->_root);
				}
				if(node == this->_null) // when we have reached a leaf we can allocate memory for the new node
				{
					node = new_node(i);
					return (node);
				}

				// recursively going down the tree (left or right according to the key value)
				if (this->_comp(i.first, node->data.first))// (i.first < node->data.first)
				{
					node->left = insert_node(node->left, i);
					node->left->parent = node;
				}
				else if (this->_comp(node->data.first, i.first)) // (i.first > node->data.first)
				{
					node->right = insert_node(node->right, i);
					node->right->parent = node;
				}
				return(balance_tree(node)); // each time the function is called a rebalancing is made
			}

			// https://www.geeksforgeeks.org/avl-tree-set-2-deletion/
			Node * delete_node(Node * node, key_type i)
			{
				if (this->_root == this->_null) // in case the tree is empty
				{
					return (this->_root);
				}
				if (node == this->_null)
				{
					return (node);
				}

				//Same as for insert, recursively go down until we find the node to delete
				if (this->_comp(i, node->data.first)) // (i < node->data.first)
				{
					node->left = delete_node(node->left, i);
				}
				else if (this->_comp(node->data.first, i)) // (i > node->data.first)
				{
					node->right = delete_node(node->right, i);
				}

				else // if value is the same as node data : node is the node to delete
				{
					Node * tmp = this->_null;
					if (node->left == this->_null || node->right == this->_null) // if there is only one child or no children
					{
						tmp = node->left != this->_null ? node->left : node->right;
						if (tmp == this->_null) // no children
						{
							tmp = node;
							node = this->_null;
						}
						else // one child
						{
							if (node->left != this->_null) // left child
							{
								Node * backup_parent = node->parent;
								tmp = node;
								node = node->left;
								node->parent = backup_parent;
							}
							else if (node->right != this->_null) // right child 
							{
								Node * backup_parent = node->parent;
								tmp = node;
								node = node->right;
								node->parent = backup_parent;
							}
						}
						if (tmp->parent == NULL && tmp->left == this->_null && tmp->right == this->_null) // mean we are left with root only
						{
							_alloc_pair.destroy(&tmp->data);
							_alloc_node.deallocate(tmp, 1);
							this->_root = this->_null;
						}
						else
						{
							if (this->_root == tmp) // update the root if needed (so that we don't end up with a rootless tree)
								this->_root = node;
							_alloc_pair.destroy(&tmp->data);
							_alloc_node.deallocate(tmp, 1);
						}
					}
					else if (node->left != this->_null && node->right != this->_null)// if there are two children
					// since the value_type : ft::pair<const Key,T>	data; has a const key, we need to destroy the pair and construct
					// it again with a new value
					{
						tmp = min_val_node(node->right); 
						_alloc_pair.destroy(&node->data); 
						_alloc_pair.construct(&node->data, tmp->data);
						node->right = delete_node(node->right, node->data.first);
					}
				}

				if (node == this->_null)
				{
					return node;
				}
				return(balance_tree(node));
			}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Debug~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
			void preOrder(Node *root)
			{
				if(root != this->_null)
				{
					std::cout << "----------------------------------------" << std::endl;
					std::cout << "| Node            | " << root->data.first << "                   |" << std::endl;
					std::cout << "| Adresse node    | " << &root << "      |" << std::endl;
					std::cout << "| Height          | " << root->height << "                   |" << std::endl;
					if(root->parent && root->parent != this->_null)
					{
						std::cout << "| Parent          | " << root->parent->data.first << "                   |" << std::endl;
						Node * next = find_next(root);
						Node * prev = find_prev(root);
						if (next)
							std::cout << "| Next            | " << next->data.first << "                   |" << std::endl;
						else
							std::cout << "| Next            | None                |" << std::endl;
						if(prev)
							std::cout << "| Prev            | " << prev->data.first << "                   |" << std::endl;
						else
							std::cout << "| Prev            | None                |" << std::endl;
					}
					if(root->left != this->_null)
						std::cout << "| Left child      | " << root->left->data.first << "                   |" << std::endl;
					else
						std::cout << "| Left child      | None                |" << std::endl;
					if(root->right != this->_null)
						std::cout << "| Right child     | " << root->right->data.first << "                   |" << std::endl;
					else
						std::cout << "| Right child     | None                |" << std::endl;
					std::cout << "----------------------------------------" << std::endl;
					std::cout << std::endl;
					preOrder(root->left);
					preOrder(root->right);
				}
			}

			struct Trunk
			{
				Trunk *prev;
				std::string str;

				Trunk(Trunk *prev, std::string str)
				{
					this->prev = prev;
					this->str = str;
				}
			};

			void showTrunks(Trunk *p)
			{
				if (p == nullptr) {
					return;
				}

				showTrunks(p->prev);
				std::cout << p->str;
			}

			void printTree(Node* root, Trunk *prev, bool isLeft, bool type)
			{
				if (root == nullptr) {
					return;
				}

				std::string prev_str = "    ";
				Trunk *trunk = new Trunk(prev, prev_str);

				printTree(root->right, trunk, true, type);

				if (!prev) {
					trunk->str = "———";
				}
				else if (isLeft)
				{
					trunk->str = "/———";
					prev_str = "   |";
				}
				else {
					trunk->str = "\\———";
					prev->str = prev_str;
				}

				showTrunks(trunk);
				if (type )
					std::cout << " " << root->data.second << std::endl;
				else
					std::cout << " " << root->data.first << std::endl;
				if (prev) {
					prev->str = prev_str;
				}
				trunk->str = "   |";

				printTree(root->left, trunk, false, type);
			}
	};
}

#endif
