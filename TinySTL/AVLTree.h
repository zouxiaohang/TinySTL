#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include "Allocator.h"

namespace TinySTL{
	//class of avl tree
	template<class T>
	class avl_tree{
	public:
		typename T value_type;
	private:
		struct node{
			T data_;
			node *left_, *right_;
			size_t height_;
			explicit node(T d = T(), node *l = 0, node *r = 0, size_t h = 0)
				:data_(d), left_(l), right_(r), height_(h){}
		};
		typedef TinySTL::allocator<T> dataAllocator;
	private:
		node *root_;
	public:
		avl_tree() :root_(0){}
		avl_tree(const avl_tree&) = delete;
		avl_tree& operator = (const avl_tree&) = delete;
		~avl_tree(){ destroyAndDeallocateAllNodes(root_); }
	private:
		void destroyAndDeallocateAllNodes(node *p){
			if (p != 0){
				destroyAndDeallocateAllNodes(p->left_);
				destroyAndDeallocateAllNodes(p->right_);
				dataAllocator::destroy(p);
				dataAllocator::deallocate(p);
			}
		}
	};
}

#endif