#include <iostream>
#include "../ft_containers.hpp"
#include "rbt_iterators.hpp"

#ifndef _RED_BLACK_TREE_HPP_
#define _RED_BLACK_TREE_HPP_

template <class Key, class T>
class rbt_iterator;

namespace ft
{
	typedef enum {RED, BLACK} Color;
	typedef enum {LEFT, RIGHT} Side;

	template <class Key, class T>
	struct Node
	{
		ft::pair<Key, T>	data;
		Color				color;
		Node				*parent, *left, *right;

		Node() : parent(NULL), left(NULL), right(NULL)
		{}

		Node(Key key, T data) : data(ft::make_pair(key, data)), color(RED), parent(NULL), left(NULL), right(NULL)
		{}

		Node (const Node& other) : data(other.data), color(other.color), parent(other.parent), left(other.left), right(other.right)
		{}

		~Node() {}

		Node& operator=(const Node& other)
		{
			if (this != &other)
			{
				data = other.data;
				color = other.color;
				parent = other.parent;
				left = other.left;
				right = other.right;
			}
			return (*this);
		}

		bool operator==(const Node& other) const
		{
			return (data == other.data && color == other.color && parent == other.parent && left == other.left && right == other.right);
		}

		bool operator!=(const Node& other) const
		{
			return (!(*this == other));
		}

		bool isLeftChild() const
		{
			return (this == parent->left);
		}

		Node *sibling() const
		{
			if (parent == NULL)
				return NULL;

			if (isLeftChild())
				return (parent->right);
			else
				return (parent->left);
		}

		Node *uncle() const
		{
			if (parent == NULL || parent->parent == NULL)
				return (NULL);

			return (this->parent->sibling());
		}

		bool hasRedChild() const
		{
			return ((left && left->color == RED) || (right && right->color == RED));
		}

		void moveDown(Node *newParent)
		{
			if (parent != NULL)
			{
				if (isLeftChild())
					parent->left = newParent;
				else
					parent->right = newParent;
			}
			newParent->parent = parent;
			parent = newParent;
		}

		Node *successor()
		{
			if (this->right == NULL)
				return (NULL);

			else if (this->right->left == NULL)
				return (this->right);

			else if (this->right->left != NULL)
				return (this->right->left);

			else
				return (NULL);
		}

		Node *predecessor()
		{
			if (this->left == NULL)
				return (NULL);

			if (this->left->right == NULL)
				return (this->left);

			else if (this->left->right != NULL)
				return (this->left->right);

			else
				return (NULL);
		}
	};

	template <
				class Key,
				class T,
				class Compare = std::less<Key>,
				class Allocator = std::allocator< ft::pair<const Key,T> >
			 >
	class RBT
	{
		public:
			typedef Key														key_type;
			typedef T														mapped_type;
			typedef ft::pair<const key_type, mapped_type>					value_type;
			typedef Compare													key_compare;
			typedef bool													value_compare;
			typedef typename Allocator::template rebind<value_type>::other	allocator_type;
			typedef typename std::size_t									size_type;
			typedef Node<key_type, mapped_type>								node_type;
			typedef Node<key_type, mapped_type> const						const_node_type;
			typedef Node<key_type, mapped_type>*							node_ptr;
			typedef Node<key_type, mapped_type>* const						const_node_ptr;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename std::ptrdiff_t	 								difference_type;
			// typedef typename std::bidirectional_iterator_tag				iterator_category;
			typedef rbt_iterator<key_type, mapped_type>					iterator;
			typedef rbt_iterator<key_type, const mapped_type>			const_iterator;





			RBT(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : root_(NULL), alloc_(allocator_type()), size_(0), comp_(key_compare())
			{}

			RBT(const RBT& other) : root_(NULL), alloc_(other.alloc_), size_(0), comp_(other.comp_)
			{
				*this = other;
			}

			~RBT()
			{
				clear();
			}

		private:
			node_ptr		root_;
			allocator_type	alloc_;
			size_type		size_;
			Compare			comp_;

		void rotate(node_ptr ptr, Side direction)
		{
			node_ptr	child = ((direction == RIGHT) ? ptr->left : ptr->right);

			if (ptr == root_)
				root_ = child;

			ptr->moveDown(child);

			if (direction == RIGHT)
			{
				ptr->left = child->right;
				if (child->right)
					child->right->parent = ptr;
				child->right = ptr;
			}
			else
			{
				ptr->right = child->left;
				if (child->left)
					child->left->parent = ptr;
				child->left = ptr;
			}
		}

		void fixRedRed(node_ptr ptr)
		{
			if (ptr == root_)
			{
				ptr->color = BLACK;
				return;
			}

			node_ptr parent = ptr->parent;
			node_ptr grand_parent = parent->parent;
			node_ptr uncle = ptr->uncle();

			if (parent->color != BLACK)
			{
				if (uncle != NULL && uncle->color == RED)
				{
					parent->color = BLACK;
					uncle->color = BLACK;
					grand_parent->color = RED;
					fixRedRed(grand_parent);
				}
				else
				{
					if (parent->isLeftChild())
					{
						if (ptr->isLeftChild())
							std::swap(parent->color, grand_parent->color);
						else
						{
							rotate(parent, LEFT);
							std::swap(ptr->color, grand_parent->color);
						}
						rotate(grand_parent, RIGHT);
					}
					else
					{
						if (ptr->isLeftChild())
						{
							rotate(parent, RIGHT);
							std::swap(ptr->color, grand_parent->color);
						}
						else
							std::swap(parent->color, grand_parent->color);
						rotate(grand_parent, LEFT);
					}
				}
			}
		}

		node_ptr	searchNode(node_ptr ptr, T value)
		{
			if (ptr == NULL)
				return (NULL);
			if (value < ptr->data)
			{
				if (ptr->left == NULL)
					return (ptr);
				else
					return (searchNode(ptr->left, value));
			}
			else if (value > ptr->data)
			{
				if (ptr->right == NULL)
					return (ptr);
				else
					return (searchNode(ptr->right, value));
			}
			else
				return (ptr);
		}

		bool	checkNodeColor(node_ptr root, T value) const
		{
			if (root == NULL)
				return (false);

			if (value == root->data)
				return (root->color);

			else if (value < root->data)
				return (checkNodeColor(root->left, value));

			else if (value > root->data)
				return (checkNodeColor(root->right, value));

			return (false);
		}

		node_ptr	findSuccessor(node_ptr ptr)
		{
			Node<const key_type, mapped_type> * curr = ptr;

			while (curr && curr->left)
				curr = curr->left;

			return (curr);
		}

		node_ptr	findReplacement(node_ptr ptr)
		{
			if (ptr->left && ptr->right)
				return (findSuccessor(ptr->right));
			if (ptr->left == NULL && ptr->right == NULL)
				return (NULL);
			if (ptr->left)
				return (ptr->left);
			else
				return (ptr->right);
		}

		void freeNode(node_ptr toFree)
		{
			if (!toFree || !toFree->parent)
				return;
			alloc_.destroy(toFree);
			alloc_.deallocate(toFree, 1);
			toFree = NULL;
		}

		void fixDoubleBlack(node_ptr ptr)
		{
			if (ptr == root_)
				return;

			node_ptr	sibling = ptr->sibling();
			node_ptr	parent = ptr->parent;

			if (sibling == NULL)
				fixDoubleBlack(parent);
			else
			{
				if (sibling->color == RED)
				{
					parent->color = RED;
					sibling->color = BLACK;
					if (sibling->isLeftChild())
						rotate(parent, RIGHT);
					else
						rotate(parent, LEFT);
					fixDoubleBlack(ptr);
				}
				else
				{
					if (sibling->hasRedChild())
					{
						if (sibling->left != NULL && sibling->left->color == RED)
						{
							if (sibling->isLeftChild())
							{
							sibling->left->color == sibling->color;
							sibling->color = parent->color;
							rotate(parent, RIGHT);
							}
							else
							{
								sibling->left->color = parent->color;
								rotate(sibling, RIGHT);
								rotate(parent, LEFT);
							}
						}
						else
						{
							if (sibling->isLeftChild())
							{
								sibling->right->color = parent->color;
								rotate(sibling, LEFT);
								rotate(parent, RIGHT);
							}
							else
							{
								sibling->right->color = sibling->color;
								sibling->color = parent->color;
								rotate(parent, LEFT);
							}
						}
						parent->color = BLACK;
					}
					else
					{
						sibling->color = RED;
						if (parent->color == BLACK)
							fixDoubleBlack(parent);
						else
							parent->color = BLACK;
					}
				}
			}
		}

		void deleteNode(node_ptr toDelete)
		{
			node_ptr	toReplace = findReplacement(toDelete);
			node_ptr	parent = toDelete->parent;
			bool bothBlack = ((toReplace == NULL || toReplace->color == BLACK) && (toDelete->color == BLACK));

			if (toReplace == NULL) //toDelete is leaf
			{
				if (toDelete == root_)
					root_ = NULL;
				else
				{
					if (bothBlack)
					fixDoubleBlack(toReplace);
					else
					{
						if (toDelete->uncle() != NULL)
							toDelete->uncle()->color = RED;
					}
					if (toDelete->isLeftChild())
					parent->left = NULL;
					else
						parent->right = NULL;
				}
				freeNode(toDelete);
				return;
			}
			else if (toDelete->left == NULL || toDelete->right == NULL) //toDelete has a child
			{
				if (toDelete == root_)
				{
					toDelete->data = toReplace->data;
					toDelete->left = toDelete->right = NULL;
					freeNode(toReplace);
				}
				else
				{
					if (toDelete->isLeftChild())
						parent->left = toReplace;
					else
						parent->right = toReplace;
					freeNode(toDelete);
					toReplace->parent = parent;
					if (bothBlack)
						fixDoubleBlack(toReplace);
					else
						toReplace->color = BLACK;
				}
				return;
			}
			else //toDelete has 2 children
			{
				std::swap(toDelete->data, toReplace->data);
				deleteNode(toDelete);
			}
		}

		public:

			bool empty() const
			{
				return (root_ == NULL);
			}

			size_type size() const
			{
				return (size_);
			}

			size_type max_size() const
			{
				return (alloc_.max_size());
			}


		iterator begin()
		{
			node_ptr tmp = root_;
			if (tmp == NULL)
				return (iterator(tmp));
			while (tmp->left != NULL)
				tmp = tmp->left;
			return (iterator(tmp));
		}

		iterator end()
		{
			return (iterator(NULL));
		}

		iterator rbegin()
		{
			node_ptr tmp = root_;
			if (tmp == NULL)
				return (iterator(tmp));
			while (tmp->right != NULL)
				tmp = tmp->right;
			return (iterator(tmp));
		}

		iterator rend()
		{
			return (iterator(NULL));
		}

		const_iterator cbegin() const
		{
			node_ptr tmp = root_;
			if (tmp == NULL)
				return (iterator(tmp));
			while (tmp->left != NULL)
				tmp = tmp->left;
			return (const_iterator(tmp));
		}

		const_iterator cend() const
		{
			return (const_iterator(NULL));
		}

		const_iterator crbegin() const
		{
			node_ptr tmp = root_;
			if (tmp == NULL)
				return (iterator(tmp));
			while (tmp->right != NULL)
				tmp = tmp->right;
			return (const_iterator(tmp));
		}

		const_iterator crend() const
		{
			return (const_iterator(NULL));
		}

		ft::pair<iterator, bool> insert(const value_type& val)
		{
			node_ptr leafNode = searchNode(root_ ,val.first);

			if (leafNode && leafNode->key == val.first)
				return (ft::make_pair(iterator(leafNode), false));

			node_ptr newNode = alloc_.allocate(1);
			alloc_.construct(newNode, val.first, val.second);

			if (root_ == NULL)
			{
				root_ = newNode;
				root_->color = BLACK;
				size_++;
				return (ft::make_pair(iterator(newNode), true));
			}

			newNode->parent = leafNode;
			if (val.first < leafNode->key)
				leafNode->left = newNode;
			else
				leafNode->right = newNode;

			fixRedRed(newNode);
			size_++;
			return (ft::make_pair(iterator(newNode), true));
		}

		iterator insert(iterator position, const value_type& val)
		{
			(void)position;
			return (insert(val).first);
		}

		template <class InputIterator>
		void insert(InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
				first++;
			}
		}

		void erase(iterator position)
		{
			deleteNode(position.node_);
			size_--;
		}

		size_type erase(const key_type& k)
		{
			if (root_ == NULL)
				return (0);
			node_ptr found = searchNode(root_, k);
			if (found->key == k)
			{
				deleteNode(found);
				size_--;
				return (1);
			}
			return (0);
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
			{
				iterator tmp = first;
				first++;
				erase(tmp);
			}
		}

		void swap(RBT& x)
		{
			node_ptr tmp = root_;
			root_ = x.root_;
			x.root_ = tmp;
		}

		void clear()
		{
			erase(begin(), end());
		}

		key_compare key_comp() const
		{
			return (comp_);
		}

		value_compare value_comp() const
		{
			return (comp_);
		}

		iterator find(const key_type& k)
		{
			node_ptr found = searchNode(root_, k);
			if (found->key == k)
				return (iterator(found));
			return (end());
		}

		const_iterator find(const key_type& k) const
		{
			node_ptr found = searchNode(root_, k);
			if (found->key == k)
				return (const_iterator(found));
			return (const_iterator(end()));
		}

		size_type count(const key_type& k) const
		{
			if (root_ == NULL)
				return (0);
			node_ptr found = searchNode(root_, k);
			if (found->key == k)
				return (1);
			return (0);
		}

		iterator lower_bound(const key_type& k)
		{
			node_ptr found = searchNode(root_, k);
			if (found->key == k)
				return (iterator(found));
			if (found->key < k)
				return (iterator(found->right));
			return (iterator(found));
		}

		const_iterator lower_bound(const key_type& k) const
		{
			node_ptr found = searchNode(root_, k);
			if (found->key == k)
				return (const_iterator(found));
			if (found->key < k)
				return (const_iterator(found->right));
			return (const_iterator(found));
		}

		iterator upper_bound(const key_type& k)
		{
			node_ptr found = searchNode(root_, k);
			if (found->key == k)
				return (iterator(found->right));
			if (found->key < k)
				return (iterator(found->right));
			return (iterator(found));
		}

		const_iterator upper_bound(const key_type& k) const
		{
			node_ptr found = searchNode(root_, k);
			if (found->key == k)
				return (const_iterator(found->right));
			if (found->key < k)
				return (const_iterator(found->right));
			return (const_iterator(found));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type& k) const
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		ft::pair<iterator,iterator> equal_range(const key_type& k)
		{
			return (ft::make_pair(lower_bound(k), upper_bound(k)));
		}

		void deleteNode(T value)
		{
			if (root_ == NULL)
				return;

			node_ptr found = searchNode(root_, value);
			if (found->data == value)
			{
				deleteNode(found);
				size_--;
			}
		};

		bool	checkNodeColor(T value) const {return (checkNodeColor(root_, value));};

	// getter for visualizer
		node_ptr	get_root(){return root_;}

		// operator overloading

		RBT& operator=(const RBT& other)
		{
			if (this != &other)
			{
				clear();
				root_ = copy(other.root_);
				size_ = other.size_;
			}
			return (*this);
		}

		bool operator< (const RBT<const key_type, mapped_type> &other) const
		{
			return (comp_(this->root_->data.first, other.root_->data.first));
		}

		bool operator> (const RBT<const key_type, mapped_type> &other) const
		{
			return (comp_(other.root_->data.first, this->root_->data.first));
		}

		bool operator<= (const RBT<const key_type, mapped_type> &other) const
		{
			return (!(*this > other));
		}

		bool operator>= (const RBT<const key_type, mapped_type> &other) const
		{
			return (!(*this < other));
		}

		bool operator== (const RBT<const key_type, mapped_type> &other) const
		{
			return (!(*this < other) && !(*this > other));
		}

		bool operator!= (const RBT<const key_type, mapped_type> &other) const
		{
			return (!(*this == other));
		}

		RBT<const key_type, mapped_type> &operator=(const RBT<const key_type, mapped_type> &other)
		{
			if (this == &other)
				return (*this);
			this->root_ = other.root_;
			return (*this);
		}
	};
}

#endif
