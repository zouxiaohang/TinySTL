#ifndef _LIST_H_
#define _LIST_H_

#include "Allocator.h"
#include "Iterator.h"
#include "ReverseIterator.h"
#include "UninitializedFunctions.h"

#include <type_traits>

namespace TinySTL{
	template<class T>
	class List;
	namespace{
		//the class of node
		template<class T>
		struct node{
			T data;
			node *prev;
			node *next;
			List<T> *container;
			node(const T& d, node *p, node *n, List<T> *c):
				data(d), prev(p), node(n), container(c){}
			bool operator ==(const node& n){
				return data == n.data && prev == n.prev && next == n.next && container == n.container;
			}
		};
		//the class of list iterator
		template<class T>
		struct listIterator :public bidirectional_iterator<T, ptrdiff_t>{
			template<class T>
			friend class List;
		private:
			typedef node<T>* nodePtr;
			nodePtr p;
		public:
			explicit listIterator(nodePtr ptr = nullptr) :p(ptr){}

			listIterator& operator++(){
				p = p->next;
				return *this;
			}
			listIterator operator++(int){
				auto res = *this;
				++*this;
				return res;
			}
			listIterator& operator --(){
				p = p->prev;
				return *this;
			}
			listIterator operator --(int){
				auto res = *this;
				--*this;
				return res;
			}
			T& operator *(){ return p->data; }
			T* operator &(){ return &(operator*()); }

			template<class T>
			friend bool operator ==(const listIterator<T>& lhs, const listIterator<T>& rhs);
			template<class T>
			friend bool operator !=(const listIterator<T>& lhs, const listIterator<T>& rhs);
		};
		template<class T>
		bool operator ==(const listIterator<T>& lhs, const listIterator<T>& rhs){
			return lhs.p == rhs.p;
		}
		template<class T>
		bool operator !=(const listIterator<T>& lhs, const listIterator<T>& rhs){
			return !(lhs == rhs);
		}
	}//end of namespace

	//the class of List
	template<class T>
	class List{
		template<class T>
		friend struct listIterator;
	private:
		typedef allocator<node<T>> nodeAllocator;
		typedef node<T> *nodePtr;
	public:
		typedef T value_type;
		typedef listIterator<T> iterator;
		typedef reverse_iterator_t<iterator> reverse_iterator;
		typedef T& reference;
		typedef size_t size_type;
	private:
		iterator head;
		iterator tail;
	public:
		List(){
			head.p = newNode();//add a dummy node
			tail.p = head.p;
		}
		List(const List& list) = delete;
		List& operator = (const List& list) = delete;
		~List(){
			for (; head != tail;){
				auto temp = head++;
				nodeAllocator::deallocate(temp.p);
			}
			nodeAllocator::deallocate(tail.p);
		}

		bool empty()const{
			return head == tail;
		}
		size_type size()const{
			size_type length = 0;
			for (auto h = head; h != tail; ++h)
				++length;
			return length;
		}
		reference front(){ return (head.p->data); }
		reference back(){ return (tail.p->prev->data); }

		void push_front(const value_type& val);
		void pop_front();
		void push_back(const value_type& val);
		void pop_back();

		iterator begin(){ return head; }
		iterator end(){ return tail; }
		reverse_iterator rbegin(){ return reverse_iterator(tail); }
		reverse_iterator rend(){ return reverse_iterator(head); }

		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, size_type n, const value_type& val);
		template <class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		iterator erase(iterator position);
		iterator erase(iterator first, iterator last);
		//void swap(List& x);
		void clear();
		//void splice(iterator position, list& x);
		//void splice(iterator position, list& x, iterator i);
		//void splice(iterator position, list& x, iterator first, iterator last);
		//void remove(const value_type& val);
		//template <class Predicate>
		//void remove_if(Predicate pred);
		//void unique();
		//template <class BinaryPredicate>
		//void unique(BinaryPredicate binary_pred);
		//void merge(list& x);
		//template <class Compare>
		//void merge(list& x, Compare comp);
		//void sort();
		//template <class Compare>
		//void sort(Compare comp);
		//void reverse();
	private:
		nodePtr newNode(const T& val = T()){
			nodePtr res = nodeAllocator::allocate();
			res->container = this;
			res->data = val;
			res->prev = nullptr;
			res->next = nullptr;
			return res;
		}
		void deleteNode(nodePtr p){ 
			p->prev = nullptr;
			p->next = nullptr;
			nodeAllocator::deallocate(p); 
		}
		void insert_aux(iterator position, size_type n, const T& val, std::true_type){
			for (auto i = n; i != 0; --i){
				position = insert(position, val);
			}
		}
		template<class InputIterator>
		void insert_aux(iterator position, InputIterator first, InputIterator last, std::false_type){
			for (; first != last; ++first){
				insert(position, *first);
			}
		}
	};
	template<class T>
	void List<T>::push_front(const value_type& val){
		auto node = newNode(val);
		head.p->prev = node;
		node->next = head.p;
		head.p = node;
	}
	template<class T>
	void List<T>::pop_front(){
		auto oldNode = head.p;
		head.p = oldNode->next;
		head.p->prev = nullptr;
		deleteNode(oldNode);
	}
	template<class T>
	void List<T>::push_back(const value_type& val){
		auto node = newNode();
		(tail.p)->data = val;
		(tail.p)->next = node;
		node->prev = tail.p;
		tail.p = node;
	}
	template<class T>
	void List<T>::pop_back(){
		auto newTail = tail.p->prev;
		newTail->next = nullptr;
		deleteNode(tail.p);
		tail.p = newTail;
	}
	template<class T>
	typename List<T>::iterator List<T>::insert(iterator position, const value_type& val){
		auto node = newNode(val);
		auto prev = position.p->prev;
		node->next = position.p;
		node->prev = prev;
		prev->next = node;
		position.p->prev = node;
		return iterator(node);
	}
	template<class T>
	void List<T>::insert(iterator position, size_type n, const value_type& val){
		insert_aux(position, n, val, typename std::is_integral<InputIterator>::type());
	}
	template<class T>
	template <class InputIterator>
	void List<T>::insert(iterator position, InputIterator first, InputIterator last){
		insert_aux(position, first, last, typename std::is_integral<InputIterator>::type());
	}
	template<class T>
	typename List<T>::iterator List<T>::erase(iterator position){
		if (position == head){
			pop_front();
			return head;
		}else{
			auto prev = position.p->prev;
			prev->next = position.p->next;
			position.p->next->prev = prev;
			deleteNode(position.p);
			return iterator(prev->next);
		}
	}
	template<class T>
	typename List<T>::iterator List<T>::erase(iterator first, iterator last){
		typename List<T>::iterator res;
		for (; first != last; ){
			auto temp = first++;
			res = erase(temp);
		}
		return res;
	}
	template<class T>
	void List<T>::clear(){
		erase(begin(), end());
	}
}

#endif