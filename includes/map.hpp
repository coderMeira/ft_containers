
#ifndef _MAP_HPP_
# define _MAP_HPP_

#include "ft_containers.hpp"

namespace ft {
	template <class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator<ft::pair<const Key,T> > >
	class map {
		private:
			typedef Key																key_type;
			typedef T																mapped_type;
			typedef ft::pair<const Key, T>											value_type;
			typedef std::size_t														size_type;
			typedef std::ptrdiff_t													difference_type;
			typedef Compare															key_compare;
			typedef Allocator														allocator_type;
			typedef value_type&														reference;
			typedef const value_type&												const_reference;
			typedef Allocator::pointer												pointer;
			typedef Allocator::const_pointer										const_pointer;
			typedef ft::iterator_traits<pointer>									iterator;
			typedef ft::iterator_traits<const_pointer>								const_iterator;
			typedef ft::reverse_iterator<iterator>									reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>							const_reverse_iterator;
			typedef typename Allocator::template rebind<value_type>::other			value_allocator_type;
			typedef typename Allocator::template rebind<value_type>::other*			value_allocator_pointer;
			typedef typename Allocator::template rebind<value_type>::other&			value_allocator_reference;
			typedef typename Allocator::template rebind<value_type>::other const &	value_allocator_const_reference;
			typedef typename Allocator::template rebind<value_type>::other const *	value_allocator_const_pointer;
			typedef ft::RBT<Key, value_type, key_compare, value_allocator_type>		tree_type;
			// typedef typename tree_type::iterator iterator;
			// typedef typename tree_type::const_iterator const_iterator;
			// typedef typename tree_type::reverse_iterator reverse_iterator;
			// typedef typename tree_type::const_reverse_iterator const_reverse_iterator;

		map() {}

		explicit map( const Compare& comp,
              const Allocator& alloc = Allocator() ) {

		}

		map( const map& other ) {
			(void)other;
		}

		~map() {

		}
	};
}

#endif
