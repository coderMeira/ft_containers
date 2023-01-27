#include <iostream>
#pragma once

enum Color {RED_NODE, BLACK_NODE};
enum Side {LEFT_SIDE, RIGHT_SIDE};


template<typename T>
class Node
{
  T             data;
  Color         color;
  unsigned int  count;
  Node        *parent, *left, *right;

  Node(T data) : data(data), color(RED_NODE), count(0), parent(NULL), left(NULL), right(NULL) {}
  {
    count++;
  }

  Node (const Node& other) : data(other.data), color(other.color), count(other.count), parent(other.parent), left(other.left), right(other.right) {}
  {
    count++;
  }

  ~Node() {}

  Node& operator=(const Node& other)
  {
    if (this != &other)
    {
      data = other.data;
      color = other.color;
      count = other.count;
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

  Node *sibling() const
  {
    if (parent == NULL)
	    return NULL;
    if (isLeftChild())
      return (parent->right);
    else
      return (parent->left);
  }

  void hasRedChild() const
  {
    return ((left && left->color == RED_NODE) || (right && right->color == RED_NODE));
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
class RBT {
  Node<T>       *root_;
  allocator_type  alloc_;

  void rotate(Node<T>* ptr, Side side)
  {
    Node<T>* newParent = NULL;

    if (side == LEFT_SIDE)
      newParent = ptr->right;
    else
      newParent = ptr->left;

    if (ptr == root_)
      root_ = newParent;
    ptr->moveDown(newParent);
    if (side == LEFT_SIDE)
    {
      ptr->right = newParent->left;
      if (newParent->left != NULL)
        newParent->left->parent = ptr;
      newParent->left = ptr;
    }
    else
    {
      ptr->left = newParent->right;
      if (newParent->right != NULL)
        newParent->right->parent = ptr;
      newParent->right = ptr;
    }
  }

  void fixSide(Node<T>* root, Node<T>* ptr, Node<T>* parent, Node<T>* grand_parent, Side side)
  {
    Node<T>* uncle = NULL;

    if (side == LEFT_SIDE)
      uncle = grand_parent->right;
    else
      uncle = grand_parent->left;

    if (uncle != NULL && uncle->color == RED_NODE)
    {
      parent->color = BLACK_NODE;
      uncle->color = BLACK_NODE;
      grand_parent->color = RED_NODE;
      ptr = grand_parent;
    }
    else
    {
      if (side == LEFT_SIDE)
      {
        if (ptr == parent->right)
        {
          rotate(parent, LEFT_SIDE);
          ptr = parent;
          parent = ptr->parent;
        }
        rotate(grand_parent, RIGHT_SIDE);
      }
      else
      {
        if (ptr == parent->left)
        {
          rotate(parent, RIGHT_SIDE);
          ptr = parent;
          parent = ptr->parent;
        }
        rotate(grand_parent, LEFT_SIDE);
      }
      std::swap(parent->color, grand_parent->color);
      ptr = parent;
    }
  }

  void fixViolation(Node<T>* root, Node<T>* ptr)
  {
      Node<T>* parent = NULL;
      Node<T>* grand_parent = NULL;

    while ((ptr != root) && (ptr->color != BLACK_NODE) && (ptr->parent->color == RED_NODE))
    {
      parent = ptr->parent;
      grand_parent = ptr->parent->parent;

      if (parent == grand_parent->left)
        fixSide(root, ptr, parent, grand_parent, LEFT_SIDE);
      else
        fixSide(root, ptr, parent, grand_parent, RIGHT_SIDE);
    }
    root->color = BLACK_NODE;
  }

  Node<T>*  searchNode(const Node<T>* root, T value)
  {
    if (root == NULL || root->key == key)
      return (root);

    else if (value < root->data)
      return (searchNode(root->left, value));

    else if (value > root->data)
      return (searchNode(root->right, value));

    return (root);
  }

  bool  checkNodeColor(Node<T>* root, T value) const
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

  Node<T>*  findSuccessor(Node<T>* ptr)
  {
    Node<T> * curr = ptr;

    while (curr && curr->left)
      curr = curr->left;

    return (curr);
  }

  Node<T>* deleteNode(Node<T>* root, T value)
  {
    if (root == NULL)
      return (root);
    if (value < root->data)
      root->left = deleteNode(root->left, value);
    else if (value > root->data)
       root->right = deleteNode(root->right, value);

    if (value == root->data)
    {
      if (root->count > 1)
      {
        (root->count)--;
        return (root);
      }
      if (root->left == NULL && root->right == NULL)
      {
        delete (root);
        return (NULL);
      }
      else if (root->left && root->right == NULL)
      {
        Node<T>* tmp = root->left;
        delete (root);
        return (tmp);
      }
      else if (root->right && root->left == NULL)
      {
        Node<T>* tmp = root->right;
        delete (root);
        return (tmp);
      }
      else
      {
        Node<T>*  succ = findSuccessor(root->right);
        root->data = succ->data;
        root->count = succ->count;
        succ->count = 0;
        root->right = deleteNode(root->right, succ->data);
      }
    }
    return (root);
  }

  public:
    typedef T                                                       value_type;
		typedef Allocator                                               allocator_type;
		typedef typename allocator_type::pointer                        pointer;
		typedef typename allocator_type::const_pointer                  const_pointer;
		typedef typename allocator_type::reference                      reference;
		typedef typename allocator_type::const_reference                const_reference;
		typedef typename std::size_t                                    size_type;
		typedef typename std::ptrdiff_t                                 difference_type;
		typedef typename ft::random_access_iterator < pointer >         iterator;
		typedef typename ft::random_access_iterator < const_pointer >   const_iterator;
		typedef typename ft::reverse_iterator<pointer>                  reverse_iterator;
		typedef typename ft::reverse_iterator<const_pointer>            const_reverse_iterator;

    RBT(){root_ = NULL;}

    void insert(T data) {
      Node<T>* found = searchNode(data)

      if (found && found->data == data)
      {
        found->count++;
        return;
      }
      if (!found)
      {
        Node<T>* ptr = alloc_.allocate(1);
        alloc_.construct(ptr, data);
        if (root_ == NULL)
        {
          root_ = ptr;
          root_->color = BLACK_NODE;
          return;
        }
        newNode->parent = found;
        if (data < found->val)
          found->left = newNode;
        else
          found->right = newNode;
        fixViolation(root_, ptr);
      }
    }

    void printTree(){printTree(root_);}

    Node<T>* searchNode(T value){return (searchNode(root_, value));}

    void deleteNode(T value){deleteNode(root_, value);};

    bool  checkNodeColor(T value) const {return (checkNodeColor(root_, value));};

    Node<T>*  get_root(){return root_;}
};
