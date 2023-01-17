#include <iostream>
#pragma once

template<typename T>
struct Node
{
  T data;
  Node *left;
  Node *right;
};

template <typename T>
class BST {
  Node<T> *root_;

  // Function to create a new node
  Node<T>* createNode(T data)
  {
    Node<T> *newNode = new Node<T>;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
  }

  // Function to insert a new node in the binary search tree
  void insert(Node<T>* &root, T data)
  {
    if (root == NULL) {
      root = createNode(data);
    } else if (data <= root->data) {
      insert(root->left, data);
    } else {
      insert(root->right, data);
    }
  }

  // Function to print the binary search tree in-order (ascending order)
  void printTree(Node<T>* root)
  {
    if (root == NULL) return;
    printTree(root->left);
    std::cout << root->data << " ";
    printTree(root->right);
  }

  bool  searchNode(Node<T>* root, T value)
  {
    if (root == NULL)
      return (false);

    if (value == root->data)
      return (true);

    else if (value < root->data)
      return (searchNode(root->left, value));

    else if (value > root->data)
      return (searchNode(root->right, value));

    return (false);
  }

  Node<T>*  findSucc(Node<T>* nd)
  {
    Node<T> * curr = nd;

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
        Node<T>*  succ = findSucc(root->right);
        root->data = succ->data;
        root->right = deleteNode(root->right, succ->data);
      }
    }
    return (root);
  }

  public:
    BST(){root_ = NULL;}

    // Function to insert a new node in the binary search tree
    void insert(T data){insert(root_, data);}

    // Function to print the binary search tree in-order (ascending order)
    void printTree(){printTree(root_);}

    bool searchNode(T value){return (searchNode(root_, value));}

    void deleteNode(T value){deleteNode(root_, value);};

    Node<T>*  get_root(){return root_;}
};
