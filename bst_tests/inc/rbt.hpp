#include <iostream>
#include "../../includes/ft_containers.hpp"

#ifndef _RBT_HPP_
#define _RBT_HPP_

namespace ft
{
  enum Color {RED, BLACK};
  enum Side {LEFT, RIGHT};


  template<typename T>
  struct Node
  {
    T             data;
    Color         color;
    unsigned int  count;
    Node        *parent, *left, *right;

    Node(T data) : data(data), color(RED), count(0), parent(NULL), left(NULL), right(NULL)
    {
      count++;
    }

    Node (const Node& other) : data(other.data), color(other.color), count(other.count), parent(other.parent), left(other.left), right(other.right)
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
  class RBT {
    public:
      typedef T                                                       value_type;
      typedef typename Allocator::template rebind<Node<T> >::other    allocator_type;
      typedef Node<T>*                                                node_ptr;
      typedef typename allocator_type::pointer                        pointer;
      typedef typename allocator_type::const_pointer                  const_pointer;
      typedef typename allocator_type::reference                      reference;
      typedef typename allocator_type::const_reference                const_reference;
      typedef typename std::size_t                                    size_type;
      typedef typename std::ptrdiff_t                                 difference_type;
      typedef typename ft::random_access_iterator<pointer>            iterator;
      typedef typename ft::random_access_iterator<const_pointer>      const_iterator;
      typedef typename ft::reverse_iterator<pointer>                  reverse_iterator;
      typedef typename ft::reverse_iterator<const_pointer>            const_reverse_iterator;

    RBT(){root_ = NULL;}

    private:
      Node<T>         *root_;
      allocator_type  alloc_;

      void rotate(node_ptr ptr, Side side)
      {
        node_ptr newParent = NULL;

        if (side == LEFT)
          newParent = ptr->right;
        else
          newParent = ptr->left;

        if (ptr == root_)
          root_ = newParent;
        ptr->moveDown(newParent);
        if (side == LEFT)
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

      void fixSide(node_ptr root, node_ptr ptr, node_ptr parent, node_ptr grand_parent, Side side)
      {
        node_ptr uncle = NULL;

        if (side == LEFT)
          uncle = grand_parent->right;
        else
          uncle = grand_parent->left;

        if (uncle != NULL && uncle->color == RED)
        {
          parent->color = BLACK;
          uncle->color = BLACK;
          grand_parent->color = RED;
          ptr = grand_parent;
        }
        else
        {
          if (side == LEFT)
          {
            if (ptr == parent->right)
            {
              rotate(parent, LEFT);
              ptr = parent;
              parent = ptr->parent;
            }
            rotate(grand_parent, RIGHT);
          }
          else
          {
            if (ptr == parent->left)
            {
              rotate(parent, RIGHT);
              ptr = parent;
              parent = ptr->parent;
            }
            rotate(grand_parent, LEFT);
          }
          std::swap(parent->color, grand_parent->color);
          ptr = parent;
        }
      }

      void fixViolation(node_ptr root, node_ptr ptr)
      {
          node_ptr parent = NULL;
          node_ptr grand_parent = NULL;

        while ((ptr != root) && (ptr->color != BLACK) && (ptr->parent->color == RED))
        {
          parent = ptr->parent;
          grand_parent = ptr->parent->parent;

          if (parent == grand_parent->left)
            fixSide(root, ptr, parent, grand_parent, LEFT);
          else
            fixSide(root, ptr, parent, grand_parent, RIGHT);
        }
        root->color = BLACK;
      }

      node_ptr  searchNode(const node_ptr root, T value)
      {
        if (root == NULL || root->data == value)
          return (root);

        else if (value < root->data)
          return (searchNode(root->left, value));

        else if (value > root->data)
          return (searchNode(root->right, value));

        return (root);
      }

      bool  checkNodeColor(node_ptr root, T value) const
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

      node_ptr  findSuccessor(node_ptr ptr)
      {
        Node<T> * curr = ptr;

        while (curr && curr->left)
          curr = curr->left;

        return (curr);
      }

      node_ptr  findReplacement(node_ptr ptr)
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

        node_ptr  sibling = ptr->sibling();
        node_ptr  parent = ptr->parent;

        if (sibling == NULL)
          fixDoubleBlack(parent);
        else
        {
          if (sibling->color == RED)
          {
            parent->color = RED;
            sibling->color = BLACK;
            if (sibling->hasRedChild())
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
        node_ptr  toReplace = findReplacement(toDelete);
        node_ptr  parent = toDelete->parent;
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
              if (toDelete->sibling() != NULL)
                toDelete->sibling()->color = RED;
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

        T  temp = toReplace->data;
        deleteNode(toReplace);
        toDelete->data = temp;
      }

    public:

    void insert(T data) {
      node_ptr found = searchNode(data);

      if (found && found->data == data)
      {
        found->count++;
        return;
      }
      if (!found)
      {
        node_ptr ptr = alloc_.allocate(1);
        alloc_.construct(ptr, data);
        if (root_ == NULL)
        {
          root_ = ptr;
          root_->color = BLACK;
          return;
        }
        node_ptr newNode = ptr;
        node_ptr curr = root_;
        node_ptr parent = NULL;

        while (curr != NULL)
        {
          parent = curr;
          if (newNode->data < curr->data)
            curr = curr->left;
          else
            curr = curr->right;
        }
        newNode->parent = parent;
        if (newNode->data < parent->data)
          parent->left = newNode;
        else
          parent->right = newNode;

        fixViolation(root_, newNode);
      }
    }

    void printTree(){printTree(root_);}

    node_ptr searchNode(T value){return (searchNode(root_, value));}

    void deleteNode(T value)
    {
      if (root_ == NULL)
        return;
      node_ptr found = searchNode(value);
      if (found && found->data == value)
      {
        if (found->count > 1)
          found->count--;
        else
          deleteNode(found);
      }
    };

    bool  checkNodeColor(T value) const {return (checkNodeColor(root_, value));};

// getter for visualizer
    node_ptr  get_root(){return root_;}

  };
}
#endif
