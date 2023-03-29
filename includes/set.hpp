#ifndef _SET_HPP_
#define _SET_HPP_

#include "pair.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include  "red_black_tree.hpp"

namespace ft {
	template <class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
	class set {
		private:
			typedef Key																key_type;
			typedef Key																value_type;
			typedef std::size_t														size_type;
			typedef std::ptrdiff_t													difference_type;
			typedef Compare															key_compare;
			typedef Alloc															allocator_type;
			typedef value_type&														reference;
			typedef const value_type&												const_reference;
			typedef typename Alloc::pointer											pointer;
			typedef typename Alloc::const_pointer									const_pointer;
			typedef typename Alloc::template rebind<value_type>::other				value_allocator_type;
			typedef typename Alloc::template rebind<value_type>::other*				value_allocator_pointer;
			typedef typename Alloc::template rebind<value_type>::other&				value_allocator_reference;
			typedef typename Alloc::template rebind<value_type>::other const &		value_allocator_const_reference;
			typedef typename Alloc::template rebind<value_type>::other const *		value_allocator_const_pointer;
			typedef RBT<Key, value_type, key_compare, value_allocator_type>			tree_type;
			typedef typename tree_type::iterator 									iterator;
			typedef typename tree_type::const_iterator 								const_iterator;
			typedef typename tree_type::reverse_iterator 							reverse_iterator;
			typedef typename tree_type::const_reverse_iterator 						const_reverse_iterator;

			tree_type	_tree;

		public:
		// Member functions

		// Constructors
		explicit set( const Compare& comp = Compare(),
			  const Alloc& alloc = Alloc() ) {
		}

		template <class InputIterator>
		set( InputIterator first, InputIterator last,
			 const Compare& comp = Compare(),
			 const Alloc& alloc = Alloc() ) {
		}

		set( const set& x ) {
		}

		// Destructor
		~set() {
		}

		// Assignation operator
		set& operator=( const set& x ) {
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

		// Modifiers
		std::pair<iterator,bool> insert( const value_type& val ) {
			return _tree.insert(val);
		}

		iterator insert( iterator position, const value_type& val ) {
			return _tree.insert(position, val);
		}

		template <class InputIterator>
		void insert( InputIterator first, InputIterator last ) {
			_tree.insert(first, last);
		}

		void erase( iterator position ) {
			_tree.erase(position);
		}

		size_type erase( const key_type& k ) {
			return _tree.erase(k);
		}

		void erase( iterator first, iterator last ) {
			_tree.erase(first, last);
		}

		void swap( set& x ) {
			_tree.swap(x._tree);
		}

		void clear() {
			_tree.clear();
		}

		// Observers
		key_compare key_comp() const {
			return _tree.key_comp();
		}

		value_compare value_comp() const {
			return _tree.value_comp();
		}

		// Operations

		iterator find( const key_type& k ) {
			return _tree.find(k);
		}

		size_type count( const key_type& k ) const {
			return _tree.count(k);
		}

		iterator lower_bound( const key_type& k ) {
			return _tree.lower_bound(k);
		}

		const_iterator lower_bound( const key_type& k ) const {
			return _tree.lower_bound(k);
		}

		iterator upper_bound( const key_type& k ) {
			return _tree.upper_bound(k);
		}

		const_iterator upper_bound( const key_type& k ) const {
			return _tree.upper_bound(k);
		}

		std::pair<const_iterator,const_iterator> equal_range( const key_type& k ) const {
			return _tree.equal_range(k);
		}

		std::pair<iterator,iterator> equal_range( const key_type& k ) {
			return _tree.equal_range(k);
		}

		// Allocator
		allocator_type get_allocator() const {
			return _tree.get_allocator();
		}
	};
};

#endif
