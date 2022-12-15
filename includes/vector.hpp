//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef _vec_TOR_HPP__
# define _vec_TOR_HPP__

#include "ft_containers.hpp"

namespace ft {
template <class T, class Allocator = std::allocator<T> >
class vector
{
    public:
    // MEMBER TYPES
        typedef T                                                       value_type;
		typedef Allocator                                               allocator_type;
		typedef typename allocator_type::pointer                        pointer;
		typedef typename allocator_type::const_pointer                  const_pointer;
		typedef typename allocator_type::reference                      reference;
		typedef typename allocator_type::const_reference                const_reference;
		typedef typename std::size_t                                    size_type;
		typedef typename std::ptrdiff_t                                 difference_type;
		typedef typename ft::random_access_iterator < pointer >         iterator;
		typedef typename ft::random_access_iterator < const_pointer >   const_iterator;
		typedef typename ft::reverse_iterator<pointer>                  reverse_iterator;
		typedef typename ft::reverse_iterator<const_pointer>            const_reverse_iterator;

    // *** CONSTRUCTORS ***

    // default constructor
    explicit vector (const allocator_type& alloc = allocator_type()) : alloc_(alloc), size_(0), capacity_(0), vec_(NULL){};
    // fill constructor
    explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : alloc_(alloc), size_(n), capacity_(n), vec_(NULL)
    {
        if (n == 0)
            return ;

        if (n > alloc_.maxsize_())
            throw std::length_error("Value passed to ft::vector is too large");

        vec_ = alloc_.allocate(n);

        for(size_type i; i < n; i++)
            alloc_.construct(vec_[i], val);
    };
    // range constructor
    template <class InputIterator>
    vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
        typename   enable_if<!is_integral<InputIterator>::value>::type* = 0) : alloc_(alloc), size_(last - first), capacity_(last - first), vec_(NULL)
        {
        if (size_ <= 0)
            return ;

        vec_ = alloc_.allocate(capacity_);

        for(size_type i = 0; first != last; first++, i++)
            alloc_.construct(vec_[i], *first);
        }
    // copy constructor
    vector (const vector& x){
        *this = x;
    };

    ~vector()
    {
        for (size_type i = 0; i < size_; i++)
            alloc_.destroy(vec_[i]);
        for (size_type i = 0; i < capacity_; i++)
            alloc_.deallocate(vec_[i]);
    };

	//*** FUNCTIONS ***

    //  Iterators
    iterator begin(void){
        return(iterator(vec_));
    }

    const_iterator begin() const{
        return (const_iterator(vec_));
    }

    iterator end(void){
        return (iterator(vec_ + size_));
    }

    const_iterator end() const {
		return const_iterator(vec_ + size_);
	}

    reverse_iterator rbegin() {
        return reverse_iterator(vec_ + size_ - 1);
	}

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(vec_ + size_ - 1);
        }
    // Capacity
	size_type size(void){
	    return (size_);
	}

    size_type   maxsize_() const{
        return (alloc_.maxsize_());
    }

    void resize (size_type n, value_type val = value_type()){
        if (n > size_)
        {
            if (n > size_ * 2)
                reserve(n);
            for (size_type i = n - size_; i > 0; i--)
                this->push_back(val);
        }
        else if (n < size_){
            while (size_ > n)
                alloc_.destroy(vec_[size_--]);
        }
    };

    size_type capacity() const {
		return capacity_;
	}

    void reserve (size_type n){
        if (n > alloc_.maxsize_())
            throw std::length_error("Value passed to ft::vector::reserve() is too large");
        if (n > capacity_){
                pointer temp = alloc_.allocate(n);
                for (size_type i = 0; i < size_; i++){
                    alloc_.construct(temp[i], vec_[i]);
                    alloc_.destroy(vec_[i]);
                }
                alloc_.deallocate(vec_, capacity_);
                vec_ = temp;
                capacity_ = n;
            }
    };

	bool empty() const {
        return (size_ == 0 ? true : false);
    }

    // Element access
    reference operator[] (size_type n) {
        return reference(vec_[n]);
    }

    const_reference operator[] (size_type n) const {
        return const_reference(vec_[n]);
    }

    reference at (size_type n);
    const_reference at (size_type n) const;

    reference front() {
        return reference(*vec_);
    }

    const_reference front() const {
        return const_reference(*vec_);
    }

    reference back() {
        return reference(*(vec_[size_ - 1]));
    }

    const_reference back() const {
        return const_reference(*(vec_[size_ - 1]));
    }

	private:
        allocator_type  alloc_;
		size_type      	size_;
		size_t	        capacity_;
		pointer         vec_;
};
}

#endif
