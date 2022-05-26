//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

#include <iostream>
#include "ft_containers.hpp"

namespace ft{
template < class T, class Alloc = std::allocator<T> >
class vector {
	public:
			//CONSTRUCTORS
		explicit vector (const allocator_type& alloc = allocator_type());
		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
		template <class InputIterator>
         vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());

copy (4)

vector (const vector& x);

		vector();
		vector(const vector&);
		~vector();
		vector&	operator= (const vector&); // const for safety... not super nesessary

		size_t	size(void) {return (size_)};

	private:
		size_t	size_;
		size_t	capacity;
		T*		vec

};
}

std::ostream&	operator<<(std::ostream&, const vector&);

#endif
