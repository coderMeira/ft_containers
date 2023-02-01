#include <iostream>
#include"../inc/bst.hpp"
#include"../inc/rbt.hpp"
#include "../inc/visualizer.hpp"

int main(void)
{
	ft::RBT<int> tree;
	int del = 5;

	tree.insert(5);
	tree.insert(2);
	tree.insert(3);
	tree.insert(11);


	const visualizer<int> v(tree);
	cout << endl << endl;
	v.visualize();
	cout << endl << endl;

	tree.deleteNode(del);

	const visualizer<int> vv(tree);
	cout << endl << endl;
	vv.visualize();
	cout << endl << endl;
}
