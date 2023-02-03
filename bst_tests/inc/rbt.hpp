#include <iostream>
#include "../../includes/ft_containers.hpp"

#ifndef _RBT_HPP_
#define _RBT_HPP_

namespace ft
{
	typedef enum {RED, BLACK} Color;
	typedef enum {LEFT, RIGHT} Side;

	template <class T>
	struct Node
	{
		T		data;
		Color	color;
		Node	*parent, *left, *right;

		Node(T data) : data(data), color(RED), parent(NULL), left(NULL), right(NULL)
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

		bool isLeftChild() const
		{
			return (this == parent->left);
		}

		Node *uncle() const
		{
			if (parent == NULL || parent->parent == NULL)
		return NULL;
			return (parent->uncle());
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
	};

	template <class T, class Allocator = std::allocator<T> >
	class RBT
	{
		public:
			typedef T		 												value_type;
			typedef typename Allocator::template rebind<Node<T> >::other	allocator_type;
			typedef Node<T>*												node_ptr;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename std::size_t									size_type;
			typedef typename std::ptrdiff_t	 								difference_type;
			typedef typename ft::random_access_iterator<pointer>			iterator;
			typedef typename ft::random_access_iterator<const_pointer>		const_iterator;
			typedef typename ft::reverse_iterator<pointer>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_pointer>			const_reverse_iterator;

		RBT(){root_ = NULL;}

		private:
			Node<T>*		root_;
			allocator_type	alloc_;

// void fixSide(node_ptr root, node_ptr ptr, node_ptr parent, node_ptr grand_parent, Side side)
			// {
			//	 node_ptr uncle = NULL;

			//	 if (side == LEFT)
			//	 uncle = grand_parent->right;
			//	 else
			//	 uncle = grand_parent->left;

			//	 if (uncle != NULL && uncle->color == RED)
			//	 {
			//	 parent->color = BLACK;
			//	 uncle->color = BLACK;
			//	 grand_parent->color = RED;
			//	 ptr = grand_parent;
			//	 }
			//	 else
			//	 {
			//	 if (side == LEFT)
			//	 {
			//		 if (!ptr->isLeftChild())
			//		 {
			//	 rotate(parent, LEFT);
			//	 ptr = parent;
			//	 parent = ptr->parent;
			//		 }
			//		 rotate(grand_parent, RIGHT);
			//	 }
			//	 else
			//	 {
			//		 if (ptr->isLeftChild())
			//		 {
			//	 rotate(parent, RIGHT);
			//	 ptr = parent;
			//	 parent = ptr->parent;
			//		 }
			//		 rotate(grand_parent, LEFT);
			//	 }
			//	 std::swap(parent->color, grand_parent->color);
			//	 ptr = parent;
			//	 }
			// }

			// void fixViolation(node_ptr ptr)
			// {
			//	 node_ptr parent = NULL;

			//	 while ((ptr != root_) && (ptr->color != BLACK) && (ptr->parent->color == RED))
			//	 {
			//	 parent = ptr->parent;

			//	 if (parent->isLeftChild())
			//		 fixSide(ptr, parent, LEFT);
			//	 else
			//		 fixSide(ptr, parent, RIGHT);
			//	 }
			//	 root_->color = BLACK;
			// }

		void rotate(node_ptr ptr, Side direction)
		{
			node_ptr	child = (direction == RIGHT) ? ptr->left : ptr->right;

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

		node_ptr	searchNode(T value)
		{
			node_ptr tmp = root_;

			while (tmp != NULL)
			{
				if (value < tmp->data)
				{
					if (tmp->left == NULL)
						break;
					else
						tmp = tmp->left;
				}
				else if (value > tmp->data)
				{
					if (tmp->right == NULL)
						break;
					else
						tmp = tmp->right;
				}
				else
					break;
			}
			return (tmp);
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
			Node<T> * curr = ptr;

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

			node_ptr	uncle = ptr->uncle();
			node_ptr	parent = ptr->parent;

			if (uncle == NULL)
				fixDoubleBlack(parent);
			else
			{
				if (uncle->color == RED)
				{
					parent->color = RED;
					uncle->color = BLACK;
					if (uncle->isLeftChild())
						rotate(parent, RIGHT);
					else
						rotate(parent, LEFT);
					fixDoubleBlack(ptr);
				}
				else
				{
					if (uncle->hasRedChild())
					{
						if (uncle->left != NULL && uncle->left->color == RED)
						{
							if (uncle->isLeftChild())
							{
							uncle->left->color == uncle->color;
							uncle->color = parent->color;
							rotate(parent, RIGHT);
							}
							else
							{
								uncle->left->color = parent->color;
								rotate(uncle, RIGHT);
								rotate(parent, LEFT);
							}
						}
						else
						{
							if (uncle->isLeftChild())
							{
								uncle->right->color = parent->color;
								rotate(uncle, LEFT);
								rotate(parent, RIGHT);
							}
							else
							{
								uncle->right->color = uncle->color;
								uncle->color = parent->color;
								rotate(parent, LEFT);
							}
						}
						parent->color = BLACK;
					}
					else
					{
						uncle->color = RED;
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

		void insert(T data)
		{
			node_ptr leafNode = searchNode(data);

			if (leafNode && leafNode->data == data)
				return;

			node_ptr newNode = alloc_.allocate(1);
			alloc_.construct(newNode, data);

			if (root_ == NULL)
			{
				root_ = newNode;
				root_->color = BLACK;
				return;
			}

			newNode->parent = leafNode;
			if (data < leafNode->data)
				leafNode->left = newNode;
			else
				leafNode->right = newNode;

			fixRedRed(newNode);
			// fixViolation(root_, newNode);
		}

		void deleteNode(T value)
		{
			if (root_ == NULL)
				return;

			node_ptr found = searchNode(value);
			if (found->data == value)
				deleteNode(found);
		};

		bool	checkNodeColor(T value) const {return (checkNodeColor(root_, value));};

	// getter for visualizer
		node_ptr	get_root(){return root_;}

		// operator overloading
		bool operator==(const RBT<T> &other) const
		{
			if (this == &other)
				return (true);
			return (this->root_ == other.root_);
		}

		bool operator!=(const RBT<T> &other) const
		{
			return (!(*this == other));
		}

		RBT<T> &operator=(const RBT<T> &other)
		{
			if (this == &other)
				return (*this);
			this->root_ = other.root_;
			return (*this);
		}

		// destructor
		~RBT(){};
	};
}
#endif
