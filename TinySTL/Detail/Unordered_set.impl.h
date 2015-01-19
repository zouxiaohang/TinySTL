#ifndef _UNORDERED_SET_IMPL_H_
#define _UNORDERED_SET_IMPL_H_

#include <functional>//for bind

namespace TinySTL{
	namespace Detail{
		template<class Key, class ListIterator, class Hash, class KeyEqual, class Allocator>
		ust_iterator<Key, ListIterator, Hash, KeyEqual, Allocator>::ust_iterator(size_t index, ListIterator it, cntrPtr ptr)
			:bucket_index_(index), iterator_(it), container_(ptr){}
		template<class Key, class ListIterator, class Hash, class KeyEqual, class Allocator>
		ust_iterator<Key, ListIterator, Hash, KeyEqual, Allocator>&
			ust_iterator<Key, ListIterator, Hash, KeyEqual, Allocator>::operator ++(){
			++iterator_;
			//如果前进一位后到达了list的末尾，则需要跳转到下一个有item的bucket的list
			if (iterator_ == container_->buckets_[bucket_index_].end()){
				for (;;){
					if (bucket_index_ == container_->buckets_.size() - 1){
						*this = container_->end();
						break;
					}
					else{
						++bucket_index_;
						if (!(container_->buckets_[bucket_index_].empty())){//此list不为空
							iterator_ = container_->buckets_[bucket_index_].begin();
							break;
						}
					}
				}
			}
			return *this;
		}
		template<class Key, class ListIterator, class Hash, class KeyEqual, class Allocator>
		ust_iterator<Key, ListIterator, Hash, KeyEqual, Allocator>
			ust_iterator<Key, ListIterator, Hash, KeyEqual, Allocator>::operator ++(int){
			auto res = *this;
			++*this;
			return res;
		}
		template<class Key, class ListIterator, class Hash, class KeyEqual, class Allocator>
		bool operator ==(const ust_iterator<Key, ListIterator, Hash, KeyEqual, Allocator>& lhs,
			const ust_iterator<Key, ListIterator, Hash, KeyEqual, Allocator>& rhs){
			return lhs.bucket_index_ == rhs.bucket_index_ &&
				lhs.iterator_ == rhs.iterator_ &&
				lhs.container_ == rhs.container_;
		}
		template<class Key, class ListIterator, class Hash, class KeyEqual, class Allocator>
		bool operator !=(const ust_iterator<Key, ListIterator, Hash, KeyEqual, Allocator>& lhs,
			const ust_iterator<Key, ListIterator, Hash, KeyEqual, Allocator>& rhs){
			return !(lhs == rhs);
		}
	}//end of Detail namespace

	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::size_type 
		Unordered_set<Key, Hash, KeyEqual, Allocator>::size()const{ 
		return size_; 
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	bool Unordered_set<Key, Hash, KeyEqual, Allocator>::empty()const{ 
		return size() == 0; 
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::size_type 
		Unordered_set<Key, Hash, KeyEqual, Allocator>::bucket_count()const{ 
		return buckets_.size(); 
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::size_type 
		Unordered_set<Key, Hash, KeyEqual, Allocator>::bucket_size(size_type i)const{ 
		return buckets_[i].size(); 
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::size_type
		Unordered_set<Key, Hash, KeyEqual, Allocator>::bucket(const key_type& key)const{
		return bucket_index(key);
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	float Unordered_set<Key, Hash, KeyEqual, Allocator>::load_factor()const{
		return (float)size() / (float)bucket_count();
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::haser 
		Unordered_set<Key, Hash, KeyEqual, Allocator>::hash_function()const{
		return haser();
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::key_equal 
		Unordered_set<Key, Hash, KeyEqual, Allocator>::key_eq()const{
		return key_equal();
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::allocator_type 
		Unordered_set<Key, Hash, KeyEqual, Allocator>::get_allocator()const{
		return allocator_type();
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	size_t Unordered_set<Key, Hash, KeyEqual, Allocator>::prime_list_[PRIME_LIST_SIZE] = {
		53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241,
		786433, 1572869, 3145739, 6291469, 12582917, 25165843, 50331653, 100663319, 201326611,
		402653189, 805306457, 1610612741, 3221225473, 4294967291,
	};
	template<class Key, class Hash, class KeyEqual, class Allocator>
	bool Unordered_set<Key, Hash, KeyEqual, Allocator>::has_key(const key_type& key){
		auto& list = buckets_[bucket_index(key)];
		auto pred = std::bind(KeyEqual(), key, std::placeholders::_1);
		return TinySTL::find_if(list.begin(), list.end(), pred) != list.end();
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::size_type
		Unordered_set<Key, Hash, KeyEqual, Allocator>::bucket_index(const key_type& key)const{
		return haser()(key) % buckets_.size();
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::size_type
		Unordered_set<Key, Hash, KeyEqual, Allocator>::next_prime(size_type n)const{
		auto i = 0;
		for (; i != PRIME_LIST_SIZE; ++i){
			if (n > prime_list_[i])
				continue;
			else
				break;
		}
		i = (i == PRIME_LIST_SIZE ? PRIME_LIST_SIZE - 1 : i);
		return prime_list_[i];
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	Unordered_set<Key, Hash, KeyEqual, Allocator>::Unordered_set(const Unordered_set& ust){
		buckets_ = ust.buckets_;
		size_ = ust.size_;
		max_load_factor_ = ust.max_load_factor_;
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	Unordered_set<Key, Hash, KeyEqual, Allocator>& Unordered_set<Key, Hash, KeyEqual, Allocator>::operator = (const Unordered_set& ust){
		if (this != &ust){
			buckets_ = ust.buckets_;
			size_ = ust.size_;
			max_load_factor_ = ust.max_load_factor_;
		}
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	Unordered_set<Key, Hash, KeyEqual, Allocator>::Unordered_set(size_type bucket_count){
		bucket_count = next_prime(bucket_count);
		buckets_.resize(bucket_count);
		size_ = 0;
		max_load_factor_ = 1.0;
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	template<class InputIterator>
	Unordered_set<Key, Hash, KeyEqual, Allocator>::Unordered_set(InputIterator first, InputIterator last){
		size_ = 0;
		max_load_factor_ = 1.0;
		auto len = last - first;
		buckets_.resize(next_prime(len));
		for (; first != last; ++first){
			auto index = bucket_index(*first);
			if (!has_key(*first)){
				buckets_[index].push_front(*first);
				++size_;
			}
		}
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::iterator 
		Unordered_set<Key, Hash, KeyEqual, Allocator>::begin(){
		size_type index = 0;
		for (; index != buckets_.size(); ++index){
			if (!(buckets_[index].empty()))
				break;
		}
		if (index == buckets_.size())
			return end();
		return iterator(index, buckets_[index].begin(), this);
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::iterator 
		Unordered_set<Key, Hash, KeyEqual, Allocator>::end(){
		return iterator(buckets_.size() - 1, buckets_[buckets_.size() - 1].end(), this);
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::local_iterator 
		Unordered_set<Key, Hash, KeyEqual, Allocator>::begin(size_type i){
		return buckets_[i].begin();
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::local_iterator 
		Unordered_set<Key, Hash, KeyEqual, Allocator>::end(size_type i){
		return buckets_[i].end();
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::iterator 
		Unordered_set<Key, Hash, KeyEqual, Allocator>::find(const key_type& key){
		auto index = bucket_index(key);
		for (auto it = begin(index); it != end(index); ++it){
			if (key_equal()(key, *it))
				return iterator(index, it, this);
		}
		return end();
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::size_type 
		Unordered_set<Key, Hash, KeyEqual, Allocator>::count(const key_type& key){
		auto it = find(key);
		return it == end() ? 0 : 1;
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	TinySTL::pair<typename Unordered_set<Key, Hash, KeyEqual, Allocator>::iterator, bool> 
		Unordered_set<Key, Hash, KeyEqual, Allocator>::insert(const value_type& val){
		if (!has_key(val)){
			if (load_factor() > max_load_factor())
				rehash(next_prime(size()));
			auto index = bucket_index(val);
			buckets_[index].push_front(val);
			++size_;
			return TinySTL::pair<iterator, bool>(iterator(index, buckets_[index].begin(), this), true);
		}
		return TinySTL::pair<iterator, bool>(end(), false);
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	template<class InputIterator>
	void Unordered_set<Key, Hash, KeyEqual, Allocator>::insert(InputIterator first, InputIterator last){
		for (; first != last; ++first){
			insert(*first);
		}
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::iterator 
		Unordered_set<Key, Hash, KeyEqual, Allocator>::erase(iterator position){
		--size_;
		auto t = position++;
		auto index = t.bucket_index_;
		auto it = buckets_[index].erase(t.iterator_);
		return position;
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	typename Unordered_set<Key, Hash, KeyEqual, Allocator>::size_type 
		Unordered_set<Key, Hash, KeyEqual, Allocator>::erase(const key_type& key){
		auto it = find(key);
		if (it == end()){
			return 0;
		}else{
			erase(it);
			return 1;
		}
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	float Unordered_set<Key, Hash, KeyEqual, Allocator>::max_load_factor()const{
		return max_load_factor_;
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	void Unordered_set<Key, Hash, KeyEqual, Allocator>::max_load_factor(float z){
		max_load_factor_ = z;
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	void Unordered_set<Key, Hash, KeyEqual, Allocator>::rehash(size_type n){
		if (n <= buckets_.size())
			return;
		Unordered_set temp(next_prime(n));
		for (auto& val : *this){
			temp.insert(val);
		}
		TinySTL::swap(*this, temp);
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	void swap(Unordered_set<Key, Hash, KeyEqual, Allocator>& lhs,
		Unordered_set<Key, Hash, KeyEqual, Allocator>& rhs){
		TinySTL::swap(lhs.buckets_, rhs.buckets_);
		TinySTL::swap(lhs.size_, rhs.size_);
		TinySTL::swap(lhs.max_load_factor_, rhs.max_load_factor_);
	}
}

#endif