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
			explicit node(T d = T(), node *l = 0, node *r = 0, size_t h = 1)
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

		void insert(const T& val);
		template<class Iterator>
		void insert(Iterator first, Iterator last);
		void erase(const T& val);

		size_t height()const{ return getHeight(root_); }
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
		node *singleLeftLeftRotate(node *k2){
			auto k1 = k2->left_;
			k2->left_ = k1->right_;
			k1->right_ = k2;
			k2->height_ = max(getHeight(k2->left_), getHeight(k2->right_)) + 1;
			k1->height_ = max(getHeight(k1->left_), k2->height_) + 1;
			return k1;
		}
		node *doubleLeftRightRotate(node * k3){
			k3->left_ = singleRightRightRotate(k3->left_);
			return singleLeftLeftRotate(k3);
		}
		node *doubleRightLeftRotate(node * k3){
			k3->right_ = singleLeftLeftRotate(k3->right_);
			return singleRightRightRotate(k3);
		}
		node *singleRightRightRotate(node * k2){
			auto k1 = k2->right_;
			k2->right_ = k1->left_;
			k1->left_ = k2;
			k2->height_ = max(getHeight(k2->left_), getHeight(k2->right_)) + 1;
			k1->height_ = max(k2->height_, getHeight(k1->right_)) + 1;
			return k1;
		}
	private:
		void insert_elem(const T& val, node *&p);
		void erase_elem(const T& val, node *&p);
		void destroyAndDeallocateAllNodes(node *p){
			if (p != 0){
				destroyAndDeallocateAllNodes(p->left_);
				destroyAndDeallocateAllNodes(p->right_);
				dataAllocator::destroy(p);
				dataAllocator::deallocate(p);
			}
		}
		size_t getHeight(const node *p)const{ return p == 0 ? 0 : p->height_; }
		const_iterator find_min_aux(const node *ptr);
		const_iterator find_max_aux(const node *ptr);
		const_iterator find_aux(const T& val, const node *ptr);
		void print_preorder_aux(const string& delim, std::ostream& os, const node *ptr)const;
		void print_inorder_aux(const string& delim, std::ostream& os, const node *ptr)const;
		void print_postorder_aux(const string& delim, std::ostream& os, const node *ptr)const;
	};// end of avl_tree
	template<class T>
	void avl_tree<T>::erase_elem(const T& val, node *&p){
		if (p == 0)
			return;
		if (p->data_ < val){
			erase_elem(val, p->right_);
		}else if (p->data_ > val){
			erase_elem(val, p->left_);
		}else{// found
			if (p->left_ != 0 && p->right_ != 0){//has two children
				size_t choose = size_ % 2;
				//随机选择删除左右，使得删除操作更平衡
				auto pos = (choose == 0 ?
					const_cast<node *>(find_min_aux(p->right_).ptr_) : const_cast<node *>(find_max_aux(p->left_).ptr_));
				p->data_ = pos->data_;
				(choose == 0 ? erase_elem(pos->data_, p->right_) : erase_elem(pos->data_, p->left_));
			}else{ //has one or no child
				auto temp = p;
				if (p->left_ == 0)
					p = p->right_;
				else
					p = p->left_;
				dataAllocator::deallocate(temp);
				--size_;
			}
		}
		if (p != 0){//最后更新p的节点高度信息和旋转维持平衡
			p->height_ = max(getHeight(p->left_), getHeight(p->right_)) + 1;
			if (getHeight(p->left_) - getHeight(p->right_) == 2){
				if (p->left_->right_ == 0)
					singleLeftLeftRotate(p);
				else
					doubleLeftRightRotate(p);
			}else if (getHeight(p->right_) - getHeight(p->left_) == 2){
				if (p->right_->left_ == 0)
					singleRightRightRotate(p);
				else
					doubleRightLeftRotate(p);
			}
		}
	}
	template<class T>
	void avl_tree<T>::erase(const T& val){
		return erase_elem(val, root_);
	}
	template<class T>
	void avl_tree<T>::insert_elem(const T& val, node *&p){
		if (p == 0){
			p = dataAllocator::allocate();
			//p->data_ = val;
			construct(&(p->data_), val);
			p->left_ = p->right_ = 0;
			p->height_ = 1;
			++size_;
		}else if (p->data_ < val){
			insert_elem(val, p->right_);
			if (getHeight(p->right_) - getHeight(p->left_) == 2){
				if (val > p->right_->data_)
					p = singleRightRightRotate(p);
				else
					p = doubleRightLeftRotate(p);
			}
		}else{
			insert_elem(val, p->left_);
			if (getHeight(p->left_) - getHeight(p->right_) == 2){
				if (val < p->left_->data_)
					p = singleLeftLeftRotate(p);
				else
					p = doubleLeftRightRotate(p);
			}
		}
		p->height_ = max(getHeight(p->left_), getHeight(p->right_)) + 1;
	}
	template<class T>
	void avl_tree<T>::insert(const T& val){
		return insert_elem(val, root_);
	}
	template<class T>
	template<class Iterator>
	void avl_tree<T>::insert(Iterator first, Iterator last){
		for (; first != last; ++first)
			insert(*first);
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
				if (temp->right_ != 0) q.push_back(temp->right_);
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