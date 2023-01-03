
#ifndef _MAP_HPP_
# define _MAP_HPP_

#include "ft_containers.hpp"

namespace ft {
	template <class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator<ft::pair<const Key,T> > >
	class map {
		private:
			typedef ft::pair<const Key, T> value_type;
			typedef ft::pair<const Key, T> *pointer;
			typedef ft::pair<const Key, T> &reference;
			typedef ft::pair<const Key, T> const &const_reference;
			typedef ft::pair<const Key, T> const *const_pointer;
			typedef size_t size_type;
			typedef ptrdiff_t difference_type;
			typedef Compare key_compare;
			typedef Allocator allocator_type;
			typedef typename Allocator::template rebind<value_type>::other
				value_allocator_type;
			typedef typename Allocator::template rebind<value_type>::other
				*value_allocator_pointer;
			typedef typename Allocator::template rebind<value_type>::other
				&value_allocator_reference;
			typedef typename Allocator::template rebind<value_type>::other
				const &value_allocator_const_reference;
			typedef typename Allocator::template rebind<value_type>::other
				const *value_allocator_const_pointer;
			typedef ft::rb_tree<Key, value_type, key_compare, value_allocator_type>
				tree_type;
			typedef typename tree_type::iterator iterator;
			typedef typename tree_type::const_iterator const_iterator;
			typedef typename tree_type::reverse_iterator reverse_iterator;
			typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

		map() {
			(void)comp;
			(void)alloc;
		}

		explicit map( const Compare& comp,
              const Allocator& alloc = Allocator() ) {
			(void)comp;
			(void)alloc;
		}

		map( const map& other ) {
			(void)other;
		}

		~map() {

		}
	};
}

#endif
