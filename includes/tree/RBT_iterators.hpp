#ifndef _RBT_ITERATORS_HPP_
#define _RBT_ITERATORS_HPP_

#include "ft_containers.hpp"
#include "../iterator_traits.hpp"
#include "../random_access_iterator.hpp"

namespace ft {
	template <class T>
	class RBT_iterator {
		public:
			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
			typedef ft::random_access_iterator<T> iterator_category;
			typedef std::ptrdiff_t difference_type;

			RBT_iterator() : pointer_(pointer()){};
			RBT_iterator(pointer ptr) : pointer_(ptr){};
			RBT_iterator(const RBT_iterator& r_a_it){*this = r_a_it;}
			RBT_iterator & operator=(const RBT_iterator& rhs) {(void) rhs; return *this;}
			~RBT_iterator(){}

			reference operator*() const
			{
				return (*pointer_);
			}

			pointer operator->() const
			{
				return (pointer_);
			}


	}

};

#endif
