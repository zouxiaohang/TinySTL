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
		class diter :public iterator<bidirectional_iterator_tag, T>{
		private:
			typedef TinySTL::deque<T>* cntrPtr;
			size_t mapIndex_;
			T *cur_;
			cntrPtr container_;
		public:
			diter() :mapIndex_(-1), cur_(0), container_(0){}
			diter(size_t index, T *ptr, cntrPtr container)
				:mapIndex_(index), cur_(ptr), container_(container){}
			diter(const diter& it) 
				:mapIndex_(it.mapIndex_), cur_(it.cur_), container_(it.container_){}
			diter& operator = (const diter& it){
				if (this != it){
					mapIndex_ = it->mapIndex_;
					cur_ = it->cur_;
					container_ = it->container_;
				}
				return *this;
			}
			reference operator *(){ return *cur_; }
			pointer operator ->(){ return &(operator*()); }
			diter& operator ++(){
				if (cur_ != getBuckTail(mapIndex_))//+1后还在同一个桶里
					++cur_;
				else{
					++mapIndex_;
					cur_ = getBuckHead(mapIndex_);
				}
				return *this;
			}
			diter operator ++(int){
				auto res = *this;
				++(*this);
				return res;
			}
			diter& operator --(){
				if (cur_ != getBuckHead(mapIndex_))//当前不指向桶头
					--cur_;
				else{
					--mapIndex_;
					cur_ = getBuckTail(mapIndex_);
				}
				return *this;
			}
			diter operator --(int){
				auto res = *this;
				--(*this);
				return res;
			}
			bool operator ==(const diter& it)const{
				return ((mapIndex_ == it.mapIndex_) &&
					(cur_ == it.cur_) && (container_ == it.container_));
			}
			bool operator !=(const diter& it)const{
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
			friend diter<T> operator + (const diter<T>& it, typename diter<T>::difference_type n);
			template<class T>
			friend diter<T> operator + (typename diter<T>::difference_type n, const diter<T>& it);
			template<class T>
			friend diter<T> operator - (const diter<T>& it, typename diter<T>::difference_type n);
			template<class T>
			friend diter<T> operator - (typename diter<T>::difference_type n, const diter<T>& it);
			template<class T>
			friend typename diter<T>::difference_type operator - (const diter<T>& it1, const diter<T>& it2);
		};
		template<class T>
		diter<T> operator + (const diter<T>& it, typename diter<T>::difference_type n){//assume n >= 0
			diter<T> res(it);
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
		diter<T> operator + (typename diter<T>::difference_type n, const diter<T>& it){
			return (it + n);
		}
		template<class T>
		diter<T> operator - (const diter<T>& it, typename diter<T>::difference_type n){//assume n >= 0
			diter<T> res(it);
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
		diter<T> operator - (typename diter<T>::difference_type n, const diter<T>& it){
			return (it - n);
		}
		template<class T>
		typename diter<T>::difference_type operator - (const diter<T>& it1, const diter<T>& it2){
			return typename diter<T>::difference_type(it1.container_->getBuckSize()) * (it1.mapIndex_ - it2.mapIndex_ - 1)
				+ (it1.cur_ - it1.getBuckHead(it1.mapIndex_)) + (it2.getBuckTail(it2.mapIndex_) - it2.cur_);
		}
	}

	//class of deque
	template<class T, class Alloc>
	class deque{
	private:
		template<class T>
		friend class diter;
	public:
		typedef T value_type;
		typedef diter<T> iterator;
		typedef const iterator const_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		typedef const reverse_iterator const_reverse_iterator;
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
				delete[] map_[i];
			delete[] map_;
		}

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
	private:
		T *getABuck(){
			return new T[getBuckSize()];
		}
		T** getANewMap(const size_t size){
			mapSize_ = getNewMapSize(size);
			return new T*[mapSize_](0);
		}
		size_t getNewMapSize(const size_t size){
			return (size == 0 ? 1 : size * 1.5);
		}
		size_t getBuckSize()const{
			return EBucksSize::BUCKSIZE;
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
	//template<class T, class Alloc>
	//deque<T, Alloc>::deque(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
	//template<class T, class Alloc>
	//template <class InputIterator>
	//deque<T, Alloc>::deque(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
	//template<class T, class Alloc>
	//deque<T, Alloc>::deque(const deque& x);
}
#endif