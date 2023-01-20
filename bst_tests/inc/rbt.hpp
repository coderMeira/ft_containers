#include <iostream>
#pragma once

enum Color {RED_NODE, BLACK_NODE};
enum Side {LEFT_SIDE, RIGHT_SIDE};


template<typename T>
struct RBNode
{
  T             data;
  Color         color;
  unsigned int  count;
  RBNode        *parent, *left, *right;

  RBNode(T data)
  {
    this->data = data;
    this->color = RED_NODE;
    this->count = 0;
    parent = left = right = NULL;
  }
};

template <class T, class Allocator = std::allocator<T> >
class RBT {
  RBNode<T>       *root_;
  allocator_type  alloc_;

  RBNode<T>* insert(RBNode<T>* root, RBNode<T>* ptr)
  {
    if (root == NULL)
      return (ptr);

    if (ptr->data == root->data)
    {
      (root->count)++;
      return (root);
    }
    else if (ptr->data < root->data)
    {
      root->left = insert(root->left, ptr);
      root->left->parent = root;
    }
    else
    {
      root->right = insert(root->right, ptr);
      root->right->parent = root;
    }
    return (root);
  }

  void  rotateLeft(RBNode<T>* root, RBNode<T>* ptr)
  {
    RBNode<T>* right_ptr = ptr->right;

    ptr->right = right_ptr->left;

    if (ptr->right != NULL)
      ptr->right->parent = ptr;

    right_ptr->parent = ptr->parent;

    if (ptr->parent == NULL)
      root = right_ptr;

    else if (ptr == ptr->parent->left)
      ptr->parent->left = right_ptr;

    else
      ptr->parent->left = ptr->right;

    right_ptr->left = ptr;
    ptr->parent - ptr->right;
  }

  void rotateRight(RBNode<T>* root, RBNode<T>* ptr)
  {
    RBNode<T>*  left_ptr = ptr->left;

    ptr->left = left_ptr->right;

    if (ptr->left != NULL)
      ptr->left->parent = ptr;

    left_ptr->parent = ptr->parent;

    if (ptr->parent == NULL)
      root = ptr->left;

    else if (ptr == ptr->parent->left)
      ptr->parent->left = left_ptr;

    else
      ptr->parent->right = left_ptr;

    left_ptr->right = ptr;
    ptr->parent = left_ptr;
  }

  void fixSide(RBNode<T>* root, RBNode<T>* ptr, RBNode<T>* parent, RBNode<T>* grand_parent, Side side)
  {
    RBNode<T>* uncle = NULL;

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
          rotateLeft(root, parent);
          ptr = parent;
          parent = ptr->parent;
        }
        rotateRight(root, grand_parent);
      }
      else
      {
        if (ptr == parent->left)
        {
          rotateRight(root, parent);
          ptr = parent;
          parent = ptr->parent;
        }
        rotateLeft(root, grand_parent);
      }
      std::swap(parent->color, grand_parent->color);
      ptr = parent;
    }
  }

  void fixViolation(RBNode<T>* root, RBNode<T>* ptr)
  {
      RBNode<T>* parent = NULL;
      RBNode<T>* grand_parent = NULL;

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

  RBNode<T>*  searchRBNode(const RBNode<T>* root, T value)
  {
    if (root == NULL || root->key == key)
      return (root);

    else if (value < root->data)
      return (searchRBNode(root->left, value));

    else if (value > root->data)
      return (searchRBNode(root->right, value));

    return (root);
  }

  bool  checkNodeColor(RBNode<T>* root, T value) const
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

  RBNode<T>*  findSucc(RBNode<T>* nd)
  {
    RBNode<T> * curr = nd;

    while (curr && curr->left)
      curr = curr->left;

    return (curr);
  }

  RBNode<T>* deleteRBNode(RBNode<T>* root, T value)
  {
    if (root == NULL)
      return (root);
    if (value < root->data)
      root->left = deleteRBNode(root->left, value);
    else if (value > root->data)
       root->right = deleteRBNode(root->right, value);

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
        RBNode<T>* tmp = root->left;
        delete (root);
        return (tmp);
      }
      else if (root->right && root->left == NULL)
      {
        RBNode<T>* tmp = root->right;
        delete (root);
        return (tmp);
      }
      else
      {
        RBNode<T>*  succ = findSucc(root->right);
        root->data = succ->data;
        root->count = succ->count;
        succ->count = 0;
        root->right = deleteRBNode(root->right, succ->data);
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
      RBNode<T>* found = searchRBNode(data)
      if (!found)
      {
        RBNode<T>* ptr = alloc_.allocate(1);
        alloc_.construct(ptr, data);
        root_ = insert(root_, ptr);
        fixViolation(root_, ptr);
      }
      else
        (found->count)++;
    }

    void printTree(){printTree(root_);}

    RBNode<T>* searchRBNode(T value){return (searchRBNode(root_, value));}

    void deleteRBNode(T value){deleteRBNode(root_, value);};

    bool  checkNodeColor(T value) const {return (checkNodeColor(root_, value));};

    RBNode<T>*  get_root(){return root_;}
};
