#ifndef RBT_ITERATORS_HPP
#define RBT_ITERATORS_HPP

#include <iterator>
#include <memory>

#include "red_black_tree.hpp"

namespace ft {
template <typename T, typename Node>
class rbt_iterator {
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;

		typedef rbt_iterator<T, Node> iterator;
		typedef rbt_iterator<const T, const Node> const_iterator;
		typedef rbt_iterator<T, Node> self_type;

		rbt_iterator() : _node(NULL) {}
		rbt_iterator(Node* node) : _node(node) {}
		rbt_iterator(const iterator& other) : _node(other._node) {}
		~rbt_iterator() {}

		iterator& operator=(const iterator& other) {
			_node = other._node;
			return *this;
		}

		reference operator*() const { return _node->value; }
		pointer operator->() const { return &_node->value; }

		iterator& operator++() {
			_node = _node->successor();
			return *this;
		}
		iterator operator++(int) {
			iterator tmp(*this);
			++(*this);
			return tmp;
		}

		iterator& operator--() {
			_node = _node->predecessor();
			return *this;
		}
		iterator operator--(int) {
			iterator tmp(*this);
			--(*this);
			return tmp;
		}

		bool operator==(const iterator& other) const { return _node == other._node; }
		bool operator!=(const iterator& other) const { return _node != other._node; }

		Node* node() const { return _node; }

	private:
  		Node* _node;
};

template <typename T, typename Node>
class rbt_reverse_iterator {
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef std::ptrdiff_t difference_type;

		typedef rbt_reverse_iterator<T, Node> iterator;
		typedef rbt_reverse_iterator<const T, const Node> const_iterator;
		typedef rbt_reverse_iterator<T, Node> self_type;

		rbt_reverse_iterator() : _node(NULL) {}
		rbt_reverse_iterator(Node* node) : _node(node) {}
		rbt_reverse_iterator(const iterator& other) : _node(other._node) {}
		~rbt_reverse_iterator() {}

		iterator& operator=(const iterator& other) {
			_node = other._node;
			return *this;
		}

		reference operator*() const { return _node->value; }
		pointer operator->() const { return &_node->value; }

		iterator& operator++() {
			_node = _node->predecessor();
			return *this;
		}
		iterator operator++(int) {
			iterator tmp(*this);
			++(*this);
			return tmp;
		}

		iterator& operator--() {
			_node = _node->successor();
			return *this;
		}
		iterator operator--(int) {
			iterator tmp(*this);
			--(*this);
			return tmp;
		}

		bool operator==(const iterator& other) const { return _node == other._node; }
		bool operator!=(const iterator& other) const { return _node != other._node; }

		Node* node() const { return _node; }

	private:
  		Node* _node;
};
}

#endif
