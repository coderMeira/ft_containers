#ifndef _RBT_NODE_HPP_
#define _RBT_NODE_HPP_

#include "ft_containers.hpp"

template<class T>
struct rbt_node {
	typedef T value_type;
	typedef rbt_node<T>* pointer;
	typedef rbt_node<T>& reference;
	typedef const rbt_node<T>* const_pointer;
	typedef const rbt_node<T>& const_reference;

	rbt_node() : parent_(pointer()), left_(pointer()), right_(pointer()), color_(false) {};
	rbt_node(const_reference val) : parent_(pointer()), left_(pointer()), right_(pointer()), color_(false), value_(val) {};
	rbt_node(const_pointer ptr) : parent_(pointer()), left_(pointer()), right_(pointer()), color_(false), value_(*ptr) {};
	rbt_node(const rbt_node& other) : parent_(other.parent_), left_(other.left_), right_(other.right_), color_(other.color_), value_(other.value_) {};
	rbt_node & operator=(const rbt_node& rhs) {parent_ = rhs.parent_; left_ = rhs.left_; right_ = rhs.right_; color_ = rhs.color_; value_ = rhs.value_; return *this;};
	~rbt_node() {};

	pointer parent_;
	pointer left_;
	pointer right_;
	bool color_;
	value_type value_;
};

#endif
