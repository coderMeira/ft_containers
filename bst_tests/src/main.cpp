#include <iostream>
#include"../inc/bst.hpp"
#include"../inc/rbt.hpp"
#include "../inc/visualizer.hpp"

int main(void)
{
	ft::RBT<int> tree;
	int del = 5;

	tree.insert(5);
	visualizer<int> a(tree);
	cout << endl << endl;
	a.visualize();

	tree.insert(2);
	visualizer<int> b(tree);
	cout << endl << endl;
	b.visualize();

	tree.insert(4);
	visualizer<int> c(tree);
	cout << endl << endl;
	c.visualize();

	tree.insert(11);

	visualizer<int> d(tree);
	cout << endl << endl;
	d.visualize();

	// tree.deleteNode(del);

	// cout << endl << endl;
	// v.visualize();
	// cout << endl << endl;
}
