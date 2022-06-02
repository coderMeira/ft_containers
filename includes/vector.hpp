//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

#include <iostream>
#include "ft_containers.hpp"

namespace ft{
template <class T, class Allocator = std::allocator<T> >
class vector
{
    //MEMBER TYPES
        typedef T                                                       value_type;
		typedef Alloc                                                   allocator_type;
		typedef typename allocator_type::reference                      reference;
		typedef typename allocator_type::const_reference                const_reference;
		typedef typename allocator_type::pointer                        pointer;
		typedef typename allocator_type::const_pointer                  const_pointer;
		typedef typename std::ptrdiff_t                                 difference_type;
		typedef typename std::size_t                                    size_type;
		// typedef typename ft::random_access_iterator<pointer>            iterator;
		// typedef typename ft::random_access_iterator<const_pointer>      const_iterator;
		// typedef typename ft::reverse_iterator<pointer>                  reverse_iterator;
		// typedef typename ft::reverse_iterator<const_pointer>            const_reverse_iterator;
    //CONSTRUCTORS

    // default
    explicit vector (const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(0), _capacity(0), _vec(NULL){};
    // fill
    explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _size(n), _capacity(n), _vec(NULL)
    {
        if (n == 0)
            return ;

        if (n > alloc_.max_size())
            throw std::length_error("Value passed to ft::vector is too large");

        _vec = _alloc.allocate(n);

        for(size_type i; i < n; i++)
            _alloc.construct(_vec + 1, val);
    }
    //range
    template <class InputIterator>
         vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
    // copy
    vector (const vector& x);

    public:

	//FUNCTIONS
	size_t	size(void) {return (size_)};

	private:
        allocator_type  _alloc;
		size_t      	_size;
		sizet	        _capacity;
		T*		        _vec;

};
}

// std::ostream&	operator<<(std::ostream&, const vector&);

#endif
