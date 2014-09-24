#ifndef _CIRCULAR_BUFFER_H_
#define _CIRCULAR_BUFFER_H_

#include "Allocator.h"
#include "Iterator.h"
#include "UninitializedFunctions.h"

namespace TinySTL{
	template<class T, size_t N, class Alloc>
	class circular_buffer;
	namespace{
		//the iterator of circular buffer
		template<class T, size_t N, class Alloc = allocator<T>>
		class cb_iter:iterator<bidirectional_iterator_tag, T>{
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

			cb_iter& operator ++(){
				setIndex_(++index_ % N);
				setPtr_(container_->start_ + index_);
				return *this;
			}
			cb_iter operator ++(int){
				cb_iter temp(*this);
				++(*this);
				return temp;
			}
			cb_iter& operator --(){
				int index = index_ - 1;
				index = (index == -1 ? index + N : index);
				setIndex_(index);
				setPtr_(container_->start_ + index_);
				return *this;
			}
			cb_iter operator --(int){
				cb_iter temp(*this);
				--(*this);
				return temp;
			}
		private:
			void setIndex_(int index){ index_ = index; }
			void setPtr_(T *ptr){ ptr_ = ptr; }
		};
	}//end of anonymous namespace

	//circular buffer
	template<class T, size_t N, class Alloc = allocator<T>>
	class circular_buffer{
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
		int indexOfHead;
		int indexOfTail;

		typedef Alloc dataAllocator;
	public:
		circular_buffer() :
			start_(0), finish_(0), indexOfHead(0), indexOfTail(0){}
		explicit circular_buffer(const int& n, const value_type& val = value_type());
		template<class InputIterator>
		circular_buffer(InputIterator first, InputIterator last);

		//just for test
		T *begin(){ return start_; }
		T *end(){ return finish_; }
	private:
		void allocateAndFillN(const int& n, const value_type& val){
			start_ = dataAllocator::allocate(N);
			finish_ = start_ + N;
			indexOfHead = indexOfTail = 0;
			if (N <= n){
				finish_ = TinySTL::uninitialized_fill_n(start_, N, val);
			}else{//N > n
				finish_ = TinySTL::uninitialized_fill_n(start_, n, val);
				finish_ = TinySTL::uninitialized_fill_n(finish_, N - n, value_type());
			}
		}
		template<class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last){
			int n = last - first;
			start_ = dataAllocator::allocate(N);
			indexOfHead = indexOfTail = 0;
			if (N <= n){
				finish_ = TinySTL::uninitialized_copy(first, first + N, start_);
			}else{//N > n
				finish_ = TinySTL::uninitialized_copy(first, last, start_);
				finish_ = TinySTL::uninitialized_fill_n(finish_, N - n, value_type());
			}
		}
	};
	template<class T, size_t N, class Alloc>
	circular_buffer<T, N, Alloc>::circular_buffer(const int& n, const value_type& val = value_type()){
		allocateAndFillN(n, val);
	}
	template<class T, size_t N, class Alloc>
	template<class InputIterator>
	circular_buffer<T, N, Alloc>::circular_buffer(InputIterator first, InputIterator last){
		allocateAndCopy(first, last);
	}
}

#endif