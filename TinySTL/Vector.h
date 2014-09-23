#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <algorithm>
#include <type_traits>

#include "Allocator.h"
#include "Algorithm.h"
#include "Iterator.h"
#include "ReverseIterator.h"
#include "UninitializedFunctions.h"

namespace TinySTL{
	
	namespace {
		template<class T>
		class viter : public TinySTL::iterator<TinySTL::random_access_iterator_tag, T>{
		private:
			T * ptr_;
		private:
			T *getPtr(){ return ptr_; }
		public:
			viter() :ptr_(0){}
			explicit viter(T *ptr):ptr_(ptr){}
			viter(const viter& vit);
			viter& operator = (const viter& vit);

			operator T* (){ return ptr_; }//change to the primitive pointer type

			T& operator *(){ return *ptr_; }
			T *operator ->(){ return &(operator *()); }
			
			viter& operator ++(){ ++ptr_; return *this; }
			viter operator ++(int){ viter temp = *this; ++(*this); return temp; }
			viter& operator --(){ --ptr_; return *this; }
			viter operator --(int){ viter temp = *this; --(*this); return temp; }

			bool operator == (const viter& vit){ return ptr_ == vit.ptr_; }
			bool operator != (const viter& vit){ return !(*this == vit); }
			viter operator + (const difference_type i){ return viter(ptr_ + i); }
			viter operator - (const difference_type i){ return viter(ptr_ - i); }
			difference_type operator - (const viter& vit){ return (ptr_ - vit.ptr_); }

			friend viter operator + (const viter& vit, const difference_type i);
			friend viter operator + (const difference_type i, const viter& vit);
			friend viter operator - (const viter& vit, const difference_type i);
			friend viter operator - (const difference_type i, const viter& vit);
		};
		template<class T>
		viter<T>::viter(const viter& vit){
				ptr_ = vit.ptr_;
		}
		template<class T>
		viter<T>& viter<T>::operator = (const viter& vit){
			if (this != &vit){
				ptr_ = vit.ptr_;
			}
		}
		template<class T>
		viter<T> operator + (const viter<T>& vit, const typename viter<T>::difference_type i){
			return vit + i;
		}
		template<class T>
		viter<T> operator + (const typename viter<T>::difference_type i, const viter<T>& vit){
			return vit + i;
		}
		template<class T>
		viter<T> operator - (const viter<T>& vit, const typename viter<T>::difference_type i){
			return vit + i;
		}
		template<class T>
		viter<T> operator - (const typename viter<T>::difference_type i, const viter<T>& vit){
			return vit + i;
		}
	}// end of anonymous namespace

	//********* vector *************
	template<class T, class Alloc = allocator<T>>
	class vector{
	private:
		T *start_;
		T *finish_;
		T *endOfStorage_;

		typedef Alloc dataAllocator;
		//Alloc dataAllocator;
	public:
		typedef T									value_type;
		typedef viter<T>							iterator;
		typedef reverse_iterator<T *>			reverse_iterator;
		typedef iterator							pointer;
		typedef T&									reference;
		typedef size_t								size_type;
		typedef typename iterator::difference_type	difference_type;
	public:
		//构造，复制，析构相关函数
		vector()
			:start_(0), finish_(0), endOfStorage_(0){}
		explicit vector(const size_type n);
		vector(const size_type n, const value_type& value);
		template<class InputIterator>
		vector(InputIterator first, InputIterator last);
		vector(const vector& v);
		vector(vector&& v);
		vector& operator = (const vector& v);
		vector& operator = (vector&& v);
		~vector(){ 
			destroyAndDeallocateAll();
		}

		//比较操作相关
		bool operator == (const vector& v);
		bool operator != (const vector& v);

		//迭代器相关
		iterator begin(){ return iterator(start_); }
		iterator end(){ return iterator(finish_); }
		reverse_iterator rbegin(){ return reverse_iterator(end()); }
		reverse_iterator rend(){ return reverse_iterator(begin()); }

		//与容量相关
		difference_type size()const{ return finish_ - start_; }
		difference_type capacity()const{ return endOfStorage_ - start_; }
		bool empty()const{ return start_ == finish_; }
		void resize(size_type n, value_type val = value_type());
		void reserve(size_type n);
		void shrink_to_fit(){ 
			dataAllocator::deallocate(finish_, endOfStorage_ - finish_); 
			endOfStorage_ = finish_;
		}

		//访问元素相关
		value_type& operator[](const difference_type i){ return *(begin() + i); }
		value_type& front(){ return *(begin()); }
		value_type& back(){ return *(--end()); }
		pointer data(){ return start_; }

		//修改容器相关的操作
		//清空容器，销毁容器中的所有对象并使容器的size为0，但不回收容器已有的空间
		void clear(){
			dataAllocator::destroy(start_, finish_);
			finish_ = start_;
		}
		void swap(vector& v){
			if (this != &v){
				std::swap(start_, v.start_);
				std::swap(finish_, v.finish_);
				std::swap(endOfStorage_, v.endOfStorage_);
			}
		}
		void push_back(const value_type& value);
		void pop_back(){
			--finish_;
			dataAllocator::destroy(finish_);
		}
		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, const size_type& n, const value_type& val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		//容器的空间配置器相关
		Alloc get_allocator(){ return dataAllocator; }
	private:
		void destroyAndDeallocateAll(){
			if (capacity() != 0){
				dataAllocator::destroy(start_, finish_);
				dataAllocator::deallocate(start_, capacity());
			}
		}
		void allocateAndFillN(const size_type n, const value_type& value){
			start_ = dataAllocator::allocate(n);
			TinySTL::uninitialized_fill_n(start_, n, value);
			finish_ = endOfStorage_ = start_ + n;
		}
		template<class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last){
			start_ = dataAllocator::allocate(last - first);
			finish_ = TinySTL::uninitialized_copy(first, last, start_);
			endOfStorage_ = finish_;
		}

		template<class InputIterator>
		void vector_aux(InputIterator first, InputIterator last, std::false_type){
			allocateAndCopy(first, last);
		}
		template<class Integer>
		void vector_aux(Integer n, const value_type& value, std::true_type){
			allocateAndFillN(n, value);
		}
		template<class InputIterator>
		void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type);
		template<class Integer>
		void insert_aux(iterator position, Integer n, const value_type& value, std::true_type);
		template<class InputIterator>
		void reallocateAndCopy(iterator position, InputIterator first, InputIterator last);
		void reallocateAndFillN(iterator position, const size_type& n, const value_type& val);
		size_type getNewCapacity(size_type len)const{
			size_type oldCapacity = endOfStorage_ - start_;
			auto res = std::max(oldCapacity, len);
			size_type newCapacity = (oldCapacity != 0 ? (oldCapacity + res) : 1);
			return newCapacity;
		}
	public:
		template<class T, class Alloc>
		friend bool operator == (const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
		template<class T, class Alloc>
		friend bool operator != (const vector<T, Alloc>& v1, const vector<T, Alloc>& v2);
	};// end of class vector

	//***********************构造，复制，析构相关***********************
	template<class T, class Alloc>
	vector<T, Alloc>::vector(const size_type n){
		allocateAndFillN(n, value_type());
	}
	template<class T, class Alloc>
	vector<T, Alloc>::vector(const size_type n, const value_type& value){
		allocateAndFillN(n, value);
	}
	template<class T, class Alloc>
	template<class InputIterator>
	vector<T, Alloc>::vector(InputIterator first, InputIterator last){
		//处理指针和数字间的区别的函数
		vector_aux(first, last, typename std::is_integral<InputIterator>::type());
	}
	template<class T, class Alloc>
	vector<T, Alloc>::vector(const vector& v){
		allocateAndCopy(v.start_, v.finish_);
	}
	template<class T, class Alloc>
	vector<T, Alloc>::vector(vector&& v){
		start_ = v.start_;
		finish_ = v.finish_;
		endOfStorage_ = v.endOfStorage_;
		v.start_ = v.finish_ = v.endOfStorage_ = 0;
	}
	template<class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator = (const vector& v){
		if (this != &v){
			allocateAndCopy(v.start_, v.finish_);
		}
		return *this;
	}
	template<class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator = (vector&& v){
		if (this != &v){
			destroyAndDeallocateAll();
			start_ = v.start_;
			finish_ = v.finish_;
			endOfStorage_ = v.endOfStorage_;
			v.start_ = v.finish_ = v.endOfStorage_ = 0;
		}
		return *this;
	}
	//*************和容器的容量相关******************************
	template<class T, class Alloc>
	void vector<T, Alloc>::resize(size_type n, value_type val = value_type()){
		if (n < size()){
			dataAllocator::destroy(start_ + n, finish_);
			finish_ = start_ + n;
		}else if (n > size() && n <= capacity()){
			auto lengthOfInsert = n - size();
			finish_ = uninitialized_fill_n(finish_, lengthOfInsert, val);
		}else if (n > capacity()){
			auto lengthOfInsert = n - size();
			T *newStart = dataAllocator::allocate(getNewCapacity(lengthOfInsert));
			T *newFinish = TinySTL::uninitialized_copy(begin(), end(), newStart);
			newFinish = TinySTL::uninitialized_fill_n(newFinish, lengthOfInsert, val);

			destroyAndDeallocateAll();
			start_ = newStart;
			finish_ = newFinish;
			endOfStorage_ = start_ + n;
		}
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::reserve(size_type n){
		if (n <= capacity())
			return;
		T *newStart = dataAllocator::allocate(n);
		T *newFinish = TinySTL::uninitialized_copy(begin(), end(), newStart);
		destroyAndDeallocateAll();

		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = start_ + n;
	}
	//***************修改容器的相关操作**************************
	template<class T,class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator position){
		return erase(position, position + 1);
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last){
		//尾部残留对象数
		difference_type lenOfTail = end() - last;
		//删去的对象数目
		difference_type lenOfRemoved = last - first;
		finish_ = finish_ - lenOfRemoved;
		for (; lenOfTail != 0; --lenOfTail){
			auto temp = (last - lenOfRemoved);
			*temp = *(last++);
		}
		return viter<T>(first);
	}
	template<class T, class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::reallocateAndCopy(iterator position, InputIterator first, InputIterator last){
		difference_type newCapacity = getNewCapacity(last - first);

		T *newStart = dataAllocator::allocate(newCapacity);
		T *newEndOfStorage = newStart + newCapacity;
		T *newFinish = TinySTL::uninitialized_copy(begin(), position, newStart);
		newFinish = TinySTL::uninitialized_copy(first, last, newFinish);
		newFinish = TinySTL::uninitialized_copy(position, end(), newFinish);

		destroyAndDeallocateAll();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = newEndOfStorage;
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::reallocateAndFillN(iterator position, const size_type& n, const value_type& val){
		difference_type newCapacity = getNewCapacity(n);

		T *newStart = dataAllocator::allocate(newCapacity);
		T *newEndOfStorage = newStart + newCapacity;
		T *newFinish = TinySTL::uninitialized_copy(begin(), position, newStart);
		newFinish = TinySTL::uninitialized_fill_n(newFinish, n, val);
		newFinish = TinySTL::uninitialized_copy(position, end(), newFinish);

		destroyAndDeallocateAll();
		start_ = newStart;
		finish_ = newFinish;
		endOfStorage_ = newEndOfStorage;
	}
	template<class T, class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::insert_aux(iterator position,
									InputIterator first, 
									InputIterator last, 
									std::false_type){
		difference_type locationLeft = endOfStorage_ - finish_; // the size of left storage
		difference_type locationNeed = last - first;

		if (locationLeft >= locationNeed){
			auto tempPtr = end() - 1;
			for (; tempPtr - position >= 0; --tempPtr){//move the [position, finish_) back
				*(tempPtr + locationNeed) = *tempPtr;
			}
			TinySTL::uninitialized_copy(first, last, position);
			finish_ += locationNeed;
		}else{
			reallocateAndCopy(position, first, last);
		}
	}
	template<class T, class Alloc>
	template<class Integer>
	void vector<T, Alloc>::insert_aux(iterator position, Integer n, const value_type& value, std::true_type){
		assert(n != 0);
		difference_type locationLeft = endOfStorage_ - finish_; // the size of left storage
		difference_type locationNeed = n;

		if (locationLeft >= locationNeed){
			auto tempPtr = end() - 1;
			for (; tempPtr - position >= 0; --tempPtr){//move the [position, finish_) back
				*(tempPtr + locationNeed) = *tempPtr;
			}
			TinySTL::uninitialized_fill_n(position, n, value);
			finish_ += locationNeed;
		}
		else{
			reallocateAndFillN(position, n, value);
		}
	}
	template<class T, class Alloc>
	template<class InputIterator>
	void vector<T, Alloc>::insert(iterator position, InputIterator first, InputIterator last){
		insert_aux(position, first, last, typename std::is_integral<InputIterator>::type());
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::insert(iterator position, const size_type& n, const value_type& val){
		insert_aux(position, n, val, typename std::is_integral<size_type>::type());
	}
	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator position, const value_type& val){
		insert(position, 1, val);
		return position;
	}
	template<class T, class Alloc>
	void vector<T, Alloc>::push_back(const value_type& value){
		insert(end(), value);
	}
	//***********逻辑比较操作相关*******************
	template<class T, class Alloc>
	bool vector<T, Alloc>::operator == (const vector& v){
		if (size() != v.size()){
			return false;
		}
		else{
			auto ptr1 = start_;
			auto ptr2 = v.start_;
			for (; ptr1 != finish_ && ptr2 != v.finish_; ++ptr1, ++ptr2){
				if (*ptr1 != *ptr2)
					return false;
			}
			return true;
		}
	}
	template<class T, class Alloc>
	bool vector<T, Alloc>::operator != (const vector& v){
		return !(*this == v);
	}
	template<class T, class Alloc>
	bool operator == (const vector<T, Alloc>& v1, const vector<T, Alloc>& v2){
		return v1 == v2;
	}
	template<class T, class Alloc>
	bool operator != (const vector<T, Alloc>& v1, const vector<T, Alloc>& v2){
		return !(v1 == v2);
	}
}

#endif