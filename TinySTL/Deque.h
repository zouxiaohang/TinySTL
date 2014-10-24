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
				if (this != &it){
					mapIndex_ = it.mapIndex_;
					cur_ = it.cur_;
					container_ = it.container_;
				}
				return *this;
			}
			void swap(dq_iter& it){
				TinySTL::swap(mapIndex_, it.mapIndex_);
				TinySTL::swap(cur_, it.cur_);
				//TinySTL::swap(container_, it.container_);
			}
			reference operator *(){ return *cur_; }
			const reference operator *()const{ return *cur_; }
			pointer operator ->(){ return &(operator*()); }
			const pointer operator ->()const{ return &(operator*()); }
			dq_iter& operator ++(){
				if (cur_ != getBuckTail(mapIndex_))//+1后还在同一个桶里
					++cur_;
				else if(mapIndex_ + 1 < container_->mapSize_){//+1后还在同一个map里
					++mapIndex_;
					cur_ = getBuckHead(mapIndex_);
				}else{//+1后跳出了map
					mapIndex_ = container_->mapSize_;
					//cur_ = container_->map_[mapIndex_] + getBuckSize();//指向map_[mapSize_-1]的尾的下一个位置
					cur_ = container_->map_[mapIndex_];
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
				else if(mapIndex_ - 1 >= 0){//-1后还在map里面
					--mapIndex_;
					cur_ = getBuckTail(mapIndex_);
				}else{
					mapIndex_ = 0;
					cur_ = container_->map_[mapIndex_];//指向map_[0]的头
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
				return container_->map_[mapIndex] + (container_->getBuckSize() - 1);
			}
			T *getBuckHead(size_t mapIndex)const{
				return container_->map_[mapIndex];
			}
			size_t getBuckSize()const{
				return container_->getBuckSize();
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
			template<class T>
			friend void swap(dq_iter<T>& lhs, dq_iter<T>& rhs);
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
				res.mapIndex_ += (n / it.getBuckSize() + 1);
				auto p = res.getBuckHead(res.mapIndex_);
				auto x = n % it.getBuckSize() - 1;
				res.cur_ = p + x;
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
				res.mapIndex_ -= (n / res.getBuckSize() + 1);
				res.cur_ = res.getBuckTail(res.mapIndex_) - (n % res.getBuckSize() - 1);
			}
			return res;
		}
		template<class T>
		dq_iter<T> operator - (typename dq_iter<T>::difference_type n, const dq_iter<T>& it){
			return (it - n);
		}
		template<class T>
		typename dq_iter<T>::difference_type operator - (const dq_iter<T>& it1, const dq_iter<T>& it2){
			if (it1.container_ == it2.container_ && it1.container_ == 0)
				return 0;
			return typename dq_iter<T>::difference_type(it1.getBuckSize()) * (it1.mapIndex_ - it2.mapIndex_ - 1)
				+ (it1.cur_ - it1.getBuckHead(it1.mapIndex_)) + (it2.getBuckTail(it2.mapIndex_) - it2.cur_) + 1;
		}
		template<class T>
		void swap(dq_iter<T>& lhs, dq_iter<T>& rhs){
			lhs.swap(rhs);
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
				if (!map_[i])
					dataAllocator::deallocate(map_[i], getBuckSize());
			delete[] map_;
		}

		deque& operator= (const deque& x);
		deque& operator= (deque&& x);

		iterator begin(){ return beg_; }
		iterator end(){ return end_; }

		size_type size() const{ return end() - begin(); }
		bool empty() const{ return begin() == end(); }

		reference operator[] (size_type n){ return *(begin() + n); }
		const_reference operator[] (size_type n) const{ return *(cbegin() + n); }
		reference front(){ return *begin(); }
		const_reference front() const{ return *cbegin(); }
		reference back(){ return *(end() - 1); }
		const_reference back() const{ return *(cend() - 1); }

		void push_back(const value_type& val);
		void push_front(const value_type& val);
		void pop_back();
		void pop_front();
		void swap(deque& x);
		void clear(){
			for (int i = 0; i != mapSize_; ++i)
				if (!map_[i])
					dataAllocator::destroy(map_[i], map_[i] + getBuckSize());
			mapSize_ = 0;
			beg_.mapIndex_ = end_.mapIndex_ = mapSize_ / 2;
			beg_.cur_ = end_.cur_ = map_[mapSize_ / 2];
		}
	private:
		T *getANewBuck(){
			return dataAllocator::allocate(getBuckSize());
		}
		T** getANewMap(const size_t size){
			T **map = new T*[size];
			for (int i = 0; i != size; ++i)
				map[i] = getANewBuck();
			return map;
		}
		size_t getNewMapSize(const size_t size){
			return (size == 0 ? 2 : size * 2);
		}
		size_t getBuckSize()const{
			return (size_t)EBucksSize::BUCKSIZE;
		}
		void init(){
			mapSize_ = 2;
			map_ = getANewMap(mapSize_);
			beg_.container_ = end_.container_ = this;
			beg_.mapIndex_ = end_.mapIndex_ = mapSize_ - 1;
			beg_.cur_ = end_.cur_ = map_[mapSize_ - 1];
		}
		bool back_full()const{ 
			return map_[mapSize_ - 1] && (map_[mapSize_]) == end().cur_;
		}
		bool front_full()const{
			return map_[0] && map_[0] == begin().cur_;
		}
		void deque_aux(size_t n, const value_type& val, std::true_type){
			int i = 0;
			for (; i != n / 2; ++i)
				(*this).push_front(val);
			for (; i != n; ++i)
				(*this).push_back(val);
		}
		template<class Iterator>
		void deque_aux(Iterator first, Iterator last, std::false_type){
			difference_type mid = (last - first) / 2;
			for (auto it = first + mid; it != first - 1; --it)
				(*this).push_front(*it);
			for (auto it = first + mid + 1; it != last; ++it)
				(*this).push_back(*it);
		}
		void reallocateAndCopy();
	public:
		template <class T, class Alloc>
		friend bool operator== (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);
		template <class T, class Alloc>
		friend bool operator!= (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs);
		template <class T, class Alloc>
		friend void swap(deque<T, Alloc>& x, deque<T, Alloc>& y);
	};//end of deque

	template<class T, class Alloc>
	deque<T, Alloc>::deque()
		:mapSize_(0), map_(0){}
	template<class T, class Alloc>
	deque<T, Alloc>::deque(size_type n, const value_type& val = value_type()){
		deque();
		deque_aux(n, val, typename std::is_integral<size_type>::type());
	}
	template<class T, class Alloc>
	template <class InputIterator>
	deque<T, Alloc>::deque(InputIterator first, InputIterator last){
		deque();
		deque_aux(first, last, typename std::is_integral<InputIterator>::type());
	}
	template<class T, class Alloc>
	deque<T, Alloc>::deque(const deque& x){
		mapSize_ = x.mapSize_;
		map_ = getANewMap(mapSize_);
		for (int i = 0; i + x.beg_.mapIndex_ != x.mapSize_; ++i)
			for (int j = 0; j != getBuckSize(); ++j)
				map_[x.beg_.mapIndex_ + i][j] = x.map_[x.beg_.mapIndex_ + i][j];
		beg_.mapIndex_ = x.beg_.mapIndex_;
		end_.mapIndex_ = x.end_.mapIndex_;
		beg_.cur_ = map_[beg_.mapIndex_] + (x.beg_.cur_ - x.map_[x.beg_.mapIndex_]);
		end_.cur_ = map_[end_.mapIndex_] + (x.end_.cur_ - x.map_[x.end_.mapIndex_]);
		beg_.container_ = end_.container_ = this;
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::reallocateAndCopy(){
		auto newMapSize = getNewMapSize(mapSize_);
		T** newMap = getANewMap(newMapSize);
		size_t startIndex = newMapSize / 4;
		for (int i = 0; i + beg_.mapIndex_ != mapSize_; ++i)
			for (int j = 0; j != getBuckSize(); ++j)
				newMap[startIndex + i][j] = map_[beg_.mapIndex_ + i][j];

		size_t n = beg_.cur_ - map_[beg_.mapIndex_];
		auto size = this->size();
		auto b = beg_, e = end_;
		clear();
		mapSize_ = newMapSize;
		map_ = newMap;
		beg_ = iterator(startIndex, newMap[startIndex] + n, this);
		end_ = beg_ + size;
		
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::push_back(const value_type& val){
		if (empty()){
			init();
		}
		else if (back_full()){
			reallocateAndCopy();
		}
		*end_ = val;
		++end_;
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::push_front(const value_type& val){
		if (empty()){
			init();
		}
		else if (front_full()){
			reallocateAndCopy();
		}
		--beg_;
		*beg_ = val;
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::pop_front(){
		dataAllocator::destroy(beg_.cur_);
		++beg_;
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::pop_back(){
		--end_;
		dataAllocator::destroy(end_.cur_);
	}
	template<class T, class Alloc>
	void deque<T, Alloc>::swap(deque<T, Alloc>& x){
		TinySTL::swap(mapSize_, x.mapSize_);
		TinySTL::swap(map_, x.map_);
		beg_.swap(x.beg_);
		end_.swap(x.end_);
	}
	template <class T, class Alloc>
	bool operator== (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs){
		auto cit1 = lhs.cbegin(), cit2 = rhs.cbegin();
		for (; cit1 != lhs.cend() && cit2 != rhs.cend(); ++cit1, ++cit2){
			if (*cit1 != *cit2)
				return false;
		}
		if (cit1 == lhs.cend() && cit2 == rhs.cend())
			return true;
		return false;
	}
	template <class T, class Alloc>
	bool operator!= (const deque<T, Alloc>& lhs, const deque<T, Alloc>& rhs){
		return !(lhs == rhs);
	}
	template <class T, class Alloc>
	void swap(deque<T, Alloc>& x, deque<T, Alloc>& y){
		x.swap(y);
	}
}
#endif