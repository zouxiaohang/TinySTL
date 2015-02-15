#ifndef _AVL_TREE_IMPL_H_
#define _AVL_TREE_IMPL_H_

namespace TinySTL{
	namespace Detail{
		template<class T>
		avl_iter<T>::avl_iter(const T *ptr, cntrPtr container)
			:ptr_(ptr), container_(container){
			if (!ptr_)
				return;
			auto temp = container_->root_;
			while (temp && temp != ptr_ && temp->data_ != ptr_->data_){
				parent_.push(temp);
				if (temp->data_ < ptr_->data_){
					//temp向右走说明temo指向的父节点不需要再次访问了
					visited_.insert(temp);//add 2015.01.14
					temp = temp->right_;
				}
				else if (temp->data_ > ptr_->data_){
					temp = temp->left_;
				}
			}
		}
		template<class T>
		avl_iter<T>& avl_iter<T>::operator ++(){
			visited_.insert(ptr_);//此node被访问
			if (ptr_->right_){//此node还有右子树
				//rvisited_.insert(ptr_);
				parent_.push(ptr_);
				ptr_ = ptr_->right_;
				while (ptr_ && ptr_->left_){
					parent_.push(ptr_);
					ptr_ = ptr_->left_;
				}
			}else{//node无右子树则只能向父节点路径移动
				ptr_ = 0;//add 2015.01.14
				while (!parent_.empty()){
					ptr_ = parent_.top();
					parent_.pop();
					if (visited_.count(ptr_) == 0){//父节点尚未访问,此时ptr_指向此节点
						visited_.insert(ptr_);
						break;
					}
					ptr_ = 0;//设为哨兵
				}//end of while
			}//end of if
			return *this;
		}
		template<class T>
		avl_iter<T> avl_iter<T>::operator ++(int){
			auto res = *this;
			++*this;
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
	}//end of Detail namespace

	template<class T>
	typename avl_tree<T>::node *avl_tree<T>::singleLeftLeftRotate(node *k2){
		auto k1 = k2->left_;
		k2->left_ = k1->right_;
		k1->right_ = k2;
		k2->height_ = max(getHeight(k2->left_), getHeight(k2->right_)) + 1;
		k1->height_ = max(getHeight(k1->left_), k2->height_) + 1;
		return k1;
	}
	template<class T>
	typename avl_tree<T>::node *avl_tree<T>::doubleLeftRightRotate(node * k3){
		k3->left_ = singleRightRightRotate(k3->left_);
		return singleLeftLeftRotate(k3);
	}
	template<class T>
	typename avl_tree<T>::node *avl_tree<T>::doubleRightLeftRotate(node * k3){
		k3->right_ = singleLeftLeftRotate(k3->right_);
		return singleRightRightRotate(k3);
	}
	template<class T>
	typename avl_tree<T>::node *avl_tree<T>::singleRightRightRotate(node * k2){
		auto k1 = k2->right_;
		k2->right_ = k1->left_;
		k1->left_ = k2;
		k2->height_ = max(getHeight(k2->left_), getHeight(k2->right_)) + 1;
		k1->height_ = max(k2->height_, getHeight(k1->right_)) + 1;
		return k1;
	}
	template<class T>
	void avl_tree<T>::destroyAndDeallocateAllNodes(node *p){
		if (p != 0){
			destroyAndDeallocateAllNodes(p->left_);
			destroyAndDeallocateAllNodes(p->right_);
			dataAllocator::destroy(p);
			dataAllocator::deallocate(p);
		}
	}
	template<class T>
	avl_tree<T>::~avl_tree(){
		destroyAndDeallocateAllNodes(root_);
	}
	template<class T>
	void avl_tree<T>::erase_elem(const T& val, node *&p){
		if (p == 0)
			return;
		if (p->data_ != val){
			if (val < p->data_)
				return erase_elem(val, p->left_);
			else
				return erase_elem(val, p->right_);
		}else{ // found
			if (p->left_ != 0 && p->right_ != 0){// has two children
				size_t choose = size_ % 2;
				//随机选择删除左右，使得删除操作更平衡
				auto pos = (choose == 0 ?
					const_cast<node *>(find_min_aux(p->right_).ptr_) : const_cast<node *>(find_max_aux(p->left_).ptr_));
				p->data_ = pos->data_;
				return (choose == 0 ? erase_elem(pos->data_, p->right_) : erase_elem(pos->data_, p->left_));
			}else{ //has one or no child
				auto temp = p;
				if (p->left_ == 0)
					p = p->right_;
				else
					p = p->left_;
				dataAllocator::destroy(temp);
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
			dataAllocator::construct(p);
			p->data_ = val;
			p->left_ = p->right_ = 0;
			p->height_ = 1;
			++size_;
		}
		else if (p->data_ < val){
			insert_elem(val, p->right_);
			if (getHeight(p->right_) - getHeight(p->left_) == 2){
				if (val > p->right_->data_)
					p = singleRightRightRotate(p);
				else
					p = doubleRightLeftRotate(p);
			}
		}
		else if (p->data_ > val){
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
	typename avl_tree<T>::const_iterator avl_tree<T>::find_aux(const T& val, const node *ptr)const{
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
	typename avl_tree<T>::const_iterator avl_tree<T>::find(const T& val)const{
		return find_aux(val, root_);
	}
	template<class T>
	typename avl_tree<T>::const_iterator avl_tree<T>::find_max_aux(const node *ptr)const{
		while (ptr != 0 && ptr->right_ != 0)
			ptr = ptr->right_;
		return const_iterator(ptr, this);
	}
	template<class T>
	typename avl_tree<T>::const_iterator avl_tree<T>::find_max()const{
		return find_max_aux(root_);
	}
	template<class T>
	typename avl_tree<T>::const_iterator avl_tree<T>::find_min_aux(const node *ptr)const{
		while (ptr != 0 && ptr->left_ != 0)
			ptr = ptr->left_;
		return const_iterator(ptr, this);
	}
	template<class T>
	typename avl_tree<T>::const_iterator avl_tree<T>::find_min()const{
		return find_min_aux(root_);
	}
}

#endif