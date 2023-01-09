#include <iostream>
#include"../inc/bst.hpp"
#include "../inc/visualizer.hpp"

int main(void)
{
	BST<int> tree;

	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	tree.insert(4);

	tree.printTree();
	// const visualizer<int> v(tree);
	// cout << endl << endl;
	// v.visualize();
	// cout << endl << endl;
}
