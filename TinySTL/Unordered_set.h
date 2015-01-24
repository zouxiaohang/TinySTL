#ifndef _UNORDERED_SET_H_
#define _UNORDERED_SET_H_

#include "Allocator.h"
#include "Algorithm.h"
#include "Functional.h"
#include "Iterator.h"
#include "List.h"
#include "Vector.h"

namespace TinySTL{
	template<class Key, class Hash, class KeyEqual, class Allocator>
	class Unordered_set;
	namespace Detail{
		template<class Key, class ListIterator, class Hash = std::hash<Key>,
		class KeyEqual = TinySTL::equal_to<Key>, class Allocator = TinySTL::allocator < Key >>
		class ust_iterator : public iterator<forward_iterator_tag, Key>{
		private:
			template<class Key, class Hash, class KeyEqual, class Allocator>
			friend class Unordered_set;
		private:
			typedef Unordered_set<Key, Hash, KeyEqual, Allocator>* cntrPtr;
			size_t bucket_index_;
			ListIterator iterator_;
			cntrPtr container_;
		public:
			ust_iterator(size_t index, ListIterator it, cntrPtr ptr);
			ust_iterator& operator ++();
			ust_iterator operator ++(int);
			Key& operator*(){ return *iterator_; }
			Key* operator->(){ return &(operator*()); }
		private:
			template<class Key, class ListIterator, class Hash, class KeyEqual, class Allocator>
			friend bool operator ==(const ust_iterator<Key, ListIterator, Hash, KeyEqual, Allocator>& lhs,
				const ust_iterator<Key, ListIterator, Hash, KeyEqual, Allocator>& rhs);
			template<class Key, class ListIterator, class Hash, class KeyEqual, class Allocator>
			friend bool operator !=(const ust_iterator<Key, ListIterator, Hash, KeyEqual, Allocator>& lhs,
				const ust_iterator<Key, ListIterator, Hash, KeyEqual, Allocator>& rhs);
		};
	}//end of namespace Detail


	template<class Key, class Hash = std::hash<Key>,
	class KeyEqual = TinySTL::equal_to<Key>, class Allocator = TinySTL::allocator < Key >>
	class Unordered_set{
	private:
		template<class Key, class ListIterator, class Hash, class KeyEqual, class Allocator>
		friend class Detail::ust_iterator;
	public:
		typedef Key key_type;
		typedef Key value_type;
		typedef size_t size_type;
		typedef Hash haser;
		typedef KeyEqual key_equal;
		typedef Allocator allocator_type;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef typename TinySTL::list<key_type>::iterator local_iterator;
		typedef Detail::ust_iterator<Key, typename TinySTL::list<key_type>::iterator, Hash, KeyEqual, Allocator> iterator;
	private:
		TinySTL::vector<TinySTL::list<key_type>> buckets_;
		size_type size_;
		float max_load_factor_;
#define PRIME_LIST_SIZE 28
		static size_t prime_list_[PRIME_LIST_SIZE];
	public:
		explicit Unordered_set(size_t bucket_count);
		template<class InputIterator>
		Unordered_set(InputIterator first, InputIterator last);
		Unordered_set(const Unordered_set& ust);
		Unordered_set& operator = (const Unordered_set& ust);

		size_type size()const;
		bool empty()const;
		size_type bucket_count()const;
		size_type bucket_size(size_type i)const;
		size_type bucket(const key_type& key)const;
		float load_factor()const;
		float max_load_factor()const;
		void max_load_factor(float z);
		void rehash(size_type n);

		iterator begin();
		iterator end();
		local_iterator begin(size_type i);
		local_iterator end(size_type i);

		iterator find(const key_type& key);
		size_type count(const key_type& key);

		TinySTL::pair<iterator, bool> insert(const value_type& val);
		template<class InputIterator>
		void insert(InputIterator first, InputIterator last);
		iterator erase(iterator position);
		size_type erase(const key_type& key);

		haser hash_function()const;
		key_equal key_eq()const;
		allocator_type get_allocator()const;
	private:
		size_type next_prime(size_type n)const;
		size_type bucket_index(const key_type& key)const;
		bool has_key(const key_type& key);
	public:
		template<class Key, class Hash, class KeyEqual, class Allocator>
		friend void swap(Unordered_set<Key, Hash, KeyEqual, Allocator>& lhs,
			Unordered_set<Key, Hash, KeyEqual, Allocator>& rhs);
	};
	
}//end of namespace TinySTL

#include "Detail\Unordered_set.impl.h"
#endif