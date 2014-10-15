#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "Allocator.h"
#include "ReverseIterator.h"

namespace TinySTL{
	//class of deque iterator
	class diter{};

	//class of deque
	template<class T, class Alloc = TinySTL::allocator<T>>
	class deque{
	public:
		typedef T value_type;
		typedef diter iterator;
		typedef const iterator const_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef reverse_iterator<const_iterator> const_reverse_iterator;
		typedef T& reference;
		typedef const reference const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
	private:
		typedef Alloc dataAllocator;

		T *bucks;
	public:
		explicit deque(const allocator_type& alloc = allocator_type());
		explicit deque(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
		template <class InputIterator>
		deque(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
		deque(const deque& x);

		~deque();

		deque& operator= (const deque& x);
		deque& operator= (deque&& x);

		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;
		const_iterator cbegin() const;
		const_iterator cend() const;
		const_reverse_iterator crbegin() const;
		const_reverse_iterator crend() const;

		size_type size() const;
		size_type max_size() const;
		void resize(size_type n, value_type val = value_type());
		bool empty() const;
		void shrink_to_fit();

		reference operator[] (size_type n);
		const_reference operator[] (size_type n) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;

		void push_back(const value_type& val);
		void push_back(value_type&& val);
		void push_front(const value_type& val);
		void push_front(value_type&& val);
		void pop_back();
		void pop_front();
		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, size_type n, const value_type& val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		void swap(deque& x);
		void clear();
	public:
		template <class T, class Alloc>
		friend bool operator== (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);
		template <class T, class Alloc>
		friend bool operator!= (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);
		template <class T, class Alloc>
		friend bool operator<  (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);
		template <class T, class Alloc>
		friend bool operator<= (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);
		template <class T, class Alloc>
		friend bool operator>  (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);
		template <class T, class Alloc>
		friend bool operator>= (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);
		template <class T, class Alloc>
		friend void swap(deque<T, Alloc>& x, deque<T, Alloc>& y);
	};//end of deque
}
#endif