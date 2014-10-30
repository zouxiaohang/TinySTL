#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include "Allocator.h"
#include "Stack.h"
#include "String.h"

#include <set>

namespace TinySTL{
	namespace {
		template<class T>
		class avl_iter;
	}
	//class of avl tree
	template<class T>
	class avl_tree{
	private:
		template<class T>
		friend class avl_iter;
	private:
		struct node{
			T data_;
			node *left_, *right_;
			size_t height_;
			typedef T value_type;
			explicit node(T d = T(), node *l = 0, node *r = 0, size_t h = 0)
				:data_(d), left_(l), right_(r), height_(h){}
		};
		typedef TinySTL::allocator<node> dataAllocator;
	public:
		typedef T value_type;
		typedef avl_iter<node> const_iterator;
		typedef const T& const_reference;
		typedef size_t size_type;
	private:
		node *root_;
		size_t size_;
	public:
		avl_tree() :root_(0), size_(0){}
		avl_tree(const avl_tree&) = delete;
		avl_tree& operator = (const avl_tree&) = delete;
		~avl_tree(){ destroyAndDeallocateAllNodes(root_); }

		void insert(const T& val);//todo
		template<class Iterator>
		void insert(Iterator first, Iterator last);//todo
		void erase(const T& val);//todo

		size_t height()const{ return root_ == 0 ? -1 : root_->height_; }
		size_t size()const{ return size_; }
		bool empty()const{ return root_ == 0; }
		const_iterator root(){ return const_iterator(root_, this); }

		const_iterator cbegin(){ return find_min(); }
		const_iterator cend(){ return const_iterator(0, this); }

		const_iterator find_min();
		const_iterator find_max();
		const_iterator find(const T& val);

		void print_preorder(const string& delim = " ", std::ostream& os = std::cout)const;
		void print_inorder(const string& delim = " ", std::ostream& os = std::cout)const;
		void print_postorder(const string& delim = " ", std::ostream& os = std::cout)const;
		void print_levelorder(const string& delim = " ", std::ostream& os = std::cout)const;
	private:
		void singleLeftLeftRotate(node *&parent, node *&child){
			parent->left_ = child->right_;
			child->right_ = parent;
			parent = child;//new root
		}
		void doubleLeftRightRotate(node *&parent, node *&child){
			singleRightRightRotate(parent->left_, parent->left_->right_);
			singleLeftLeftRotate(parent, parent->left_);
		}
		void doubleRightLeftRotate(node *&parent, node *&child){
			singleLeftLeftRotate(parent->right_, parent->right_->left_);
			singleRightRightRotate(parent, parent->right);
		}
		void singleRightRightRotate(node *&parent, node *&child){
			parent->right_ = child->left_;
			child->left_ = parent;
			parent = child;//new root
		}
	private:
		void destroyAndDeallocateAllNodes(node *p){
			if (p != 0){
				destroyAndDeallocateAllNodes(p->left_);
				destroyAndDeallocateAllNodes(p->right_);
				dataAllocator::destroy(p);
				dataAllocator::deallocate(p);
			}
		}
		const_iterator find_min_aux(const node *ptr);
		const_iterator find_max_aux(const node *ptr);
		const_iterator find_aux(const T& val, const node *ptr);
		void print_preorder_aux(const string& delim, std::ostream& os, const node *ptr)const;
		void print_inorder_aux(const string& delim, std::ostream& os, const node *ptr)const;
		void print_postorder_aux(const string& delim, std::ostream& os, const node *ptr)const;
	};// end of avl_tree
	template<class T>
	void avl_tree<T>::insert(const T& val){

	}
	template<class T>
	void avl_tree<T>::print_preorder_aux(const string& delim, std::ostream& os, const node *ptr)const{
		if (ptr != 0){
			os << ptr->data_ << delim;
			print_preorder_aux(delim, os, ptr->left_);
			print_preorder_aux(delim, os, ptr->right_);
		}
	}
	template<class T>
	void avl_tree<T>::print_preorder(const string& delim, std::ostream& os)const{
		print_preorder_aux(delim, os, root_);
	}
	template<class T>
	void avl_tree<T>::print_inorder_aux(const string& delim, std::ostream& os, const node *ptr)const{
		if (ptr != 0){
			print_inorder_aux(delim, os, ptr->left_);
			os << ptr->data_ << delim;
			print_inorder_aux(delim, os, ptr->right_);
		}
	}
	template<class T>
	void avl_tree<T>::print_inorder(const string& delim, std::ostream& os)const{
		print_inorder_aux(delim, os, root_);
	}
	template<class T>
	void avl_tree<T>::print_postorder_aux(const string& delim, std::ostream& os, const node *ptr)const{
		if (ptr != 0){
			print_postorder_aux(delim, os, ptr->left_);
			print_postorder_aux(delim, os, ptr->right_);
			os << ptr->data_ << delim;
		}
	}
	template<class T>
	void avl_tree<T>::print_postorder(const string& delim, std::ostream& os)const{
		print_postorder_aux(delim, os, root_);
	}
	template<class T>
	void avl_tree<T>::print_levelorder(const string& delim, std::ostream& os)const{
		auto temp = root_;
		if (temp != 0){
			std::deque<node *> q;
			q.push_back(temp);
			while (!q.empty()){
				temp = q.front();
				q.pop_front();
				os << temp->data_ << delim;
				if (temp->left_ != 0) q.push_back(temp->left_);
				if (temp->right_ != 0) q.push_back(temp->right);
			}
		}
	}
	template<class T>
	typename avl_tree<T>::const_iterator avl_tree<T>::find_aux(const T& val, const node *ptr){
		while (ptr != 0){
			if (ptr->data_ < val)
				ptr = ptr->right_;
			else if (ptr->data_ > val)
				ptr = ptr->left_;
			else
				break;
		}
		return const_iterator(ptr, this);
	}
	template<class T>
	typename avl_tree<T>::const_iterator avl_tree<T>::find(const T& val){
		return find_aux(val, root_);
	}
	template<class T>
	typename avl_tree<T>::const_iterator avl_tree<T>::find_max_aux(const node *ptr){
		while (ptr != 0 && ptr->right_ != 0)
			ptr = ptr->right_;
		return const_iterator(ptr, this);
	}
	template<class T>
	typename avl_tree<T>::const_iterator avl_tree<T>::find_max(){
		return find_max_aux(root_);
	}
	template<class T>
	typename avl_tree<T>::const_iterator avl_tree<T>::find_min_aux(const node *ptr){
		while (ptr != 0 && ptr->left_ != 0)
			ptr = ptr->left_;
		return const_iterator(ptr, this);
	}
	template<class T>
	typename avl_tree<T>::const_iterator avl_tree<T>::find_min(){
		return find_min_aux(root_);
	}

	namespace{
		//class of avl tree iterator
		template<class T>//T = node
		class avl_iter{
		private:
			template<class T>
			friend class avl_tree;
		private:
			typedef typename avl_tree<typename T::value_type>::value_type value_type;
			typedef typename avl_tree<typename T::value_type>::const_reference const_reference;
			typedef typename const T::value_type *const_pointer;
			typedef avl_tree<typename T::value_type> * cntrPtr;
		private:
			const T *ptr_;
			cntrPtr container_;
			stack<const T *> parent_;//保存从root到ptr_的父节点的路径
			std::set<const T *> visited_;
		public:
			avl_iter(const T *ptr, cntrPtr container)
				:ptr_(ptr), container_(container){
				auto temp = container_->root_;
				while (temp &&ptr_ && temp != ptr_ && temp->data_ != ptr_->data_){
					parent_.push(temp);
					if (temp->data_ < ptr_->data_)
						temp = temp->right_;
					else if (temp->data_ > ptr_->data_)
						temp = temp->left_;
				}
			}

			operator const T*(){ return ptr_; }
			const_reference operator*(){ return ptr_->data_; }
			const_pointer operator ->(){ return &(operator*()); }

			avl_iter left()const{ return avl_iter(ptr_->left_, container_); }
			avl_iter right()const{ return avl_iter(ptr_->right_, container_); }

			avl_iter& operator ++();
			avl_iter operator ++(int);
			avl_iter& operator --();
			avl_iter operator --(int);
		public:
			template<class T>
			friend bool operator ==(const avl_iter<T>& it1, const avl_iter<T>& it2);
			template<class T>
			friend bool operator !=(const avl_iter<T>& it1, const avl_iter<T>& it2);
		};//end of avl_iter
		template<class T>
		avl_iter<T>& avl_iter<T>::operator ++(){
			visited_.insert(ptr_);//设为已访问
			if (ptr_->right_ != 0){
				parent_.push(ptr_);
				ptr_ = ptr_->right_;
				while (ptr_ != 0 && ptr_->left_ != 0){
					parent_.push(ptr_);
					ptr_ = ptr_->left_;
				}
			}
			else{
				if (!parent_.empty() && visited_.count(parent_.top()) == 0){//父节点未访问
					ptr_ = parent_.top();
					parent_.pop();
				}
				else{
					ptr_ = 0;
				}
			}
			return *this;
		}
		template<class T>
		avl_iter<T> avl_iter<T>::operator ++(int){
			auto res = *this;
			++*this;
			return res;
		}
		template<class T>
		avl_iter<T>& avl_iter<T>::operator --(){
			visited_.erase(ptr_);//设为未访问
			if (ptr_->left_ != 0){
				parent_.push(ptr_);
				ptr_ = ptr_->left_;
				while (ptr_ && ptr_->right_){
					parent_.push(ptr_);
					ptr_ = ptr_->right_;
				}
			}
			else{
				if (!parent_.empty() && visited_.count(parent_.top()) == 1){//父节点已经访问了
					ptr_ = parent_.top();
					parent_.pop();
				}
			}
			return *this;
		}
		template<class T>
		avl_iter<T> avl_iter<T>::operator --(int){
			auto res = *this;
			--*this;
			return res;
		}
		template<class T>
		bool operator ==(const avl_iter<T>& it1, const avl_iter<T>& it2){
			return it1.ptr_ == it2.ptr_;
		}
		template<class T>
		bool operator !=(const avl_iter<T>& it1, const avl_iter<T>& it2){
			return !(it1 == it2);
		}
	}
}

#endif