#ifndef __REVERSE_ITERATOR__
# define __REVERSE_ITERATOR__

#include <iostream>
#include "iterator_traits.hpp"

namespace ft{
	template <class Iterator>
	class reverse_iterator
		{
		public:
			typedef ft::iterator_traits<Iterator>						traits_type;

			typedef Iterator									iterator_type;
			typedef typename traits_type::value_type			value_type;
			typedef typename traits_type::difference_type		difference_type;
			typedef typename traits_type::pointer				pointer;
			typedef typename traits_type::reference				reference;
			typedef typename traits_type::iterator_category		iterator_category;

			// CONSTRUCTORS
			// default
			reverse_iterator() : _pointer(pointer()){};
			// parametrized
			explicit reverse_iterator(iterator_type it) : _pointer(it){};
			// copy
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter> & rev_it)
									: _pointer(rev_it.base() - 1)
			{}
			// destructor
			~reverse_iterator(){};

			// OPERATORS
			// Forward iterator requirements
			reference operator*() const{
				return (*_pointer);
			}

			pointer operator->() const{
				return &(operator*());
			}

			reverse_iterator & operator++() {
				--_pointer;
				return *this;
			}

			// reverse_iterator operator++(int){
			// 	reverse_iterator temp = *this;
			// 	++(*this);
			// 	return temp;
			// }

			// Bidirectional iterator requirements
			reverse_iterator & operator--(){
				++_pointer;
				return (*this);
			}

			reverse_iterator operator--(int){
				reverse_iterator temp = *this;
				--(*this);
				return temp;
			}

			// reverse_iterator operator--()
			// {
			// 	return (reverse_iterator(_pointer++));
			// }

			// Random access iterator requirements
			reference operator[](difference_type n) const
			{
				return (base()[-n-1]);
			}

			reverse_iterator& operator+=(difference_type n)
			{
				_pointer -= n;
				return (*this);
			}

			reverse_iterator& operator-=(difference_type n)
			{
				_pointer += n;
				return (*this);
			}

			reverse_iterator operator+(difference_type n) const
			{
				return (reverse_iterator(_pointer - n));
			}

			reverse_iterator operator-(difference_type n) const
			{
				return (reverse_iterator(_pointer + n));
			}

			iterator_type base() const{
				return (_pointer + 1);
			}

		private:
				pointer	_pointer;
	};

template <typename IteratorL, typename IteratorR>
inline bool operator== (const reverse_iterator<IteratorL> & lhs,
		                const reverse_iterator<IteratorR> & rhs)
{
	return (lhs.base() == rhs.base());
}

template <typename Iterator>
inline bool operator== (const reverse_iterator<Iterator> & lhs,
		                const reverse_iterator<Iterator> & rhs)
{
	return (lhs.base() == rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator!= (const reverse_iterator<IteratorL> & lhs,
		               const reverse_iterator<IteratorR> & rhs)
{
	return (lhs.base() != rhs.base());
}

template <typename Iterator>
inline bool operator!= (const reverse_iterator<Iterator> & lhs,
		   				const reverse_iterator<Iterator> & rhs)
{
	return (lhs.base() != rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator< (const reverse_iterator<IteratorL> & lhs,
		   			  const reverse_iterator<IteratorR> & rhs)
{
	return (lhs.base() < rhs.base());
}

template <typename Iterator>
inline bool operator< (const reverse_iterator<Iterator> & lhs,
		   			  const reverse_iterator<Iterator> & rhs)
{
	return (lhs.base() < rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator<= (const reverse_iterator<IteratorL> & lhs,
		   			  const reverse_iterator<IteratorR> & rhs)
{
	return (lhs.base() <= rhs.base());
}

template <typename Iterator>
inline bool operator<= (const reverse_iterator<Iterator> & lhs,
		   				const reverse_iterator<Iterator> & rhs)
{
	return (lhs.base() <= rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator> (const reverse_iterator<IteratorL> & lhs,
		   				const reverse_iterator<IteratorR> & rhs)
{
	return (lhs.base() > rhs.base());
}

template <typename Iterator>
inline bool operator> (const reverse_iterator<Iterator> & lhs,
		   				const reverse_iterator<Iterator> & rhs)
{
	return (lhs.base() > rhs.base());
}

template <typename IteratorL, typename IteratorR>
inline bool operator>= (const reverse_iterator<IteratorL> & lhs,
						const reverse_iterator<IteratorR> & rhs)
{
	return (lhs.base() >= rhs.base());
}

template <typename Iterator>
inline bool operator>= (const reverse_iterator<Iterator> & lhs,
						const reverse_iterator<Iterator> & rhs)
{
	return (lhs.base() >= rhs.base());
}

/****
** Arithmetic Operators
*/

template <typename IteratorL, typename IteratorR>
inline typename reverse_iterator<IteratorL>::difference_type
operator-(const reverse_iterator<IteratorL> & lhs,
		  const reverse_iterator<IteratorR> & rhs )
{
	return (lhs.base() - rhs.base());
}

template <typename Iterator>
inline typename reverse_iterator<Iterator>::difference_type
operator-(const reverse_iterator<Iterator> & lhs,
		  const reverse_iterator<Iterator> & rhs )
{
	return (lhs.base() - rhs.base());
}

template <typename Iterator>
inline reverse_iterator<Iterator>
operator+(typename reverse_iterator<Iterator>::difference_type n,
		  const reverse_iterator<Iterator> & rhs)
{
	return (reverse_iterator<Iterator>(rhs.base() + n));
}
}

#endif
