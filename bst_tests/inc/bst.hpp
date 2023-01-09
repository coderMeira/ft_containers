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
  Node<T>* createNode(T data) {
    Node<T> *newNode = new Node<T>;
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
  }

  // Function to insert a new node in the binary search tree
  void insert(Node<T>* &root, T data) {
    if (root == NULL) {
      root = createNode(data);
    } else if (data <= root->data) {
      insert(root->left, data);
    } else {
      insert(root->right, data);
    }
  }

  // Function to print the binary search tree in-order (ascending order)
  void printTree(Node<T>* root) {
    if (root == NULL) return;
    printTree(root->left);
    std::cout << root->data << " ";
    printTree(root->right);
  }

  public:
    BST() {
      root_ = NULL;
    }

    // Function to insert a new node in the binary search tree
    void insert(T data) {
      insert(root_, data);
    }

    // Function to print the binary search tree in-order (ascending order)
    void printTree() {
      printTree(root_);
    }

    Node<T>*  get_root(){return root_;};
};
