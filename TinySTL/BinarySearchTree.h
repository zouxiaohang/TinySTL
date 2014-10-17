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
			T data_;
			node *left_;
			node *right_;
		};
		typedef TinySTL::allocator<node> nodeAllocator;
	public:
		typedef T vaule_type;
		typedef bst_iter<node> iterator;
		typedef T& reference;
	private:
		node *root_;
	public:
		binary_search_tree() :root_(0){}
		binary_search_tree(const binary_search_tree&) = delete;
		binary_search_tree& operator=(const binary_search_tree&) = delete;
		~binary_search_tree(){}//TODO

		void insert(const T& val);

		void print_preorder(const string& delim = " ", std::ostream& os = std::cout)const;
		void print_inorder(const string& delim = " ", std::ostream& os = std::cout)const;
		void print_postorder(const string& delim = " ", std::ostream& os = std::cout)const;
	private:
		void insert_elem(const T& val, node *&ptr);
		void print_preorder_aux(const string& delim, std::ostream& os, const node *ptr)const;
		void print_inorder_aux(const string& delim, std::ostream& os, const node *ptr)const;
		void print_postorder_aux(const string& delim, std::ostream& os, const node *ptr)const;
	};//end of bst class
	template<class T>
	void binary_search_tree<T>::insert_elem(const T& val, node *&ptr){
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

	namespace{
		//class of bst iterator
		template<class T>
		class bst_iter{};
	}
}

#endif