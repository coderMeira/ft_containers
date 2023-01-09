#pragma once
#include "bst.hpp"
#include <string>
#include <queue>

using namespace std;

template <class T>
class visualizer
{

	BST<T> tree_;
	Node<T>* tree_root_;
	int tree_height_;
	int tree_nodes_;
	string** values_;

	int node_length_;
	int node_type_;
	int node_shift_factor_;
	string empty_node_;

	int space_length_;
	int space_shift_factor_;

	queue<Node<T>*> breadth_first_search();
	int get_tree_height(Node<T>*) const;
	int get_nodes_count(int) const;
	int get_subtree_width(int) const;

public:

	explicit visualizer(BST<T> tree, int = -1, int = -1);
	~visualizer() = default;
	void visualize() const;
};

#include "../src/visualizer.cpp"