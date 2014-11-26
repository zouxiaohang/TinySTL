#ifndef _LIST_H_
#define _LIST_H_

#include "Allocator.h"
#include "UninitializedFunctions.h"

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
		struct listIterator{
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
			bool operator ==(const listIterator& it){
				return *p == *(it.p);
			}
			bool operator !=(const listIterator& it){
				return !(*this == it);
			}
		};
	}//end of namespace

	//the class of List
	template<class T>
	class List{
	private:
		typedef allocator<node<T>> nodeAllocator;
		typedef node<T> *nodePtr;
	public:
		typedef T value_type;
		typedef listIterator<T> iterator;
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
		/*List(const List& list){

		}*/
		~List(){
			for (; head != tail;){
				auto temp = head++;
				nodeAllocator::deallocate(temp.p);
			}
			nodeAllocator::deallocate(tail.p);
		}

		void push_front(const value_type& val);
		void pop_front();
		void push_back(const value_type& val);
		void pop_back();

		iterator begin()const{ return head; }
		iterator end()const{ return tail; }
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
}

#endif