#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include "Allocator.h"
#include "Iterator.h"
#include "Stack.h"
#include "String.h"

#include <set>

namespace TinySTL{
	namespace Detail{
		template<class T>
		class avl_iter;
	}
	//class of avl tree
	template<class T>
	class avl_tree{
	private:
		template<class T>
		friend class Detail::avl_iter;
	private:
		struct node{
			T data_;
			node *left_, *right_;
			size_t height_;
			typedef T value_type;
			explicit node(T d = T(), node *l = 0, node *r = 0, size_t h = 1)
				:data_(d), left_(l), right_(r), height_(h){}
		};
		typedef TinySTL::allocator<node> dataAllocator;
	public:
		typedef T value_type;
		typedef Detail::avl_iter<node> const_iterator;
		typedef const T& const_reference;
		typedef size_t size_type;
	private:
		node *root_;
		size_t size_;
	public:
		avl_tree() :root_(0), size_(0){}
		avl_tree(const avl_tree&) = delete;
		avl_tree& operator = (const avl_tree&) = delete;
		~avl_tree();

		void insert(const T& val);
		template<class Iterator>
		void insert(Iterator first, Iterator last);
		void erase(const T& val);

		size_t height()const{ return getHeight(root_); }
		size_t size()const{ return size_; }
		bool empty()const{ return root_ == 0; }
		const_iterator root()const{ return const_iterator(root_, this); }

		const_iterator cbegin()const{ return find_min(); }
		const_iterator cend()const{ return const_iterator(0, this); }

		const_iterator find_min()const;
		const_iterator find_max()const;
		const_iterator find(const T& val)const;

		void print_preorder(const string& delim = " ", std::ostream& os = std::cout)const;
		void print_inorder(const string& delim = " ", std::ostream& os = std::cout)const;
		void print_postorder(const string& delim = " ", std::ostream& os = std::cout)const;
		void print_levelorder(const string& delim = " ", std::ostream& os = std::cout)const;
	private:
		node *singleLeftLeftRotate(node *k2);
		node *doubleLeftRightRotate(node * k3);
		node *doubleRightLeftRotate(node * k3);
		node *singleRightRightRotate(node * k2);
	private:
		void insert_elem(const T& val, node *&p);
		void erase_elem(const T& val, node *&p);
		void destroyAndDeallocateAllNodes(node *p);
		size_t getHeight(const node *p)const{ return p == 0 ? 0 : p->height_; }
		const_iterator find_min_aux(const node *ptr)const;
		const_iterator find_max_aux(const node *ptr)const;
		const_iterator find_aux(const T& val, const node *ptr)const;
		void print_preorder_aux(const string& delim, std::ostream& os, const node *ptr)const;
		void print_inorder_aux(const string& delim, std::ostream& os, const node *ptr)const;
		void print_postorder_aux(const string& delim, std::ostream& os, const node *ptr)const;
	};// end of avl_tree
	namespace Detail{
		//class of avl tree iterator
		template<class T>//T = node
		class avl_iter :
			public iterator<forward_iterator_tag, typename avl_tree<typename T::value_type>::value_type>{
		private:
			template<class T>
			friend class avl_tree;
		private:
			//typedef typename avl_tree<typename T::value_type>::value_type value_type;
			typedef typename avl_tree<typename T::value_type>::const_reference const_reference;
			typedef typename const T::value_type *const_pointer;
			typedef const avl_tree<typename T::value_type> * cntrPtr;
		private:
			const T *ptr_;
			cntrPtr container_;
			stack<const T *> parent_;//保存从root到ptr_的父节点的路径
			std::set<const T *> visited_;//当前节点是否被访问过（此node被访问说明其左子树已被访问了）
		public:
			avl_iter(const T *ptr, cntrPtr container);

			operator const T*()const{ return ptr_; }
			const_reference operator*()const{ return ptr_->data_; }
			const_pointer operator ->()const{ return &(operator*()); }

			avl_iter left()const{ return avl_iter(ptr_->left_, container_); }
			avl_iter right()const{ return avl_iter(ptr_->right_, container_); }

			avl_iter& operator ++();
			avl_iter operator ++(int);
		public:
			template<class T>
			friend bool operator ==(const avl_iter<T>& it1, const avl_iter<T>& it2);
			template<class T>
			friend bool operator !=(const avl_iter<T>& it1, const avl_iter<T>& it2);
		};//end of avl_iter
	}
}


#include "Detail\AVLTree.impl.h"
#endif