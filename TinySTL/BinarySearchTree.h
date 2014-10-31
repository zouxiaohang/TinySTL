#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

#include "Allocator.h"
#include "Queue.h"
#include "Stack.h"
#include "String.h"

#include <deque>
#include <set>

namespace TinySTL{
	namespace {
		template<class T>
		class bst_iter;
	}
	//class of binary_search_tree
	template<class T>
	class binary_search_tree{
	private:
		template<class T>
		friend class bst_iter;
	private:
		struct node{
			typedef T value_type;
			T data_;
			node *left_;
			node *right_;
			explicit node(T d = T(), node *l = 0, node *r = 0)
				:data_(d), left_(l), right_(r){}
		};
		typedef TinySTL::allocator<node> nodeAllocator;
	public:
		typedef T value_type;
		typedef bst_iter<node> const_iterator;
		typedef const T& const_reference;
		typedef size_t size_type;
	private:
		node *root_;
		size_t size_;
	public:
		binary_search_tree() :root_(0), size_(0){}
		binary_search_tree(const binary_search_tree&) = delete;
		binary_search_tree& operator=(const binary_search_tree&) = delete;
		~binary_search_tree(){
			deallocateAllNodes(root_);
		}

		void insert(const T& val);
		template<class Iterator>
		void insert(Iterator first, Iterator last);
		void erase(const T& val);

		bool empty()const{ return root_ == 0; }
		size_t size()const{ return size_; }
		size_t height()const{ return height_aux(root_); }
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
		void deallocateAllNodes(node *ptr){
			if (ptr){
				deallocateAllNodes(ptr->left_);
				deallocateAllNodes(ptr->right_);
				nodeAllocator::deallocate(ptr);
			}
		}
		size_t height_aux(node *p)const;
		void erase_elem(const T& val, node *&ptr);
		void insert_elem(const T& val, node *&ptr);
		const_iterator find_min_aux(const node *ptr);
		const_iterator find_max_aux(const node *ptr);
		const_iterator find_aux(const T& val, const node *ptr);
		void print_preorder_aux(const string& delim, std::ostream& os, const node *ptr)const;
		void print_inorder_aux(const string& delim, std::ostream& os, const node *ptr)const;
		void print_postorder_aux(const string& delim, std::ostream& os, const node *ptr)const;
	};//end of bst class
	template<class T>
	size_t binary_search_tree<T>::height_aux(node *p)const{
		TinySTL::queue<node *> q, level;
		size_t nlevel = 0;
		if (p != 0){
			level.push(p);
			++nlevel;
			while (!(q.empty() && level.empty())){
				if (level.empty()){
					++nlevel;
					while (!q.empty()){
						level.push(q.front());
						q.pop();
					}
				}
				auto temp = level.front();
				level.pop();
				if (temp->left_ != 0) q.push(temp->left_);
				if (temp->right_ != 0) q.push(temp->right_);
			}
		}
		return nlevel;
	}
	template<class T>
	void binary_search_tree<T>::erase_elem(const T& val, node *&ptr){
		if (ptr == 0)
			return;
		if (ptr->data_ != val){
			if (val < ptr->data_)
				return erase_elem(val, ptr->left_);
			else
				return erase_elem(val, ptr->right_);
		}else{ // found
			if (ptr->left_ != 0 && ptr->right_ != 0){// has two children
				size_t choose = size_ % 2;
				//随机选择删除左右，使得删除操作更平衡
				auto pos = (choose == 0?
					const_cast<node *>(find_min_aux(ptr->right_).ptr_) : const_cast<node *>(find_max_aux(ptr->left_).ptr_));
				ptr->data_ = pos->data_;
				return (choose == 0 ? erase_elem(pos->data_, ptr->right_) : erase_elem(pos->data_, ptr->left_));
			}else{ //has one or no child
				auto temp = ptr;
				if (ptr->left_ == 0)
					ptr = ptr->right_;
				else
					ptr = ptr->left_;
				nodeAllocator::deallocate(temp);
				--size_;
			}
		}
	}
	template<class T>
	void binary_search_tree<T>::erase(const T& val){
		erase_elem(val, root_);
	}
	template<class T>
	void binary_search_tree<T>::insert_elem(const T& val, node *&ptr){//重复的元素不插入
		if (ptr == 0){
			ptr = nodeAllocator::allocate();
			ptr->data_ = val;
			ptr->left_ = ptr->right_ = 0;
			++size_;
		}
		else{
			if (val < ptr->data_){
				return insert_elem(val, ptr->left_);
			}
			else if (val > ptr->data_){
				return insert_elem(val, ptr->right_);
			}
		}
	}
	template<class T>
	void binary_search_tree<T>::insert(const T& val){
		insert_elem(val, root_);
	}
	template<class T>
	template<class Iterator>
	void binary_search_tree<T>::insert(Iterator first, Iterator last){
		for (; first != last; ++first)
			insert(*first);
	}
	template<class T>
	void binary_search_tree<T>::print_levelorder(const string& delim, std::ostream& os)const{
		auto temp = root_;
		if (temp != 0){
			std::deque<node *> q;
			q.push_back(temp);
			while (!q.empty()){
				temp = q.front();
				q.pop_front();
				if (temp->left_ != 0) q.push_back(temp->left_);
				if (temp->right_ != 0) q.push_back(temp->right_);
				os << temp->data_ << delim;
			}
		}
	}
	template<class T>
	void binary_search_tree<T>::print_preorder_aux(const string& delim, std::ostream& os, const node *ptr)const{
		if (ptr){
			os << ptr->data_ << delim;
			print_preorder_aux(delim, os, ptr->left_);
			print_preorder_aux(delim, os, ptr->right_);
		}
	}
	template<class T>
	void binary_search_tree<T>::print_preorder(const string& delim, std::ostream& os)const{
		print_preorder_aux(delim, os, root_);
	}
	template<class T>
	void binary_search_tree<T>::print_inorder_aux(const string& delim, std::ostream& os, const node *ptr)const{
		if (ptr){
			print_inorder_aux(delim, os, ptr->left_);
			os << ptr->data_ << delim;
			print_inorder_aux(delim, os, ptr->right_);
		}
	}
	template<class T>
	void binary_search_tree<T>::print_inorder(const string& delim, std::ostream& os)const{
		print_inorder_aux(delim, os, root_);
	}
	template<class T>
	void binary_search_tree<T>::print_postorder_aux(const string& delim, std::ostream& os, const node *ptr)const{
		if (ptr){
			print_postorder_aux(delim, os, ptr->left_);
			print_postorder_aux(delim, os, ptr->right_);
			os << ptr->data_ << delim;
		}
	}
	template<class T>
	void binary_search_tree<T>::print_postorder(const string& delim, std::ostream& os)const{
		print_postorder_aux(delim, os, root_);
	}
	template<class T>
	typename binary_search_tree<T>::const_iterator binary_search_tree<T>::find_min_aux(const node *ptr){
		while (ptr && ptr->left_ != 0){
			ptr = ptr->left_;
		}
		return const_iterator(ptr, this);
	}
	template<class T>
	typename binary_search_tree<T>::const_iterator binary_search_tree<T>::find_min(){
		return find_min_aux(root_);
	}
	template<class T>
	typename binary_search_tree<T>::const_iterator binary_search_tree<T>::find_max_aux(const node *ptr){
		while (ptr && ptr->right_ != 0){
			ptr = ptr->right_;
		}
		return const_iterator(ptr, this);
	}
	template<class T>
	typename binary_search_tree<T>::const_iterator binary_search_tree<T>::find_max(){
		return find_max_aux(root_);
	}
	template<class T>
	typename binary_search_tree<T>::const_iterator binary_search_tree<T>::find_aux(const T& val, const node *ptr){
		while (ptr){
			if (val == ptr->data_)
				break;
			else if (val < ptr->data_)
				ptr = ptr->left_;
			else
				ptr = ptr->right_;
		}
		return const_iterator(ptr, this);
	}
	template<class T>
	typename binary_search_tree<T>::const_iterator binary_search_tree<T>::find(const T& val){
		return find_aux(val, root_);
	}

	namespace{
		//class of bst iterator
		template<class T>//T = node
		class bst_iter{
		private:
			template<class T>
			friend class binary_search_tree;
		private:
			typedef typename binary_search_tree<typename T::value_type>::value_type value_type;
			typedef typename binary_search_tree<typename T::value_type>::const_reference const_reference;
			typedef typename const T::value_type *const_pointer;
			typedef binary_search_tree<typename T::value_type> * cntrPtr;
		private:
			const T *ptr_;
			cntrPtr container_;
			stack<const T *> parent_;//保存从root到ptr_的父节点的路径
			std::set<const T *> visited_;
		public:
			bst_iter(const T *ptr, cntrPtr container)
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

			bst_iter left()const{ return bst_iter(ptr_->left_, container_); }
			bst_iter right()const{ return bst_iter(ptr_->right_, container_); }

			bst_iter& operator ++();
			bst_iter operator ++(int);
			bst_iter& operator --();
			bst_iter operator --(int);
		public:
			template<class T>
			friend bool operator ==(const bst_iter<T>& it1, const bst_iter<T>& it2);
			template<class T>
			friend bool operator !=(const bst_iter<T>& it1, const bst_iter<T>& it2);
		};//end of bst_iter
		template<class T>
		bst_iter<T>& bst_iter<T>::operator ++(){
			visited_.insert(ptr_);//设为已访问
			if (ptr_->right_ != 0){
				parent_.push(ptr_);
				ptr_ = ptr_->right_;
				while (ptr_ != 0 && ptr_->left_ != 0){
					parent_.push(ptr_);
					ptr_ = ptr_->left_;
				}
			}else{
				if (!parent_.empty() && visited_.count(parent_.top()) == 0){//父节点未访问
					ptr_ = parent_.top();
					parent_.pop();
				}else{
					ptr_ = 0;
				}
			}
			return *this;
		}
		template<class T>
		bst_iter<T> bst_iter<T>::operator ++(int){
			auto res = *this;
			++*this;
			return res;
		}
		template<class T>
		bst_iter<T>& bst_iter<T>::operator --(){
			visited_.erase(ptr_);//设为未访问
			if (ptr_->left_ != 0){
				parent_.push(ptr_);
				ptr_ = ptr_->left_;
				while (ptr_ && ptr_->right_){
					parent_.push(ptr_);
					ptr_ = ptr_->right_;
				}
			}else{
				if (!parent_.empty() && visited_.count(parent_.top()) == 1){//父节点已经访问了
					ptr_ = parent_.top();
					parent_.pop();
				}
			}
			return *this;
		}
		template<class T>
		bst_iter<T> bst_iter<T>::operator --(int){
			auto res = *this;
			--*this;
			return res;
		}
		template<class T>
		bool operator ==(const bst_iter<T>& it1, const bst_iter<T>& it2){
			return it1.ptr_ == it2.ptr_;
		}
		template<class T>
		bool operator !=(const bst_iter<T>& it1, const bst_iter<T>& it2){
			return !(it1 == it2);
		}
	}
}

#endif