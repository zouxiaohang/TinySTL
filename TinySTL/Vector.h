#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <type_traits>

#include "Allocator.h"
#include "Iterator.h"
#include "UninitializedFunctions.h"

namespace TinySTL{
	
	namespace {
		template<class T>
		class viter: public iterator<random_access_iterator<T, ptrdiff_t>, T>{
		private:
			T * ptr_;
		private:
			T *getPtr(){ return ptr_; }
		public:
			viter() :ptr_(0){}
			explicit viter(T *ptr):ptr_(ptr){}
			viter(const viter& vit);
			viter& operator = (const viter& vit);

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

	template<class T, class Alloc = allocator<T>>
	class vector{
	private:
		T *start_;
		T *finish_;
		T *endOfStorage_;

		typedef Alloc dataAllocator;
		//Alloc dataAllocator;
	public:
		typedef T			value_type;
		typedef viter<T>	iterator;
		typedef iterator	pointer;
		typedef T&			reference;
		typedef size_t		size_type;
		typedef typename iterator::difference_type difference_type;
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
		~vector(){ 
			dataAllocator::destroy(start_, finish_); 
			dataAllocator::deallocate(start_, endOfStorage_ - start_); 
		}

		//迭代器相关
		iterator begin(){ return iterator(start_); }
		iterator end(){ return iterator(finish_); }

		//与容量相关
		difference_type size()const{ return finish_ - start_; }
		difference_type capacity()const{ return endOfStorage_ - start_; }
		bool empty()const{ return start_ == finish_; }

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
		//TODO
		void push_back(const value_type& value);
		void pop_back(){
			--finish_;
			dataAllocator::destroy(finish_);
		}
		//TODO
		iterator insert(iterator position, const value_type& val);
		//TODO
		void insert(iterator position, size_type n, const value_type& val);
		//TODO
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		//TODO
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);

		//容器的空间配置器相关
		Alloc get_allocator(){ return dataAllocator; }
	private:
		void allocateAndFillN(const size_type n, const value_type& value){
			start_ = dataAllocator::allocate(n);
			uninitialized_fill_n(start_, n, value);
			finish_ = endOfStorage_ = start_ + n;
		}
		template<class InputIterator>
		void allocateAndCopy(InputIterator first, InputIterator last){
			start_ = dataAllocator::allocate(last - first);
			finish_ = uninitialized_copy(first, last, start_);
			endOfStorage_ = finish_;
		}

		template<class InputIterator>
		void vector_aux(InputIterator first, InputIterator last, std::false_type){
			allocateAndCopy(first, last);
		}
		template<class Integer>
		void vector_aux(Integer n, Integer value, std::true_type){
			allocateAndFillN(n, value);
		}
	};
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
		v.clear();
	}
	template<class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator = (const vector& v){
		if (this != &v){
			allocateAndCopy(v.start_, v.finish_);
		}
		return *this;
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
}

#endif