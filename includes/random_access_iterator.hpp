#ifndef __RANDOM_ACCESS_ITERATOR_HPP__
# define __RANDOM_ACCESS_ITERATOR_HPP__

#include <iostream>
#include "iterator_traits.hpp"

namespace ft{
	template <class T>
	class random_access_iterator {

		public:
		typedef ft::iterator_traits<T>						traits_type;

		typedef typename traits_type::value_type			value_type;
		typedef typename traits_type::difference_type		difference_type;
		typedef typename traits_type::pointer				pointer;
		typedef typename traits_type::reference				reference;
		typedef typename traits_type::iterator_category		iterator_category;

		// CONSTRUCTORS
		// default
		random_access_iterator() : pointer_(pointer()){};
		// parametrized
		random_access_iterator(pointer ptr) : pointer_(ptr){};
		// copy
		template <class Iter>
  		random_access_iterator(const random_access_iterator<Iter>& r_a_it) : pointer_(r_a_it.base()){}
		random_access_iterator(const random_access_iterator& r_a_it){*this = r_a_it;}
		// = operator
		random_access_iterator & operator=(const random_access_iterator& rhs) {(void) rhs; return *this;}
		// destructor
		~random_access_iterator(){}


 		// Forward iterator requirements
		reference operator*() const
		{
			return (*pointer_);
		}

		pointer operator->() const
		{
			return (pointer_);
		}

		random_access_iterator & operator++()
		{
			++pointer_;
			return (*this);
		}

		random_access_iterator operator++(int)
		{
			random_access_iterator temp;
			temp.pointer_ = pointer_++;
			return temp;
		}

		// Bidirectional iterator requirements

		random_access_iterator & operator--() {
			--pointer_;
			return (*this);
		}

		// random_access_iterator operator--()
		// {
		// 	return (random_access_iterator(pointer_--));
		// }

		// Random access iterator requirements
		reference operator[](difference_type n) const
		{
			return (pointer_[n]);
		}

		random_access_iterator& operator+=(difference_type n)
		{
			pointer_ += n;
			return (*this);
		}

		random_access_iterator& operator-=(difference_type n)
		{
			pointer_ -= n;
			return (*this);
		}

		random_access_iterator operator+(difference_type n) const
		{
			return (random_access_iterator(pointer_ + n));
		}

		random_access_iterator operator-(difference_type n) const
		{
			return (random_access_iterator(pointer_ - n));
		}

		const pointer& base() const{
			return (pointer_);
		}

		private:
		pointer	pointer_;
	};

template <typename IteratorL, typename IteratorR>
inline bool operator== (const random_access_iterator<IteratorL> & lhs,
		                const random_access_iterator<IteratorR> & rhs)
{
	return (lhs.base() == rhs.base());
}

template <typename Iterator>
inline bool operator== (const random_access_iterator<Iterator> & lhs,
		                const random_access_iterator<Iterator> & rhs)
{
	return (lhs.base() == rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator!= (const random_access_iterator<IteratorL> & lhs,
		               const random_access_iterator<IteratorR> & rhs)
{
	return (lhs.base() != rhs.base());
}

template <typename Iterator>
inline bool operator!= (const random_access_iterator<Iterator> & lhs,
		   				const random_access_iterator<Iterator> & rhs)
{
	return (lhs.base() != rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator< (const random_access_iterator<IteratorL> & lhs,
		   			  const random_access_iterator<IteratorR> & rhs)
{
	return (lhs.base() < rhs.base());
}

template <typename Iterator>
inline bool operator< (const random_access_iterator<Iterator> & lhs,
		   			  const random_access_iterator<Iterator> & rhs)
{
	return (lhs.base() < rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator<= (const random_access_iterator<IteratorL> & lhs,
		   			  const random_access_iterator<IteratorR> & rhs)
{
	return (lhs.base() <= rhs.base());
}

template <typename Iterator>
inline bool operator<= (const random_access_iterator<Iterator> & lhs,
		   				const random_access_iterator<Iterator> & rhs)
{
	return (lhs.base() <= rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator> (const random_access_iterator<IteratorL> & lhs,
		   				const random_access_iterator<IteratorR> & rhs)
{
	return (lhs.base() > rhs.base());
}

template <typename Iterator>
inline bool operator> (const random_access_iterator<Iterator> & lhs,
		   				const random_access_iterator<Iterator> & rhs)
{
	return (lhs.base() > rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator>= (const random_access_iterator<IteratorL> & lhs,
						const random_access_iterator<IteratorR> & rhs)
{
	return (lhs.base() >= rhs.base());
}

template <typename Iterator>
inline bool operator>= (const random_access_iterator<Iterator> & lhs,
						const random_access_iterator<Iterator> & rhs)
{
	return (lhs.base() >= rhs.base());
}

/****
** Arithmetic Operators
*/

template <typename IteratorL, typename IteratorR>
inline typename random_access_iterator<IteratorL>::difference_type
operator-(const random_access_iterator<IteratorL> & lhs,
		  const random_access_iterator<IteratorR> & rhs )
{
	return (lhs.base() - rhs.base());
}

template <typename Iterator>
inline typename random_access_iterator<Iterator>::difference_type
operator-(const random_access_iterator<Iterator> & lhs,
		  const random_access_iterator<Iterator> & rhs )
{
	return (lhs.base() - rhs.base());
}

template <typename Iterator>
inline random_access_iterator<Iterator>
operator+(typename random_access_iterator<Iterator>::difference_type n,
		  const random_access_iterator<Iterator> & rhs)
{
	return (random_access_iterator<Iterator>(rhs.base() + n));
}
}

#endif
