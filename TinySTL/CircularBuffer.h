#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

#include "Allocator.h"
#include "Iterator.h"
#include "UninitializedFunctions.h"

#include <cassert>

namespace TinySTL{
	template<class T, size_t N, class Alloc>
	class circular_buffer;
	namespace{
		//the iterator of circular buffer
		template<class T, size_t N, class Alloc = allocator<T>>
		class cb_iter:iterator<bidirectional_iterator_tag, T>{//bidirectional iterator
		private:
			typedef circular_buffer<T, N, Alloc> cb;
			typedef cb *cbPtr;

			T *ptr_;
			int index_;
			cbPtr container_;
		public:
			cb_iter() :ptr_(0), index_(0), container_(0){}
			explicit cb_iter(T *ptr, cbPtr container) :
				ptr_(ptr), index_(ptr - container->start_), container_(container){}
		public:
			operator T*(){ return ptr_; }
			T& operator *(){ return *ptr_; }
			T *operator ->(){ return &(operator*()); }

			cb_iter& operator ++(){
				setIndex_(nextIndex(index_));
				setPtr_(container_->start_ + index_);
				return *this;
			}
			cb_iter operator ++(int){
				cb_iter temp(*this);
				++(*this);
				return temp;
			}
			cb_iter& operator --(){
				setIndex_(prevIndex(index_));
				setPtr_(container_->start_ + index_);
				return *this;
			}
			cb_iter operator --(int){
				cb_iter temp(*this);
				--(*this);
				return temp;
			}
			bool operator == (const cb_iter& it)const{
				return (container_ == it.container_) &&
					(ptr_ == it.ptr_) && (index_ == it.index_);
			}
			bool operator != (const cb_iter& it)const{
				return !((*this) == it);
			}
			/*bool operator <= (const cb_iter& it)const{
				cb_iter cur = *this;
				for (; cur != container_->last(); ++cur){
					if (cur == it) return true;
				}
				return (cur == it ? true : false);
			}*/
		private:
			void setIndex_(int index){ index_ = index; }
			void setPtr_(T *ptr){ ptr_ = ptr; }
			int nextIndex(int index){ return (++index) % N; }
			int prevIndex(int index){
				--index;
				index = (index == -1 ? index + N : index);
				return index;
			}
		};
	}//end of anonymous namespace

	//circular buffer
	template<class T, size_t N, class Alloc = allocator<T>>
	class circular_buffer{
		template<class T, size_t N, class Alloc>
		friend class cb_iter;
	public:
		typedef T			value_type;
		typedef cb_iter<T, N>	iterator;
		typedef iterator	pointer;
		typedef T&			reference;
		typedef int		size_type;
		typedef ptrdiff_t	difference_type;
	private:
		T *start_;
		T *finish_;
		int indexOfHead;//the first position
		int indexOfTail;//the last position 
		size_type size_;

		typedef Alloc dataAllocator;
	public:
		circular_buffer() :
			start_(0), finish_(0), indexOfHead(0), indexOfTail(0), size_(0){}
		explicit circular_buffer(const int& n, const value_type& val = value_type());
		template<class InputIterator>
		circular_buffer(InputIterator first, InputIterator last);
		~circular_buffer(){
			/*dataAllocator::destroy(start_, finish_);
			dataAllocator::deallocate(start_, finish_);*/
		}

		bool full(){ return size_ == N; }
		bool empty(){ return size_ == 0; }
		difference_type capacity(){ return finish_ - start_; }
		size_type size(){ return size_; }

		//just for test
		/*T *begin(){ return start_; }
		T *end(){ return finish_; }*/
		iterator first(){ return iterator(start_ + indexOfHead, this); }
		iterator last(){ return iterator(start_ + indexOfTail, this); }

		reference operator [](size_type i){ return *(start_ + i); }
	private:
		void allocateAndFillN(const int& n, const value_type& val){//only for ctor
			start_ = dataAllocator::allocate(N);
			finish_ = start_ + N;
			indexOfHead = 0;
			if (N <= n){
				finish_ = TinySTL::uninitialized_fill_n(start_, N, val);
				indexOfTail = N - 1;
				size_ = N;
			}else{//N > n
				finish_ = TinySTL::uninitialized_fill_n(start_, n, val);
				finish_ = TinySTL::uninitialized_fill_n(finish_, N - n, value_type());
				indexOfTail = n - 1;
				size_ = n;
			}
		}
		template<class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last){//only for ctor
			int n = last - first;
			start_ = dataAllocator::allocate(N);
			indexOfHead = 0;
			if (N <= n){
				finish_ = TinySTL::uninitialized_copy(first, first + N, start_);
				indexOfTail = N - 1;
			}else{//N > n
				finish_ = TinySTL::uninitialized_copy(first, last, start_);
				finish_ = TinySTL::uninitialized_fill_n(finish_, N - n, value_type());
				indexOfTail = n - 1;
			}
		}
		int nextIndex(int index){ return ++index % N; }
	};//end of circular buffer
	template<class T, size_t N, class Alloc>
	circular_buffer<T, N, Alloc>::circular_buffer(const int& n, const value_type& val = value_type()){
		assert(n != 0);
		allocateAndFillN(n, val);
	}
	template<class T, size_t N, class Alloc>
	template<class InputIterator>
	circular_buffer<T, N, Alloc>::circular_buffer(InputIterator first, InputIterator last){
		assert((last - first) >= 2);
		allocateAndCopy(first, last);
	}
}

#endif