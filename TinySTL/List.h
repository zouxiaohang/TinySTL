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
			node *next;
			List<T> *container;
			node(const T& d, node *n, List<T> *c):
				data(d), node(n), container(c){}
			bool operator ==(const node& n){
				return data == n.data && next == n.next && container == n.container;
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
	private:
		nodePtr newNode(const T& val = T()){
			nodePtr res = nodeAllocator::allocate();
			res->container = this;
			res->data = val;
			res->next = nullptr;
			return res;
		}
	};
}

#endif