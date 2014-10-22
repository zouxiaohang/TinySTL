#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "Allocator.h"
#include "Iterator.h"
#include "ReverseIterator.h"

namespace TinySTL{
	template<class T, class Alloc = allocator<T>>
	class deque;
	namespace{
		//class of deque iterator
		template<class T>
		class dq_iter :public iterator<bidirectional_iterator_tag, T>{
		private:
			template<class T, class Alloc>
			friend class deque;
		private:
			typedef TinySTL::deque<T>* cntrPtr;
			size_t mapIndex_;
			T *cur_;
			cntrPtr container_;
		public:
			dq_iter() :mapIndex_(-1), cur_(0), container_(0){}
			dq_iter(size_t index, T *ptr, cntrPtr container)
				:mapIndex_(index), cur_(ptr), container_(container){}
			dq_iter(const dq_iter& it) 
				:mapIndex_(it.mapIndex_), cur_(it.cur_), container_(it.container_){}
			dq_iter& operator = (const dq_iter& it){
				if (this != it){
					mapIndex_ = it->mapIndex_;
					cur_ = it->cur_;
					container_ = it->container_;
				}
				return *this;
			}
			reference operator *(){ return *cur_; }
			pointer operator ->(){ return &(operator*()); }
			dq_iter& operator ++(){
				if (cur_ != getBuckTail(mapIndex_))//+1后还在同一个桶里
					++cur_;
				else{
					++mapIndex_;
					cur_ = getBuckHead(mapIndex_);
				}
				return *this;
			}
			dq_iter operator ++(int){
				auto res = *this;
				++(*this);
				return res;
			}
			dq_iter& operator --(){
				if (cur_ != getBuckHead(mapIndex_))//当前不指向桶头
					--cur_;
				else{
					--mapIndex_;
					cur_ = getBuckTail(mapIndex_);
				}
				return *this;
			}
			dq_iter operator --(int){
				auto res = *this;
				--(*this);
				return res;
			}
			bool operator ==(const dq_iter& it)const{
				return ((mapIndex_ == it.mapIndex_) &&
					(cur_ == it.cur_) && (container_ == it.container_));
			}
			bool operator !=(const dq_iter& it)const{
				return !(*this == it);
			}
		private:
			T *getBuckTail(size_t mapIndex)const{
				return container_[mapIndex] + container_->getBuckSize() - 1;
			}
			T *getBuckHead(size_t mapIndex)const{
				return container_->map_[mapIndex];
			}
		public:
			template<class T>
			friend dq_iter<T> operator + (const dq_iter<T>& it, typename dq_iter<T>::difference_type n);
			template<class T>
			friend dq_iter<T> operator + (typename dq_iter<T>::difference_type n, const dq_iter<T>& it);
			template<class T>
			friend dq_iter<T> operator - (const dq_iter<T>& it, typename dq_iter<T>::difference_type n);
			template<class T>
			friend dq_iter<T> operator - (typename dq_iter<T>::difference_type n, const dq_iter<T>& it);
			template<class T>
			friend typename dq_iter<T>::difference_type operator - (const dq_iter<T>& it1, const dq_iter<T>& it2);
		};
		template<class T>
		dq_iter<T> operator + (const dq_iter<T>& it, typename dq_iter<T>::difference_type n){//assume n >= 0
			dq_iter<T> res(it);
			auto m = res.getBuckTail(res.mapIndex_) - res.cur_;
			if (n <= m){//前进n步仍在同一个桶中
				res.cur_ += n;
			}
			else{
				n = n - m;
				res.mapIndex_ += n / res.container_->getBuckSize();
				res.cur_ = res.getBuckHead(res.mapIndex_) + n % res.container_->getBuckSize();
			}
			return res;
		}
		template<class T>
		dq_iter<T> operator + (typename dq_iter<T>::difference_type n, const dq_iter<T>& it){
			return (it + n);
		}
		template<class T>
		dq_iter<T> operator - (const dq_iter<T>& it, typename dq_iter<T>::difference_type n){//assume n >= 0
			dq_iter<T> res(it);
			auto m = res.cur_ - res.getBuckHead(res.mapIndex_);
			if (n <= m)//后退n步还在同一个桶中
				res.cur_ -= n;
			else{
				n = n - m;
				res.mapIndex_ -= n / res.container_->getBuckSize();
				res.cur_ = res.getBuckTail(res.mapIndex_) - n % res.container_->getBuckSize();
			}
			return res;
		}
		template<class T>
		dq_iter<T> operator - (typename dq_iter<T>::difference_type n, const dq_iter<T>& it){
			return (it - n);
		}
		template<class T>
		typename dq_iter<T>::difference_type operator - (const dq_iter<T>& it1, const dq_iter<T>& it2){
			return typename dq_iter<T>::difference_type(it1.container_->getBuckSize()) * (it1.mapIndex_ - it2.mapIndex_ - 1)
				+ (it1.cur_ - it1.getBuckHead(it1.mapIndex_)) + (it2.getBuckTail(it2.mapIndex_) - it2.cur_);
		}
	}

	//class of deque
	template<class T, class Alloc>
	class deque{
	private:
		template<class T>
		friend class dq_iter;
	public:
		typedef T value_type;
		typedef dq_iter<T> iterator;
		typedef const iterator const_iterator;
		typedef T& reference;
		typedef const reference const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef Alloc allocator_type;
	private:
		typedef Alloc dataAllocator;
		enum class EBucksSize{BUCKSIZE = 64};
	private:
		iterator beg_, end_;
		size_t mapSize_;
		T **map_;
	public:
		deque();
		explicit deque(size_type n, const value_type& val = value_type());
		template <class InputIterator>
		deque(InputIterator first, InputIterator last);
		deque(const deque& x);

		~deque(){
			for (int i = 0; i != mapSize_; ++i)
				dataAllocator::deallocate(map_[i], getBuckSize());
			delete[] map_;
		}

		deque& operator= (const deque& x);
		deque& operator= (deque&& x);

		iterator begin(){ return beg_; }
		const_iterator begin() const{ return beg_; }
		iterator end(){ return end_; }
		const_iterator end() const{return end_}
		const_iterator cbegin() const{ return beg_; }
		const_iterator cend() const{ return end_; }

		size_type size() const{ return end() - begin(); }
		bool empty() const{ return begin() == end(); }

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
		void swap(deque& x);
		void clear();
	private:
		T *getABuck(){
			return dataAllocator::allocate(getBuckSize);
		}
		T** getANewMap(const size_t size){
			mapSize_ = size;
			return new T*[mapSize_](0);
		}
		/*size_t getNewMapSize(const size_t size){
			return (size == 0 ? 1 : size * 1.5);
		}*/
		size_t getBuckSize()const{
			return (size_t)EBucksSize::BUCKSIZE;
		}
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

	template<class T, class Alloc>
	deque<T, Alloc>::deque()
		:mapSize_(0), map_(0){}
	template<class T, class Alloc>
	deque<T, Alloc>::deque(size_type n, const value_type& val = value_type()){
		auto nMap = n / getBuckSize() + 1 + 2;
		map_ = getANewMap(nMap);
	}
	//template<class T, class Alloc>
	//template <class InputIterator>
	//deque<T, Alloc>::deque(InputIterator first, InputIterator last);
	//template<class T, class Alloc>
	//deque<T, Alloc>::deque(const deque& x);
}
#endif