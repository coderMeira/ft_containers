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

        if (n > alloc_.max_size())
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

    // Destructor
    ~vector()
    {
        clear();
        if (capacity_ > 0)
            alloc_.deallocate(vec_, capacity_);
        capacity_ = 0;
    };

	//*** FUNCTIONS ***
    // Assign
    vector& operator=( const vector& other ) {
        if (this == &other)
            return (*this);

        clear();
        if (capacity_ > 0)
            alloc_.deallocate(vec_, capacity_);

        size_ = other.size_;
        capacity_ = other.capacity_;
        vec_ = alloc_.allocate(capacity_);

        for (size_type i = 0; i < size_; i++)
            alloc_.construct(vec_[i], other.vec_[i]);

        return (*this);
    }

    void assign( size_type count, const T& value ) {
        clear();
        if (capacity_ > 0)
            alloc_.deallocate(vec_, capacity_);

        size_ = count;
        capacity_ = count;
        vec_ = alloc_.allocate(capacity_);

        for (size_type i = 0; i < size_; i++)
            alloc_.construct(vec_[i], value);
    }

    allocator_type get_allocator() const {
        return (alloc_);
    }

    // Element access
    reference at (size_type n) {
        if (n >= size_) {
            std::stringstream error;
            error << "vector::_M_range_check: __n (which is " << n << ") >= this->size() (which is " << size_ << ")";
            throw(std::out_of_range(error.str()));
		}
		return reference(vec_[n]);
    }

    const_reference at (size_type n) const {
        if (n >= size_) {
            std::stringstream error;
            error << "vector::_M_range_check: __n (which is " << n << ") >= this->size() (which is " << size_ << ")";
            throw(std::out_of_range(error.str()));
        }
		return const_reference(vec_[n]);
    }

    reference operator[] (size_type n) {
        return reference(vec_[n]);
    }

    const_reference operator[] (size_type n) const {
        return const_reference(vec_[n]);
    }

    reference front() {
        return (reference(*vec_));
    }

    const_reference front() const {
        return (const_reference(*vec_));
    }

    reference back() {
        return (reference(*(vec_[size_ - 1])));
    }

    const_reference back() const {
        return (const_reference(*(vec_[size_ - 1])));
    }

    value_type* data() {
        return (vec_);
    }

    const value_type* data() const {
        return (const_pointer(vec_));
    }

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
		return (const_iterator(vec_ + size_));
	}

    reverse_iterator rbegin() {
        return (reverse_iterator(vec_ + size_ - 1));
	}

    const_reverse_iterator rbegin() const {
        return (const_reverse_iterator(vec_ + size_ - 1));
    }

    reverse_iterator rend() {
        return (reverse_iterator(vec_));
	}

    const_reverse_iterator rend() const {
        return (const_reverse_iterator(vec_));
    }

    // Capacity
	bool    empty() const {
        return (size_ == 0 ? true : false);
    }

	size_type   size(void){
	    return (size_);
	}

    size_type   max_size() const{
        return (alloc_.max_size());
    }

    void reserve (size_type n){
        if (n > alloc_.max_size())
            throw std::length_error("Value passed to ft::vector::reserve() is too large");
        if (n > capacity_){
                pointer temp = alloc_.allocate(n);
                for (size_type i = 0; i < size_; i++){
                    alloc_.construct(temp + i, vec_[i]);
                    alloc_.destroy(vec_ + i);
                }
                alloc_.deallocate(vec_, capacity_);
                vec_ = temp;
                capacity_ = n;
            }
    }

    size_type capacity() const {
		return (capacity_);
	}

    // Modifiers
    void clear() {
        for (size_type i = 0; i < size_; i++) {
            alloc_.destroy(vec_ + i);
        }
        size_ = 0;
    }

    iterator insert(const_iterator pos, const T& value ) {
        size_t i = pos - begin();
        pointer ptr = vec_[i];
        if (capacity_ < size_ + 1)
            reserve(1);
        if (i != size_)
            std::copy(pos, end(), ptr);
        alloc_.construct(vec_[i], value);
        size_++;
        return (iterator(vec_[pos]));
    }

    iterator erase( iterator pos ) {
        size_t i = pos - begin();
        pointer ptr = vec_[i];
        alloc_.destroy(vec_[i]);
        if (i != size_)
            std::copy(pos + 1, end(), ptr);
        size_--;
        return (iterator(vec_[pos]));
    }

    void push_back(const value_type& val) {
        if (!capacity_)
            reserve(1);
        else if (size_ >= capacity_)
            reserve(2 * capacity_);
        alloc_.construct(vec_ + size_++, val);
    }

    void pop_back(void) {
        if (size_ > 0)
            alloc_.destroy(vec_ + --size_);
    }

    void resize (size_type n, value_type val = value_type()){
        if (n > size_)
        {
            if (n > size_ * 2)
                reserve(n);
            for (size_type i = n - size_; i > 0; i--)
                push_back(val);
        }
        else if (n < size_){
            while (size_ > n)
                alloc_.destroy(vec_[size_--]);
        }
    }

    void swap(vector& x) {
        std::swap(alloc_, x.alloc_);
        std::swap(size_, x.size_);
        std::swap(capacity_, x.capacity_);
        std::swap(vec_, x.vec_);
    }

    // Non-member function overloads

    private:
        allocator_type  alloc_;
		size_type      	size_;
		size_t	        capacity_;
		pointer         vec_;
};
    template <class T, class Alloc>
    bool operator==( const vector<T,Alloc>& lhs,
                    const vector<T,Alloc>& rhs ) {
        if (lhs.size() != rhs.size())
            return (false);
        for (size_t i = 0; i < lhs.size(); i++)
            if (lhs[i] != rhs[i])
                return (false);
        return (true);
    }

    template< class T, class Alloc >
    bool operator!=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) {return (!(lhs == rhs));}

    template< class T, class Alloc >
    bool operator<( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) {return(lhs.size() < rhs.size());}

    template< class T, class Alloc >
    bool operator<=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) {return (lhs.size() <= rhs.size());}

    template< class T, class Alloc >
    bool operator>( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) {return (lhs.size() > rhs.size());}

    template< class T, class Alloc >
    bool operator>=( const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs ) {return (lhs.size() >= rhs.size());}
}

#endif
