#include <iostream>
#include"../inc/bst.hpp"
#include"../inc/rbt.hpp"
#include "../inc/visualizer.hpp"

int main(void)
{
	RBT<int> tree;
	int find = 5;

	tree.insert(5);
	tree.insert(2);
	tree.insert(6);
	tree.insert(4);
	tree.insert(1);
	tree.insert(3);
	tree.insert(11);


	// tree.printTree();
	const visualizer<int> v(tree);
	cout << endl << endl;
	v.visualize();
	cout << endl << endl;

	// if (tree.searchNode(find))
	// 	cout << find << " was found in the tree\n";
	// else
	// 	cout << find << " was NOT found in the tree\n";

	tree.deleteRBNode(5);

	const visualizer<int> vv(tree);
	cout << endl << endl;
	vv.visualize();
	cout << endl << endl;
}

			// cout << setw(node_length_) << setfill('0') << (!values_[level][node].empty() && tree_.checkNodeColor(stoi(node_value.c_str())) == BLACK_NODE ? node_value : RED_CLR + node_value + RESET_CLR);
