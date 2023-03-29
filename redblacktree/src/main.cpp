#include <iostream>

#include "../inc/rbt.hpp"
#include "../inc/visualizer.hpp"

using namespace std;
int main(void)
{
	ft::RBT<string, int> tree;
	int del = 5;

	tree.insert(5);
	visualizer<string, int> a(tree);
	cout << endl << endl;
	a.visualize();

	tree.insert(2);
	visualizer<string, int> b(tree);
	cout << endl << endl;
	b.visualize();

	tree.insert(4);
	visualizer<string, int> c(tree);
	cout << endl << endl;
	c.visualize();

	tree.insert(11);

	visualizer<string, int> d(tree);
	cout << endl << endl;
	d.visualize();

	tree.deleteNode(del);

	visualizer<string, int> v(tree);
	cout << endl << endl;
	v.visualize();
}
