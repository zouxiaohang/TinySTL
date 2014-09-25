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
			//fuck
			//fuck
			//fuck
			//fuck
			//wish to do like this, but buggy
			//for (auto it = cb.first(); it <= cb.last(); ++it)
			//	{ cout << *it << endl; }
			//fuck
			//fuck
			//fuck
			bool operator <= (const cb_iter& it)const{//fuck
				if (*this == it) return true;
				auto indexOfThis = ptr_ - container_->start_;
				auto indexOfIt = it.ptr_ - it.container_->start_;

				if (indexOfThis < indexOfIt){
					if (container_->indexOfHead < indexOfThis || container_->indexOfHead > indexOfIt)
						return true;
					else if (container_->indexOfHead < indexOfIt && container_->indexOfHead > indexOfThis)
						return false;
				}else{//indexOfThis > indexOfIt
					if (container_->indexOfHead < indexOfIt || container_->indexOfHead > indexOfThis)
						return false;
					else if (container_->indexOfHead < indexOfThis && container_->indexOfHead > indexOfIt)
						return true;
				}
			}
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
		typedef T				value_type;
		typedef cb_iter<T, N>	iterator;
		typedef iterator		pointer;
		typedef T&				reference;
		typedef int				size_type;
		typedef ptrdiff_t		difference_type;
	private:
		T *start_;
		T *finish_;
		int indexOfHead;//the first position
		int indexOfTail;//the last position 
		size_type size_;

		typedef Alloc dataAllocator;
	public:
		explicit circular_buffer(const int& n, const value_type& val = value_type());
		template<class InputIterator>
		circular_buffer(InputIterator first, InputIterator last);
		circular_buffer(const circular_buffer& cb);
		circular_buffer& operator = (const circular_buffer& cb);
		circular_buffer& operator = (circular_buffer&& cb);
		circular_buffer(circular_buffer&& cb);
		~circular_buffer(){
			clear();
			dataAllocator::deallocate(start_, size_);
		}

		bool full(){ return size_ == N; }
		bool empty(){ return size_ == 0; }
		difference_type capacity(){ return finish_ - start_; }
		size_type size(){ return size_; }
		void clear(){ 
			for (; !empty(); indexOfHead = nextIndex(indexOfHead), --size_){
				dataAllocator::destroy(start_ + indexOfHead);
			}
			indexOfHead = indexOfTail = 0;
		}

		iterator first(){ return iterator(start_ + indexOfHead, this); }
		iterator last(){ return iterator(start_ + indexOfTail, this); }

		reference operator [](size_type i){ return *(start_ + i); }
		reference front(){ return *(start_ + indexOfHead); }
		reference back(){ return *(start_ + indexOfTail); }
		void push_back(const T& val);
		void pop_front();

		bool operator == (circular_buffer& cb){
			auto it1 = first(), it2 = cb.first();
			for (;it1 != last() && it2 != cb.last(); ++it1, ++it2){
				if (*it1 != *it2) return false;
			}
			return (it1 == last()) && (it2 == cb.last()) && (*(last()) == *(cb.last()));
		}
		bool operator != (circular_buffer& cb){
			return !(*this == cb);
		}

		Alloc get_allocator(){ return dataAllocator; }
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
				size_ = N;
			}else{//N > n
				finish_ = TinySTL::uninitialized_copy(first, last, start_);
				finish_ = TinySTL::uninitialized_fill_n(finish_, N - n, value_type());
				indexOfTail = n - 1;
				size_ = n;
			}
		}
		int nextIndex(int index){ return (index + 1) % N; }
		void copyAllMembers(const circular_buffer& cb){
			start_ = cb.start_;
			finish_ = cb.finish_;
			indexOfHead = cb.indexOfHead;
			indexOfTail = cb.indexOfTail;
			size_ = cb.size_;
		}
		void zeroCircular(circular_buffer& cb){
			cb.start_ = cb.finish_ = 0;
			cb.indexOfHead = cb.indexOfTail = cb.size_ = 0;
		}
		void clone(const circular_buffer& cb){
			start_ = dataAllocator::allocate(N);
			finish_ = start_ + N;
			size_ = N;
			indexOfHead = cb.indexOfHead;
			indexOfTail = cb.indexOfTail;
			TinySTL::uninitialized_copy(cb.start_, cb.finish_, start_);
		}
	public:
		template<class T, size_t N, class Alloc>
		friend std::ostream& operator <<(std::ostream& os, circular_buffer<T, N, Alloc>& cb);
	};//end of circular buffer

	//**********构造，复制，析构相关*****************
	template<class T, size_t N, class Alloc>
	circular_buffer<T, N, Alloc>::circular_buffer(const int& n, const value_type& val = value_type()){
		assert(n != 0);
		allocateAndFillN(n, val);
	}
	template<class T, size_t N, class Alloc>
	template<class InputIterator>
	circular_buffer<T, N, Alloc>::circular_buffer(InputIterator first, InputIterator last){
		allocateAndCopy(first, last);
	}
	template<class T, size_t N, class Alloc>
	circular_buffer<T, N, Alloc>::circular_buffer(const circular_buffer<T, N, Alloc>& cb){
		clone(cb);
	}
	template<class T, size_t N, class Alloc>
	circular_buffer<T, N, Alloc>::circular_buffer(circular_buffer<T, N, Alloc>&& cb){
		copyAllMembers(cb);
		zeroCircular(cb);
	}
	template<class T, size_t N, class Alloc>
	circular_buffer<T, N, Alloc>& circular_buffer<T, N, Alloc>::operator = (const circular_buffer<T, N, Alloc>& cb){
		if (this != &cb){
			clone(cb);
		}
		return *this;
	}
	template<class T, size_t N, class Alloc>
	circular_buffer<T, N, Alloc>& circular_buffer<T, N, Alloc>::operator = (circular_buffer<T, N, Alloc>&& cb){
		if (*this != cb){
			copyAllMembers(cb);
			zeroCircular(cb);
		}
		return *this;
	}
	//************插入，删除相关***********************
	template<class T, size_t N, class Alloc>
	void circular_buffer<T, N, Alloc>::push_back(const T& val){
		if (full()){
			indexOfTail = nextIndex(indexOfTail);
			dataAllocator::construct(start_ + indexOfTail, val);
			indexOfHead = nextIndex(indexOfHead);
		}else{
			indexOfTail = nextIndex(indexOfTail);
			dataAllocator::construct(start_ + indexOfTail, val);
			++size_;
		}
	}
	template<class T, size_t N, class Alloc>
	void circular_buffer<T, N, Alloc>::pop_front(){
		if (empty())
			throw;
		dataAllocator::destroy(start_ + indexOfHead);
		indexOfHead = nextIndex(indexOfHead);
		--size_;
	}

	template<class T, size_t N, class Alloc>
	std::ostream& operator <<(std::ostream& os, circular_buffer<T, N, Alloc>& cb){
		circular_buffer<T, N, Alloc>::size_type size = cb.size();
		if (!cb.empty()){
			os << "(";
			for (auto it = cb.first(); it != cb.last() && size != 0; ++it, --size){
				os << *it << ", ";
			}
			os << *(cb.last()) << ")";
		}
		return os;
	}
}

#endif