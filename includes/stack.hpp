
#ifndef STACK_HPP
# define STACK_HPP

#include "ft_containers.hpp"

namespace ft {

	template <class T, class Container = ft::vector<T> >
	class stack {
		public:
			typedef Container container_type;
			typedef T value_type;
			typedef size_t size_type;
			typedef typename container_type::reference reference;
			typedef typename container_type::const_reference const_reference;

			explicit stack (const container_type& cont = container_type()) : c(cont) {
			}

			stack( const stack& other ) {
				*this->c = other.c;
			}

			~stack() {

			}

			bool empty() const {
				return (c.empty());
			}

			size_type size() const {
				return (c.size());
			}

			value_type& top() {
				return (c.back());
			}

			const value_type& top() const {
				return (c.back());
			}

			void push (const value_type& val) {
				c.push_back(val);
			}

			void pop() {
				c.pop_back();
			}


		friend bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs.c == rhs.c);
		}

		friend bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs.c != rhs.c);
		}

		friend bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs.c < rhs.c);
		}

		friend bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs.c <= rhs.c);
		}

		friend bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs.c > rhs.c);
		}

		friend bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs) {
			return (lhs.c >= rhs.c);
		}
		protected:
			container_type c;
	};
}

#endif

