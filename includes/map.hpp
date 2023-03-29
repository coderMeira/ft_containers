
#ifndef _MAP_HPP_
# define _MAP_HPP_

#include "ft_containers.hpp"
#include <map>
#include "../redblacktree/inc/rbt.hpp"

namespace ft {
	template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key,T> > >
	class map {
		private:
			typedef Key																key_type;
			typedef T																mapped_type;
			typedef ft::pair<const Key, T>											value_type;
			typedef std::size_t														size_type;
			typedef std::ptrdiff_t													difference_type;
			typedef Compare															key_compare;
			//value compare
			class value_compare {
				friend class map;
				protected:
					Compare comp;
					value_compare(Compare c) : comp(c) {}
				public:
					typedef bool result_type;
					typedef value_type first_argument_type;
					typedef value_type second_argument_type;
					bool operator()(const value_type& x, const value_type& y) const {
						return comp(x.first, y.first);
					}
			};

			typedef Allocator														allocator_type;
			typedef value_type&														reference;
			typedef const value_type&												const_reference;
			typedef typename Allocator::pointer										pointer;
			typedef typename Allocator::const_pointer								const_pointer;
			typedef typename Allocator::template rebind<value_type>::other			value_allocator_type;
			typedef typename Allocator::template rebind<value_type>::other*			value_allocator_pointer;
			typedef typename Allocator::template rebind<value_type>::other&			value_allocator_reference;
			typedef typename Allocator::template rebind<value_type>::other const &	value_allocator_const_reference;
			typedef typename Allocator::template rebind<value_type>::other const *	value_allocator_const_pointer;
			typedef RBT<Key, value_type, key_compare, value_allocator_type>			tree_type;
			typedef typename tree_type::iterator 									iterator;
			typedef typename tree_type::const_iterator 								const_iterator;
			typedef typename tree_type::reverse_iterator 							reverse_iterator;
			typedef typename tree_type::const_reverse_iterator 						const_reverse_iterator;

			tree_type	_tree;

		public:
		// Member functions

		// Constructors
		explicit map( const Compare& comp = Compare(),
			  const Allocator& alloc = Allocator() ) {
		}

		template <class InputIterator>
		map( InputIterator first, InputIterator last,
			 const Compare& comp = Compare(),
			 const Allocator& alloc = Allocator() ) {
			(void)first;
			(void)last;
			(void)comp;
			(void)alloc;
		}

		map( const map& other ) {
			(void)other;
		}

		// Destructor
		~map() {
		}

		// Assignation operator
		map& operator=( const map& other ) {
			(void)other;
			return *this;
		}

		// Iterators
		iterator begin() {
			return _tree.begin();
		}

		const_iterator begin() const {
			return _tree.begin();
		}

		iterator end() {
			return _tree.end();
		}

		const_iterator end() const {
			return _tree.end();
		}

		reverse_iterator rbegin() {
			return _tree.rbegin();
		}

		const_reverse_iterator rbegin() const {
			return _tree.rbegin();
		}

		reverse_iterator rend() {
			return _tree.rend();
		}

		const_reverse_iterator rend() const {
			return _tree.rend();
		}

		// Capacity
		bool empty() const {
			return _tree.empty();
		}

		size_type size() const {
			return _tree.size();
		}

		size_type max_size() const {
			return _tree.max_size();
		}

		// Element access
		mapped_type& operator[]( const key_type& key ) {
			(void)key;
			return _tree[key];
		}

		// Modifiers
		ft::pair<iterator,bool> insert( const value_type& value ) {
			return _tree.insert(value);
		}

		iterator insert( iterator position, const value_type& value ) {
			(void)position;
			return _tree.insert(value).first;
		}

		template <class InputIterator>
		void insert( InputIterator first, InputIterator last ) {
			(void)first;
			(void)last;
		}

		void erase( iterator position ) {
			(void)position;
		}

		size_type erase( const key_type& key ) {
			(void)key;
			return 0;
		}

		void erase( iterator first, iterator last ) {
			(void)first;
			(void)last;
		}

		void swap( map& other ) {
			(void)other;
		}

		void clear() {
		}

		// Observers
		key_compare key_comp() const {
			return _tree.key_comp();
		}

		value_compare value_comp() const {
			return value_compare(_tree.key_comp());
		}

		// Operations
		iterator find( const key_type& key ) {
			(void)key;
			return _tree.find(key);
		}

		const_iterator find( const key_type& key ) const {
			(void)key;
			return _tree.find(key);
		}

		size_type count( const key_type& key ) const {
			(void)key;
			return 0;
		}

		iterator lower_bound( const key_type& key ) {
			(void)key;
			return _tree.lower_bound(key);
		}

		const_iterator lower_bound( const key_type& key ) const {
			(void)key;
			return _tree.lower_bound(key);
		}

		iterator upper_bound( const key_type& key ) {
			(void)key;
			return _tree.upper_bound(key);
		}

		const_iterator upper_bound( const key_type& key ) const {
			(void)key;
			return _tree.upper_bound(key);
		}

		ft::pair<const_iterator,const_iterator> equal_range( const key_type& key ) const {
			(void)key;
			return ft::pair<const_iterator,const_iterator>(_tree.lower_bound(key), _tree.upper_bound(key));
		}

		ft::pair<iterator,iterator> equal_range( const key_type& key ) {
			(void)key;
			return ft::pair<iterator,iterator>(_tree.lower_bound(key), _tree.upper_bound(key));
		}

		// Allocator
		allocator_type get_allocator() const {
			return _tree.get_allocator();
		};
	};
}

#endif
