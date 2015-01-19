#ifndef _UNORDERED_SET_IMPL_H_
#define _UNORDERED_SET_IMPL_H_

#include <functional>

namespace TinySTL{
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
	Unordered_set<Key, Hash, KeyEqual, Allocator>::Unordered_set(size_type bucket_count){
		bucket_count = next_prime(bucket_count);
		buckets_.resize(bucket_count);
		size_ = 0;
	}
	template<class Key, class Hash, class KeyEqual, class Allocator>
	template<class InputIterator>
	Unordered_set<Key, Hash, KeyEqual, Allocator>::Unordered_set(InputIterator first, InputIterator last){
		size_ = 0;
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
}

#endif