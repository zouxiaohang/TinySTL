#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_

#include "Allocator.h"
#include "String.h"

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
		};
		typedef TinySTL::allocator<node> nodeAllocator;
	public:
		typedef T vaule_type;
		typedef bst_iter<node> const_iterator;
		typedef const T& const_reference;
	private:
		node *root_;
	public:
		binary_search_tree() :root_(0){}
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

		const_iterator find_min();
		const_iterator find_max();
		const_iterator find(const T& val);

		void print_preorder(const string& delim = " ", std::ostream& os = std::cout)const;
		void print_inorder(const string& delim = " ", std::ostream& os = std::cout)const;
		void print_postorder(const string& delim = " ", std::ostream& os = std::cout)const;
	private:
		void deallocateAllNodes(node *ptr){
			if (ptr){
				deallocateAllNodes(ptr->left_);
				deallocateAllNodes(ptr->right_);
				nodeAllocator::deallocate(ptr);
			}
		}
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
	void binary_search_tree<T>::erase_elem(const T& val, node *&ptr){
		if (ptr == 0)
			return;
		if (ptr->data_ != val){
			if (val < ptr->data_)
				erase_elem(val, ptr->left_);
			else
				erase_elem(val, ptr->right_);
		}else{ // found
			if (ptr->left_ != 0 && ptr->right_ != 0){// has two children
				auto pos = const_cast<node *>(find_min_aux(ptr->right_).ptr_);
				ptr->data_ = pos->data_;
				erase_elem(pos->data_, ptr->right_);
			}else{ //has one or no child
				nodeAllocator::deallocate(ptr);
				if (ptr->left_ == 0)
					ptr = ptr->right_;
				else
					ptr = ptr->left_;
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
		return const_iterator(ptr);
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
		return const_iterator(ptr);
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
		return const_iterator(ptr);
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
			typedef typename binary_search_tree<typename T::value_type>::vaule_type value_type;
			typedef typename binary_search_tree<typename T::value_type>::const_reference const_reference;
			typedef typename const T::value_type *const_pointer;
		private:
			const T *ptr_;
		public:
			bst_iter(const T *ptr) :ptr_(ptr){}

			operator const T*(){ return ptr_; }
			const_reference operator*(){ return ptr_->data_; }
			const_pointer operator ->(){ return &(operator*()); }
		public:
			template<class T>
			friend bool operator ==(const bst_iter<T>& it1, const bst_iter<T>& it2);
			template<class T>
			friend bool operator !=(const bst_iter<T>& it1, const bst_iter<T>& it2);
		};
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