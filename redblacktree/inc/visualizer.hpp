#pragma once
#include <string>
#include <queue>
#include "../inc/rbt.hpp"

using namespace std;

template <class Key, class T>
class visualizer
{

	ft::RBT<Key, T> tree_;
	ft::Node<Key, T>* tree_root_;
	int tree_height_;
	int tree_nodes_;
	string** values_;

	int node_length_;
	int node_type_;
	int node_shift_factor_;
	string empty_node_;
	int space_length_;
	int space_shift_factor_;

	queue<ft::Node<Key, T>*> breadth_first_search();
	int get_tree_height(ft::Node<Key, T>*) const;
	int get_nodes_count(int) const;
	int get_subtree_width(int) const;

public:

	explicit visualizer(ft::RBT<Key, T> tree, int = -1, int = -1);
	~visualizer() = default;
	void visualize() const;
};

#include "../src/visualizer.cpp"
