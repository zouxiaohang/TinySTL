#ifndef _UNORDERED_SET_H_
#define _UNORDERED_SET_H_

#include "Allocator.h"
#include "Algorithm.h"
#include "Functional.h"
#include "List.h"
#include "Vector.h"
#include <list>
#include <vector>

namespace TinySTL{
	template<class Key, class Hash = std::hash<Key>,
	class KeyEqual = TinySTL::equal_to<Key>, class Allocator = TinySTL::allocator < Key >>
	class Unordered_set{
	public:
		typedef Key key_type;
		typedef Key value_type;
		typedef size_t size_type;
		typedef Hash haser;
		typedef Allocator allocator_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
	private:
		TinySTL::vector<TinySTL::list<key_type>> buckets_;
		size_type size_;
#define PRIME_LIST_SIZE 28
		static size_t prime_list_[PRIME_LIST_SIZE];
	public:
		explicit Unordered_set(size_t bucket_count);
		template<class InputIterator>
		Unordered_set(InputIterator first, InputIterator last);
		//Unordered_set(const Unordered_set& ust);
		//Unordered_set& operator = (const Unordered_set& ust);
	private:
		size_type next_prime(size_type n)const;
		size_type bucket_index(const key_type& key)const;
		bool has_key(const key_type& key);
	};
}//end of namespace TinySTL

#include "Detail\Unordered_set.impl.h"
#endif