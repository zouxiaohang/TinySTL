#ifndef _CIRCULAR_BUFFER_IMPL_H_
#define _CIRCULAR_BUFFER_IMPL_H_

namespace TinySTL{
	namespace Detail{
		template<class T, size_t N, class Alloc>
		int cb_iter<T, N, Alloc>::prevIndex(int index){
			--index;
			index = (index == -1 ? index + N : index);
			return index;
		}
		template<class T, size_t N, class Alloc>
		bool cb_iter<T, N, Alloc>::operator == (const cb_iter& it)const{
			return (container_ == it.container_) &&
				(ptr_ == it.ptr_) && (index_ == it.index_);
		}
		template<class T, size_t N, class Alloc>
		bool cb_iter<T, N, Alloc>::operator != (const cb_iter& it)const{
			return !((*this) == it);
		}
		template<class T, size_t N, class Alloc>
		cb_iter<T, N, Alloc>& cb_iter<T, N, Alloc>::operator ++(){
			setIndex_(nextIndex(index_));
			setPtr_(container_->start_ + index_);
			return *this;
		}
		template<class T, size_t N, class Alloc>
		cb_iter<T, N, Alloc> cb_iter<T, N, Alloc>::operator ++(int){
			cb_iter temp(*this);
			++(*this);
			return temp;
		}
		template<class T, size_t N, class Alloc>
		cb_iter<T, N, Alloc>& cb_iter<T, N, Alloc>::operator --(){
			setIndex_(prevIndex(index_));
			setPtr_(container_->start_ + index_);
			return *this;
		}
		template<class T, size_t N, class Alloc>
		cb_iter<T, N, Alloc> cb_iter<T, N, Alloc>::operator --(int){
			cb_iter temp(*this);
			--(*this);
			return temp;
		}
		template<class T, size_t N, class Alloc>
		cb_iter<T, N, Alloc>& cb_iter<T, N, Alloc>::operator = (const cb_iter& cit){
			if (this != &cit){
				ptr_ = cit.ptr_;
				index_ = cit.index_;
				container_ = cit.container_;
			}
			return *this;
		}
		template<class T, size_t N, class Alloc>
		cb_iter<T, N, Alloc> operator +(const cb_iter<T, N, Alloc>& cit, std::ptrdiff_t i){
			int real_i = i % (std::ptrdiff_t)N;//assume i >= 0
			if (real_i < 0)
				real_i += N;
			cb_iter<T, N, Alloc> res = cit;
			res.setIndex_(res.index_ + real_i);
			res.setPtr_(res.ptr_ + res.index_);
			return res;
		}
		template<class T, size_t N, class Alloc>
		cb_iter<T, N, Alloc> operator -(const cb_iter<T, N, Alloc>& cit, std::ptrdiff_t i){
			cb_iter<T, N, Alloc> res = cit;
			return (res + (-i));
		}
	}//end of Detail namespace

	//**********构造，复制，析构相关*****************
	template<class T, size_t N, class Alloc>
	circular_buffer<T, N, Alloc>::~circular_buffer(){
		clear();
		dataAllocator::deallocate(start_, size_);
	}
	template<class T, size_t N, class Alloc>
	circular_buffer<T, N, Alloc>::circular_buffer(const int& n, const value_type& val = value_type()){
		assert(n != 0);
		allocateAndFillN(n, val);
	}
	template<class T, size_t N, class Alloc>
	template<class InputIterator>
	circular_buffer<T, N, Alloc>::circular_buffer(InputIterator first, InputIterator last){
		//bug fix
		//2015.01.05
		assert(first != last);
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
		}
		else{
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
	template<class T, size_t N, class Alloc>
	void circular_buffer<T, N, Alloc>::clear(){
		for (; !empty(); indexOfHead = nextIndex(indexOfHead), --size_){
			dataAllocator::destroy(start_ + indexOfHead);
		}
		indexOfHead = indexOfTail = 0;
	}
	template<class T, size_t N, class Alloc>
	bool circular_buffer<T, N, Alloc>::operator == (circular_buffer& cb){
		auto it1 = first(), it2 = cb.first();
		for (; it1 != last() && it2 != cb.last(); ++it1, ++it2){
			if (*it1 != *it2) return false;
		}
		return (it1 == last()) && (it2 == cb.last()) && (*(last()) == *(cb.last()));
	}
	template<class T, size_t N, class Alloc>
	bool circular_buffer<T, N, Alloc>::operator != (circular_buffer& cb){
		return !(*this == cb);
	}
	template<class T, size_t N, class Alloc>
	void circular_buffer<T, N, Alloc>::allocateAndFillN(const int& n, const value_type& val){//only for ctor
		start_ = dataAllocator::allocate(N);
		finish_ = start_ + N;
		indexOfHead = 0;
		if (N <= n){
			finish_ = TinySTL::uninitialized_fill_n(start_, N, val);
			indexOfTail = N - 1;
			size_ = N;
		}
		else{//N > n
			finish_ = TinySTL::uninitialized_fill_n(start_, n, val);
			finish_ = TinySTL::uninitialized_fill_n(finish_, N - n, value_type());
			indexOfTail = n - 1;
			size_ = n;
		}
	}
	template<class T, size_t N, class Alloc>
	template<class InputIterator>
	void circular_buffer<T, N, Alloc>::allocateAndCopy(InputIterator first, InputIterator last){//only for ctor
		int n = last - first;
		start_ = dataAllocator::allocate(N);
		indexOfHead = 0;
		if (N <= n){
			finish_ = TinySTL::uninitialized_copy(first, first + N, start_);
			indexOfTail = N - 1;
			size_ = N;
		}
		else{//N > n
			finish_ = TinySTL::uninitialized_copy(first, last, start_);
			finish_ = TinySTL::uninitialized_fill_n(finish_, N - n, value_type());
			indexOfTail = n - 1;
			size_ = n;
		}
	}
	template<class T, size_t N, class Alloc>
	void circular_buffer<T, N, Alloc>::copyAllMembers(const circular_buffer& cb){
		start_ = cb.start_;
		finish_ = cb.finish_;
		indexOfHead = cb.indexOfHead;
		indexOfTail = cb.indexOfTail;
		size_ = cb.size_;
	}
	template<class T, size_t N, class Alloc>
	void circular_buffer<T, N, Alloc>::zeroCircular(circular_buffer& cb){
		cb.start_ = cb.finish_ = 0;
		cb.indexOfHead = cb.indexOfTail = cb.size_ = 0;
	}
	template<class T, size_t N, class Alloc>
	void circular_buffer<T, N, Alloc>::clone(const circular_buffer& cb){
		start_ = dataAllocator::allocate(N);
		finish_ = start_ + N;
		size_ = N;
		indexOfHead = cb.indexOfHead;
		indexOfTail = cb.indexOfTail;
		TinySTL::uninitialized_copy(cb.start_, cb.finish_, start_);
	}
}

#endif